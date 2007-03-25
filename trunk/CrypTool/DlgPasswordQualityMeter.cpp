// DlgPasswordQualityMeter.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgPasswordQualityMeter.h"

#include "passwordqualitymeter.h"
#include ".\dlgpasswordqualitymeter.h"


// CDlgPasswordQualityMeter-Dialogfeld

CDlgPasswordQualityMeter::CDlgPasswordQualityMeter(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasswordQualityMeter::IDD, pParent)
{
	password = "";
	showPassword = true;
	useCrypToolAlphabet = true;

	intQualityKeePass = 0;
	intQualityMozilla = 0;
	intQualityPGP = 0;
	intQualityCrypTool = 0;

	stringQualityKeePass = "";
	stringQualityMozilla = "";
	stringQualityPGP = "";
	stringQualityCrypTool = "";
}

CDlgPasswordQualityMeter::~CDlgPasswordQualityMeter()
{
}

void CDlgPasswordQualityMeter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_PASSWORD, password);
	DDX_Check(pDX, IDC_CHECK_SHOWPASSWORD, showPassword);
	DDX_Check(pDX, IDC_CHECK_USECRYPTOOLALPHABET, useCrypToolAlphabet);

	DDX_Text(pDX, IDC_QUALITY_KEEPASS, stringQualityKeePass);
	DDX_Text(pDX, IDC_QUALITY_MOZILLA, stringQualityMozilla);
	DDX_Text(pDX, IDC_QUALITY_PGP, stringQualityPGP);
	DDX_Text(pDX, IDC_QUALITY_CRYPTOOL, stringQualityCrypTool);

	DDX_Control(pDX, IDC_PROGRESS_KEEPASS, controlQualityKeePass);
	DDX_Control(pDX, IDC_PROGRESS_MOZILLA, controlQualityMozilla);
	DDX_Control(pDX, IDC_PROGRESS_PGP, controlQualityPGP);
	DDX_Control(pDX, IDC_PROGRESS_CRYPTOOL, controlQualityCrypTool);
}

BOOL CDlgPasswordQualityMeter::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	UpdateUserInterface();
	
	return FALSE;  // Geben Sie TRUE zur�ck, au�er ein Steuerelement soll den Fokus erhalten
}

void CDlgPasswordQualityMeter::EditPasswordChanged()
{
	UpdateData(true);

	intQualityKeePass = passwordQualityKeePass(password);
	intQualityMozilla = passwordQualityMozilla(password);
	intQualityPGP = passwordQualityPGP(password);

	// determine CrypTool password quality
	if(useCrypToolAlphabet)
	{	
		// if the internally used alphabet of CrypTool is considered, then the password quality average is 
		// based on the estimated entropy of the password. that means
		// - a maximum password quality of 128 bit is assumed (see PGP approach) and 
		// - each password character is chosen randomly and idependently out of the password space.
		double entropy = log2(theApp.TextOptions.m_alphabet.GetLength());
		double quality = password.GetLength() * entropy;
		// moreover we suppose that the maximum password quality is 128 bits
		if(quality > 128) intQualityCrypTool = 100;
		else intQualityCrypTool = (int)(((double)(quality/128))*100);
	}
	else
	{
		// we assume a password space of 95 printable characters that are chosen randomly and idenpendently
		double entropy = log2(95);
		double quality = password.GetLength() * entropy;
		// moreover we suppose that the maximum password quality is 128 bits
		if(quality > 128) intQualityCrypTool = 128;
		intQualityCrypTool = (int)(((double)(quality/128))*100);
	}
	
	UpdateUserInterface();
}

void CDlgPasswordQualityMeter::UpdateUserInterface()
{
	// first scale down quality values if necessary
	if(intQualityKeePass >= 100) intQualityKeePass = 100;
	if(intQualityKeePass < 0) intQualityKeePass = 0;
	if(intQualityMozilla >= 100) intQualityMozilla = 100;
	if(intQualityMozilla < 0) intQualityMozilla = 0;
	if(intQualityPGP >= 100) intQualityPGP = 100;
	if(intQualityPGP < 0) intQualityPGP = 0;
	if(intQualityCrypTool >= 100) intQualityCrypTool = 100;
	if(intQualityCrypTool < 0) intQualityCrypTool = 0;

	// update (string) quality display
	_itoa(intQualityKeePass, pc_str, 10);
	stringQualityKeePass = pc_str;
	stringQualityKeePass.Append(" %");
	_itoa(intQualityMozilla, pc_str, 10);
	stringQualityMozilla = pc_str;
	stringQualityMozilla.Append(" %");
	_itoa(intQualityPGP, pc_str, 10);
	stringQualityPGP = pc_str;
	stringQualityPGP.Append(" %");
	_itoa(intQualityCrypTool, pc_str, 10);
	stringQualityCrypTool = pc_str;
	stringQualityCrypTool.Append(" %");

	// update (progress bar) quality display
	controlQualityKeePass.SetRange(0, 100);
	controlQualityKeePass.SetPos(intQualityKeePass);
	controlQualityMozilla.SetRange(0, 100);
	controlQualityMozilla.SetPos(intQualityMozilla);
	controlQualityPGP.SetRange(0, 100);
	controlQualityPGP.SetPos(intQualityPGP);
	controlQualityCrypTool.SetRange(0, 100);
	controlQualityCrypTool.SetPos(intQualityCrypTool);
	
	// set focus to password edit field
	((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetFocus();

	UpdateData(false);
}

BEGIN_MESSAGE_MAP(CDlgPasswordQualityMeter, CDialog)
	ON_EN_CHANGE(IDC_EDIT_PASSWORD, EditPasswordChanged)
	ON_BN_CLICKED(IDC_CHECK_USECRYPTOOLALPHABET, OnBnClickedCheckUsecryptoolalphabet)
	ON_BN_CLICKED(IDC_CHECK_SHOWPASSWORD, OnBnClickedCheckShowpassword)
END_MESSAGE_MAP()



// CDlgPasswordQualityMeter-Meldungshandler

void CDlgPasswordQualityMeter::OnBnClickedCheckUsecryptoolalphabet()
{
	UpdateData(true);

	// print warning if user deactivates the use of the CrypTool alphabet
	if(!useCrypToolAlphabet)
	{
		LoadString(AfxGetInstanceHandle(), IDS_PQM_CRYPTOOLALPHABETINACTIVE, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
	}

	EditPasswordChanged();
}

void CDlgPasswordQualityMeter::OnBnClickedCheckShowpassword()
{
	UpdateData(true);

	if(showPassword) ((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetPasswordChar(0);
	else ((CEdit*)GetDlgItem(IDC_EDIT_PASSWORD))->SetPasswordChar('*');

	UpdateUserInterface();
}