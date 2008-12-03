// DlgPrimeTest.cpp : Implementierungsdatei
//

#include "stdafx.h"
#include "CrypToolApp.h"
#include "DialogeMessage.h"
#include "DlgPrimeTest.h"
#include ".\dlgprimetest.h"
#include "DlgFactorisationDemo.h"

#include "PrimeTest.h"
#include "PrimeTestAKS.h"
#include "PrimePolynom.h"


// CDlgPrimeTest-Dialogfeld

IMPLEMENT_DYNAMIC(CDlgPrimeTest, CDialog)
CDlgPrimeTest::CDlgPrimeTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrimeTest::IDD, pParent)
  , m_radio(0)
  , m_algo(0)
{
  m_editNumber = _T("");
}

CDlgPrimeTest::~CDlgPrimeTest()
{
}

//////////////////////////////////////////////////////////////////////////////
UINT singleThreadAKS( PVOID x )
{
  CDlgPrimeTest *dlg;
  dlg = (CDlgPrimeTest*)x;

#ifdef PRIMETEST_TIME_MEASUREMENT
  // ----------------------------------
  // Time measurement
  clock_t time1, time2;
  double test_time;
  
  // Start timer
  time1 = clock();
  // ----------------------------------
#endif

  // Perform AKS
  int res = dlg->primAKS.aks();

#ifdef PRIMETEST_TIME_MEASUREMENT
  // ----------------------------------
  // Time measurement
  // End timer
  time2 = clock();
  
  // Calc duration
  test_time = ((double)time2 - (double)time1)/1000;
  
  // Set result to member field
  dlg->algoTime = test_time;
  // ----------------------------------
#endif

  // stopProcessing = 1 -> aks finished
  // stopProcessing = 0 -> aks canceled
  if(dlg->primAKS.stopProcessing != 0)
  {
    // Close Running dialog
    dlg->dlgRun->EndDialog(IDCANCEL);
        
    // AKS delivered result
    dlg->SetThreadResult(res);
  }
	return 0;
}

void CDlgPrimeTest::SetThreadResult(int res)
{
  // Update result field after AKS succeeded
  UpdateResultField(res, inputNumber);
}

//////////////////////////////////////////////////////////////////////////////

void CDlgPrimeTest::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_PRIMETEST_EDIT_RESULT, m_Result);
  DDX_Radio(pDX, IDC_PRIMETEST_RADIO_MILLERRABIN, m_algo);
  DDX_Control(pDX, IDC_PRIMETEST_EDIT_NUMBER, m_control_editName);
  DDX_Control(pDX, IDC_PRIMETEST_EDIT_NUMBER, m_control_editName);
  DDX_Text(pDX, IDC_PRIMETEST_EDIT_NUMBER, m_editNumber);
  DDX_Control(pDX, IDC_STATIC_PRIM_RES, m_picPrime);
  DDX_Control(pDX, IDC_STATIC_PRIM_RES2, m_picNotPrime);
  DDX_Control(pDX, IDC_BUTTON_JUMP_TO_FACTORIZATION, m_control_buttonJumpToFactorization);
}


BEGIN_MESSAGE_MAP(CDlgPrimeTest, CDialog)
  ON_BN_CLICKED(IDC_PRIMETEST_BUTTON_TEST, OnBnClickedPrimetestButtonTest)
  ON_BN_CLICKED(IDC_PRIMETEST_BUTTON_CANCEL, OnBnClickedPrimetestButtonCancel)
  ON_BN_CLICKED(IDC_PRIMETEST_BUTTON_LOADNUMBER, OnBnClickedPrimetestButtonLoadnumber)
  ON_BN_CLICKED(IDC_PRIMETEST_RADIO_MILLERRABIN, OnBnClickedAlgo)
  ON_EN_CHANGE(IDC_PRIMETEST_EDIT_NUMBER, OnEnChangePrimetestEditNumber)
  ON_BN_CLICKED(IDC_PRIMETEST_RADIO_FERMAT, OnBnClickedPrimetestRadio)
  ON_BN_CLICKED(IDC_PRIMETEST_RADIO_SOLOVAY, OnBnClickedPrimetestRadio)
  ON_BN_CLICKED(IDC_PRIMETEST_RADIO_MILLERRABIN, OnBnClickedPrimetestRadio)
  ON_BN_CLICKED(IDC_PRIMETEST_RADIO_AKS, OnBnClickedPrimetestRadio)
  ON_BN_CLICKED(IDC_BUTTON_JUMP_TO_FACTORIZATION, CDlgPrimeTest::OnBnClickedButtonJumpToFactorization)
