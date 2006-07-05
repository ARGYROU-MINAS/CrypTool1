// MFC-ZahlenHaiDlg.cpp : Implementierungsdatei
// zahl.cpp

#include "stdafx.h"
#include "WBButton.h"
#include "MFC-ZahlenHai.h"
#include "MFC-ZahlenHaiDlg.h"
#include "math.h"

#include <iostream>
#include <fstream>

#include <stdlib.h>
#include ".\mfc-zahlenhaidlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CString bestWay;

using namespace std;
// CAboutDlg-Dialogfeld f�r Anwendungsbefehl 'Info'

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
// Dialogfelddaten
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterst�tzung
	
// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};

#define NUM_COLUMNS 6
struct listenHeader
{
	UINT columnTitle;
	int columnFormat;
	int columnWidth;
};

listenHeader columnheader[NUM_COLUMNS]={
	{IDS_ZUG,LVCFMT_LEFT,39},
	{IDS_SPIELER,LVCFMT_RIGHT,88},
	{IDS_HAI,LVCFMT_RIGHT,189},
	{IDS_SPIELER_PUNKTE,LVCFMT_RIGHT,90},
	{IDS_HAI_PUNKTE,LVCFMT_RIGHT,90},
	{IDS_REST,LVCFMT_RIGHT,56}
};

//Array enh�lt die bereits berechneten maximalen Punktezahlen 
//Das muss noch weg. Daf�r soll die Anzahl der Zelen aus der Spieldaten.txt herausgelesen werden
int maxPossiblePoints[] = {0,2,3,7,9,15,17,21,30,40,44,50,52,66,81,89,93,111,113,124,144,166};
const int yAchse=sizeof(maxPossiblePoints)/sizeof(int);
const int xAchse=4;
CString Optimal[yAchse][xAchse];
CString optionenSetting="";
CString toolTipSetting="";
CString exePath = GetCommandLine();
int showWinner=0;
int checkList=0;


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// CMFCZahlenHaiDlg Dialogfeld

CMFCZahlenHaiDlg::CMFCZahlenHaiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCZahlenHaiDlg::IDD, pParent)
	, pointsPlayer(0)
	, pointsComputer(0)
	, sumOfAllNumbers(0)
	, startInfo(_T(""))
	//, gameIdea(_T(""))
{
	numbers = 20;
}

void CMFCZahlenHaiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, numbers);
	DDX_Text(pDX, IDC_STATIC_SUM, sumText);
	//DDX_Text(pDX, IDC_RICHEDIT21, gameIdea);
	//DDX_Text(pDX, IDC_STATIC_DISCLAIMER, disclaimerText);
	//DDX_Text(pDX, IDC_STATIC_INFO, infoText);
	DDX_Text(pDX, IDC_START_INFO, startInfo);

	DDX_Control(pDX, IDC_LIST2, ListControl);
	DDX_Control(pDX, IDC_TAB1, tabControl);

	DDX_Control(pDX, IDC_STATIC_HAI_LISTE, haiListe);

	DDX_Control(pDX, IDC_LEDTEXT, m_LedText);
	//DDX_Control(pDX, IDC_LED_WINNER, m_LedWinner);
	DDX_Control(pDX, ID_BUTTON_RULES,Spielregeln);
	DDX_Control(pDX, IDC_BUTTON_OPTION,Spieloptionen);
	//DDX_Control(pDX, IDC_RICHEDIT21, richEditIdea);

	DDX_Control(pDX, IDC_BUTTON01, arrayButtonControl[0]);
	DDX_Control(pDX, IDC_BUTTON02, arrayButtonControl[1]);
	DDX_Control(pDX, IDC_BUTTON03, arrayButtonControl[2]);
	DDX_Control(pDX, IDC_BUTTON04, arrayButtonControl[3]);
	DDX_Control(pDX, IDC_BUTTON05, arrayButtonControl[4]);
	DDX_Control(pDX, IDC_BUTTON06, arrayButtonControl[5]);
	DDX_Control(pDX, IDC_BUTTON07, arrayButtonControl[6]);
	DDX_Control(pDX, IDC_BUTTON08, arrayButtonControl[7]);
	DDX_Control(pDX, IDC_BUTTON09, arrayButtonControl[8]);
	DDX_Control(pDX, IDC_BUTTON10, arrayButtonControl[9]);
	DDX_Control(pDX, IDC_BUTTON11, arrayButtonControl[10]);
	DDX_Control(pDX, IDC_BUTTON12, arrayButtonControl[11]);
	DDX_Control(pDX, IDC_BUTTON13, arrayButtonControl[12]);
	DDX_Control(pDX, IDC_BUTTON14, arrayButtonControl[13]);
	DDX_Control(pDX, IDC_BUTTON15, arrayButtonControl[14]);
	DDX_Control(pDX, IDC_BUTTON16, arrayButtonControl[15]);
	DDX_Control(pDX, IDC_BUTTON17, arrayButtonControl[16]);
	DDX_Control(pDX, IDC_BUTTON18, arrayButtonControl[17]);
	DDX_Control(pDX, IDC_BUTTON19, arrayButtonControl[18]);
	DDX_Control(pDX, IDC_BUTTON20, arrayButtonControl[19]);
	DDX_Control(pDX, IDC_BUTTON21, arrayButtonControl[20]);
	DDX_Control(pDX, IDC_BUTTON22, arrayButtonControl[21]);
	DDX_Control(pDX, IDC_BUTTON23, arrayButtonControl[22]);
	DDX_Control(pDX, IDC_BUTTON24, arrayButtonControl[23]);
	DDX_Control(pDX, IDC_BUTTON25, arrayButtonControl[24]);
	DDX_Control(pDX, IDC_BUTTON26, arrayButtonControl[25]);
	DDX_Control(pDX, IDC_BUTTON27, arrayButtonControl[26]);
	DDX_Control(pDX, IDC_BUTTON28, arrayButtonControl[27]);
	DDX_Control(pDX, IDC_BUTTON29, arrayButtonControl[28]);
	DDX_Control(pDX, IDC_BUTTON30, arrayButtonControl[29]);
}

BEGIN_MESSAGE_MAP(CMFCZahlenHaiDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON01, IDC_BUTTON30, OnBnClickedButton)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnTcnSelchangeTab1)
	
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(ID_BUTTON_END, OnBnClickedButtonEnd)
	ON_BN_CLICKED(IDC_BUTTON_STARTNEW, OnBnClickedButtonStartnew)
	ON_BN_CLICKED(ID_BUTTON_RULES, OnBnClickedButtonRules)
	ON_BN_CLICKED(IDC_BUTTON_REST, OnBnClickedButtonRest)
	ON_BN_CLICKED(IDC_BUTTON_OPTION, OnBnClickedButtonOption)
END_MESSAGE_MAP()

// CMFCZahlenHaiDlg Meldungshandler



