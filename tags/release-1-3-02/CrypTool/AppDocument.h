#ifndef AFX_MYDOCUMENT_H__AD95E458_D56B_11D3_878E_00C04F795E36__INCLUDED_
#define AFX_MYDOCUMENT_H__AD95E458_D56B_11D3_878E_00C04F795E36__INCLUDED_

// MyDocument.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Dokument CAppDocument 

class CAppDocument : public CDocument
{
protected:
	CAppDocument();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CAppDocument)

// Attribute
public:

// Operationen
public:
	virtual void SetData(int);

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CAppDocument)
	public:
	virtual void Serialize(CArchive& ar);   // Überschrieben für Dokument-Ein-/Ausgabe
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementierung
public:
	HWND hWndVaterFenster;
	CWnd* CWndVaterFenster;
	CString csSchluessel;
	int iSchluesselTyp;
	virtual ~CAppDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CAppDocument)
	afx_msg void OnUpdateGotoVater(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowKey(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_MYDOCUMENT_H__AD95E458_D56B_11D3_878E_00C04F795E36__INCLUDED_
