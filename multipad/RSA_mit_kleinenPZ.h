#if !defined(AFX_RSA_MIT_KLEINENPZ_H__42495664_FB3E_11D4_BEF2_0006291976BD__INCLUDED_)
#define AFX_RSA_MIT_KLEINENPZ_H__42495664_FB3E_11D4_BEF2_0006291976BD__INCLUDED_

//#include <miracl.h>
//#include <big.h>
//#include "..\LIBMIRACL\INCLUDE\BIG.H"	// Hinzugefügt von der Klassenansicht
#include "RSA_Berechnungen.h"	// Hinzugefügt von der Klassenansicht
#include "DlgPrimesGenerator.h"	// Hinzugefügt von der Klassenansicht
//#include "Primes_and_random_numbers.h"	// Hinzugefügt von der Klassenansicht
#include "DlgRSAwithSmallPrimesOptions.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RSA_mit_kleinenPZ.h : Header-Datei
//


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld RSA_mit_kleinenPZ 
class RSA_mit_kleinenPZ : public CDialog
{
	
// Konstruktion
public:
	void EncryptASCII();
	void DecryptASCII();
	void EncryptDialogueOfSisters();
	void DecryptDialogueOfSisters();
	void EncryptAlphabet();
	void DecryptAlphabet();
	void EncryptNumbers();
	void DecryptNumbers();
	
	RSA_mit_kleinenPZ(CWnd* pParent = NULL);   // Standardkonstruktor
	~RSA_mit_kleinenPZ();

// Dialogfelddaten
	//{{AFX_DATA(RSA_mit_kleinenPZ)
	enum { IDD = IDD_DIALOG_RSA_MIT_KLEINEN_PRIMZAHLEN };
	CEdit	m_control_edit13;
	CButton	m_ButtonOptionen;
	CButton	m_ButtonEncrypt;
	CButton	m_ButtonDecrypt;
	CEdit	m_control_edit11;
	CEdit	m_control_edit12;
	CEdit	m_control_edit10;
	CEdit	m_control_q;
	CEdit	m_control_p;
	CString	m_eingabe_p;
	CString	m_eingabe_q;
	CString	m_geheime_parameter;
	CString	m_oeffentliche_parameter_pq;
	CString	m_oeffentliche_schluessel_e;
	CString	m_geheime_schluessel_d;
	CString	m_edit10;
	CString	m_edit11;
	CString	m_edit12;
	CString	m_Header1;
	CString	m_Header2;
	CString	m_Header3;
	CString	m_Header4;
	CString	m_edit13;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(RSA_mit_kleinenPZ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(RSA_mit_kleinenPZ)
	afx_msg void OnButtonPzGenerieren();
	afx_msg void OnUpdateEdit10();
	afx_msg void OnOptionen();
	afx_msg void OnParameterAktualisieren();
	afx_msg void OnButtonVerschluesseln();
	afx_msg void OnButtonEntschluesseln();
	virtual void OnEndDialog();
	virtual BOOL OnInitDialog();
	afx_msg void OnUpdatePrimeP();
	afx_msg void OnUpdatePrimeQ();
	afx_msg void OnUpdatePublicKeyE();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetHeadLine( CString &mHeader, int IDS_STRING_ID, int base = 0 );
	int GetBase();
	DlgPrimesGenerator            *DlgRSAPrimes;
	CDlgRSAwithSmallPrimesOptions *DlgOptions;
	TutorialRSA                   *RSA;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_RSA_MIT_KLEINENPZ_H__42495664_FB3E_11D4_BEF2_0006291976BD__INCLUDED_
