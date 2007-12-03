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


// DlgSignatureAttack.cpp: Implementierungsdatei
//

#include "stdafx.h"

#include "CrypToolApp.h"
#include "CrypToolTools.h"
#include "DlgSignatureAttack.h"
#include "DlgOptionsSignatureAttack.h"
#include "DlgStatisticsSignatureAttack.h"
#include "FileTools.h"
#include "CrypToolTools.h"
#if !defined(_MSC_VER) || _MSC_VER <= 1200
#include <iostream.h>
#include <fstream.h>
#else
#include <iostream>
#include <fstream>
using namespace std;
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include "SignatureAttack.h"
#include "SignatureAttackMFC.h"
#include "OptionsForSignatureAttack.h"
#include "ErrorcodesForSignatureAttack.h"
#include "DlgShowProgress.h"
#include ".\dlgsignatureattack.h"

// Verzeichnis, in dem CT gerade l�uft (siehe CrypToolApp.cpp)
extern char *Pfad;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgSignatureAttack 


CDlgSignatureAttack::CDlgSignatureAttack(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSignatureAttack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSignatureAttack)
	m_file_harmless = _T("");
	m_file_dangerous = _T("");
	//}}AFX_DATA_INIT
}


void CDlgSignatureAttack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSignatureAttack)
	DDX_Control(pDX, IDC_FILE_HARMLESS, m_control_file_harmless);
	DDX_Control(pDX, IDC_FILE_DANGEROUS, m_control_file_dangerous);
	DDX_Control(pDX, IDC_COMPUTE, m_control_compute);
	DDX_Text(pDX, IDC_FILE_HARMLESS, m_file_harmless);
	DDX_Text(pDX, IDC_FILE_DANGEROUS, m_file_dangerous);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSignatureAttack, CDialog)
	//{{AFX_MSG_MAP(CDlgSignatureAttack)
	ON_BN_CLICKED(IDC_OPTIONS, OnOptions)
	ON_BN_CLICKED(IDC_BROWSE_HARMLESS, OnBrowseOriginal)
	ON_BN_CLICKED(IDC_BROWSE_DANGEROUS, OnBrowseFake)
	ON_BN_CLICKED(IDC_COMPUTE, OnCompute)
	ON_EN_UPDATE(IDC_FILE_DANGEROUS, OnUpdateFileFake)
	ON_EN_UPDATE(IDC_FILE_HARMLESS, OnUpdateFileOriginal)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_USEDEFAULTMESSAGES, OnBnClickedButtonUsedefaultmessages)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgSignatureAttack 

void CDlgSignatureAttack::OnOptions() 
{
	CDlgOptionsSignatureAttack DlgOSA;
	DlgOSA.DoModal();
}

void CDlgSignatureAttack::OnBrowseOriginal() 
{
	UpdateData(TRUE);
	BrowseDocument(m_file_harmless);
	UpdateData(FALSE);
}

void CDlgSignatureAttack::OnBrowseFake() 
{
	UpdateData(TRUE);
	BrowseDocument(m_file_dangerous);
	UpdateData(FALSE);
}