BOOL CMFCZahlenHaiDlg::OnInitDialog()
{
	//Default Language des Betriebssystems herausfinden
	readGameData();
	//disclaimerText.Format(IDS_DISCLAIMER_TEXT);
	//infoText.Format(IDS_INFO_TEXT);
	startInfo.Format(IDS_START_INFO);
	//gameIdea.Format(IDS_GAME_IDEA);

	optionen.controlUpperLimit=2;

	int regUpperLimit=readRegistry();

	//TTS_BALLON is ein Test
	toolTip.Create(this, TTS_NOPREFIX | TTS_BALLOON | TTS_ALWAYSTIP);
	toolTipNumbers.Create(this,TTS_NOPREFIX | TTS_BALLOON | TTS_ALWAYSTIP);

	//Anzeige Dauer
	toolTip.SendMessage(TTM_SETDELAYTIME, TTDT_AUTOPOP, SHRT_MAX);
	toolTipNumbers.SendMessage(TTM_SETDELAYTIME, TTDT_AUTOPOP, SHRT_MAX);

	//Breite der ToolTips wird festgelegt-> sieht dann wie Zeilenumbruch aus
	toolTip.SetMaxTipWidth(1000);
	toolTipNumbers.SetMaxTipWidth(1000);
	
	//Farbe f�r den Text und den Hintergrund der Tool Tipps
	toolTip.SetTipTextColor(RGB(0,0,0));
	toolTip.SetTipBkColor(RGB(213,227,241));
	toolTipNumbers.SetTipTextColor(RGB(0,0,0));
	toolTipNumbers.SetTipBkColor(RGB(213,227,241));
	CDialog::OnInitDialog();
	
	//Formatierung des Textes im RichEdit Feld
	/*CHARFORMAT cf;
	cf.dwMask = CFM_STRIKEOUT|CFM_BOLD;
	cf.dwEffects = CFE_BOLD;
	CString language="";
	language.LoadString(IDS_SPRACHE);
	if(language=="DE")
	{
        richEditIdea.SetSel(0,12);
		richEditIdea.SetWordCharFormat(cf);
		richEditIdea.SetSel(54,65);
		richEditIdea.SetWordCharFormat(cf);
	}
	else
	{
		richEditIdea.SetSel(0,18);
		richEditIdea.SetWordCharFormat(cf);
		richEditIdea.SetSel(54,65);
		richEditIdea.SetWordCharFormat(cf);
	}*/
	// Hinzuf�gen des Men�befehls "Info..." zum Systemmen�.
	// IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
	    CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// Symbol f�r dieses Dialogfeld festlegen. Wird automatisch erledigt
	// wenn das Hauptfenster der Anwendung kein Dialogfeld ist
	SetIcon(m_hIcon, TRUE);			// Gro�es Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	
	//Beim Start des Spiels sind bereits 20 Buttons aktiv, so dass der Spieler direkt starten kann
	hai.upperLimit=regUpperLimit;
	numbers=regUpperLimit;
	hai.init(hai.getUpperLimit());

	//Die Schriftgr��e der Zahlen auf den Muscheln wird gesetzt
	//150 = Schriftgr��e (wie bei Word) mal 10 - eine gr��ere Schrift passt nicht auf die Muscheln
	CClientDC dc(this);
	fontButton.CreatePointFont(145, "Arial", &dc);

	//LOGFONT logFont;
	//logFont.lfUnderline = TRUE;
	//logFont.lfHeight = 13;
	//logFont.lfWeight = FW_BOLD; // Auf Fettdruck umstellen
	
	CString numberShark="";
	numberShark.LoadString(IDS_NUMBER_SHARK);
	CString titleVersion="";
	titleVersion.LoadString(IDS_TITLE_VERSION);
	this->SetWindowText(numberShark+titleVersion);
	
	updatePoints();
	updateButtons();
	
	updateTab();
	updateToolTips();
	 
	CSetList(-1);
	ListControl.ShowWindow(0);

	haiListe.ShowWindow(1);
	((CEdit*)GetDlgItem(IDC_STATIC_LISTE))->ShowWindow(false);
	
	//�nderung der LED-Anzeige: Hindergrundfarbe, Farbe der Zeichen
	//DigiStatic.cpp m_BackColor
	//m_LedWinner.SetBkColor(RGB(0,0,0));
	//m_LedText.SetColor(RGB(200,220,245),RGB(255,255,0));
	//m_LedWinner.SetColor(RGB(200,220,245),RGB(255,255,0));

	DWORD dwExStyle= tabControl.GetExtendedStyle();
	tabControl.SetExtendedStyle(dwExStyle | TCS_EX_FLATSEPARATORS);

	((CEdit*)GetDlgItem(IDC_BUTTON_REST))->EnableWindow(false);
	
	/*
	Spielregeln.LoadBitmaps(IDB_BITMAP2,5,0,0,0,0);
	Spielregeln.SetFontColor(RGB(133,75,130));
	Spieloptionen.LoadBitmaps(IDB_BITMAP3,5,0,0,0,0);
	Spieloptionen.SetFontColor(RGB(255,255,255));
    */

	return TRUE;  // Geben Sie TRUE zur�ck, au�er ein Steuerelement soll den Fokus erhalten
}
BOOL CMFCZahlenHaiDlg::PreTranslateMessage(MSG *pMsg)
{
	if(pMsg->message == WM_KEYDOWN)
	{
		//Abfangen des Drucks auf die Enter Taste
		if(pMsg->wParam == 13)
		{
			////Wenn Enter gedr�ckt wurde
			enterWasPressed();
			return true;
		}
		//Pfeiltasten nach Oben und Unten
		if(pMsg->wParam ==38 || pMsg->wParam==40)
		{
			arrowKeyPressed(pMsg->wParam);
			return true;
		}
	}

   if(IsWindow(toolTip.m_hWnd)) //existiert ?
   {
      toolTip.RelayEvent(pMsg);
	  toolTipNumbers.RelayEvent(pMsg);
   }
  
   return CDialog::PreTranslateMessage(pMsg);
}
void CMFCZahlenHaiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// Wenn Sie dem Dialogfeld eine Schaltfl�che "Minimieren" hinzuf�gen, ben�tigen Sie 
//  den nachstehenden Code, um das Symbol zu zeichnen. F�r MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgef�hrt.

void CMFCZahlenHaiDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Ger�tekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}	
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, w�hrend der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CMFCZahlenHaiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Erstellung der List in welcher die Punkte von Spieler und Computer eingetragen werden
void CMFCZahlenHaiDlg::CSetList(int playerchoice)
{
	int currentRound = hai.getCurrentRound();
	int player = playerchoice;
	int rest=0;
	CString title="";
	
	///////////////////////////////////////////////////////////////////////////////////
	if(!currentRound)
	{
	
		int i;
		int bufferLength=1;
		LV_COLUMN lvc;

		lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
		for(i = 0; i<6; i++)
		{
			lvc.iSubItem = i;
			title.LoadString(columnheader[i].columnTitle);
			lvc.pszText = title.GetBuffer(bufferLength);
			lvc.cx = columnheader[i].columnWidth;
			lvc.fmt = columnheader[i].columnFormat;
			ListControl.InsertColumn(i,&lvc);
			title.ReleaseBuffer();
		}
		///////////////////////SET UP THE MULTILINE HEADER CONTROL
		font.CreatePointFont(190,"MS Serif");

		CHeaderCtrl* pHeader = NULL;
		pHeader=ListControl.GetHeaderCtrl();

		if(pHeader==NULL)
			return;
	
		VERIFY(header.SubclassWindow(pHeader->m_hWnd));	

		//A BIGGER FONT MAKES THE CONTROL BIGGER
		header.SetFont(&font);
	
		HDITEM hdItem;

		hdItem.mask = HDI_FORMAT;
	
		for(i=0; i<header.GetItemCount(); i++)
		{
			header.GetItem(i,&hdItem);

			hdItem.fmt|= HDF_OWNERDRAW;
		
			header.SetItem(i,&hdItem);
		}
	}


	/////////////////////////////////////////////////////////////////////////////////////

	//Der Spieler kann einzelne Zeilen in der Liste ausw�hlen
	ListControl.SetExtendedStyle(ListControl.GetExtendedStyle()|LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
	char buffer[1000];
	CString stringFinalPointsComputer="";
	CString stringFinalPointsPlayer="";
	CString stringRounds="";
	CString stringNumberscomputer="";
	CString stringNumbersPlayer="";
	CString stringUsableNumbersLeft="";
	CString primeInfo="";
	CString test="";

	primeInfo.LoadString(IDS_PRIME_INFO);
	
	stringRounds=itoa(currentRound, buffer, 10);
	stringFinalPointsPlayer=itoa(hai.getPointsPlayer(), buffer, 10);
	stringFinalPointsComputer=itoa(hai.getPointsComputer(), buffer, 10);
	
	if(hai.getComputerNumbers().n == 0 || rest>0)
	{
		stringNumberscomputer=itoa(player, buffer,10);
		if(isPrime(player))
				stringNumberscomputer+=primeInfo;
		stringNumbersPlayer="0";
	}
	
	stringNumbersPlayer=itoa(player, buffer, 10);
	if(isPrime(player))
		stringNumbersPlayer+=primeInfo;
		
	for(int i=0; i<hai.getComputerNumbers().n && rest==0; i++)
	{
		if(i == 0) 
		{
			stringNumberscomputer+=itoa(hai.getComputerNumbers().pNumbers[i],buffer,10);
			if(isPrime(hai.getComputerNumbers().pNumbers[i]))
				stringNumberscomputer+=primeInfo;
		}
		else
		{
			stringNumberscomputer+=", ";		
			stringNumberscomputer+=itoa(hai.getComputerNumbers().pNumbers[i],buffer,10);
			if(isPrime(hai.getComputerNumbers().pNumbers[i]))
				stringNumberscomputer+=primeInfo;
		}
	}
	
	stringUsableNumbersLeft=itoa(hai.usableNumbersLeft(),buffer,10);
	//Die Zahlen, die jede Runde von dem Spieler und dem Computer gezogen werden, werden in die Liste eingetragen
    ListControl.InsertItem(currentRound-1, stringRounds);
	if(!hai.getComputerNumbers().n == 0 && rest==0)
	    ListControl.SetItemText(currentRound-1, 1, stringNumbersPlayer);
	else
	    ListControl.SetItemText(currentRound-1, 1,"0");
	ListControl.SetItemText(currentRound-1, 2, stringNumberscomputer);
	
	//Die Punktezahlen von Spieler und Computer werden in die Liste geschrieben
	ListControl.SetItemText(currentRound-1, 3, stringFinalPointsPlayer);
	ListControl.SetItemText(currentRound-1, 4, stringFinalPointsComputer);
	ListControl.SetItemText(currentRound-1, 5, stringUsableNumbersLeft);

	//Immer die letzte eingetragene Zeile ist sichtbar
	int nCount = ListControl.GetItemCount();
	if (nCount > 0)
	   ListControl.EnsureVisible(nCount-1, FALSE);
}

//Die Warnung "warning C4100: 'pNMHD R': Unreferenzierter formaler Parameter " wird f�r OnTcnSelchange1 ausgeschalten
#pragma warning(push)
#pragma warning( disable : 4100 )
void CMFCZahlenHaiDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	//Wenn ein neuer Reiter ausgew�hlt wird, werden auch die Buttons auf diesem Reiter aktualisiert
	updateButtons();
	//Aktualisierung(selektierbar, nicht selektierbar) der Buttons f�r das aktuelle Tab
	*pResult = 0;
}
#pragma warning(pop)

