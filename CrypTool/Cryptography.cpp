/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

#include "stdafx.h"
#include "commdlg.h"
#include "CrypToolApp.h"
#include "CryptDoc.h"
#include "DlgKey.h"
#include "DlgShowKey.h"
#include "DlgKeyHex.h"
#include "Cryptography.h"
#include "DlgKeyHill5x5.h"
#include "DlgKeyHill10x10.h"
#include "HillEncryption.h"
#include "DlgShowProgress.h"
#include "DlgKeySubstitution.h"
// #include "secure.h"
#include "DlgOptionsSubstitutionAnalysis.h"
#include "DlgManualSubstAnalysis.h"
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#else
#include <iostream>
using namespace std;
#endif
#include <stdio.h>
#include "ChrTools.h"
#include "AppDocument.h"
#include "PlayfairAnalysis.h"
#include "DlgKeyPlayfair.h"
#include "DlgPlayfairAnalysis.h"
#include "RandomAnalysisTools.h"
#include "DlgHomophonicSubstitution.h"
#include "DlgKeyHomophone.h"
#include "DlgNGramAnalysis.h"
#include "DlgRandomGenerator.h"
#include "DlgPeriodicityAnalysis.h"
#include "DlgKeyPermutation.h"
#include "DlgKeyPermutationInfo.h"
#include "DlgSelectHashFunction.h"
#include "SecudeCryptography.h"
#include "DlgHashDemo.h"
#include "DlgSignatureDemo.h"
#include "DlgEntropyInfo.h"
#include "Mac.h"
// #include "DlgMac.h"
#include "DlgHMAC.h"
#include "DlgMonSubst.h"
#include "Solitaire.h"
#include "DlgSolitaire.h"

#include "DialogeMessage.h"
#include "MakeNewName.h"
#include "CrypToolTools.h"

#include "ScintillaDoc.h"
#include "ScintillaView.h"
#include "DlgKeyHexFixedLen.h"
#include "DlgBruteForceAES.h" 
#include "ListResults.h"
#include "bruteforceheap.h"

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define MAX_LAENGE_STRTEXT 16000

char *Eingabedatei;
int *MaxPermu[26];
float Fortschritt=20.0;

#pragma warning(disable : 4996)


#if 0
///////////////////////////////////////////////////////////////////////
// FIXME


int symEncProviderSecude::onErrCleanUp()
{
	int decryptionError = 0;
	struct ErrStack *err;
	err = theApp.SecudeLib.th_remove_last_error();
	if ( err->e_number == 1792 ) decryptionError = 0;
	else                         decryptionError = err->e_number;
	if(err->e_text) theApp.SecudeLib.aux_free(err->e_text);
	if(err->e_proc) theApp.SecudeLib.aux_free(err->e_proc);
	if(err->e_addr)
	{
		switch (err->e_addrtype)
		{
		case int_n:
			break;
		case OctetString_n:
			theApp.SecudeLib.aux_free_OctetString((OctetString **) &(err->e_addr));
			break;
		case BitString_n:
			theApp.SecudeLib.aux_free_BitString((BitString **) &(err->e_addr));
			break;
		case AlgId_n:
			//					theApp.SecudeLib.aux_free_AlgId((AlgId **) &(err->e_addr));
			break;
		case KeyInfo_n:
			theApp.SecudeLib.aux_free_KeyInfo((KeyInfo **) &(err->e_addr));
			break;
		case ObjId_n:
			theApp.SecudeLib.aux_free_ObjId((ObjId **) &(err->e_addr));
			break;
		case KeyBits_n:
			theApp.SecudeLib.aux_free_KeyBits((KeyBits **) &(err->e_addr));
			break;
		case PSEToc_n:
			theApp.SecudeLib.aux_free_PSEToc((PSEToc **) &(err->e_addr));
			break;
		}
	}
	theApp.SecudeLib.aux_free(err);
	return decryptionError;
}



int	symEncProviderSecude::set_key(const char *key, int keylength)
{

	return 0;
}

int	symEncProviderSecude::encrypt()
{
	// ASSERT()
	if (theApp.SecudeLib.sec_encrypt_all (&in, &out, &keyinfo)==-1)
		return onErrCleanUp()
	else
		return 0;
}

int	symEncProviderSecude::decrypt()
{
	// ASSERT()
	if (theApp.SecudeLib.sec_decrypt_all (&in, &out, &keyinfo)==-1)
		return onErrCleanUp()
	else
		return 0;
}

symEncProviderCrypTool::symEncProviderCrypTool()
{


}



#endif

//////////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void solve (int Tiefe, int DMax, int *Permu[26], int Perm[], int score, char *PatSet[100][50], char *Cipher[100][100], int *MaxScore, int *MaxPermu[26], float Delta);
int SucheLeer (int Start, int Laenge, SymbolArray& text);
bool match (char *current, char *common);

/* local functions */
void FreePar(CryptPar *par)
{
	if(!(par->flags & CRYPT_FREE_MEM)) return;

	if(par->infile) free((void *) par->infile);
	if(par->OldTitle) free((void *) par->OldTitle);
	if(par->key) free(par->key);
}

void SetDialogTitle( CDlgKey &Dialog, int IDS_STRING_ID )
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
	Dialog.SetAlternativeWindowText(pc_str);
}

void SetDialogTitle( CDlgKeyHex &Dialog, int IDS_STRING_ID )
{
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
	Dialog.SetAlternativeWindowText(pc_str);
}

// ========================================================================
/*MKraft: hier Kaskaden-bool ?bergeben*/
void CaesarAsc(const char *infile, const char *OldTitle)
{
    char outfile[1024];
    CDlgKey KeyDialog(-1);
	SymbolArray text(AppConv);

// == load INPUT
	if ( !CheckAlphabet() ) return;
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return;
	SetDialogTitle( KeyDialog, IDS_STRING_KEY_INPUT_CAESAR );

// == KeyDialog
	if(KeyDialog.Display()!=IDOK) return;
	SymbolArray Key(AppConv);
	Key.ReadString(KeyDialog.GetData());
	Key += 1;

/* MKraft
*	hier Kaskaden-bool abfragen */
// == Encryption / Decryption
	SHOW_HOUR_GLASS
	GetTmpName(outfile,"cry",".txt");
	if(KeyDialog.m_Decrypt)
		text -= Key;
	else
		text += Key;
	text.Write(outfile);
	Reformat(infile, outfile, FALSE);

// == Open the new document
	OpenNewDoc( outfile, KeyDialog.GetData(), OldTitle, IDS_STRING_CAESAR, KeyDialog.m_Decrypt );

	HIDE_HOUR_GLASS
}

void VigenereAsc(const char *infile, const char *OldTitle)
{
    char outfile[1024];
    CDlgKey KeyDialog(MAX_VIGENERE);
// == KeyDialog
		SetDialogTitle( KeyDialog, IDS_STRING_KEY_INPUT_VIGENERE );
	if(KeyDialog.Display()!=IDOK) 
		return;

	SymbolArray text(AppConv);
// == load INPUT
	if ( !CheckAlphabet() ) 
		return;
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) 
		return;

// == Encryption / Decryption
	SHOW_HOUR_GLASS
	GetTmpName(outfile,"cry",".txt");
	SymbolArray Key(AppConv);
	Key.ReadString(KeyDialog.GetData());
	if(KeyDialog.m_Decrypt)
		text -= Key;
	else
		text += Key;
	text.Write(outfile);
	Reformat(infile, outfile, FALSE);
	
// == Open the new document
	OpenNewDoc( outfile, KeyDialog.GetData(), OldTitle, IDS_STRING_VIGENERE, KeyDialog.m_Decrypt );

	HIDE_HOUR_GLASS
}

void XorBin(const char *infile, const char *OldTitle)
{
    char outfile[1024], *buffer;
    CDlgKeyHex KeyDialog(MAX_VIGENERE);
	SymbolArray text(IdConv);
	
// == load INPUT
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return;
	SetDialogTitle( KeyDialog, IDS_STRING_KEY_INPUT_XOR );

// == KeyDialog
	if(KeyDialog.Display()!=IDOK) return;

// == Encryption / Decryption
	SHOW_HOUR_GLASS
    GetTmpName(outfile,"cry",".tmp");
	SymbolArray Key(IdConv,KeyDialog.GetLen());
	buffer = KeyDialog.GetData();
	for(int i=KeyDialog.GetLen()-1;i>=0;i--) Key[i]=buffer[i];
    text ^= Key;
    text.Write(outfile);

// == Open the new document
	OpenNewDoc( outfile, KeyDialog.m_einstr, OldTitle, IDS_STRING_XOR, KeyDialog.m_Decrypt );

	HIDE_HOUR_GLASS
}

void AddBin(const char *infile, const char *OldTitle)
{
    char outfile[1024], *buffer;
    CDlgKeyHex KeyDialog(MAX_VIGENERE);
	SymbolArray text(IdConv);
	
// == load INPUT
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return;
	SetDialogTitle( KeyDialog, IDS_STRING_KEY_INPUT_ADD );

// == KeyDialog
	if(KeyDialog.Display()!=IDOK) return;

// == Encryption / Decryption
	SHOW_HOUR_GLASS
    GetTmpName(outfile,"cry",".tmp");
	SymbolArray Key(IdConv,KeyDialog.GetLen());
	buffer = KeyDialog.GetData();
	for(int i=KeyDialog.GetLen()-1;i>=0;i--) Key[i]=buffer[i];
    if(KeyDialog.m_Decrypt)
        text -= Key;
    else
        text += Key;
    text.Write(outfile);

// == Open the new document
	OpenNewDoc( outfile, KeyDialog.m_einstr, OldTitle, IDS_STRING_ADD, KeyDialog.m_Decrypt );

	HIDE_HOUR_GLASS
}

void VernamBin(const char *infile, const char *OldTitle)
{
	char fname[1024], line[1024], ftitle[1024];
    char outfile[1024], title[1024];
    CAppDocument *NewDoc;
	SymbolArray text(IdConv);

// == load INPUT
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return;
	
// == load KEY
	{
		// Initialisierung des File-Dialogs:
		CString sFileFilter;
		CString sDefName("*.txt");
		CString sTitle;
		DWORD   dwFlags(OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST);
		sFileFilter.LoadString(IDS_OPEN_DOCUMENT_FILTER);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_VERNAM_KEYFILE,pc_str,STR_LAENGE_STRING_TABLE);
		strcpy(title, OldTitle);
		if ( strlen(title) > 32 )
		{
			strcpy(title+29, "...");
		}
		sprintf(line, pc_str, title);
		sTitle = line;
		// sTitle.LoadString(IDS_STRING_VERNAM_KEYFILE);
		CFileDialog* doc;
		doc = new CFileDialog(TRUE, NULL, sDefName, dwFlags, sFileFilter);
		doc->m_ofn.lpstrTitle = sTitle;

		if(doc->DoModal()==IDOK)// Aufruf des File-Dialogs
		{			
			strcpy(ftitle, LPCTSTR (doc->GetFileName()));
			strcpy(fname, LPCTSTR (doc->GetPathName()));
			delete doc;
		}
		else
		{
			delete doc;
			return;
		}
	}

// == Encryption / Decryption
	SHOW_HOUR_GLASS
    GetTmpName(outfile,"cry",".tmp");
	SymbolArray Key(IdConv);
	Key.Read( fname );
	/* if the key size is zero, notify the user and DON'T ENCRYPT/DECRYPT anything */
	if(Key.GetSize() == 0) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_INVALID_VERNAM_KEY,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox(pc_str, MB_ICONINFORMATION);
	}
	/* else: encrypt/decrypt */
	else {
		int a = Key.GetSize();
		int b = text.GetSize();

		if(Key.GetSize() < text.GetSize()) {
			/* notify the user if the key is shorter than the text that is to be encrypted */
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SHORT_VERNAM_KEY,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox(pc_str, MB_ICONINFORMATION);
		}
		/* do the actual encryption */
		text ^= Key;
	}
	text.Write(outfile);

// == Open the new document
	CString csKey = "Datei ";
	csKey += fname;
    NewDoc = theApp.OpenDocumentFileNoMRU(outfile,csKey);
    remove(outfile);
	LoadString(AfxGetInstanceHandle(),IDS_STRING_VERNAM_ENCRYPTION_OF,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(line,pc_str,ftitle);
    if(NewDoc) {
        MakeNewName(title,sizeof(title),line,OldTitle);
        NewDoc->SetTitle(title);
    }
	HIDE_HOUR_GLASS
}


void PlayfairBin(const char *infile, const char *OldTitle)
{
 	char fileNameCleartext[128], fileNamePreformattedText[128], fileNameCiphertext[128], title[128];

	// ?berpr?fen, ob die Eingabedatei mindestens zwei g?ltige Zeichen enth?lt,
	// d.h. Zeichen, die im entsprechenden Alphabet vorkommen.
	FILE *stream;
	long infile_zeichen_anz = 0;
	int ch;
	char c;

	// Das Lesen der Datei wurde wegen Geschwindigkeitsvorteilen nachtr?glich nicht
	// mehr durch MFC implementiert. Um durch die Code?nderung keinen Absturz zu verursachen,
	// wird die Pr?fung _NUR_ bei erfolgreicher Datei?ffnung durchgef?hrt.
	if( (stream = fopen(infile, "rb" )) )
	{
		ch = fgetc(stream);	
		
		// Bis zum Erreichen des Dateiendes (EOF) wird die gesamte Datei durchsucht
		// und jedes Zeichen einzeln auf G?ltigkeit ?berpr?ft.
		int i;
		for(i=0; feof( stream ) == 0; i++ )
		{
			c = (char)ch;

			if( ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')  ) )
			{
				infile_zeichen_anz++;
				
				// An dieser Stelle ist das G?ltigkeitskriterium erreicht,
				// die for-Schleife wird demnach abgebrochen.
				if ( infile_zeichen_anz >= 2 ) break;
			}

			ch = fgetc( stream );
		
		}
	
		fclose( stream );
	
	}
	
	if (infile_zeichen_anz < 2)
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 2);
		return;
	}
	
	GetTmpName(fileNameCiphertext,"cry",".txt");

	CDlgKeyPlayfair KeyDialog(infile, fileNameCiphertext, theApp.TextOptions.getKeepCharactersNotPresentInAlphabetUnchanged(), theApp.TextOptions.getKeepUpperLowerCaseInformation());

	if(KeyDialog.Display()!=IDOK) return;

	// flomar, 04/16/2010
	// retrieve Playfair options
	PlayfairOptions playfairOptions = KeyDialog.getPlayfairOptions();
	// set file names for cleartext, preformatted text and ciphertext
	GetTmpName(fileNameCleartext, "cry", ".txt");
	GetTmpName(fileNamePreformattedText, "cry", ".txt");
	GetTmpName(fileNameCiphertext, "cry", ".txt");
	playfairOptions.fileNameCleartext = fileNameCleartext;
	playfairOptions.fileNamePreformattedText = fileNamePreformattedText;
	playfairOptions.fileNameCiphertext = fileNameCiphertext;

	// complete key as string (KEY, SEPARATOR1, SEPARATOR2)
	CString stringCompleteKey;
	stringCompleteKey.Append("KEY: ");
	stringCompleteKey.Append(KeyDialog.GetData());
	stringCompleteKey.Append(", SEPARATOR1: ");
	stringCompleteKey.Append(playfairOptions.separator1);
	stringCompleteKey.Append(", SEPARATOR2: ");
	stringCompleteKey.Append(playfairOptions.separator2);
	stringCompleteKey.Append(", MATRIXSIZE: ");
	CString matrixSize; matrixSize.Format("%d", playfairOptions.matrixSize);
	stringCompleteKey.Append(matrixSize);
	if(playfairOptions.ignoreDoubleCharactersInKey)
		stringCompleteKey.Append(STR_OPT_IGNORE_DUPLICATE_LETTERS_IN_KEY);
	if(playfairOptions.separateDoubleCharactersOnlyWithinPairs)
		stringCompleteKey.Append(STR_OPT_SEPERATE_DUPLICATE_ONLY_WITHIN_PAIRS);

	// apply Playfair with the desired options
	KeyDialog.m_Alg->ApplyPlayfair(playfairOptions);

	// show the preformatted text (only if we were ENcrypting, not DEcrypting)
	if(!playfairOptions.decryption) {
		CScintillaDoc *preformattedTextDocument = (CScintillaDoc*)(theApp.OpenDocumentFileNoMRU(playfairOptions.fileNamePreformattedText));
		CString preformattedTextDocumentTitle;
		preformattedTextDocumentTitle.Format(IDS_STRING_PLAYFAIR_PREFORMAT, OldTitle);
		preformattedTextDocument->SetTitle(preformattedTextDocumentTitle);
		preformattedTextDocument->activatePlayfairView();
	}

	// show the ciphertext (including key and full title)
	CScintillaDoc *resultTextDocument = (CScintillaDoc*)(theApp.OpenDocumentFileNoMRU(playfairOptions.fileNameCiphertext, stringCompleteKey));
	GetNewDocTitle(stringCompleteKey.GetBuffer(), OldTitle, IDS_PLAYFAIR, title, 128, playfairOptions.decryption);
	CString resultTextDocumentTitle = title;
	resultTextDocument->SetTitle(resultTextDocumentTitle);
	resultTextDocument->activatePlayfairView();
	
	HIDE_HOUR_GLASS
}