void CDlgSignatureAttack::OnCompute() 
{
	unsigned long u_SigAttTestMode = (unsigned long)FALSE;
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS ) == ERROR_SUCCESS )
	{
		CT_READ_REGISTRY_DEFAULT(u_SigAttTestMode, "SignatureAttackTestMode", u_SigAttTestMode);
		CT_CLOSE_REGISTRY();

		if (u_SigAttTestMode)
		{
			SHOW_HOUR_GLASS

			bool DocFiles = false;
			char FilePath[256], *HarmlessText, *DangerousText;
			CString LogPath;
			CWinThread *CWThread;
			FILE *SigAttTest;
			ifstream ifstr_Harmless, ifstr_Dangerous;
			int HarmlessDocLength, DangerousDocLength;
			MSG FloydMessage;
			ofstream ofstr_Harmless, ofstr_Dangerous;
			struct stat stat_object;
			time_t StartTime;
			UINT MessageID;


			CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS );
			unsigned long l_SignificantBitLengthMIN = 0;
			CT_READ_REGISTRY_DEFAULT(l_SignificantBitLengthMIN, "SignificantBitLengthMIN", l_SignificantBitLengthMIN);
			unsigned long l_SignificantBitLengthMAX = 0;
			CT_READ_REGISTRY_DEFAULT(l_SignificantBitLengthMAX, "SignificantBitLengthMAX", l_SignificantBitLengthMAX);
			unsigned long l_SignificantBitLengthJump = 1;
			CT_READ_REGISTRY_DEFAULT(l_SignificantBitLengthJump, "SignificantBitLengthJump", l_SignificantBitLengthJump);
			unsigned long l_HashAlgorithmIDMIN = 0; 
			CT_READ_REGISTRY_DEFAULT(l_HashAlgorithmIDMIN, "HashAlgorithmIDMIN", l_HashAlgorithmIDMIN);
			unsigned long l_HashAlgorithmIDMAX = 0;
			CT_READ_REGISTRY_DEFAULT(l_HashAlgorithmIDMAX, "HashAlgorithmIDMAX", l_HashAlgorithmIDMAX);
			unsigned long l_Attempts = 0;
			CT_READ_REGISTRY_DEFAULT(l_Attempts, "Attempts", l_Attempts);
			unsigned long l_AttemptsMAX = ULONG_MAX;
			CT_READ_REGISTRY_DEFAULT(l_AttemptsMAX, "AttemptsMAX", l_AttemptsMAX);
			unsigned long SignificantBitLengthCounter, HashAlgorithmsCounter, AttemptsCounter, TotalAttemptsCounter = 0;
			char s_logPath[1025] = "C:\\";
			unsigned long max_strLength = 1024;
			CT_READ_REGISTRY_DEFAULT(s_logPath, "LogPath", s_logPath, max_strLength);
			LogPath = s_logPath;
			CT_CLOSE_REGISTRY();

			time(&StartTime);

			for (SignificantBitLengthCounter = l_SignificantBitLengthMIN; SignificantBitLengthCounter <= l_SignificantBitLengthMAX; 
				SignificantBitLengthCounter += l_SignificantBitLengthJump)
			{

				CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE );
				CT_WRITE_REGISTRY(SignificantBitLengthCounter, "SignatureAttackSignificantBitLength");
				CT_CLOSE_REGISTRY();

				for (HashAlgorithmsCounter = l_HashAlgorithmIDMIN; HashAlgorithmsCounter <= l_HashAlgorithmIDMAX;
					HashAlgorithmsCounter ++)
				{
					CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE );
					CT_WRITE_REGISTRY(HashAlgorithmsCounter, "SignatureAttackHashAlgorithmID");
					CT_CLOSE_REGISTRY();

					for (AttemptsCounter = 0; AttemptsCounter < l_Attempts; AttemptsCounter ++)
					{
						if (TotalAttemptsCounter == l_AttemptsMAX)
						{
							return;
						}
						TotalAttemptsCounter ++;

						char tmpStr[1025]; unsigned long tmpStrLength = 1024;
						CT_OPEN_REGISTRY_SETTINGS( KEY_READ );
						CT_READ_REGISTRY(tmpStr, "HarmlessDocument", tmpStrLength);
						m_file_harmless = tmpStr;
						CT_READ_REGISTRY(tmpStr, "DangerousDocument", tmpStrLength);
						m_file_dangerous = tmpStr;
						CT_CLOSE_REGISTRY();


		#ifdef _SIG_ATT_PRE_RPE_MODIFY

						if ( u_SigAttTestMode ) // F�r Statistische Unabh�ngigkeit, vor jedem Versuch Pre(Pre)Modifizieren
						{
							ifstr_Harmless.open(m_file_harmless, ios::in | ios::binary);
							stat((const char *) m_file_harmless, & stat_object);
							if (0 == stat_object.st_size)
							{
								GenerateMessageText(15);
								return;
							}
							HarmlessDocLength = stat_object.st_size;
							HarmlessText = new char[HarmlessDocLength];
							ifstr_Harmless.read(HarmlessText, HarmlessDocLength);
							ifstr_Harmless.close();
							ofstr_Harmless.open(m_file_harmless, ios::out | ios::binary);
							HarmlessText[HarmlessDocLength-1] = AttemptsCounter + 32;
							ofstr_Harmless.write(HarmlessText, HarmlessDocLength);
							ofstr_Harmless.close();


							ifstr_Dangerous.open(m_file_dangerous, ios::in | ios::binary);
							stat((const char *) m_file_dangerous, & stat_object);
							if (0 == stat_object.st_size)
							{
								GenerateMessageText(15);
								return;
							}
							DangerousDocLength = stat_object.st_size;
							DangerousText = new char[DangerousDocLength];
							ifstr_Dangerous.read(DangerousText, DangerousDocLength);
							ifstr_Dangerous.close();
							ofstr_Dangerous.open(m_file_dangerous, ios::out | ios::binary);
							DangerousText[DangerousDocLength-1] = AttemptsCounter + 32;
							ofstr_Dangerous.write(DangerousText, DangerousDocLength);
							ofstr_Dangerous.close();
						}
		#endif

						OptionsForSignatureAttack OFSA(m_file_harmless, m_file_dangerous, u_SigAttTestMode);
						if (0 != OFSA.GetErrorcode())
						{
							return;
						}

						if (false == DocFiles)
						{
							DocFiles = true;

							ifstr_Harmless.open(m_file_harmless, ios::in | ios::binary);
							ifstr_Dangerous.open(m_file_dangerous, ios::in | ios::binary);
							_snprintf(FilePath, sizeof(FilePath) - 1, "%s%d%s", LogPath, StartTime, _SIG_ATT_HARMLESS);
							ofstr_Harmless.open(FilePath, ios::out | ios::binary);
							_snprintf(FilePath, sizeof(FilePath) - 1, "%s%d%s", LogPath, StartTime, _SIG_ATT_DANGEROUS);
							ofstr_Dangerous.open(FilePath, ios::out | ios::binary);
							if (!ifstr_Harmless || !ifstr_Dangerous || !ofstr_Harmless || !ofstr_Dangerous)
							{
								return;
							}

							stat((const char *) m_file_harmless, & stat_object);
							if (0 == stat_object.st_size)
							{
								GenerateMessageText(15);
								return;
							}
							HarmlessDocLength = stat_object.st_size;
							HarmlessText = new char[HarmlessDocLength];					

							stat((const char *) m_file_dangerous, & stat_object);
							if (0 == stat_object.st_size)
							{
								GenerateMessageText(15);
								return;
							}
							DangerousDocLength = stat_object.st_size;
							DangerousText = new char[DangerousDocLength];

							ifstr_Harmless.read(HarmlessText, HarmlessDocLength);
							ofstr_Harmless.write(HarmlessText, HarmlessDocLength);

							ifstr_Harmless.close();
							ofstr_Harmless.close();

							ifstr_Dangerous.read(DangerousText, DangerousDocLength);
							ofstr_Dangerous.write(DangerousText, DangerousDocLength);
							ifstr_Dangerous.close();
							ofstr_Dangerous.close();

							delete []HarmlessText;
							delete []DangerousText;
							
							_snprintf(FilePath, sizeof(FilePath) - 1, "%s%d%s", LogPath, StartTime, _SIG_ATT_HEADER);
							SigAttTest = fopen(FilePath, "w+");
							if (NULL == SigAttTest)
							{
								return;
							}

							fprintf(SigAttTest, "Birthday Attack on Digital Signatures -- Configuration\n\nThe File CrypTool.ini has set up the following Configuration:\n\n");
							fprintf(SigAttTest, "SignificantBitLengthMIN=%d\n"
									"SignificantBitLengthMAX=%d\n"
									"SignificantBitLengthJump=%d\n"
									"HashAlgorithmIDMIN=%d\n"
									"HashAlgorithmIDMAX=%d\n"
									"Attempts=%d\n"
									"HarmlessDocument=%s\n"
									"DangerousDocument=%s\n"
									"LogPath=%s\n", 
								l_SignificantBitLengthMIN , l_SignificantBitLengthMAX, l_SignificantBitLengthJump,
							   l_HashAlgorithmIDMIN, l_HashAlgorithmIDMAX, l_Attempts,
							   m_file_harmless, m_file_dangerous, LogPath);



							unsigned long u_SignatureAttackModificationMethod = 0;
							CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS );
							CT_READ_REGISTRY_DEFAULT(u_SignatureAttackModificationMethod, "SignatureAttackModificationMethod", u_SignatureAttackModificationMethod);
							fprintf(SigAttTest,
								"\n\nInternal Information\n\nModificationMethod=%d\nHarmlessFile=%s%d%s\nHarmlessFileLength=%d\nDangerousFile=%s%d%s\nDangerousFileLength=%d",
								u_SignatureAttackModificationMethod,
								LogPath, StartTime, _SIG_ATT_HARMLESS, HarmlessDocLength,
								LogPath, StartTime,	_SIG_ATT_DANGEROUS, DangerousDocLength);

		#ifdef _SIG_ATT_SPEED_INCREMENT

							fprintf(SigAttTest, "\nModifyOriginalDocumentBeforeRun=1");

		#endif

		#ifndef _SIG_ATT_SPEED_INCREMENT

							fprintf(SigAttTest, "\nModifyOriginalDocumentBeforeRun=0");

		#endif

		#ifdef _SIG_ATT_MODIFYING_OPTIMIZER

							fprintf(SigAttTest, "\nSpeedOptimizer=1");

		#endif

		#ifndef _SIG_ATT_MODIFYING_OPTIMIZER

							fprintf(SigAttTest, "\nSpeedOptimizer=0");

		#endif

		#ifdef _SIG_ATT_ALWAYS_INIT_HASH

							fprintf(SigAttTest, "\nAlwaysInitHash=1");

		#endif

		#ifndef _SIG_ATT_ALWAYS_INIT_HASH

							fprintf(SigAttTest, "\nAlwaysInitHash=0");

		#endif

							strcpy(tmpStr, "");
							max_strLength = 1024;
							CT_READ_REGISTRY(tmpStr, "Comments", max_strLength);
							CT_CLOSE_REGISTRY();
							

							fprintf(SigAttTest, "\nComments=%s", tmpStr);
							fclose(SigAttTest);

							_snprintf(FilePath, sizeof(FilePath) - 1, "%s%d%s", LogPath, StartTime, _SIG_ATT_LOG);
							SigAttTest = fopen(FilePath, "w+");
							if (NULL == SigAttTest)
							{
								return;
							}
						}

						// Beginn - Versuchsreihe ohne Fortschrittsanzeige
						/*SignatureAttack *S_A = new SignatureAttack(&OFSA, SigAttTest, TotalAttemptsCounter);
						S_A->Do_Floyd();*/
						// Ende - Versuchsreihe ohne Fortschrittsanzeige

						// Beginn - Versuchsreihe mit Fortschrittsanzeige
						MessageID = RegisterWindowMessage("Floyd_Terminated");

						SignatureAttack *S_A = new SignatureAttackMFC(&OFSA, SigAttTest, TotalAttemptsCounter,
							this->m_hWnd, MessageID);
						CWThread = AfxBeginThread(SignatureAttackMFC::StaticThreadFunction, (void *)S_A);
						
						while (1)
						{
							if (PeekMessage(&FloydMessage, NULL, 0, 0, PM_NOREMOVE))
							{
								GetMessage(&FloydMessage, NULL, 0, 0);
								if (MessageID == FloydMessage.message)
								{
									break;	// nur wenn der Floyd-Algorithmus beendet wurde, Schleife verlassen - 
								}			// andere Messages werden ignoriert

								TranslateMessage(&FloydMessage); 
								DispatchMessage(&FloydMessage);
							}

							else WaitMessage();
						}
						// Ende - Versuchsreihe mit Fortschrittsanzeige

						if (_SIG_ATT_FLOYD_CANCELED == S_A->GetResults()->GetFloydResult())
						{
							delete S_A;				// Versuchsreihe vom Benutzer abgebrochen !
							fflush(SigAttTest);
							GenerateMessageText(_SIG_ATT_TEST_SERIES_STOPPED, MB_ICONINFORMATION);
							return;
						}

						delete S_A;
						fflush(SigAttTest);
					}
				}
			}
			fclose(SigAttTest);
			HIDE_HOUR_GLASS
		}

		else
		{
			CAppDocument *NewHarmlessDocument, *NewDangerousDocument;
			char *hashasci, hashhex [128], outfile[1024], doctitle[1024];
			CString crypT, msg;
			int Errorcode, ii, SignificantBitLength, strlen = 0;
			ofstream ModifiedHarmlessFile, ModifiedDangerousFile;

			crypT.Format(IDS_STRING_SIG_ATT_CRYPTOOL);

			OptionsForSignatureAttack OFSA(m_file_harmless, m_file_dangerous, u_SigAttTestMode);
			if (0 != OFSA.GetErrorcode())
			{
				GenerateMessageText(OFSA.GetErrorcode());
				return;
			}

			// Beginn - Angriff ohne Fortschrittsanzeige
			/*SignatureAttack *S_A = new SignatureAttack(&OFSA);
			SHOW_HOUR_GLASS
			S_A->Do_Floyd();
			HIDE_HOUR_GLASS*/
			// Ende - Angriff ohne Fortschrittsanzeige

			// Beginn - Angriff mit Fortschrittsanzeige
			CWinThread *CWThread;
			MSG FloydMessage;
			UINT MessageID;

			MessageID = RegisterWindowMessage("Floyd_Terminated");

			SignatureAttack *S_A = new SignatureAttackMFC(&OFSA, NULL, 0, this->m_hWnd, MessageID);
			CWThread = AfxBeginThread(SignatureAttackMFC::StaticThreadFunction, (void *)S_A);
			
			while (1)
			{
				if (PeekMessage(&FloydMessage, NULL, 0, 0, PM_NOREMOVE))
				{
					GetMessage(&FloydMessage, NULL, 0, 0);
					if (MessageID == FloydMessage.message)
					{
						break;	// nur wenn der Floyd-Algorithmus beendet wurde, Schleife verlassen - andere Messages werden
					}			// ignoriert

					TranslateMessage(&FloydMessage); 
					DispatchMessage(&FloydMessage);
				}

				else WaitMessage();
			}
			// Ende - Angriff mit Fortschrittsanzeige

			Errorcode = S_A->GetResults()->GetFloydResult();
			if (_SIG_ATT_DOCUMENTS_FOUND != Errorcode)
			{
				delete S_A;
				GenerateMessageText(Errorcode, MB_ICONINFORMATION);
				return;
			}

			GenerateMessageText(Errorcode, MB_ICONINFORMATION);
			SHOW_HOUR_GLASS

			GetTmpName(outfile,"cry",".tmp");
			ModifiedHarmlessFile.open(outfile, ios::out | ios::binary);
			if (!ModifiedHarmlessFile)
			{
				HIDE_HOUR_GLASS
				GenerateMessageText(IDS_STRING_FILE_NOT_OPEN);
				return;
			}
			ModifiedHarmlessFile.write(OFSA.GetHarmlessDocument()->GetDocumentData(),
				OFSA.GetHarmlessDocument()->GetDocumentLength());
			ModifiedHarmlessFile.close();
			NewHarmlessDocument = theApp.OpenDocumentFileNoMRU(outfile);

			// Dokumenttitel f�r Vorlage erstellen:
			msg.Format(IDS_STRING_SIG_ATT_DOCUMENT_TITLE_HARMLESS);

			hashasci = S_A->GetResults()->GetMatchingHashBytes();
			SignificantBitLength = OFSA.GetSignificantBitLength();
			for (ii = 0; ii < SignificantBitLength / 8; ii ++)
			{
				strlen += _snprintf(hashhex + strlen, 3, "%2.2X ", (unsigned char) hashasci[ii]);
			}

			if (0 != SignificantBitLength % 8)
			{
				strlen += _snprintf(hashhex + strlen, 4, "... ");
			}
					hashhex[strlen - 1] = '\0';

			_snprintf(doctitle, sizeof(doctitle) - 1, "%s%s, <%s>",
				msg, OFSA.GetHashOp()->GetHashAlgorithmName(), hashhex);
			NewHarmlessDocument->SetTitle(doctitle);

			GetTmpName(outfile,"cry",".tmp");
			ModifiedDangerousFile.open(outfile, ios::out | ios::binary);
			if (!ModifiedDangerousFile)
			{
				HIDE_HOUR_GLASS
				GenerateMessageText(IDS_STRING_FILE_NOT_OPEN);
				return;
			}
			ModifiedDangerousFile.write(OFSA.GetDangerousDocument()->GetDocumentData(),
				OFSA.GetDangerousDocument()->GetDocumentLength());
			ModifiedDangerousFile.close();
			NewDangerousDocument = theApp.OpenDocumentFileNoMRU(outfile);
			
			// Dokumenttitel f�r 2. Dokument erstellen:
			msg.Format(IDS_STRING_SIG_ATT_DOCUMENT_TITLE_DANGEROUS);
			_snprintf(doctitle, sizeof(doctitle) - 1, "%s%s, <%s>",
				msg, OFSA.GetHashOp()->GetHashAlgorithmName(), hashhex);
			NewDangerousDocument->SetTitle(doctitle);
			
			HIDE_HOUR_GLASS
			
			CDlgStatisticsSignatureAttack DlgSSA;
			DlgSSA.SetData(S_A->GetResults(),
				OFSA.GetHarmlessDocument()->GetModifiedBytes(), OFSA.GetDangerousDocument()->GetModifiedBytes());
			DlgSSA.DoModal();
			if (true == DlgSSA.GetPrintStatistics())
			{
				DlgSSA.PrintStatistics();
			}

			delete S_A;
		}

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

}

