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


// aestoolDlg.cpp : Implementierungsdatei
// $Id$

#include "stdafx.h"
#include "io.h"
#include "aestool.h"
#include "aestoolDlg.h"
#include "aestoolcrypto.h"
#include "splash.h"
#include "help.h"
#include "direct.h"
#include <stdio.h>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CAestoolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld f?r Anwendungsbefehl "Info"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialogfelddaten
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	virtual BOOL OnInitDialog();

	// Vom Klassenassistenten generierte ?berladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst?tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// Keine Nachrichten-Handler
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set the AES-Tool version (i.e. "AES-Tool 2.5.1")
	CWnd *window = GetDlgItem(IDC_AES_TOOL_VERSION);
	if(window) window->SetWindowText(CAestoolApp::getAESToolVersionString());

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CAestoolDlg Dialogfeld

CAestoolDlg::CAestoolDlg(CString key,CString in,CString out,CWnd* pParent /*=NULL*/)
	: m_CMD_inKey(key), m_CMD_inName(in), m_CMD_outName(out), 
	  CDialog(CAestoolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAestoolDlg)
	m_Format = -1;
	m_checkShowPassword = 1;
	m_checkEnterPasswordAsHex = 1;
	m_checkSecurelyDeleteSourceFileAfterEncryption = 0;
	//}}AFX_DATA_INIT
	// Beachten Sie, dass LoadIcon unter Win32 keinen nachfolgenden DestroyIcon-Aufruf ben?tigt
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Format = 0;
	if (!out.IsEmpty())
		m_Format = out.Right(4).CompareNoCase(".exe") == 0 ? 0 : 1;
	m_derivedPassword = 0;
	m_derivedPasswordLength = 0;
}

CAestoolDlg::~CAestoolDlg()
{
	delete[] m_derivedPassword;
}

void CAestoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAestoolDlg)
	DDX_Control(pDX, IDC_STATIC_TITLE, m_CStaticTitle);
	DDX_Control(pDX, IDC_BUTTON_ENCRYPT, m_CButtonEncrypt);
	DDX_Control(pDX, IDC_BUTTON_DECRYPT, m_CButtonDecrypt);
	DDX_Control(pDX, IDC_RADIO_EXE, m_CRadioExe);
	DDX_Control(pDX, IDC_RADIO_AES, m_CRadioAes);
	DDX_Control(pDX, IDC_EDIT_SRC, m_CEditSrc);
	DDX_Control(pDX, IDC_EDIT_KEY_HEX, m_CHEditKey);
	DDX_Control(pDX, IDC_EDIT_KEY_ASCII, m_EditKey);
	DDX_Control(pDX, IDC_BUTTON_SRC, m_CButtonSrc);
	DDX_Radio(pDX, IDC_RADIO_EXE, m_Format);
	DDX_Check(pDX, IDC_CHECK_SHOW_PASSWORD, m_checkShowPassword);
	DDX_Check(pDX, IDC_CHECK_ENTER_PASSWORD_AS_HEX, m_checkEnterPasswordAsHex);
	DDX_Check(pDX, IDC_CHECK_SECURELY_DELETE_SOURCE_FILE_AFTER_ENCRYPTION, m_checkSecurelyDeleteSourceFileAfterEncryption);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAestoolDlg, CDialog)
	//{{AFX_MSG_MAP(CAestoolDlg)
	ON_WM_DESTROY()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SRC, OnSucheSrc)
	ON_BN_CLICKED(IDC_BUTTON3, OnHelp)
	ON_EN_CHANGE(IDC_EDIT_KEY_HEX, updateEncryptDecryptButtons)
	ON_EN_CHANGE(IDC_EDIT_KEY_ASCII, updateEncryptDecryptButtons)
	ON_EN_CHANGE(IDC_EDIT_SRC, OnChangeSrc)
	ON_BN_CLICKED(IDC_CHECK_SHOW_PASSWORD, OnCheckShowPassword)
	ON_BN_CLICKED(IDC_CHECK_ENTER_PASSWORD_AS_HEX, OnCheckEnterPasswordAsHex)
	ON_BN_CLICKED(IDC_RADIO_EXE, OnRadioFormat)
	ON_BN_CLICKED(IDC_RADIO_AES, OnRadioFormat)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT, OnOK)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, OnOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAestoolDlg Nachrichten-Handler

