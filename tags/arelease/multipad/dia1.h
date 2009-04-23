//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef DIA1_H
#define DIA1_H
// dia1.h : header file
//

//#include "MyCEdit.h"

#define MAX_VIGENERE	1024

/////////////////////////////////////////////////////////////////////////////
// dia1 dialog

class dia1 : public CDialog
{
// Construction
public:
	int len;

	dia1(int maxlen, CWnd* pParent = NULL);   // standard constructor

	virtual char * GetData( void );
	virtual int GetLen( void );
	virtual int Display();
// Dialog Data
	//{{AFX_DATA(dia1)
	enum { IDD = IDD_DIALOG_KEY_INPUT };
	CEdit	m_text_ctl;
	CString	m_text;
	CString	m_static_text;
	int		m_Decrypt;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dia1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(dia1)
	afx_msg void OnUpdateEdit1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // DIA1_H