void PlayfairAnalyse(const char *infile, const char *OldTitle)
{
	char outfile[128], title[128];
	GetTmpName(outfile,"cry",".tmp");
	class CDlgPlayfairAnalysis KeyDialog(infile,outfile,theApp.TextOptions.getKeepCharactersNotPresentInAlphabetUnchanged(),theApp.TextOptions.getKeepUpperLowerCaseInformation());

	if(KeyDialog.Display()!=IDOK) return;

	// retrieve Playfair options
	PlayfairOptions playfairOptions = KeyDialog.getPlayfairOptions();
	// set file name for result text
	GetTmpName(outfile,"cry",".txt");
	playfairOptions.fileNameCiphertext = outfile;

	// complete key as string (KEY, SEPARATOR1, SEPARATOR2)
	CString stringCompleteKey;
	stringCompleteKey.Append("KEY: ");
	stringCompleteKey.Append(KeyDialog.GetData());
	stringCompleteKey.Append(", SEPARATOR1: ");
	stringCompleteKey.Append(playfairOptions.separator1);
	stringCompleteKey.Append(", SEPARATOR2: ");
	stringCompleteKey.Append(playfairOptions.separator2);
	stringCompleteKey.Append(", MATRIXSIZE: ");
	CString matrixSize; matrixSize.Format("%d", playfairOptions.matrixSize);
	stringCompleteKey.Append(matrixSize);
	if(playfairOptions.ignoreDoubleCharactersInKey)
		stringCompleteKey.Append(STR_OPT_IGNORE_DUPLICATE_LETTERS_IN_KEY);
	if(playfairOptions.separateDoubleCharactersOnlyWithinPairs)
		stringCompleteKey.Append(STR_OPT_SEPERATE_DUPLICATE_ONLY_WITHIN_PAIRS);

	// apply Playfair with the desired options
	KeyDialog.m_Alg->ApplyPlayfair(playfairOptions);

	// show the new document
	CScintillaDoc *resultTextDocument = (CScintillaDoc*)(theApp.OpenDocumentFileNoMRU(outfile, stringCompleteKey));
	GetNewDocTitle(stringCompleteKey.GetBuffer(), OldTitle, IDS_PLAYFAIR, title, 128, playfairOptions.decryption);
	CString resultTextDocumentTitle = title;
	resultTextDocument->SetTitle(resultTextDocumentTitle);
	resultTextDocument->activatePlayfairView();

	HIDE_HOUR_GLASS
}


void Hill(const char *infile, const char *OldTitle)
{
   CKeyHillBase hillbase( HILL_RANGE );
   if ( IDOK == hillbase.run() )
   {
      char *cbuffer;
      int   lbuffer;

      if ( !readSource( infile, cbuffer, lbuffer, TRUE ) )
      {
         if ( !lbuffer )
         {
		      Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		      return;
         }

         SHOW_HOUR_GLASS

         CHillEncryption he( (const char*)theApp.TextOptions.getAlphabet(), hillbase.dim );
         if ( !hillbase.cryptMode ) // encrypt
         {
            he.set_enc_mat( *hillbase.HillMat );
            he.set_plaintext( cbuffer );
            delete []cbuffer;

            he.verschluesseln();

      		cbuffer = new char[he.get_laenge_cipher()+1];
            he.get_ciphertext(cbuffer);
         }
         else
         {
            he.set_dec_mat( *hillbase.HillMat );
            he.set_ciphertext( cbuffer );
            delete []cbuffer;

            he.entschluesseln();

      		cbuffer = new char[he.get_laenge_plain()+1];
            he.get_plaintext(cbuffer);

         }

         // ENCODE KEY TO STR
         CString cs_keystr;
         hillbase.keyToStr( cs_keystr );

	      // STORE OUTPUT
         char outfile[1024];
	      GetTmpName(outfile,"cry",".txt");
         ofstream out(outfile);
	      out << cbuffer;
	      out.close();
	      delete []cbuffer;

         // Ver- bzw. Entschluesselte Daten aus Hill-Klasse auslesen und in neuem Fenster anzeigen
         // und danach die temporaere Datei wieder loeschen
         Reformat(infile, outfile, FALSE);
         OpenNewDoc( outfile, cs_keystr, OldTitle, IDS_STRING_HILL, hillbase.cryptMode, SCHLUESSEL_QUADRATISCH );

         if ( hillbase.verbose )
	      {
		      GetTmpName(outfile,"cry",".txt");
		      ofstream verboseOut(outfile);

            CString out;
		      he.OutputHillmatrix(out);
		      verboseOut << out.GetBuffer(0);
		      verboseOut.close();

		      CAppDocument *NewDoc;
		      NewDoc = theApp.OpenDocumentFileNoMRU(outfile);
		      remove(outfile);
		      if (NewDoc) {
			      char title[128]; 
			      GetNewDocTitle(cs_keystr, OldTitle, IDS_STRING_HILL_DETAILS, title, 128, hillbase.cryptMode, SCHLUESSEL_QUADRATISCH );
			      NewDoc->SetTitle(title);
			      CView* CView_hilf = ((CMDIFrameWnd*)theApp.m_pMainWnd)->MDIGetActive()->GetActiveView();
			      ((CScintillaView*)CView_hilf)->OnViewFontCourier10();
		      }
	      }

   	   HIDE_HOUR_GLASS
      }
   }
}


void Entropy( const char* infile, SymbolArray &text, const char* oldtitle)
{
	LoadText( infile, text );
	if ( !CheckTextSize( text ) ) return;
	int nalph = text.GetModulus();
	int nsymbol = 0;

	SHOW_HOUR_GLASS

	NGram distr(text);
	for (int i = 0; i < nalph; i++) 
		if (distr[i])
			nsymbol++;

	CDlgEntropyInfo entropyInfo;
	entropyInfo.SetParameter( oldtitle, nalph, nsymbol, log2(nalph), distr.Entropie());
	entropyInfo.DoModal();	

	HIDE_HOUR_GLASS
}

void EntropyASCII(const char *infile, const char *OldTitle)
{
    SymbolArray text(AppConv);
	Entropy( infile, text, OldTitle );
}

void EntropyBin(const char *infile, const char *OldTitle)
{
    SymbolArray text(IdConv);
	Entropy( infile, text, OldTitle );
}


int deltas[]={1,2,5,10,20,25,50,100,200,250,500,1000};

UINT Vitanycorr(PVOID p)
{
	CryptPar *par;
	char outfile[128];

	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ANALYZE_VITANY,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Display(pc_str);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_END_ANALYZE_VITANY,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	class CRandomAnalysisTools analyse((char *)par->infile);
	analyse.WriteAnalyse(outfile,par->OldTitle);

	if((par->flags & CRYPT_DO_PROGRESS ) && (theApp.fs.m_canceled == 0)) {
		while(theApp.fs.Set(100)!=100) Sleep(100);
		theApp.fs.cancel();
	}

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	par->flags |= CRYPT_DONE;
	FreePar(par);

	return 0;
}


// === PERIODENANALYSE
// September 2000 - Peter Gruber Entwurf
// Oktober 2000 - Henrik Koy Fehlerbeseitigung
// Januar 2001 - Thomas Gauweiler: Fehlerbeseitigung & linearer Algorithmus
// Juni 2001 - Thomas Gauweiler: neue Ausgabe mit Speichern in Datei
// 
UINT Periode(PVOID p)
{
	CryptPar *par;

	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PERIOD_ANALYSIS,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Display(pc_str);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PERIOD_ANALYSIS_D,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	CDlgPeriodicityAnalysis POutp;
	POutp.OldTitle = strdup(par->OldTitle);
	class CRandomAnalysisTools analyse((char *)par->infile);
	int isPeriode;
	OPENFILENAME ofn;
	// Ausgabe der Periodenl?nge
	char fname[257], ftitle[128], fboxtitle[128];

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS

	// Initialisierung des Fortschrittbalkens
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PERIOD_ANALYSIS_D,pc_str,STR_LAENGE_STRING_TABLE);
	theApp.fs.Set(0,pc_str);

	// Thomas' Variante
	// eigentliche Periodenanalyse
	isPeriode = analyse.FindPeriod();

	// Vollst?ndigkeit des Fortschrittbalkens anzeigen
	theApp.fs.Set(100,pc_str);

	if((par->flags & CRYPT_DO_PROGRESS ) && (theApp.fs.m_canceled == 0)) {
		while(theApp.fs.Set(100)!=100) Sleep(100);
		theApp.fs.cancel();
	}
	while(theApp.fs.m_displayed) Sleep(10);

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	par->flags |= CRYPT_DONE;

	FreePar(par);
	p = NULL;


	// prepare the fileselectorbox dialog
	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = AfxGetMainWnd()->m_hWnd;
	ofn.hInstance = AfxGetInstanceHandle();
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_FSBDTITLE,pc_str,STR_LAENGE_STRING_TABLE);
	ofn.lpstrTitle = fboxtitle;	fboxtitle[0] = '\0';
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_FSBDTITLE,fboxtitle,128);
	ofn.Flags = OFN_HIDEREADONLY;
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_FILENAME,pc_str,STR_LAENGE_STRING_TABLE);
	ofn.lpstrFile = fname;	strcpy(fname, pc_str);
	ofn.nMaxFile = sizeof(fname)-1;
	ofn.lpstrFileTitle = ftitle;	ftitle[0] = '\0';
	ofn.nMaxFileTitle = sizeof(ftitle);

	POutp.zahlenanalyse = &analyse;
	if ( isPeriode > 0 )
	{
		POutp.DoModal();
	}


/*
	if ((isPeriode > 0) && (POutp.DoModal()==IDOK) && (GetSaveFileName(&ofn)) && (fname[0]!='\0'))
	{  // Ausgabewerte speichern
		FILE *out;
		out=fopen(fname,"w");

		LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_TITLE,pc_str,STR_LAENGE_STRING_TABLE);
		fprintf(out,pc_str, "");
		LoadString(AfxGetInstanceHandle(),IDS_STRING_PA_HEADER,pc_str,STR_LAENGE_STRING_TABLE);
		fprintf(out,pc_str);

		int maxtxtlen = (analyse.periodResults[analyse.cnt_periodResults-1].length<PA_MAXPRINTLENGTH) ? analyse.periodResults[analyse.cnt_periodResults-1].length : PA_MAXPRINTLENGTH;
//			for (int i=0; i<analyse.cnt_periodResults; i++) {
		for (int i=analyse.cnt_periodResults-1; i>=0; i--) {
			line[0] = '\0';
			fprintf(out,"%d\t", analyse.cnt_periodResults-i);
			fprintf(out,"%d\t", analyse.periodResults[i].offset+1);
			fprintf(out,"%d\t", analyse.periodResults[i].length);
			fprintf(out,"%d\t\t", analyse.periodResults[i].repeated+1);

			pc_str1[0]='\0';
			char s [PA_MAXPRINTLENGTH*4+10]; s[0]='\0';
			int len = (analyse.periodResults[i].length)<PA_MAXPRINTLENGTH ? analyse.periodResults[i].length : PA_MAXPRINTLENGTH;
			for (int k=0; k<len; k++) {
				s[k] = IsText(analyse.periodResults[i].str[k]) ? analyse.periodResults[i].str[k] : '.';
				sprintf(pc_str1,"%s %02.2X", pc_str1, (unsigned char)analyse.periodResults[i].str[k]);
			}
			s[len]='\0';

			fprintf(out,"%s\t", s);
			for (int j= (maxtxtlen - analyse.periodResults[i].length+7) / 8; j>0; j--) fprintf(out,"\t");
			fprintf(out,"%s\n", pc_str1);
		}
		fclose(out);

	}
*/
	// Keine Periode gefunden
	if (isPeriode == 0)
	{
		Message(IDS_STRING_NO_PERIOD_FOUND, MB_ICONINFORMATION);
	}

	// Zu analysierende Textdatei zu kurz
	if (isPeriode < 0)
	{
		Message(IDS_STRING_ERR_PERIOD_ANALYSIS_TEXTLENGTH, MB_ICONEXCLAMATION);
	}


	return 0;
}



UINT Autocorr(PVOID p)
{
    int i, j, n, r,fsize;
	char line[256], name[128], name2[128];
	CAppDocument *NewDoc = NULL;
	CryptPar *par;
	CFile f;
	FILE *fo;

	r=0;
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS

    SymbolArray text(IdConv);
	if(par->flags & CRYPT_ASCII)
		text.SetConverter((class Converter &) AppConv);

	// FLAG f?r Fortschrittsanzeiger
	if(par->flags & CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOCORRELATION,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Display(pc_str);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOCORRELATION_COMPLETE,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

   	SCorrelation *tx;
	if(par->result) {
		tx = (SCorrelation *) par->result;
		n = fsize = tx->GetSize();
	}
	else {
		text.Read(par->infile);
		fsize = text.GetSize();
		n =	min(fsize/2,200);

		tx = new SCorrelation(text,n);	// Auto-Korrelation 1..200 betrachten,
	}

	if(fsize < 8) { // Mindestl?nge 8 Zeichen
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 8);
		r=1;
		goto cancel;
	}

	if((par->flags & (CRYPT_DISPLAY_BG | CRYPT_DISPLAY_IMMEDIATE)) !=0) {
		GetTmpName(name,"cry",".plt");
		fo = fopen(name,"wt");

		for(i=1;i<n;i++) {
			j = (int) (*tx)[i];
			if(theApp.PlotOptions.m_relativ)
				fprintf(fo,"%f\n",(double)j*100/fsize);   /* relative ?bereinstimmung*/
			else
				fprintf(fo,"%d\n",j);
			if(((i%5)==0) && (par->flags & CRYPT_DO_PROGRESS)) {
					theApp.fs.Set((i*100)/n);
					if(theApp.fs.m_canceled) {
						fclose(fo);
						remove(name);
						r=1;
						goto cancel;
					}
			}
		}
		fclose(fo);

		// get the tmp name without file extension
		strcpy(name2, name);
		name2[strlen(name)-4] = 0x0;
	
		LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOCORRELATION_OF,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName(line,sizeof(line),pc_str,par->OldTitle);
	
	
		if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
			CArchive ar( &f, CArchive::store);
			CString s1 = line;
				LoadString(AfxGetInstanceHandle(),IDS_STRING_SHIFT,pc_str,STR_LAENGE_STRING_TABLE);
			CString s2 = pc_str;
			if (theApp.PlotOptions.m_relativ)
				LoadString(AfxGetInstanceHandle(),IDS_REL_MATCH,pc_str,STR_LAENGE_STRING_TABLE);
			else
				LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_MATCHING_CHARACTERS,pc_str,STR_LAENGE_STRING_TABLE);
			CString s3 = pc_str;

			ar << s1 << s2 << s3;
	
			// CONTINUOUS  X_CHAR  Y_CHAR
			ar << (int)1 << '0' << '0';
				
			ar.Close(); f.Close();

		}

		if(par->flags & (CRYPT_DISPLAY_BG | CRYPT_DISPLAY_IMMEDIATE)) {
			theApp.ThreadOpenDocumentFileNoMRU(name,line);
		}
	}
	else {
		for(i=1;i<n;i++) {
			j = (int) (*tx)[i];
			if((par->flags & CRYPT_DO_PROGRESS) && (i%5==0)) theApp.fs.Set((i*100)/n);
			if((par->flags & CRYPT_DO_PROGRESS) && (theApp.fs.m_canceled)) goto cancel;
		}
	}


cancel:


	if(!par->result) {
		free(tx);
	}

	if((par->flags & CRYPT_DO_PROGRESS ) && (theApp.fs.m_canceled == 0)) {
		while(theApp.fs.Set(100)!=100) Sleep(100);
		theApp.fs.cancel();
	}

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	par->flags |= CRYPT_DONE;
	FreePar(par);

	return r;
}

