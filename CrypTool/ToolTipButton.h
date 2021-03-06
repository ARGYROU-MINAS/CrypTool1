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

#ifndef _TOOLTIPBUTTON_H_
#define _TOOLTIPBUTTON_H_

#if _MSC_VER > 1000
#pragma once
#endif

class CToolTipButton : public CBitmapButton {
public:
	CToolTipButton();
	virtual ~CToolTipButton();

protected:
	CToolTipCtrl m_ToolTip;

public:
	void SetToolTipText(CString* spText, BOOL bActivate = TRUE);

protected:
	void InitToolTip();

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
};

#endif