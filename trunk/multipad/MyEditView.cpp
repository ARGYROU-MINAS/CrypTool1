// MyEditView.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "multipad.h"
#include "MyEditView.h"
#include "SchluesselAusgabeLinear.h"
#include "HillSchluesselAusgabe.h"
#include "HillSchluesselAusgabeGross.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEditView

IMPLEMENT_DYNCREATE(CMyEditView, CRichEditView)

CMyEditView::CMyEditView()
{
}

CMyEditView::~CMyEditView()
{
}


BEGIN_MESSAGE_MAP(CMyEditView, CRichEditView)
	//{{AFX_MSG_MAP(CMyEditView)
	ON_WM_KILLFOCUS()
	ON_COMMAND(ID_GOTO_VATER, OnGotoVater)
	ON_COMMAND(ID_SHOW_KEY, OnShowKey)
	ON_WM_CONTEXTMENU()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Zeichnung CMyEditView 

void CMyEditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// ZU ERLEDIGEN: Code zum Zeichnen hier einf�gen
}

/////////////////////////////////////////////////////////////////////////////
// Diagnose CMyEditView

#ifdef _DEBUG
void CMyEditView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CMyEditView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CMyEditView 


// Zum Sprung zum Vaterfenster ist es notwendig, da� wir uns die windowHandle merken.
void CMyEditView::OnKillFocus(CWnd* pNewWnd) 
{
	// Dies muss vorher gemacht werden, damit das Fenster noch den Eingabefokus hat,
	// um die Fenster Handle speichern zu koennen.
	hWndAktivesFenster = m_hWnd;

	CRichEditView::OnKillFocus(pNewWnd);
	
	// TODO: Code f�r die Behandlungsroutine f�r Nachrichten hier einf�gen
	
}

void CMyEditView::OnGotoVater() 
{
	// TODO: Code f�r Befehlsbehandlungsroutine hier einf�gen

	// Sprung zum Fenster, sofern es noch ge�ffnet ist
	if ( IsWindow(((CMyDocument*)GetDocument())->hWndVaterFenster) )
	{
		((CMDIFrameWnd*)theApp.m_pMainWnd)->
			MDIActivate(((CMyDocument*)GetDocument())->CWndVaterFenster);
	}
}

void CMyEditView::OnShowKey() 
{
	// TODO: Code f�r Befehlsbehandlungsroutine hier einf�gen

	CString Key = ((CMyDocument*)m_pDocument)->csSchluessel;

	if ( Key.GetLength() > 0 )
	{
		if ( ((CMyDocument*)m_pDocument)->iSchluesselTyp == SCHLUESSEL_LINEAR )
		{
			CSchluesselAusgabeLinear AusgabeFenster;
			
			AusgabeFenster.m_Key = Key;

			// Fenster anzeigen
			AusgabeFenster.DoModal();
		}
		else if ( ((CMyDocument*)m_pDocument)->iSchluesselTyp == SCHLUESSEL_QUADRATISCH )
		{
			// Hill Verfahren: 
			// Format des Schluessels: Zeilenweise, durch jeweils ein Leerzeichen getrennt
			// HILL_MAX_DIM=5: 5x5 hat also 25+4=29 Zeichen
			if (Key.GetLength() <= HILL_MAX_DIM*HILL_MAX_DIM+(HILL_MAX_DIM-1))
			{
				CHillSchluesselAusgabe AusgabeFenster;

				AusgabeFenster.SchluesselAnzeigen(Key);
				
				// Es wird immer der Schluessel zum Verschluesseln angezeigt
				AusgabeFenster.m_decrypt = FALSE;
				
				// Fenster anzeigen
				AusgabeFenster.DoModal();
			}
			else
			{
				CHillSchluesselAusgabeGross AusgabeFenster;

				AusgabeFenster.SchluesselAnzeigen(Key);
				
				// Es wird immer der Schluessel zum Verschluesseln angezeigt
				AusgabeFenster.m_decrypt = FALSE;
				
				// Fenster anzeigen
				AusgabeFenster.DoModal();
			}
		}
		else
		{
			ASSERT(false);
		}
	}
}


void CMyEditView::SerializeRaw(CArchive & ar)
{
	char *buffer;
	int bufflen=20000, len;
	long start, end, textlen, pos;

	SetRedraw(FALSE);
	GetRichEditCtrl().GetSel(start, end);
	buffer = (char *) malloc(bufflen+3);

	if (ar.IsStoring())
	{
		textlen = GetRichEditCtrl().GetTextLength();
		for(pos = 0; pos < textlen; ) {
			GetRichEditCtrl().SetSel(pos, pos+bufflen);
			len = GetRichEditCtrl().GetSelText(buffer);
			TRY
			{
				ar.Write(buffer, len);
			}
			CATCH_ALL(e)
			{
				THROW_LAST();
			}
			END_CATCH_ALL
			pos += len;
		}
	}
	else
	{
		CFile* pFile = ar.GetFile();
		ASSERT(pFile->GetPosition() == 0);
		long nFileSize = pFile->GetLength();
		// ReadFromArchive takes the number of characters as argument

		for(pos = 0; pos < nFileSize; ) {
			len = ar.Read(buffer, bufflen);
			buffer[len]=0;
			GetRichEditCtrl().SetSel(pos,pos);
			GetRichEditCtrl().ReplaceSel(buffer);
			pos += len;
			if(!len) break;
		}
		GetRichEditCtrl().EmptyUndoBuffer();
		ASSERT_VALID(this);
	}
	free(buffer);
	GetRichEditCtrl().SetSel(start, end);
	SetRedraw(TRUE);
	ASSERT_VALID(this);
}