UINT FloatingEntropy(PVOID p)
// Berechnung der "gleitenden Entropie" in einem Fenster (Default: 64 Bytes, Max 256)
// Anzeige als Diagramm ?hnlich der Autokorrelation
{
    int i, n, r, l;
	char line[256], name[128], name2[128];
	unsigned char buffer[1024], c;
	int num[256], g;
	double ld[257], e;
	CAppDocument *NewDoc = NULL;
	CryptPar *par;
	CFile f;
	FILE *fi, *fo;
	int winsize = 64;

	r=0;
	winsize = 64;
	par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS

	if(par->flags & CRYPT_DO_PROGRESS) {
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FLOATING_FREQ,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Display(pc_str);
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FLOATING_FREQ_FINISHED,pc_str,STR_LAENGE_STRING_TABLE);
		theApp.fs.Set(0,pc_str);
	}
	n = filesize(par->infile);
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	fi = fopen(par->infile,"rb");
	l = fread(buffer, 1, sizeof(buffer), fi);
	fo = NULL;

	if(l<winsize) {
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, winsize);
		r=1;
		goto cancel;
	}

	// initialisierung von ld
	ld[0]=0.0;
	for(i=min(257,winsize);i>0;i--) {
//		t = ((double)i) / ((double)winsize);  // verwende Logarithmus
//		ld[i] = -t * log(t) / log(2);
		ld[i] = 1;	// z?hlen der unterschiedlichen Zeichen
	}

	// initiale Bef?llung des Arrays num
	for(i=0;i<256;i++) num[i] = 0;
	for(i=0;i<winsize;i++) num[buffer[i]]++;

	// initialisieren der Entropie
	for(e=i=0;i<256;i++) e += ld[num[i]];

	GetTmpName(name,"cry",".plt");
	fo = fopen(name,"wt");

	// ganze Datei abarbeiten
	g = 0;
	do {
		for(i=winsize;i<l;i++) {
			// Entropie in Datei schreiben
			fprintf(fo,"%g\n",e);
			if(((g%5)==0) && (par->flags & CRYPT_DO_PROGRESS)) {
					theApp.fs.Set((g*100)/n);
					if(theApp.fs.m_canceled) {
						fclose(fo);
						remove(name);
						r=1;
						goto cancel;
					}
			}
			// Entropie updaten
			c = buffer[i-winsize];
			e -= ld[num[c]];
			num[c]--;
			e += ld[num[c]];
			c = buffer[i];
			e -= ld[num[c]];
			num[c]++;
			e += ld[num[c]];
			g++;
		}
		memcpy(buffer,buffer+l-winsize,winsize);
		l = winsize + fread(buffer+winsize, 1, sizeof(buffer)-winsize, fi);
	} while(l>winsize);

	fclose(fo);

	// get the tmp name without file extension
	strcpy(name2, name);
	name2[strlen(name)-4] = 0x0;
	
	//////// string name aendern
	LoadString(AfxGetInstanceHandle(),IDS_STRING_MSG_FLOATING_FREQ_OF,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName(line,sizeof(line),pc_str,par->OldTitle);
	
	
	if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
		CArchive ar( &f, CArchive::store);
		CString s1 = line;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FLOATING_ENTROPY_SEQUENCE_POSITION,pc_str,STR_LAENGE_STRING_TABLE);
		CString s2 = pc_str;
		LoadString(AfxGetInstanceHandle(),IDS_FLOATING_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
		CString s3 = pc_str;

		ar << s1 << s2 << s3;
	
		// CONTINUOUS  X_CHAR  Y_CHAR
		ar << (int)1 << '0' << '0';
				
		ar.Close(); f.Close();

	}

	if(par->flags & (CRYPT_DISPLAY_BG | CRYPT_DISPLAY_IMMEDIATE)) {
		theApp.ThreadOpenDocumentFileNoMRU(name,line);
	}


cancel:

	fclose(fi);

	if((par->flags & CRYPT_DO_PROGRESS ) && (theApp.fs.m_canceled == 0)) {
		while(theApp.fs.Set(100)!=100) Sleep(100);
		theApp.fs.cancel();
	}

	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	par->flags |= CRYPT_DONE;
	FreePar(par);

	return r;
}

void HistogramASCII(const char *infile, const char *OldTitle)
{
    char line[256], name[128], name2[128], numbuff[20];
	CFile f;

	SHOW_HOUR_GLASS

    SymbolArray text(AppConv);

    text.Read(infile);
	if ( !CheckTextSize( text ) ) return;

    NGram distr(text);
	GetTmpName(name,"cry",".plt");

	int len = text.GetSize();
	LoadString(AfxGetInstanceHandle(),IDS_STRING_ASCII_HISTOGRAM_OF,pc_str,STR_LAENGE_STRING_TABLE);
    MakeNewName2(line,sizeof(line),pc_str,_itoa(len, numbuff, 10),OldTitle);

	distr.Show(OStream(name)<< OStream::Title(0) << OStream::Description(0) << OStream::Summary(0) << OStream::Percent());
	// get the tmp name without file extension
	strcpy(name2, name);
	name2[strlen(name)-4] = 0x0;

	if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
		CArchive ar( &f, CArchive::store);
		CString s1 = line;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_VALUE,pc_str,STR_LAENGE_STRING_TABLE);
		CString s2 = pc_str;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
		CString s3 = pc_str;

		// headline <<  x_label << y_label
		ar << s1 << s2 << s3;
		// CONTINUOUS  X_CHAR  Y_CHAR
		ar << (int)0 << (char)0x40 << (char)0x30;
		ar.Close(); f.Close();
	}

    theApp.ThreadOpenDocumentFileNoMRU(name,line);
	HIDE_HOUR_GLASS
}



void HistogramBin(const char *infile, const char *OldTitle)
{
    char line[256],name[128], name2[128], numbuff[20];
	CFile f;

	SHOW_HOUR_GLASS

    SymbolArray text(IdConv);
    text.Read(infile);
	if ( !CheckTextSize( text ) ) return;

    NGram distr(text);
	GetTmpName(name,"cry",".plt");

	int len = text.GetSize();
	LoadString(AfxGetInstanceHandle(),IDS_STRING_BINARY_HISTOGRAM_OF,pc_str,STR_LAENGE_STRING_TABLE);
    MakeNewName2(line,sizeof(line),pc_str,_itoa(len, numbuff, 10),OldTitle);
	distr.Show(OStream(name)<< OStream::Title(0) << OStream::Description(0) << OStream::Summary(0) << OStream::Percent());

	// get the tmp name without file extension
	strcpy(name2, name);
	name2[strlen(name)-4] = 0x0;

	if( f.Open( name2, CFile::modeCreate | CFile::modeWrite ) ) {
		CArchive ar( &f, CArchive::store);
		CString s1 = line;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_VALUE,pc_str,STR_LAENGE_STRING_TABLE);
		CString s2 = pc_str;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_FREQUENCY,pc_str,STR_LAENGE_STRING_TABLE);
		CString s3 = pc_str;

		// headline <<  x_label << y_label
		ar << s1 << s2 << s3;

		// CONTINUOUS  X_CHAR  Y_CHAR
		ar << (int)0 << '0' << '0';
		ar.Close(); f.Close();
	}

    theApp.ThreadOpenDocumentFileNoMRU(name,line);
	HIDE_HOUR_GLASS
}


