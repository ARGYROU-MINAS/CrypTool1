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

#if !defined(AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEPSEPINPROMPT_H__C7A5452A_8D2D_4408_A983_FC5EE1517D2F__INCLUDED_)
#define AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEPSEPINPROMPT_H__C7A5452A_8D2D_4408_A983_FC5EE1517D2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSideChannelAttackVisualizationHEPSEPINPrompt.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSideChannelAttackVisualizationHEPSEPINPrompt 

class CDlgSideChannelAttackVisualizationHEPSEPINPrompt : public CDialog
{
// Konstruktion
public:
	CDlgSideChannelAttackVisualizationHEPSEPINPrompt(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgSideChannelAttackVisualizationHEPSEPINPrompt)
	enum { IDD = IDD_SIDECHANNELATTACKVISUALIZATION_HE_PSEPINPROMPT };
	CString	m_pin;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgSideChannelAttackVisualizationHEPSEPINPrompt)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgSideChannelAttackVisualizationHEPSEPINPrompt)
		// HINWEIS: Der Klassen-Assistent fügt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGSIDECHANNELATTACKVISUALIZATIONHEPSEPINPROMPT_H__C7A5452A_8D2D_4408_A983_FC5EE1517D2F__INCLUDED_