BOOL CDlgSignatureAttack::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS ) == ERROR_SUCCESS )
	{
		char tmpStr[1025] = "";
		unsigned long max_StrLength = 1024;
		CT_READ_REGISTRY_DEFAULT(tmpStr, "SignatureAttackHarmlessFile", tmpStr, max_StrLength);
		m_file_harmless = tmpStr;

		strcpy(tmpStr, "");
		max_StrLength = 1024;
		CT_READ_REGISTRY_DEFAULT(tmpStr, "SignatureAttackDangerousFile", tmpStr, max_StrLength);
		m_file_dangerous = tmpStr;

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}

void CDlgSignatureAttack::OnUpdateFileFake() 
{
	UpdateData(TRUE);
	AreValidPaths();
	UpdateData(FALSE);
}

void CDlgSignatureAttack::OnUpdateFileOriginal() 
{
	UpdateData(TRUE);
	AreValidPaths();
	UpdateData(FALSE);
}

bool CDlgSignatureAttack::AreValidPaths()
{
	if (TRUE == m_file_harmless.IsEmpty() || TRUE == m_file_dangerous.IsEmpty())
	{
		m_control_compute.EnableWindow(FALSE);
		return false;
	}

	m_control_compute.EnableWindow(TRUE);
	return true;
}

