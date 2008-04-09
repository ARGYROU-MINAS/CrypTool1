/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef DIALOGKEYHEX_H
#define DIALOGKEYHEX_H

#include "DlgKeyVigenere.h"
#include "HexEdit.h"

#define MAX_ANZ_HEX_BLOECKE MAX_VIGENERE
// DialogKeyHex.h : Header-Datei
//
/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgKeyHex 

class CDlgKeyHexAnalysis : public CDlgKeyVigenereAnalyisis
{
// Konstruktion
public:
	CDlgKeyHexAnalysis(CWnd* pParent = NULL);   // Standardkonstruktor

	virtual char * GetData( void );
	virtual int GetLen( void );
	virtual int GetHexData(LPTSTR v, int len); // copy m_einstr, removing non-hex chars
	virtual int Display(char *, int);
	virtual int Display(CString);
	int len;

// Dialogfelddaten
	//{{AFX_DATA(CDlgKeyHexAnalysis)
	enum { IDD = IDD_KEY_ANALYSIS };
	CHexEdit	m_einfeld;
	CString	m_einstr;
	CString	m_static_text;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgKeyHexAnalysis)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	CFont m_font; // font for key display
	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgKeyHexAnalysis)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio f�gt zus�tzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // DIALOGKEYHEX_H