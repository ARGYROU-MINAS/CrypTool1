//////////////////////////////////////////////////////////////////
//
// Copyright 1998-2001 Deutsche Bank AG, Frankfurt am Main
//
// SecudeTools
//
// $Id$
//
// Toolbox for complex Secude SDK operations
//
// 2001 Martin Bartosch <m.bartosch@cynops.de>; Cynops GmbH
//
// $Log$
// Revision 1.1  2001/11/09 15:37:35  idj100
// Sourcen von Martin Bartosch mit Eingebunden
// RSA-Demo überarbeitet
//
//

#include "stdafx.h"

#include <pem.h>

#include "multipad.h"
#include "SecudeTools.h"


ObjId * CrypToolPSEName_OID()
{
	static ObjId oid;
	static unsigned int oid_n[6] = { 2, 206, 5, 4, 3, 2 };

	oid.oid_nelem = 6;
	oid.oid_elements = oid_n;

	return(&oid);
}


static char * basename(char *psename)
{
    char *pos;

    if ((pos = strrchr(psename, PATH_SEPARATION_CHAR)))
		pos++;
    else
		pos = psename;

    return theApp.SecudeLib.aux_cpy_String(pos);
}



// store key and certificate in P12 bag structureput key and cert in bag (P12) structure, "consume" cert and keyId */
static void store_kc(P12_Bag ***P12bagpp, 
					 OctetString *lkid, 
					 KeyInfo *key,
					 Certificate *cert,
					 OctetString *name, 
					 int encrypt_priv_key)
{
    P12_Bag **P12bagp = *P12bagpp, *P12bag = **P12bagpp;

    // store private key
    P12bag = *P12bagp = (P12_Bag*) theApp.SecudeLib.aux_malloc(sizeof(P12_Bag));
	memset(P12bag, 0, sizeof(P12_Bag));
    P12bag->int_encryption = encrypt_priv_key;
    P12bag->type = P12_bc_key;
    P12bag->friendlyName = theApp.SecudeLib.aux_cpy_OctetString(name);
    P12bag->localKeyID = theApp.SecudeLib.aux_cpy_OctetString(lkid);
    P12bag->additionalAttr = NULL;
    P12bag->content.key = theApp.SecudeLib.aux_create_PrivateKeyInfo(key, cert, NULL);

    // store certificate
    P12bag = P12bag->next = (P12_Bag*) theApp.SecudeLib.aux_malloc(sizeof(P12_Bag));
	memset(P12bag, 0, sizeof(P12_Bag));
    P12bag->int_encryption = TRUE;
    P12bag->type = P12_bc_cert;
    P12bag->friendlyName = name;
    P12bag->localKeyID = lkid; // use object allocated by caller
    P12bag->additionalAttr = NULL;
    P12bag->content.cert = cert;
	P12bag->next = NULL;

    *P12bagpp = &(P12bag->next); 

    return;
}




