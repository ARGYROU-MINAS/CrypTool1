//////////////////////////////////////////////////////////////////
// Copyright 1998-2000 Deutsche Bank AG, Frankfurt am Main
//////////////////////////////////////////////////////////////////
// DlgAsymKeyCreat.cpp: Implementierungsdatei
//////////////////////////////////////////////////////////////////
// Programmiert von Bartol Filipovic 1999-2000
// Deutsche Bank AG Frankfurt - IT Security
//////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "multipad.h"
#include "DlgAsymKeyCreat.h"

#include "secure.h"	// Header-File f�r das SECUDE-Toolkit
#include "af.h"		// Header-File f�r den SECUDE Authentication Framework
//#include "fileutil.h"
#include "pkcs.h"	// SECUDE Header-File

#include "s_ecFp.h"
#include "s_ecconv.h"
#include "arithmet.h"

#include "Read_Ini_File.h"
#include "KeyFileHandling.h"
#include "DlgEcKeysCreat.h"
#include "DLG_param.h"

#include <time.h>


// the extern (global) Variables are from multipad.cpp
extern char *Pfad; // Directory Path of the main programm
extern char pc_str[STR_LAENGE_STRING_TABLE]; // from multipad.cpp
extern char pc_str1[STR_LAENGE_STRING_TABLE]; // from multipad.cpp

extern char *CaPseDatei, *CaPseVerzeichnis, *Pfad, *PseVerzeichnis; // aus multipad.cpp


/////////////////////////////////////////////////////////////////////////////
// Dialogfeld CDlgAsymKeyCreat 


CDlgAsymKeyCreat::CDlgAsymKeyCreat(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAsymKeyCreat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAsymKeyCreat)
	m_edit1 = _T("");
	m_edit2 = _T("");
	m_edit3 = _T("");
	m_edit4 = _T("");
	m_rsa_modul_str = _T("");
	m_dsa_prime_str = _T("");
	m_ec_dom_par_str = _T("");
	m_verfahren = -1;
	m_zahlensystem = -1;
	m_ShowKeypair = FALSE;
	m_user_keyinfo = _T("");
	m_ec_dom_par_editbox = _T("");
	//}}AFX_DATA_INIT

	curveParameter = (EcDomParam_ac_ptr) malloc(sizeof(__DomParamAc_struct)); // Allocate memory. !! DELETE with destruktor!!
	if (curveParameter == NULL) return; // error. keine Speicherallokation
	curveParameter->E = (ecFp_curve_t) malloc(sizeof(__CurveFp_struct));
	if (curveParameter->E == NULL) return; // error. keine Speicherallokation
	curveParameter->G = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
	if (curveParameter->G == NULL) return; // error. keine Speicherallokation
	curveParameter->pubKey = (ecFp_point_ac_t) malloc(sizeof(__PointAc_struct));
	if (curveParameter->pubKey == NULL) return; // error. keine Speicherallokation
	curveParameter->pubKey->infinity=1; // pubKey is not defined yet
	inttoln(0, curveParameter->privKey); // initialize privKey = 0 (not defined yet)
}

CDlgAsymKeyCreat::~CDlgAsymKeyCreat()
{
	free (curveParameter->pubKey);
	free (curveParameter->G);
	free (curveParameter->E);
	free (curveParameter);
}


void CDlgAsymKeyCreat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAsymKeyCreat)
	DDX_Control(pDX, IDC_LIST1, m_dom_param_listview);
	DDX_Control(pDX, IDC_EDIT5, m_ctrl5);
	DDX_Control(pDX, IDC_CHECK1, m_ShowKeypairButton);
	DDX_Control(pDX, IDC_RADIO6, m_hexadecimal_radio);
	DDX_Control(pDX, IDC_RADIO5, m_decimal_radio);
	DDX_Control(pDX, IDC_RADIO4, m_octal_radio);
	DDX_Control(pDX, IDC_RADIO1, m_RSARadio);
	DDX_Control(pDX, IDC_RADIO3, m_ECRadio);
	DDX_Control(pDX, IDC_RADIO2, m_DSARadio);
	DDX_Control(pDX, IDC_COMBO3, m_ec_combo);
	DDX_Control(pDX, IDC_COMBO2, m_dsa_combo);
	DDX_Control(pDX, IDC_COMBO1, m_rsa_combo);
	DDX_Control(pDX, IDC_EDIT4, m_ctrl4);
	DDX_Control(pDX, IDC_EDIT3, m_ctrl3);
	DDX_Control(pDX, IDC_EDIT2, m_ctrl2);
	DDX_Control(pDX, IDC_EDIT1, m_ctrl1);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
	DDX_CBString(pDX, IDC_COMBO1, m_rsa_modul_str);
	DDX_CBString(pDX, IDC_COMBO2, m_dsa_prime_str);
	DDX_CBString(pDX, IDC_COMBO3, m_ec_dom_par_str);
	DDX_Radio(pDX, IDC_RADIO1, m_verfahren);
	DDX_Radio(pDX, IDC_RADIO4, m_zahlensystem);
	DDX_Check(pDX, IDC_CHECK1, m_ShowKeypair);
	DDX_Text(pDX, IDC_EDIT5, m_user_keyinfo);
	DDX_Text(pDX, IDC_EDIT6, m_ec_dom_par_editbox);
	//}}AFX_DATA_MAP
}

