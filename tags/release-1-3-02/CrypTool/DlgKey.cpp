//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// dia1.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgKey.h"
#include "Cryptography.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgKey dialog

CDlgKey::CDlgKey(int maxlen, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgKey::IDD, pParent)
{
	char line[80];

	len = (maxlen > 0) ? maxlen : -maxlen;
	//{{AFX_DATA_INIT(CDlgKey)
	m_text = _T("");
	m_static_text = _T("");
	//}}AFX_DATA_INIT
	if ( maxlen > 0 )
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_MAX_INPUT_LENGTH_TXT,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,len);
		m_static_text = line;
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_KEY_INPUT_LENGTH,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(line,pc_str,len);
		m_static_text = line;
	}
	s_alternativeWindowText[0]=0;
}

int CDlgKey::Display()
{
	int res;

	res=DoModal();
	return res;
}

void CDlgKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgKey)
	DDX_Control(pDX, IDOK, m_EncryptionButton);
	DDX_Control(pDX, IDC_BUTTON1, m_DecryptionButton);
	DDX_Control(pDX, IDC_EDIT1, m_text_ctl);
	DDX_Text(pDX, IDC_EDIT1, m_text);
	DDV_MaxChars(pDX, m_text, len);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_static_text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgKey, CDialog)
	//{{AFX_MSG_MAP(CDlgKey)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_BN_CLICKED(IDC_BUTTON1, OnDecrypt)
	ON_BN_CLICKED(IDOK, OnEncrypt)
	ON_BN_CLICKED(IDC_BUTTON2, OnPasteKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgKey message handlers


char * CDlgKey::GetData( void )
{
	return m_text.GetBuffer(MAX_VIGENERE+1);
}

int CDlgKey::GetLen( void )
{
	return m_text.GetLength();
}

void CDlgKey::OnUpdateEdit1() 
{
	int sels, sele, i, k;
	char c;
	CString res;

	UpdateData(TRUE); /* get the displayed value in m_text */


	m_text_ctl.GetSel(sels, sele);
	res.Empty();

	if(theApp.TextOptions.m_IgnoreCase) m_text.MakeUpper();

	for(k=i=0;i<m_text.GetLength();i++) {
		c = m_text[i];
		if(AppConv.IsInAlphabet(c)) { // valid character
			res += c;
			k++;
		}
		else { // invalid character
			MessageBeep(MB_OK);
			if(k<sels) sels--;
			if(k<sele) sele--;
		}
	}

	m_text = res;
	if ( m_text.GetLength() )
	{
		m_EncryptionButton.EnableWindow(TRUE);
		m_DecryptionButton.EnableWindow(TRUE);	
	}
	else
	{
		m_EncryptionButton.EnableWindow(FALSE);
		m_DecryptionButton.EnableWindow(FALSE);	
	}
	UpdateData(FALSE);
	m_text_ctl.SetSel(sels,sele);
} 

void CDlgKey::OnDecrypt() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	m_Decrypt = 1;
	OnOK();
}

void CDlgKey::OnEncrypt() 
{
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	m_Decrypt = 0;
	OnOK();
}

void CDlgKey::SetAlternativeWindowText(LPCTSTR s_title)
{
    strncpy(s_alternativeWindowText, s_title, 126);
	s_alternativeWindowText[126]=0;
}

BOOL CDlgKey::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	// TODO: Zus�tzliche Initialisierung hier einf�gen
	VERIFY(m_Paste.AutoLoad(IDC_BUTTON2,this));
	


	if (s_alternativeWindowText[0])
		SetWindowText(s_alternativeWindowText);
	m_EncryptionButton.EnableWindow(FALSE);
	m_DecryptionButton.EnableWindow(FALSE);	

	CString Title;
	Title=s_alternativeWindowText;

	if ( IsKeyEmpty( Title ))
	{
		m_Paste.EnableWindow(TRUE);
	}
	else
	{
		m_Paste.EnableWindow(FALSE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}


void CDlgKey::OnPasteKey() 
{
	UpdateData(TRUE);

	CString Title;
	Title=s_alternativeWindowText;

	ExtractStrKeyType( strTitle, Title );
	if ( PasteKey(strTitle,m_text) )
	{
		m_EncryptionButton.EnableWindow(TRUE);
		m_DecryptionButton.EnableWindow(TRUE);	
	}
	UpdateData(FALSE);
}