OctetString *PKCS12_encode(PSE pse, OctetString * PIN, int iterationcount, int encrypt_priv_key)
{
	P12_Safe P12safe;
    P12_Bag **P12bagp, *P12bag;
	char *name;
	ObjId oid;
    KeyInfo *key;
    Certificate *cert, *rootcert;
    SET_OF_Certificate *certset;
    OctetString *lkid;
    OctetString ostr;
    char oarr[4] = { 0x01, 0x00, 0x00, 0x00 };
    FCPath *fcpath, *fcpath_ptr;
    PKRoot *pkroot;
	int rc;

	OctetString *P12container;

    // local key IDs
    ostr.noctets = 4; 
	ostr.octets = oarr;
	
    memset(&P12safe, 0, sizeof(P12safe));
    P12safe.version = 3;
    P12safe.iterationCount = iterationcount;

    // algorithms
    P12safe.alg_oid.mac   = theApp.SecudeLib.aux_cpy_ObjId(theApp.SecudeLib.sha1_oid);
    P12safe.alg_oid.enc   = theApp.SecudeLib.aux_cpy_ObjId(theApp.SecudeLib.pbeWithSHA1And40BitRC2CBC_oid);
    P12safe.alg_oid.espvk = theApp.SecudeLib.aux_cpy_ObjId(theApp.SecudeLib.pbeWithSHA1AndDES3xCBC_oid);

    P12safe.bags = NULL;
    P12bagp = &P12safe.bags;

	name = basename(pse->pse_name);

	// cryptool only supports one key pair per PSE. if this changes in the future,
	// this code must be extended
    if (theApp.SecudeLib.sec_onekeypaironly(theApp.SecudeLib.af_get_PSESel(pse, NULL))) 
	{
		// retrieve PSE objects
		cert = (Certificate *) theApp.SecudeLib.af_pse_get(pse, "Cert", &oid);
		key = (KeyInfo *) theApp.SecudeLib.af_pse_get(pse, "SKnew", &oid);
		if (!cert || !key) 
			return NULL;

		lkid = theApp.SecudeLib.aux_cpy_OctetString(&ostr);
		store_kc(&P12bagp, lkid, key, cert, theApp.SecudeLib.aux_latin1_to_unicode(name, FALSE), encrypt_priv_key);
		/* don't free lkid and cert; they are "consumed" by stuff_key_cert */
		theApp.SecudeLib.aux_free_KeyInfo(&key);
    } 
	else 
		return NULL;

    theApp.SecudeLib.aux_free_String(&name);

    fcpath = theApp.SecudeLib.af_pse_get_FCPath(pse, NULL);
    if (fcpath) 
	{
		for (fcpath_ptr = fcpath; fcpath_ptr; fcpath_ptr= fcpath_ptr->next_forwardpath) 
			for (certset = fcpath_ptr->liste; certset && certset->element; certset = certset->next) 
			{
				// add all available certificates
				P12bag = *P12bagp = (P12_Bag*) theApp.SecudeLib.aux_malloc(sizeof(P12_Bag));
				memset(P12bag, 0, sizeof(P12_Bag));
				P12bag->int_encryption = TRUE;
				P12bag->type = P12_bc_cert;
				P12bag->friendlyName = NULL; // should we set something more informative...?
				P12bag->localKeyID = NULL; // no local key
				P12bag->additionalAttr = NULL;
				P12bag->content.cert = certset->element; 
				certset->element = NULL;
				P12bag->next = NULL;

				P12bagp = &(P12bag->next);
		    }
		theApp.SecudeLib.aux_free_FCPath(&fcpath);
	} 
	else
		theApp.SecudeLib.aux_free_error();

	pkroot = theApp.SecudeLib.af_pse_get_PKRoot(pse);
	if (pkroot) 
	{
		rootcert = theApp.SecudeLib.af_PKRoot2Protocert(pkroot);
		theApp.SecudeLib.aux_free_PKRoot(&pkroot);

		// we should now have the root certificate

		// add cert
		P12bag = *P12bagp = (P12_Bag*) theApp.SecudeLib.aux_malloc(sizeof(P12_Bag));
		memset(P12bag, 0, sizeof(P12_Bag));
		P12bag->int_encryption = TRUE;
		P12bag->type = P12_bc_cert;
		P12bag->friendlyName = NULL; // ???
		P12bag->localKeyID = NULL; // no local key
		P12bag->additionalAttr = NULL;
		P12bag->content.cert = rootcert;
		P12bag->next = NULL;

		P12bagp = &(P12bag->next);
	}


	P12container = theApp.SecudeLib.aux_alloc_OctetString();
	P12container->octets = NULL;
	P12container->noctets = 0;
	
	rc = theApp.SecudeLib.pkcs12_encode(&P12safe, PIN, P12container);
	// FIXME: error handling?

	return(P12container);
}