END_MESSAGE_MAP()


// CDlgPrimeTest-Meldungshandler
void CDlgPrimeTest::OnBnClickedPrimetestButtonTest()
{

#ifdef PRIMETEST_TIME_MEASUREMENT
  // ----------------------------------
  // Fields needed for time measurement
  clock_t time1, time2;
  double test_time;
  // ----------------------------------
#endif
  
  int res;
  int err_ndx;
  CString strBigNum;
	Big numBig;

  // Clear edit field
  m_Result.SetWindowText("");

  // Hide result images
  m_picNotPrime.ShowWindow(FALSE);
  m_picPrime.ShowWindow(FALSE);

  // Read number:
  if(m_editNumber.IsEmpty())
  {
    Message( IDS_STRING_PRIMETEST_ERROR_EMPTY, MB_ICONSTOP ); 
  }
  else
  {
    // ----------------------------
    int error = CheckFormula(m_editNumber,10,strBigNum,err_ndx);
    if (error == 0)
	  {
		  //Fehler in der Eingabe, von Parser abgefangen
		  m_control_editName.SetSel(0,m_editNumber.GetLength());
		  m_control_editName.SetFocus();
		  Message( IDS_STRING_INPUT_FALSE, MB_ICONSTOP );
		  return;
	  }
    // ----------------------------

    // Check input number or term
    if(evaluate::CEvalIntExpr( numBig, m_editNumber.GetBuffer( m_editNumber.GetLength()+1) ) == false)
    {
		  // Zahl zu gross
		  m_control_editName.SetSel(0,m_editNumber.GetLength());
		  m_control_editName.SetFocus();
		  Message( IDS_STRING_BIG_NUMBER, MB_ICONINFORMATION );
		  return;
    }
    else
    {
      // Convert Big number to CString
      BigToCString( numBig, strBigNum );
    }

    // Set number as string to PrimeTest class
    // This field is used from the thread to retrieve the input number
    inputNumber = strBigNum.GetBuffer(strBigNum.GetLength()+1);
    
#ifdef PRIMETEST_TIME_MEASUREMENT
    // ----------------------------------
    // Start timer for time measurement
    time1 = clock();
    // ----------------------------------
#endif
    
    // Use chosen algorithm
    switch(m_algo)
    {
      case(0):  // Miller-Rabin
      {
        SHOW_HOUR_GLASS   // Change mouse pointer

        GeneratePrimes P;
        P.SetP(numBig);
        if(P.MillerRabinTest(100))
        {
          // change return value
          res = 1;
        }
        else
        {
          // change return value
          res = 0;
        }
        HIDE_HOUR_GLASS   // Change mouse pointer
        break;
      }
      case(1):  // Fermat
      {
        SHOW_HOUR_GLASS   // Change mouse pointer

        GeneratePrimes P;
        P.SetP(numBig);
        if(P.FermatTest(100))
        {
          // change return value
          res = 1;
        }
        else
        {
          // change return value
          res = 0;
        }
        
        HIDE_HOUR_GLASS   // Change mouse pointer
        break;
      }
      case(2):  // Solovay-Strassen
      {
        SHOW_HOUR_GLASS   // Change mouse pointer

        PrimeTest prim = PrimeTest(strBigNum.GetBuffer(strBigNum.GetLength()+1));
        // Call Solovay-Strassen with required accuracy
        res = prim.solovay_strassen("99.999999999999999");
        
        HIDE_HOUR_GLASS   // Change mouse pointer
        break;
      }
      case(3):  // AKS
      {
        // Set number to AKS 
        primAKS = PrimeTestAKS(strBigNum.GetBuffer(strBigNum.GetLength()+1));

		    MSG AKSMessage;
		    UINT MessageID;

        // Define message to cancel AKS
        MessageID = RegisterWindowMessage("AKS_Terminate");

        // Start dialogue and show window befor start of thread
        dlgRun = new CDlgPrimeTestRunning;
        dlgRun->SetMessageParam(MessageID);
        dlgRun->ShowWindow(SW_SHOWNORMAL);
        
        // Start AKS in seperate Thread
        CWinThread* pThread = AfxBeginThread(singleThreadAKS, this, THREAD_PRIORITY_NORMAL);
        
        // wait for cancel or result of aks
        while(1)
        {
          // Check if AKS hasn't finished already
          if(primAKS.stopProcessing != 1)
          {
            dlgRun->EndDialog(IDCANCEL);
          }

					if (PeekMessage(&AKSMessage, NULL, 0, 0, PM_NOREMOVE))
					{
						GetMessage(&AKSMessage, NULL, 0, 0);
						if (MessageID == AKSMessage.message)
						{
              primAKS.stopProcessing = 0;
              res = 3;
							break;	// nur wenn der Floyd-Algorithmus beendet wurde, Schleife verlassen - 
						}			// andere Messages werden ignoriert

						TranslateMessage(&AKSMessage); 
						DispatchMessage(&AKSMessage);
					}

					else WaitMessage();
        }
                
        // end wait 
        break;
      }
      default:
        // No provided algorithm has been chosen
        res = 5;
      break;
    }

#ifdef PRIMETEST_TIME_MEASUREMENT
    // ----------------------------------
    // Determine time duration of algo
    time2 = clock();
    test_time = ((double)time2 - (double)time1)/1000;
    
    // Set duration to member field 
    algoTime = test_time;

    // Prepare text output of time in edit field
    CString strTime;
    strTime.Format("(time2[%i]-time1[%i])=testtime[%f] ",
                    time2,
                    time1,
                    test_time);

    strBigNum = strTime + strBigNum;
    // ----------------------------------
#endif

    UpdateResultField(res, strBigNum);
  }
}

