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


// SchluesselAusgabeLinear.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgShowKey.h"
#include "KeyRepository.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgShowKey 


CDlgShowKey::CDlgShowKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgShowKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgShowKey)
	m_Key = _T("");
	//}}AFX_DATA_INIT
}


void CDlgShowKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowKey)
	DDX_Control(pDX, IDC_EDIT1, m_CtrlKey);
	DDX_Text(pDX, IDC_EDIT1, m_Key);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgShowKey, CDialog)
	//{{AFX_MSG_MAP(CDlgShowKey)
	ON_BN_CLICKED(IDC_BUTTON1, OnCopyKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgShowKey 


void CDlgShowKey::OnCopyKey() 
{
	//In der Zwischen Ablage kopieren
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	CopyKey(strTitle, m_Key); 
///////////////////////////////////////////////
//	HENRIK KOY 06-08-2002
//  Das Einf�gen des Schl�sselstrings in die Windows-Zwischenablage bewirkt, dass der vom User eventuell
//  dorthinein gespeicherte Inhalt �berschrieben wird (verwirrt den User). -- deshalb auskommentiert
//	m_CtrlKey.SetSel(0,-1); 
//	m_CtrlKey.Copy();
	CDialog::OnOK();
}

BOOL CDlgShowKey::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_font.CreatePointFont(100,"Courier New");
	m_CtrlKey.SetFont(&m_font);
	if (strTitle[0])
	{
		LoadString(AfxGetInstanceHandle(),IDS_METHOD_KEY,pc_str,STR_LAENGE_STRING_TABLE);
		char keyMethodStr[128];
		sprintf( keyMethodStr, pc_str, strTitle );
		SetWindowText(keyMethodStr);
	}

	// TODO: Zus�tzliche Initialisierung hier einf�gen
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

int CDlgShowKey::DoModal() 
{
	// TODO: Speziellen Code hier einf�gen und/oder Basisklasse aufrufen
	return CDialog::DoModal();
}

