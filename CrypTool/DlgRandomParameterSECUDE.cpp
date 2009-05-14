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

// DlgParamRandSECUDE.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgRandomParameterSECUDE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRandomParameterSECUDE 


CDlgRandomParameterSECUDE::CDlgRandomParameterSECUDE(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRandomParameterSECUDE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRandomParameterSECUDE)
	LoadString(AfxGetInstanceHandle(),IDS_STRING_RAND_SECUDE,pc_str,STR_LAENGE_STRING_TABLE);
	m_MessageSecude = pc_str;
	//}}AFX_DATA_INIT
}


void CDlgRandomParameterSECUDE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRandomParameterSECUDE)
	DDX_Text(pDX, IDC_EDIT1, m_MessageSecude);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRandomParameterSECUDE, CDialog)
	//{{AFX_MSG_MAP(CDlgRandomParameterSECUDE)
		// HINWEIS: Der Klassen-Assistent f�gt hier Zuordnungsmakros f�r Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgRandomParameterSECUDE 
