#if !defined(AFX_DLGPARAMRANDSECUDE_H__87703502_3308_11D5_92F3_00B0D0161C45__INCLUDED_)
#define AFX_DLGPARAMRANDSECUDE_H__87703502_3308_11D5_92F3_00B0D0161C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgParamRandSECUDE.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgRandomParameterSECUDE 

class CDlgRandomParameterSECUDE : public CDialog
{
// Konstruktion
public:
	CDlgRandomParameterSECUDE(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgRandomParameterSECUDE)
	enum { IDD = IDD_RANDOMPARAMETER_SECUDE };
	CString	m_MessageSecude;
	//}}AFX_DATA


// �berschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktions�berschreibungen
	//{{AFX_VIRTUAL(CDlgRandomParameterSECUDE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgRandomParameterSECUDE)
		// HINWEIS: Der Klassen-Assistent f�gt hier Member-Funktionen ein
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ f�gt unmittelbar vor der vorhergehenden Zeile zus�tzliche Deklarationen ein.

#endif // AFX_DLGPARAMRANDSECUDE_H__87703502_3308_11D5_92F3_00B0D0161C45__INCLUDED_