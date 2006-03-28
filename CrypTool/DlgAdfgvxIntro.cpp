// DlgAdfgvxIntro.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DlgAdfgvxIntro.h"
#include ".\dlgadfgvxintro.h"


// DlgAdfgvxIntro-Dialogfeld

IMPLEMENT_DYNAMIC(DlgAdfgvxIntro, CDialog)
DlgAdfgvxIntro::DlgAdfgvxIntro(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAdfgvxIntro::IDD, pParent)
	, noIntro(FALSE)
{
}

DlgAdfgvxIntro::~DlgAdfgvxIntro()
{
}

void DlgAdfgvxIntro::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, noIntro);
}


BEGIN_MESSAGE_MAP(DlgAdfgvxIntro, CDialog)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
END_MESSAGE_MAP()


// DlgAdfgvxIntro-Meldungshandler

void DlgAdfgvxIntro::OnBnClickedCheck1()
{
	UpdateData(true);

	if (noIntro==true)
		theApp.WriteProfileInt("Settings","ADFGVX_IntroDialogue",0);
	else
		theApp.WriteProfileInt("Settings","ADFGVX_IntroDialogue",1);
}