int AnalyseMonoManual(const char *infile, const char *OldTitle)
{
	int vore[26], nache[26], i;   
	for (i=0; i<26; i++){
		nache[i]=0;
		vore[i]=0;
	}

	// Umlaute und Zeilenumbrueche umwandeln
	char outfile2[1024];
	GetTmpName(outfile2,"cry",".txt");
	FILE *stream, *stream2;
		
	int ch;
	if( (stream = fopen( infile, "rt" )) == NULL )
		exit( 0 );
	if( (stream2 = fopen( outfile2, "wt" )) == NULL )
		exit( 0 );

	while ( feof( stream ) == 0 )
	{
		ch = fgetc( stream );
		switch(ch) {
		case (-1):
			break;
		case ('\n'):					// Zeilenumbruch
			fwrite (" \n", 1, 2, stream2);
			break;
		case (252):
			fwrite ("ue", 1, 2, stream2);
			break;
		case (220):
			fwrite ("Ue", 1, 2, stream2);
			break;
		case (246):
			fwrite ("oe", 1, 2, stream2);
			break;
		case (214):
			fwrite ("Oe", 1, 2, stream2);
			break;
		case (228):
			fwrite ("ae", 1, 2, stream2);
			break;
		case (196):
			fwrite ("Ae", 1, 2, stream2);
			break;
		case ('?'):
			fwrite ("ss", 1, 2, stream2);
			break;
		default:
			fputc (ch, stream2);
			break;
		}
	}
	fclose (stream);
	fclose (stream2);
	
	Eingabedatei=outfile2;
	SymbolArray text(AlphaSpaceConv);
	text.Read(outfile2);
	int Laenge=text.GetSize(); // L?nge des eingelesenen Textes
	// int Leerzeichen;		// FIXME: not used (Position des n?chsten Leerzeichens)
	int Start=0;			// Merkt sich, wo das letzte Leerezichen gefunden wurde
	char *current=(char*) malloc (50);

	// Initialisieurng vom Permu und MaxPermu
	// Permu speichert die gerade untersuchte Substitution und MaxPermu die Substitution,
	// die bisher das beste Ergebnis brachte.
	int *Permu[26];//,*MaxPermu[26];
	//int *Permu[26];
	for (i=0; i<26; i++){
		Permu[i]=(int*)malloc(sizeof(int));
		*Permu[i]=-1;
		MaxPermu[i]=(int*)malloc(sizeof(int));
		*MaxPermu[i]=-1;
	}

	/* Manuelle Bearbeitung des Textes:
	   Das Nachbearbeitungsfenster wird aufgerufen. Im oberen Teil des Fensters werden
	   jedoch noch keine Zuordnungen vorgenommen (alles mit '*' initialisiert).
	   Der Benutzer kann Zuordnungen eingeben. Die daraus resultierende aktuelle
	   Substitution wird benutzt, um den zu bearbeitenden Ciphertext zu entschl?sseln.
	   Das Resultat wird im unteren Texfenster dargestellt.				*/

	CDlgManualSubstAnalysis Dialogbox;
	if (Dialogbox.DoModal()==IDOK){
		// Entschl?sseln und Ausgabe des Textes
		char outfile[1024], title[1024];
		GetTmpName(outfile,"cry",".txt");

		Laenge=text.GetSize();

		LPTSTR string = new TCHAR[Laenge + 1];
		int len;

		for (len=i=0 ; i<Laenge; i++){
			if (text[i]!=26){
				if (*MaxPermu[text[i]]!=-1){
					string[len++]=(char)(*MaxPermu[text[i]]);
				}
				else {
					string[len++]=(char)text[i]+'a';}
			}
		}
		string[len]=0;

		char *Ausgabe2=string;
		// Kopieren von char *Ausgabe2 in die Datei <outfile> (mit Hilfe der Secude Funktionen)
		OctetString help;
		help.noctets=strlen(Ausgabe2);
		help.octets=Ausgabe2;
		theApp.SecudeLib.aux_OctetString2file(&help,outfile,2);
		delete string;

		ForceReformat(outfile2, outfile, TRUE);

		// Berechnung der (Teil-)Permutation zur Anzeige im Titel
		char schluessel[27];
		for (i=0; i<26;i++)
		{
			schluessel[i] = '*';
		}
		for (i=0; i<26;i++)
		{
			if (*MaxPermu[i] != -1)
			{
				schluessel[(*MaxPermu[i])-'A'] = i+'A';
			}
		}
		schluessel[26]='\0';

		LoadString(AfxGetInstanceHandle(),IDS_STRING_POSSIBLE_PLAINTEXT_OF,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName2(title,sizeof(title),pc_str,schluessel,OldTitle);
		theApp.ThreadOpenDocumentFileNoMRU(outfile, title, schluessel);
		remove(outfile2);	
	}
	// Den allokierten Speicherplatz von current, Permu und MaxPermu freigeben
	free (current);
	for (i=0; i<26; i++){
		free (Permu[i]);
		free (MaxPermu[i]);
	}
	return 0;
}


/* Funktion zur monoalphabetischen Ver- und Entschl?sselung			*/
void Mono(const char *infile, const char *OldTitle) {

	CFile inputFile(infile, CFile::modeRead);
	const int inputFileLength = inputFile.GetLength();

	// we store the original file contents in "sourceBuffer"
	char *sourceBuffer = new char[inputFileLength + 1];
	// later on we put the encryption/decryption result into "targetBuffer"
	char *targetBuffer = new char[inputFileLength + 1];
	memset(sourceBuffer, 0, inputFileLength + 1);
	memset(targetBuffer, 0, inputFileLength + 1);
	inputFile.Read(sourceBuffer, inputFileLength);
	inputFile.Close();

	// dump an error message and return if the file doesn't contain at least one character
	if(!inputFileLength) {
		CString message;
		message.LoadString(IDS_STRING_ERR_INPUT_TEXT_LENGTH);
		message.Format(message, 1);
		AfxMessageBox(message, MB_ICONEXCLAMATION);
		return;
	}

	// return if the user cancelled the dialog
	CDlgMonSubst dlgMono;
	if(dlgMono.DoModal() != IDOK) {
		return;
	}

	// get the currently configured alphabet
	CString alphabet = theApp.TextOptions.getAlphabet();

	// this might be helpful later on (used as workaround)
	CString lowerAlphabet = alphabet; lowerAlphabet.MakeLower();
	CString upperAlphabet = alphabet; upperAlphabet.MakeUpper();

	// get the complete key (see declaration of getKey() for details)
	CString key = dlgMono.getKey();
	const int keyLength = key.GetLength();

	// we'll need this when writing the target file
	unsigned int targetBufferLength = 0;

	// in case of a decryption, we simply switch key and alphabet and then process it as if it were an encryption
	if(!dlgMono.m_cryptDirection) {
		CString temp = key;
		key = alphabet;
		alphabet = temp;
	}

	// go through all characters of the text
	for(int i=0; i<inputFileLength; i++) {
		// check if the current character is part of the alphabet
		if(alphabet.Find(sourceBuffer[i]) != -1) {
			// apply the encryption
			targetBuffer[targetBufferLength++] = key[alphabet.Find(sourceBuffer[i])];
		}
		else {
			// if the option below is not set, we discard non-alphabet characters
			if(!theApp.TextOptions.getKeepCharactersNotPresentInAlphabetUnchanged()) {
				continue;
			}
			else {
				// barring case-sensitivity, we might still get a match here... so check that
				if(!theApp.TextOptions.getDistinguishUpperLowerCase()) {
					if(lowerAlphabet.Find(sourceBuffer[i]) != -1) {
						if(theApp.TextOptions.getKeepUpperLowerCaseInformation()) {
							// interpret the character as upper case, then process it and implicitly convert it back to lower case
							targetBuffer[targetBufferLength++] = tolower(key[alphabet.Find(toupper(sourceBuffer[i]))]);
						}	
						else {
							// just like above, but we don't convert back
							targetBuffer[targetBufferLength++] = key[alphabet.Find(toupper(sourceBuffer[i]))];
						}	
					}
					else if(upperAlphabet.Find(sourceBuffer[i]) != -1) {
						if(theApp.TextOptions.getKeepUpperLowerCaseInformation()) {
							// interpret the character as lower case, then process it and implicitly convert it back to upper case
							targetBuffer[targetBufferLength++] = toupper(key[alphabet.Find(tolower(sourceBuffer[i]))]);
						}	
						else {
							// just like above, but we don't convert back
							targetBuffer[targetBufferLength++] = key[alphabet.Find(tolower(sourceBuffer[i]))];
						}
					}
					else {
						// at that point we don't touch the character
						targetBuffer[targetBufferLength++] = sourceBuffer[i];
					}
				}
				else {
					// at that point we don't touch the character
					targetBuffer[targetBufferLength++] = sourceBuffer[i];
				}
			}
		}
	}

	// we can free the source buffer here
	delete sourceBuffer;

	// write the target buffer to a file
	char outfile[CRYPTOOL_PATH_LENGTH];
	GetTmpName(outfile, "cry", ".txt");
	CFile outputFile(outfile, CFile::modeCreate | CFile::modeWrite);
	outputFile.Write(targetBuffer, targetBufferLength);
	outputFile.Close();

	// now we can free the target buffer
	delete targetBuffer;

	CDocument *NewDoc = theApp.OpenDocumentFileNoMRU(outfile,dlgMono.getKey());
	if(NewDoc) 
	{
		// oh my god...
		char title[4096];
		if(!dlgMono.m_cryptDirection)
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		else
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		// LoadString(AfxGetInstanceHandle(),IDS_STRING_SUBSTITUTION,pc_str,STR_LAENGE_STRING_TABLE);
		// Der eingegebene Schluessel ist zur Ausgabe in der Titelzeile nicht geeignet,
		// da bei der Analyse nur die Permutation gefunden werden kann, 
		// nicht jedoch das Schl?sselwort. 
		// Wegen der Konsistenz wird hier nur die Permutation ausgegeben 
		MakeNewName3(title,sizeof(title),pc_str1, dlgMono.typeOfEncryption ,OldTitle,dlgMono.getKey());
		NewDoc->SetTitle(title);
	}
}

UINT AnaSubst(PVOID p) {
/*  Diese Funktion dient zum Brechen einer monoalphabetischen Substitution.
	Sie arbeitet mit deutschen und englischen Standardtexten.
	Die Leerzeichen m?ssen im Ciphertext enthalten sein.

	Die Analyse basiert auf einer Liste mit den h?ufigsten W?rtern der jeweiligen 
	Sprache. Im englischen ist die Wahrscheinlichkeit, da? ein zuf?llig aus einem
	Standardtext herausgegriffenes Wort in dieser Liste enthalten ust gerade 0,5.

	Die W?rter des Ciphertextes werden (ihrem Muster nach) mit den W?rtern in der 
	Liste verglichen. Bei jeder m?glichen Zuordnung ergibt sich daraus eine
	(partielle) Substitution. Durch einen Suchbaum wird diejenige Substitution
	ermittelt, die mit den meisten partiellen Substitutionen vertr?glich ist.

	Quelle: George W. Hart
		   To Decode Short Cryptograms
		   Communications of the ACM, Sept 1994, Vol 37, No.4
*/
	
	CryptPar *par;
	//Eingabedatei=infile;
	int vore[26], nache[26], anfang[26], ende[26],i,j;
	for (i=0; i<26; i++){
		nache[i]=0;
		vore[i]=0;
	}

	// Anzeigen des Auswahlfensters f?r die gew?nchte Analysemethode
	CDlgOptionsSubstitutionAnalysis Dialog;

	par = (CryptPar *) p;

	// **********************************************************************************
	// **********************************************************************************
	// **********************************************************************************
	int Grenze = 0;
	char **common = 0;

	// the list of common words
	std::vector<std::string> wordlist;

	if(Dialog.DoModal()== IDOK) {		
		// flomar, July 2012: instead of the old approach with hard-coded words we give 
		// the user the option to select his/her own word files (note: one word per line);
		// by default (CrypTool installation) the data resembles the old hard-coded words
		if(Dialog.isAnalysisAutomatic()) {
			CString filenameWordlist;
			if(Dialog.isAnalysisAutomaticGerman()) {
				// GERMAN: the wordlist is based on statistical 
				// evaluations by the original author of this code
				filenameWordlist = Dialog.m_editWordlistGerman;
			}
			if(Dialog.isAnalysisAutomaticEnglish()) {
				// ENGLISH: the wordlist is based on George W. 
				// Hart's work, "To Decode Short Cryptograms", 
				// Communications of the ACM, Sept 1994, Vol 37, No.4			*
				filenameWordlist = Dialog.m_editWordlistEnglish;
			}
			std::ifstream fileWordlist(filenameWordlist);
			if(fileWordlist.is_open()) {
				while(fileWordlist.good()) {
					std::string word;
					getline(fileWordlist, word);
					CString wordCString = word.c_str();
					// convert to upper-case through CString
					wordCString.MakeUpper();
					wordlist.push_back((std::string)wordCString);
				}
				fileWordlist.close();
			}
			else {
				// TODO/FIXME: error handling anyone?
				return 0;
			}
			Grenze = wordlist.size();
			common = new char*[Grenze];
			for(int wordlistIndex=0; wordlistIndex<Grenze; wordlistIndex++) {
				common[wordlistIndex] = (char*)(wordlist[wordlistIndex].c_str());
			}
		}
	}
	else {
		// TODO/FIXME: error handling anyone?
			return 0;
	}
	// **********************************************************************************
	// **********************************************************************************
	// **********************************************************************************

	// enable progress bar for automatic analysis only
	if(Dialog.isAnalysisAutomatic()) {
		if(par->flags & CRYPT_DO_PROGRESS) {
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SUBSTITUTION_ANALYSE,pc_str,STR_LAENGE_STRING_TABLE);
			theApp.fs.Display(pc_str);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_SUBSTITUTION_ANALYSE_COMPLETE,pc_str,STR_LAENGE_STRING_TABLE);
			theApp.fs.Set(0,pc_str);
			Sleep(1);
		}
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			SHOW_HOUR_GLASS
	}

	// Umlaute und Zeilenumbrueche umwandeln
	char outfile2[1024];
	GetTmpName(outfile2,"cry",".txt");
	FILE *stream, *stream2;
		
	int ch;
	if( (stream = fopen( par->infile, "rt" )) == NULL )
		exit( 0 );
	if( (stream2 = fopen( outfile2, "wt" )) == NULL )
		exit( 0 );

	while ( feof( stream ) == 0 )
	{
		ch = fgetc( stream );
		switch(ch) {
		case (-1):
			break;
		case ('\n'):					// Zeilenumbruch
			fwrite (" \n", 1, 2, stream2);
			break;
		case (252):
			fwrite ("ue", 1, 2, stream2);
			break;
		case (220):
			fwrite ("Ue", 1, 2, stream2);
			break;
		case (246):
			fwrite ("oe", 1, 2, stream2);
			break;
		case (214):
			fwrite ("Oe", 1, 2, stream2);
			break;
		case (228):
			fwrite ("ae", 1, 2, stream2);
			break;
		case (196):
			fwrite ("Ae", 1, 2, stream2);
			break;
		case ('?'):
			fwrite ("ss", 1, 2, stream2);
			break;
		default:
			fputc (ch, stream2);
			break;
		}
	}
	fclose (stream);
	fclose (stream2);
	
	Eingabedatei=outfile2;
	SymbolArray text(AlphaSpaceConv);
	text.Read(outfile2);
	int Laenge=text.GetSize(); // L?nge des eingelesenen Textes
	int Leerzeichen;		// Position des n?chsten Leerzeichens
	int Start=0;			// Merkt sich, wo das letzte Leerezichen gefunden wurde
	char *current=(char*) malloc (50);

	// Initialisieurng vom Permu und MaxPermu
	// Permu speichert die gerade untersuchte Substitution und MaxPermu die Substitution,
	// die bisher das beste Ergebnis brachte.
	int *Permu[26];//,*MaxPermu[26];
	//int *Permu[26];
	for (i=0; i<26; i++){
		Permu[i]=(int*)malloc(sizeof(int));
		*Permu[i]=-1;
		MaxPermu[i]=(int*)malloc(sizeof(int));
		*MaxPermu[i]=-1;
	}

	/* Manuelle Bearbeitung des Textes:
	   Das Nachbearbeitungsfenster wird aufgerufen. Im oberen Teil des Fensters werden
	   jedoch noch keine Zuordnungen vorgenommen (alles mit '*' initialisiert).
	   Der Benutzer kann Zuordnungen eingeben. Die daraus resultierende aktuelle
	   Substitution wird benutzt, um den zu bearbeitenden Ciphertext zu entschl?sseln.
	   Das Resultat wird im unteren Texfenster dargestellt.				*/

	if(Dialog.isAnalysisManual()){
		// Anzeigen des Nachbearbeitungsfensters
		if(Dialog.isAnalysisManualOption1())
		{
			LoadString(AfxGetInstanceHandle(), IDS_ANALYSIS_SUBSTITUTION, pc_str, STR_LAENGE_STRING_TABLE);
			CString SubstKey;
			if(PasteKey(pc_str, SubstKey)) {
				for(int i=0; i<26; i++) {
					*MaxPermu[i] = SubstKey[i];
				}
			}
		}

		CDlgManualSubstAnalysis Dialogbox;
		if (Dialogbox.DoModal()==IDOK){
			// Entschl?sseln und Ausgabe des Textes
			char outfile[1024], title[1024];
			GetTmpName(outfile,"cry",".txt");

			Laenge=text.GetSize();

			LPTSTR string = new TCHAR[Laenge + 1];
			int len;

			for (len=i=0 ; i<Laenge; i++){
				if (text[i]!=26){
					if (*MaxPermu[text[i]]!=-1){
						string[len++]=(char)(*MaxPermu[text[i]]);
					}
					else {
						string[len++]=(char)text[i]+'a';}
				}
			}
			string[len]=0;

			char *Ausgabe2=string;
			// Kopieren von char *Ausgabe2 in die Datei <outfile> (mit Hilfe der Secude Funktionen)
			OctetString help;
			help.noctets=strlen(Ausgabe2);
			help.octets=Ausgabe2;
			theApp.SecudeLib.aux_OctetString2file(&help,outfile,2);
			delete string;

			ForceReformat(outfile2, outfile, TRUE);

			// Berechnung der (Teil-)Permutation zur Anzeige im Titel
			char schluessel[27];
			for (i=0; i<26;i++)
			{
				schluessel[i] = '*';
			}
			for (i=0; i<26;i++)
			{
				if (*MaxPermu[i] != -1)
				{
					schluessel[(*MaxPermu[i])-'A'] = i+'A';
				}
			}
			schluessel[26]='\0';

			LoadString(AfxGetInstanceHandle(),IDS_STRING_POSSIBLE_PLAINTEXT_OF,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName2(title,sizeof(title),pc_str,schluessel,par->OldTitle);
			theApp.ThreadOpenDocumentFileNoMRU(outfile, title, schluessel);
			remove(outfile2);	
		}
		// Den allokierten Speicherplatz von current, Permu und MaxPermu freigeben
		free (current);
		for (i=0; i<26; i++){
			free (Permu[i]);
			free (MaxPermu[i]);
		}
		delete []common;
		return 0;
	}
	
	// Variable Max_Score wird mit?bergeben
	int MaxScore=-1;

	int oft=-1;

	bool doppelt=false;


	/* Die Option
	   'e' als h?ufigstes Zeichen annehmen 
	   wurde angew?hlt.
	   Das h?ufigste Zeichen im Text wird bestimmt und die Anfangspermutation wird so gesetzt,
	   da? dieses Zeichen die Verschl?sselung von 'e' darstellt.*/
	if(Dialog.isAnalysisAutomaticOption1()) {
		NGram t(text);
		int maxim=0;
		for (/*int*/ i=0; i<26; i++){
			if ((int)t.GetCount(i)>=maxim){
				if ((int)t.GetCount(i)==maxim){
					doppelt=true;}
				else {
					doppelt=false;}
				oft=i;
				maxim=t.GetCount(i);			
			}
		}
		if (doppelt==true){
			Message(IDS_STRING_MSG_FREQ_ANALYSE_NOTE, MB_ICONINFORMATION);
		}
		else{
			*Permu[oft]=69;
		}
	}

	
	/* Ein zweidimensionales Feld Cipher wird erzeugt, in dem die Worte des Ciphertextes 
	   abgelegt werden.
	   Dabei werden Worte, die das selbe Pattern haben in einer Zeile (d.h. identische erste
	   Koordinate) abgelegt.
	   Doppelte W?rter werden ignoriert.
	   Ciphertextworte, f?r die kein passendes Pattern in common vorkommt, werden auch ignoriert.			*/

	/* In der i-ten Zeile von PatSet werden all die Eintr?ge aus common gespeichert, die vom Pattern her zur
	   i-ten Zeile von Cipher passen																		*/

	char *Cipher [100][100];
	char *PatSet [100][50];
	// Felder Cipher und PatSet initialieren
	for (i=0;i< 100; i++){
		for (j=0;j<100;j++){
			Cipher[i][j]=NULL;}
		for (j=0; j<50; j++){
			PatSet[i][j]=NULL;}
	}

	
	if(par->flags & CRYPT_DO_PROGRESS)    theApp.fs.Set(10);
	int Worte_in_Analyse=0;
	
	while ((Start<Laenge)&&(Worte_in_Analyse<100)){

		if((par->flags & CRYPT_DO_PROGRESS)&&(theApp.fs.m_canceled)) {
			delete []common;
			return 0;
		}
		Leerzeichen=SucheLeer(Start, Laenge, text);

		// Es werden W?rter gefunden, die l?nger als 20 Zeichen sind.
		// D.h. entweder der Text hat gar keine Leerzeichen oder das
		// Wort ist wirklich l?nger als 20 Zeichen.
		// W?rter, die l?nger als 20 Zeichen sind, kommen aber in common nicht vor
		// und k?nnen mi?achtet werden.
		if ((Leerzeichen-Start)>20){
			Start=Leerzeichen+1;
			continue;}
		// Kopiere das letzte Wort (bis zum Blank) nach char *current
		// Gleichzeitig werden die Felder vore[26] und nache[26] mit den 
		// Buchstabenh?ufigkeiten vor bzw. nach dem e gepflegt
		for (/*int*/ i=0;i<(Leerzeichen-Start);i++){
			current[i]=(int)text[Start+i]+65;
			if ((i<((Leerzeichen-Start)-1))&&(current[i]==(oft+65))){
				nache[(int)text[Start+i+1]]++;}
			if ((i!=0)&&(current[i]==(oft+65))){
				vore[current[i-1]-65]++;}
		}
		// geh?rt noch zum Kopiervorgang
		current[Leerzeichen-Start]=0;
		// Pflege der Felder anfang[26] und ende[26]
		anfang[current[0]-65]++;
		ende[current[Leerzeichen-Start-1]-65]++;


		// Suche die Zeile im Feld Cipher, die das selbe Pattern hat wie current
		for (i=0; i<100; i++){
			if (Cipher [i][0]==NULL){   // Pattern kommt in Cipher noch nicht vor
				// Teste, ob es f?r dieses Ciphertextwort ein passendes Pattern in common gibt
				bool passt=FALSE;
				for (int k=0; k<Grenze; k++){
					if (match(current, common[k])==TRUE){
						passt=TRUE;
						break;}
				}

				// Es gibt kein passendes Pattern f?r current in der Liste common
				if (passt==FALSE){
					break;}

				// Es gibt ein passendes Pattern
				if (passt==TRUE){

					Worte_in_Analyse++;
					// Lege neuen Eintrag in Cipher an		
					Cipher [i][0]=(char*)malloc(strlen(current)+1);
					// Cipher [i][0] den Wert von current zuweisen
					for (int k=0; k<(int)strlen(current); k++){
						Cipher [i][0][k]=current[k];
					}
					Cipher [i][0][strlen(current)]=0;
					
					// F?ge die entsprechenden Patterns nach PatSet hinzu
					int j=0;
					for (int l=0; l<Grenze; l++){
						if (match (current, common[l])==TRUE){
							// F?ge common [i] in PatSet ein
							PatSet [i][j]=(char*)malloc(strlen(common[l])+1);
							for (int k=0; k<(int)strlen(common[l]); k++){
								PatSet [i][j][k]=common[l][k];
							}
							PatSet [i][j][strlen(common[l])]=0;
							j++;

						}
					}						
					break;
				}				
			}

			if (match(Cipher [i][0],current)==TRUE){   // Zeile mit passendem Pattern gefunden
				// Schaue, ob das Wort (exakt, nicht das pattern) schon in der Zeile vorhanden ist
				
				for (int j=0; j<100;j++){
					if (Cipher [i][j]==NULL){
						Worte_in_Analyse++;
						// current in die Zeile einf?gen
						// current nach Cipher [i][j] kopieren
						Cipher [i][j]=(char*)malloc(strlen(current)+1);
						for (int k=0; k<(int)strlen(current); k++){
							Cipher [i][j][k]=current[k];
						}
						Cipher [i][j][strlen(current)]=0;
						break;
					}
					else {
						// Vergleiche Cipher [i][j] mit current
						bool gleich=TRUE;
						if (strlen(Cipher[i][j])==strlen(current)){
							for (int k=0; k<(int)strlen(current); k++){
								if (Cipher[i][j][k]!=current[k]){
									gleich=FALSE;
								}
							}
						}
						else {gleich=FALSE;}
						if (gleich){

							break;
						}
					}
				}
				break;
			}
		}
		Start=Leerzeichen+1;
	}

	// Setze die Frtschrittsanzeige auf 10%
	if(par->flags & CRYPT_DO_PROGRESS) {
		theApp.fs.Set(15);
	}

	// Bestimmung von DMax, der Anzahl der verschiedenen Patternklassen
	int DMax;
	for (i=0; i<100; i++){
		if (Cipher [i][0]==NULL){
			DMax=i;
			break;
		}
	}

///////////////////////////////////////////////////////////////////////
// Ordnen der Ciphertextklassen
///////////////////////////////////////////////////////////////////////

/*  Finden des Root-Wortes
	Wir suchen die Ciphertextklasse, f?r die die Anzahl der verschiedenen 
	Buchstaben im Pattern geteilt durch die Gr??e der Pattern Set maximal ist			

	Das Feld nBuch[100] speichert die Anzahl der verschiedenen Buchstaben der Patterns 
	Das Feld nPatSet die Gr??e der zugeh?rigen Pattern Set
	Das Feld Taken merkt sich, ob die entsprechende Ciphertexte Klasse bereits 
	in die Sortierung aufgenommen wurde	Die Reihenfolge wird in Perm[100] gespeichert */
	float max=0;
	int nMax;
	int nBuch[100];
	int nPatSet[100];
	int Perm[100];
	bool taken[100];
	for (i=0; i<100; i++){
		nBuch[i]=0;
		nPatSet[i]=0;
		taken[i]=FALSE;}

	nMax=0;
	if(par->flags & CRYPT_DO_PROGRESS) {
		theApp.fs.Set(16);
	}

	for (i=0; i<DMax; i++){

		if(par->flags & CRYPT_DO_PROGRESS) {
			if(theApp.fs.m_canceled) {
				delete []common;
				return 0;
			};
		}

		bool benutzt[26];
		for (j=0; j<26;j++){
			benutzt[j]=FALSE;}
		for (j=0; j<(int)strlen(Cipher[i][0]); j++){
			if (benutzt[(Cipher[i][0][j])-65]==FALSE){
				benutzt[(Cipher[i][0][j])-65]=TRUE;
				nBuch[i]++;
			}
		}

		for (j=0; j<50; j++){
			if (PatSet[i][j]!=NULL){
				nPatSet[i]++;
			}
			else
			{	
				break;
			}
		}

		if (((float)nBuch[i])/((float)nPatSet[i])>max){
			max=((float)nBuch[i])/((float)nPatSet[i]);
			nMax=i;}
	}

	if(par->flags & CRYPT_DO_PROGRESS) {
		theApp.fs.Set(17);
	}
	taken[nMax]=TRUE;
	Perm[0]=nMax;
	Perm[1]=nMax;

	/* Alle anderen Ciphertextklassen werden nach der L?nge von nBuch sortiert
	   Dabei kommen die gr??ten Werte f?r nBuch zuerst (Sinn: dadurch wird das Durchlaufen des
	   Suchbaumes effizienter)				*/
	for (i=1; i<DMax; i++){
		if((par->flags & CRYPT_DO_PROGRESS)&&(theApp.fs.m_canceled)) {
			delete []common;
			return 0;
		}

// Bestimme das aktuelle Maximum nMax der nBuch
//	theApp.fs.Set(i);

		nMax=-1;
		int Maximum=-1;
		for (int j=0; j<DMax; j++){
			if (taken[j]==FALSE){
				if (nBuch[j]>Maximum){
					Maximum=nBuch[j];
					nMax=j;
				}
			}
		}
		taken[nMax]=TRUE;

		// Setze Perm[i] auf nMax;
		Perm[i]=nMax;
		Sleep(0);	// 
	}

	if(par->flags & CRYPT_DO_PROGRESS) {
		theApp.fs.Set(18);
	}

	//////////////////////////////////////////////////////////////
	// Ende (Ordnen der Ciphertextklassen)
	//////////////////////////////////////////////////////////////

	// Der Wert Delta gibt an, um wieviel die Fortschrittsanzeige jedesmal hochgesetzt werden
	// soll.
	// Da die Fortschrittsanzeige bei jedem Aufruf der Funktion "solve" bei Suchtiefe 1
	// hochgesetzt wird
	float Delta=40.0;
	nMax=0;
	while (Cipher[Perm[0]][nMax]!=NULL)   nMax++;
	Delta=Delta/((float)nMax+1);
	nMax=0;
	while (Cipher[Perm[1]][nMax]!=NULL)   nMax++;
	Delta=Delta/((float)nMax+1);

	
	// Setzen der Fortschrittsanzeige auf 20%
	if(par->flags & CRYPT_DO_PROGRESS) {
		theApp.fs.Set(20,pc_str);}

	/////////////////////////////////////////////////////////////
	// erweiterte Analyse (f?r deutsche Klartexte)
	/////////////////////////////////////////////////////////////

	// Bestimme den Buchstaben, der im Chiffrat am h?ufigsten nach dem e vorkommt.
	// Wir nehmen an, da? dieser Buchstabe entweder auf n oder auf r abgebildet wird
	if(Dialog.isAnalysisAutomaticOption2() && doppelt==false){

		
		// Sortieren der Listen vore[26], nache[26], anfang[26] und ende[26]
		bool benutzt[26];
		int nacheSort[26], voreSort[26], anfangSort[26], endeSort[26];

		//Sortiere nache[26] und lege das Ergebnis in nacheSort[26] ab
		for (i=0; i<26; i++){
			benutzt[i]=false;
		}

		int Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			// Finde den n?chsth?heren Wert
			// Alle Werte, deren benutzt-Wert auf true steht sind schon vergebe
			for (int j=0; j<26; j++){
				if ((nache[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=nache[j];
					Maximum=j;
				}
			}
			nacheSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}

		//Sortiere vore[26] und lege das Ergebnis in voreSort[26] ab
		for (i=0; i<26; i++){
			benutzt[i]=false;
		}

		Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			for (int j=0; j<26; j++){
				if ((vore[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=nache[j];
					Maximum=j;
				}
			}
			voreSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}

		//Sortiere anfang[26] und lege das Ergebnis in anfangSort[26] ab
		for (i=0; i<26; i++){
			benutzt[i]=false;
		}

		Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			for (int j=0; j<26; j++){
				if ((anfang[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=anfang[j];
					Maximum=j;
				}
			}
			anfangSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}

		//Sortiere ende[26] und lege das Ergebnis in endeSort[26] ab
		for (i=0; i<26; i++){
			benutzt[i]=false;
		}

		Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			for (int j=0; j<26; j++){
				if ((ende[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=ende[j];
					Maximum=j;
				}
			}
			endeSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}



		/* Bestimme das n als den Buchstaben, der in den Listen
		   endeSort[26] und nacheSort[26] "am weitesten oben steht".
		   Unter "am weitesten oben steht" ist zu verstehen, da? die
		   Summe der Indizes minimal ist.						*/

		/* Da es h?ufig Schwierigkeiten in der Unterscheidung von n und r
		   gab, die weiteren Analysen jedoch auf der Erkennung des n beruhen,
		   wurde die Funktion erweitert.
		   Es werden nun die beiden Minima berechnet.
		   Als das n wird dann der Wert (von beiden) angenommen, 
		   der in allen vier Listen am weitesten oben steht. Der andere Buchstabe
		   wird als Chiffrat des r angenommen.
			 der in der 
		   Liste endeSort[26] am weitesten oben steht		*/


		int Minimum=5000, Minimum2=5000;
		int Punkte=100, Punkte2=100;
		for (i=0; i<26; i++){
			// suche den Buchstaben endeSort[i] in der Liste nacheSort[26]
			for (int j=0; j<26; j++){
				if ((endeSort[i]==nacheSort[j])&&(*Permu[endeSort[i]]==-1)){
					if ((i+j)<Punkte2){	// in Liste
						if ((i+j)<Punkte){	// neues Minimum
							Punkte2=Punkte;
							Minimum2=Minimum;
							Punkte=i+j;
							Minimum=i;
						}
						else {		// neuen 2. Platz
							Punkte2=i+j;
							Minimum2=i;
						}
					}
				}
			}
		}

		// Unterscheide n und r
		// Kann durchaus noch verbessert werden.
		if (Minimum<Minimum2){
			*Permu[endeSort[Minimum]]=78;
			*Permu[endeSort[Minimum2]]=82;
		}
		else{
			*Permu[endeSort[Minimum2]]=78;
			*Permu[endeSort[Minimum]]=82;
		}


		// Erstelle eine Liste mit den h?ufigsten Buchstaben vor und nach dem n
		int vorn[26], vornSort[26], nachn[26], nachnSort[26];
		for (i=0; i<26; i++){
			vorn[i]=0;
			vornSort[i]=0;
			nachn[26];
			nachnSort[26];
			benutzt[i]=false;
		}
		for (i=0; i<Laenge; i++){
			if (text[i]==13){
				if (i!=0){
					if (text[i-1]!=26){
						vorn[text[i-1]]++;
					}
				}
				if (i<Laenge-1){
					if (text[i+1]!=26){
						nachn[text[i+1]]++;
					}
				}
			}
		}

		// Sortieren der Liste vorn[26]
		Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			for (int j=0; j<26; j++){
				if ((vorn[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=ende[j];
					Maximum=j;
				}
			}
			vornSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}

		// Sortieren der Liste nachn[26]
		for (i=0; i<26; i++){
			benutzt[i]=false;
		}
		Maximum=-1, Maximalwert=-1;
		for (i=0; i<26; i++){
			for (int j=0; j<26; j++){
				if ((nachn[j]>Maximalwert)&&(benutzt[j]==false)){
					Maximalwert=ende[j];
					Maximum=j;
				}
			}
			nachnSort[i]=Maximum;
			benutzt[Maximum]=true;
			Maximalwert=-1;
		}


		/* Bestimme das i als den Buchstaben, der in den Listen
		   voreSort[26] und nacheSort[26] und vornSort[26] am "weitesten oben steht".		*/

		Punkte=100;
		for (i=0; i<26; i++){
			// suche den Buchstaben voreSort[i] in der Liste nacheSort[26]
			for (int j=0; j<26; j++){
				if ((voreSort[i]==nacheSort[j])&&(*Permu[voreSort[i]]==-1)){
					for (int k=0; k<26; k++){
						if (voreSort[i]==vornSort[k]){
							if ((i+j+k)<=Punkte){
								Punkte=i+j+k;
								Minimum=i;
							}
						}
					}
				}
			}
		}
		if (*Permu[voreSort[Minimum]]==-1){
			*Permu[voreSort[Minimum]]=73;
		}



		// Mit der eben ermittelten (partiellen) Substitution wird
		// jetzt nach einer L?sung gesucht.
		Fortschritt=20;
		solve (0, DMax, Permu, Perm, 0, PatSet, Cipher, &MaxScore, MaxPermu, Delta);

		
	}

	///////////////////////////////////////////////////////////////////
	// Ende (erweiterte Analyse)
	///////////////////////////////////////////////////////////////////

	else{  // Option "erweiterte Analyse" wurde nicht gew?hlt

		/* Erster Aufruf von solve:
		   Die einzelnen Parameter bedeuten folgendes:
		   1. Parameter: aktuelle Suchtiefe (Null steht f?r Wurzel)
		   2. Parameter: Tiefe des Baumes
		   3. Parameter: aktuelle (partielle) Permutation (zu Beginn leer)
		   4. Parameter: Reihenfolge der Ciphertextklassen
		   5. Parameter: aktuelle Punktzahl (zu Beginn Null)
		   6. Parameter: die Ciphertextklassen
		   7. Parameter: die Pattern Sets
		*/
		Fortschritt=20;
		solve (0, DMax, Permu, Perm, 0, PatSet, Cipher, &MaxScore, MaxPermu, Delta);
	}

	// L?schen der Fortschrittsanzeige
	theApp.fs.cancel();
	while(theApp.fs.m_displayed) Sleep(100);
	
	// Anzeigen des Nachbearbeitungsfensters
	CDlgManualSubstAnalysis Dialogbox;
	if (Dialogbox.DoModal()==IDCANCEL){		// "Cancel" angeklickt
		// Belegten Speicherplatz freigeben
		free(current);
		// Den allokierten Speicherplatz von Permu und MaxPermu freigeben
		for (i=0; i<26; i++){
			free (Permu[i]);
			free (MaxPermu[i]);
		}
		delete []common;
		return 0;
	}

	// Entschl?sseln und Ausgabe des Textes
	char outfile[1024], title[1024];
	GetTmpName(outfile,"cry",".txt");

	Laenge=text.GetSize();

	LPTSTR string = new TCHAR[Laenge + 1];
	int len;

	for (len=i=0 ; i<Laenge; i++){
		if (text[i]!=26){
			if (*MaxPermu[text[i]]!=-1){
				string[len++]=(char)(*MaxPermu[text[i]]);
			}
			else {
				string[len++]=(char)text[i]+'a';}
		}
	}
	string[len]=0;


	// Den String string in einem eigenen Textfenster ausgeben
	// Kopieren von string nach char *Ausgabe2
	// Kopieren von Cstring string1 nach Char *string3
//	LPTSTR string = new TCHAR[Ausgabe.GetLength()+1];
//	_tcscpy(string, Ausgabe);		
	char *Ausgabe2=string;
	// Kopieren von char *Ausgabe2 in die Datei <outfile> (mit Hilfe der Secude Funktionen)
	OctetString help;
	help.noctets=strlen(Ausgabe2);
	help.octets=Ausgabe2;
	theApp.SecudeLib.aux_OctetString2file(&help,outfile,2);
	delete string;

	ForceReformat(outfile2, outfile, TRUE);

	// Berechnung der (Teil-)Permutation zur Anzeige im Titel
	char schluessel[27];

	for (i=0; i<26;i++)
	{
		schluessel[i] = '*';
	}
	for (i=0; i<26;i++)
	{
		if (*MaxPermu[i] != -1)
		{
			schluessel[(*MaxPermu[i])-'A'] = i+'A';
		}
	}
	schluessel[26]='\0';

	LoadString(AfxGetInstanceHandle(),IDS_STRING_POSSIBLE_PLAINTEXT_OF,pc_str,STR_LAENGE_STRING_TABLE);
	MakeNewName2(title,sizeof(title),pc_str,schluessel,par->OldTitle);
	theApp.ThreadOpenDocumentFileNoMRU(outfile, title, schluessel);
//	remove(outfile);	
	remove(outfile2);

	free(current);


	// Den allokierten Speicherplatz von Permu und MaxPermu freigeben
	for (i=0; i<26; i++){
		free (Permu[i]);
		free (MaxPermu[i]);
	}
	delete []common;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		HIDE_HOUR_GLASS

	return 0;
}

int SucheLeer (int Start, int Laenge, SymbolArray& text){
	while (Start<Laenge){
		if (text[Start]==26){
			return Start;
		}
		Start=Start+1;
	}

	// Es kommt kein Leerzeichen im Text mehr vor
	// Bearbeite das letzte Wort
	return (Laenge);
}

/* ?berpr?ft, ob die beiden der Funktion ?bergebenen W?rter das
   selbe Muster (Pattern) haben.						*/
bool match (char *current, char *common){
	if (strlen(current)!=strlen(common)){
		return FALSE;
	}
	for (int l=1; l<(int)strlen(current); l++){
		for (int j=0; j<l; j++){
			if ((current[l]==current[j])&&(common[l]!=common[j])){
				return FALSE;
			}
			if ((current[l]!=current[j])&&(common[l]==common[j])){
				return FALSE;
			}
		}
	}
	return TRUE;
}

void compare_score (int *Permu[26], int *MaxScore, int score, int *MaxPermu[26]){

	// Vergleiche die ?bergebene Punktzahl mit der maximalen Punktzahl
	// ist die aktuelle Punktzahl h?her, so ist die aktuelle Permutation
	// die im Moment wahrscheinlichste.

	if (score>*MaxScore){
		// Speichere score als neue Maximalpunktzahl
		*MaxScore=score;
		// Kopieren von Permu nach MaxPermu
		for (int i=0; i<26; i++){
			*MaxPermu[i]=*Permu[i];
		}
	}
}


/* Die Funktion konsistent erh?lt als Eingabe ein (partielle) Permutation Perm sowie
   zwei Strings w und x.
   Die Strings w und x induzieren ebenfalls eine partielle Permutation.
   konsistent ?berpr?ft, ob diese beiden Permutationen vertr?glich sind */
bool konsistent (int *Permu[26], int *PermuNeu[26], char *w, char *x){

	int i;
	for (i=0; i<26; i++){
		*PermuNeu[i]=*Permu[i];}
	for (i=0; i<(int)strlen(w); i++){
		if ((*Permu[w[i]-65]!=-1)&&(*Permu[w[i]-65]!=x[i])){
			return FALSE;}
		for (int j=0; j<26; j++){
			if (*Permu[j]==x[i]){
				if ((w[i]-65)!=j){
					return FALSE;
				}
			}
		}
		*PermuNeu[w[i]-65]=(int)x[i];
	}
	return TRUE;
}

/* Eigentliche Analyse-Funktion
   Wird rekursiv aufgerufen						*/
void solve (int Tiefe, int DMax, int *Permu[26], int Perm[], int score, char *PatSet[100][50], char *Cipher[100][100], int *MaxScore, int *MaxPermu[26], float Delta){
	
	if(theApp.fs.m_canceled)   return;
	if (Tiefe==DMax){
		compare_score(Permu, MaxScore, score, MaxPermu);
	}
	else{
		int i=0;
		int *PermuNeu[26];
		int k;

		for (k=0; k<26; k++){
			PermuNeu[k]=(int*)malloc(sizeof(int));
			*PermuNeu[k]=-1;}
		while (Cipher[Perm[Tiefe]][i]!=NULL){
			if (Tiefe==1){
				// Setze Fortschrittsanzeige neu
				Fortschritt+=Delta;
				theApp.fs.Set((int)Fortschritt);
			}
			int j=0;
			while (PatSet[Perm[Tiefe]][j]!=NULL){
				
				if (konsistent (Permu, PermuNeu, Cipher[Perm[Tiefe]][i], PatSet[Perm[Tiefe]][j])==TRUE){
					solve (Tiefe+1, DMax, PermuNeu, Perm, score+1,PatSet, Cipher, MaxScore, MaxPermu, Delta);
				}
				j++;
			}
			i++;
		}
		if (Tiefe==1){
			// Setze Fortschrittsanzeige neu
			Fortschritt+=Delta;
			theApp.fs.Set((int)Fortschritt);
		}
		if (score==0){
			Fortschritt+=(float)(40.0/(float)DMax);
			theApp.fs.Set((int)Fortschritt);
		}
		solve (Tiefe+1, DMax, Permu, Perm, score, PatSet, Cipher, MaxScore, MaxPermu, Delta);
		// Den allokierten Speicherplatz von PermuNeu freigeben
		for (k=0; k<26; k++){
			free (PermuNeu[k]);
		}
	}
}


// =====================================================================================
// Homophone encryption:
// 
// Jan Blumenstein & Henrik Koy (March 2001)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//
// -------------------------------------------------------------------------------------

void HomophoneAsc(const char *infile, const char *OldTitle)
{
	if ( !CheckAlphabet() ) return;
	SymbolArray text(AppConv);
	text.Read(infile);
	if ( !CheckTextSize( text ) ) return;
	
	char inbuffer[buffsize+3];
	CDlgKeyHomophone DH;
	// DH.DeactivateDecryptionButton = TRUE;
	for (int i=0; ; i++ ) {
		DH.c_SourceFile[i] = infile[i];
		if (infile[i] == 0) break;
	}

	ifstream in(infile, ios::binary | ios::in);	
	in.read(inbuffer,buffsize);

	CAppDocument *NewDoc;

	if(IDOK!=DH.DoModal()) 
	{
		theApp.TextOptions.getAlphabetReference() = DH.m_AlphabetBackup;
		in.close();
		return;
	}
	theApp.TextOptions.getAlphabetReference() = DH.m_AlphabetBackup;

// Routine zur Homophonen Verschl?sselung
	char outbuffer[17000];
	long outbuffsize;
	char outfile[1024],title[1024];
	int value;
	GetTmpName(outfile,"cry",".hex");
	ofstream out(outfile, ios::binary | ios::out );

	unsigned char	* p_value = (unsigned char*)&value;
    char		      residuum = 0;
	unsigned char     offsetResiduum = 0;
	int               bitLength = DH.HB.LogKeySize( 2 );

	if(true==DH.Get_crypt())			// Verschl?sselung
	{
		while(in.gcount())
		{
			outbuffsize=0;
			char buff = 0;
			bool umlautFlag = FALSE;
			for (int i=0;i<in.gcount(); )
			{		
				if ( DH.HB.GetKeyType() == HOM_ENC_TXT )
				{
					if ( DH.m_encodeUmlauts && buff == 0 )
					{
						switch ( (char)inbuffer[i] ) {
						case '?': inbuffer[i] = 'a'; buff = 'e'; umlautFlag = true;
							break;
						case '?': inbuffer[i] = 'o'; buff = 'e'; umlautFlag = true;
							break;
						case '?': inbuffer[i] = 'u'; buff = 'e'; umlautFlag = true;
							break;
						case '?': inbuffer[i] = 's'; buff = 's'; umlautFlag = true;
							break;
						case '?': inbuffer[i] = 'A'; buff = 'e'; umlautFlag = true;
							break;
						case '?': inbuffer[i] = 'O'; buff = 'e'; umlautFlag = true;
							break;
						case '?': inbuffer[i] = 'U'; buff = 'e'; umlautFlag = true;
							break;
						}					
						value=DH.HB.Encrypt((unsigned char)inbuffer[i]);					
					}

					if ( !buff )
					{	
						value=DH.HB.Encrypt((unsigned char)inbuffer[i]);
						i++;
					}
					else if ( umlautFlag ) 
					{
						umlautFlag = false;
					}
					else
					{
						value=DH.HB.Encrypt((unsigned char)buff);
						buff = 0;
						i++;
					}
				}
				else
				{
					value = DH.HB.Encrypt((unsigned char)inbuffer[i++]);
				}

				if ( value >= 0 )
				{
					value <<= offsetResiduum;
					value |= residuum;
					offsetResiduum += bitLength;

					int j;
					for (j=0; offsetResiduum >= 8; j++ )
					{
						outbuffer[outbuffsize]= p_value[j];
						outbuffsize++;
						offsetResiduum -= 8;
					}
					if ( offsetResiduum ) 
					{
						residuum = p_value[j];
					}
					else
					{
						residuum = 0;
					}
				}
			}

			out.write(outbuffer,outbuffsize);
			in.read(inbuffer,buffsize);
		}
		if ( residuum ) 
			out << residuum; 
	}
	else								// Entschl?sselung
	{
		DH.HB.Make_dec_table();
		value = 0;
		unsigned char offsetResiduumPrev = 0;
		int j = 0;

		while(in.gcount())
		{
			outbuffsize=0;
			for (int i=0;i<in.gcount();)
			{
				p_value[j] = inbuffer[i];
				i++; j++; offsetResiduum += 8;
				while ( offsetResiduum >= bitLength )
				{
					value = (value << offsetResiduumPrev) + residuum;
					int val = value % (1 << bitLength);
					outbuffer[outbuffsize]=DH.HB.Decrypt( val );
					outbuffsize++;
					offsetResiduum -= bitLength;
					residuum = value >> bitLength;

					value = j = 0;
					offsetResiduumPrev = offsetResiduum;
				}
			}
			out.write(outbuffer,outbuffsize);
			in.read((char *)inbuffer,buffsize);
		}
	}

	in.close();
 	out.close();

	NewDoc = theApp.OpenDocumentFileNoMRU(outfile,DH.HB.GetKeyStr());
	remove(outfile);
	if(NewDoc) 
	{
		if(true==DH.Get_crypt())
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		}
		else
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		}
		LoadString(AfxGetInstanceHandle(),IDS_STRING_HOMOPHONE,pc_str,STR_LAENGE_STRING_TABLE);
		MakeNewName3(title,sizeof(title),pc_str1,pc_str,OldTitle,DH.HB.GetKeyStr());
		NewDoc->SetTitle(title);
	}

	HIDE_HOUR_GLASS
} // end Hompohone Asc

// flomar, 2019/02/20
void HomophonicSubstitutionAsc(const char *infile, const char *title) {
	CDlgHomophonicSubstitution dlg(infile, title);
	const int result = dlg.DoModal();
	if(result == IDENCRYPT || result == IDDECRYPT) {
		char outfile[1024];
		GetTmpName(outfile, "cry", ".hex");
		if(result == IDENCRYPT) {
			const bool resultEncryption = dlg.executeEncryption(outfile);
			if(!resultEncryption) {
				AfxMessageBox("TODO/FIXME: critical error");
				remove(outfile);
				return;
			}
		}
		if(result == IDDECRYPT) {
			const bool resultDecryption = dlg.executeDecryption(outfile);
			if(!resultDecryption) {
				AfxMessageBox("TODO/FIXME: critical error");
				remove(outfile);
				return;
			}
		}
		CAppDocument *document = theApp.OpenDocumentFileNoMRU(outfile, dlg.getKeyAsString());
		remove(outfile);
		if(document) {
			CString documentTitle;
			CString stringAlgorithm;
			CString stringTitle;
			CString stringKey;
			stringAlgorithm.LoadString(IDS_STRING_HOMOPHONIC_SUBSTITUTION);
			stringTitle = title;
			stringKey = dlg.getKeyAsString();
			if(result == IDENCRYPT) {
				documentTitle.Format(IDS_STRING_ENCRYPTION_OF_USING_KEY, stringAlgorithm, stringTitle, stringKey);
			}
			if(result == IDDECRYPT) {
				documentTitle.Format(IDS_STRING_DECRYPTION_OF_USING_KEY, stringAlgorithm, stringTitle, stringKey);
			}
			document->SetTitle(documentTitle);
		}
	}
}

// =====================================================================================
// NGram Analyse:
// 
// Henrik Koy (March 2001)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Description:
//
// -------------------------------------------------------------------------------------

void NGramAsc(const char *infile, const char *OldTitle)
{
	SHOW_HOUR_GLASS

    char      * buffer;
	CFile f( infile, CFile::modeRead );
	unsigned long fLen = (unsigned long)((f.GetLength() < 1048576) ? f.GetLength() : 1048576);  //  2^20 bytes restriction restriction
	buffer = new char[fLen+1];
	f.Read( (void *)buffer, fLen );	
	CDlgNGramAnaylsis DiaNGram;
	DiaNGram.LoadText(buffer, fLen, OldTitle, 0);

    DiaNGram.DoModal();

    if ( DiaNGram.b_saveNGramList() )
	{
		CAppDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(DiaNGram.outfile);
		remove(DiaNGram.outfile);
		if (NewDoc) {
			char title[128], method[20]; 
			switch ( DiaNGram.m_N_NGram )  {
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
				sprintf( method, pc_str, DiaNGram.m_NrNGram );
				break;
			}
			LoadString(AfxGetInstanceHandle(),IDS_TITLE_NGRAMANALYSIS,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName2(title,sizeof(title),pc_str,OldTitle,method);
			NewDoc->SetTitle(title);
		}
	}

	HIDE_HOUR_GLASS
}

void NGramBin(const char *infile, const char *OldTitle)
{
	SHOW_HOUR_GLASS

    char      * buffer;	
	CFile f( infile, CFile::modeRead );
	unsigned long fLen = (unsigned long)((f.GetLength() < 1048576) ? f.GetLength() : 1048576);  // 2^18 bytes restriction
	buffer = new char[fLen+1];
	f.Read( (void *)buffer, fLen );

	CDlgNGramAnaylsis DiaNGram;
	DiaNGram.LoadText(buffer, fLen, OldTitle, 1);

	DiaNGram.DoModal();

    if ( DiaNGram.b_saveNGramList() )
	{
		CAppDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(DiaNGram.outfile);
		remove(DiaNGram.outfile);
		if (NewDoc) {
			char title[128], method[20]; 
			switch ( DiaNGram.m_N_NGram )  {
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
				sprintf( method, pc_str, DiaNGram.m_NrNGram );
				break;
			}
			LoadString(AfxGetInstanceHandle(),IDS_TITLE_NGRAMANALYSIS,pc_str,STR_LAENGE_STRING_TABLE);
			MakeNewName2(title,sizeof(title),pc_str,OldTitle,method);
			NewDoc->SetTitle(title);
		}
	}

	HIDE_HOUR_GLASS
}

// =============================================================
// == permutation cryptology 
// == Peer Wichmann July 2001
void DoPerm(char *dest, char *src, int len, int *p, int plen, int Zin, int Zout)
{		
	int i, k, pt;
	int Zeilenzahl, LetzteZLen;
	int pres[MAX_PERM_LENGTH], sstart[MAX_PERM_LENGTH], slen[MAX_PERM_LENGTH];

	Zeilenzahl = len / plen;
	LetzteZLen = len % plen;
	for(i=0;i<LetzteZLen;i++) slen[i] = Zeilenzahl+1;
	for(i=LetzteZLen;i<plen;i++) slen[i] = Zeilenzahl;
	sstart[0]=0;
	for(i=1;i<plen;i++) sstart[i] = sstart[i-1] + slen[i-1];

	memcpy(pres, p, plen * sizeof(int));
	for(i=k=0;i<plen;i++)
		if(pres[k] >= LetzteZLen)
			memcpy(pres+k, pres+k+1, sizeof(int) * (plen - i));
		else
			k++;


	if(Zin == 0) // zeilenweise einlesen
		if(Zout == 1) // zeilenweise einlesen, spaltenweise auslesen
			for(pt=i=0;i<plen;i++)
				for(k=p[i];k<len;k+=plen)
					dest[pt++]=src[k];
		else {//zeilenweise einlesen, zeilenweise auslesen
			for(pt=i=0;i<Zeilenzahl;i++,pt+=plen) // ganze Zeilen
				for(k=0;k<plen;k++)
					dest[pt+k]=src[pt+p[k]];
			for(i=0;i<LetzteZLen;i++) // letzte Zeile
				dest[pt+i]=src[pt+pres[i]];
		}
	else	// spaltenweise einlesen
		if(Zout == 1) // spaltenweise einlesen, spaltenweise auslesen
			for(pt=i=0;i<plen;i++) {
				memcpy(dest+pt, src+sstart[p[i]], slen[p[i]]);
				pt += slen[p[i]];
			}
		else {//spaltenweise einlesen, zeilenweise auslesen 
			for(pt=i=0;i<Zeilenzahl;i++)
				for(k=0;k<plen;k++)
					dest[pt++]=src[sstart[p[k]]+i];
			for(i=0; i<LetzteZLen; i++) // letzte Zeile
				dest[pt++]=src[sstart[pres[i]]+Zeilenzahl];
		}
}

void DoInvPerm(char *dest, char *src, int len, int *p, int plen, int Zin, int Zout)
{
	int i, k, pt;
	int Zeilenzahl, LetzteZLen;
	int pres[MAX_PERM_LENGTH], sstart[MAX_PERM_LENGTH], slen[MAX_PERM_LENGTH];

	Zeilenzahl = len / plen;
	LetzteZLen = len % plen;
	for(i=0;i<LetzteZLen;i++) slen[i] = Zeilenzahl+1;
	for(i=LetzteZLen;i<plen;i++) slen[i] = Zeilenzahl;
	sstart[0]=0;
	for(i=1;i<plen;i++) sstart[i] = sstart[i-1] + slen[i-1];

	memcpy(pres, p, plen * sizeof(int));
	for(i=k=0;i<plen;i++)
		if(pres[k] >= LetzteZLen)
			memcpy(pres+k, pres+k+1, sizeof(int) * (plen - i));
		else
			k++;


	if(Zin == 0) // zeilenweise einlesen
		if(Zout == 1) // zeilenweise einlesen, spaltenweise auslesen
			for(pt=i=0;i<plen;i++)
				for(k=p[i];k<len;k+=plen)
					dest[k]=src[pt++]; 
		else {//zeilenweise einlesen, zeilenweise auslesen
			for(pt=i=0;i<Zeilenzahl;i++,pt+=plen) // ganze Zeilen
				for(k=0;k<plen;k++)
					dest[pt+p[k]]=src[pt+k];
			for(i=0;i<LetzteZLen;i++) // letzte Zeile
				dest[pt+pres[i]]=src[pt+i];
		}
	else	// spaltenweise einlesen
		if(Zout == 1) // spaltenweise einlesen, spaltenweise auslesen
			for(pt=i=0;i<plen;i++) {
				memcpy(dest+sstart[p[i]], src+pt, slen[p[i]]);
				pt += slen[p[i]];
			}
		else {//spaltenweise einlesen, zeilenweise auslesen // TBD
			for(pt=i=0;i<Zeilenzahl;i++)
				for(k=0;k<plen;k++)
					dest[sstart[p[k]]+i]=src[pt++];
			for(i=0; i<LetzteZLen; i++) // letzte Zeile
				dest[sstart[pres[i]]+Zeilenzahl]=src[pt++];
		}
}


void Permutation(const char *infileName, const char *OldTitle, BOOL TEXTMODE)
{
	CDlgKeyPermutation Perm;
	Perm.setInputFilename(infileName);
	Perm.m_DataType = ( TEXTMODE ) ? 0 : 1;
    if (Perm.DoModal()==IDOK)
	{
		char *mSrc = NULL, *mDest = NULL; 
		int   lSrc = 0,     lDest = 0;
		TEXTMODE = ( Perm.m_DataType );
		if ( 0 > readSource( infileName, mSrc, lSrc, TEXTMODE ) )
		{
			// FIXME: ERROR
			return;
		}

		if (!lSrc )
		{
			// FIXME: ERROR
			return;
		}

		mDest = (char *) malloc(lSrc+1);
		char *pData;

		// PERMUTATION
		if(Perm.m_Dec) 
		{ // DECRYPTION
			if(Perm.m_P2len)
			{
				if ( !Perm.m_Invert )
				{
					DoInvPerm(mDest, mSrc, lSrc, Perm.m_P2inv, Perm.m_P2len, Perm.m_P2InSeq ^ Perm.m_P2Perm  ^ 1, Perm.m_P2OutSeq ^ Perm.m_P2Perm  ^ 1);
					DoInvPerm(mSrc, mDest, lSrc, Perm.m_P1inv, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);
					pData = mSrc;
				}
				else
				{
					DoInvPerm(mDest, mSrc, lSrc, Perm.m_P2, Perm.m_P2len, Perm.m_P2InSeq ^ Perm.m_P2Perm  ^ 1, Perm.m_P2OutSeq ^ Perm.m_P2Perm  ^ 1);
					DoInvPerm(mSrc, mDest, lSrc, Perm.m_P1, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);
					pData = mSrc;
				}
			}
			else
			{
				if ( !Perm.m_Invert )
				{
					DoInvPerm(mDest, mSrc, lSrc, Perm.m_P1inv, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);
					pData = mDest;
				}
				else
				{
					DoInvPerm(mDest, mSrc, lSrc, Perm.m_P1, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);
					pData = mDest;
				}
			}
		}
		else 
		{ // ENCRYPTION
			if ( !Perm.m_Invert )
				DoPerm(mDest, mSrc, lSrc, Perm.m_P1inv, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);
			else
				DoPerm(mDest, mSrc, lSrc, Perm.m_P1, Perm.m_P1len, Perm.m_P1InSeq ^ Perm.m_P1Perm  ^ 1, Perm.m_P1OutSeq ^ Perm.m_P1Perm  ^ 1);

			if(Perm.m_P2len)
			{
				pData = mSrc;
				if ( !Perm.m_Invert )
					DoPerm(mSrc, mDest, lSrc, Perm.m_P2inv, Perm.m_P2len, Perm.m_P2InSeq ^ Perm.m_P2Perm  ^ 1, Perm.m_P2OutSeq ^ Perm.m_P2Perm  ^ 1);
				else
					DoPerm(mSrc, mDest, lSrc, Perm.m_P2, Perm.m_P2len, Perm.m_P2InSeq ^ Perm.m_P2Perm  ^ 1, Perm.m_P2OutSeq ^ Perm.m_P2Perm  ^ 1);
			}
			else pData = mDest;
		}

		char *outFileName = NULL;
		if ( 0 > writeDest(pData, lSrc, outFileName, TEXTMODE, infileName) )
		{
			// FIXME: ERROR
		}
		else
		{
			char Invert[20];
			char dType[20];
			char *key    = new char[6*16+Perm.m_Perm1.GetLength()+Perm.m_Perm2.GetLength() + strlen(PARAM_TOKEN)+60];
			char *title  = NULL; 
			strcpy(Invert, Perm.m_Invert   ? INV_TOKEN : "");
			strcpy(dType , (Perm.m_DataType) ? TEXT_TOKEN : BINARY_TOKEN );

			if(Perm.m_P2len)
				sprintf(key,"%s;%s %s%s%s%i,%i,%i,%i,%i,%i", Perm.m_Perm1, Perm.m_Perm2, PARAM_TOKEN, dType, Invert,
						Perm.m_P1InSeq, Perm.m_P1Perm, Perm.m_P1OutSeq,
						Perm.m_P2InSeq, Perm.m_P2Perm, Perm.m_P2OutSeq);
			else
				sprintf(key,"%s %s%s%s%i,%i,%i,%i,%i,%i", Perm.m_Perm1, PARAM_TOKEN, dType, Invert,
						Perm.m_P1InSeq, Perm.m_P1Perm, Perm.m_P1OutSeq,
						Perm.m_P2InSeq, Perm.m_P2Perm, Perm.m_P2OutSeq);
			CAppDocument *NewDoc;
			NewDoc = theApp.OpenDocumentFileNoMRU(outFileName,key);
			remove(outFileName);	
			if(NewDoc) 
			{
				if(Perm.m_Dec)
					LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
				else
					LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
				LoadString(AfxGetInstanceHandle(),IDS_CRYPT_PERMUTATION,pc_str,STR_LAENGE_STRING_TABLE);
				
				int titlelength = strlen(key) + strlen(pc_str) + strlen(pc_str1) + strlen(OldTitle) +1;
				title = new char[titlelength];
				MakeNewName3(title,titlelength,pc_str1,pc_str,OldTitle,key);
				NewDoc->SetTitle(title);
			}			
			delete []title;
			delete []key;
			delete []outFileName;
		}

		free (mDest);
		free(mSrc);
	}  // IDOK == DoModal()
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Hashwert einer Datei berechnen, ohne dass die Datei selbst in den Dialog ge?ffnet werden 
// mu?. (Henrik Koy: Maerz. 2002)

void HashOfAFile()
{
	char fname[257], ftitle[128];
 
// == load INPUT
	{		
		// Initialisierung des File-Dialogs:
		CString sFileFilter;
		CString sDefName("*.*");
		CString sTitle;
		DWORD   dwFlags(OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST);
		sFileFilter.LoadString(IDS_OPEN_DOCUMENT_FILTER);
		sTitle.LoadString(IDS_OPENHASHOFAFILE);
		CFileDialog* doc;
		doc = new CFileDialog(TRUE, NULL, sDefName, dwFlags, sFileFilter);
		doc->m_ofn.lpstrTitle = sTitle;

		if(doc->DoModal()==IDOK)// Aufruf des File-Dialogs
		{			
			strcpy(ftitle, LPCTSTR (doc->GetFileName()));
			strcpy(fname, LPCTSTR (doc->GetPathName()));
			delete doc;
		}
		else
		{
			delete doc;
			return;
		}
	}
	CDlgSelectHashFunction Dlg;
	if ( Dlg.DoModal() == IDOK )
	{
		Secude::hash(fname, ftitle, Dlg.m_selectedHashFunction+1 );
	}
}


//####################################
//Myriam Zeuner, Projekt Hashdemo

void Hashdemo(const char *infile,const char *OldTitle)
{
	long FileSize;
	{
		struct stat *obj;
		obj = new (struct stat);
		int result = stat((const char*)infile,obj);
		FileSize = obj->st_size;
		delete obj;
		if ( result != 0 )
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_FileNotFound,pc_str,100);
			AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
			return;
		}
	}
	if ( FileSize > 16000 )
	{
		CString msg;
		msg.Format(IDS_STRING_Hashdemo_DateilaengeZuLang,MAX_LAENGE_STRTEXT);
		AfxMessageBox((LPCTSTR)msg,MB_ICONEXCLAMATION,IDD_HASH_DEMO + 0x20000UL - 0x30000);	
		FileSize = 16000;
	}

	CDlgHashDemo HashDlg;
	if ( 0 == HashDlg.loadData(infile, OldTitle, FileSize) )
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_KeineWerteGefunden,pc_str,100);
		AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
		return;
	}


	AfxInitRichEdit(); // GRRMPF
	HashDlg.DoModal();
	// Die Instanz der Klasse (Der Dialog) wird modal aufgerufen

}

//crypt.cpp
void SignatureTutorial(const char *infile, const char* OldTitle)
{
	if(CDlgSignatureDemo* SigDemo = new CDlgSignatureDemo)
	{
		SigDemo->InitDocument( infile, OldTitle );
		SigDemo->DoModal();
		delete SigDemo;
	}
}


//Christine St?tzel, September 2004
//Message Authentication Code
void CreateMac(const char *infile, const char *OldTitle)
{
	long FileSize;
	{
		struct stat *obj;	
		obj = new (struct stat);
		//obj speichert Statusinformationen ?ber infile
		int result = stat((const char*)infile, obj);
		//FileSize = Gr??e der Datei in Bytes
		FileSize = obj->st_size;
		delete obj;
		//wenn ein Fehler zur?ckgegeben wurde
		if ( result != 0 )
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_FileNotFound,pc_str,100);
			AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
			return;
		}
	}
	if ( FileSize > 16000 )
	{
		LoadString(AfxGetInstanceHandle(), IDS_STRING_MAC_ZuLang, pc_str, 120);
		AfxMessageBox(pc_str, MB_ICONEXCLAMATION|MB_OK);	
		FileSize = 16000;
	}
	
	OctetString *TextFile;
	TextFile = new OctetString;
	//noctets enth?lt die Anzahl der Bytes, octets ist ein Feld er entsprechenden Gr??e
	TextFile->noctets = FileSize;
	TextFile->octets  = new char [FileSize+1];
	//die aktuelle Datei kann zum Lesen ge?ffnet werden
	CFile text(infile, CFile::modeRead);
	//liest Daten aus der verkn?pften Datei in einen Puffer
	text.Read((void *)TextFile->octets, FileSize);
	text.Close();
	//Endekennung f?r das letzte Element
	TextFile->octets[FileSize] = '\0';
	if (strlen(TextFile->octets) == 0)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_Hashdemo_KeineWerteGefunden,pc_str,100);
		AfxMessageBox(pc_str,MB_ICONEXCLAMATION);
		return;
	}
	CDlgHMAC macdlg;
	//das file wird im CString strText des Dialogs gespeichert
	macdlg.strText = CString((char*)TextFile->octets);
	macdlg.DoModal();
	delete []TextFile->octets;
	delete TextFile;
}

