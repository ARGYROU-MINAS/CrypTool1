//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// multipad.cpp : Defines the class behaviors for the Multipad application.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "multipad.h"
#include "CryptDoc.h"
#include "PlotDoc.h"
#include "PlotView.h"
#include "FixedView.h"
#include "HexView.h"
#include "crypt.h"
#include "CryptDocTemplate.h"
#include "OptionsDialog.h"
#include "ECsecude.h"
#include <locale.h>
#include "About.h"

#include "asymmetric.h" // f�r KeyGen() in OnCRYPTKeyGen()
#include "DlgAsymKeys.h" // f�r OnShowKeys()

// globale Variablen fuer Zugriff auf Stringtable
// Deklariert in multipad.h
char pc_str[STR_LAENGE_STRING_TABLE];
char pc_str1[STR_LAENGE_STRING_TABLE];

// Globale Variablen fuer Zugriff auf Initialisierunsdatei
char *initializing_file="EC-Param.ini"; // This is the filename of the file, which contains the initializing values for assymmetric key generation

// Globale Variablen fuer wichtige Pfade und Dateien
char *Pfad; // Verzeichnis in dem CrypTool zur Laufzeit liegt
char *PseVerzeichnis; // PSE-Verzeichnis von CrypTool =Pfad+"/PSE";
char *CaPseVerzeichnis; // =Pfad+"/PSE/PSECA";
char *CaPseDatei; // =Pfad+"/PSE/PSECA/pseca";

// globale Variable, die angibt, ob der Dialog f�r kleine oder gro�e Schl�ssel
// und welche Dimension bei Hill Verfahren ge�ffnet werden soll
// Werte: siehe multipad.h
int iHillSchluesselFensterGroesse;
int iHillSchluesselDim;

// globale Variable, in der immer die Fenster Handle des aktive Fensters steht
HWND hWndAktivesFenster;
 

CMultiPadApp NEAR theApp;

BEGIN_MESSAGE_MAP(CMultiPadApp, CWinApp)
	//{{AFX_MSG_MAP(CMultiPadApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_OPTIONS_ANALYSIS, OnOptionsAnalysis)
	ON_COMMAND(ID_WINDOW_CLOSE_ALL, OnWindowCloseAll)
	ON_COMMAND(ID_OPTTEXT, OnOpttext)
	ON_UPDATE_COMMAND_UI(ID_CRYPT_KeyGen, OnUpdateNeedSecudeTicket)
	ON_COMMAND(ID_SHOW_ALL_EC_KEYS, OnShowKeys)
	ON_COMMAND(ID_CRYPT_KeyGen, OnKeyGen)
	ON_UPDATE_COMMAND_UI(ID_SHOW_ALL_EC_KEYS, OnUpdateNeedSecudeTicket)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)     // file commands...
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
// BEGINN Fuer Hilfe-Funktionalitaet eingefuegt
	// Globale Hilfebefehle
	ON_COMMAND(ID_HELP_FINDER, CWinApp::OnHelpFinder)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CWinApp::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, CWinApp::OnHelpFinder)
// ENDE
END_MESSAGE_MAP()