//	DDX_Control(pDX, IDC_RADIO3, m_ec_radio);

BEGIN_MESSAGE_MAP(CDlgAsymKeyCreat, CDialog)
	//{{AFX_MSG_MAP(CDlgAsymKeyCreat)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeEcCombo)
	ON_BN_CLICKED(IDC_RADIO1, OnRSARadio)
	ON_BN_CLICKED(IDC_RADIO2, OnDSARadio)
	ON_BN_CLICKED(IDC_RADIO3, OnECRadio)
	ON_BN_CLICKED(IDC_RADIO5, OnDecimalRadio)
	ON_BN_CLICKED(IDC_RADIO4, OnOctalRadio)
	ON_BN_CLICKED(IDC_RADIO6, OnHexRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Behandlungsroutinen f�r Nachrichten CDlgAsymKeyCreat 

void CDlgAsymKeyCreat::OnOK() 
{
	UpdateData (TRUE);

	// Check if Name, Last Name, PIN-Code, and PIN-Verification were entered
	if (m_edit1==""){
		// Name fehlt
		LoadString(AfxGetInstanceHandle(),IDS_STRING41416,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41408,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_ctrl1.SetFocus();
		return;
	}

	if (m_edit2==""){
		// Vorname fehlt
		LoadString(AfxGetInstanceHandle(),IDS_STRING41417,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41408,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_ctrl2.SetFocus();
		return;
	}

	if (m_edit3==""){
		// PIN-Code fehlt
		LoadString(AfxGetInstanceHandle(),IDS_STRING41418,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41408,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_ctrl3.SetFocus();
		return;
	}

	if (m_edit4==""){
		// PIN-Code-Verifikation fehlt
		LoadString(AfxGetInstanceHandle(),IDS_STRING41419,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41408,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_ctrl4.SetFocus();
		return;
	}

	if (m_edit3!=m_edit4){
		// PIN-Code und PIN-Code-Verifikation stimmen nicht �berein
		LoadString(AfxGetInstanceHandle(),IDS_STRING41420,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41408,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		// Die Eingabefelder von PIN und PIN-Verifikation l�schen
		m_edit3="";
		m_edit4="";
		UpdateData(FALSE);
		m_ctrl3.SetFocus();
		return;
	}

	if ( /*(m_edit1.Find(EC_KEYFILE_IDSTRING ) > (-1)) ||*/ (m_edit1.Find(PSE_FILE_SUFFIX) > (-1)) ||
		 /*(m_edit2.Find(EC_KEYFILE_IDSTRING ) > (-1)) ||*/ (m_edit2.Find(PSE_FILE_SUFFIX) > (-1)) ||
		 /*(m_user_keyinfo.Find(EC_KEYFILE_IDSTRING ) > (-1)) ||*/ (m_user_keyinfo.Find(PSE_FILE_SUFFIX) > (-1)) )
	{		
		// Name oder Vorname oder Schl�sselkennung enth�lt unzul�ssige Zeichenfolge.
		// EC_KEYFILE_IDSTRING, "RSA" und "DSA" werden intern zum identifizieren Schl�sselbezeichnern
		// benutzt - diese Teilstrings d�rfen aber dennoch vom Benutzer eingegeben werden, da es 
		// in der Funktion CKeyFile::ExtractData() zu keinen Problemen kommt.
		// PSE_FILE_SUFFIX dient als Dateiendung f�r die Datei in der geheimer Schl�ssel
		// gespeichert wird (PSE) und sollte/darf nicht in den Benutzereingaben auftauchen.
		char tmp_str[200];
		LoadString(AfxGetInstanceHandle(),IDS_STRING41559,pc_str,STR_LAENGE_STRING_TABLE);
		sprintf(tmp_str, pc_str, PSE_FILE_SUFFIX);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41560,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(tmp_str,pc_str1,MB_ICONWARNING|MB_OK);

		/* Eingaben nicht l�schen, damit Benutzer noch sieht was er eingegeben hatte.
		if ( m_user_keyinfo.Find(EC_KEYFILE_IDSTRING ) > (-1) ){
			m_ctrl5.SetFocus();
			m_user_keyinfo = ""; // Eingabe l�schen
		}
		else if ( m_edit1.Find(EC_KEYFILE_IDSTRING ) > (-1) ){
			m_ctrl1.SetFocus();
			m_edit1 = ""; // Eingabe l�schen
		}
		else if ( m_edit2.Find(EC_KEYFILE_IDSTRING ) > (-1) ){
			m_ctrl2.SetFocus();
			m_edit2 = ""; // Eingabe l�schen
		}
		*/
		return;
	}

	// Der Name und Vorname, sowie die optionale Schl�sselkennung werden als Dateinamen
	// benutzt. Daher sind einige (BETRIEBSYSTEMABH�NGIGE) Sonderzeichen (Win NT: \/:*?"<>| )
	// nicht erlaubt. Eine diesbez�gliche �berpr�fung findet nun statt.
	// Weiterhin werden einige Zeichen ausgeschlossen die intern von CrypTool zum Parsen von Dateinamen
	// benutzt werden, z.B. [ und ]
	if ((m_edit1.FindOneOf("\\/:*?\"<>|~$%&,;[]") > (-1)) ||
		(m_edit2.FindOneOf("\\/:*?\"<>|~$%&,;[]") > (-1)) ||
		(m_user_keyinfo.FindOneOf("\\/:*?\"<>|~$%&,;[]") > (-1)) ){
		// AfxMessageBox("Sonderzeichen enthalten");
		LoadString(AfxGetInstanceHandle(),IDS_STRING41549,pc_str,STR_LAENGE_STRING_TABLE);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41560,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str, pc_str1, MB_ICONWARNING|MB_OK);
		return;
	}
	
	// convert the String m_rsa_modul_str (from rsa-combobox) to an int, and store it in rsa_modul
	LPTSTR modul_char = new TCHAR[m_rsa_modul_str.GetLength()+1];
	_tcscpy(modul_char, m_rsa_modul_str);
	rsa_modul = atoi(modul_char);
	delete(modul_char);

	// convert the String m_dsa_prime_str (from dsa-combobox) to an int, and store it in dsa_modul
	LPTSTR prime_char = new TCHAR[m_dsa_prime_str.GetLength()+1];
	_tcscpy(prime_char, m_dsa_prime_str);
	dsa_prime = atoi(prime_char);
	delete(prime_char);

	// Check if the value in rsa-combobox is valid for rsa_keysize
	if ((m_rsa_combo.IsWindowEnabled()) && 
		((rsa_modul<MIN_RSA_MODULSIZE) || (rsa_modul>MAX_RSA_MODULSIZE)))
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING41421,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, pc_str1, MIN_RSA_MODULSIZE-1, MAX_RSA_MODULSIZE+1);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41422,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_rsa_combo.SetFocus();
		return;
	}

	if (m_dsa_combo.IsWindowEnabled() && dsa_prime>MAX_RSA_MODULSIZE)
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING61419,pc_str1,STR_LAENGE_STRING_TABLE);
		sprintf(pc_str, pc_str1, MAX_RSA_MODULSIZE+1);
		LoadString(AfxGetInstanceHandle(),IDS_STRING41422,pc_str1,STR_LAENGE_STRING_TABLE);
		MessageBox(pc_str,pc_str1,MB_ICONWARNING|MB_OK);
		m_dsa_combo.SetFocus();
		return;
	}

	CreateAsymKeys(); // Create Keys with memberfunction CreateAsymKeys()

	// Die Eingabefelder von PIN und PIN-Verifikation l�schen
	m_edit3="";
	m_edit4="";
	UpdateData(FALSE);
	m_ctrl3.SetFocus();

	return; // Dialogbox ge�ffnet lassen, um dem Benutzer die M�glichkeit zu geben mehrere
	// Schl�ssel unter seinem Namen direkt hintereinander anzulegen

	// CDialog::OnOK();
}

BOOL CDlgAsymKeyCreat::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// m_dom_param_listview aufbauen

	LoadString(AfxGetInstanceHandle(),IDS_STRING32887,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 0, pc_str, LVCFMT_RIGHT, 65 , 0); // Parameter

	LoadString(AfxGetInstanceHandle(),IDS_STRING32888,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 1, pc_str, LVCFMT_LEFT, 455 , 1); // Wert des Parameters

	LoadString(AfxGetInstanceHandle(),IDS_STRING32894,pc_str,STR_LAENGE_STRING_TABLE);
	m_dom_param_listview.InsertColumn( 2, pc_str, LVCFMT_LEFT, 50 , 2); // Bitl�nge

	// Daten Initialisieren

	CReadIniFile iniFile;

	CReadIniFile::CStringList ecIDlist;

	CString default_rsa_modulsize = "512"; // Default: RSA with 512 Bits
	CString default_dsa_primesize = "512"; // Default: DSA with 512 Bits

	int combolist_stringindex;

	m_rsa_combo.LimitText(4); // User can insert at most 4 characters

	// SELECT default key size from the (preinitialized) combolist entries
	m_rsa_combo.SelectString(-1, default_rsa_modulsize);
	m_dsa_combo.SelectString(-1, default_dsa_primesize);

	base = 10; // display numbers in listbox (elliptic curve parameters) in base 'base'

	CheckRadioButton (IDC_RADIO1, IDC_RADIO3, IDC_RADIO1); // RSA key generation is default setup

	CheckRadioButton (IDC_RADIO4, IDC_RADIO6, IDC_RADIO5); // select the radio button which represents base

	m_dsa_combo.EnableWindow(FALSE); // Set dsa-combobox inactiv
	m_ec_combo.EnableWindow(FALSE); // Set ec-combobox inactiv
	m_dom_param_listview.EnableWindow(FALSE); // Set "elliptic curve parameter info box" inactiv
	m_octal_radio.EnableWindow(FALSE); // and so on ...
	m_decimal_radio.EnableWindow(FALSE);
	m_hexadecimal_radio.EnableWindow(FALSE);
	m_ShowKeypairButton.EnableWindow(TRUE);

	m_ShowKeypairButton.SetCheck(1); // Check the button

	UpdateData(TRUE);

	if (iniFile.GetEcIDList(ecIDlist) == -1)
	{
		m_ECRadio.EnableWindow(FALSE); // Enable ec_radio_button (not able to read iniFile)
	}
	else
	{
		// no problems due opening IniFile 
		while ( !ecIDlist.IsEmpty()){
			m_ec_combo.AddString(ecIDlist.RemoveHead()); // Add curve ID to combobox-list
		}	

		if (!iniFile.GetPreSelEcID(curveID))
		{
			// A curve ID is in the iniFile specified as default curve ID 
			combolist_stringindex = m_ec_combo.SelectString( -1, curveID);
		}

		iniFile.GetEcDomParam(curveID, curveParameter); // get curve parameter of the curve with name 'curveID'

		// Convert curve parameter to numberstrings in default_base
		int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
		if (error)
		{
			// error while converting curveParameter to Strings
			LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
			return TRUE;
		}

		UpdateEcListBox(curveParameter, &ecParamString, curveID);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zur�ckgeben
}


void CDlgAsymKeyCreat::UpdateEcListBox(EcDomParam_ac_ptr curveParameter, EcDomParamAcAsString *ecParamString, CString curveID)
{	
	unsigned int bitlength;

	UpdateData(TRUE);
	LoadString(AfxGetInstanceHandle(),IDS_STRING32889,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str1, pc_str, curveID);
	m_ec_dom_par_editbox = (CString) pc_str1;
	UpdateData(FALSE);

	m_dom_param_listview.DeleteAllItems(); // Delete all data in the listview
	m_dom_param_listview.InsertItem( 0, " " );
	m_dom_param_listview.InsertItem( 1, "a" );
	m_dom_param_listview.SetItemText( 1, 1, ecParamString->a );
	// l = lngtouse(L_NUMBER r); /* l+1 == (length of r in bits) */
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->E->a);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 1, 2, pc_str ); // Bitl�nge von a

	m_dom_param_listview.InsertItem( 2, "b" );
	m_dom_param_listview.SetItemText( 2, 1, ecParamString->b );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->E->b);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 2, 2, pc_str ); // Bitl�nge von b

	m_dom_param_listview.InsertItem( 3, "p" );
	m_dom_param_listview.SetItemText( 3, 1, ecParamString->p );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->E->p);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 3, 2, pc_str ); // Bitl�nge von p

	LoadString(AfxGetInstanceHandle(),IDS_STRING32890,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str1, pc_str, curveID);
	m_dom_param_listview.InsertItem( 4, (CString) pc_str1 ); // "x coord of G"
	m_dom_param_listview.SetItemText( 4, 1, ecParamString->G_xcoord );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->G->x);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 4, 2, pc_str ); // Bitl�nge von x coord of G

	LoadString(AfxGetInstanceHandle(),IDS_STRING32891,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str1, pc_str, curveID);
	m_dom_param_listview.InsertItem( 5, (CString) pc_str1 ); // "y coord of G"
	m_dom_param_listview.SetItemText( 5, 1, ecParamString->G_ycoord );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->G->y);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 5, 2, pc_str ); // Bitl�nge von y coord of G

	m_dom_param_listview.InsertItem( 6, "k" );
	m_dom_param_listview.SetItemText( 6, 1, ecParamString->k );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->k);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 6, 2, pc_str ); // Bitl�nge von k

	m_dom_param_listview.InsertItem( 7, "r" );
	m_dom_param_listview.SetItemText( 7, 1, ecParamString->r );
	bitlength = theApp.SecudeLib.lngtouse(curveParameter->r);
	_itoa(bitlength+1, pc_str, 10);
	m_dom_param_listview.SetItemText( 7, 2, pc_str ); // Bitl�nge von r

	m_dom_param_listview.InsertItem( 8, " " );
}