long Rot13CaesarAscStart(SymbolArray & text, const char *infile)
{
	LoadText(infile, text);
	return text.GetSize();
}

void Rot13CaesarAscFinish(SymbolArray & text, const char * infile, char * sKey, BOOL bDecrypt, const char *OldTitle, UINT type, bool keyOffsetZero)
{
	char outfile[1024];
	SymbolArray Key(AppConv);
	
	// make sure only the first character of the key is actually used as Caesar key,
	// because using the whole key including the key offset part leads to some weird behaviour
	Key.ReadString(sKey, 1);

	// handle key offset (whether A=0 or A=1)
	if(!keyOffsetZero)
		Key += 1;

// == Encryption / Decryption
	SHOW_HOUR_GLASS
	GetTmpName(outfile,"cry",".txt");
	if (bDecrypt)
	{
		text -= Key;
	}
	else
	{
		text += Key;
	}
	text.Write(outfile);
	Reformat(infile, outfile, FALSE);

// == Open the new document
	OpenNewDoc(outfile, sKey, OldTitle, type, bDecrypt);

	HIDE_HOUR_GLASS
}

void SymmetricEncryption(int AlgId, cryptProvider provider, 
						 const char* infile, const char *OldTitle,
						 int fixed_keylength)
{
	CString Title, AlgString;
	AlgString.LoadString(AlgId);
	int errorCode = 0;
	char keybuffhex[256/4+1];
	unsigned char keybuffbin[256/8];

	Title.Format(IDS_STRING_KEYINPUT_SYMMETRIC, AlgString);
    CDlgKeyHexFixedLen KeyDialog;

	if ( !fixed_keylength ) switch (AlgId)
	{
		case IDS_CRYPT_MARS:
		case IDS_CRYPT_RC6:
		case IDS_CRYPT_RIJNDAEL:
		case IDS_CRYPT_SERPENT:
		case IDS_CRYPT_TWOFISH:
			KeyDialog.Init(Title,128,256,64);
			break;
		case IDS_CRYPT_DESL:
		case IDS_CRYPT_DES_CBC:
		case IDS_CRYPT_DES_ECB:
			KeyDialog.Init(Title,64,64,64,CRYPT_PARITY_DES);
			break;
		case IDS_CRYPT_TRIPLE_DES_CBC:
		case IDS_CRYPT_TRIPLE_DES_ECB:
			KeyDialog.Init(Title,128,128,128,CRYPT_PARITY_DES);
			break;
		case IDS_CRYPT_DESX:
		case IDS_CRYPT_DESXL:
			KeyDialog.Init(Title,192,192,192,CRYPT_PARITY_DESX);
			break;
		case IDS_CRYPT_IDEA:
			KeyDialog.Init(Title,128,128,128);
			break;
		case IDS_CRYPT_RC2:
		case IDS_CRYPT_RC4:
			KeyDialog.Init(Title,8,128,8);
			break;
		default:
			ASSERT(0);
	}
	else
		KeyDialog.Init(Title,fixed_keylength,fixed_keylength,1);

	if (KeyDialog.DoModal() != IDOK) 
		return;

	unsigned char *key = (unsigned char *) KeyDialog.GetKeyBytes();
	int            keylen = KeyDialog.GetKeyByteLength();
	ASSERT(keylen <= sizeof keybuffbin);
	for(int i=0;i<keylen; i++) keybuffbin[i] = key[i];
	
	ASSERT(2*keylen + 1 <= sizeof keybuffhex);
	for(int i=0; i<keylen; i++) 
		sprintf(keybuffhex+2*i,"%02.2X",keybuffbin[i]);

	char outfile[CRYPTOOL_PATH_LENGTH];
    GetTmpName(outfile,"cry",".tmp");

	try {
		if ( KeyDialog.ModeIsDecrypt() )
		{
			errorCode = sym_decrypt(AlgId, provider, keybuffhex, keylen<<3,infile, outfile);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		}
		else
		{
			errorCode = sym_encrypt(AlgId, provider, keybuffhex, keylen<<3,infile, outfile);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
		}
		char title[128];
		CAppDocument *NewDoc;
		NewDoc = theApp.OpenDocumentFileNoMRU(outfile,KeyDialog.GetKeyFormatted());
		remove(outfile);
		if(NewDoc) {
			MakeNewName3(title,sizeof(title),pc_str1,AlgString,OldTitle,KeyDialog.GetKeyFormatted());
			NewDoc->SetTitle(title);
		}
	}
	catch ( CString errStr ) {
		if ( provider == SECUDE_PROVIDER )
		{
			errStr.AppendChar('\n');
			errStr.Append(theApp.SecudeLib.LASTTEXT);
		}
		AfxMessageBox(errStr, MB_ICONSTOP);
	}
}


