//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
//////////////////////////////////////////////////////////////////


#ifndef AFX_RSAENC_H__9BB28A41_A60A_11D2_8881_00C04F795E28__INCLUDED_
#define AFX_RSAENC_H__9BB28A41_A60A_11D2_8881_00C04F795E28__INCLUDED_

// RsaEnc.h : Header-Datei
//
#include "KeyFileHandling.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CRsaEnc 

class CRsaEnc : public CDialog
{
// Konstruktion
public:
	CRsaEnc(CWnd* pParent = NULL);   // Standardkonstruktor

	CString Name;
	CString Firstname;
	CString CreatTime;

// Dialogfelddaten
	//{{AFX_DATA(CRsaEnc)
	enum { IDD = IDD_DIALOG_RSAENC };
	CListCtrl	m_listview;
	BOOL	m_ShowDuration;
	//}}AFX_DATA

// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CRsaEnc)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	int m_lastSelectedRow;
	int sortBy;
	unsigned nKeylistType;

	CString KeyType;
	CString KeyInfo;

	CString UserKeyId;

	void InitAsymKeyListBox(unsigned nLocalKeylistType);
	void UpdateRowSel(int row);
	int GetSpecifRow(UINT mask);

	CSortAsymKeyList sortedAsymKeyList;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CRsaEnc)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_RSAENC_H__9BB28A41_A60A_11D2_8881_00C04F795E28__INCLUDED_