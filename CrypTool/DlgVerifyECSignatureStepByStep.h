/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 2000
//////////////////////////////////////////////////////////////////

#ifndef AFX_DLGSIGNVERIFSTEPS_H__AD62EB2F_03C5_11D4_879D_00C04F795E36__INCLUDED_
#define AFX_DLGSIGNVERIFSTEPS_H__AD62EB2F_03C5_11D4_879D_00C04F795E36__INCLUDED_

// DlgSignVerifSteps.h : Header-Datei
//

#include "s_ecFp.h"
#include "AsymmetricEncryption.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgVerifyECSignatureStepByStep 

class CDlgVerifyECSignatureStepByStep : public CDialog
{
// Konstruktion
public:
	CDlgVerifyECSignatureStepByStep(OctetString *msgOcts, bool msgFromFile, CString fname,\
					   EcDomParam_ac_ptr dp_ac,\
					   L_NUMBER *c_in, L_NUMBER *d_in, int signlength,\
					   char *sigalg_id, char *hashalg_id,\
					   CString UserKeyId, CString firstname, CString name,\
					   CString cID, CString cInfo,\
					   BOOL duration, CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CDlgVerifyECSignatureStepByStep)
	enum { IDD = IDD_VERIFY_ECSIGNATURE_STEPBYSTEP };
	CButton	m_OkButtonCtrl;
	CButton	m_RadioOctets;
	CButton	m_RadioHexadezimal;
	CButton	m_RadioDezimal;
	CButton	m_RadioOktal;
	CEdit	m_StepCtrl;
	CEdit	m_SignHexDumpCtrl;
	CEdit	m_MsgHexDumpCtrl;
	CEdit	m_TextVerifStepsCtrl;
	CEdit	m_DataDisplayCtrl;
	CEdit	m_TextSignCtrl;
	CEdit	m_TextMessageCtrl;
	CButton	m_ContinueButtonCtrl;
	CString	m_TextMessage;
	CString	m_TextSign;
	CString	m_DataDisplay;
	CString	m_TextVerifSteps;
	CString	m_MsgHexDump;
	CString	m_SignHexDump;
	CString	m_Step;
	//}}AFX_DATA


// ?berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions?berschreibungen
	//{{AFX_VIRTUAL(CDlgVerifyECSignatureStepByStep)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst?tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CFont m_Font;
	CFont m_Font2;

	EcDomParamAcAsString DomParamAcString;

	clock_t verifStart;
	clock_t verifFinish;
	double duration;

	int base;
	int step;
	int nFirstVisibleLine;
	int hexdumpCols;

	int SignLength;

	int maxsteps;

	OctetString *messageOcts;
	bool messageFromFile;
	EcDomParam_ac_ptr DomParamAc;
	L_NUMBER *c;
	L_NUMBER *d;
	char *SigAlg;
	char *HashAlg;

	CString filename;

	CString UserKeyFile;
	CString Firstname;
	CString Name;
	
	CString curveID;
	CString curveInfo;

	BOOL showDuration;

	typedef struct{
		int rangecheckfailed; // if rangecheckfailed==1 signature is invalid
		__PointAc_struct P; // if P = (inf,inf) signature is invalid; else P=(x,y) on E
		L_NUMBER i[MAXLGTH];
		L_NUMBER f[MAXLGTH];
		unsigned int l;
		L_NUMBER g[MAXLGTH];
	} verif_nr_data_struct;

	verif_nr_data_struct NrVerifData;

	typedef struct{
		CString Px;
		CString Py;
		CString i;
		CString f;
		CString l;
		CString g;
	} NrVerifDataStringStruct;

	NrVerifDataStringStruct NrVerifDataStrings;
	
	typedef struct{
		unsigned int l;
		L_NUMBER f[MAXLGTH];
		int rangecheckfailed; // if rangecheckfailed==1 signature is invalid
		L_NUMBER h[MAXLGTH];
		L_NUMBER h1[MAXLGTH];
		L_NUMBER h2[MAXLGTH];
		__PointAc_struct P; // if P = (inf,inf) signature is invalid; else P=(x,y) on E
		L_NUMBER i[MAXLGTH];
		L_NUMBER c1[MAXLGTH];
	} verif_dsa_data_struct;

	verif_dsa_data_struct DsaVerifData;

	typedef struct{
		CString l;
		CString f;
		CString h;
		CString h1;
		CString h2;
		CString Px;
		CString Py;
		CString i;
		CString c1;
	} DsaVerifDataStringStruct;

	DsaVerifDataStringStruct DsaVerifDataStrings;

	int ecssa_sign_verif_op_ac( /* in */ L_NUMBER *c,
			      L_NUMBER *d,
			      OctetString *M,
			      EcDomParam_ac_ptr Key,
			      char *sign_primitiv_id, /* "ECSP-DSA" or "ECSP-NR" */
			      char *hash_id); /* select hash_id for emsa1: "SHA-1" or "RIPEMD-160" */

	int emsa1_encoding_operation(/*out*/ L_NUMBER *f,
		             /*in   */ OctetString *M,
		                         unsigned int l,
		                         char *hash_id); /* "SHA-1" or "RIPEMD-160" */

	int emsa1_verfication_operation(/* in */ L_NUMBER *f,
			           OctetString *M,
			           unsigned int l,
			           char *hash_id); /* "SHA-1" or "RIPEMD-160" */

	int ecFp_ecvp_dsa_ac( L_NUMBER *c, L_NUMBER *d, ecFp_point_ac_srcptr W, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G, L_NUMBER *r,L_NUMBER *f);

	int ecFp_ecvp_nr_ac(L_NUMBER *c, L_NUMBER *d, ecFp_point_ac_srcptr W, ecFp_curve_srcptr E, ecFp_point_ac_srcptr G,L_NUMBER *r, L_NUMBER *f);

	int UpdateSigEditBox();

	int DsaDataStructToDsaDataStringStruct();
	int NrDataStructToNrDataStringStruct();
	int UpdateDataDisplay();
	void SignatureInvalid();
	void SignatureValid();

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgVerifyECSignatureStepByStep)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonContinue();
	afx_msg void OnRadioOktal();
	afx_msg void OnRadioDezimal();
	afx_msg void OnRadioHexadezimal();
	afx_msg void OnRadioOctets();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f?gt zus?tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSIGNVERIFSTEPS_H__AD62EB2F_03C5_11D4_879D_00C04F795E36__INCLUDED_