UINT SymmetricBruteForce(PVOID p)
{
// 
	int windowlen = theApp.Options.m_BFEntropyWindow;
	int r = 0, skip_parity = 0;


	CryptPar *par = (CryptPar *) p;
	if(par->flags & CRYPT_DO_WAIT_CURSOR)
		SHOW_HOUR_GLASS

//  get file size
	FILE *fi = fopen(par->infile,"rb");
	fseek(fi,0,SEEK_END);
	int datalen = ftell(fi);
	fclose(fi);
	
	if(datalen < 1) 
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, 1);
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			HIDE_HOUR_GLASS
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return r;
	}
	if(datalen > windowlen)     
		datalen=windowlen;

//	load brute force pattern
	algorithm_info *info = (algorithm_info*)par->key;
	CString AlgTitle;
	AlgTitle.LoadString(info->AlgId);

	CDlgBruteForceAES KeyDialog;

//	Skip parity bits during enumeration (i.e. DES variants)
	if ( info->AlgId == IDS_CRYPT_DES_CBC ||
		 info->AlgId == IDS_CRYPT_DES_ECB ||
		 info->AlgId == IDS_CRYPT_TRIPLE_DES_CBC ||
		 info->AlgId == IDS_CRYPT_TRIPLE_DES_ECB ||
		 info->AlgId == IDS_CRYPT_DESL )
		skip_parity = CRYPT_PARITY_DES;
	else if ( info->AlgId == IDS_CRYPT_DESX || info->AlgId == IDS_CRYPT_DESXL )
		skip_parity = CRYPT_PARITY_DESX;
	else
		skip_parity = CRYPT_PARITY_NONE;

	if(KeyDialog.Display(AlgTitle.GetBuffer(),par->keylenmin,par->keylenmax,par->keylenstep,skip_parity)!=IDOK)
	{
		if(par->flags & CRYPT_DO_WAIT_CURSOR)
			HIDE_HOUR_GLASS
		par->flags |= CRYPT_DONE;
		FreePar(par);
		return r;
	}

