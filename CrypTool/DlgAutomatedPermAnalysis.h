/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universitšt Siegen und Darmstadt

This file is part of CrypTool.

CrypTool is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

Foobar is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with CrypTool; if not, write to the Free Software Foundation,
Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

In addition, as a special exception, Secude GmbH gives permission to
link the code of this program with the library SECUDE (or with
modified versions of SECUDE that use the same license as SECUDE), and
distribute linked combinations including the two. You must obey the
GNU General Public License in all respects for all of the code used
other than SECUDE. If you modify this file, you may extend this
exception to your version of the file, but you are not obligated to do
so. If you do not wish to do so, delete this exception statement from
your version.
 
In addition, as a special exception, Shamus Software Ltd. gives
permission to link the code of this program with the library libmiracl
(or with modified versions of libmiracl that use the same license as
libmiracl), and distribute linked combinations including the two. You
must obey the GNU General Public License in all respects for all of
the code used other than libmiracl. If you modify this file, you may
extend this exception to your version of the file, but you are not
obligated to do so. If you do not wish to do so, delete this exception
statement from your version.

**********************************************************************/


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

public:
	automated_permanalysis permanalysis;
	CDlgAutomatedPermAnalysis(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgAutomatedPermAnalysis();

// Dialog Data
	enum { IDD = IDD_AUTOMATED_PERM_ANALYSIS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnBerechnen();
	afx_msg void OnBnClickedRbFest();
	afx_msg void OnBnClickedBtnAbbruch();
	afx_msg void OnBnClickedGbEinlesen();
	afx_msg void OnBnClickedRbIntervall();
	afx_msg void OnBnClickedRbSuchen();
	afx_msg void OnBnClickedBtnKlartext();
	afx_msg void OnBnClickedBtnGeheimtext();
	int rb_einlesen;
	int rb_permutation;
	int rb_auslesen;
	CString tb_klartext;
	CString tb_geheimtext;
	int rb_permsize;
	CString tb_fest;
	CString tb_lowerLimit;
	CString tb_upperLimit;
};


#endif