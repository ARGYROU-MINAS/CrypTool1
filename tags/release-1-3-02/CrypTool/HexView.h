//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
#ifndef AFX_HEXVIEW_H__0EFC0691_5F70_11D3_8772_00C04F795E36__INCLUDED_
#define AFX_HEXVIEW_H__0EFC0691_5F70_11D3_8772_00C04F795E36__INCLUDED_

// HexView.h : Header-Datei
//

#include "AppEditView.h"

/////////////////////////////////////////////////////////////////////////////
// Ansicht CHexView 

class CHexView : public CAppEditView
{
protected:
	CHexView();           // Dynamische Erstellung verwendet geschützten Konstruktor
	DECLARE_DYNCREATE(CHexView)

// Attribute
public:

// Operationen
public:
	int m_NoPrintChars;
	int m_TrailBlanks;
	HRESULT QueryAcceptData(LPDATAOBJECT lpdataobj, CLIPFORMAT *lpcfFormat, DWORD dwReco, 
		                    BOOL bReally, HGLOBAL hMetaFile);
	virtual void SerializeRaw(CArchive& ar);
	CSize CharSize;

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CHexView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // Überschrieben zum Zeichnen dieser Ansicht
	//}}AFX_VIRTUAL

// Implementierung
protected:
	virtual ~CHexView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	int m_NewSize;
	BOOL m_SizeActive;
	int AdjustCursor(int direction);
	int m_curlen;
	int m_totlen;
	int m_lineoffset;
	int m_curline;
	int m_hexwidth;
	int m_charoffset;
	int m_lineindex;
	char m_line[1024];
	CFont m_Font;
	//{{AFX_MSG(CHexView)
	afx_msg void OnUpdateFalse(CCmdUI* pCmdUI);
	afx_msg void OnEmpty();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdateTotxt(CCmdUI* pCmdUI);
	afx_msg void OnEditUndo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char GetCharAt(int offset);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio fügt zusätzliche Deklarationen unmittelbar vor der vorhergehenden Zeile ein.

#endif // AFX_HEXVIEW_H__0EFC0691_5F70_11D3_8772_00C04F795E36__INCLUDED_