// Updates result field
void CDlgPrimeTest::UpdateResultField(int result, CString text)
{
  //UpdateData(true);
  CString strResult = "";

  // by default, disable button "jump to factorization"
  this->m_control_buttonJumpToFactorization.EnableWindow(false);

#ifdef PRIMETEST_TIME_MEASUREMENT
  // ----------------------------------
  // Output time required by algo
  strResult.Format("(%f seconds) ",algoTime);
  // ----------------------------------
#endif

  switch(result)
  {
    case(0):    // nicht prim
        LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIMETEST_RESULT_NOTPRIME,pc_str,STR_LAENGE_STRING_TABLE);
        strResult += pc_str;
        strResult += text;
        
        // Show not prime image
        m_picNotPrime.ShowWindow(TRUE);
        m_picPrime.ShowWindow(FALSE);
        
        // enable button "jump to factorization"
        this->m_control_buttonJumpToFactorization.EnableWindow(true);
    break;
    case(1):    // prim
        LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIMETEST_RESULT_PRIME,pc_str,STR_LAENGE_STRING_TABLE);
        strResult += pc_str;
        strResult += text;

        // Show prime image
        m_picPrime.ShowWindow(TRUE);
        m_picNotPrime.ShowWindow(FALSE);
        //strResult.Format("(%i) ist eine Primzahl",m_algo);
    break;
    case(2):    // vermutlich
        LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIMETEST_RESULT_PROBABLEPRIME,pc_str,STR_LAENGE_STRING_TABLE);
        strResult += pc_str;
        strResult += text;

        // Show prime image
        m_picPrime.ShowWindow(TRUE);
        m_picNotPrime.ShowWindow(FALSE);
        //strResult.Format("(%i) ist wahrscheinlich prim",m_algo);
    break;
    case(3):    // cancel
        LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIMETEST_RESULT_CANCEL,pc_str,STR_LAENGE_STRING_TABLE);
        strResult = pc_str;
        //strResult.Format("(%i) test abgebrochen",m_algo);
        
        // hide result pictures
        m_picNotPrime.ShowWindow(FALSE);
        m_picPrime.ShowWindow(FALSE);
    break;
    default:    // error
        LoadString(AfxGetInstanceHandle(),IDS_STRING_PRIMETEST_RESULT_ERROR,pc_str,STR_LAENGE_STRING_TABLE);
        strResult = pc_str;
        //strResult.Format("fehler bei der Verarbeitung");
        
        // hide result pictures
        m_picNotPrime.ShowWindow(FALSE);
        m_picPrime.ShowWindow(FALSE);
    break;
  }

  SetDlgItemText(IDC_PRIMETEST_EDIT_RESULT, strResult);
  //UpdateData(false);
}

