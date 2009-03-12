/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////

#ifndef _keyfilehandling_
#define _keyfilehandling_
#include "s_ecFp.h"
#include "AsymmetricEncryption.h"

#include <time.h>

#include <afxtempl.h>

#define PSE_FILE_SUFFIX ".pse"
#define P12_FILE_SUFFIX ".p12"

class CKeyFile : public CStdioFile
{
public:

	CKeyFile(void);

	//CString KeysTocFile;
	CStdioFile DataFile;
	//int maxLineLength;

	int DeleteUserKeyFiles(CString user_file, CString& passwd, int filetype);
	int CreateEcKeyFiles(CString user, CString& passwd, EcDomParam_ac_ptr userCurveParam, EcDomParamAcAsString *userCurveParamStr);
	int GetEcPublicParam(CString user, EcDomParam_ac_ptr userCurveParam);
	int GetEcAllParam(CString user, CString& passwd, EcDomParam_ac_ptr userCurveParam);
	int GetEcPrivateKey(CString user, CString& passwd, L_NUMBER * privKey);
	bool FilenameExisting(CString user_file);
	CString CreateFilename(CString Name, CString Firstname, CString AlgType, CString KeySize, CString CreatTime, CString KeyInfo);
	CString CreateFilename2(CString Name, CString Firstname, CString AlgTypeWithKeySize, CString CreatTime, CString KeyInfo);
	CString CreateDistName(CString Name, CString Firstname, CString CreatTime);
	int ExtractData(CString filename, char **tcreat, char **creatime, char **name, char **firstname, char **keyType, char **keyID);
};


// Sorting Flags
#define BY_NAME 1
#define BY_FIRSTNAME 2
#define BY_KEYTYPE 3
#define BY_CREATTIME 4
#define BY_PERS_KEYID 5


class CAsymmKeyAttrib
{
public:

	CAsymmKeyAttrib(int sortflag=BY_NAME); // Konstruktor

	CString Name; // Name of owner
	CString Firstname; // Firstname of owner
	CString KeyType; // Key Type {EC-xxx, RSA-xxx, DSA-xxx}
	CString UTCstring; // Time in seconds since UTC 1/1/70
	CString CreatTime; // Datum und Zeit der Erzeugung in menschl. lesbarer Form
	CString PersKeyInfo; // Prrs�nliche Schl�sselkennung des Schl�sselerzeugers

	CString UserKeyfileName; // obige Daten zusammengesetzt zu der Form
	                         // [Name][Firstname][KeyType][CreatTime][KeyInfo]
	int sortby;

	bool operator==(const CAsymmKeyAttrib& a) const // �berladen des Vergleichsoperators
	{
		if (sortby==BY_NAME) return (Name == a.Name);
		else if (sortby==BY_FIRSTNAME) return (Firstname == a.Firstname);
		else if (sortby==BY_KEYTYPE) return (KeyType == a.KeyType);
		else if (sortby==BY_CREATTIME)
		{
			//return (UTCstring == a.UTCstring);

			time_t t1, t2;
			
			LPTSTR string1 = new TCHAR[UTCstring.GetLength()+1];
			strcpy_s(string1,strlen(string1), UTCstring);
			char *cstr1 = string1;

			LPTSTR string2 = new TCHAR[a.UTCstring.GetLength()+1];
			strcpy_s(string2,strlen(string2), a.UTCstring);
			char *cstr2 = string2;

			t1 = atol(cstr1);
			t2 = atol(cstr2);

			delete string1;
			delete string2;

			return (t1 == t2);
		}
		else if (sortby==BY_PERS_KEYID) return (PersKeyInfo == a.PersKeyInfo);
		else return (Name == a.Name); // falls keine der obigen alternativen greift, so Vergleiche die Namen 
	}

	//CAsymmKeyAttrib operator<(const CAsymmKeyAttrib& a) const;

	//bool operator<(const CAsymmKeyAttrib& op2); // �berladen des < Operators

		
	bool operator<(const CAsymmKeyAttrib& a) const // �berladen des < Operators
	{
		if (sortby==BY_NAME) return (Name < a.Name);
		else if (sortby==BY_FIRSTNAME) return (Firstname < a.Firstname);
		else if (sortby==BY_KEYTYPE) return (KeyType < a.KeyType);
		else if (sortby==BY_CREATTIME) return (UTCstring < a.UTCstring);
		else if (sortby==BY_PERS_KEYID) return (PersKeyInfo < a.PersKeyInfo);
		else return (Name < a.Name); // falls keine der obigen alternativen greift, so Vergleiche die Namen 
	}
};

/*
CAsymmKeyAttrib CAsymmKeyAttrib::operator<(const CAsymmKeyAttrib& op2) // �berladen des < Operators
{	
	return (UTCstring < op2.UTCstring);
}
*/

typedef CList <CAsymmKeyAttrib,CAsymmKeyAttrib> CSortAsymKeyList;

/*
bool CSortAsymKeyList::operator<(const CAsymmKeyAttrib& op2) // �berladen des < Operators
{	
	return (UTCstring < op2.UTCstring);
}
*/

#define EC_KEY   1 // nur EC Schl�ssel in die Liste
#define RSA_KEY  2 // nur RSA Schl�ssel in die Liste
#define DSA_KEY  4 // nur DSA Schl�ssel in die Liste
#define ASYM_KEY 7 // alle verf�gbaren asym. Schl�ssel (EC, RSA, DSA) in die Liste

class CAvailabAsymmKeys // : public CAsymmKeyAttrib
{
public:

	CAvailabAsymmKeys(void);
	int GetKeyList(CSortAsymKeyList& sortedAsymKeyList, unsigned nKeyType, int sortflag=BY_NAME);
	// nKeyType gibt an, welche Schl�sselbezeichner in die Liste aufgenommen werden:
	// nKeyType == ASYM_KEY : alle (EC, RSA, DSA)
	// nKeyType == EC_KEY  : nur EC
	// nKeyType == RSA_KEY : nur RSA
	// nKeyType == DSA_KEY : nur DSA
	// nKeyType == RSA_KEY | EC_KEY  : RSA und EC
	// usw.

	int SortList(CSortAsymKeyList& sortedAsymKeyList, int sortby=BY_NAME);

//private:

};

#endif