BOOL CAestoolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// set the default dialog title (i.e. "AES-Tool 2.5.1")
	this->SetWindowText(CAestoolApp::getAESToolVersionString());

	// call the event handlers for both check boxes to make sure the UI is adjusted accordingly
	OnCheckShowPassword();
	OnCheckEnterPasswordAsHex();
	
	// Hinzuf?gen des Men?befehls "Info..." zum Systemmen?.

	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	//m_consoleDetached = (INVALID_HANDLE_VALUE == GetStdHandle(STD_OUTPUT_HANDLE) ||
	//					 _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),0) == -1);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{	
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Symbol f?r dieses Dialogfeld festlegen. Wird automatisch erledigt
	//  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Gro?es Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	m_CButtonEncrypt.EnableWindow(FALSE);
	m_CButtonDecrypt.EnableWindow(FALSE);

	// initialize key field
	m_CHEditKey.SetWindowText(m_CMD_inKey);
	// limit key field (HEX)
	m_CHEditKey.SetLimitText(64);
	// limit key field (ASCII)
	m_EditKey.SetLimitText(32);

	// EXEFile bestimmen
	GetModuleFileName(GetModuleHandle(NULL), EXEName.GetBuffer(512), 511);
	EXEName.ReleaseBuffer();

	m_SrcInfo.setName(EXEName);
	if (m_SrcInfo.isEncrypted()) {
		m_CMD_inName = EXEName;
		UpdateData(FALSE);
#if 0 // FIXME LATER Warning is moved: "NOTE" in Help Dialog
		CSplash dia;
		if(IDCANCEL == dia.DoModal()) EndDialog( IDCANCEL );
#endif
	}
	m_CEditSrc.SetWindowText(m_CMD_inName);
	// m_CEditSrc.DragAcceptFiles();
	OnChangeSrc();

	UpdateData(FALSE);
	m_CEditSrc.SetSel(0,-1);

	return TRUE;  // Geben Sie TRUE zur?ck, au?er ein Steuerelement soll den Fokus erhalten
}

void CAestoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CAestoolDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// Wollen Sie Ihrem Dialogfeld eine Schaltfl?che "Minimieren" hinzuf?gen, ben?tigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. F?r MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch f?r Sie erledigt.

void CAestoolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Ger?tekontext f?r Zeichnen

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Symbol in Client-Rechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// Die Systemaufrufe fragen den Cursorform ab, die angezeigt werden soll, w?hrend der Benutzer
//  das zum Symbol verkleinerte Fenster mit der Maus zieht.
HCURSOR CAestoolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAestoolDlg::OnSucheSrc() 
{
	CString name;
	m_CEditSrc.GetWindowText(name);
	CFileDialog Dlg(TRUE, NULL, name, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		"All Files (*.*)|*.*|EXE Files (*.exe)|*.exe|AES Files (*.aes)|*.aes||", this);
	if(IDCANCEL == Dlg.DoModal()) return;
	m_CEditSrc.SetWindowText(Dlg.GetPathName());
	int curPos = Dlg.GetPathName().GetLength();
	m_CEditSrc.SetSel(curPos, curPos);

	// ASCII
	if(m_checkEnterPasswordAsHex == 0) {
		if(m_EditKey.GetWindowTextLength() > 0) {
			bool encrypted = m_SrcInfo.isEncrypted();
			if(encrypted) m_CButtonDecrypt.SetFocus();
			else m_CButtonEncrypt.SetFocus();
		}
		else {
			m_EditKey.SetFocus();
		}
	}
	// HEX
	else {
		if(m_CHEditKey.GetWindowTextLength() > 0) {
			bool encrypted = m_SrcInfo.isEncrypted();
			if(encrypted) m_CButtonDecrypt.SetFocus();
			else m_CButtonEncrypt.SetFocus();
		}
		else {
			m_CHEditKey.SetFocus();
		}
	}
}