BOOL CMultiPadApp::InitInstance()
{
//	_tsetlocale(LC_ALL, _T(""));


	//Initialisierung der globalen Variablen
	iHillSchluesselFensterGroesse = HILL_SCHLUESSEL_KLEIN;
	iHillSchluesselDim = 2;

	hWndAktivesFenster = 0;

	KeyOpenDocumentFile.Empty();
	KeyTypeOpenDocumentFile = SCHLUESSEL_INIT;

	// CaPseDatei, CaPseVerzeichnis und Pfad (alle drei char *)
	// Es soll zun�chst der (komplette) Pfad der Anwendung herausgefunden werden.
	// Hierzu mu� unterschieden werden, ob die Anwendung von der Kommandozeile oder
	// aus dem Explorer (oder einer �hnlichen Anwendung) heraus aufgerufen wird.
	
	CString Pfad2=GetCommandLine();
	
	// AfxMessageBox (Pfad2);

	if (Pfad2.Find("\\")==-1){  // Es liegt noch kein kompletter Pfad vor
		// Pfad2.Find(":\\") wurde ge�ndert in Pfad2.Find("\\"), da bei Programmaufrufen
		// �ber das Netz ein falscher Pfad angegeben wurde.
		// Setze den Pfad aus GetCommandLine() und GetCurrentDirectory zusammen
		char* Pfad3=(char*)malloc(100);
		GetCurrentDirectory(99,Pfad3);
		CString Pfad4=(CString)Pfad3;
	
		// AfxMessageBox (Pfad3);

		free (Pfad3);
		// Setze den Pfad zusammen
		Pfad2=Pfad4+"\\"+Pfad2;

		// AfxMessageBox (Pfad2);

		// Schneide das f�hrende Hochkomma (") weg
		Pfad2=Pfad2.Left(Pfad2.ReverseFind(92)+1);

		// AfxMessageBox (Pfad2);

	}
	else{						// GetCommandLine hat bereits den kompletten Pfad geliefert
		// Schneide den Anwendungsnamen weg (nur der Pfad interessiert uns)
		Pfad2=Pfad2.Left(Pfad2.ReverseFind(92)+1);

		// AfxMessageBox (Pfad2);

		// Schneide das f�hrende Hochkomma (") weg
		Pfad2.SetAt(0,' ');
		Pfad2.TrimLeft();
	
		// AfxMessageBox (Pfad2);

	}

	// Umwandeln der Baskslashes in Slashes
	for (int i=0;i<Pfad2.GetLength();i++){
		if (Pfad2[i]==92){
			Pfad2.SetAt(i,47);}
	}

	// AfxMessageBox (Pfad2);
	
	//Die beiden folgenden Zeilen m�ssen f�r die endg�ltige Toolkit-Version (andere
	//Verzeichnisstruktur) herausgenommen werden!!!
	//Pfad2=Pfad2.Left(Pfad2.ReverseFind(92));
	//Pfad2=Pfad2.Left(Pfad2.ReverseFind(92));

	//Kopieren des Inhalts von CString Pfad2 nach char *Pfad
	LPTSTR help1 = new TCHAR[Pfad2.GetLength()+1];
	_tcscpy(help1, Pfad2);
	Pfad=help1;
	
	CString PseV, CaPseD, CaPseV;
	PseV  =Pfad2+"PSE";
	CaPseD=Pfad2+"PSE/PSECA/pseca";
	CaPseV=Pfad2+"PSE/PSECA";
		
	LPTSTR help2 = new TCHAR[CaPseD.GetLength()+1];
	_tcscpy(help2, CaPseD);
	CaPseDatei=help2;

	LPTSTR help3 = new TCHAR[CaPseV.GetLength()+1];
	_tcscpy(help3, CaPseV);
	CaPseVerzeichnis=help3;

	LPTSTR help4 = new TCHAR[PseV.GetLength()+1];
	_tcscpy(help4, PseV);
	PseVerzeichnis=help4;

	//Ende der Initialiserung der globalen Variablen

	Enable3dControls();
	/* Einstellen der L�nge der MRU-Liste */
	LoadStdProfileSettings(10);
    MRU_Flag = TRUE;

	AddDocTemplate(new CCryptDocTemplate(IDR_TEXTTYPE,
		RUNTIME_CLASS(CCryptDoc), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CMyEditView)));
	AddDocTemplate(new CCryptDocTemplate(IDR_ASCTYPE,
		RUNTIME_CLASS(CAscDoc), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CFixedView)));
	AddDocTemplate(new CCryptDocTemplate(IDR_PLOTTYPE,
		RUNTIME_CLASS(CPlotDoc), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CPlotView)));
	AddDocTemplate(new CCryptDocTemplate(IDR_HEXTYPE,
		RUNTIME_CLASS(CHexDoc), RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CHexView)));

	m_pMainWnd = new CMainFrame;
	m_MainWnd = m_pMainWnd;
	((CFrameWnd*)m_pMainWnd)->LoadFrame(IDR_MAINFRAME);
	m_pMainWnd->ShowWindow(m_nCmdShow);

	// enable file manager drag/drop and DDE Execute open
	m_pMainWnd->DragAcceptFiles();
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;// nothing s'gonna happen at application startup
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Am Anfang ist noch kein Fenster ge�ffnet, die Hilfe soll mit "Wie Sie starten ge�ffnet werden"
	//::WinHelp(0, AfxGetApp()->m_pszHelpFilePath, HELP_COMMAND, (DWORD)"JumpId(starten)");
	WinHelp(ID_WIE_SIE_STARTEN+0x10000);

	// initialize the application dependent Converter
	AppConv.SetAlphabet(TextOptions.m_alphabet.GetBuffer(257), TextOptions.m_IgnoreCase);

	SecudeStatus = SecudeLib.OpenSecudeLib(); // secude und Ticket verfuegbar ?
	if(SecudeStatus!=2) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING41570,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41500,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(NULL,pc_str,pc_str1,MB_ICONWARNING|MB_OK);
	}

	// Secude ptr fuer EC-Lib setzen
