/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universit�t Siegen und Darmstadt

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


//////////////////////////////////////////////////////////////////
// Copyright 1998-2002 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// AnalyseNGram.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "FileTools.h"
#include "DlgNGramAnalysis.h"
#include "DialogeMessage.h"
#include "MakeNewName.h"
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgNGramAnaylsis 

CDlgNGramAnaylsis::CDlgNGramAnaylsis(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNGramAnaylsis::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNGramAnaylsis)
		m_N_NGram      = 0;
	    m_ShowCntNGram = 26;
		m_NrNGram      = 4;
	//}}AFX_DATA_INIT
	b_SaveNGramList = false;
	NGramPtr = NULL;

	NGramActualized = FALSE;
}

CDlgNGramAnaylsis::~CDlgNGramAnaylsis()
{
	if ( NGramPtr ) delete NGramPtr;
}

void CDlgNGramAnaylsis::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNGramAnaylsis)
	DDX_Control(pDX, IDC_EDIT1, m_ShowCntNGramCtrl);
	DDX_Control(pDX, IDC_EDIT2, m_NrNGramCtrl);
	DDX_Control(pDX, IDC_LIST1,  m_ListView);
	DDX_Radio  (pDX, IDC_RADIO1, m_N_NGram);
	DDX_Text(pDX, IDC_EDIT1, m_ShowCntNGram);
	DDX_Text(pDX, IDC_EDIT2, m_NrNGram);
	DDV_MinMaxLong(pDX, m_NrNGram, 3, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNGramAnaylsis, CDialog)
	//{{AFX_MSG_MAP(CDlgNGramAnaylsis)
		ON_BN_CLICKED(IDC_BUTTON2, OnEvalNGram)
		ON_BN_CLICKED(IDOK, OnSaveNGramList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgNGramAnaylsis 

int CDlgNGramAnaylsis::DoModal() 
{
	// TODO: Speziellen Code hier einf�gen und/oder Basisklasse aufrufen
	
	return CDialog::DoModal();
}

BOOL CDlgNGramAnaylsis::OnInitDialog()
{
	int colWidth = 100;										// Spaltenbreite in Pixel

	CDialog::OnInitDialog();

	m_ListView.SetExtendedStyle( LVS_EX_FULLROWSELECT );
	LoadString(AfxGetInstanceHandle(),IDS_STRING_HOMOPHONE_NR,pc_str,STR_LAENGE_STRING_TABLE);
	m_ListView.InsertColumn(1,pc_str,LVCFMT_LEFT,colWidth-32,1);							// Zeichen
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_LIST2,pc_str,STR_LAENGE_STRING_TABLE);
	m_ListView.InsertColumn(2,pc_str,LVCFMT_LEFT,colWidth-40,2);							// Anzahl
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_LIST3,pc_str,STR_LAENGE_STRING_TABLE);
	m_ListView.InsertColumn(3,pc_str,LVCFMT_LEFT,colWidth-10,3);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_COLUMN_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
	m_ListView.InsertColumn(3,pc_str,LVCFMT_LEFT,colWidth,3);
	SetupListBox( m_N_NGram+1 );
	m_NrNGramCtrl.EnableWindow(true);

	char line[CRYPTOOL_PATH_LENGTH];
	LoadString(AfxGetInstanceHandle(),IDS_NGRAM_TITLE,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line, pc_str, Title);
	SetWindowText(CString(line));
	return(TRUE);
}

// -----------------------------------------------------------------------------------------------------

void CDlgNGramAnaylsis::LoadText( char *buffer, const unsigned long Size, const char *OldTitle,
							 BOOL BinaryFile )
{
	bufferRef  = buffer;  
	bufferSize = Size;
	isBinary   = BinaryFile;
	strcpy(Title, OldTitle);
}


// -----------------------------------------------------------------------------------------------------