//Aktualisierung der Buttons f�r die Eingabe der gew�nschten Zahlen
void CMFCZahlenHaiDlg::updateButtons()
{
	int upperLimit = hai.getUpperLimit();
	optionen.optionenUpperLimit=upperLimit;
	int *numbersTemp = hai.getNumbers();
	
	bool found;
	CString stringBeschriftung="";
	CString stringNumber="";
	
	char Buffer[100];

	for(int i=0; i<MAX_ZAHLENHAI_BUTTON; i++)
	{
		//Die Nummer des ausgew�hlten Reiters wird zur�ckgegeben
		int tab = tabControl.GetCurSel();
		int counter=0;
		if(tab < 0)
			tab=0;
		int number = tab * MAX_ZAHLENHAI_BUTTON + i + 1;
        //Alle Buttons darstellen bzw. ausblenden
		
		arrayButtonControl[i].ShowWindow(number <= upperLimit);
		
		if(number <= upperLimit)
		{
			//Alle Buttons sollen ausw�hlbar sein.Alle auf PLAYER oder COMPUTER gesetzten sollen ausgegraut sein
			arrayButtonControl[i].EnableWindow(numbersTemp[number] == FREE);
			arrayButtonControl[i].LoadBitmaps(IDB_BITMAP1,5,0,0,0,0);
//			
			arrayButtonControl[i].SetTextFont(fontButton);
            arrayButtonControl[i].SetFontColor(RGB(255,255,0));
					
			stringBeschriftung=itoa(number, Buffer, 10);
		    arrayButtonControl[i].SetWindowText(stringBeschriftung);

			//Durch diese Abfrage werden die ToolTips nur geschrieben wenn sie auch aktiviert sind
			if(optionen.showToolTips)
			{
				CString factor;
				CString isFactor;

				int j;
				//number ist eine Zahl aus den zur Verf�gung stehenden Zahlen
				//In der Schleife werden alle noch vorhandenen Teiler einer Zahl herausgefunden
				for(j=1; j <= number/2+1; j++)
				{	
					//wenn die Zahle noch nicht gew�hlt wurde
					if(numbersTemp[j] == FREE)
					{	
						//wenn j ein Teiler von number ist
						if((!(number % j)) && (number != j))
						{
							stringNumber=itoa(j, Buffer, 10);
							stringNumber+=", ";
							factor += stringNumber;
                    	}
					}
				}
				
				if(number<upperLimit/2+1)
				{
                    for(j=number+1;j<=upperLimit  && counter<=10; j++)
					{
						if(numbersTemp[number]==FREE && numbersTemp[j]==FREE)
						{
							if(!(j%number))
							{
								counter++;
								stringNumber=itoa(j,Buffer,10);
								stringNumber+=", ";
								
								if(counter==10)
								{
									stringNumber.Delete(stringNumber.GetLength()-2,1);
									stringNumber+="....";
								}
								if(counter<=10)
                                    isFactor+=stringNumber;
							}
						}
					}
				}
				//Das letzte Zeichen in dem CString factor, ein Komma, wird gel�scht
				factor.Delete(factor.GetLength()-2,1);
				isFactor.Delete(isFactor.GetLength()-2,1);
				//Wenn keine Teiler in die ToolTips geschrieben werden, soll "Keine Teiler mehr vorhanden!" in dem String factor stehen
				if (factor=="")
				{
					CString toolTipNumber="";
					toolTipNumber.Format(IDS_TOOL_TIP_NUMBER,stringBeschriftung);
					CString toolTipIsFactor="";
					if(isFactor=="")
						isFactor.LoadString(IDS_ISNOT_FACTOR);
					toolTipIsFactor.Format(IDS_TOOL_TIP_ISFACTOR, isFactor);
					factor.Format(IDS_TOOL_TIP_TEXT_NO_FACTORS,toolTipNumber, toolTipIsFactor);
				}
				
				else
				{
					//wenn Teiler gefunden wurde beginnen die ToolTips mit "�brige Teiler: "
					CString toolTipNumber="";
					toolTipNumber.Format(IDS_TOOL_TIP_NUMBER,stringBeschriftung);
					CString toolTipIsFactor="";
					if(isFactor=="")
					{
						isFactor.LoadString(IDS_ISNOT_FACTOR);
						toolTipIsFactor=isFactor;
					}
					else
                        toolTipIsFactor.Format(IDS_TOOL_TIP_ISFACTOR, isFactor);

					CString factortitle;
					factortitle.Format(IDS_TOOL_TIP_TEXT,toolTipNumber,factor,toolTipIsFactor);
					factor=factortitle;
					
				}
				//Die ToolTips werden zu jedem Button hinzugef�gt
				toolTipNumbers.AddTool(&(arrayButtonControl[i]), factor);
				toolTipNumbers.Activate(true);
			}
			else
			{
				toolTipNumbers.Activate(false);
			}
		}
	}
	
	//Immer wenn eine nicht teilbare Zahl im Zahlen Block vorhanden ist erscheint der Button
	//"Zahlen ohne Teiler f�r den Zahlenhai"
	
	
	for(int i= upperLimit; i > upperLimit/2; i--)
	{
		found=false;
		
		for(int j=1; j<=i/2 && found==false && numbersTemp[i]==FREE; j++)
		{
			if(numbersTemp[j]==FREE)
			{
                if(i%j)
					found=false;
				else
					found=true;
			}
		}
		if(found==false && numbersTemp[i]==FREE)
		{
			((CEdit*)GetDlgItem(IDC_BUTTON_REST))->EnableWindow(true);
		}
	}

	//In dem ToolTip des Haifutter Buttons werden die Zahlen angezeigt welche sich der Hai nehmen w�rde.
	CString bla="";
	found=false;
	int counter=0;
	for(int i= upperLimit; i > upperLimit/2; i--)
	{
		found=false;
		for(int j=1; j<=i/2 && found==false && numbersTemp[i]==FREE; j++)
		{
			if(numbersTemp[j]==FREE)
			{
                if(!(i%j))
					found = true;
				else
					found = false;
			}
		}
		if(numbersTemp[i]==FREE && found==false)
		{
			counter++;
			if(counter<=10)
			{
                bla+=itoa(i,Buffer,10);
				bla+=", ";
			}
			if(counter==10)
			{
				bla.Delete(bla.GetLength()-2,1);
				bla+="....";
			}

		}
		
	}
	CString tipText;
	tipText.Format(IDS_BUTTON_REST, bla);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_REST), tipText);
	
	Invalidate(false);
	//Auswertung der Spielergebnisse wenn das Spiel beendet ist
	//Der Benutzer hat die M�glichkeit die Spielz�ge in eine Zusammenfassung zu schreiben
	
	if(showWinner==0)
	{
        if(winner())
		{
			writeLogFile();
		}
		else
		{
			//Bei jeder Wahl wird der Focus auf den aktuell aktiven Reiter gesetzt
			tabControl.SetFocus();
		}
	}

	if(optionen.playername!="")
	{
		CString sharkAgainst="";
		sharkAgainst.LoadString(IDS_SHARK_AGAINST);
		CString numberShark="";
		numberShark.LoadString(IDS_NUMBER_SHARK);
		CString titleVersion="";
		titleVersion.LoadString(IDS_TITLE_VERSION);
		this->SetWindowText(numberShark+sharkAgainst+optionen.playername+titleVersion);
	}
}

//Anzeiger der Punktest�nde von Spieler und Hai werden aktualisiert
void CMFCZahlenHaiDlg::updatePoints()
{
	int upperLimit=hai.getUpperLimit();
	pointsPlayer = hai.getPointsPlayer();
	pointsComputer = hai.getPointsComputer();

	char buffer[30];
	CString strPointsPlayer="";
	strPointsPlayer=itoa(pointsPlayer,buffer,10);
	CString strPointsComputer="";
	strPointsComputer=itoa(pointsComputer,buffer,10);
	m_LedText.SetText(strPointsPlayer + ":" + strPointsComputer);

	//CString bla="";
    //bla=hai.setSeperators(upperLimit+((upperLimit*(upperLimit-1))/2));

	sumText.Format(IDS_SUM_TEXT, upperLimit, upperLimit+((upperLimit*(upperLimit-1))/2));
	usablenumbersleft = hai.usableNumbersLeft();

	UpdateData(false);
}