void CDlgSignatureAttack::BrowseDocument(CString & DocType)
{
	CString filename;

	CFileDialog FDlg(TRUE, NULL, filename, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		"All Files (*.*)|*.*|TXT Files (*.txt)|*.txt||", this);
	if (IDCANCEL == FDlg.DoModal())
	{
		return;
	}

	DocType = FDlg.GetPathName();
	
	if (m_file_harmless.IsEmpty())
	{
		m_control_compute.EnableWindow(FALSE);
		m_control_file_harmless.SetFocus();
	}
	else if (m_file_dangerous.IsEmpty())
	{
		m_control_compute.EnableWindow(FALSE);
		m_control_file_dangerous.SetFocus();
	}
	else
	{
		m_control_compute.EnableWindow(TRUE);
		m_control_compute.SetFocus();
	}
}

void CDlgSignatureAttack::GenerateMessageText(int Errorcode, UINT MessageBoxStyle)
{
	CString msg;

	switch (Errorcode)
	{
		case _SIG_ATT_BAD_HARMLESS_FILE:		msg.LoadString(IDS_STRING_SIG_ATT_BAD_HARMLESS_FILE); break;
		case _SIG_ATT_BAD_DANGEROUS_FILE:		msg.LoadString(IDS_STRING_SIG_ATT_BAD_DANGEROUS_FILE); break;
		case _SIG_ATT_BAD_HASH_ALGORITHM:		msg.LoadString(IDS_STRING_SIG_ATT_BAD_HASH_ALGORITHM); break;
		case _SIG_ATT_DOCUMENTS_FOUND:			
			{
				unsigned long u_bitLength = _OPT_SIG_ATT_STANDARD_BITLENGTH;
				if ( CT_OPEN_REGISTRY_SETTINGS( KEY_ALL_ACCESS ) == ERROR_SUCCESS )
				{
					CT_READ_REGISTRY_DEFAULT(u_bitLength, "SignatureAttackSignificantBitLength", u_bitLength);
					CT_CLOSE_REGISTRY();
				}
				msg.Format(IDS_STRING_SIG_ATT_DOCUMENTS_FOUND, u_bitLength); 
			}
			break;
		case _SIG_ATT_NO_DOCUMENTS_FOUND:		msg.LoadString(IDS_STRING_SIG_ATT_NO_DOCUMENTS_FOUND); break;
		case _SIG_ATT_BAD_MODIFIABILITY:		msg.LoadString(IDS_STRING_SIG_ATT_BAD_MODIFIABILITY); break;
		case _SIG_ATT_FLOYD_CANCELED:			msg.LoadString(IDS_STRING_SIG_ATT_FLOYD_CANCELED); break;
		case _SIG_ATT_TEST_SERIES_STOPPED:		msg.LoadString(IDS_STRING_SIG_ATT_STA_TEST_SERIES_STOPPED); break;

		default:								msg.LoadString(IDS_STRING_SIG_ATT_UNKNOWN_ERROR);
	}
	
	MessageBox(msg, "CrypTool", MessageBoxStyle | MB_APPLMODAL);
}

