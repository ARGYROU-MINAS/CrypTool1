/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

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


#if !defined(AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_)
#define AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRSAwithSmallPrimesOptions.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgOptionsRSADemo 

class CDlgOptionsRSADemo : public CDialog
{
// Konstruktion
public:
	void MsgAnzahlZeichen();
	void ReInitBlockLength(BOOL setMaxBlockLength = FALSE);
	void MsgBlockLength();
	bool CompareModulAlphabetSize(CString N_str);
	CDlgOptionsRSADemo(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgOptionsRSADemo)
	enum { IDD = IDD_OPTIONS_RSA_DEMO };
	CButton	m_RSAVariantCtrl;
	CButton m_CodingControl;
	CEdit	m_BlockLengthCtrl;
	CEdit	m_alphabetControl;
	CString	m_alphabet;
	int		m_numberBasis;
	int		m_TextOptions;
	int     m_RSAVariant;
	UINT	m_BlockLength;
	int     m_Bitlength;
	CString	m_MaxBlockLength;
	int		m_codingMethod;
	CString	m_AnzahlZeichen;
	//}}AFX_DATA
	double m_log2N;
	CString RSA_Modul;
	int Anzahl_Zeichen;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgOptionsRSADemo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgOptionsRSADemo)
	afx_msg void OnSelectRSA();
	afx_msg void OnSelectDialougeOfSisters();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeAlphabet();
	afx_msg void OnSelectASCII();
	afx_msg void OnSelectAlphabet();
	virtual void OnOK();
	afx_msg void OnCodingNumberSystem();
	afx_msg void OnCodingBAdic();
	afx_msg void OnBase10();
	afx_msg void OnBase2();
	afx_msg void OnBase8();
	afx_msg void OnBase16();
	virtual void OnCancel();
	afx_msg void OnChangeEdit3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int GetBlockLength();

	CString s_alphabet;
	int     s_numberBasis;
	int     s_TextOptions;
	int     s_RSAVariant;
	int     s_BlockLength;
	CString s_MaxBlockLength;
	int     s_codingMethod;
	CString s_AnzahlZeichen;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGRSAWITHSMALLPRIMESOPTIONS_H__98A64261_5414_11D5_9319_00B0D0161C45__INCLUDED_
