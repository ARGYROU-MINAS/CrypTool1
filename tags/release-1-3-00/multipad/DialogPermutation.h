#if !defined(AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_)
#define AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DialogPermutation.h : Header-Datei
//
#include "AscEdit.h"
#include "crypt.h"

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDialogPermutation 

class CDialogPermutation : public CDialog
{
	CBitmapButton m_Paste;
	// Konstruktion
public:
	int MakePermInt(CString *Pin, int p[], int pinv[]);
	CString makeASCII( CString &line);
	int PrintPerm(char *dest, int *perm, int len);
	int m_Dec;
	int MakePerm(CString *Pin, int p[26], int pinv[26]);
	int m_P1[26];
	int m_P1inv[26];
	int m_P1len;
	int m_P2[26];
	int m_P2inv[26];
	int m_P2len;
	CDialogPermutation(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDialogPermutation)
	enum { IDD = IDD_DIALOG_PERMUTATION };
	CButton	m_Decrypt;
	CButton	m_Encrypt;
	CAscEdit	m_CPerm2;
	CAscEdit	m_CPerm1;
	CString	m_Perm1;
	CString	m_Perm2;
	CString	m_P1out;
	CString	m_P2out;
	int		m_P1InSeq;
	int		m_P1OutSeq;
	int		m_P2InSeq;
	int		m_P2OutSeq;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDialogPermutation)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDialogPermutation)
	afx_msg void OnDecrypt();
	afx_msg void OnEncrypt();
	afx_msg void OnPasteKey();
	afx_msg void OnChangeEdit1();
	afx_msg void OnChangeEdit2();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DIALOGPERMUTATION_H__9FC148C1_75F4_11D5_8B5F_0010A4F6E7D5__INCLUDED_