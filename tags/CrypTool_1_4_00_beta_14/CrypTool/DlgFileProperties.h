#if !defined(AFX_DLGFILEPROPERTIES_H__3D89C9AE_32B4_4A62_BA7A_8528F5079608__INCLUDED_)
#define AFX_DLGFILEPROPERTIES_H__3D89C9AE_32B4_4A62_BA7A_8528F5079608__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFileProperties.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgFileProperties 

class CDlgFileProperties : public CDialog
{
	CString m_key;
	int     m_keyType;
//	CBitmapButton m_paste;
	CBitmapButton m_showKey;

	// Konstruktion
public:
	void copyFileInfos(CString contentName, CString fName, CString title, 
		CString key, int keyType, CString strView);
	CDlgFileProperties(CWnd* pParent = NULL);   // Standardkonstruktor

// Dialogfelddaten
	//{{AFX_DATA(CDlgFileProperties)
	enum { IDD = IDD_FILE_PROPERTIES };
	CString	m_tmpFilename;
	CString	m_fileType;
	CString	m_fileSize;
	CString	m_strTitle;
	CString	m_strFilePath;
	CString	m_strPathTemp;
	CString	m_fileName;
	//}}AFX_DATA


// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CDlgFileProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	//}}AFX_VIRTUAL

// Implementierung
protected:

	// Generierte Nachrichtenzuordnungsfunktionen
	//{{AFX_MSG(CDlgFileProperties)
	afx_msg void OnShowKey();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_DLGFILEPROPERTIES_H__3D89C9AE_32B4_4A62_BA7A_8528F5079608__INCLUDED_
