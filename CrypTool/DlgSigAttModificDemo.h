#if !defined(AFX_DLGSIGATTMODIFICDEMO_H__ABE40D51_3900_11D7_9E4E_000629718A52__INCLUDED_)
#define AFX_DLGSIGATTMODIFICDEMO_H__ABE40D51_3900_11D7_9E4E_000629718A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSigAttModificDemo.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSigAttModificDemo 

class CDlgSigAttModificDemo : public CDialog
{
// Konstruktion
public:
	CDlgSigAttModificDemo(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSigAttModificDemo)
	enum { IDD = IDD_SIGATTMODIFICDEMO };
	CButton	m_control_method;
	CButton	m_control_unprintable;
	CButton	m_control_printable;
	CButton	m_control_double;
	CButton	m_control_eol;
	CEdit	m_control_hashvalue;
	CString	m_file;
	CString	m_hashvalue;
	int		m_sigbit;
	int		m_method;
	int		m_printable;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSigAttModificDemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSigAttModificDemo)
	afx_msg void OnSerach();
	afx_msg void OnModify();
	afx_msg void OnAttachment();
	afx_msg void OnMethod();
	afx_msg void OnPrintable();
	afx_msg void OnUnprintable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSIGATTMODIFICDEMO_H__ABE40D51_3900_11D7_9E4E_000629718A52__INCLUDED_
