//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic, 2000

#ifndef AFX_DIALOGCERT_H__B1DF5657_F6FB_11D2_888E_00C04F795E28__INCLUDED_
#define AFX_DIALOGCERT_H__B1DF5657_F6FB_11D2_888E_00C04F795E28__INCLUDED_

// DialogCert.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowCertificate 

class CDlgShowCertificate : public CDialog
{
// Konstruktion
public:
	CDlgShowCertificate(CWnd* pParent = NULL);   // Standardkonstruktor
	CDlgShowCertificate(CString CertIn, CWnd* pParent = NULL);

// Dialogfelddaten
	//{{AFX_DATA(CDlgShowCertificate)
	enum { IDD = IDD_SHOW_CERTIFICATE };
	CEdit	m_dummyCtrl;
	CEdit	m_CertEditCtrl;
	CString	m_CertEdit;
	CString	m_dummy;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgShowCertificate)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	CString Cert;
	CFont m_Font;
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgShowCertificate)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_DIALOGCERT_H__B1DF5657_F6FB_11D2_888E_00C04F795E28__INCLUDED_