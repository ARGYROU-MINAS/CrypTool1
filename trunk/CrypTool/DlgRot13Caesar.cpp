// DlgRot13Caesar.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "cryptoolapp.h"
#include "DlgRot13Caesar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRot13Caesar 


CDlgRot13Caesar::CDlgRot13Caesar(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRot13Caesar::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRot13Caesar)
	//}}AFX_DATA_INIT
}


void CDlgRot13Caesar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRot13Caesar)
	DDX_Control(pDX, IDC_TO, m_CtrlTo);
	DDX_Control(pDX, IDC_FROM, m_CtrlFrom);
	DDX_Control(pDX, ID_ENCRYPT, m_EncryptionButton);
	DDX_Control(pDX, ID_DECRYPT, m_DecryptionButton);
	DDX_Control(pDX, IDC_DIST, m_dist_control);
	DDX_Control(pDX, IDC_KEY, m_CtrlKey);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_RADIO2, m_CtrlRadioRot13);
	DDX_Control(pDX, IDC_MESSAGE_ROT13, m_CtrlMessageRot13);
	DDX_Control(pDX, IDC_EDIT1, m_CtrlShowAlSize);
}


BEGIN_MESSAGE_MAP(CDlgRot13Caesar, CDialog)
	//{{AFX_MSG_MAP(CDlgRot13Caesar)
	ON_BN_CLICKED(IDC_RADIO2, OnRot13Rad)
	ON_BN_CLICKED(IDC_RADIO1, OnCaesarRad)
	ON_EN_UPDATE(IDC_KEY, OnUpdateKey)
	ON_BN_CLICKED(IDC_PASTE_KEY, OnPasteKey)
	ON_BN_CLICKED(ID_ENCRYPT, OnEncrypt)
	ON_BN_CLICKED(ID_DECRYPT, OnDecrypt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgRot13Caesar 

BOOL CDlgRot13Caesar::OnInitDialog() 
{
	CDialog::OnInitDialog();

// Paste Button
	VERIFY(m_paste.AutoLoad(IDC_PASTE_KEY,this));
	if ( IsKeyEmpty( pc_str ))
	{
		m_paste.EnableWindow(TRUE);
	}
	else
	{
		m_paste.EnableWindow(FALSE);
	}

	VERIFY(m_font.CreatePointFont(100,"Courier New"));
	m_CtrlFrom.SetFont(&m_font);
	m_CtrlTo.SetFont(&m_font);
	m_CtrlKey.SetFont(&m_font);
	m_CtrlKey.SetLimitText(1);
	m_CtrlFrom.SetWindowText(theApp.TextOptions.m_alphabet);
	m_CtrlTo.SetWindowText  ("");
	m_CtrlKey.SetWindowText ("");

	

	int length = theApp.TextOptions.m_alphabet.GetLength();
	if ( (length % 2) )
	{
		m_CtrlRadioRot13.EnableWindow(FALSE);
		LoadString(AfxGetInstanceHandle(),IDS_ROT13_INFO_NEGATIVE,pc_str,STR_LAENGE_STRING_TABLE);
		m_CtrlMessageRot13.SetWindowText(pc_str);
	}

	LoadString(AfxGetInstanceHandle(),IDS_ROT13_CAESAR_CASE,pc_str,STR_LAENGE_STRING_TABLE);
	CString l_str("");
	l_str.AppendFormat(pc_str, length);
	m_CtrlShowAlSize.SetWindowText(l_str);

	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1); 
	UpdateData();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}


void CDlgRot13Caesar::OnRot13Rad()
{
	CString Rot13Key = theApp.TextOptions.m_alphabet.GetAt(theApp.TextOptions.m_alphabet.GetLength() / 2);
	m_CtrlKey.SetWindowText(Rot13Key);
	m_CtrlKey.EnableWindow(FALSE);
}

void CDlgRot13Caesar::OnCaesarRad()
{
	m_CtrlKey.EnableWindow();
}

void CDlgRot13Caesar::OnUpdateKey()
{
	static int BUSY = 0;  // FIXME
	if (BUSY) return;

	BUSY++;

	BOOL validKey_flag = FALSE;
	int cStart, cEnd;
	CString m_key;

	m_CtrlKey.GetSel(cStart, cEnd);

// Read the Key
	CString alphabet = theApp.TextOptions.m_alphabet;
	m_CtrlKey.GetWindowText(m_key);

// Process non empty text
	if ( !m_key.IsEmpty() ) 
	{
		if ( theApp.TextOptions.m_ConvertCase )  // Only Capital Letters ?
			m_key.MakeUpper();

		for (m_dist = 0; m_dist < alphabet.GetLength(); m_dist++)
			if ( m_key == alphabet.GetAt(m_dist) )
			{
				// Inform about the Caesar distance
				m_dist = (m_dist+1) % alphabet.GetLength();

				CString target;
				target.Format("%d", m_dist);   
				m_dist_control.SetWindowText(target);

				// Output the encryption mapping
				CString to = _T("");
				for (int ii = 0; ii < alphabet.GetLength(); ii ++)
				{
					to.AppendChar( alphabet.GetAt((ii+m_dist) % alphabet.GetLength()) );
				}
				m_CtrlTo.SetWindowText(to);

				// 
				m_CtrlKey.SetWindowText(m_key);

				// Button Management
				m_EncryptionButton.EnableWindow();
				m_DecryptionButton.EnableWindow();
				validKey_flag = TRUE;
				break;
			}
	}
	if ( !validKey_flag ) // ALL BLANK
	{
		m_dist_control.SetWindowText("");
		m_CtrlKey.SetWindowText("");
		m_CtrlTo.SetWindowText("");
		m_EncryptionButton.EnableWindow(FALSE);
		m_DecryptionButton.EnableWindow(FALSE);
	}
	m_CtrlKey.SetSel(cStart, cEnd);

	BUSY--;
}



void CDlgRot13Caesar::OnPasteKey() 
{
	CString cs, hilf;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_CAESAR,pc_str,STR_LAENGE_STRING_TABLE);

	if ( PasteKey(pc_str,cs) )
	{
		if (theApp.TextOptions.m_alphabet.Find(cs))
		{
			m_CtrlKey.SetWindowText(cs);
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_ROT13_CAESAR_BAD_KEY,pc_str,255);
			AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
		}
	}
}

void CDlgRot13Caesar::OnEncrypt() 
{
	m_Decrypt = 0;
	OnOK();
}

void CDlgRot13Caesar::OnDecrypt() 
{
	m_Decrypt = 1;
	OnOK();	
}

