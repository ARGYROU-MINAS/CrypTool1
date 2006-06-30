/*********************************************************************

Copyright (C) Deutsche Bank AG 1998-2003, Frankfurt am Main
Copyright (C) Universitšt Siegen und Darmstadt

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



// DlgADFGVX.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgADFGVX.h"
#include ".\dlgadfgvx.h"
#include "adfgvx.h"
#include "FileTools.h"
#include "CrypToolTools.h"
#include "KeyRepository.h"
#include "DialogeMessage.h"


// CDlgADFGVX-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgADFGVX, CDialog)
CDlgADFGVX::CDlgADFGVX(char* infile, CString oldTitle, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgADFGVX::IDD, pParent)
	, password(_T(""))
	, printStage1(FALSE)
	, blockSizeStage1(2)
	, blockSizeStage2(5)
	, numberedPassword(_T(""))
	, newLineStage2(FALSE)
	, newLineStage1(TRUE)
	, restart(false)
	,pwdInvalid(false)
	,pwdDouble(false)

{
	this->infile = infile;
	this->oldTitle = oldTitle;
	this->cipher = new adfgvx();
	for (int row=0;row<6;row++)
		for(int col=0;col<6;col++)
			this->matrix[row][col] = cipher->getMatrix(row,col);
}

CDlgADFGVX::~CDlgADFGVX()
{
}

void CDlgADFGVX::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXTFIELD_PASSWORD, password);
	//DDV_MaxChars(pDX, password, 26);
	DDX_Text(pDX, IDC_M00, matrix[0][0]);
	DDV_MaxChars(pDX, matrix[0][0], 1);
	DDX_Text(pDX, IDC_M01, matrix[0][1]);
	DDV_MaxChars(pDX, matrix[0][1], 1);
	DDX_Text(pDX, IDC_M02, matrix[0][2]);
	DDV_MaxChars(pDX, matrix[0][2], 1);
	DDX_Text(pDX, IDC_M03, matrix[0][3]);
	DDV_MaxChars(pDX, matrix[0][3], 1);
	DDX_Text(pDX, IDC_M04, matrix[0][4]);
	DDV_MaxChars(pDX, matrix[0][4], 1);
	DDX_Text(pDX, IDC_M05, matrix[0][5]);
	DDV_MaxChars(pDX, matrix[0][5], 1);
	DDX_Text(pDX, IDC_M10, matrix[1][0]);
	DDV_MaxChars(pDX, matrix[1][0], 1);
	DDX_Text(pDX, IDC_M11, matrix[1][1]);
	DDV_MaxChars(pDX, matrix[1][1], 1);
	DDX_Text(pDX, IDC_M12, matrix[1][2]);
	DDV_MaxChars(pDX, matrix[1][2], 1);
	DDX_Text(pDX, IDC_M13, matrix[1][3]);
	DDV_MaxChars(pDX, matrix[1][3], 1);
	DDX_Text(pDX, IDC_M14, matrix[1][4]);
	DDV_MaxChars(pDX, matrix[1][4], 1);
	DDX_Text(pDX, IDC_M15, matrix[1][5]);
	DDV_MaxChars(pDX, matrix[1][5], 1);
	DDX_Text(pDX, IDC_M20, matrix[2][0]);
	DDV_MaxChars(pDX, matrix[2][0], 1);
	DDX_Text(pDX, IDC_M21, matrix[2][1]);
	DDV_MaxChars(pDX, matrix[2][1], 1);
	DDX_Text(pDX, IDC_M22, matrix[2][2]);
	DDV_MaxChars(pDX, matrix[2][2], 1);
	DDX_Text(pDX, IDC_M23, matrix[2][3]);
	DDV_MaxChars(pDX, matrix[2][3], 1);
	DDX_Text(pDX, IDC_M24, matrix[2][4]);
	DDV_MaxChars(pDX, matrix[2][4], 1);
	DDX_Text(pDX, IDC_M25, matrix[2][5]);
	DDV_MaxChars(pDX, matrix[2][5], 1);
	DDX_Text(pDX, IDC_M30, matrix[3][0]);
	DDV_MaxChars(pDX, matrix[3][0], 1);
	DDX_Text(pDX, IDC_M31, matrix[3][1]);
	DDV_MaxChars(pDX, matrix[3][1], 1);
	DDX_Text(pDX, IDC_M32, matrix[3][2]);
	DDV_MaxChars(pDX, matrix[3][2], 1);
	DDX_Text(pDX, IDC_M33, matrix[3][3]);
	DDV_MaxChars(pDX, matrix[3][3], 1);
	DDX_Text(pDX, IDC_M34, matrix[3][4]);
	DDV_MaxChars(pDX, matrix[3][4], 1);
	DDX_Text(pDX, IDC_M35, matrix[3][5]);
	DDV_MaxChars(pDX, matrix[3][5], 1);
	DDX_Text(pDX, IDC_M40, matrix[4][0]);
	DDV_MaxChars(pDX, matrix[4][0], 1);
	DDX_Text(pDX, IDC_M41, matrix[4][1]);
	DDV_MaxChars(pDX, matrix[4][1], 1);
	DDX_Text(pDX, IDC_M42, matrix[4][2]);
	DDV_MaxChars(pDX, matrix[4][2], 1);
	DDX_Text(pDX, IDC_M43, matrix[4][3]);
	DDV_MaxChars(pDX, matrix[4][3], 1);
	DDX_Text(pDX, IDC_M44, matrix[4][4]);
	DDV_MaxChars(pDX, matrix[4][4], 1);
	DDX_Text(pDX, IDC_M45, matrix[4][5]);
	DDV_MaxChars(pDX, matrix[4][5], 1);
	DDX_Text(pDX, IDC_M50, matrix[5][0]);
	DDV_MaxChars(pDX, matrix[5][0], 1);
	DDX_Text(pDX, IDC_M51, matrix[5][1]);
	DDV_MaxChars(pDX, matrix[5][1], 1);
	DDX_Text(pDX, IDC_M52, matrix[5][2]);
	DDV_MaxChars(pDX, matrix[5][2], 1);
	DDX_Text(pDX, IDC_M53, matrix[5][3]);
	DDV_MaxChars(pDX, matrix[5][3], 1);
	DDX_Text(pDX, IDC_M54, matrix[5][4]);
	DDV_MaxChars(pDX, matrix[5][4], 1);
	DDX_Text(pDX, IDC_M55, matrix[5][5]);
	DDV_MaxChars(pDX, matrix[5][5], 1);
	// DDX_Control(pDX, IDC_BUTTON_INSERT_KEY, buttonInsertKey);
	DDX_Check(pDX, IDC_CHECK_OUTPUT, printStage1);
	DDX_Text(pDX, IDC_EDIT_BLOCKSIZE_STAGE2, blockSizeStage2);
	//DDV_MinMaxInt(pDX, blockSizeStage2, 0, 26);
	DDX_Text(pDX, IDC_EDIT_BLOCKSIZE_STAGE1, blockSizeStage1);
	//DDV_MinMaxInt(pDX, blockSizeStage1, 0, 26);
	DDX_Text(pDX, IDC_TEXTFIELD_NUMBERS, numberedPassword);

	DDX_Check(pDX, IDC_CHECK_NEWLINE_STAGE2, newLineStage2);
	DDX_Check(pDX, IDC_CHECK_NEWLINE_STAGE1, newLineStage1);
	DDX_Check(pDX, IDC_CHECK_BLOCK_STAGE2, boxBlockOutput2);
	DDX_Check(pDX, IDC_CHECK_BLOCK_STAGE1, boxBlockOutput1);
	DDX_Check(pDX, IDC_CHECK_OUTPUT, boxOutput1);
	DDX_Control(pDX, IDC_EDIT_BLOCKSIZE_STAGE2, editBlockLength2);
	DDX_Control(pDX, IDC_EDIT_BLOCKSIZE_STAGE1, editBlockLength1);
	DDX_Check(pDX, IDC_CHECK_NEWLINE_STAGE2, boxNewLine2);
	DDX_Check(pDX, IDC_CHECK_NEWLINE_STAGE1, boxNewLine1);
}

BEGIN_MESSAGE_MAP(CDlgADFGVX, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ENCRYPT, OnBnClickedButtonEncrypt)
	ON_BN_CLICKED(IDC_BUTTON_DECRYPT, OnBnClickedButtonDecrypt)
	ON_BN_CLICKED(IDC_BUTTON_INSERT_KEY, OnBnClickedButtonInsertKey)
	ON_BN_CLICKED(IDC_MATRIX_SHUFFLE, OnBnClickedMatrixShuffle)
	ON_BN_CLICKED(IDC_MATRIX_STANDARD, OnBnClickedMatrixStandard)
	ON_BN_CLICKED(IDC_CANCEL, OnBnClickedCancel)
	ON_EN_CHANGE(IDC_M00, OnEnChangeM00)
	ON_EN_CHANGE(IDC_M01, OnEnChangeM01)
	ON_EN_CHANGE(IDC_M02, OnEnChangeM02)
	ON_EN_CHANGE(IDC_M03, OnEnChangeM03)
	ON_EN_CHANGE(IDC_M04, OnEnChangeM04)
	ON_EN_CHANGE(IDC_M05, OnEnChangeM05)
	ON_EN_CHANGE(IDC_M10, OnEnChangeM10)
	ON_EN_CHANGE(IDC_M11, OnEnChangeM11)
	ON_EN_CHANGE(IDC_M12, OnEnChangeM12)
	ON_EN_CHANGE(IDC_M13, OnEnChangeM13)
	ON_EN_CHANGE(IDC_M14, OnEnChangeM14)
	ON_EN_CHANGE(IDC_M15, OnEnChangeM15)
	ON_EN_CHANGE(IDC_M20, OnEnChangeM20)
	ON_EN_CHANGE(IDC_M21, OnEnChangeM21)
	ON_EN_CHANGE(IDC_M22, OnEnChangeM22)
	ON_EN_CHANGE(IDC_M23, OnEnChangeM23)
	ON_EN_CHANGE(IDC_M24, OnEnChangeM24)
	ON_EN_CHANGE(IDC_M25, OnEnChangeM25)
	ON_EN_CHANGE(IDC_M30, OnEnChangeM30)
	ON_EN_CHANGE(IDC_M31, OnEnChangeM31)
	ON_EN_CHANGE(IDC_M32, OnEnChangeM32)
	ON_EN_CHANGE(IDC_M33, OnEnChangeM33)
	ON_EN_CHANGE(IDC_M34, OnEnChangeM34)
	ON_EN_CHANGE(IDC_M35, OnEnChangeM35)
	ON_EN_CHANGE(IDC_M40, OnEnChangeM40)
	ON_EN_CHANGE(IDC_M41, OnEnChangeM41)
	ON_EN_CHANGE(IDC_M42, OnEnChangeM42)
	ON_EN_CHANGE(IDC_M43, OnEnChangeM43)
	ON_EN_CHANGE(IDC_M44, OnEnChangeM44)
	ON_EN_CHANGE(IDC_M45, OnEnChangeM45)
	ON_EN_CHANGE(IDC_M50, OnEnChangeM50)
	ON_EN_CHANGE(IDC_M51, OnEnChangeM51)
	ON_EN_CHANGE(IDC_M52, OnEnChangeM52)
	ON_EN_CHANGE(IDC_M53, OnEnChangeM53)
	ON_EN_CHANGE(IDC_M54, OnEnChangeM54)
	ON_EN_CHANGE(IDC_M55, OnEnChangeM55)
	ON_EN_CHANGE(IDC_TEXTFIELD_PASSWORD, OnEnChangeTextfieldPassword)
	ON_BN_CLICKED(IDC_CHECK_OUTPUT, OnBnClickedCheckOutputStage1)
	ON_BN_CLICKED(IDC_ERASEMATRIX, OnBnClickedErasematrix)
	ON_BN_CLICKED(IDC_CHECK_BLOCK_STAGE2, OnBnClickedCheckBlockStage2)
	ON_BN_CLICKED(IDC_CHECK_BLOCK_STAGE1, OnBnClickedCheckBlockStage1)
END_MESSAGE_MAP()

BOOL CDlgADFGVX::OnInitDialog() 
{
	CDialog::OnInitDialog();
	VERIFY(buttonInsertKey.AutoLoad(IDC_BUTTON_INSERT_KEY,this));

	this->GetDlgItem(IDC_BUTTON_ENCRYPT)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_DECRYPT)->EnableWindow(false);

	//check if the txt is in ADFGVX-format
	this->validCiphertext=this->cipher->readCiphertext(infile);

	//if clipboard has key from adfgvx-typ, enable paste button
	
	if (IsKeyEmpty("ADFGVX Chiffre"))
		this->buttonInsertKey.EnableWindow(TRUE);
	else
		this->buttonInsertKey.EnableWindow(FALSE);

	return true;
}
// CDlgADFGVX-Meldungshandler

void CDlgADFGVX::OnBnClickedButtonEncrypt()
{	
	UpdateData(true);
	bool validBlocksizes=true;
	//wrong blocksizes: errormessage
	if ((blockSizeStage2<1)|(blockSizeStage2>26))
	{
		blockSizeStage2=5;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_BLOCKLENGTH_STAGE2,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		validBlocksizes=false;
		UpdateData(false);	
	}
	if ((blockSizeStage1<1)|(blockSizeStage1>26))
	{
		blockSizeStage1=password.GetLength();
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_BLOCKLENGTH_STAGE1,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		validBlocksizes=false;
		UpdateData(false);	
	}
	if(validBlocksizes)
	{
		//validate the transposition-password
		int validPassword=cipher->CheckPassword(1, 1, password);
		
		//passwordLength<1
		if (validPassword==6)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_6,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
		}

		//invalid characters are removed; recheck
		if (validPassword==4)
		{
			CString oldPassword=password;
			password=cipher->CleansePassword(validPassword, password);
			UpdateData(false);
			//LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_4,pc_str,STR_LAENGE_STRING_TABLE);
			//CString message=(CString)pc_str+(CString)(password);
			//MessageBox(message);
			pwdInvalid=true;
			restart=true;
			OnEnChangeTextfieldPassword();

			OnBnClickedButtonEncrypt();
		}	

		//redundant characters: redundant characters are removed, minLength/maxLength is adjusted
		if (validPassword==7)
		{
			CString oldPassword=password;
			password=cipher->CleansePassword(validPassword, password);
			UpdateData(false);
			//LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_7,pc_str,STR_LAENGE_STRING_TABLE);
			//CString message=(CString)pc_str+(CString)(password);
			//MessageBox(message);
			pwdDouble=true;
			restart=true;
			OnEnChangeTextfieldPassword();

			OnBnClickedButtonEncrypt();
		}

		if (validPassword==0)
		{
			if(restart)
			{
				CString message="";
				if(pwdInvalid)
				{
					LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_4,pc_str,STR_LAENGE_STRING_TABLE);
					message += CString(pc_str); // message.Append(pc_str);
				}
				if(pwdDouble)
				{
					if(pwdInvalid)
						message += CString("\n"); // message.Append("\n");
					LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_7,pc_str,STR_LAENGE_STRING_TABLE);
					message += CString(pc_str); // message.Append(pc_str);
				}
				LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_NEWPWD, pc_str, STR_LAENGE_STRING_TABLE);
				message += CString(pc_str); // message.Append(pc_str);
				message += CString(password); // message.Append(password);
				if(boxBlockOutput1|boxBlockOutput2)
					LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_RESTART_LENGTH, pc_str, STR_LAENGE_STRING_TABLE);
				else
					LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_RESTART, pc_str, STR_LAENGE_STRING_TABLE);
				message += CString(pc_str); // message.Append(pc_str);
				MessageBox(message);
				restart=false;
				pwdInvalid=false;
				pwdDouble=false;
			}
			else
                Encrypt();
		}
	}
}

void CDlgADFGVX::OnBnClickedButtonDecrypt()
{
	UpdateData(true);
	
	bool validBlocksizes=true;
	//wrong blocksize: error message
	if ((blockSizeStage2<0)|(blockSizeStage2>26))
	{
		blockSizeStage2=5;
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_BLOCKLENGTH_STAGE2,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		validBlocksizes=false;
		UpdateData(false);	
	}
	if ((blockSizeStage1<0)|(blockSizeStage1>26))
	{
		blockSizeStage1=password.GetLength();
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_BLOCKLENGTH_STAGE1,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		validBlocksizes=false;
		UpdateData(false);	
	}
	if(validBlocksizes)
	{
		//validate the transposition-password
		int validPassword=cipher->CheckPassword(1, 1, password);
		
		//passwordLength<1
		if (validPassword==6)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_6,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
		}

		//invalid characters are removed; recheck
		if (validPassword==4)
		{
			CString oldPassword=password;
			password=cipher->CleansePassword(validPassword, password);
			UpdateData(false);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_4,pc_str,STR_LAENGE_STRING_TABLE);
			CString message=(CString)pc_str+(CString)(password);
			MessageBox(message);
			restart=true;
			OnEnChangeTextfieldPassword();

			OnBnClickedButtonDecrypt();
		}	

		//redundant characters: redundant characters are removed, minLength/maxLength is adjusted
		if (validPassword==7)
		{
			CString oldPassword=password;
			password=cipher->CleansePassword(validPassword, password);
			UpdateData(false);
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_7,pc_str,STR_LAENGE_STRING_TABLE);
			CString message=(CString)pc_str+(CString)(password);
			MessageBox(message);
			restart=true;
			OnEnChangeTextfieldPassword();

			OnBnClickedButtonDecrypt();
		}

		if (validPassword==0)
		{
			if(restart)
			{
				LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_RESTART, pc_str, STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
				restart=false;
				
			}
			else
                Decrypt();
		}
	}
}

void CDlgADFGVX::OnBnClickedButtonInsertKey()
{
	CString key; 
	PasteKey("ADFGVX",key);
	//position of ',' first part represent passwort, 
	//second one the serialized matrix
	int split = key.Find(',');
	//set password variable for dialog
	password = key.Left(split);
	//set matrix variables for dialog
	for (int row=0;row<6;row++)
		for(int col=0;col<6;col++)
			this->matrix[row][col] = key[split+2+row*6+col];
	//synchronize data : set textfields to values of variables
	UpdateData(FALSE);
		
	//check whether en- or decryption is possible
	CheckProgress();
	UpdateData(true);
	numberedPassword=cipher->LettersToNumbers(this->password);
	UpdateData(false);
}
void CDlgADFGVX::OnBnClickedMatrixShuffle()
{
	//synchronize data with textfields
	UpdateData(true);
	
	char zv[6][6]={'A','B','C','D','E','F',
					'G','H','I','J','K','L',
					'M','N','O','P','Q','R',
					'S','T','U','V','W','X',
					'Y','Z','0','1','2','3',
					'4','5','6','7','8','9'};

	vector <char> rand;

	//fill the vector
	for (int col=0; col<6;col++)
		for(int row=0;row<6;row++)
			rand.push_back(zv[col][row]);

	// shuffle-function in <algorithm> for <vector>
	random_shuffle(rand.begin(),rand.end());

	//copy back to codeMatrix
	int i=0;
	for(int row=0;row<6;row++)
		for (int col=0;col<6;col++)
			this->matrix[row][col]=rand.at(i++);

	//synchronize data with textfields
	UpdateData(false);

	//check whether en- or decryption is possible
	CheckProgress();
}

void CDlgADFGVX::OnBnClickedMatrixStandard()
{
	//synchronize data with textfields
	UpdateData(true);
	
	char zv[6][6]={'A','B','C','D','E','F',
					'G','H','I','J','K','L',
					'M','N','O','P','Q','R',
					'S','T','U','V','W','X',
					'Y','Z','0','1','2','3',
					'4','5','6','7','8','9'};

	//copy back to codeMatrix
	for(int row=0;row<6;row++)
		for (int col=0;col<6;col++)
			this->matrix[row][col]=zv[row][col];

	//synchronize data with textfields
	UpdateData(false);

	//check whether en- or decryption is possible
	CheckProgress();
}

void CDlgADFGVX::OnBnClickedCheckOutputStage1()
{
	UpdateData(true);
	if(boxOutput1==true)
	{
		GetDlgItem(IDC_CHECK_BLOCK_STAGE1)->EnableWindow(true);
		printStage1=true;
	}

	else
	{
		boxBlockOutput1=false;
		GetDlgItem(IDC_CHECK_BLOCK_STAGE1)->EnableWindow(false);
		UpdateData(false);
		OnBnClickedCheckBlockStage1();
	}
}
void CDlgADFGVX::OnBnClickedCancel()
{
	CDialog::OnCancel();
}


void CDlgADFGVX::OnOK()
{
	if(GetFocus()==GetDlgItem(IDC_BUTTON_ENCRYPT))
		CDlgADFGVX::OnBnClickedButtonEncrypt();

	if(GetFocus()==GetDlgItem(IDC_BUTTON_DECRYPT))
		CDlgADFGVX::OnBnClickedButtonDecrypt();

	else
		CDialog::NextDlgCtrl();
}

// the following 36 functions call CheckInput to check all edit-control-fields as well as CheckProgress
void CDlgADFGVX::OnEnChangeM00()
{	
	oldEntry=matrix[0][0];
	UpdateData(TRUE);	
	matrix[0][0]=CheckInput(oldEntry, matrix[0][0]);
	//UpdateRemChars(); 
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM01()
{
	oldEntry=matrix[0][1];
	UpdateData(TRUE);	
	matrix[0][1]=CheckInput(oldEntry, matrix[0][1]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM02()
{
	oldEntry=matrix[0][2];
	UpdateData(TRUE);	
	matrix[0][2]=CheckInput(oldEntry, matrix[0][2]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM03()
{
	oldEntry=matrix[0][3];
	UpdateData(TRUE);	
	matrix[0][3]=CheckInput(oldEntry, matrix[0][3]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM04()
{
	oldEntry=matrix[0][4];
	UpdateData(TRUE);	
	matrix[0][4]=CheckInput(oldEntry, matrix[0][4]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM05()
{
	oldEntry=matrix[0][5];
	UpdateData(TRUE);	
	matrix[0][5]=CheckInput(oldEntry, matrix[0][5]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM10()
{
	oldEntry=matrix[1][0];
	UpdateData(TRUE);	
	matrix[1][0]=CheckInput(oldEntry, matrix[1][0]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM11()
{
	oldEntry=matrix[1][1];
	UpdateData(TRUE);	
	matrix[1][1]=CheckInput(oldEntry, matrix[1][1]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM12()
{
	oldEntry=matrix[1][2];
	UpdateData(TRUE);	
	matrix[1][2]=CheckInput(oldEntry, matrix[1][2]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM13()
{
	oldEntry=matrix[1][3];
	UpdateData(TRUE);	
	matrix[1][3]=CheckInput(oldEntry, matrix[1][3]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM14()
{
	oldEntry=matrix[1][4];
	UpdateData(TRUE);	
	matrix[1][4]=CheckInput(oldEntry, matrix[1][4]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM15()
{
	oldEntry=matrix[1][5];
	UpdateData(TRUE);	
	matrix[1][5]=CheckInput(oldEntry, matrix[1][5]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM20()
{
	oldEntry=matrix[2][0];
	UpdateData(TRUE);	
	matrix[2][0]=CheckInput(oldEntry, matrix[2][0]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM21()
{
	oldEntry=matrix[2][1];
	UpdateData(TRUE);	
	matrix[2][1]=CheckInput(oldEntry, matrix[2][1]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM22()
{
	oldEntry=matrix[2][2];
	UpdateData(TRUE);	
	matrix[2][2]=CheckInput(oldEntry, matrix[2][2]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM23()
{
	oldEntry=matrix[2][3];
	UpdateData(TRUE);	
	matrix[2][3]=CheckInput(oldEntry, matrix[2][3]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM24()
{
	oldEntry=matrix[2][4];
	UpdateData(TRUE);	
	matrix[2][4]=CheckInput(oldEntry, matrix[2][4]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM25()
{
	oldEntry=matrix[2][5];
	UpdateData(TRUE);	
	matrix[2][5]=CheckInput(oldEntry, matrix[2][5]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM30()
{
	oldEntry=matrix[3][0];
	UpdateData(TRUE);	
	matrix[3][0]=CheckInput(oldEntry, matrix[3][0]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM31()
{
	oldEntry=matrix[3][1];
	UpdateData(TRUE);	
	matrix[3][1]=CheckInput(oldEntry, matrix[3][1]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM32()
{
	oldEntry=matrix[3][2];
	UpdateData(TRUE);	
	matrix[3][2]=CheckInput(oldEntry, matrix[3][2]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM33()
{
	oldEntry=matrix[3][3];
	UpdateData(TRUE);	
	matrix[3][3]=CheckInput(oldEntry, matrix[3][3]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM34()
{
	oldEntry=matrix[3][4];
	UpdateData(TRUE);	
	matrix[3][4]=CheckInput(oldEntry, matrix[3][4]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM35()
{
	oldEntry=matrix[3][5];
	UpdateData(TRUE);	
	matrix[3][5]=CheckInput(oldEntry, matrix[3][5]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM40()
{
	oldEntry=matrix[4][0];
	UpdateData(TRUE);	
	matrix[4][0]=CheckInput(oldEntry, matrix[4][0]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM41()
{
	oldEntry=matrix[4][1];
	UpdateData(TRUE);	
	matrix[4][1]=CheckInput(oldEntry, matrix[4][1]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM42()
{
	oldEntry=matrix[4][2];
	UpdateData(TRUE);	
	matrix[4][2]=CheckInput(oldEntry, matrix[4][2]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM43()
{
	oldEntry=matrix[4][3];
	UpdateData(TRUE);	
	matrix[4][3]=CheckInput(oldEntry, matrix[4][3]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM44()
{
	oldEntry=matrix[4][4];
	UpdateData(TRUE);	
	matrix[4][4]=CheckInput(oldEntry, matrix[4][4]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM45()
{
	oldEntry=matrix[4][5];
	UpdateData(TRUE);	
	matrix[4][5]=CheckInput(oldEntry, matrix[4][5]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM50()
{
	oldEntry=matrix[5][0];
	UpdateData(TRUE);	
	matrix[5][0]=CheckInput(oldEntry, matrix[5][0]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM51()
{
	oldEntry=matrix[5][1];
	UpdateData(TRUE);	
	matrix[5][1]=CheckInput(oldEntry, matrix[5][1]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM52()
{
	oldEntry=matrix[5][2];
	UpdateData(TRUE);	
	matrix[5][2]=CheckInput(oldEntry, matrix[5][2]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM53()
{
	oldEntry=matrix[5][3];
	UpdateData(TRUE);	
	matrix[5][3]=CheckInput(oldEntry, matrix[5][3]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM54()
{
	oldEntry=matrix[5][4];
	UpdateData(TRUE);	
	matrix[5][4]=CheckInput(oldEntry, matrix[5][4]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::OnEnChangeM55()
{
	oldEntry=matrix[5][5];
	UpdateData(TRUE);	
	matrix[5][5]=CheckInput(oldEntry, matrix[5][5]);
	//UpdateRemChars();
	UpdateData(FALSE);
	CheckProgress();
	//Resubstitute();
	CDialog::NextDlgCtrl();
}

void CDlgADFGVX::Decrypt()
{
	SHOW_HOUR_GLASS
		char outfile[256];
		char stage1[256];
		char* temp;
		//saves the password and serialized matrix 
		CString pwdString;
		pwdString += password;
		pwdString += ", ";
		//get filename of temporary file
		GetTmpName(outfile,"cry",".txt");
		GetTmpName(stage1,"cry",".txt");
		for (int row=0;row<6;row++)
			for(int col=0;col<6;col++)
			{
				//cipher->setMatrix(row,col,matrix[row][col][0]);
				pwdString += matrix[row][col][0];
			}
		
		/*notification about not separating the plaintext is not necessary
		if (blockSizeStage2>0)
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_BLOCK_NOTIFY,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
		}
		*/
		
		//if the block.output-box for the stage ist unchecked, set the block length to zero
		if(boxBlockOutput2==false)
			blockSizeStage2=0;
		if(boxBlockOutput1==false)
			blockSizeStage1=0;

		int rtn = cipher->decrypt(this->infile, outfile, password, blockSizeStage2, newLineStage2, blockSizeStage1, newLineStage1, stage1);
		//if no error occured
		if (rtn == 0)
		{
			OpenNewDoc(outfile,pwdString,this->oldTitle,IDS_CRYPT_ADFGVX,true,1);
			if(printStage1&&blockSizeStage1>0)
				OpenNewDoc(stage1,pwdString,this->oldTitle,IDS_CRYPT_ADFGVX_STAGE_1,false,1);
			this->EndDialog(1);
		}
		
		//if password is missing because all characters were invalid
		else if (rtn == 1) 
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_1,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
			this->GetDlgItem(IDC_BUTTON_ENCRYPT)->EnableWindow(false);
			this->GetDlgItem(IDC_BUTTON_DECRYPT)->EnableWindow(false);

		}
		/*now in CheckProgress()
		//if matrix has double entries
		else if (rtn == 2){
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_2,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
		}
		//if matrix has invalid characters
		else if (rtn == 3){
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_3,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
		}
		//if ciphertext contains invalid characters
		else if (rtn == 4){
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_10,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
		}
		//if ciphertext has odd number of characters
		else if (rtn == 5){
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_5,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
		} 
		*/
		//if anything else happens
		else
			MessageBox("Unbekannter Fehler");
		HIDE_HOUR_GLASS
}