void CDlgAsymKeyCreat::OnSelchangeEcCombo() 
{
	// Show parameters of the selected curve ID
	// The parameters are loaded from the file 'initializing_file'

	CReadIniFile iniFile;

	m_ec_combo.GetLBText(m_ec_combo.GetCurSel(), curveID);

	iniFile.GetEcDomParam(curveID, curveParameter); // get curve parameter of the curve with name 'curveID'

	// Convert curve parameter to numberstrings in default base
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error)
	{
		// error while converting curveParameter to Strings
		LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		return;
	}

	UpdateEcListBox(curveParameter, &ecParamString, curveID);

}

void CDlgAsymKeyCreat::OnRSARadio() 
{
	m_rsa_combo.EnableWindow(TRUE); // Set rsa-combobox activ
	m_dsa_combo.EnableWindow(FALSE); // Set dsa-combobox inactiv
	m_ec_combo.EnableWindow(FALSE); // Set ec-combobox inactiv
	m_dom_param_listview.EnableWindow(FALSE); // Set "elliptic curve parameter info box" inactiv
	m_octal_radio.EnableWindow(FALSE);
	m_decimal_radio.EnableWindow(FALSE);
	m_hexadecimal_radio.EnableWindow(FALSE);
	m_ShowKeypairButton.EnableWindow(TRUE);
}

