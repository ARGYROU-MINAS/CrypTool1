//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
//////////////////////////////////////////////////////////////////

#ifndef AFX_RSADEC_H__11C1DEFD_F5DB_11D3_8798_00C04F795E36__INCLUDED_
#define AFX_RSADEC_H__11C1DEFD_F5DB_11D3_8798_00C04F795E36__INCLUDED_

// RsaDec.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CRsaDec 

#include "KeyFileHandling.h"

class CRsaDec : public CDialog
{
// Konstruktion
public:
	CRsaDec(CWnd* pParent = NULL);   // Standardkonstruktor

	CString UserKeyId;

// Dialogfelddaten
	//{{AFX_DATA(CRsaDec)
	enum { IDD = IDD_DIALOG_RSADEC };
	CListCtrl	m_listview;
	CEdit	m_PinCodeEditctrl;
	CString	m_PinCode;
	BOOL	m_ShowDuration;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CRsaDec)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementierung
protected:

	int m_lastSelectedRow;
	int sortBy;
	unsigned nKeylistType;

	CString KeyType;
	CString KeyInfo;
	CString Name;
	CString Firstname;
	CString CreatTime;

	void InitAsymKeyListBox(unsigned nLocalKeylistType);
	void UpdateRowSel(int row);
	int GetSpecifRow(UINT mask);

	CSortAsymKeyList sortedAsymKeyList;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CRsaDec)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemclickListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownListKeys(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_RSADEC_H__11C1DEFD_F5DB_11D3_8798_00C04F795E36__INCLUDED_