void CDlgADFGVX::Encrypt()
{
	SHOW_HOUR_GLASS
		char outfile[256];
		char stage1[256];
		char* temp;
		//saves the password and serialized matrix 
		CString pwdString;
		pwdString += password;
		pwdString += ", ";
		//get filename of temporary file
		GetTmpName(outfile,"cry",".txt");
		GetTmpName(stage1,"cry",".txt");
		//set matrix character by character
		for (int row=0;row<6;row++)
			for(int col=0;col<6;col++) 
			{
				//cipher->setMatrix(row,col,matrix[row][col][0]);
				pwdString += matrix[row][col][0];
			}

		//if the block.output-box for the stage ist unchecked, set the block length to zero
		if(boxBlockOutput2==false)
			blockSizeStage2=0;
		if(boxBlockOutput1==false)
			blockSizeStage1=0;

		//execute encryption function 
		int rtn = cipher->encrypt(this->infile, outfile, password, blockSizeStage2, newLineStage2, blockSizeStage1, newLineStage1, stage1);
		//handle error or show result

		//encrypt and exit dialog
		if (rtn == 0)
		{
			if(printStage1&&blockSizeStage1>0)	
				OpenNewDoc(stage1,pwdString,this->oldTitle,IDS_CRYPT_ADFGVX_STAGE_1,false,1);

			OpenNewDoc(outfile,pwdString,this->oldTitle,IDS_CRYPT_ADFGVX,false,1);
			
			this->EndDialog(1);
		}
		
		
		//if password is missing because all characters were invalid
		else if (rtn == 1) 
		{
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_1,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
			this->GetDlgItem(IDC_BUTTON_ENCRYPT)->EnableWindow(false);
			this->GetDlgItem(IDC_BUTTON_DECRYPT)->EnableWindow(false);

		}
		/* now done while entering the password: CheckProgress()
		//if matrix has double entries
		else if (rtn == 2){
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_2,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
		}
		//if matrix has unvalid characters
		else if (rtn == 3){
			LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_3,pc_str,STR_LAENGE_STRING_TABLE);
			MessageBox(pc_str);
		}*/
		//if anything else happens
		else
			MessageBox("Unbekannter Fehler");
		HIDE_HOUR_GLASS
}