void CDlgSignatureAttack::OnCancel() 
{

	
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY(m_file_harmless, "SignatureAttackHarmlessFile");
		CT_WRITE_REGISTRY(m_file_dangerous, "SignatureAttackDangerousFile");

		CT_CLOSE_REGISTRY();
	}
	else
	{
		// FIXME
	}

	CDialog::OnCancel();
}

void CDlgSignatureAttack::OnBnClickedButtonUsedefaultmessages()
{
	/* The user wants to restore the default settings here. We CAN'T read the settings 
	from the registry here, because the user might already have changed the registry 
	entries. Instead, built the path manually here. */
	char fullPathOriginal[STR_LAENGE_STRING_TABLE+1];
	char fullPathFake[STR_LAENGE_STRING_TABLE+1];
	char pathOriginal[STR_LAENGE_STRING_TABLE+1];
	char pathFake[STR_LAENGE_STRING_TABLE+1];
	LoadString(AfxGetInstanceHandle(), IDS_SIGATT_HARMLESS, pathOriginal, STR_LAENGE_STRING_TABLE);
	LoadString(AfxGetInstanceHandle(), IDS_SIGATT_DANGEROUS, pathFake, STR_LAENGE_STRING_TABLE);
	sprintf(fullPathOriginal, "%s%s", Pfad, pathOriginal);
	sprintf(fullPathFake, "%s%s", Pfad, pathFake);
	m_file_harmless = fullPathOriginal;
	m_file_dangerous = fullPathFake;
	UpdateData(false);
}