#define DoOneFn(a,b,c,d) ECSecudeLib.##c = SecudeLib.##c;
#define DoOneData(a,b) ECSecudeLib.##b = SecudeLib.##b;
	DoECAll
#undef DoOneFn
#undef DoOneData

	return TRUE;
}

void CMultiPadApp::OnAppAbout()
{
	// Aenderung Jens Liebehenschel, 18.02.00
	// Beim Doppelklick kam nicht mehr das Fenster mit den Namen der Autoren.
	// Die Nachricht wird nur bei Ansprechen �ber die Klasse CAbout behandelt.
//	CDialog(IDD_ABOUTBOX).DoModal();
	CAbout klasse;
	klasse.DoModal();
	// Ende der Aenderung
}

IMPLEMENT_DYNCREATE(CMainFrame, CMDIFrameWnd)
BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_OPTIONS_PLOT, OnOptionsPlot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT buttons[] =
{
	ID_FILE_NEW, ID_FILE_OPEN, ID_FILE_SAVE, ID_SEPARATOR,
	ID_EDIT_CUT, ID_EDIT_COPY, ID_EDIT_PASTE, ID_SEPARATOR,
	ID_FILE_PRINT, ID_APP_ABOUT
};

static UINT indicators[] =
{
	ID_SEPARATOR, ID_INDICATOR_CAPS, ID_INDICATOR_NUM, ID_INDICATOR_SCRL
};

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	((m_ToolBar.Create(this) &&
// Die folgende Zeile ist neu, dafuer mussten die beiden naechsten Zeilen raus
		m_ToolBar.LoadToolBar(IDR_MAINFRAME) &&
//		m_ToolBar.LoadBitmap(IDR_MAINFRAME) &&
//		m_ToolBar.SetButtons(buttons, sizeof(buttons)/sizeof(UINT)) &&
		m_StatusBar.Create(this) &&
		m_StatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	  ? 0 : -1);

	// Kopiert aus einem vom Application Wizard erzeugten MDI-Projekt
	// BEGINN
	// ZU ERLEDIGEN: Entfernen, wenn Sie keine QuickInfos oder variable Symbolleiste w�nschen
	m_ToolBar.SetBarStyle(m_ToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// ZU ERLEDIGEN: L�schen Sie diese drei Zeilen, wenn Sie nicht wollen, dass die Symbolleiste
	//  andockbar ist.
	m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBar);
	// ENDE

	return CMDIFrameWnd::OnCreate(lpCreateStruct);
}