void CDlgADFGVX::OnEnChangeTextfieldPassword()
{
	//check whether en- or decryption is possible
	CheckProgress();
	UpdateData(true);
	numberedPassword=cipher->LettersToNumbers(this->password);
	UpdateData(false);
}



//function to check if the input is a valid character & if there are double characters in the matrix
CString CDlgADFGVX::CheckInput(CString oldEntry, CString input)
{
	int counter=0;
	if ( input==' ' || input=='*' || input.GetLength()==0 )
		return "*";
	if (('A'<=input&&input<='z') || ('0'<=input&&input<='9'))
	{
		//checks, if the matrix contains the input more than once, 
		//the "unnecessary" brackets: 
		//i found the for-loop enter line "if(counter>1)" every time. don't know why...
		for (int col=0;col<6;col++)
		{
			for(int row=0;row<6;row++)
			{
				if(matrix[row][col]==input)	
					counter++;
			}
		}

		//if that is the case, the user can choose what to do		
		if(counter>1)
		{
			//option dialog: keep new & delete old or cancel entry?
			if('0'<=input&&input<='9')
				LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_CHAR_EXISTS_1B, pc_str, STR_LAENGE_STRING_TABLE);
			else
				LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_CHAR_EXISTS_1A, pc_str, STR_LAENGE_STRING_TABLE);
			CString message=(CString)pc_str+(CString)(input);
			LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_CHAR_EXISTS_2, pc_str, STR_LAENGE_STRING_TABLE);
			message+=pc_str;
			if (AfxMessageBox (message,MB_YESNO)==IDYES)
			{
				//brackets: see above
				for (int col=0;col<6;col++)
				{
					for(int row=0;row<6;row++)
					{
						if(matrix[row][col]==input)
							matrix[row][col]="*";
					}
				}
			}
			else
				return oldEntry;
		}
								

		return input;
	}
	//invalid character: error message is displayed and the filed is reset
	else
	{
		
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_11,pc_str,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str);
		return oldEntry;
	}
}

