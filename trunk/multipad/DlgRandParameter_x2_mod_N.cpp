// DlgRandParameter_x2_mod_N.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "DlgRandParameter_x2_mod_N.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld DlgRandParameter_x2_mod_N 


DlgRandParameter_x2_mod_N::DlgRandParameter_x2_mod_N(CWnd* pParent /*=NULL*/)
	: CDialog(DlgRandParameter_x2_mod_N::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgRandParameter_x2_mod_N)
	m_EditModul_N = _T("");
	//}}AFX_DATA_INIT
}


void DlgRandParameter_x2_mod_N::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgRandParameter_x2_mod_N)
	DDX_Text(pDX, IDC_EDIT1, m_EditModul_N);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgRandParameter_x2_mod_N, CDialog)
	//{{AFX_MSG_MAP(DlgRandParameter_x2_mod_N)
		// HINWEIS: Der Klassen-Assistent f�gt hier Zuordnungsmakros f�r Nachrichten ein
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten DlgRandParameter_x2_mod_N 

void DlgRandParameter_x2_mod_N::SetModul(CString &NStr)
{
	m_EditModul_N = NStr;
}

CString DlgRandParameter_x2_mod_N::GetModul()
{
	return m_EditModul_N;
}