//Aktualisierung der TabControl
void CMFCZahlenHaiDlg::updateTab()
{
	tabControl.DeleteAllItems();
	int upperLimit = hai.getUpperLimit();
	int tab = ((upperLimit + (MAX_ZAHLENHAI_BUTTON - 1))/MAX_ZAHLENHAI_BUTTON);
	char Buffer[10];
	CString stringTabCount="";

	for(int i=0; i<tab; i++)
	{
		int a = 1 + (i * MAX_ZAHLENHAI_BUTTON);
		int b = a + MAX_ZAHLENHAI_BUTTON - 1;
		if(b > upperLimit)
			b=upperLimit;
		//Beschriftung der Reiter
		stringTabCount=itoa(a,Buffer,10);
		stringTabCount+="-";
		stringTabCount+=itoa(b,Buffer,10);
		tabControl.InsertItem(i, stringTabCount);
	}
	
}
//ToolTips f�r die einzelnen Buttons.
void CMFCZahlenHaiDlg::updateToolTips()
{
	CString TipText;
	//mit CMsg wird das Laden von Strings aus der String Table und die Weiterverwendung vereinfacht
	TipText.LoadString(IDS_BUTTON_STARTNEW);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_STARTNEW), TipText);
	TipText.LoadString(IDS_BUTTON_END);
	toolTip.AddTool(GetDlgItem(ID_BUTTON_END), TipText);
	TipText.LoadString(IDS_BUTTON_RULES);
	toolTip.AddTool(GetDlgItem(ID_BUTTON_RULES), TipText);
	TipText.LoadString(IDS_BUTTON_OK);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_OK), TipText);
	TipText.LoadString(IDS_BUTTON_OPTION);
	toolTip.AddTool(GetDlgItem(IDC_BUTTON_OPTION), TipText);
	//TipText.LoadString(IDS_BUTTON_REST);
	  
	toolTip.Activate(true);

	//Andere Variante
	//toolTip.AddTool(GetDlgItem(IDC_BUTTON_STARTNEW), CMsg(IDS_BUTTON_STARTNEW));
}
//Wenn der Spieler der Knopf "Neues Spiel" dr�ckt werden die Punkteanzeigen, sowie die
//angezeigten Buttons gel�scht
void CMFCZahlenHaiDlg::OnBnClickedButtonStartnew()
{
	// START NEW
	// Wenn der Spieler der Button "Neues Spiel" dr�ckt werden alle Punktest�nde gel�scht und die Einstellungen vom vorhergehenden Spiel bleiben erhalten
	showWinner=0;
	checkList=0;
	hai.init(hai.getUpperLimit());
	
	updatePoints();
	updateButtons();
	
	updateToolTips();
	// Liste l�schen bei Klick auf "Neues Spiel"
	ListControl.DeleteAllItems();  
					
	//Der Schreibschutz des Eingabefeldes f�r die Obergrenze wird bei Neustart aufgehoben
	//m_LedWinner.DeleteTempMap();
	//m_LedWinner.ShowWindow(0);
	
	ListControl.ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_STATIC_LISTE))->ShowWindow(0);
	haiListe.ShowWindow(1);

	((CEdit*)GetDlgItem(IDC_START_INFO))->ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_STATIC_SUM))->ShowWindow(1);
	((CEdit*)GetDlgItem(IDC_STATIC))->ShowWindow(1);
	((CEdit*)GetDlgItem(IDC_EDIT1))->ShowWindow(1);
	((CEdit*)GetDlgItem(IDC_BUTTON_OK))->ShowWindow(1);
	((CEdit*)GetDlgItem(IDC_STATIC_EINSTELLUNGEN))->ShowWindow(1);
	//((CEdit*)GetDlgItem(IDC_RICHEDIT21))->ShowWindow(1);

	((CEdit*)GetDlgItem(IDC_EDIT1))->SetReadOnly(false);
	((CEdit*)GetDlgItem(IDC_BUTTON_OK))->EnableWindow(true);
	((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(true);
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetFocus();
	((CEdit*)GetDlgItem(IDC_BUTTON_REST))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_STATIC_SUM))->ShowWindow(false);

    m_LedText.ShowWindow(0);
}

//Wenn der Spieler den Knopf "Ende" dr�ckt beendet sich das Programm
void CMFCZahlenHaiDlg::OnBnClickedButtonEnd()
{
	// flomar
/*	char str[1000];
	memset(str, 0, 1000);
	itoa(globalPoints, str, 10);
	CString c = "Punkte: ";
	c += CString(str);
	MessageBox(c, "Punkte", MB_ICONINFORMATION);
	return;
*/

	writeRegistry();

	// ENDE
	OnCancel();
}

//Wenn der Spieler auf den Knopf "Regeln" dr�ckt erscheint ein extra Fenster welches kurz die Regeln erkl�rt
void CMFCZahlenHaiDlg::OnBnClickedButtonRules()
{
	rules.DoModal();
}
//Wenn der OK Button gedr�ckt wird
void CMFCZahlenHaiDlg::OnBnClickedButtonOk()
{
	//Daten werden aktualisiert
	UpdateData(true);
	((CEdit*)GetDlgItem(IDC_STATIC_SUM))->ShowWindow(true);
	//Kontrolle ob die Zahl, die der Spieler eingegeben hat, nicht kleiner als 0 und nicht gr��er als 9999 ist.
	//L�sst sich beliebig erweitern. MAX_ZAHLENHAI_NUMBERS in der MFC-ZahlenHaiDlg.h muss nur ge�ndert werden
	if(numbers < 1 || numbers > MAX_ZAHLENHAI_NUMBERS)
	{
		CString input;
		input.Format(IDS_INVALID_INPUT, MAX_ZAHLENHAI_NUMBERS);
		CString headline;
		headline.LoadString(IDS_VALID_INPUT_HEADLINE);
		MessageBox(input,headline ,MB_ICONWARNING);
		return;
	}

	//Speicher f�r numbers wird alokiert und pointsplayer, sowie pointscomputer werden 0 gesetzt
	hai.init(numbers);
	
	//Anzeige der Buttons, sowie der Punktest�nde werden zur�ckgesetzt
	updateTab();
	updatePoints();
	updateButtons();
	updateToolTips();

	((CEdit*)GetDlgItem(IDC_START_INFO))->ShowWindow(1);
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetReadOnly(true);	
	((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_BUTTON_OK))->EnableWindow(false);
}

//Weiter Spieloptionen
void CMFCZahlenHaiDlg::OnBnClickedButtonOption()
{
	if(hai.getUpperLimit() <= sizeof(maxPossiblePoints)/sizeof(int))
		optionen.controlUpperLimit=0;
	else
		optionen.controlUpperLimit=1;
	optionen.showButton=1;
	optionen.DoModal();

	//Wenn der Optionen Dialog �ber den Button "Start" verlassen wird, wird der Wert exitOptions auf 1 gesetzt, so dass
	//die maximale Punktezahl berechnet wird. Wenn man den Dialog normla verl�sst ist dieser Wert 0
	if(optionen.exitOptions==1)
		addOnInformation();

	updatePoints();
	updateButtons();
	
	updateToolTips();
	toolTip.Activate(TRUE);
	((CEdit*)GetDlgItem(IDC_BUTTON_OPTION))->SetFocus();
}

