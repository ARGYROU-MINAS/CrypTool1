//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
//////////////////////////////////////////////////////////////////


#ifndef AFX_DLGSIGN_H__A55D2FEB_B45F_11D2_8D43_00C04F795E36__INCLUDED_
#define AFX_DLGSIGN_H__A55D2FEB_B45F_11D2_8D43_00C04F795E36__INCLUDED_

// DlgSign.h : Header-Datei
//

#include "s_ecFp.h"
#include "KeyFileHandling.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSign 

class CDlgSign : public CDialog
{
// Konstruktion
public:
	CDlgSign(CWnd* pParent = NULL);   // Standardkonstruktor

	CDlgSign::~CDlgSign();

// Dialogfelddaten
	//{{AFX_DATA(CDlgSign)
	enum { IDD = IDD_DIALOG_SIGN };
	CButton	m_CheckSteps;
	CButton	m_pcRadio;
	CButton	m_acRadio;
	CButton	m_RadioECNR;
	CButton	m_RadioECDSA;
	CButton	m_RadioDSA;
	CButton	m_RadioRSA;
	CButton	m_CheckRSA;
	CButton	m_CheckDSA;
	CButton	m_CheckEC;
	CListCtrl	m_listview;
	CButton	m_ctrl11;
	CButton	m_ctrl15;
	CButton	m_ctrl14;
	CButton	m_ctrl13;
	CButton	m_ctrl12;
	CEdit	m_ctrl1;
	CString	m_edit;
	int		m_radio;
	int		m_SignAlg;
	int		m_EcPointRepresModus;
	BOOL	m_ShowDuration;
	BOOL	m_ShowSteps;
	//}}AFX_DATA

	EcDomParam_ac_ptr DomParamAc; // The Domain Parameter (affine coordinates) of the selected elliptic Curve
	EcDomParam_pc_ptr DomParamPc; // The Domain Parameter (projective coordinates) of the selected elliptic Curve

	bool use_affine_coord;// TRUE:affine coordinates;FALSE:projective coordinate

	CString UserKeyId;

	CString Name;
	CString Firstname;
	CString KeyType;

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgSign)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	int m_lastSelectedRow;
	int sortBy;
	unsigned nKeylistType;

	CString KeyInfo;
	CString CreatTime;

	void InitAsymKeyListBox(unsigned nLocalKeylistType);
	int FindRow( CString pattern);
	int GetSpecifRow(UINT mask);
	void EnableAllRadioButtons();
	void UpdateRowSel(int row);
	void FreeEcMemory();

	CSortAsymKeyList sortedAsymKeyList;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSign)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckDsaKeys();
	afx_msg void OnCheckEcKeys();
	afx_msg void OnCheckRsaKeys();
	afx_msg void OnRadioRSA();
	afx_msg void OnRadioDSA();
	afx_msg void OnRadioECDSA();
	afx_msg void OnRadioECNR();
	afx_msg void OnRadioAffinCoord();
	afx_msg void OnRadioProjectCoord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DLGSIGN_H__A55D2FEB_B45F_11D2_8D43_00C04F795E36__INCLUDED_