//	initialize brute force
	int key_bitlength = KeyDialog.GetBinlen();

	// load ciphertext 
	sym_brute *brute;
	{
		char *cipher;
		cipher = (char*)malloc(datalen);
		fi = fopen(par->infile,"rb");
		int inputSize = fread(cipher,1,datalen,fi);
		fclose(fi);
		// initialise ...
		brute = init_sym_brute(info->AlgId, info->provider, key_bitlength, cipher, datalen);
		free(cipher);
	}

//  start progress dialog
	CString title;
	title.Format(IDS_STRING_ANALYSE_ON,AlgTitle);
	if(par->flags & CRYPT_DO_PROGRESS)
	{
		CString message;
		message.Format(IDS_STRING_MSG_SEARCHING_COMPLETE,KeyDialog.GetSearchBitLen());
		theApp.fs.setModelTitleFormat(&KeyDialog,title,message);
		theApp.fs.Display();
	}

//  Build alphabet set
	int alphaSet[256];
	for (int i=0; i<256; i++)
	{
		switch ( theApp.Options.i_alphabetOptions ) {
			case 0: alphaSet[i] = 1;
				break;
			case 1: alphaSet[i] = ( i >= 32 ) ? 1 : 0;
				break;
			case 2: alphaSet[i] = ( 0 <= theApp.TextOptions.getAlphabet().Find((char)i) ) ? 1 : 0;
				break;
		}
		if ( i == (int)'\0' || i == (int)'\n' || i == (int)'\r' || i == (int)'\t' )
			alphaSet[i] = 1;
	}

//	precomputations for fast entropy calculation
	double entr;
	double *xlogx = new double[datalen + 1];
	if (!xlogx) return 0;
	xlogx[0] = 0.0;
	int i;
	for (i = 1; i <= datalen; i++) 
		xlogx[i] = -1.0 * i * log(i/double(datalen))/log(2.0);


//  brute force
#define BRUTEFORCE_HEAPSIZE 50
	CBruteForceHeap candidates;
	candidates.init( key_bitlength/8, datalen, BRUTEFORCE_HEAPSIZE);

	int pos=0;
	int distr[256];
	theApp.fs.startClock();

	while (KeyDialog.Step())    // next key
	{           
		if(par->flags & CRYPT_DO_PROGRESS)
		{
			if(theApp.fs.m_canceled)
			{
				// theApp.fs.cancel();
				break;
			}
		}

 		char *plain = brute->decrypt(KeyDialog.GetData());

		if ( theApp.Options.i_alphabetOptions )
		{
			BOOL decryptionResult_invalid = FALSE;
			for (int i=0; i<brute->decrypted_bytes; i++)
				if (!alphaSet[(int)plain[i]])
				{
					decryptionResult_invalid = TRUE;
					break;
				}
			if ( decryptionResult_invalid )
				continue;
		}

		//	compute entropy
		memset(distr,0,sizeof(distr));
		for(i=0;i<brute->decrypted_bytes;i++)
			distr[(unsigned char) plain[i]]++;
		entr = 0.0;
		i = 0; 
		while (i<256) {
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
			entr += xlogx[distr[i++]];
		}
		entr /= (double)datalen;

		if ( candidates.check_add( entr ) )
			candidates.add_candidate( entr, KeyDialog.GetData(), plain, brute->decrypted_bytes );
	}

	if(par->flags & CRYPT_DO_PROGRESS) theApp.fs.cancel();
	WaitForSingleObject( theApp.fs.pEvent.m_hObject, INFINITE );
	//theApp.fs.m_displayed = false;

	if ( !candidates.heapsize )
	{
		Message(IDS_STRING_NO_VALID_KEYS_FOUND, MB_ICONINFORMATION);
	}
	else
	{
		candidates.sort();
		CListResults dlgResults(datalen);
		dlgResults.LoadList( candidates.list, candidates.heapsize );
		// TODO load list
		if ( IDOK == dlgResults.DoModal() )
		{
			char outfile[CRYPTOOL_PATH_LENGTH];
			char line[CRYPTOOL_PATH_LENGTH];
			GetTmpName(outfile,"cry",".tmp");
			try {
				sym_decrypt(info->AlgId, info->provider, dlgResults.get_keyhex(), key_bitlength, par->infile, outfile);
				
				LoadString(AfxGetInstanceHandle(),IDS_STRING_AUTOMATIC_ANALYSE,pc_str,STR_LAENGE_STRING_TABLE);
				MakeNewName3(line,sizeof(line),pc_str, AlgTitle, par->OldTitle, dlgResults.get_keyhex());
				theApp.ThreadOpenDocumentFileNoMRU(outfile,line,dlgResults.get_keyhex());
			}
			catch ( CString errStr ) {
				if ( info->provider == SECUDE_PROVIDER )
				{
					errStr.AppendChar('\n');
					errStr.Append(theApp.SecudeLib.LASTTEXT);
				}
				AfxMessageBox(errStr, MB_ICONSTOP);
			}
		}
	}

	delete brute;

	par->flags |= CRYPT_DONE;
	FreePar(par);

	return r;
}