void CDlgNGramAnaylsis::Register(int N)
{
	int  i,j;
	l_N = N;

	if ( NGramPtr ) delete NGramPtr;
	if ( isBinary )
	{
		NGramPtr = new CNGram( bufferSize, (unsigned short)l_N, 256 );
		char SubStr[NGRAM_NMAX];
		SubStr[l_N] = 0;
		for ( i=0; (unsigned long)i<bufferSize; i++ )
		{
			if (i < l_N) SubStr[i] = bufferRef[i];
			else      
			{
				for ( j=1; j<l_N; j++) SubStr[j-1] = SubStr[j];
				SubStr[l_N-1] = bufferRef[i];
			}
			if ( i+1>= l_N ) // register Substring in N-Gram analysis
			{
				NGramPtr->add( SubStr );				
			}
		}
	}
	else
	{
		NGramPtr = new CNGram( bufferSize, (unsigned short)l_N, theApp.TextOptions.m_alphabet.GetLength() );
		char SubStr[NGRAM_NMAX];
		SubStr[l_N] = 0;
		int  l=0;
		for ( i=0; (unsigned long)i<bufferSize; i++ )
		{
			bool Flag = false;

			char chr = bufferRef[i];
			if ( !theApp.TextOptions.m_Case && chr >= 'a' && chr <= 'z' ) 
				chr = chr + ('A'-'a');
			for (j=0; j<theApp.TextOptions.m_alphabet.GetLength(); j++ )
				if ( chr == theApp.TextOptions.m_alphabet[j] ) 
				{ 
					Flag = true; 
					break;
				}
			if ( Flag )
			{
				if ( l<l_N ) 
				{
					SubStr[l++] = chr;
				}
				else
				{
					for ( j=1; j<l_N; j++) SubStr[j-1] = SubStr[j];
					SubStr[l_N-1] = chr;
				}
			}
			else
			{
				l=0;
			}
			if ( l>=l_N ) // register Substring in N-Gram analysis
			{
				NGramPtr->add( SubStr ); 
			}
		}

	}
	NGramPtr->sort();
}


// -----------------------------------------------------------------------------------------------------

void CDlgNGramAnaylsis::SetupListBox( int N )
{
	char          string[100];
	char          SubStr[NGRAM_NMAX+1];
	unsigned long cnt;
	double        rel;
	int  i,j;

	m_ListView.DeleteAllItems(); 
	if ( !NGramActualized ) Register( N );
	
	NGramPtr->resetIterator();
	unsigned long ListSize = (m_ShowCntNGram<NGramPtr->getIndividuals()) ? m_ShowCntNGram : NGramPtr->getIndividuals();
	if ( ListSize > 5000 ) 
		ListSize = 5000;
	for (i=0; (unsigned long)i<ListSize; i++)
	{
		NGramPtr->get( SubStr, cnt, rel );

		sprintf(string, "%3i", i+1);
		j=m_ListView.InsertItem(i,string);

		if ( isBinary )
		{
			for (int k=0; k<N; k++)	
			{
				int nr = (unsigned char)SubStr[k];
				char ch; 
				long c = nr % 16;

				nr /= 16;
				if (c<10)
				{
					ch = '0'+(char)c;
				}
				else
				{
					c-= 10; 
					ch = 'A'+(char)c;
				} 
				string[4*k+1] = ch;

				c = nr % 16;
				nr /= 16;
				if (c<10)
				{
					ch = '0'+(char)c;
				}
				else
				{
					c-= 10; 
					ch = 'A'+(char)c;
				} 
				string[4*k] = ch;

				if (k+1<N) 
				{
					string[4*k+2] = ',';
					string[4*k+3] = ' ';
				}
			}
			string[4*N-2] = 0;
		}
		else
		{
			strcpy(string, SubStr);
		}
		m_ListView.SetItemText(j,1,string);
		sprintf(string,"  %2.4f", rel*100.0);
		m_ListView.SetItemText(j,2,string);
		sprintf(string,"  %1i", cnt);
		m_ListView.SetItemText(j,3,string);
	}
}


// -----------------------------------------------------------------------------------------------------

int CDlgNGramAnaylsis::GetN()
{
	return m_N_NGram;
}


// -----------------------------------------------------------------------------------------------------

void CDlgNGramAnaylsis::OnEvalNGram() 
{
	SHOW_HOUR_GLASS
	UpdateData(TRUE);
	if ( m_ShowCntNGram <= 5000 )
	{	
		if ( m_N_NGram > 2 )
		{
			if ( m_NrNGram > NGRAM_NMAX ) 
			{
				m_NrNGram = NGRAM_NMAX;
			}
			SetupListBox( m_NrNGram );
		}
		else
		{
			SetupListBox( m_N_NGram+1 );
		}
	}
	else
	{
		Message( IDS_NGRAMLIST_TOLONG, MB_ICONEXCLAMATION );
		m_ShowCntNGramCtrl.SetFocus();
		m_ShowCntNGramCtrl.SetSel(0,-1);
	}
	UpdateData(FALSE);
	HIDE_HOUR_GLASS
}


