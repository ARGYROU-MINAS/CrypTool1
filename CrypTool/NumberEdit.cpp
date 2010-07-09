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

#include "stdafx.h"
#include "NumberEdit.h"
#include "CrypToolTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNumberEdit::CNumberEdit() {
	// some initializations
	stringNumber = "";
	selectionStart = 0;
	selectionEnd = 0;
	// get separators from resource file (we need them later on)
	theIntegralSeparator = getIntegralNumberSeparator();
	theFractionalSeparator = getFractionalNumberSeparator();
	// do we want to show integral separators?
	showIntegralSeparators = true;
}

CNumberEdit::~CNumberEdit() {
	
}

BEGIN_MESSAGE_MAP(CNumberEdit, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_PASTE, OnPaste)
END_MESSAGE_MAP()

void CNumberEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// we don't want the user to alter disabled edit fields
	if(!IsWindowEnabled()) {
		return;
	}

	// we react to a specific set of characters only: signs [+-], digits [0-9], 
	// and fractional separators (i.e. [,] in German, and [.] in English)
	CString validCharacters = "+-0123456789";
	validCharacters.AppendChar(theFractionalSeparator);
	validCharacters.AppendChar(VK_BACK);
	validCharacters.AppendChar(VK_DELETE);
	if(validCharacters.Find(nChar) == -1) {
		return;
	}

	// get the current selection
	GetSel(selectionStart, selectionEnd);

	// deletion through BACK key
	if(nChar == VK_BACK) {
		if(selectionStart == selectionEnd) {
			stringNumber.Delete(selectionStart - 1, 1);
			SetWindowText(stringNumber);
			SetSel(selectionStart - 1, selectionStart - 1);
		}
		else {
			stringNumber.Delete(selectionStart, selectionEnd - selectionStart);
			SetWindowText(stringNumber);
			SetSel(selectionStart, selectionStart);
		}
	}

	// SIGNS
	if(nChar == '+' || nChar == '-') {
		if(selectionStart == 0) {
			stringNumber.Delete(selectionStart, selectionEnd - selectionStart);
			stringNumber.Insert(selectionStart, nChar);
			SetWindowText(stringNumber);
			SetSel(selectionStart + 1, selectionStart + 1);
		}	
	}
	// NUMBERS
	if(nChar >= '0' && nChar <= '9') {
		stringNumber.Delete(selectionStart, selectionEnd - selectionStart);
		stringNumber.Insert(selectionStart, nChar);
		SetWindowText(stringNumber);
		SetSel(selectionStart + 1, selectionStart + 1);
	}
	// FRACTIONAL SEPARATOR
	if(nChar == theFractionalSeparator && stringNumber.Find(theFractionalSeparator) == -1) {
		stringNumber.Delete(selectionStart, selectionEnd - selectionStart);
		stringNumber.Insert(selectionStart, nChar);
		SetWindowText(stringNumber);
		SetSel(selectionStart + 1, selectionStart + 1);
	}

	// adjust the number format (in particular, insert integral separators)
	adjustNumberFormat();
}

void CNumberEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	// we react to a specific set of characters only
	switch(nChar) {
	case VK_LEFT:
	case VK_RIGHT:
	case VK_UP:
	case VK_DOWN:
		CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
		break;
	default:
		break;
	}
	SetRedraw(TRUE);
	Invalidate(TRUE);
}

LRESULT CNumberEdit::OnPaste(WPARAM wparam, LPARAM lparam) {
	CString clipboardText;

	// at first we try to get the contents of the clipboard
  if(::IsClipboardFormatAvailable(CF_TEXT)) {
    // open the clipboard to get clipboard text
    if(::OpenClipboard(m_hWnd)) {
      HANDLE  hClipBrdData = NULL;
      if((hClipBrdData = ::GetClipboardData(CF_TEXT)) != NULL) {
        LPTSTR  lpClipBrdText = (LPTSTR)::GlobalLock(hClipBrdData);
        if(lpClipBrdText) {
          clipboardText = lpClipBrdText;
          ::GlobalUnlock(hClipBrdData);
        }
      }
			VERIFY(::CloseClipboard());
		}
	
		// now we should have the contents of the clipboard;
		// however, we need to replace the line breaks with spaces 
		// to prevent the input field from getting messed up
		int lineBreakIndex = 0;
		while((lineBreakIndex = clipboardText.Find("\r\n")) != -1) {
			clipboardText.Delete(lineBreakIndex, 2);
			clipboardText.Insert(lineBreakIndex, " ");
		}
	}

	// replace existing selection (don't replace text that was not selected)
	CString oldText;
	GetWindowText(oldText);
	
	int selectionStart = 0;
	int selectionEnd = 0;
	this->GetSel(selectionStart, selectionEnd);

	// create new string number (with the pasted contents from the clipboard)
	CString newStringNumber;
	newStringNumber.Append(stringNumber.GetBuffer(), selectionStart);
	newStringNumber.Append(clipboardText);
	newStringNumber.Append(stringNumber.GetBuffer() + selectionEnd, stringNumber.GetLength() - selectionEnd);

	// assign new string number
	stringNumber = newStringNumber;
	// adjust the number format (in particular, insert integral separators)
	adjustNumberFormat();
	
	return 0;
}

