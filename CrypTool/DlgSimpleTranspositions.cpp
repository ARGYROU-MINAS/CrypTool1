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

// DlgSimpleTranspositions.cpp : implementation file
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgSimpleTranspositions.h"
#include "Cryptography.h"
#include "CrypToolTools.h"

IMPLEMENT_DYNAMIC(CDlgSimpleTranspositions, CDialog)

CDlgSimpleTranspositions::CDlgSimpleTranspositions(char* infile, CString oldTitle, CWnd* pParent)
	: CDialog(CDlgSimpleTranspositions::IDD, pParent)
	, key(0)
{
	fileName = infile;
	fileNameTitle = oldTitle;

	// the type is Scytale by default
	type = 0;
	// the default key is 2
	key = 2;
	// the default offset is 0
	offset = 0;

	// init the bitmaps
	bitmapScytale.LoadBitmapA(IDB_SIMPLE_TRANSPOSITION_SCYTALE);
	bitmapRailFence.LoadBitmapA(IDB_SIMPLE_TRANSPOSITION_RAIL_FENCE);
}

CDlgSimpleTranspositions::~CDlgSimpleTranspositions()
{

}

void CDlgSimpleTranspositions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO_SCYTALE, type);
	DDX_Control(pDX, IDC_SIMPLE_TRANSPOSITION_IMAGE, controlImage);
	DDX_Text(pDX, IDC_EDIT_KEY, key);
	DDX_Text(pDX, IDC_EDIT_OFFSET, offset);
}


BEGIN_MESSAGE_MAP(CDlgSimpleTranspositions, CDialog)
	ON_BN_CLICKED(ID_ENCRYPT, &CDlgSimpleTranspositions::OnBnClickedEncrypt)
	ON_BN_CLICKED(ID_DECRYPT, &CDlgSimpleTranspositions::OnBnClickedDecrypt)
	ON_BN_CLICKED(IDC_RADIO_SCYTALE, OnRadioScytale)
	ON_BN_CLICKED(IDC_RADIO_RAIL_FENCE, OnRadioRailFence)
	ON_BN_CLICKED(ID_TEXTOPTIONS, &CDlgSimpleTranspositions::OnBnClickedTextoptions)
	ON_BN_CLICKED(IDC_PASTE_KEY, OnPasteKey)
END_MESSAGE_MAP()

BOOL CDlgSimpleTranspositions::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// some assertions for debug mode
	VERIFY(controlBitmapButtonPaste.AutoLoad(IDC_PASTE_KEY,this));

	// add tool tip to the paste button
	CString buttonPasteText;
	buttonPasteText.LoadString(IDS_STRING_PASTE_KEY_FROM_KEY_STORE);
	controlBitmapButtonPaste.SetToolTipText(&buttonPasteText);

	// load stored settings (key and offset) from registry
	loadSettings();

	UpdateData(false);

	// update the GUI
	updateGUI();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur?ckgeben
}

// CDlgSimpleTranspositions message handlers

void CDlgSimpleTranspositions::OnBnClickedEncrypt()
{
	UpdateData(true);

	// check if the key is valid
	if(key < 1) {
		LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}

	// check if the offset is valid
	if(offset < 0) {
		LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_OFFSET_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}

	// now, do the actual encryption
	if(type == 0) { // SCYTALE
		int result = ScytaleEncryption(fileName.GetBuffer(), fileNameTitle.GetBuffer(), key, offset, true);
		if(result == -1) {
			LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);	
			return;
		}
	}
	if(type == 1) { // RAIL FENCE
		int result = RailFenceEncryption(fileName.GetBuffer(), fileNameTitle.GetBuffer(), key, offset, true);
		if(result == -1) {
			LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);	
			return;
		}
	}
	
	// store settings (key and offset)
	saveSettings();

	EndDialog(IDOK);
}

void CDlgSimpleTranspositions::OnBnClickedDecrypt()
{
	UpdateData(true);

	// check if the key is valid
	if(key < 1) {
		LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}

	// check if the offset is valid
	if(offset < 0) {
		LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_OFFSET_INVALID, pc_str, STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, "CrypTool", MB_ICONINFORMATION);
		return;
	}

	// now, do the actual encryption
	if(type == 0) // SCYTALE
		ScytaleEncryption(fileName.GetBuffer(), fileNameTitle.GetBuffer(), key, offset, false);
	if(type == 1) // RAIL FENCE
		RailFenceEncryption(fileName.GetBuffer(), fileNameTitle.GetBuffer(), key, offset, false);

	// store settings (key and offset)
	saveSettings();

	EndDialog(IDOK);
}

void CDlgSimpleTranspositions::OnBnClickedTextoptions()
{
	// allow the user to change the CrypTool alphabet
	theApp.TextOptions.DoModal();
}

void CDlgSimpleTranspositions::OnRadioScytale()
{
	// we want to update the GUI depending on the state we're in
	updateGUI();
}