void CDlgAsymKeyCreat::OnDSARadio() 
{
	m_rsa_combo.EnableWindow(FALSE); // Set rsa-combobox inactiv
	m_dsa_combo.EnableWindow(TRUE); // Set dsa-combobox activ
	m_ec_combo.EnableWindow(FALSE); // Set ec-combobox inactiv
	m_dom_param_listview.EnableWindow(FALSE); // Set "elliptic curve parameter info box" inactiv
	m_octal_radio.EnableWindow(FALSE);
	m_decimal_radio.EnableWindow(FALSE);
	m_hexadecimal_radio.EnableWindow(FALSE);
	m_ShowKeypairButton.EnableWindow(FALSE);
}

void CDlgAsymKeyCreat::OnECRadio() 
{
	m_rsa_combo.EnableWindow(FALSE); // Set rsa combobox inactiv
	m_dsa_combo.EnableWindow(FALSE); // Set dsa combobox inactiv
	m_ec_combo.EnableWindow(TRUE); // Set ec combobox activ
	m_dom_param_listview.EnableWindow(TRUE); // Set "elliptic curve parameter info box" activ
	m_octal_radio.EnableWindow(TRUE);
	m_decimal_radio.EnableWindow(TRUE);
	m_hexadecimal_radio.EnableWindow(TRUE);
	m_ShowKeypairButton.EnableWindow(TRUE);
}