//function to check if de- or encryption is possible with the current parameters
//if that is the case, the respective buttons are activated
void CDlgADFGVX::CheckProgress()
{
	bool validMatrix, validPassword, validAdfgvx;
	validMatrix=validPassword=validAdfgvx=false;

	this->GetDlgItem(IDC_BUTTON_ENCRYPT)->EnableWindow(false);
	this->GetDlgItem(IDC_BUTTON_DECRYPT)->EnableWindow(false);

	UpdateData(true);
	//the password is only checked in length for it is annyoing if the password is corrected while typing.
	//so: passwordcorrection only when leaving the dialog
	if (this->password.GetLength()>0)
		validPassword=true;

	//it's unnecessary to check all parameters, if the one fails, the others can be postponed
	//the quickest certainly is the password-check
	if(validPassword)
	{
		//check if the matrix is filled correctly
		//set matrix character by character
		for (int row=0;row<6;row++)
			for(int col=0;col<6;col++) 
			{
				cipher->setMatrix(row,col,matrix[row][col][0]);
				pwdString += matrix[row][col][0];
			}
			int rtn=this->cipher->checkMatrix();
			
			//this cannot possibly happen at this stage, since this is checked before, i didn't remove it though, 
			//perhaps it is needed in a future revision of the code

			//if matrix has double entries
			/*if (rtn == 2)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_2,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			}
			//if matrix has invalid characters
			//i found this message annoying, so i leave it out
			else if (rtn == 3)
			{
				LoadString(AfxGetInstanceHandle(),IDS_STRING_ADFGVX_ERROR_3,pc_str,STR_LAENGE_STRING_TABLE);
				MessageBox(pc_str);
			}*/

			//if we arrive here, the matrix is valid
			if (rtn == 0)
				validMatrix=true;

			//whether the text is already ADFGVX and therefore can be decrypted ist determined at OnInitDialog
			if (this->validCiphertext == 0)
			validAdfgvx=true;
	}

		

		//all tests completed: the results
		if (validMatrix && validPassword)
		{
			this->GetDlgItem(IDC_BUTTON_ENCRYPT)->EnableWindow(true);
			if(validAdfgvx)
				this->GetDlgItem(IDC_BUTTON_DECRYPT)->EnableWindow(true);
		}
}



