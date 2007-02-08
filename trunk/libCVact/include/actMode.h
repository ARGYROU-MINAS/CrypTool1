//////////////////////////////////////////////////////////////////////////////////
// Name:      actMode.h
// Product:   cv act library
// Purpose:   enumerations
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_MODE_H
#define ACT_MODE_H

namespace act
{
	enum
	{
		ENCRYPT=100,
		DECRYPT,
		SIGN,
		VERIFY,
		MAC,

		PRIVATE =200,
		PUBLIC ,
		SECRET ,
		DOMAINPARAMS,
		PKCS8_TYPE,

		CIPHER = 300,
		PADDING,
		DERIVATOR,
		BCMODE,
		KEYSIZE,
		RAWKEY,
		IV,
		BLOCKSIZE,
		EFFECTIVE_KEYSIZE,
		LABEL,

		ENCODER=400,
		PRIVATEKEY,
		PUBLICKEY,
		PUBLICSIZE,
		KEY,
		SIGNATURE,
		AGREEMENT,

		MODULO=500,
		PRIME_P,
		PRIME_Q,
		MODULOSIZE,
		PRIME_P_SIZE,
		PRIME_Q_SIZE,

		CURVE=600,
		PUBLIC_X,
		PUBLIC_Y,
		STATICPUBLIC_X,
		STATICPUBLIC_Y,
		EPHEMERALPUBLIC_X,
		EPHEMERALPUBLIC_Y,
		CURVEPARAM,
		COMPRESSED,
		UNCOMPRESSED,
		HYBRID,
		IMPLICITYCA,
		GF2CURVE, 
		PRIMECURVE,
	
		RING = 700,
		RINGORDER,
		RINGGENERATOR,
		COFACTOR,
		COMPATIBLE,
		NEWEPHEMERAL,
		CHECKDOMAINPARAMS,

		STATICPRIVATEKEY,
		STATICPUBLICKEY,
		EPHEMERALPRIVATEKEY,
		EPHEMERALPUBLICKEY,

		PIN = 800,
		CARDTYPE,
		CARDPORTTYPE,
		PORTNR,
		DLLNAME,
		READERNAME,
		CHANGEMASTERPIN,
		CHANGEPIN,
		USERPIN,
		MASTERPIN,
		PINPAD,
		USERNAME,
		INFOTEXT,
		SIGNKEY,
		ENCKEY,
		SIGNCERTIFICATE,
		ENCCERTIFICATE,
		ROOTCERTIFICATE,
		LOCK_KEY,
		DHKEY,
		DHCERTIFICATE,
		PERSONALIZED,
		READERNAMES,
		AID,
		NULLPIN,
		SELECTKEY,
		ALLCERTIFICATE,
		APPLICATION,//For TCOS
		KEYUSAGE,
		MECHANISM,
		CERTIFICATE,
		KEYTYPE,

		CTAPI_PORT = 900, 
		PCSC_PORT,

		CARDOS_CARD = 1000, 
		TCOS_CARD, 
		CVACT_CARD, 
		PKCS11_CARD,
		MICARDOEC_CARD,
		STARCOSPK_CARD,
		ETRUST_CARD,
//		MICARDOPUBLIC_CARD,
		CARDOSM4_CARD,
		MICARDOP21_CARD,

		HASH=1100,
		SALT,
		SALT_LENGTH,
		EMLEN,

		X = 1200,
		MULTIPLIER,

		VERSION = 1300,
		ISSUER,
		SUBJECT,
		SERIALNR,
		ISSUER_DER,
		SUBJECT_DER,
		ISSUER_UID,
		SUBJECT_UID,
		NOTBEFORE_DER,
		NOTAFTER_DER,
		THISUPDATE_DER,
		NEXTUPDATE_DER,
		TBS,

		// GF(P)-Curves
		SECGp112r1=0x1000,
		SECGp112r2,
		SECGp128r1,
		SECGp128r2,
		SECGp160r1,
		SECGp160r2,
		SECGp160k1,
		ANSIp192r1,
		ANSIp192r2,
		ANSIp192r3,
		NISTp192r1,
		SECGp192r1,
		SECGp192k1,
		NISTp224r1,
		SECGp224r1,
		SECGp224k1,
		ANSIp239r1,
		ANSIp239r2,
		ANSIp239r3,
		ANSIp256r1,
		NISTp256r1,
		SECGp256r1,
		SECGp256k1,
		NISTp384r1,
		NISTp521r1,

		// GF(2^m)-Curves
		SECGz113r1=0x2000,
		SECGz113r2,
		SECGz131r1,
		SECGz131r2,
		ANSIz163r1,
		ANSIz163r2,
		ANSIz163r3,
		NISTz163r1,
		NISTz163k1,
		SECGz163r1,
		SECGz163r2,
		SECGz163k1,
		ANSIz176w1,
		ANSIz191r1,
		ANSIz191r2,
		ANSIz191r3,
		SECGz193r1,
		SECGz193r2,
		ANSIz208w1,
		NISTz233r1,
		NISTz233k1,
		SECGz233r1,
		SECGz233k1,
		ANSIz239r1,
		ANSIz239r2,
		ANSIz239r3,
		SECGz239k1,
		ANSIz272w1,
		NISTz283r1,
		NISTz283k1,
		SECGz283r1,
		SECGz283k1,
		ANSIz304w1,
		ANSIz359r1,
		ANSIz368w1,
		NISTz409r1,
		NISTz409k1,
		SECGz409r1,
		SECGz409k1,
		ANSIz431r1,
		NISTz571r1,
		NISTz571k1,
		SECGz571r1,
		SECGz571k1
	};
}

#endif