// import 
int PKCS12_import(PSE pse, OctetString *input, OctetString *password, int newpse)
{
    P12_Safe P12safe;
	char verified;
    P12_Bag *thisbag;
	int rc, keys, certs, ii, ok, bags;
	Certificate *thiscert;
    FCPath *fcpath, *fcpathp, *fcpathlast;
	PKRoot *pkroot;
    PSESel *psesel;
	OctetString *ostr;
	char *name;
	char *ext;
	RSAPrivateKey * rsaprivkey;
    KeyInfo *keyinfo;
    KeyBits *keybits;
    BitString *bitstr;

    memset(&P12safe, 0, sizeof(P12safe));
    verified = 0;

    rc = theApp.SecudeLib.pkcs12_decode(input, password, &P12safe, &verified);
    
    if (rc) 
		return(rc);

    if (!verified) 
		return(-1);
	
    certs = 0;
	keys = 0;

    for (thisbag = P12safe.bags; thisbag; thisbag = thisbag->next) 
	{
		switch (thisbag->type) 
		{
			case P12_bc_key:
				keys++; 
				break;
			case P12_bc_cert:
				certs++; 
				break;
		}
    }

    if (keys != 1) 
	{
		// FIXME: more than one key pair is not supported
		return(-1);
    }

	

    thiscert = NULL; 
    fcpath = NULL;
	fcpathp = NULL;
	fcpathlast = NULL;

    if (newpse) 
	{
		for (ii = 0; ii < certs; ii++) 
		{
			for (thisbag = P12safe.bags; thisbag; thisbag = thisbag->next)
				if (thisbag->type == P12_bc_cert) 
				{
					if (!thiscert)
						if (thisbag->localKeyID) // own certificate
						{
							thiscert = thisbag->content.cert; 
							thisbag->content.cert = NULL;
							thisbag->type = (enum P12_BagContent) -2; // flag this bag for memory deletion
							break;
						} 
						else
							continue;

					ok = FALSE;

					if (fcpathp) 
						ok = (!theApp.SecudeLib.aux_cmp_DName(fcpathp->liste->element->tbs->issuer,
								thisbag->content.cert->tbs->subject));
					else 
						ok = (!theApp.SecudeLib.aux_cmp_DName(thiscert->tbs->issuer,
								thisbag->content.cert->tbs->subject));

					if (ok) 
					{
						fcpathlast = fcpathp;

						if (!fcpathp) 
						{
							fcpath = (FCPath *) theApp.SecudeLib.aux_malloc(sizeof(FCPath));
							memset(fcpath, 0, sizeof(FCPath));
							fcpathp = fcpath;
						}
						else
						{
							fcpathp->next_forwardpath = (FCPath *) theApp.SecudeLib.aux_malloc(sizeof(FCPath));
							memset(fcpathp->next_forwardpath, 0, sizeof(FCPath));
							fcpathp = fcpathp->next_forwardpath;
						}
						fcpathp->liste = (SET_OF_Certificate *) theApp.SecudeLib.aux_malloc(sizeof(SET_OF_Certificate));
						memset(fcpathp->liste, 0, sizeof(SET_OF_Certificate));
						fcpathp->liste->element = thisbag->content.cert; 
						thisbag->content.cert = NULL;
						thisbag->type = (enum P12_BagContent) -2; // flag this bag for memory deletion
						break;
					}
				}
			if (!thisbag) // loop was terminated without being left with "break"
			{ 
				fprintf(stderr, "internal error: loop not left with break\n");
				return -2;
			}
		}

		if (fcpathp) 
		{
			if (theApp.SecudeLib.aux_cmp_DName(fcpathp->liste->element->tbs->issuer, 
				fcpathp->liste->element->tbs->subject)) 
			{
				fprintf(stderr, "internal error: root is no root\n");
				return -3;
			}
			pkroot = theApp.SecudeLib.aux_create_PKRoot(fcpathp->liste->element, NULL);
			fcpathp->liste->element = NULL;
			if (fcpathp)
				theApp.SecudeLib.aux_free_FCPath(&fcpathp);
			if (fcpathlast) 
				fcpathlast->next_forwardpath = NULL;
		    else
				fcpath = NULL;

		    // write PKRoot to PSE (using SECURE interface because of OID)
		    psesel = theApp.SecudeLib.af_get_PSESel(pse, (ObjId *) 0);
			psesel->object = theApp.SecudeLib.aux_cpy_String(PKRoot_name);
			psesel->object_type = theApp.SecudeLib.PKRoot_oid;
		    ostr = theApp.SecudeLib.e_PKRoot(pkroot);
		    theApp.SecudeLib.sec_write_PSE(psesel, ostr);
			theApp.SecudeLib.aux_free_OctetString(&ostr);
		}
		if (fcpath) 
		{
			// write FCPath to PSE (using SECURE IF, because of OID)
			psesel = theApp.SecudeLib.af_get_PSESel(pse, (ObjId *) 0);
			psesel->object = theApp.SecudeLib.aux_cpy_String(FCPath_name);
			psesel->object_type = theApp.SecudeLib.FCPath_oid;
		    ostr = theApp.SecudeLib.e_FCPath(fcpath);
		    theApp.SecudeLib.sec_write_PSE(psesel, ostr);
			theApp.SecudeLib.aux_free_OctetString(&ostr);
		}

		// write Cert to PSE (using SECURE IF, because of OID)
		psesel = theApp.SecudeLib.af_get_PSESel(pse, (ObjId *) 0);
		psesel->object = theApp.SecudeLib.aux_cpy_String(Cert_name);
		psesel->object_type = theApp.SecudeLib.Cert_oid;
		ostr = theApp.SecudeLib.e_Certificate(thiscert);
		theApp.SecudeLib.sec_write_PSE(psesel, ostr);
		theApp.SecudeLib.aux_free_OctetString(&ostr);
    }



    for (thisbag = P12safe.bags, bags = 1; thisbag; thisbag = thisbag->next, bags++) 
	{
		name = NULL;
		if (newpse) 
		{
			switch (thisbag->type) 
			{
				case P12_bc_key:
					name = theApp.SecudeLib.aux_cpy_String(SKnew_name); 
					break;
				case P12_bc_cert:
					name = theApp.SecudeLib.aux_cpy_String(Cert_name); 
					break;
		    }
		}
		if (!name) // existing_pse
		{
			switch (thisbag->type) 
			{
				case P12_bc_key:
					ext = "_key"; 
					break;
				case P12_bc_cert:
					ext = "_cert"; 
					break;
				default:
					ext = "";
			}
			name = (char *) theApp.SecudeLib.aux_malloc(strlen(ext) + 20);
			sprintf(name, "p12_%d%s", bags, ext);
		}
	
		switch (thisbag->type) 
		{
			case P12_bc_key:
				switch (theApp.SecudeLib.aux_ObjId2AlgEnc(thisbag->content.key->privateKeyAlgorithm->objid)) 
				{
					case RSA:
						rsaprivkey = theApp.SecudeLib.d_RSAPrivateKey(thisbag->content.key->privateKey);
						if (!rsaprivkey) 
						{
							fprintf(stderr, "could not decode RSAPrivateKey\n");
						    return -1;
						}

						if (rsaprivkey->pubex.noctets != 3) 
						{
							fprintf(stderr, "pubex not F4!?!\n"); // FIXME
							return -1;
						}

						keybits = (KeyBits *) theApp.SecudeLib.aux_malloc(sizeof(KeyBits));
						memset(keybits, 0, sizeof(KeyBits));
						keybits->part1.noctets = rsaprivkey->prime1.noctets;
						keybits->part1.octets = rsaprivkey->prime1.octets; 
						rsaprivkey->prime1.octets = NULL;
						keybits->part2.noctets = rsaprivkey->prime2.noctets;
						keybits->part2.octets = rsaprivkey->prime2.octets; 
						rsaprivkey->prime1.octets = NULL;

						bitstr = theApp.SecudeLib.e_KeyBits(keybits);

						keyinfo = (KeyInfo *) theApp.SecudeLib.aux_malloc(sizeof(KeyInfo));
						memset(keyinfo, 0, sizeof(KeyInfo));
						keyinfo->subjectkey.nbits = bitstr->nbits;
						keyinfo->subjectkey.bits = bitstr->bits; 
						bitstr->bits = NULL;
						keyinfo->subjectAI = theApp.SecudeLib.aux_cpy_AlgId(thisbag->content.key->privateKeyAlgorithm);

						// write KeyInfo to PSE (using SECURE IF, because of OID)
						psesel = theApp.SecudeLib.af_get_PSESel(pse, (ObjId *) 0);
						psesel->object = name;
						psesel->object_type = theApp.SecudeLib.SKnew_oid;
						ostr = theApp.SecudeLib.e_KeyInfo(keyinfo);
						theApp.SecudeLib.sec_write_PSE(psesel, ostr);

						break;
					default:
						return -1;
			    }
				break;

			case P12_bc_cert:
				if (newpse) // use Cert / FCPath / PKRoot
					break;
				// write Cert to PSE (using SECURE IF, because of OID)
				psesel = theApp.SecudeLib.af_get_PSESel(pse, (ObjId *) 0);
				psesel->object = name;
				psesel->object_type = theApp.SecudeLib.Cert_oid;
				ostr = theApp.SecudeLib.e_Certificate(thisbag->content.cert);
				theApp.SecudeLib.sec_write_PSE(psesel, ostr);
				break;
			case -2:
			    theApp.SecudeLib.aux_free_String(&name); 
				break;
			default:
				theApp.SecudeLib.aux_free_String(&name); 
				fprintf(stderr, "  unsupported bag type\n");
		}
    }



	return(0);
}
