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


// DlgDiffieHellmanIntro.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CryptoolApp.h"
#include "DlgDiffieHellmanIntro.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanIntro 


CDlgDiffieHellmanIntro::CDlgDiffieHellmanIntro(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDiffieHellmanIntro::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDiffieHellmanIntro)
	m_Check_NoShow = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgDiffieHellmanIntro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDiffieHellmanIntro)
	DDX_Check(pDX, IDC_CHECK_NOSHOW, m_Check_NoShow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDiffieHellmanIntro, CDialog)
	//{{AFX_MSG_MAP(CDlgDiffieHellmanIntro)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgDiffieHellmanIntro 

void CDlgDiffieHellmanIntro::OnOK() 
{
	UpdateData(true);
	
	// In CrypTool.INI ablegen, ob der Intro-Dialogue beim n�chsten Start wieder aufgerufen werden soll
	this->m_Check_NoShow ? theApp.WriteProfileInt("Settings", "DH_IntroDialogue", 0) : theApp.WriteProfileInt("Settings", "DH_IntroDialogue", 1);
	
	CDialog::OnOK();
}
