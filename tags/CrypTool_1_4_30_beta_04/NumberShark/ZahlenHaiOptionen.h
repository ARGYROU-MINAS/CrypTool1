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

#pragma once
#include "afxwin.h"
#include "afxcmn.h"

//#include "MFC-ZahlenHaiDlg.h"

// ZahlenHaiOptionen-Dialogfeld

class ZahlenHaiOptionen : public CDialog
{

	DECLARE_DYNAMIC(ZahlenHaiOptionen)
	
	

public:
	ZahlenHaiOptionen(CWnd* pParent = NULL);   // Standardkonstruktor
	virtual ~ZahlenHaiOptionen();

// Dialogfelddaten
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:

	CTabCtrl dialogOptionsTab;
	
	CStatic optionenButtonMax;
	CButton checkButton;
	CButton checkButtonOption;
	CButton checkStartNumber;
	CButton radioButton1;
	CButton radioButton2;
	
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedButtonMax();
	afx_msg void OnBnClickedRadioMax1();
	afx_msg void OnBnClickedRadioMax2();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);

	BOOL showToolTips;
	BOOL showOption;
    BOOL showStartNumber;
	
	int showButton;
	int exitOptions;
	int controlUpperLimit;
	int calcUpperLimit;
	int calculateMaxNew;
	int showMax;
	int optionenUpperLimit;

	CString playername;
	CString optionStart;
	CString optionToolTip;
	CString optionGameStart;
	CString optionRemember;
	CString optionenMaxP;
	
	void drawStartTab();
	void drawOptionsTab();
	CString gameIdea;
	CString disclaimerText;
	CString infoText;
	CRichEditCtrl richEditIdea;
	CStatic accControl;
};