IMPLEMENT_DYNCREATE(CPadDoc, CMyDocument)
BEGIN_MESSAGE_MAP(CPadDoc, CMyDocument)
	//{{AFX_MSG_MAP(CPadDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CPadDoc::Serialize(CArchive& ar)
{
	((CMyEditView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////

void CMultiPadApp::AddToRecentFileList(LPCTSTR lpszPathName)
{
    if(MRU_Flag) CWinApp::AddToRecentFileList(lpszPathName);
}

// Ein neues Dokument (CMyDocument) wird geoeffnet und die Informationen
// Window Handle des Vaterfanster, Schluessel und Type des Schluessels
// in diesem Dokuemnt gespeichert.
// Ausserdem wird dieses neue Dokument nicht in die Recent-Liste aufgenommen.
// Parameter: Dateiname der zu oeffnenden Datei
//				schluessel (vorbelegt mit "")
//				Type des Schluessels (vorbelegt mit SCHLUESSEL_LINEAR)
CMyDocument * CMultiPadApp::OpenDocumentFileNoMRU(const char *name, CString Key, int KeyType)
{
    BOOL oldflag;
    CMyDocument *doc;

    oldflag = MRU_Flag;
    MRU_Flag = FALSE;

	// Vor dem �ffnen des neuen Dokuments die WindowHandle 
	// und den View des aktiven Fensters merken.
	HWND HWND_hilf = hWndAktivesFenster; // global
	CWnd* CWnd_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive();

    doc = (CMyDocument*)OpenDocumentFile(name);

	doc->hWndVaterFenster = HWND_hilf;
	doc->CWndVaterFenster = CWnd_hilf;
	doc->csSchluessel = Key;
	doc->iSchluesselTyp = KeyType;

    MRU_Flag = oldflag;
    return doc;
}

BOOL CMultiPadApp::WriteProfileDouble( LPCTSTR lpszSection, LPCTSTR lpszEntry, double Value )
{
	char line[128];
	sprintf(line,"%g",Value);
	return WriteProfileString(lpszSection, lpszEntry, line);
}

void CMultiPadApp::OnOptionsAnalysis() 
{
	Options.DoModal();
}

void CMultiPadApp::OnWindowCloseAll() 
{
	SaveAllModified();
	CloseAllDocuments(FALSE);	
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	char line[128];
	CMyDocument *NewDoc = NULL;
	int n;
/*	static int state=0;*/

	if(nIDEvent == 42) {
		switch(theApp.OpenBGFlag) {
		case(0):
			break;
		case(1):
			break;
		case(2):
			NewDoc = theApp.OpenDocumentFileNoMRU(theApp.OpenPath, theApp.KeyOpenDocumentFile, 
												theApp.KeyTypeOpenDocumentFile);
			theApp.KeyOpenDocumentFile.Empty();
			theApp.KeyTypeOpenDocumentFile = SCHLUESSEL_INIT;
			if(NewDoc) {
				NewDoc->SetTitle(theApp.OpenTitle);
				theApp.DoWaitCursor(0);
			}
			remove(theApp.OpenPath);
			strcpy(line,theApp.OpenPath);
			n=strlen(line);
			if((n>4) && (0==strcmp(line+n-4,".plt"))) {
				line[n-4]=0;
				remove(line);
			}
			theApp.OpenBGFlag=-1;
			break;
		default:
			theApp.OpenBGFlag=-1;
			KillTimer(42);
			break;
		}
	}
	if(nIDEvent == 44) {
		theApp.fs.DoModal();
		theApp.DoWaitCursor(0);
	}
	
	CMDIFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnOptionsPlot() 
{
	int t1,t2;

	t1 = theApp.PlotOptions.m_bar_width;
	t2 = theApp.PlotOptions.m_curve;
	if(theApp.PlotOptions.DoModal() != IDOK) {
		theApp.PlotOptions.m_bar_width = t1;
		theApp.PlotOptions.m_curve = t2;
	}
}

void CMultiPadApp::ThreadOpenDocumentFileNoMRU(const char * name, const char * title, char *Key, int KeyType)
{
	int i;

	for(i=0;((i<50)&&(OpenBGFlag==2));i++) Sleep(100);
	OpenBGFlag=2;
	strncpy(OpenTitle, title, sizeof(OpenTitle)-1);
	OpenTitle[sizeof(OpenTitle)-1]=0;
	strncpy(theApp.OpenPath, name, sizeof(OpenPath)-1);
	OpenPath[sizeof(OpenPath)-1]=0;
	KeyOpenDocumentFile = Key;
	KeyTypeOpenDocumentFile = KeyType;
	m_MainWnd->SendMessage(WM_TIMER,42,NULL);
}

void CMultiPadApp::OnOpttext() 
{
	TextOptions.DoModal();
}



int CMultiPadApp::ExitInstance()
{
	if(CaPseDatei) free(CaPseDatei);
	if(CaPseVerzeichnis) free(CaPseVerzeichnis);
	if(Pfad) free(Pfad);
	if(PseVerzeichnis) free(PseVerzeichnis);
//	m_pRecentFileList->WriteList();

	return CWinApp::ExitInstance();
}

void CMultiPadApp::OnUpdateNeedSecudeTicket(CCmdUI* pCmdUI) 
{
    if(theApp.SecudeStatus == 2) pCmdUI->Enable(TRUE);
	else pCmdUI->Enable(FALSE);	
}

void CMultiPadApp::OnShowKeys() 
{
	// UpdateContent();
	CDlgAsymKeys TocDialog;
	TocDialog.DoModal();
}

void CMultiPadApp::OnKeyGen() 
{
	KeyGen();
}