// this function is called by both buttons, the encrypt AND decrypt button; the 
// actual processing (encryption or decryption) is done implicitly in this function
void CAestoolDlg::OnOK() 
{
	UpdateData(TRUE);

	// the key (void pointer and length)
	void *keyData = 0;
	int keyLength = 0;

	// flomar, 11/24/2011: changes due to the new ASCII edit field; handle HEX 
	// and ASCII separately (not just here, but everywhere in this dialog), and 
	// then set the "keyData" and "keyLength" (see above) for encryption/decryption	

	// ASCII
	if(m_checkEnterPasswordAsHex == 0) {
		// get the user input (the ASCII password)
		CString keyTemp; m_EditKey.GetWindowText(keyTemp);
		// apply our PKCS#5 password derivation function (with a FIXED salt, as a random salt would cause a lot of trouble in terms of backwards compatibility)
		createPKCS5Password(keyTemp.GetBuffer(), "theNotSoRandomCrypToolSalt", 10000, &m_derivedPassword, &m_derivedPasswordLength);
		// set key data and (fixed) key length
		keyData = m_derivedPassword;
		keyLength = m_derivedPasswordLength;
	}
	// HEX
	else {													
		// set key data and key length
		keyData = m_CHEditKey.BinData;
		keyLength = m_CHEditKey.BinLen;
	}

	InfoBlock infoblock;
	if (m_SrcInfo.isEncrypted())
		switch (infoblock.decrypt(m_SrcInfo,keyData,keyLength)) {
		case InfoBlock::CORRUPT:
			char stringBuffer[2048+1];
			char stringErrorMessage[2048+1];
			memset(stringBuffer, 0, 2048+1);
			memset(stringErrorMessage, 0, 2048+1);
			LoadString(AfxGetInstanceHandle(), IDS_STRING_KEYERROR, stringBuffer, 2048);
			sprintf(stringErrorMessage, stringBuffer, m_SrcInfo.getName().GetBuffer());
			AfxMessageBox(stringErrorMessage, MB_OK);
			if(m_checkEnterPasswordAsHex == 0) { m_EditKey.SetSel(0, -1); m_EditKey.SetFocus(); }
			else { m_CHEditKey.SetSel(0,-1); m_CHEditKey.SetFocus(); }
			return;
		case InfoBlock::NOMEM:
			AfxMessageBox(IDS_STRING_NOMEMORY,MB_OK);
			return;
		}

	CString mask;
	if(m_SrcInfo.isEncrypted())
		mask = "All Files (*.*)|*.*||";
	else if(m_Format == 0)
		mask = "Exe Files (*.exe)|*.exe||";
	else
		mask = "AES Files (*.aes)|*.aes||";
	CString dstname = 
		m_CMD_outName.IsEmpty() ? 
			defaultDstName(&m_SrcInfo,&infoblock,m_Format == 0) :
			m_CMD_outName;
	CFileDialog Dlg(FALSE, NULL, dstname, 
		OFN_OVERWRITEPROMPT|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY, mask, this);

	if(IDCANCEL == Dlg.DoModal()) return;
	dstname = Dlg.GetPathName();

	CString text = dstname;
	bool success;
	unsigned id;
	
	if(m_SrcInfo.isEncrypted()) {
		success = AesToolDecrypt(keyData, keyLength, m_SrcInfo, dstname, text);
		id = success ? IDS_STRING_DECOK : IDS_STRING_DECERROR;
	}
	else {
		success = AesToolEncrypt(keyData, keyLength, m_SrcInfo, dstname, (m_Format == 0 ? (LPCTSTR)EXEName : 0), text);
		id = success ? IDS_STRING_ENCOK : IDS_STRING_ENCERROR;
		// flomar, 11/25/2011: in case we have a successful encryption and the 
		// appropriate check box is checked, we try to securely delete the source file
		if(success && m_checkSecurelyDeleteSourceFileAfterEncryption != 0)
			securelyDeleteSourceFile();
	}

	// flomar, 02/11/2010
	// the default behavior of afx message boxes is misleading in this particular instance: we want 
	// a simple "notification icon" in case of a successful encryption/decryption, otherwise we go 
	// with the "warning sign" (which is the default behavior)
	CString msg;
	msg.Format(id,text);
	if(success) AfxMessageBox(msg, MB_OK|MB_ICONINFORMATION);
	else AfxMessageBox(msg, MB_OK);
}

void CAestoolDlg::OnRadioFormat() 
{
	UpdateData();
}

void CAestoolDlg::OnHelp() 
{
	CHelp dia;
	dia.DoModal();
}