void CMyEditView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Code f�r die Behandlungsroutine f�r Nachrichten hier einf�gen

	// Es ist nicht moeglich, die Zustaende des Anwendungsmenues abzulesen, und diese
	// dann als Zustaende fuer das Kontextmenue zu verwenden, da die Zustaende der 
	// Befehle des Anwendungsmenues erst nach Oeffnen des Menues aktualisiet werden. 
	// Deshalb wurde die Aktivierung/Deaktivierung von Menuepunktenn zu Fu� gemacht.
	// Die folgenden Funktionen stammen aus DevStudion\Vc\mfc\src\VIEWEDIT.CPP
	// void CRichEditView::OnUpdateNeedSel(CCmdUI* pCmdUI)
	// void CRichEditView::OnUpdateNeedClip(CCmdUI* pCmdUI)
	// void CRichEditView::OnUpdateNeedText(CCmdUI* pCmdUI)
	// (void CRichEditView::OnUpdateNeedFind(CCmdUI* pCmdUI))
	// void CRichEditView::OnUpdateEditUndo(CCmdUI* pCmdUI)

	// Kontextmenue laden
	CMenu KontextMenu;
	KontextMenu.LoadMenu(IDR_CONTEXT_MENU);

	// Ist kein Text markiert ?
	long nStartChar, nEndChar;
	GetRichEditCtrl().GetSel(nStartChar, nEndChar);
	if (nStartChar == nEndChar)
	{
		// Ausschneiden, Kopieren und Loeschen deaktivieren
		KontextMenu.EnableMenuItem(ID_EDIT_CUT, MF_GRAYED);
		KontextMenu.EnableMenuItem(ID_EDIT_COPY, MF_GRAYED);
		KontextMenu.EnableMenuItem(ID_EDIT_CLEAR, MF_GRAYED);
	}

	// Befindet sich kein Text in der Zwischenablage ?
	if (! ::IsClipboardFormatAvailable(CF_TEXT))
	{
		// Einfuegen deaktivieren
		KontextMenu.EnableMenuItem(ID_EDIT_PASTE, MF_GRAYED);
	}

	// Befindet sich kein Text im Fenster ?
	if (GetWindowTextLength() == 0)
	{
		// Alles markieren deaktivieren
		KontextMenu.EnableMenuItem(ID_EDIT_SELECT_ALL, MF_GRAYED);
	}

	// Ist Rueckgaengig machen nicht moeglich ?
	if (! GetRichEditCtrl().CanUndo())
	{
		KontextMenu.EnableMenuItem(ID_EDIT_UNDO, MF_GRAYED);
	}

	// Existiert das Vaterfenster nicht (mehr) ?
	if(!IsWindow(((CMyDocument*)GetDocument())->hWndVaterFenster))
	{
		// Sprung zum Vaterfenster deaktivieren
        KontextMenu.EnableMenuItem(ID_GOTO_VATER, MF_GRAYED);
	}
	
	// Gibt es keinen Schluessel ?
	if(((CMyDocument*)GetDocument())->csSchluessel.GetLength() == 0)
	{
		// Schleussel anzeigen deaktivieren
        KontextMenu.EnableMenuItem(ID_SHOW_KEY, MF_GRAYED);
	}

	// Und schliesslich das Kontextmenue anzeigen
	KontextMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);
}


void CMyEditView::OnSetFocus(CWnd* pOldWnd) 
{
	CRichEditView::OnSetFocus(pOldWnd);
	
	// Zum Sprung zum Vaterfenster ist es notwendig, da� wir uns die windowHandle merken.
	// Dies muss nach OnSetFocus gemacht werden, damit das Fenster den Eingabefokus hat,
	// um die Fenster Handle speichern zu koennen.
	hWndAktivesFenster = m_hWnd;
}

HRESULT CMyEditView::QueryAcceptData(LPDATAOBJECT lpdataobj, CLIPFORMAT *lpcfFormat, DWORD dwReco, BOOL bReally, HGLOBAL hMetaFile)
{
	ASSERT(lpcfFormat != NULL);
	if (!bReally) // not actually pasting
		return S_OK;

	COleDataObject dataobj;
	dataobj.Attach(lpdataobj, FALSE);
	// if format is 0, then force particular formats if available
	if (*lpcfFormat == 0 && (m_nPasteType == 0))
	{
		if (dataobj.IsDataAvailable(CF_TEXT))
		{
			*lpcfFormat = CF_TEXT;
			return S_OK;
		}
	}
	return S_FALSE;
}
