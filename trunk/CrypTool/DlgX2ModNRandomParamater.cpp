// DlgRandParameter_x2_mod_N.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgX2ModNRandomParamater.h"
#include "IntegerArithmetic.h"
#include "DialogeMessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgX2ModNRandomParamater 


CDlgX2ModNRandomParamater::CDlgX2ModNRandomParamater(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgX2ModNRandomParamater::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgX2ModNRandomParamater)
	m_EditModul_N = _T("");
	//}}AFX_DATA_INIT
}


void CDlgX2ModNRandomParamater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgX2ModNRandomParamater)
	DDX_Control(pDX, IDC_EDIT1, m_Control_Edit_Modul_N);
	DDX_Text(pDX, IDC_EDIT1, m_EditModul_N);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgX2ModNRandomParamater, CDialog)
	//{{AFX_MSG_MAP(CDlgX2ModNRandomParamater)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgX2ModNRandomParamater 

void CDlgX2ModNRandomParamater::SetModul(CString &NStr)
{
	m_EditModul_N = NStr;
}

CString CDlgX2ModNRandomParamater::GetModul()
{
	return m_EditModul_N;
}

void CDlgX2ModNRandomParamater::OnOK() 
{
	// TODO: Zus�tzliche Pr�fung hier einf�gen
	BOOL NumberIsOK;
	int     ndx;
	UpdateData(TRUE);
	{ 
		CString upnStr;
		NumberIsOK = EvalFormula(m_EditModul_N, ndx);
	}
	UpdateData(FALSE);
	if ( NumberIsOK )
	{
		CDialog::OnOK();
	}
	else
	{
		// ********* Fehlermeldung
		if (ndx == -1)
		{
			Message(IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION);
			m_Control_Edit_Modul_N.SetSel(0,-1);
			m_Control_Edit_Modul_N.SetFocus();
		}
		else
		{
			Message(IDS_STRING_INPUT_FALSE, MB_ICONSTOP);
			m_Control_Edit_Modul_N.SetSel(ndx-1,-1);
			m_Control_Edit_Modul_N.SetFocus();
		}
	}
}
