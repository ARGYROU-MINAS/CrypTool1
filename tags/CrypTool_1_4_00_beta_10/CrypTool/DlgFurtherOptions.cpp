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


// DlgFurtherOptions.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgFurtherOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFurtherOptions 


CDlgFurtherOptions::CDlgFurtherOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFurtherOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFurtherOptions)
	m_ShowIntroDialogue = FALSE;
	m_SCAKeyword = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFurtherOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFurtherOptions)
	DDX_Check(pDX, IDC_CHECK1, m_ShowIntroDialogue);
	DDX_Text(pDX, IDC_EDIT_SCAKEYWORD, m_SCAKeyword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFurtherOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgFurtherOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgFurtherOptions 

BOOL CDlgFurtherOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Einstellungen aus .ini-Datei holen

	// Soll Intro-Screen angezeigt werden?
	if(theApp.GetProfileInt("Settings", "DH_IntroDialogue", 1))
		this->m_ShowIntroDialogue = true;
	// Wie lautet das Schl�sselwort f�r den Seitenkanalangriff? (Default: Alice)
	this->m_SCAKeyword = theApp.GetProfileString("Settings", "SCA_Keyword", "Alice");
	
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}


void CDlgFurtherOptions::OnOK() 
{
	UpdateData(true);
	
	// Einstellungen in .ini-Datei schreiben

	// Diffie-Hellman-Intro-Dialog
	this->m_ShowIntroDialogue ? theApp.WriteProfileInt("Settings", "DH_IntroDialogue", 1) : theApp.WriteProfileInt("Settings", "DH_IntroDialogue", 0);
	// SCA-Keyword (nur schreiben, wenn nicht leer! Ansonsten Default: Alice)
	if(this->m_SCAKeyword != "") theApp.WriteProfileString("Settings", "SCA_Keyword", this->m_SCAKeyword);
	else theApp.WriteProfileString("Settings", "SCA_Keyword", "Alice");
	
	CDialog::OnOK();
}