CString CNumberEdit::getNumberAsCString() {
	CString result;
	CString validCharacters = "+-0123456789.";
	for(int i=0; i<stringNumber.GetLength(); i++) {
		if(validCharacters.Find(stringNumber[i]) != -1) {
			result.AppendChar(stringNumber[i]);
		}
	}
	return result;
}

CString CNumberEdit::getNumberAsCStringLanguageDependent(const bool &_withDigitGroupings) {
	CString result;
	CString validCharacters = "+-0123456789";
	validCharacters.AppendChar(theIntegralSeparator);
	validCharacters.AppendChar(theFractionalSeparator);
	for(int i=0; i<stringNumber.GetLength(); i++) {
		if(validCharacters.Find(stringNumber[i]) != -1) {
			result.AppendChar(stringNumber[i]);
		}
	}
	return result;
}

void CNumberEdit::setNumber(const CString &_number) {
	CString result;
	// we go through our string number and remove everything but valid characters, 
	// which are signs [+-], the ten digits [0-9], and the fractional separator 
	char fractionalSeparator = getFractionalNumberSeparator();
	CString validCharacters = "+-0123456789";
	validCharacters.AppendChar(fractionalSeparator);
	for(int i=0; i<_number.GetLength(); i++) {
		if(validCharacters.Find(_number[i]) != -1) {
			result.AppendChar(_number[i]);
		}
	}
	stringNumber = result;
	SetWindowText(stringNumber);
	SetSel(stringNumber.GetLength(), stringNumber.GetLength());
}

void CNumberEdit::setText(const CString &_text) {
	// we purposely don't do any checks here: this function is provided for 
	// convenience; it can be used for displaying random text in the edit field
	stringNumber = _text;
	SetWindowText(stringNumber);
}

void CNumberEdit::adjustNumberFormat() {
	// get the current selection
	GetSel(selectionStart, selectionEnd);

	// chop leading sign (if necessary), and store it for later use
	CString stringNumberSign;
	if(stringNumber[0] == '+' || stringNumber[0] == '-') {
		stringNumberSign.AppendChar(stringNumber[0]);
		stringNumber.Delete(0, 1);
	}

	// chop trailing fractional part (if necessary), and store it for later use
	CString stringNumberFractionalSeparator;
	CString stringNumberFractionalPart;
	int i = stringNumber.Find(theFractionalSeparator);
	if(i != -1) {
		stringNumberFractionalPart = stringNumber;
		stringNumberFractionalPart.Delete(0, i + 1);
		stringNumber.Delete(i, stringNumber.GetLength() - i);
		stringNumberFractionalSeparator.AppendChar(theFractionalSeparator);
	}

	// determine the amount of integral separators BEFORE reformatting
	int amountOfIntegralSeparatorsStart = 0;
	for(int i=0; i<stringNumber.GetLength(); i++) {
		if(stringNumber[i] == theIntegralSeparator) {
			amountOfIntegralSeparatorsStart++;
		}
	}

	// remove all existing integral separators
	stringNumber.Remove(theIntegralSeparator);

	// determine the amount of integral separators we need
	int amountOfIntegralSeparatorsEnd = (stringNumber.GetLength() - 1) / 3;

	// insert integral separators (if desired)
	if(showIntegralSeparators) {
		for(int i=0; i<amountOfIntegralSeparatorsEnd; i++) {
			stringNumber.Insert(stringNumber.GetLength() - 3*(i+1) - i, theIntegralSeparator);
		}
	}
	
	// re-build string number
	if(stringNumberSign.GetLength() > 0)
		stringNumber.Insert(0, stringNumberSign);
	if(stringNumberFractionalSeparator.GetLength() > 0)
		stringNumber.AppendChar(theFractionalSeparator);
	if(stringNumberFractionalPart.GetLength() > 0)
		stringNumber.Append(stringNumberFractionalPart);

	// display string number
	SetWindowText(stringNumber);	

	// update selection
	if(showIntegralSeparators) {
		int offset = amountOfIntegralSeparatorsEnd - amountOfIntegralSeparatorsStart;
		SetSel(selectionStart + offset, selectionEnd + offset);
	}
	else {
		SetSel(selectionStart, selectionStart);
	}
}