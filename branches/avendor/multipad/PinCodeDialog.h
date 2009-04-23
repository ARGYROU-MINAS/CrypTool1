//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_PINCODEDIALOG_H__F1360882_35D6_11D3_8D69_00C04F795E36__INCLUDED_
#define AFX_PINCODEDIALOG_H__F1360882_35D6_11D3_8D69_00C04F795E36__INCLUDED_

// PinCodeDialog.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CPinCodeDialog 

class CPinCodeDialog : public CDialog
{
// Konstruktion
public:
	CPinCodeDialog(int modus, CString keyinfo, CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CPinCodeDialog)
	enum { IDD = IDD_DIALOG_PINCODE };
	CEdit	m_InfoBoxCtrl;
	CEdit	m_ModusInfoBoxCtrl;
	CEdit	m_PinEditControl;
	CString	m_PinCode;
	CString	m_InfoBox;
	CString	m_ModusInfoBox;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CPinCodeDialog)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CString UserKeyId;
	int Modus;
	CFont m_Font;

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CPinCodeDialog)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_PINCODEDIALOG_H__F1360882_35D6_11D3_8D69_00C04F795E36__INCLUDED_