void CAestoolDlg::updateEncryptDecryptButtons()
{
	// we enable the encrypt/decrypt buttons only if...
	//  a) we're in HEX mode and m_CHEditKey is not empty, AND m_SrcInfo exists
	//  b) we're in ASCII mode and m_EditKey is not empty, AND m_SrcInfo exists
	bool enable = false;
	// check for ASCII mode
	if(m_checkEnterPasswordAsHex == 0) {
		if(m_EditKey.GetWindowTextLength() > 0 && m_SrcInfo.exists()) {
			enable = true;
		}
	}
	// check for HEX mode
	else {
		if(m_CHEditKey.GetWindowTextLength() > 0 && m_SrcInfo.exists()) {
			enable = true;
		}
	}
	// enable/disable the encrypt/decrypt buttons
	if(enable) {
		if(m_SrcInfo.isEncrypted()) {
			m_CButtonEncrypt.EnableWindow(false);
			m_CButtonDecrypt.EnableWindow(true);
		}
		else {
			m_CButtonEncrypt.EnableWindow(true);
			m_CButtonDecrypt.EnableWindow(false);
		}
	}
	else {
		m_CButtonEncrypt.EnableWindow(false);
		m_CButtonDecrypt.EnableWindow(false);
	}
}

void CAestoolDlg::EnDisableCheckSecurelyDeleteSourceFileAfterEncryption()
{
	// enable/disable checkbox for securely deleting source file after encryption
	CWnd *window = GetDlgItem(IDC_CHECK_SECURELY_DELETE_SOURCE_FILE_AFTER_ENCRYPTION);
	if(!window) return;
	// find out whether the source file at hand is encrypted
	bool encrypted = m_SrcInfo.isEncrypted();
	window->EnableWindow(!encrypted);
}

void CAestoolDlg::OnChangeSrc()	// wird aufgerufen, wenn der Benutzer die Quelldatei von Hand
									//?ndert
{
	// update source file information
	CString text;
	CString name;
	m_CEditSrc.GetWindowText(name);

	// change app title
	text = CAestoolApp::getAESToolVersionString();
	// if the name is not empty, we append the name in brackets
	if(!name.IsEmpty()) text.Append(" [" + name + "]");
	free((void*)theApp.m_pszAppName);
	theApp.m_pszAppName = _strdup(text);

	switch (m_SrcInfo.setName(name)) {
	case SrcInfo::VERSION:
		AfxMessageBox(IDS_STRING_VERSION,MB_OK);
		break;
	case SrcInfo::CORRUPT:
		AfxMessageBox(IDS_STRING_CORRUPT,MB_OK);
		break;
	case SrcInfo::NOMEM:
		AfxMessageBox(IDS_STRING_NOMEMORY,MB_OK);
		break;
	}

	// update encrypt/decrypt buttons depending on internal state
	updateEncryptDecryptButtons();
	
	bool encrypted = m_SrcInfo.isEncrypted();

	// enable/disable direction radio buttons
	m_CRadioExe.EnableWindow(!encrypted);
	m_CRadioAes.EnableWindow(!encrypted);

	// also, make sure the check box for securely deleting the source file is enabled/disabled
	EnDisableCheckSecurelyDeleteSourceFileAfterEncryption();
}

void CAestoolDlg::OnCheckShowPassword() 
{
	UpdateData(true);
	
	if(m_checkShowPassword == 0) {
		m_CHEditKey.SetPasswordChar('*');
		m_CHEditKey.Invalidate();
		m_EditKey.SetPasswordChar('*');
		m_EditKey.Invalidate();
	}
	else {
		m_CHEditKey.SetPasswordChar(0);
		m_CHEditKey.Invalidate();
		m_EditKey.SetPasswordChar(0);
		m_EditKey.Invalidate();
	}

	// set the focus to the password field
	if(m_checkEnterPasswordAsHex == 0) {
		m_EditKey.SetFocus();
	}
	else {
		m_CHEditKey.SetFocus();
	}
}