// -----------------------------------------------------------------------------------------------------

void CDlgNGramAnaylsis::OnSaveNGramList() 
{
	char          SubStr[NGRAM_NMAX+1];
	unsigned long cnt;
	double        rel;
	
	UpdateData(TRUE);
	SHOW_HOUR_GLASS
	b_SaveNGramList = true;
	
	GetTmpName(outfile,"cry",".tmp");
	ofstream txt_NGram(outfile);
	// TODO Title via Ressourcen String Einf�gen
	char string[100];
	char title[CRYPTOOL_PATH_LENGTH], method[20]; 
	switch ( m_N_NGram )  {
	case 0: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_HISTOGRAM,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy( method, pc_str );
		break;
	case 1: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_DIGRAM,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy( method, pc_str );
		break;
	case 2: LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_TRIGRAM,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy( method, pc_str );
		break;
	case 3:  LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_NGRAM,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf( method, pc_str, m_NrNGram );
		break;
	}
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_ANALYSIS_OF,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(title, pc_str, method, Title, bufferSize);
//	MakeNewName2(title,sizeof(title),pc_str, Title,method);
	txt_NGram << title << "\n";
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_DESCRIPTION,pc_str,STR_LAENGE_STRING_TABLE);
	txt_NGram << pc_str << "\n\n";
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_NO,pc_str,STR_LAENGE_STRING_TABLE);
	txt_NGram.width(5); 
	txt_NGram << pc_str << '\t';
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_SUBSTR,pc_str,STR_LAENGE_STRING_TABLE);
	int wd = 0;
	while(pc_str[wd] != 0 ) wd++;
	if (isBinary)
		wd = (wd > l_N*3 -1) ? wd+2 : l_N*3+1;
	else
		wd = (wd > l_N ) ? wd +2 : l_N +2;
	txt_NGram.width(wd);
	txt_NGram << pc_str << '\t';
	LoadString(AfxGetInstanceHandle(),IDS_STRING_NGRAM_RELFREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
	txt_NGram.width(12);
	txt_NGram << pc_str << '\t';
	LoadString(AfxGetInstanceHandle(),IDS_STRING_COLUMN_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
	txt_NGram << pc_str << '\n';

	if ( !NGramActualized ) 
		Register ( l_N );

	NGramPtr->resetIterator();
	unsigned long ListSize = (m_ShowCntNGram<NGramPtr->getIndividuals()) ? m_ShowCntNGram : NGramPtr->getIndividuals();
	UpdateData(FALSE);
	for (int i=0; (unsigned long)i<ListSize; i++)
	{
		txt_NGram.width(5);
		txt_NGram << i+1 << "\t";

		NGramPtr->get( SubStr, cnt, rel );

		// int i_Ndx = SA->GetIndex(i);
		if ( isBinary )
		{
			for (int k=0; k<l_N; k++)	
			{
				int nr = (unsigned char)SubStr[k];
				char ch; 
				long c = nr % 16;

				nr /= 16;
				if (c<10)
				{
					ch = '0'+(char)c;
				}
				else
				{
					c-= 10; 
					ch = 'A'+(char)c;
				} 
				string[4*k+1] = ch;

				c = nr % 16;
				nr /= 16;
				if (c<10)
				{
					ch = '0'+(char)c;
				}
				else
				{
					c-= 10; 
					ch = 'A'+(char)c;
				} 
				string[4*k] = ch;

				if (k+1<l_N) 
				{
					string[4*k+2] = ',';
					string[4*k+3] = ' ';
				}
			}
			string[4*l_N-2] = 0;
		}
		else
		{
			strcpy(string, SubStr);
		}
		txt_NGram.width(wd);
		txt_NGram << string << "\t";
		txt_NGram.width(15);
		txt_NGram.precision(4);
		txt_NGram.setf(ios::fixed, ios::floatfield);
		txt_NGram << rel*100.0 << "\t";
		txt_NGram.width(7);
		txt_NGram << '\t';
		txt_NGram << cnt << '\n';
	}
	txt_NGram.close();
	HIDE_HOUR_GLASS
	// TODO: Code f�r die Behandlungsroutine der Steuerelement-Benachrichtigung hier einf�gen
	CDialog::OnOK();
}


// -----------------------------------------------------------------------------------------------------

bool CDlgNGramAnaylsis::b_saveNGramList()
{
	return b_SaveNGramList;
}

//////////////////////////////////////////////////////////////////////
// CNGram Klasse
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CNGram::CNGram()
{
}

CNGram::~CNGram()
{
	delete []NGramHashTable;
}

struct hashEntry {
	unsigned long count;
	char          SubStr[NGRAM_NMAX];
};

CNGram::CNGram(const unsigned long fileSize, const unsigned short _N, const unsigned short alphabetSize )
{
	N            = _N;
	Size         = fileSize - N+1;
	hashed       = 0;
	AlphabetSize = alphabetSize;
	if ( N <= 2 ) 
	{
		unsigned long Sz = unsigned long(pow((long)AlphabetSize, N));
		HashTableSize = min(Sz+Sz/8, Size+Size/8);
	}
	else
		HashTableSize = Size+Size/8;
	if ( 0 == (HashTableSize % 2) ) 
		HashTableSize++;
	NGramHashTable = new char[HashTableSize*(4+N)];
	memset(NGramHashTable, 0, HashTableSize*(4+N));
	individuals = 0;
	resetIterator();
}

void CNGram::add( const char *substring )
{
	unsigned long hashAddress = 0;
	for (unsigned short i=0; i<N; i++) 
	{
		char chr = substring[i];
		hashAddress = ((hashAddress<<6) +(unsigned short)chr) % HashTableSize;
	}
	hashEntry *hPtr; 
	unsigned long qP = 1;
	while ( TRUE )  
	{
		hPtr = (hashEntry*)(NGramHashTable + ((4+N)*hashAddress) );
		if ( !hPtr->count )
		{
			hPtr->count = 1;
			memcpy( hPtr->SubStr, substring, N );
			individuals++;
			break;
		}
		// in case of free Table
		if ( memcmp(hPtr->SubStr, substring, N) )
		{ // quadratic probing
			hashAddress = (hashAddress + 17*qP + 7*qP*qP) % HashTableSize; 
			qP++;
			if (qP > HashTableSize)
			{
				AfxMessageBox("Not usable hash function", MB_ICONSTOP);
				break;
			}
			if ( qP > 1000 ) AfxMessageBox("Bad hash function", MB_ICONSTOP);
		}
		else
		{
			hPtr->count++;
			break;	
		}
	}
	hashed++;
}


static int NGramSize = 1;

int compare( const void *arg1, const void *arg2 )
{
	hashEntry *he_1, *he_2;
	he_1 = (hashEntry*)arg1;
	he_2 = (hashEntry*)arg2;
	if ( he_1->count < he_2->count ) return 1;
	if ( he_1->count > he_2->count ) return -1;
    return memcmp(he_1->SubStr, he_2->SubStr, NGramSize);
}


int  CNGram::preSort( int tSize, int cnt )
{
	int j1, j2;
	hashEntry* hPtr1;
	hashEntry* hPtr2;
	char* tmp;
	tmp = new char[4+N];
	j1 = tSize-1;
	while ( 1 ) {
		hPtr1 = (hashEntry*)(NGramHashTable+j1*(4+N));
		if ( j1 && hPtr1->count == cnt ) j1--;
		else                           break;
	}
	j2 = j1;
	while ( j1 >= 0 ) 
	{
		hPtr1 = (hashEntry*)(NGramHashTable+j1*(4+N));
		if ( hPtr1->count == cnt ) {
			memcpy( tmp, (void*)hPtr1, 4+N );
			hPtr2 = (hashEntry*)(NGramHashTable+j2*(4+N));
			memcpy( (void*)hPtr1, (void*)hPtr2, 4+N );
			memcpy( (void*)hPtr2, tmp, 4+N );
			j2--;
		}
		j1--;
	}
	delete []tmp;
	return j2+1;
}

void CNGram::sort()
{
	NGramSize = N;
	int tSize = HashTableSize;
	tSize = preSort( tSize, 0 );
	qsort((void*)NGramHashTable, (size_t)tSize, 4+N, compare );
}

void CNGram::get( char *SubStr, unsigned long &cnt, double &rel )
{
	hashEntry *hPtr;
	char *charPtr = NGramHashTable + ((4+N)*iterator);
	hPtr = (hashEntry*)charPtr;
	int i;
	for (i=0; i<N; i++) SubStr[i] = hPtr->SubStr[i];
	SubStr[i] = 0;
	cnt = hPtr->count;
	rel = (double)cnt / hashed;
	iterator++;
}

