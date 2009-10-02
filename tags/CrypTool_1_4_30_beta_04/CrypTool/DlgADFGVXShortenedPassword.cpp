/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

// DlgADFGVXShortenedPassword.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgADFGVXShortenedPassword.h"


// CDlgADFGVXShortenedPassword-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgADFGVXShortenedPassword, CDialog)
CDlgADFGVXShortenedPassword::CDlgADFGVXShortenedPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgADFGVXShortenedPassword::IDD, pParent)
{
}

CDlgADFGVXShortenedPassword::CDlgADFGVXShortenedPassword(CString text, CWnd* pParent)
	: CDialog(CDlgADFGVXShortenedPassword::IDD, pParent)
{
	mText = text;
}

BOOL CDlgADFGVXShortenedPassword::OnInitDialog()
{
	GetDlgItem(IDC_TEXT_INFO)->SetWindowText(mText);
	return true;
}

CDlgADFGVXShortenedPassword::~CDlgADFGVXShortenedPassword()
{
}

void CDlgADFGVXShortenedPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgADFGVXShortenedPassword, CDialog)
END_MESSAGE_MAP()


// CDlgADFGVXShortenedPassword-Meldungshandler