// Rail Fence encryption (part of the simple transpositions dialog)
// RETURN VALUES:		1 (success), -1 (invalid key), -2 (invalid file handle)
int RailFenceEncryption(const char *infile, const char *oldTitle, int key, int offset, bool encrypt) {
	// since this is the rail fence encryption, the type is: 1
	const int type = 1;
	
	// create a handle for the input file
	std::ifstream fileInput;
	fileInput.open(infile);
	if(!fileInput) return -2;

	// store the contents of the file in bufferString
	std::string bufferString;
	char buffer[4096 + 1];
	memset(buffer, 0, 4096 + 1);
	do {
		memset(buffer, 0, 4096 + 1);
		fileInput.read(buffer, 4096);
		bufferString.append(buffer);
	}
	while(!fileInput.eof());
	fileInput.close();

	// we use this later to restore characters that were not to be touched
	std::string originalBufferString = bufferString;

	// ignore non-alphabet characters
	CString bufferStringValid;
	for(unsigned int i=0; i<bufferString.length(); i++) {
		if(theApp.TextOptions.getAlphabet().Find(bufferString[i]) != -1) {
			bufferStringValid.AppendChar(bufferString[i]);
		}
	}
	bufferString = bufferStringValid;

	// IMPORTANT: the key is invalid if it is "1" or >= the length of the clear text
	if(key <= 1 || key >= (int)bufferString.length()) {
		return -1;
	}

	// *** BEGIN ENCRYPTION/DECRYPTION PROCESS ***
	int textLength = bufferString.length();
	char *clearText = new char[textLength + offset + 1];
	memset(clearText, 0, textLength + offset + 1);
	char *cipherText = new char[textLength + offset + 1];
	memset(cipherText, 0, textLength + offset + 1);

	// ******************
	// *** ENCRYPTION ***
	// ******************
	if(encrypt) {
		// the period of the encryption
		int n = 2 * key - 2; 
		if(offset > 0) offset = (offset % n);
		if(offset < 0) offset = (offset % n) + n;
		// get the clear text and respect leading zeros (thus, the offset variable)
		memcpy(clearText + offset, bufferString.c_str(), textLength);
		// now, process all characters of the clear text
		int charactersProcessed = 0;
		for(int d=0; d<=n/2; d++) {
			for(int j=0; j<textLength+offset; j++) {
				if(j%n == d || j%n == n-d) {
					cipherText[charactersProcessed++] = clearText[j];
				}	
			}
		}
		// remove zeros
		char *cipherTextTemp = new char[textLength + 1];
		memset(cipherTextTemp, 0, textLength + 1);
		for(int i=0; i<textLength+offset; i++) {
			if(cipherText[i] != 0) {
				strncat(cipherTextTemp, cipherText + i, 1);
			}
		}
		// store the result in "cipherText"
		memset(cipherText, 0, textLength + 1);
		memcpy(cipherText, cipherTextTemp, textLength);

		// free memory
		delete[] cipherTextTemp;
	}
	// ******************
	// *** DECRYPTION ***
	// ******************
	else {
		// the period of the encryption
		int n = 2 * key - 2;
		offset = (offset % n);
		if(offset < 0) offset = (offset + n);
		// get the cipher text
		memcpy(cipherText, bufferString.c_str(), textLength);
		// process all characters of the cipher text
		int *charactersInRow = new int[key];
		memset(charactersInRow, 0, key * 4);
		int currentRow = 0;
		memset(charactersInRow, 0, 3);
		std::string *rows = new std::string[key];
		// flatten out the cipher text
		for(int index=offset; index<textLength+offset; index++) {
			// determine which row we're in (zero-based, from top down)
			int localOffset = index % n;
			// is it going up or down the fence?
			if(localOffset < key) { // *down*
				currentRow = localOffset;
			}
			else {									// *up*
				currentRow = (key - 1);
				int steps = localOffset - (key - 1);
				currentRow -= steps;
			}	
			charactersInRow[currentRow]++;
		}
		// now, assemble each row
		int charactersProcessed = 0;
		for(int i=0; i<key; i++) {
			char *temp = new char[textLength + 1];
			memset(temp, 0, textLength + 1);
			memcpy(temp, cipherText + charactersProcessed, charactersInRow[i]);
			rows[i].append(temp);
			charactersProcessed += charactersInRow[i];
			// free memory
			delete[] temp;
		}
		// transform flattened out cipher text into clear text
		int *charactersInRowProcessed = new int[key];
		memset(charactersInRowProcessed, 0, key * 4);
		charactersProcessed = 0;
		for(int index=offset; index<textLength+offset; index++) {
			// determine which row we're in (zero-based, from top down)
			int localOffset = index % n;
			// is it going up or down the fence?
			if(localOffset < key) { // *down*
				currentRow = localOffset;
			}
			else {									// *up*
				currentRow = (key - 1);
				int steps = localOffset - (key - 1);
				currentRow -= steps;
			}	
			// construct the clear text character by character
			clearText[charactersProcessed++] = rows[currentRow].c_str()[charactersInRowProcessed[currentRow]++];
		}
		// this is ugly, but we're working on "cipherText" in the lines below; thus we copy from 
		// "clearText" to "cipherText" although we were actually decrypting here
		memset(cipherText, 0, textLength + 1);
		memcpy(cipherText, clearText, strlen(clearText));

		// free memory
		delete[] rows; 
		delete[] charactersInRow;
		delete[] charactersInRowProcessed;
	}

	std::string cipherTextString = cipherText;
	delete clearText;
	delete cipherText;
	// *** END ENCRYPTION/DECRYPTION PROCESS ***

	// now, after encryption/decryption, restore characters that were not to be touched
	CString finalCipherTextString;
	if ( theApp.TextOptions.getKeepCharactersNotPresentInAlphabetUnchanged() ) 
   {
		for (unsigned int i=0, j=0; i<originalBufferString.length() && j<cipherTextString.length(); i++) 
      {
			// if we do have a character here that was NOT part of the alphabet, leave it 
			// alone and store it in the finalCipherTextString variable
			if(theApp.TextOptions.getAlphabet().Find(originalBufferString[i]) == -1) 
         {
				finalCipherTextString.Append((CString)originalBufferString.c_str()[i]);
			}
			else {
				finalCipherTextString.Append((CString)cipherTextString.c_str()[j++]);
			}
		}
	}
	else {
		finalCipherTextString = (CString)cipherTextString.c_str();
	}
	cipherTextString = finalCipherTextString;

	// create a name for the outfile
	char outfile[4096];
	GetTmpName(outfile, "cry", ".txt");

	// create a file handle for the output file
	std::ofstream fileOutput;
	fileOutput.open(outfile, ios::out);
	if(!fileOutput) return -2;

	// write the output file
	fileOutput.write(cipherTextString.c_str(), cipherTextString.length());
	fileOutput.close();

	// complete key as string (TYPE, KEY, KEY OFFSET)
	CString stringCompleteKey;
	char stringType[4096 + 1];
	char stringKey[4096 + 1];
	char stringOffset[4096 + 1];
	memset(stringType, 0, 4096 + 1);
	memset(stringKey, 0, 4096 + 1);
	memset(stringOffset, 0, 4096 + 1);
	itoa(type, stringType, 10);
	itoa(key, stringKey, 10);
	itoa(offset, stringOffset, 10);
	stringCompleteKey.Append("TYPE: ");
	stringCompleteKey.Append(stringType);
	stringCompleteKey.Append(", KEY: ");
	stringCompleteKey.Append(stringKey);
	stringCompleteKey.Append(", KEY OFFSET: ");
	stringCompleteKey.Append(stringOffset);

	// open the new document
	CDocument *document = theApp.OpenDocumentFileNoMRU(outfile, stringCompleteKey);
	if(document) {
		char title[4096];
		memset(title, 0, 4096);
		// set the document title depending on whether we have an encryption or a decryption
		if(encrypt) LoadString(AfxGetInstanceHandle(), IDS_STRING_RAIL_FENCE_ENCRYPTION_OF, pc_str, STR_LAENGE_STRING_TABLE);
		else LoadString(AfxGetInstanceHandle(), IDS_STRING_RAIL_FENCE_DECRYPTION_OF, pc_str, STR_LAENGE_STRING_TABLE);
		// now add the old title and the key into the new title
		sprintf(title, pc_str, oldTitle, stringCompleteKey);
		// set the new document title
		document->SetTitle(title);
	}

	return 1;
}

// Scytale encryption (part of the simple transpositions dialog)
// RETURN VALUES:		1 (success), -1 (invalid key), -2 (invalid file handle)
int ScytaleEncryption(const char *infile, const char *oldTitle, int key, int offset, bool encrypt) {
	// since this is the Scytale encryption, the type is: 0
	const int type = 0;

	// create a handle for the input file
	std::ifstream fileInput;
	fileInput.open(infile);
	if(!fileInput) return -2;

	// store the contents of the file in bufferString
	std::string bufferString;
	char buffer[4096 + 1];
	memset(buffer, 0, 4096 + 1);
	do {
		memset(buffer, 0, 4096 + 1);
		fileInput.read(buffer, 4096);
		bufferString.append(buffer);
	}
	while(!fileInput.eof());
	fileInput.close();

	// we use this later to restore characters that were not to be touched
	std::string originalBufferString = bufferString;

	// ignore non-alphabet characters
	CString bufferStringValid;
	for(unsigned int i=0; i<bufferString.length(); i++) {
		if(theApp.TextOptions.getAlphabet().Find(bufferString[i]) != -1) {
			bufferStringValid.AppendChar(bufferString[i]);
		}
	}
	bufferString = bufferStringValid;

	// IMPORTANT: the key is invalid if it is "1" or >= the length of the clear text
	if(key <= 1 || key >= (int)bufferString.length()) {
		return -1;
	}

	// *** BEGIN ENCRYPTION/DECRYPTION PROCESS ***
	int textLength = bufferString.length();
	char *clearText = new char[textLength + offset + 1];
	memset(clearText, 0, textLength + offset + 1);
	memcpy(clearText, bufferString.c_str(), textLength);
	char *cipherText = new char[textLength + offset + 1];
	memset(cipherText, 0, textLength + offset + 1);

	// we need this check to make sure too big offsets don't mess up the encryption; thus, 
	// by convention, offsets bigger than the text length are reduced modulo the text length
	if(offset > textLength) offset = textLength;

	// we need to know how many columns ("windings") we have on our Scytale
	int numberOfColumns = (textLength + offset) / key;
	if((textLength + offset) % key) numberOfColumns++;

	// in the context of the Scytale encryption "the offset" indicates which winding 
	// we're starting to write on (0 = the first winding, 1 = the second winding...)
	offset = offset % numberOfColumns;

	// ENCRYPTION
	if(encrypt) {

		int charactersProcessed = 0;

		// declare a vector of rows (size: key)
		char **rows = new char*[key];
		for(int row=0; row<key; row++) {
			rows[row] = new char[numberOfColumns + 1];
			memset(rows[row], 0, numberOfColumns + 1);
		}
		int *charactersInRowProcessed = new int[key];
		memset(charactersInRowProcessed, 0, 4 * key);

		// fill the rows
		for(int index=0; index<textLength+offset; index++) {
			int row = index / numberOfColumns;
			if(offset > index) memset(rows[row] + charactersInRowProcessed[row]++, 0, 1);
			else memcpy(rows[row] + charactersInRowProcessed[row]++, clearText + charactersProcessed++, 1);
		}
		
		// create the ciphertext
		charactersProcessed = 0;
		for(int column=0; column<numberOfColumns; column++) {
			for(int row=0; row<key; row++) {
				// ignore zero bytes
				if(rows[row][column] == 0) continue;
				memcpy(cipherText + charactersProcessed++, rows[row] + column, 1);
			}
		}

		// free memory
		delete[] rows;
		delete[] charactersInRowProcessed;
	}
	// DECRYPTION
	else {
		
		int charactersProcessed = 0;

		// declare a vector of rows (size: key)
		char **rows = new char*[key];
		for(int row=0; row<key; row++) {
			rows[row] = new char[numberOfColumns + 1];
			memset(rows[row], 0, numberOfColumns + 1);
		}
		int *charactersInRowProcessed = new int[key];
		memset(charactersInRowProcessed, 0, 4 * key);

		// fill the rows
		charactersProcessed = 0;
		for(int column=0; column<numberOfColumns; column++) {
			for(int row=0; row<key; row++) {
				// ignore zero bytes
				if(offset > column && row == 0) continue;
				// make sure we end rows correctly (that is, not copy too much)
				if(row*numberOfColumns + column - offset >= textLength) continue;
				memcpy(rows[row] + charactersInRowProcessed[row]++, clearText + charactersProcessed++, 1); 
			}
		}	

		// create the clear text
		charactersProcessed = 0;
		for(int row=0; row<key; row++) {
			memcpy(cipherText + charactersProcessed, rows[row], strlen(rows[row]));
			charactersProcessed += strlen(rows[row]);
		}

		// flomar, 03/10/2009
		// again, it's ugly that we're storing the result in cipherText instead of clearText 
		// although we're executing a decryption; this will be fixed when there's more time

		// free memory
		delete[] rows;
		delete[] charactersInRowProcessed;
	}

	std::string cipherTextString = cipherText;
	delete clearText;
	delete cipherText;
	// *** END ENCRYPTION/DECRYPTION PROCESS ***

	// now, after encryption/decryption, restore characters that were not to be touched
	CString finalCipherTextString;
	if ( theApp.TextOptions.getKeepCharactersNotPresentInAlphabetUnchanged() ) 
   {
		for ( unsigned int i=0, j=0; i<originalBufferString.length() && j<cipherTextString.length(); i++ ) 
      {
			// if we do have a character here that was NOT part of the alphabet, leave it 
			// alone and store it in the finalCipherTextString variable
			if(theApp.TextOptions.getAlphabet().Find(originalBufferString[i]) == -1) 
         {
				finalCipherTextString.Append((CString)originalBufferString.c_str()[i]);
			}
			else 
         {
				finalCipherTextString.Append((CString)cipherTextString.c_str()[j++]);
			}
		}
	}
	else {
		finalCipherTextString = (CString)cipherTextString.c_str();
	}
	cipherTextString = finalCipherTextString;

	// create a name for the outfile
	char outfile[4096];
	GetTmpName(outfile, "cry", ".txt");

	// create a file handle for the output file
	std::ofstream fileOutput;
	fileOutput.open(outfile, ios::out);
	if(!fileOutput) return -2;

	// write the output file
	fileOutput.write(cipherTextString.c_str(), cipherTextString.length());
	fileOutput.close();

	// complete key as string (TYPE, KEY, KEY OFFSET)
	CString stringCompleteKey;
	char stringType[4096 + 1];
	char stringKey[4096 + 1];
	char stringOffset[4096 + 1];
	memset(stringType, 0, 4096 + 1);
	memset(stringKey, 0, 4096 + 1);
	memset(stringOffset, 0, 4096 + 1);
	itoa(type, stringType, 10);
	itoa(key, stringKey, 10);
	itoa(offset, stringOffset, 10);
	stringCompleteKey.Append("TYPE: ");
	stringCompleteKey.Append(stringType);
	stringCompleteKey.Append(", KEY: ");
	stringCompleteKey.Append(stringKey);
	stringCompleteKey.Append(", KEY OFFSET: ");
	stringCompleteKey.Append(stringOffset);

	// open the new document
	CDocument *document = theApp.OpenDocumentFileNoMRU(outfile, stringCompleteKey);
	if(document) {
		char title[4096];
		memset(title, 0, 4096);
		// set the document title depending on whether we have an encryption or a decryption
		if(encrypt) LoadString(AfxGetInstanceHandle(), IDS_STRING_SCYTALE_ENCRYPTION_OF, pc_str, STR_LAENGE_STRING_TABLE);
		else LoadString(AfxGetInstanceHandle(), IDS_STRING_SCYTALE_DECRYPTION_OF, pc_str, STR_LAENGE_STRING_TABLE);
		// now add the old title and the key into the new title
		sprintf(title, pc_str, oldTitle, stringCompleteKey);
		// set the new document title
		document->SetTitle(title);
	}

	return 1;
}

void Solitaire(const char *infile, const char *OldTitle)
{
	CDlgSolitaire mySol(infile, NULL);
	if ( IDOK != mySol.DoModal() )
		return;

	char outfile[1024];

	SHOW_HOUR_GLASS
	GetTmpName(outfile,"cry",".txt");
	
	crypt_solitaire( mySol.sol_action, infile, outfile, CString(mySol.InitialDeck) );

// == Open the new document
	OpenNewDoc( outfile, mySol.InitialDeck, OldTitle, IDS_CRYPT_SOLITAIRE, ( mySol.sol_action ) ? 0 : 1 );

	HIDE_HOUR_GLASS
}