void CDlgAsymKeyCreat::OnDecimalRadio() 
{
	base = 10;
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error)
	{
		// error while converting curveParameter to Strings
		LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		return;
	}
	UpdateEcListBox(curveParameter, &ecParamString, curveID);
}

void CDlgAsymKeyCreat::OnOctalRadio() 
{
	base = 8;
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error)
	{
		// error while converting curveParameter to Strings
		LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		return;
	}
	UpdateEcListBox(curveParameter, &ecParamString, curveID);
}

void CDlgAsymKeyCreat::OnHexRadio() 
{
	base = 16;
	int error = EcDomParamAcToString(&ecParamString, curveParameter, base);
	if (error)
	{
		// error while converting curveParameter to Strings
		LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
		AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
		return;
	}
	UpdateEcListBox(curveParameter, &ecParamString, curveID);
}


/* Die folgende Funktion erzeugt ein (asymmetrisches) Schl�sselpaar und legt es
   PIN-gesch�tzt lokal ab.
   Grunds�tzlich mu� hier zwischen Verfahren unterschieden werden, die auf dem
   SECUDE-Toolkit aufbauen und Verfahren, die komplett selbst erstellt wurden.

   Verfahren, die auf SECUDE aufbauen:
   Ein Schl�sselpaar und eine PSE (Personal Secure Environment, durch PIN-Nummer
   gesch�tzter Bereich eines Benutzers) werden erzeugt. Der geheime Schl�ssel wird
   in der PSE (PIN-gesch�tzt) abgelegt. Der �ffentliche Schl�ssel wird durch eine 
   lokale CA zertifiziert und das Zertifikat in einer CA-Datenbank abgelegt.

   Komplett selbst erstellte Verfahren:
   Auch hier werden ein Schl�sselpaar und eine PSE erzeugt. Der geheime Schl�ssel
   wird wieder in der PSE gespeichert.
   Dieser Schl�ssel kann allerdings nicht durch die Funktionen im SECUDE-Toolkit
   zertifiziert werden, da dazu der (lokalen) CA ein selbst-signiertes (Prototyp-)
   Zertifikat vorzulegen w�re, dessen Unterschrift sie �berpr�ft und bei korrekter
   Verifikation zertifiziert.
   Da SECUDE das entsprechende Signaturverfahren jedoch nicht kennt, kann es auch die 
   Signatur nicht �berpr�fen.
   Deshalb werden die �ffentlichen Schl�ssel (lokal) in einer �ffentlichen Datei abgelegt.
   Dies betrifft vorerst nur Signatur-Verfahren, die auf Elliptischen Kurven arbeiten.
   Bei Hinzuf�gen von weiteren Verfahren, die nicht von SECUDE bereitgestellt werden, stellt
   sich jedoch dasselbe Problem.
*/
void CDlgAsymKeyCreat::CreateAsymKeys()
{
	AlgId *Algorithmus;
	Key keyinfo;

	CKeyFile KeyHandling; // In der Datei CKeyFile::KeyHandling werden die Schl�sselbezeichner
	                      // abgespeichert

	bool use_secude_api;
	CString verfahren;
	CString keyBits;
	CString UserKeyId;
	CString time_of_creat;
	int error;

	CString UserName = m_edit1;
	CString UserFirstName = m_edit2;
	CString UserPinCode = m_edit3;

	clock_t start;
	clock_t finish;
	double duration;

	// Ermittlung des vom Benutzer im Dialogfeld gew�hlten Verfahrens:
			
	if (m_verfahren == 0)
	{
		// Generate RSA key pair
		use_secude_api = TRUE;
		Algorithmus = theApp.SecudeLib.md5WithRsaEncryption_aid;
		keyinfo.alg = theApp.SecudeLib.rsa_aid;
		keyinfo.key_size = rsa_modul; // used keysize as int
		verfahren = RSA_KEYFILE_IDSTRING;
		keyBits = m_rsa_modul_str; // used keysize as string
	}
	if (m_verfahren == 1)
	{
		// Generate DSA key pair
		use_secude_api = TRUE;
		Algorithmus = theApp.SecudeLib.dsaWithSHA1_aid;
		keyinfo.alg = theApp.SecudeLib.dsa_aid;
		keyinfo.key_size = dsa_prime; // used keysize as int
		verfahren = DSA_KEYFILE_IDSTRING;
		keyBits = m_dsa_prime_str; // used keysize as string
	}
	if (m_verfahren == 2)
	{
		// Generate Elliptic Curve key pair
		
		use_secude_api = FALSE;

		// generate keys
		if (m_ShowKeypair == TRUE)
		{
			// User wants to see the generated keypair
			start = clock();
			CDlgEcKeysCreat ShowEcKeys(curveParameter, &ecParamString, curveID);
			if(ShowEcKeys.DoModal()==IDCANCEL) return; // Cancel Button pushed
			else
			{
				// key pair was generated in ShowEcKeys()
				// ecParamString und curveParameter sind entsprechend initialisiert
				finish = clock();
				duration = (double)(finish - start) / CLOCKS_PER_SEC; // Dauer der Schl�ssel Erzeugung
			}
		}
		else
		{
			// User didn't want to see the generated keypair; there is no keypair generated yet
			theApp.DoWaitCursor(1);
			start = clock();
			error = GenEcKeyPair(curveParameter); // create key pairs
			finish = clock();
			duration = (double)(finish - start) / CLOCKS_PER_SEC; // Dauer der Schl�ssel Erzeugung
			if (error)
			{
				// error while creating key pair
				LoadString(AfxGetInstanceHandle(),IDS_STRING41541,pc_str,STR_LAENGE_STRING_TABLE);
				AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
				return;
			}
			error = EcDomParamAcToString(&ecParamString, curveParameter, 16);
			if (error)
			{
				// error while converting curveParameter to Strings
				LoadString(AfxGetInstanceHandle(),IDS_STRING41545,pc_str,STR_LAENGE_STRING_TABLE);
				AfxMessageBox (((CString)pc_str),MB_ICONSTOP);
				return;
			}
			theApp.DoWaitCursor(0);
		}
		
		theApp.DoWaitCursor(1);
		// Datum und Zeitpunkt der Schl�sselerzeugung
		char buffer[20];
		time_t aclock;
		time( &aclock ); // Get time in seconds
		_itoa(aclock, buffer, 10);
		time_of_creat = (CString) buffer; // time_of_creat: Time in seconds since UTC 1/1/70

		UserKeyId = KeyHandling.CreateFilename(UserName, UserFirstName, EC_KEYFILE_IDSTRING, m_ec_dom_par_str, time_of_creat, m_user_keyinfo);
		// UserKeyId ist der Dateiname ohne Suffix PSE_FILE_SUFFIX
		// UserKeyId ist aufgrund von time_of_creat EINDEUTIG

		// create public and private keyfiles 
		error = KeyHandling.CreateEcKeyFiles(UserKeyId, UserPinCode, curveParameter, &ecParamString);
		if (error == -1)
		{
			// irgendein Fehler beim erzeugen der PSE ist aufgetreten
			LoadString(AfxGetInstanceHandle(),IDS_STRING41430,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			return;
		}
		else if (error == -2)
		{
			// irgendein Fehler beim �ffnen der PSE ist aufgetreten
			LoadString(AfxGetInstanceHandle(),IDS_STRING41432,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			return;
		}
		else if (error == -9)
		{
			// Fehler: die Dateien f�r die �ffentlichen bzw. geheimen Parameter konnten nicht
			// im Verzeichnis "Pfad" (siehe multipad.cpp) erzeugt werden
			LoadString(AfxGetInstanceHandle(),IDS_STRING32877,pc_str,STR_LAENGE_STRING_TABLE);
			sprintf(pc_str1, pc_str, Pfad);
			AfxMessageBox (((CString)pc_str1),MB_ICONSTOP);
			return;
		}
		else if (error != 0)
		{
			return; // sonstige Fehler
		}

		theApp.DoWaitCursor(0);
	}

	if (use_secude_api)
	{
		// RSA or DSA key generation with secude API's

		// Datum und Zeitpunkt der Schl�sselerzeugung
		char buffer[20];
		time_t aclock;
		time( &aclock ); // Get time in seconds
		_itoa(aclock, buffer, 10);
		time_of_creat = (CString) buffer; // time_of_creat: Time in seconds since UTC 1/1/70

		// Anlegen der PSE mit den Daten aus den Eingabefeldern der Dialogbox, dabei werden zus�tzliche
		// Erkennungsmerkmale verwendet:

		UserKeyId = KeyHandling.CreateFilename(UserName, UserFirstName, verfahren, keyBits, time_of_creat, m_user_keyinfo);
		// UserKeyId ist aufgrund von time_of_creat EINDEUTIG

		CString secret_key_file = (CString) PseVerzeichnis + ((CString)"/") + UserKeyId + ((CString)PSE_FILE_SUFFIX);
		LPTSTR string2 = new TCHAR[secret_key_file.GetLength()+1];
		_tcscpy(string2, secret_key_file);		
		char *string3=string2;

		// Kopieren von CString m_edit3 nach char *string5, PIN-Nummer
		LPTSTR string4 = new TCHAR[m_edit3.GetLength()+1];
		_tcscpy(string4, m_edit3);
		char *string5=string4;
		
		// Anlegen einer PSE f�r den neuen Benutzer 
		// Erkl�rung der Parameter
		// string 3: Name der PSE samt absoluter Pfad
		// NULL	   : PSE f�r Benutzer anlegen
		// string 5: PIN-Nummer
		// NULL    : Software-PSE anlegen
		// TRUE    : Schl�sselpaar in PSE kann f�r Verschl. und Sign. verwendet werden
		PSE PseHandle;
		
		PseHandle=theApp.SecudeLib.af_create (string3  , NULL, string5, NULL, TRUE);
		if (PseHandle==NULL)
		{	// Fehler bei der PSE-Erzeugung
			LoadString(AfxGetInstanceHandle(),IDS_STRING41430,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			return;
		}

		// Initialisierung der Struktur, in die der neu erzeugte Schl�ssel abgelegt wird
		keyinfo.key=NULL;
		keyinfo.pse_sel=NULL;
		keyinfo.add_object=NULL;
		keyinfo.add_object_type=NULL;
		keyinfo.private_key=NULL;

		theApp.DoWaitCursor(1);
		start = clock();
		error = theApp.SecudeLib.af_gen_key (PseHandle, &keyinfo, SIGNATURE, 1); // create key pairs
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC; // Dauer der Schl�ssel Erzeugung
		if (error == -1)
		{
			// Fehler bei der Schl�sselerzeugung
			LoadString(AfxGetInstanceHandle(),IDS_STRING41542,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// L�sche die neu angelegte PSE
			remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			theApp.DoWaitCursor(0);
			return;
		}
		else                         // Secude Api ???
		{
			int mlen,elen,i;
			unsigned char *buf;
			KeyBits *ki;
			L_NUMBER temp[MAXLGTH];

			ki=theApp.SecudeLib.d_KeyBits(&(keyinfo.key->subjectkey));
			if (ki&&m_ShowKeypair == TRUE)
			{
				class DLG_param showparam;

				mlen=ki->part1.noctets;
				buf=(unsigned char *)ki->part1.octets;
				sprintf(pc_str,"0x");
				for (i=0;i<mlen;i++)
					sprintf(pc_str+2+(2*i),"%02X",buf[i]);
				string_to_ln(pc_str,temp);
				LoadString(AfxGetInstanceHandle(),IDS_STRING61420,pc_str,STR_LAENGE_STRING_TABLE);
				showparam.addentry(pc_str,temp);
				elen=ki->part2.noctets;
				buf=(unsigned char *)ki->part2.octets;
				sprintf(pc_str,"0x");
				for (i=0;i<elen;i++)
					sprintf(pc_str+2+(2*i),"%02X",buf[i]);
				string_to_ln(pc_str,temp);
				LoadString(AfxGetInstanceHandle(),IDS_STRING61421,pc_str,STR_LAENGE_STRING_TABLE);
				showparam.addentry(pc_str,temp);
				LoadString(AfxGetInstanceHandle(),IDS_STRING61422,pc_str,STR_LAENGE_STRING_TABLE);
				sprintf(pc_str1,pc_str,UserKeyId);
				showparam.settitel(pc_str1);
				if (showparam.DoModal()!=IDOK)
				{
					remove(string3);
					// Freigeben von dynamisch angelegtem Speicher
					delete string2;
					delete string4;
					theApp.DoWaitCursor(0);
					return;
				}

			}
		}
		theApp.DoWaitCursor(0);

		// Initialisierung der Variablen, die zur Zertifizierung notwendig sind
		OctetString SNummer;
		char *string="000001";
		SNummer.noctets=strlen(string);
		SNummer.octets=string;

		DName *DisName; // Distinguishing Name: unter diesem Bezeichner/Namen wird das Zertifikat in die
		                // CA-Datenbank geschrieben
		CString string6 = KeyHandling.CreateDistName(UserName, UserFirstName, time_of_creat);
		LPTSTR string7 = new TCHAR[string6.GetLength()+1];
		_tcscpy(string7, string6);
		char *string8=string7;

		DisName=theApp.SecudeLib.aux_Name2DName(string8);

		// Erzeugung des Prototyp-Zertifikates
		// Erkl�rung der Parameter:
		// PseHandle    : 
		// keyinfo.key  : zu zertifizierender �ff. Schl.
		// Algorithmus  : Algorithmus-Identifier
		// SKnew        : 
		// DisName
		// SNummer
		// NULL
		// NULL
		// TRUE
		// NULL

		Certificate *Zert;
		Zert=theApp.SecudeLib.af_create_Certificate (PseHandle, keyinfo.key, Algorithmus,"SKnew",
			DisName, &SNummer, NULL, NULL, TRUE, NULL);
		if (Zert==NULL)
		{
			// Fehler bei der Zertifikatserzeugung
			LoadString(AfxGetInstanceHandle(),IDS_STRING41433,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// L�sche die neu angelegte PSE
			remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			delete string7;
			return;
		}

		PSE PseHandle2;
		
		// �ffnen der CA-PSE
		PseHandle2=theApp.SecudeLib.af_open(CaPseDatei, CaPseVerzeichnis, PSEUDO_MASTER_CA_PINNR, NULL);
		if (PseHandle2==NULL)
		{
			// Fehler beim �ffnen der CA-PSE
			LoadString(AfxGetInstanceHandle(),IDS_STRING41411,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// L�sche die neu angelegte PSE
			remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			delete string7;
			return;
		}

		// �bergabe des Prototyp-Zertifikates an die CA, die den enthaltenen Schl�ssel
		// zertifiziert
		Certificate *Zert2;
		Zert2=theApp.SecudeLib.af_certify(PseHandle2, Zert, NULL, theApp.SecudeLib.md5WithRsaEncryption_aid, NULL);
		if (Zert2==NULL)
		{
			// Fehler bei der Zertifizierung
			LoadString(AfxGetInstanceHandle(),IDS_STRING41434,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// L�sche die neu angelegte PSE
			remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			delete string7;
			return;
		}
		
		//Zertifikat in die CA-Datenbank einf�gen!!!
		int fehler=theApp.SecudeLib.af_cadb_add_Certificate (PseHandle2, SIGNATURE, Zert2);
		if (fehler==-1)
		{
			// Fehler beim Einf�gen des Zertifikats in die CA-Datenbank
			LoadString(AfxGetInstanceHandle(),IDS_STRING41435,pc_str,STR_LAENGE_STRING_TABLE);
			AfxMessageBox (((CString)pc_str)+theApp.SecudeLib.LASTTEXT,MB_ICONSTOP);
			// L�sche die neu angelegte PSE
			remove(string3);
			// Freigeben von dynamisch angelegtem Speicher
			delete string2;
			delete string4;
			delete string7;
			return;
		}
		
		theApp.SecudeLib.af_close(PseHandle2);
		theApp.SecudeLib.aux_free_DName (&DisName);
		theApp.SecudeLib.af_close(PseHandle);
		// Freigeben von dynamisch angelegtem Speicher

		delete string2;
		delete string4;
		delete string7;
	}

	// Eine Sekunde Verz�gerung eingebaut, damit time_of_creat: Time in seconds since UTC 1/1/70
	// f�r verschiedene Schl�ssel immer verschieden ist (Wahrung der EINDEUTIGKEIT von UserKeyId)
	Sleep(1000); // wait a second

	// user-information: key pair succesfully created.
	LoadString(AfxGetInstanceHandle(),IDS_STRING41440,pc_str,STR_LAENGE_STRING_TABLE);
	sprintf(pc_str1, pc_str, UserKeyId);
	LoadString(AfxGetInstanceHandle(),IDS_STRING32911,pc_str,STR_LAENGE_STRING_TABLE);
	char temp[100];
	sprintf(temp, pc_str, duration);
	AfxMessageBox (((CString)pc_str1)+((CString)"\n\n")+temp,MB_ICONINFORMATION);
}