// Button "Schnelles Ende". Der Button erscheint wenn nur noch nichtteilbare Zahlen vorhanden sind, der Spieler also keine Punkte mehr 
// bekommen k�nnte. Wenn der Button gedr�ckt wird erh�lt der Computer die restlichen Zahlen.
// aus der Funktion hai.assignFreeNumbersToComputer() aus EvoZahlenHai muss der Wert i irgendwie mit CSetList in Verbindung gebracht werden
void CMFCZahlenHaiDlg::OnBnClickedButtonRest()
{
	updatePoints();
	updateButtons();
	
	bool found=false;
	int *numbersTemp = hai.getNumbers();
	int upperLimit=hai.getUpperLimit();
		
	for(int i= upperLimit; i > upperLimit/2; i--)
	{
		found=false;
		for(int j=1; j<=i/2 && found==false && numbersTemp[i]==FREE; j++)
		{
			if(numbersTemp[j]==FREE)
			{
                if(!(i%j))
					found = true;
				else
					found = false;
			}
		}
		if(numbersTemp[i]==FREE && found==false)
		{
			hai.startRound(i);
			CSetList(i);
		}
		
	}
	
	//Diese Funktion soll hinter der Tastenkombination Strg+Shift+L liegen.
	//Der Zahlenhai soll alle anderen Zahlen bekommen-> allerdings nur als Test
	/*
	for(int i=2; i<=upperLimit; i++)
	{
		if(numbersTemp[i]==FREE)
			numbersTemp[i]==COMPUTER;

		hai.startRound(i);
		CSetList(i);
	}
	*/
	updatePoints();
	updateButtons();
	
	
	((CEdit*)GetDlgItem(IDC_BUTTON_REST))->EnableWindow(false);
}
//Bei jeder Wahl des Spieler beginnt eine neue Runde
//Der Wert der Buttons wird durch die Beschriftung und das aktuell aktive Tab bestimmt
void CMFCZahlenHaiDlg::OnBnClickedButton(unsigned int nID)
{
	if(!checkList)
	{
        //((CEdit*)GetDlgItem(IDC_RICHEDIT21))->ShowWindow(0);
		ListControl.ShowWindow(1);
		checkList=1;
		haiListe.ShowWindow(0);
		((CEdit*)GetDlgItem(IDC_STATIC_LISTE))->ShowWindow(1);
		((CEdit*)GetDlgItem(IDC_BUTTON1))->EnableWindow(false);
	    ((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(false);
	    //Wird sowieso erst eingeblendet, wenn mit dem Spiel gestartet wird, und dann
		//soll ja schon der LED Text erscheinen
		//((CEdit*)GetDlgItem(IDC_STATIC_SUM))->ShowWindow(true);
	    ((CEdit*)GetDlgItem(IDC_START_INFO))->ShowWindow(false);

		((CEdit*)GetDlgItem(IDC_BUTTON_OK))->ShowWindow(false);
		((CEdit*)GetDlgItem(IDC_EDIT1))->ShowWindow(false);
		((CEdit*)GetDlgItem(IDC_STATIC))->ShowWindow(false);
		((CEdit*)GetDlgItem(IDC_STATIC_EINSTELLUNGEN))->ShowWindow(false);
        m_LedText.ShowWindow(1);
	}
			
	int nButton = nID + 1 - IDC_BUTTON01;
	ASSERT(nButton >=1 && nButton <= MAX_ZAHLENHAI_BUTTON);
	ASSERT(IDC_BUTTON30 - IDC_BUTTON01 == 29);
	    
	nButton = nButton + tabControl.GetCurSel() * MAX_ZAHLENHAI_BUTTON;
	hai.startRound(nButton);
	CSetList(nButton);

	updatePoints();
	updateButtons();
		
	//((CEdit*)GetDlgItem(IDC_STATIC_DISCLAIMER))->ShowWindow(0);
	//((CEdit*)GetDlgItem(IDC_STATIC_INFO))->ShowWindow(0);
	
}

//Die Ergebnisse, welche in der Liste im Spiel zu sehen sind werden auf Wunsch des Benutzers am Ende des Spiels auch noch in eine Zusammenfassung
//geschrieben. Die Zusammenfassung ist so breit wie n�tig, orientiert sich also an der L�nge der Zahlen, welche eingetragen werden.
//Am Beginn der Liste, und nach jedem 50ten Eintrag wird eine kleine Orientierung gegeben, welche Spalte welche Daten beinhaltet.
//Wenn bei einem neuen Spiel eine Zusammenfassung geschrieben wird, wird die bereits existierende �berschrieben. Dies sollte nur auf Wunsch des Benutzers 
//m�glich sein.
//Es soll noch die M�glichkeit geben die Zusammenfassung in einem bestimmten Ordner zu speichern.

void CMFCZahlenHaiDlg::writeLogFile()
{
	CString logfileDate;
	CString logfileName;
	CString logfileNumbers;
	CString time;
	CTime t = CTime::GetCurrentTime();
	time = t.Format("%B %d, %Y, %H:%M");
	
	showWinner=1;
	char Buffer[1000];
	
	CString upperLimitNumbers = itoa(hai.getUpperLimit(),Buffer,10);
	CString playerName = optionen.playername;
	CString SpielerPunkte;
	SpielerPunkte=itoa(hai.getPointsPlayer(),Buffer,10);

	CStdioFile file;
	//Je nach Sprachversion hei�t die Datei, in welcher das Spiel gespeichert wird anders.
	CString filename;
	filename.LoadString(IDS_FILE_NAME);
	if(playerName=="")
		playerName="name";

	CString upperLimitZeug = upperLimitNumbers;
	
	
	//Der Dateiname wird durch die Anzahl im Zahlenvorrat, die Punktzahl des Spielers und den Spielernamen erweitert.
	//Die erm�glicht eine Art Highscore, und das Schreiben mehrerer Dateien
	filename=upperLimitZeug+"_"+SpielerPunkte+"_"+playerName+"_"+filename;
	//Die Datei "Zusammenfassung.txt" wird zum schreiben ge�ffnet
	file.Open(filename,CFile::modeCreate|CFile::modeWrite);
	
	SpielerPunkte="";

    CString LogText;
	file.WriteString("\r\n"+filename);
	LogText.LoadString(IDS_LOGFILE_DATE);
	file.WriteString(LogText+time);
	LogText.LoadString(IDS_LOGFILE_NAME);
	file.WriteString(LogText+optionen.playername);
	LogText.LoadString(IDS_LOGFILE_NUMBERS);
	file.WriteString(LogText+upperLimitNumbers);
	
	//((CEdit*)GetDlgItem(IDC_BUTTON_REST))->EnableWindow(false);
	
	//CStrings f�r die �berschriften der einzelnen Spalten
	CString Zug;
	CString Spieler;
	CString Hai;
	CString HaiPunkte;
	CString Rest;
	
	Zug.LoadString(IDS_ZUG2);
	Hai.LoadString(IDS_HAI2);
	Spieler.LoadString(IDS_SPIELER2);
	SpielerPunkte.LoadString(IDS_SPIELER_PUNKTE2);
	HaiPunkte.LoadString(IDS_HAI_PUNKTE2);
	Rest.LoadString(IDS_REST2);

	/*
	Spieler.Delete(Spieler.Find("-",0)+1,1);
	Hai.Delete(Hai.Find("-",0)+1,1);
	SpielerPunkte.Delete(SpielerPunkte.Find("-",0)+1,1);
	HaiPunkte.Delete(HaiPunkte.Find("-",0)+1,1);
	Rest.Delete(Rest.Find("-",0)+1,1);
*/
    //Anzahl der Spalten wird herausgefunden
	int cols = ListControl.GetHeaderCtrl()->GetItemCount();
	int *n_max;
	n_max = new int [cols];
	//Zwei Schleifen, welche f�r die Breite der Spalten zust�ndig sind, wenn der Inhalt der Spalten kleiner ist als die �berschrift
	//bzw. die Header
	//i durchl�uft die Zeilen und j die jeweiligen Spalten 
	for (int i=0; i<ListControl.GetItemCount(); i++)
	{
		for (int j=0; j<cols; j++)
		{
			//Wenn die L�nge des Textes im Header kleiner ist als die der gr��ten Zahlenreihe in der Tabelle,
			//dann wird die �berschrift links mit Leerzeichen aufgef�llt
			CString line="";
			line += ListControl.GetItemText(i,j);
			
			switch(j)
			{
				//Wenn das Wort "Zug" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingef�gt, bis die Gr��e passt
				case 0:n_max[j] = Zug.GetLength();while(Zug.GetLength() < line.GetLength())Zug.Insert(0, " ");break;
								
				//Wenn das Wort "Spieler" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingef�gt, bis die Gr��e passt
				case 1:n_max[j] = Spieler.GetLength();while(Spieler.GetLength() < line.GetLength())Spieler.Insert(0, " ");break;
				
				//Wenn das Wort "Hai" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingef�gt, bis die Gr��e passt
				case 2:n_max[j] = Hai.GetLength();while(Hai.GetLength() < line.GetLength())Hai.Insert(0, " ");break;
								
				//Wenn das Wort "Spieler-Punkte" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingef�gt, bis die Gr��e passt
				case 3:n_max[j] = SpielerPunkte.GetLength();while(SpielerPunkte.GetLength() < line.GetLength())SpielerPunkte.Insert(0, " ");break;
				
				//Wenn das Wort "Hai-Punkte" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingef�gt, bis die Gr��e passt
				case 4:n_max[j] = HaiPunkte.GetLength();while(HaiPunkte.GetLength() < line.GetLength())HaiPunkte.Insert(0, " ");break;
				
				//Wenn das Wort "Rest" kleiner ist als der Inhalt der Spalte, dann werden Leerzeichen eingef�gt, bis die Gr��e passt
				case 5:n_max[j] = Rest.GetLength();while(Rest.GetLength() < line.GetLength())Rest.Insert(0, " ");break;
			};
			
        line += ListControl.GetItemText(i,j);
		//n-max wird die gr��te Spaltenbreite zugewiesen
		if (n_max[j] < line.GetLength()) n_max[j] = line.GetLength();
		}
	}
	
	//Die �berschrift der einzelnen Spalten werden geschrieben
	CString logfileHeadline;
	logfileHeadline.LoadString(IDS_LOGFILE_HEADLINE);
	file.WriteString(logfileHeadline);

	//In den �berschriften der Spielverlaufstabelle wird das "-" Zeichen gesucht und die nachfolgende
	//Stelle wird gel�scht. Da diese Stelle ein Zeilenumbruch ist, ist die Darstellung in der Zusammenfassung
	//nicht richtig

	


	CString head = Zug + " | " + Spieler + " | " + Hai + " | " + SpielerPunkte + " | " + HaiPunkte + " | " + Rest + " |\r\n";
	file.WriteString(head);
	//Zwei Schleifen, welche f�r die Breite der Spalten zust�ndig sind, wenn der Inhalt der Spalten kleiner ist als die �berschrift
	//bzw. die Header
	//i durchl�uft die Zeilen und j die jeweiligen Spalten 
	//VC7 kann den G�ltigkeitsbereich von i bei mehrfachen Konstrukten for(int i ...) korrekt
	//    verarbeiten. Da VC6 dies nicht kann, wurde i hier nicht noch einmal deklariert.
	for(int i =0;i <ListControl.GetItemCount();i++)
	{
		CString line="\r\n";
		for(int j =0;j < ListControl.GetHeaderCtrl()->GetItemCount();j++)
		{
			//Wenn die L�nge des Textes der geschrieben wird kleiner ist als die vorher ermittelte gr��te L�nge, dann wird diese
			//mit Freizeichen links aufgef�llt
			CString tmpStr = ListControl.GetItemText(i,j);
			while (tmpStr.GetLength() < n_max[j]) tmpStr.Insert(0, " ");
			line += tmpStr + " | ";
			//Alle 50 Zeilen wird zur Orientierung eine zus�tzliche Zeile eingef�gt, welche die Header der Spalten wieder einf�gt
			int n=i%50;
			if(i!=0 && n==0 && j==0 && ListControl.GetItemCount() > 50)
				file.WriteString("\r\n\r\n"+head);
		}
		file.WriteString(line);
	}
	if(i>=60)
        file.WriteString("\r\n\r\n"+head);
	delete []n_max;

	
	 
	CString pointsPlayer = itoa(hai.getPointsPlayer(),Buffer,10);
	CString pointsComputer = itoa(hai.getPointsComputer(),Buffer,10);
	CString currentRound = itoa(hai.getCurrentRound(),Buffer,10);
	
	CString logfilePointsPlayer;
	CString logfilePointsComputer;
	CString logfileRounds;
	CString lead;
	CString behind;

	//Punkte und Rundenanzahl werden nach der Tabelle in die Zusammenfassung geschrieben		
	LogText.LoadString(IDS_LOGFILE_POINTS_PLAYER);
	file.WriteString(LogText+pointsPlayer);
	LogText.LoadString(IDS_LOGFILE_POINTS_COMPUTER);
	file.WriteString(LogText+pointsComputer);
	LogText.LoadString(IDS_LOGFILE_ROUNDS);
	file.WriteString(LogText+currentRound);
	if(hai.getPointsPlayer() > hai.getPointsComputer())
	{
		LogText.LoadString(IDS_LOG_LEAD);
		int lead = hai.getPointsPlayer()-hai.getPointsComputer();
		file.WriteString(LogText+(itoa(lead,Buffer,10)));
	}
	else
	{
		if(hai.getPointsPlayer() < hai.getPointsComputer())
		{
			LogText.LoadString(IDS_LOG_BEHIND);
			int behind = hai.getPointsComputer()-hai.getPointsPlayer();
			file.WriteString(LogText+(itoa(behind,Buffer,10)));
		}
	}
	int upperLimit=hai.getUpperLimit();
	//Wenn die maximale Punktezahl f�r die gew�hlte Zahl schonmal berechnet wurde, wird das errechnete Ergebnis
	//auch mit in der Zusammenfassung angegeben
	if(upperLimit <= sizeof(maxPossiblePoints)/sizeof(int))
	{
     	CString logfileMaxPoints;
		logfileMaxPoints.LoadString(IDS_LOGFILE_MAXPOINTS);
		file.WriteString(logfileMaxPoints+ Optimal[upperLimit-1][2]);
	}

	file.Close();

	//Andere M�glichkeit
	//file.WriteString(CMsg(IDS_LOGFILE_ROUNDS)+currentRound);
}
// Der Gewinner des Spiels wird ermittelt und das Ergebnis wird ausgegeben
int CMFCZahlenHaiDlg::winner()
{
	if(!hai.gameFinished())
		return 0;

	char Buffer[1000];
	int pointsPlayer = hai.getPointsPlayer();
	int pointsComputer = hai.getPointsComputer();

	((CEdit*)GetDlgItem(IDC_BUTTON_REST))->EnableWindow(false);
	//Um den Pfad der Zusammenfassung angeben zu k�nnen wird der Pfad der Exe Datei gespeichert und um den Namen der Exe Datei 
	//gek�rzt
	CString exePathSummary=exePath;
	int pos = exePathSummary.ReverseFind( '\\');
	exePathSummary = exePathSummary.Mid(1, pos-1);

	CString upperLimitZeug=itoa(hai.getUpperLimit(),Buffer,10);
	CString SpielerPunkte=itoa(pointsPlayer, Buffer, 10);
	CString playerName = optionen.playername;
	CString filename;
	filename.LoadString(IDS_FILE_NAME);
	if(playerName=="")
		playerName="name";

	CString summaryName=upperLimitZeug+"_"+SpielerPunkte+"_"+playerName+"_"+filename;
	CString text;
	text.Format(IDS_LOGFILE_LOCATION,summaryName,exePathSummary);
	
	((CEdit*)GetDlgItem(IDC_STATIC_SUM))->ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_STATIC))->ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_EDIT1))->ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_BUTTON_OK))->ShowWindow(0);
	((CEdit*)GetDlgItem(IDC_STATIC_EINSTELLUNGEN))->ShowWindow(0);

	//m_LedWinner.ShowWindow(1);

	/*if(pointsPlayer>pointsComputer)
	{
		//CString ledWinner="";
		//ledWinner.LoadString(IDS_LED_WIN);
		//m_LedWinner.SetText(ledWinner);
	}
	else
	{
		if(pointsPlayer<pointsComputer)
		{
			CString ledLoser="";
			ledLoser.LoadString(IDS_LED_LOST);
			m_LedWinner.SetText(ledLoser);
		}
		else
		{
			CString ledDraw="";
			ledDraw.LoadString(IDS_LED_DRAW);
			m_LedWinner.SetText(ledDraw);
		}
	}*/
	summary.uebergeben(this->hai, exePathSummary, summaryName);
	summary.DoModal();
	
	int writeFile=1;
	showWinner=1;

	if(summary.radio1==1)
		writeFile=1;
	if(summary.radio2==1)
        writeFile=0;

	return writeFile;
	//Bei Messageboxes mit Antwortm�glichkeiten gibt die Funktion einen int Wert der Antwort zur�ck
}

