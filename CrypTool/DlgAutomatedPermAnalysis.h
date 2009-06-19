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

//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef _AUTOMATEDPERM_ANALYSIS_H
#define _AUTOMATEDPERM_ANALYSIS_H

#include "afxwin.h"
#include "resource.h"
#include "automated_permanalysis.h"

// CDlgAutomatedPermAnalysis dialog

class CDlgAutomatedPermAnalysis : public CDialog
{
	DECLARE_DYNAMIC(CDlgAutomatedPermAnalysis)
private:
	HWND hWndEditReference;

	automated_permanalysis permanalysis;
	char *fn_source;
	char *fn_reference;
	__int64 source_filesize;

	void OpenFile(const char *fileName);
	void SaveFile();

	LRESULT ScinMSG(UINT Msg, WPARAM wParam=0, LPARAM lParam=0) {
		return FromHandle(hWndEditReference)->SendMessage(Msg, wParam, lParam);
	}

	void setRefCaption();
	void setViewOptions();

public:
	CDlgAutomatedPermAnalysis(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAutomatedPermAnalysis();

// Dialog Data
	enum { IDD = IDD_AUTOMATED_PERM_ANALYSIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	void check_dir(int &rowByRow, int &colByCol, int isRowByRow);
public:
	virtual BOOL OnInitDialog();
	int setSourceFilename(const char *filename);
	afx_msg void OnBnClickedLoadFile();
	int m_refTextType;
	int m_chk_inRowbyRow;
	int m_chk_permRowbyRow;
	int m_chk_outRowbyRow;
	int m_chk_inColbyCol;
	int m_chk_permColbyCol;
	int m_chk_outColbyCol;
	int m_DataType;
	CString m_editRangeFrom;
	CString m_editRangeTo;
	CEdit   m_ctrlRefernceHeader;
	afx_msg void OnBnClickedCompute();
	afx_msg void OnBnClickedinRowByRow();
	afx_msg void OnBnClickedinColByCol();
	afx_msg void OnBnClickedPermRowByRow();
	afx_msg void OnBnClickedPermColByCol();
	afx_msg void OnBnClickedOutRowByRow();
	afx_msg void OnBnClickedOutColByCol();
	afx_msg void OnBnClickedRadioSourceIsCiphertext();
	afx_msg void OnBnClickedRadioSourceIsPlaintext();
	afx_msg void OnBnClickedRadioText();
	afx_msg void OnBnClickedRadioBinary();
	afx_msg void OnBnClickedTextOptions();
};


#endif