void CDlgPrimeTest::OnBnClickedPrimetestButtonCancel()
{
  UpdateData(true);
	CDialog::OnCancel();
	UpdateData(false);
}

void CDlgPrimeTest::OnBnClickedPrimetestButtonLoadnumber()
{
  // TODO: F�gen Sie hier Ihren Kontrollbehandlungscode f�r die Benachrichtigung ein.
	//SEQUENCE_OF_Extension *thisextension = NULL;
	CFile file;	
  char *buffer = 0;
  CFileException e;

	// pop up file selector box
	CFileDialog Dlg(TRUE, ".*", NULL, OFN_HIDEREADONLY,"All Files (*.*)|*.*||", this);
	
  if(IDCANCEL == Dlg.DoModal())
  {
    return;
  }

  // Get path name to prime number file
  CString p_file = Dlg.GetPathName();
  
  try {

    // read input file
    if(!file.Open(p_file,CFile::modeRead | CFile::typeBinary, &e )) 
    {
      // Unable to open file
      Message(IDS_STRING_FILEOPENERROR, MB_ICONEXCLAMATION);
	    return;
    }

	  ASSERT(file.GetLength() < ULONG_MAX);
	  unsigned long fileLength = (unsigned long)file.GetLength();
  	
    // Create buffer
	  buffer = (char *) calloc(fileLength + 1,sizeof(char));
	  if (!buffer) 
    {
      Message(AFX_IDP_FAILED_MEMORY_ALLOC, MB_ICONEXCLAMATION);
		  return;
	  }

	  // load Sourcedata
    file.Read(buffer, fileLength);
    file.Close();

    // Save sourcedata in string and remove whitespaces
    CString str = buffer;
    str.Remove('\n');
    str.Remove(0x0d);
    str.Remove(0x20);
    free(buffer);
    
    UpdateData(true);
    SetDlgItemText(IDC_PRIMETEST_EDIT_NUMBER, str);
    UpdateData(false);

  } catch (CFileException *e) 
  {
    e->Delete();
		if (buffer)	free(buffer);
 		return;
	}
}

void CDlgPrimeTest::OnBnClickedAlgo()
{
  UpdateData(true);

  // Clear result field
  SetDlgItemText(IDC_PRIMETEST_EDIT_RESULT, "");
  
  // hide result pictures
  m_picNotPrime.ShowWindow(FALSE);
  m_picPrime.ShowWindow(FALSE);

	UpdateData(false);
}

BOOL CDlgPrimeTest::OnInitDialog()
{
  CDialog::OnInitDialog();

  //m_Result.SetReadOnly(TRUE); // Doesn't look good with gray background!

  return TRUE;  // return TRUE unless you set the focus to a control
  // AUSNAHME: OCX-Eigenschaftenseite muss FALSE zur�ckgeben.
}

void CDlgPrimeTest::OnEnChangePrimetestEditNumber()
{
  // TODO:  Falls dies ein RICHEDIT-Steuerelement ist, wird das Kontrollelement
  // diese Benachrichtigung nicht senden, es sei denn, Sie setzen den CDialog::OnInitDialog() au�er Kraft.
  // Funktion und Aufruf CRichEditCtrl().SetEventMask()
  // mit dem ENM_CHANGE-Flag ORed in der Eingabe.

  UpdateData(true);

  // Clear result field
  SetDlgItemText(IDC_PRIMETEST_EDIT_RESULT, "");

  // disable button "jump to factorization"
  this->m_control_buttonJumpToFactorization.EnableWindow(false);

  // Hide result fields
  m_picPrime.ShowWindow(FALSE);
  m_picNotPrime.ShowWindow(FALSE);

  UpdateData(false);
}

void CDlgPrimeTest::OnBnClickedPrimetestRadio()
{
  UpdateData(true);

  // Clear result field
  SetDlgItemText(IDC_PRIMETEST_EDIT_RESULT, "");

  // hide result pictures
  m_picNotPrime.ShowWindow(FALSE);
  m_picPrime.ShowWindow(FALSE);

	UpdateData(false);
}

void CDlgPrimeTest::OnBnClickedButtonJumpToFactorization()
{
  // show factorization demo dialog with the current number
  CDlgFactorisationDemo dlg;
  dlg.m_CompositeNoStr = this->m_editNumber;
  AfxInitRichEdit();
  dlg.DoModal();
}