// Wenn der Benutzer den Button "Maximale Punkte" dr�ckt
void CMFCZahlenHaiDlg::addOnInformation()
{
	int upperLimit = hai.getUpperLimit();
	CString question;
	question.LoadString(IDS_QUESTION);
	CString headline;
	headline.LoadString(IDS_MAX_POINTS_HEADLINE);
	
	if(optionen.calculateMaxNew)
	{
		CString warning;
		warning.Format(IDS_WARNING, upperLimit, upperLimit);
		int r = MessageBox(warning,headline, MB_ICONWARNING | MB_YESNO);
		if(r==IDYES) addOn();
	}
	else
	{
		if(optionen.showMax)
		{
			CString answer;
           	answer.Format(IDS_MAX_POINTS_INFORMATION, upperLimit, maxPossiblePoints[upperLimit-1], upperLimit, maxPrime(upperLimit));
			int r = MessageBox(answer,headline, MB_ICONINFORMATION | MB_YESNO);
			//Gibt dem Spieler die M�glichkeit sich den optimalen Weg mit anzeigen zu lassen
			if(r==IDYES)
			{
				answer.Format(IDS_MAX_POINTS_INFORMATION2, upperLimit, atoi(Optimal[upperLimit-1][2]),Optimal[upperLimit-1][1], upperLimit, maxPrime(upperLimit));
				MessageBox(answer,headline, MB_ICONINFORMATION | MB_OK);
			}
		}
	}
}

//Ausgabe von zus�tzlichen Features wie maximal m�gliche Punkte, durchlaufene Knoten, ben�tigte Zeit etc.
//wird f�r die maxPoints ben�tigt
void CMFCZahlenHaiDlg::addOn()
{
	int tempUpperLimit = hai.getUpperLimit();
	int maxPts = maxPoints(tempUpperLimit);
	
	CString result;
  	CString headline;
	
	headline.LoadString(IDS_MAX_POINTS_HEADLINE);
	result.Format(IDS_MAX_POINTS_NEW, tempUpperLimit, maxPts, getTime(), getNumberOfRounds(), maxPrime(tempUpperLimit), bestWay);	
	MessageBox(result,headline, MB_ICONINFORMATION);

/*
	// flomar
	int tempUpperLimit = hai.getUpperLimit();
    int maxPts = 0;
	globalPoints = 0;
	AfxBeginThread(maxPointsStatic, (LPVOID)(int)(tempUpperLimit));
*/
    	

}