void CDlgADFGVX::OnBnClickedErasematrix()
{
	LoadString (AfxGetInstanceHandle(), IDS_STRING_ADFGVX_MATRIX_RESET, pc_str, STR_LAENGE_STRING_TABLE);

	if (AfxMessageBox (pc_str,MB_YESNO)==IDYES)
	{
		for (int col=0;col<6;col++)
			for(int row=0;row<6;row++)
				this->matrix[row][col]='*';
		UpdateData(false);
		
	}
}

void CDlgADFGVX::OnBnClickedCheckBlockStage2()
{
	UpdateData(true);
	if(boxBlockOutput2==true)
	{
		editBlockLength2.EnableWindow(true);
		GetDlgItem(IDC_CHECK_NEWLINE_STAGE2)->EnableWindow(true);
	}
	else
	{
		editBlockLength2.EnableWindow(false);
		boxNewLine2=false;
		GetDlgItem(IDC_CHECK_NEWLINE_STAGE2)->EnableWindow(false);
		blockSizeStage2=5;	
	}
	UpdateData(false);
}

void CDlgADFGVX::OnBnClickedCheckBlockStage1()
{
	UpdateData(true);
	if(boxBlockOutput1==true)
	{
		editBlockLength1.EnableWindow(true);
		GetDlgItem(IDC_CHECK_NEWLINE_STAGE1)->EnableWindow(true);
		blockSizeStage1=password.GetLength();
	}
	else
	{
		editBlockLength1.EnableWindow(false);
		GetDlgItem(IDC_CHECK_NEWLINE_STAGE1)->EnableWindow(false);
		blockSizeStage1=2;
		boxNewLine1=false;
	}
	UpdateData(false);
}