void CDlgSimpleTranspositions::OnRadioRailFence()
{
	// we want to update the GUI depending on the state we're in
	updateGUI();
}

void CDlgSimpleTranspositions::updateGUI() 
{
	UpdateData(true);

	// the first thing we want to do is find out which mode we're running in
	if(type == 0) {				// SCYTALE
		// update the key description
		CWnd *windowKeyDescription = GetDlgItem(IDC_SIMPLE_TRANSPOSITION_KEY);
		if(windowKeyDescription) {
			LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_DESCRIPTION_SCYTALE, pc_str, STR_LAENGE_STRING_TABLE);
			windowKeyDescription->SetWindowTextA(pc_str); 
		}
		// update the image
		controlImage.SetBitmap(bitmapScytale);

	}
	if(type == 1) {				// RAIL FENCE
		// update the key description
		CWnd *windowKeyDescription = GetDlgItem(IDC_SIMPLE_TRANSPOSITION_KEY);
		if(windowKeyDescription) {
			LoadString(AfxGetInstanceHandle(), IDS_SIMPLE_TRANSPOSITION_KEY_DESCRIPTION_RAIL_FENCE, pc_str, STR_LAENGE_STRING_TABLE);
			windowKeyDescription->SetWindowTextA(pc_str);
		}
		// update the image
		controlImage.SetBitmap(bitmapRailFence);
	}

	// display the paste key button only if there's a valid key in the key store
	if(checkPasteKeyVariant(IDS_CRYPT_SIMPLETRANSPOSITION).key)
		controlBitmapButtonPaste.EnableWindow(TRUE);
	else controlBitmapButtonPaste.EnableWindow(FALSE);

	UpdateData(false);
}

void CDlgSimpleTranspositions::loadSettings() {
	// try to load settings (key and offset) from windows registry
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_READ, IDS_REGISTRY_SETTINGS, "SimpleTranspositions") == ERROR_SUCCESS) {		
		unsigned long ulType = type;
		unsigned long ulKey = key;
		unsigned long ulOffset = offset;
		CT_READ_REGISTRY(ulType, "Type");
		CT_READ_REGISTRY(ulKey, "Key");
		CT_READ_REGISTRY(ulOffset, "Offset");
		CT_CLOSE_REGISTRY();
		type = ulType;
		key = ulKey;
		offset = ulOffset;
	}
}

void CDlgSimpleTranspositions::saveSettings() {
	// try to write settings (key and offset) to windows registry
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_WRITE, IDS_REGISTRY_SETTINGS, "SimpleTranspositions") == ERROR_SUCCESS) {
		CT_WRITE_REGISTRY((unsigned long)type, "Type");
		CT_WRITE_REGISTRY((unsigned long)key, "Key");
		CT_WRITE_REGISTRY((unsigned long)offset, "Offset");
		CT_CLOSE_REGISTRY();
	}
}

void CDlgSimpleTranspositions::OnPasteKey() 
{
	SimpleTranspositionKey theKey;
	// check for simple transposition key
	theKey = checkPasteKeyVariant(IDS_CRYPT_SIMPLETRANSPOSITION);
	
	// display error message if it's not a simple transposition key
	if(!theKey.key) {
		LoadString(AfxGetInstanceHandle(),IDS_SIMPLETRANSPOSITION_BAD_KEY,pc_str,255);
		AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
	}
	// if the key is valid, enable/disable the respective GUI elements ("simulate" user input)...
	else {
		this->type = theKey.type;
		this->key = theKey.key;
		this->offset = theKey.offset;
	}

	// this is ugly, but without this line the pasted key gets overwritten
	UpdateData(false);

	// ...and update the GUI
	updateGUI();
}

SimpleTranspositionKey CDlgSimpleTranspositions::checkPasteKeyVariant(int SID)
{
	SimpleTranspositionKey theKey;
	CString theKeyString;
	LoadString(AfxGetInstanceHandle(),SID,pc_str,STR_LAENGE_STRING_TABLE);
	if (PasteKey(pc_str, theKeyString)) {
		// what we get here is a string of the form "TYPE: 0, KEY: 3, KEY OFFSET: 0" or 
		// "TYPE: 1, KEY: 4, KEY OFFSET: 2" (and so on), so we separate the key type 
		// (here: "0" or "1") from the actual key (here: "3" or "4") and the key offset 
		// (here: "0" or "2").
		CString type = extractValueFromStringByKey("TYPE", theKeyString);
		CString key = extractValueFromStringByKey("KEY", theKeyString);
		CString offset = extractValueFromStringByKey("KEY OFFSET", theKeyString);
		// copy key and offset into key structure
		theKey.type = _ttoi(type);
		theKey.key = _ttoi(key);
		theKey.offset = _ttoi(offset);
	}
	return theKey;
}