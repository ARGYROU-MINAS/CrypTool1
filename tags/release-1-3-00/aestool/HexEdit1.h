#if !defined(AFX_HEXEDIT1_H__04BE516C_E9FF_11D3_888D_0010A4F6E7D5__INCLUDED_)
#define AFX_HEXEDIT1_H__04BE516C_E9FF_11D3_888D_0010A4F6E7D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HexEdit1.h : Header-Datei
//

/////////////////////////////////////////////////////////////////////////////
// Fenster CHexEdit 

class CHexEdit : public CEdit
{
// Konstruktion
public:
	CHexEdit();

// Attribute
public:

// Operationen
public:

// Überschreibungen
	// Vom Klassen-Assistenten generierte virtuelle Funktionsüberschreibungen
	//{{AFX_VIRTUAL(CHexEdit)
	//}}AFX_VIRTUAL

// Implementierung
public:
	int SetHex(char *data, int len);
	char * BinData;
	int BinLen;
	virtual ~CHexEdit();

	// Generierte Nachrichtenzuordnungsfunktionen
protected:
	//{{AFX_MSG(CHexEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int SelOrigin;
	int active;
	int HexVal(char c);
	int BinBuffLen;
	void postproc( char *oldstring, int start, int end );
	void preproc( char **oldstring, int *start, int *end );
	int shrink(int val);
	int extend(int val, int max);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // AFX_HEXEDIT1_H__04BE516C_E9FF_11D3_888D_0010A4F6E7D5__INCLUDED_