void CAestoolDlg::OnCheckEnterPasswordAsHex()
{
	UpdateData(true);

	// set the key header (either HEX or ASCII) according to "m_checkEnterPasswordAsHex"
	CString stringKeyHeader;
	if(m_checkEnterPasswordAsHex == 0) stringKeyHeader.LoadString(IDS_STRING_KEY_HEADER_ASCII);
	else stringKeyHeader.LoadString(IDS_STRING_KEY_HEADER_HEX);
	CWnd *windowKeyHeader = GetDlgItem(IDC_KEY_HEADER);
	if(windowKeyHeader != 0) windowKeyHeader->SetWindowTextA(stringKeyHeader);
	
	// show/hide HEX or ASCII edit field
	CWnd *windowEditHex = GetDlgItem(IDC_EDIT_KEY_HEX);
	CWnd *windowEditAscii = GetDlgItem(IDC_EDIT_KEY_ASCII);
	if(m_checkEnterPasswordAsHex == 0) {	
		if(windowEditHex != 0) windowEditHex->ShowWindow(SW_HIDE);
		if(windowEditAscii != 0) windowEditAscii->ShowWindow(SW_SHOW);
		// set the focus to the ASCII password field
		m_EditKey.SetFocus();
	}
	else {
		if(windowEditHex != 0) windowEditHex->ShowWindow(SW_SHOW);
		if(windowEditAscii != 0) windowEditAscii->ShowWindow(SW_HIDE);
		// set the focus to the HEX password field
		m_CHEditKey.SetFocus();
	}
	
	// make sure the encrypt/decrypt buttons are updated
	updateEncryptDecryptButtons();
}

CString CAestoolDlg::defaultDstName(SrcInfo *si, InfoBlock *ib,bool selfextracting /* = true*/)
// ib has to be defined only if si->isEncrypted()
// selfextracting must only be defined if !si->isEncrypted()
{
	ASSERT(si->exists());
	CString srcname = si->getName();
	CString dstname;
	if (si->isEncrypted()) { // decrypt
		int backslash = srcname.ReverseFind('\\');
		dstname = srcname.Left(backslash + 1); // dir portion of m_name 
		dstname += ib->getOrigName();
	} else { // encrypt
		int dot = srcname.ReverseFind('.');
		if (dot == -1)
			dstname = srcname;
		else 
			dstname = srcname.Left(dot);
		if (selfextracting)
			dstname += ".exe";
		else 
			dstname += ".aes";
	}
	return dstname;
}			

void CAestoolDlg::securelyDeleteSourceFile()
{
	// flomar, 11/25/2011: this function is supposed to "securely delete" the source file after encryption; 
	// however, I'm going with a very basic approach as I simply overwrite the source file a couple of times 
	// with different patterns before finally deleting it; for a more sophisticated solution you might want 
	// to check out Eraser (http://www.heidi.ie/eraser/)

	// this is a list of bytes that define which bytes the source file is overwritten with in 
	// each pass; don't ask me why I chose this exact compilation, it just looks neat
	std::vector<int> listPatterns;
	listPatterns.push_back(0x00);
	listPatterns.push_back(0xF0);
	listPatterns.push_back(0x0F);
	listPatterns.push_back(0xFF);

	// the buffer is used to copy chunks of data to the source file
	const size_t BUFFERSIZE = 4096;
	char buffer[BUFFERSIZE];
	// try to open the source file exclusively
	CFile file;
	if(file.Open(m_SrcInfo.getName().GetBuffer(), CFile::typeBinary | CFile::modeWrite | CFile::shareExclusive)) {
		// overwrite the file using the list of patterns above
		const ULONGLONG length = file.GetLength();
		for(unsigned int p=0; p<listPatterns.size(); p++) {
			memset(buffer, listPatterns[p], BUFFERSIZE);
			file.SeekToBegin();
			ULONGLONG numberOfBytesWritten = 0;
			ULONGLONG numberOfBytesToBeWritten = BUFFERSIZE;
			while(numberOfBytesWritten < length) {
				if(numberOfBytesWritten + numberOfBytesToBeWritten > length) {
					numberOfBytesToBeWritten = length - numberOfBytesWritten;
				}
				file.Write(&buffer, (size_t)numberOfBytesToBeWritten);
				numberOfBytesWritten += numberOfBytesToBeWritten;
			}
			file.Flush();
		}
		file.Close();
		// don't forget to actually remove the file
		CFile::Remove(m_SrcInfo.getName());
		// and last but not least, clear the m_SrcInfo field and set focus to search source button
		m_CEditSrc.SetWindowText("");
		OnChangeSrc();
		m_CButtonSrc.SetFocus();
	}
	else {
		CString message;
		message.Format(IDS_STRING_FILE_DELETION_FAILED, m_SrcInfo.getName());
		MessageBox(message, "CrypTool", MB_OK);
	}
}