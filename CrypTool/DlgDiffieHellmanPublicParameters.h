/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universität Siegen und Darmstadt

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


#if !defined(AFX_DLGDIFFIEHELLMANPUBLICPARAMETERS_H__4D741E0D_E4AE_11D6_A894_00025532117A__INCLUDED_)
#define AFX_DLGDIFFIEHELLMANPUBLICPARAMETERS_H__4D741E0D_E4AE_11D6_A894_00025532117A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <list>


// DlgDiffieHellmanPublicParameters.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgDiffieHellmanPublicParameters 
struct factor {
	int		exp;
	int     isPrime;
	CString strNum;

	factor(CString STRNUM, int ISPRIME)
	{ exp = 1; isPrime = ISPRIME; strNum = STRNUM; }
	void incExp() { exp++; }
};


class CDlgDiffieHellmanPublicParameters : public CDialog
{
// Konstruktion
	std::list<factor> factorlistPhiOfP;

	int PrimeParameterGenerationRFC2631(int bitlengthP, int bitlengthQ);

public:
	CDlgDiffieHellmanPublicParameters(CWnd* pParent = NULL);				// Standardkonstruktor
	CDlgDiffieHellmanPublicParameters(std::string,std::string,CWnd* pParent = NULL);	// Zusatzkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgDiffieHellmanPublicParameters)
	enum { IDD = IDD_DIFFIEHELLMAN_PUBLICPARAMETERS };
	CEdit	m_PrimeControl;
	CEdit	m_GeneratorControl;
	CString	m_Generator;
	CString	m_Prime;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgDiffieHellmanPublicParameters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgDiffieHellmanPublicParameters)
	virtual void OnOK();
	afx_msg void OnGeneratePrime();
	afx_msg void OnGenerateGenerator();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGDIFFIEHELLMANPUBLICPARAMETERS_H__4D741E0D_E4AE_11D6_A894_00025532117A__INCLUDED_