//Wenn sich der Fokus �ber einem der Zahlenbuttons befindet und der Benutzer die Enter Taste dr�ckt, wird dieser Button ausgew�hlt
void CMFCZahlenHaiDlg::enterWasPressed()
{
	int buttonID = this->GetFocus()->GetDlgCtrlID();
	//Wenn auf einem der 30 Buttons mit Zahlen Enter gedr�ckt wird
	if(buttonID >= IDC_BUTTON01 && buttonID <= IDC_BUTTON30)
		this->OnBnClickedButton(buttonID);
	else
        //Wenn in dem Edit Feld Enter gedr�ckt wird, wird die Zahl gleich ausgew�hlt
		if(buttonID == IDC_EDIT1)
		{
			//OK-Button wurde gedr�ckt
			OnBnClickedButtonOk();
			//Der Focus wird auf den Button mit der Zahl 1 gelegt
			arrayButtonControl[0].SetFocus();
			((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(false);
		}
		//Aktivierung der Enter Taste auf allen Buttons
		else
			if(buttonID==IDC_BUTTON_REST)
				OnBnClickedButtonRest();
			else
			    if(buttonID==IDC_BUTTON_OPTION)
					OnBnClickedButtonOption();
				else
				    if(buttonID==IDC_BUTTON_STARTNEW)
							OnBnClickedButtonStartnew();
						else
						    if(buttonID==ID_BUTTON_RULES)
								OnBnClickedButtonRules();
}

//Diese Funktion sorgt daf�r, das der Benutzer mit den Pfeiltasten durch die Zahlen gehen kann 
void CMFCZahlenHaiDlg::arrowKeyPressed(WPARAM wParam)
{
	//aktuell aktiver Reiter
	int tab = tabControl.GetCurSel();
	int tabCount = tabControl.GetItemCount();
	int *numbersTemp=hai.getNumbers();

	//buttonID gibt die ID des gew�hlten Button an
	int buttonID = this->GetFocus()->GetDlgCtrlID();
	//maxStepsLeft und maxStepsRight, geben die Anzahl der vorhandenen Felder links und rechtes vom gew�hlten Button an, um damit seine
	//Position zu bestimmen
	int maxStepsRight=0;
	int maxStepsLeft=0;

	//Pfeiltaste nach Oben
	if(wParam==38)
	{
		//befindet sich der Fokus auf einem der 30 Zahlenbuttons?
		if(buttonID >= IDC_BUTTON01 && buttonID <= IDC_BUTTON30)
		{
			//nur Buttons in der mittleren und untersten Reihe
			if(buttonID>=IDC_BUTTON11 && buttonID <= IDC_BUTTON30)
			{
				//ist der Button genau oben dr�ber frei?
				if(numbersTemp[buttonID-IDC_BUTTON01-9+tab*MAX_ZAHLENHAI_BUTTON]==FREE)
				{
					//wenn frei, dann erh�lt der Button den Fokus 
					arrayButtonControl[buttonID-IDC_BUTTON01-10].SetFocus();
					return;
				}
				else
				{
					//mittlere Reihe
					if(buttonID>=IDC_BUTTON11 && buttonID<=IDC_BUTTON20)
					{
						maxStepsRight=IDC_BUTTON20-buttonID;
						maxStepsLeft=buttonID-IDC_BUTTON11;
						nextFreeButtonAbove(buttonID, maxStepsLeft, maxStepsRight);
					}
					//untere Reihe
					else
					{
						maxStepsRight=IDC_BUTTON30-buttonID;
						maxStepsLeft=buttonID-IDC_BUTTON21;
						nextFreeButtonAbove(buttonID, maxStepsLeft, maxStepsRight);
					}
				}
			}
			else
			{
                //wenn sich der Fokus in der oberen Reihe befindet, und somit der Reiter gewechselt werden soll
				maxStepsRight=IDC_BUTTON10-buttonID;
				maxStepsLeft=buttonID-IDC_BUTTON01;

				//der aktuell ausgew�hlte Reiter
				tab = tabControl.GetCurSel();
				//neuer Reiter wird ermittelt und ausgew�hlt
				if(tab>0 && tab<=tabCount)
                    tabControl.SetCurSel(tab-1);
				//neuer ausgew�hlter Reiter
				tab = tabControl.GetCurSel();
				//auf dem neuen Reiter werden die Buttons aktualisiert
				updateButtons();
				
				//Nachdem der neue Reiter ausgew�hlt ist wird noch der Fokus auf einen Button gesetzt
				//Abfrage ob der Button direkt �ber dem momentan ausgew�hlten noch frei ist
				if(numbersTemp[buttonID-IDC_BUTTON01+20+1+tab*MAX_ZAHLENHAI_BUTTON]==FREE)
				{
					//wenn der Button noch frei ist, erh�lt dieser den Fokus
					arrayButtonControl[buttonID-IDC_BUTTON01+20].SetFocus();
					//kann eigentlich auch raus
					return;
				}
				//wenn der Button �ber dem aktuell ausgew�hlten nicht mehr frei ist
				else
				{
					//alle Buttons links von dem bereits vergebenen werden durchsucht, bis ein freier gefunden wurde
					for(int i=0; i<maxStepsLeft; i++)
					{
						//-i-1, da i bei 0 anf�ngt zu z�hlen
						if(numbersTemp[buttonID-IDC_BUTTON01+20+tab*MAX_ZAHLENHAI_BUTTON - i] == FREE)
						{
							//der Index des freien Buttons wird auf maxStepsLeft gesetzt
							maxStepsLeft=i;					                            
							break;
						}
					}
					//alle Buttons rechts von dem bereits vergebenne werden durchsucht, bis ein freier gefunden wurde
					for(i=0; i<maxStepsRight; i++)
					{
						//+i+1, da i bei 0 anf�ngt zu z�hlen
						if(numbersTemp[buttonID-IDC_BUTTON01+20+tab*MAX_ZAHLENHAI_BUTTON + i+2] == FREE)
						{
							//der Index des freien Buttons wird auf maxStepsRight gesetzt
							maxStepsRight=i;					                            
							break;
						}
					}

					if(maxStepsLeft>maxStepsRight)
					{
						//Schritt nach rechts, wenn maxStepsRight kleiner als maxStepsLeft
						arrayButtonControl[buttonID-IDC_BUTTON01+20+maxStepsRight+1].SetFocus();
					}
					else
					{
						//Schritt nach links, wenn maxStepsLeft kleiner oder gleich maxStepsRight
						arrayButtonControl[buttonID-IDC_BUTTON01+20-maxStepsLeft-1].SetFocus();
					}
				}
			}
		}
	}
	//Pfeiltaste nach Unten
	if(wParam==40)
	{
		//befindet sich der Fokus auf einem der 30 Zahlenbuttons?
		if(buttonID >= IDC_BUTTON01 && buttonID <= IDC_BUTTON30)
		{
			//nur Buttons in der mittleren und obersten Reihe
			if(buttonID>=IDC_BUTTON01 && buttonID <= IDC_BUTTON20)
			{
				//ist der Button genau drunter frei?
				if(numbersTemp[buttonID-IDC_BUTTON01+11+tab*MAX_ZAHLENHAI_BUTTON]==FREE)
				{
					arrayButtonControl[buttonID-IDC_BUTTON01+10].SetFocus();
					return;
				}
				else
				{
					//obere Reihe
					if(buttonID>=IDC_BUTTON01 && buttonID<=IDC_BUTTON10)
					{
						maxStepsRight=IDC_BUTTON10-buttonID;
						maxStepsLeft=buttonID-IDC_BUTTON01;
						nextFreeButtonBelow(buttonID, maxStepsLeft, maxStepsRight);
					}
					//mittlere Reihe
					if(buttonID>=IDC_BUTTON11 && buttonID<=IDC_BUTTON20)
					{
						maxStepsRight=IDC_BUTTON20-buttonID;
						maxStepsLeft=buttonID-IDC_BUTTON11;
						nextFreeButtonBelow(buttonID, maxStepsLeft, maxStepsRight);
					}

				}
			}
			else
			{
                //wenn sich der Fokus in der unteren Reihe befindet, und somit dert Reiter gewechselt werden soll
				maxStepsRight=IDC_BUTTON30-buttonID;
				maxStepsLeft=buttonID-IDC_BUTTON21;
				//der aktuell ausgew�hlte Reiter
				tab = tabControl.GetCurSel();
				//Neuer Reiter wird ermittelt und ausgew�hlt
				if(tab>=0 && tab<tabCount)
                    tabControl.SetCurSel(tab+1);
				//neuer ausgew�hlter Reiter
				tab = tabControl.GetCurSel();
				updateButtons();
				
				//Nachdem der neue Reiter ausgew�hlt ist, wird noch der Fokus auf einen neuen Button gesetzt
				//Abfrage ob der Button direkt unter dem momentan ausgew�hlten noch frei ist
				if(numbersTemp[buttonID-IDC_BUTTON01-19+tab*MAX_ZAHLENHAI_BUTTON]==FREE)
				{
					arrayButtonControl[buttonID-IDC_BUTTON01-20].SetFocus();
					return;
				}
				//wenn der Button unter dem aktuell ausgew�hlten nicht mehr frei ist
				else
				{
					//alle Buttons rechts von dem bereits vergebenen werden durchsucht, bis ein freier gefunden wurde
					for(int i=0; i<maxStepsRight;i++)
					{
						if(numbersTemp[buttonID-IDC_BUTTON01-19+tab*MAX_ZAHLENHAI_BUTTON+i+1]==FREE)
						{
							maxStepsRight=i;
							break;
						}
					}
					//alle Buttons links von dem breits vergebenen werden durchsuchr, bis ein freier gefunden wurde
					for(i=0; i<maxStepsLeft; i++)
					{
						if(numbersTemp[buttonID-IDC_BUTTON01-19+tab*MAX_ZAHLENHAI_BUTTON-i-1]==FREE)
						{
							maxStepsLeft=i;
							break;
						}
					}
					if(maxStepsRight>maxStepsLeft)
					{
						//Schritt nach links, wenn maxStepsLeft kleiner als maxStepsRight
						arrayButtonControl[buttonID-IDC_BUTTON01-20-maxStepsLeft-1].SetFocus();
					}
					else
					{
						//Schritt nach rechts, wenn maxStepsRight kleiner oder gleich maxStepsLeft
						arrayButtonControl[buttonID-IDC_BUTTON01-20+maxStepsRight+1].SetFocus();
					}
				}
			}
		}
		else
		{
			//Wenn der Benutzer die Pfeiltaste nach unten dr�ckt und sich der Fokus auf einem Reiter befindet
			if(buttonID == IDC_TAB1)
			{
				//aktuell ausgew�hlter Reiter wird herausgefunden
				tab=tabControl.GetCurSel();
				//momentan dargestellter Zahlenbereich wird durchsucht
				for(int i = MAX_ZAHLENHAI_BUTTON*tab+1; i<=MAX_ZAHLENHAI_BUTTON*tab+MAX_ZAHLENHAI_BUTTON; i++)
				{
					//wenn eine freie Zahl gefunden wurde
					if(numbersTemp[i]==FREE)
					{
						//die erste freie Zahl die gefunden wurde erh�lt den Focus
						arrayButtonControl[i-tab*30-1].SetFocus();
						//Abbruch der for-Schleife
						i = MAX_ZAHLENHAI_BUTTON*tab+31;
					}
				}
			}
		}
	}
}

//Die Funktion findet den n�chstegelegensten freien Button in der n�chst h�heren Zeile und legt den Focus auf diesen
void CMFCZahlenHaiDlg::nextFreeButtonAbove(int buttonID, int maxStepsLeft, int maxStepsRight)
{
	int tab = tabControl.GetCurSel();
	int *numbersTemp=hai.getNumbers();

	for(int i=0; i<maxStepsLeft; i++)
	{
		//-i-1, da i bei 0 anf�ngt zu z�hlen
		if(numbersTemp[buttonID-IDC_BUTTON01-9+tab*MAX_ZAHLENHAI_BUTTON - i-1] == FREE)
		{
			maxStepsLeft=i;					                            
			break;
		}
	}
	for(i=0; i<maxStepsRight; i++)
	{
		//+i+1, da i bei 0 anf�ngt zu z�hlen
		if(numbersTemp[buttonID-IDC_BUTTON01-9+tab*MAX_ZAHLENHAI_BUTTON + i+1] == FREE)
		{
			maxStepsRight=i;					                            
			break;
		}
	}

	//es wird verglichen in welcher Richtung eher ein feier Button zufinden ist
	if(maxStepsLeft>maxStepsRight)
	{
		//Schritt nach rechts, wenn maxStepsRight kleiner als maxStepsLeft
		arrayButtonControl[buttonID-IDC_BUTTON01-10+maxStepsRight+1].SetFocus();
	}
	else
	{
		//Schritt nach links, wenn maxStepsLeft kleiner oder gleich maxStepsRight
		arrayButtonControl[buttonID-IDC_BUTTON01-10-maxStepsLeft-1].SetFocus();
	}
}
//Die Funktion findet den n�chstegelegensten freien Button in der n�chst niedrigeren/unteren Zeile und legt den Focus auf diesen
void CMFCZahlenHaiDlg::nextFreeButtonBelow(int buttonID, int maxStepsLeft, int maxStepsRight)
{
	int tab=tabControl.GetCurSel();
	int *numbersTemp=hai.getNumbers();

	for(int i=0; i<maxStepsLeft; i++)
	{
		//-i-1, da i bei 0 anf�ngt zu z�hlen
		if(numbersTemp[buttonID-IDC_BUTTON01+11+tab*MAX_ZAHLENHAI_BUTTON-i-1]==FREE)
		{
			maxStepsLeft=i;
			break;
		}
	}
	for(i=0; i<maxStepsRight; i++)
	{
		//+i+1, da i bei 0 anf�ngt zu z�hlen
		if(numbersTemp[buttonID-IDC_BUTTON01+11+tab*MAX_ZAHLENHAI_BUTTON+i+1]==FREE)
		{
			maxStepsRight=i;
			break;
		}
	}

	//es wird verglichen, in welcher Richtung eher ein freier Button zu finden  ist
	if(maxStepsRight > maxStepsLeft)
	{
		//Schritt nach links, wenn maxStepsLeft kleiner ist als maxStepsRight
		arrayButtonControl[buttonID-IDC_BUTTON01+10-maxStepsLeft-1].SetFocus();
	}
	else
	{
		//Schritt nach links, wenn maxStepsRight kleiner oder gleich maxStepsLeft
		arrayButtonControl[buttonID-IDC_BUTTON01+10+maxStepsRight+1].SetFocus();
	}
}

//Die Datei "Spieldaten.txt" enth�lt von allen bisher berechneten maximalen Punktzahlen die Ergebnisse
//kommentieren
void CMFCZahlenHaiDlg::readGameData()
{
    CStdioFile GameData;
	CString Line="";
	CString Teil="";
	CString fileName="";
	fileName.LoadString(IDS_GAME_DATA);

	//Versuch die Datei "GameData.txt" zu �ffnen
	BOOL openOk = GameData.Open(fileName,CFile::modeRead);
	//wenn sich die Datei �ffnen l�sst(also vorhanden ist)
	if(openOk)
	{
        int Stelle=0;
		for(int i=0; i<yAchse; i++)
	    {
			int count = 0;
			GameData.ReadString(Line);
			while(count<4)
			{
				Stelle=Line.Find(":",Stelle);
				if(Stelle > -1)
				{
					Optimal[i][count]=Line.Left(Stelle);
				}
				else
				{
					Stelle=Line.Find("|",0);
					Optimal[i][count]=Line.Left(Stelle);
					count = 4;
				}
				count++;
				Line.Delete(0,Stelle+1);
				Stelle = 0;
			}
		}
	}
	GameData.Close();
}
void CMFCZahlenHaiDlg::WinHelp(DWORD dwData, UINT nCmd)
{
	CString exePathHelp=exePath;
	CString helpFile="";
	helpFile.LoadString(IDS_HELP_FILE);
	exePathHelp.Delete(0,1);
		
	int pos = exePathHelp.ReverseFind( '\\');
	exePathHelp = exePathHelp.Mid(0, pos+1);
	exePathHelp+=helpFile;
	//HH_DISPLAY_TOPIC durch HH_HELP_CONTEXT austauschen
	::HtmlHelp(this->m_hWnd, exePathHelp,HH_DISPLAY_TOPIC, NULL);
}

int CMFCZahlenHaiDlg::readRegistry()
{
	//L�uft so nicht unter dem VC++ 6.0 Compiler

	optionenSetting.LoadString(IDS_REG_TRUE);
	toolTipSetting.LoadString(IDS_REG_TRUE);
	int regUpperLimit;
	
	//Die Einstellungen der Optionen werden aus der Registry geladen
	//TODO: kommentieren
	ULONG strLength = 128;
	char valueName[128], valuePlayer[128], valueOptionen[128], valueToolTips[128], valueNumber[128];

	int returnKey = regKey.Open(HKEY_CURRENT_USER,"Software\\Zahlenhai\\Settings",KEY_READ);
	if(returnKey == ERROR_SUCCESS)
	{
		regKey.Open(HKEY_CURRENT_USER, "Software\\Zahlenhai\\Settings",KEY_ALL_ACCESS);
		strcpy(valueName, "OptionenSettings");
		regKey.QueryStringValue(valueName,valueOptionen, &strLength);
        optionenSetting=valueOptionen;
		
		strLength = 128;
		strcpy(valueName,"ToolTipSettings");
		regKey.QueryStringValue(valueName,valueToolTips, &strLength);
		toolTipSetting = valueToolTips;
		
		if(toolTipSetting=="true")
			optionen.showToolTips=true;
		else
			optionen.showToolTips=false;

		strLength = 128;
		strcpy(valueName, "Spielername"); 
		regKey.QueryStringValue(valueName, valuePlayer, &strLength);
		optionen.playername=valuePlayer;

		strLength = 128;
		strcpy(valueName, "Startnummer");
		regKey.QueryStringValue(valueName, valueNumber, &strLength);
		startNumberSetting=valueNumber;
		if(startNumberSetting=="true")
		{
			optionen.showStartNumber=true;
			strLength = 128;
			strcpy(valueName, "Startzahl"); 
			regKey.QueryStringValue(valueName, valueNumber, &strLength);
			regUpperLimit=atoi(valueNumber);
			regKey.Close();
		}
		else
		{
			optionen.showStartNumber=false;
			regUpperLimit=20;
		}

		if(optionenSetting=="true")
		{
			optionen.showOption=true;
			optionen.showButton=0;
			optionen.DoModal();
		}
		else
		{
			optionen.showOption=false;
			optionen.playername="";
		}
	}
	else
	{
		regUpperLimit=20;
		optionen.showButton=0;
		optionen.DoModal();
		
	}

	return regUpperLimit;

	//Andere Variante
	//regKey.QueryStringValue(valueName, valueNumber, &strLength);
}

void CMFCZahlenHaiDlg::writeRegistry()
{
	//L�uft so nicht unter dem VC++ 6.0 Compiler

	// 1. Stelle sicher, dass ein registry key existiert
	char valueName[128];
	char charUpperLimit[128];
	int regUpperLimit = hai.getUpperLimit();
	if(regKey.Open(HKEY_CURRENT_USER,"Software\\Zahlenhai\\Settings",KEY_WRITE)== ERROR_FILE_NOT_FOUND)
	{
		HKEY hKey;
		RegCreateKeyEx(HKEY_CURRENT_USER,"Software\\Zahlenhai\\Settings", 0, NULL, REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS | KEY_WRITE | KEY_READ, NULL, &hKey, NULL);
	}
	else
		regKey.Close();


	// 2. bereite persistente Optionen vor
	if(optionen.showOption==false)
		optionenSetting="false";
	else
		optionenSetting="true";

	if(optionen.showToolTips==false)
		toolTipSetting="false";
	else
		toolTipSetting="true";

	if(optionen.showStartNumber==false)
		startNumberSetting="false";
	else
		startNumberSetting="true";

	// 3. schreibe persistente Optionen
	
	regKey.Open(HKEY_CURRENT_USER, "Software\\Zahlenhai\\Settings", KEY_ALL_ACCESS);
	
	strcpy(valueName,"OptionenSettings");
	regKey.SetStringValue(valueName, optionenSetting);
	strcpy(valueName,"ToolTipSettings");
	regKey.SetStringValue(valueName, toolTipSetting);
	strcpy(valueName,"Spielername");
	regKey.SetStringValue(valueName, optionen.playername);
	strcpy(valueName, "Startnummer");
	regKey.SetStringValue(valueName, startNumberSetting);
	strcpy(valueName,"Startzahl");
	regKey.SetStringValue(valueName, itoa(regUpperLimit,charUpperLimit,10));
	
	regKey.Close();

	//Andere Variante
	//regKey.SetStringValue(valueName, itoa(regUpperLimit,charUpperLimit,10),REG_SZ);
}
/*
//Setzten der Tausenderpunkte
char* CMFCZahlenHaiDlg::itoa_fmt(unsigned long ul_num)
{
	char pc_str[1000];
	unsigned long str_length, str_ptr;
	char * str, c_pt;

	// pre-compute the length of the output string
	str_length = (!ul_num) ? 2 : (unsigned long)floor(log((double)ul_num)/log(10.0))+2;
	str_length += (str_length-2)/3;
	str = new char [str_length];

	str_ptr = str_length-1;
	
	// write num blocks
	do {
		str_ptr = (str_ptr >= 3) ? str_ptr-3 : 0;
		itoa((int)(ul_num % 1000), str + str_ptr, 10);
		ul_num /= 1000;
		if (str_ptr) str_ptr--;
	} while (ul_num);

	// write 'dots'
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PT,pc_str,STR_LAENGE_STRING_TABLE);
	c_pt = pc_str[0];
	do {
		str_ptr += strlen(str+str_ptr);
		if ( str_ptr < str_length -1 ) str[str_ptr] = c_pt;
	} while ( str_ptr < str_length-1 );

	return str;
}*/