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
#include "assert.h"
#include "CrypToolApp.h"
#include "CrypToolTools.h"
#include "Cryptography.h"
#include "KeyRepository.h"
#include "SquareMatrixModN.h"
#include "KeyHillBase.h"
#include "DlgKeyHill5x5.h"
#include "DlgKeyHill10x10.h"
#include "DlgShowKeyHill5x5.h"
#include "DlgShowKeyHill10x10.h"

/////////////////////////////////////////////////////////////////////////////
//
CKeyHillBase::CKeyHillBase(unsigned long p_keyRange) :
   HillMat(0), 
	max_dim(p_keyRange),
   key_range(p_keyRange),
	dim(1),
	matType(HILL_CHAR_MATRIX), 
	multType(VECTOR_MATRIX),
	cryptMode(0),
   currentDialog(0),
   currDlg( DLG_HILL_5x5 )
{
	HillNumMat  = new CHiEdit*[key_range];
	HillAlphMat = new CEdit*  [key_range];
	for ( unsigned long i=0; i<key_range; i++ )
	{
		HillNumMat[i]  = new CHiEdit[key_range];
		HillAlphMat[i] = new CEdit[key_range];
	}
}

CKeyHillBase::~CKeyHillBase()
{
	for ( unsigned long i=0; i<key_range; i++ )
	{
		delete []HillNumMat[i];
		delete []HillAlphMat[i];
	}
	delete []HillNumMat;
	delete []HillAlphMat;
   delete HillMat;
}

///////////////////////////////////////////////////
// MATRIX EDIT I/O
///////////////////////////////////////////////////
void CKeyHillBase::SetHillMatrix( CSquareMatrixModN *mat )
{
	unsigned long i, j;
	CString cs;

	for ( i=0; i<max_dim; i++ )
		for ( j=0; j<max_dim; j++ )
			if ( i<dim && j<dim )
         { 
            char c = chr((*mat)(i,j));
            if ( c >= 0 )
            {
				   HillAlphMat[i][j].SetWindowTextA( CString(c) );
				   cs.Format( "%02d", (*mat)(i,j) + HillOptions.m_alphabetOffset );
				   HillNumMat[i][j].SetWindowTextA( cs );
            }
            else // ERROR
               HillNumMat[i][j].SetWindowTextA( _T("") );
			}
			else
			{
				HillAlphMat[i][j].SetWindowTextA( _T("") );
				HillNumMat[i][j].SetWindowTextA(_T(""));
			}
}

CSquareMatrixModN* CKeyHillBase::GetHillMatrix()
{
   CSquareMatrixModN * mat;

	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM));
	unsigned long modul = theApp.TextOptions.getAlphabet().GetLength();

   mat = new CSquareMatrixModN( dim, modul );
	CString cs;
	unsigned long i, j;
	for (i=0; i<dim; i++)
		for (j=0; j<dim; j++)
		{
			HillAlphMat[i][j].GetWindowText(cs);
			ASSERT( 0 >= ord( cs[0] ) );
         (*mat)(i,j) = ord(cs[0]);
		}
   return mat;
}

////////////////////////////////////////////
// NUMBER MATRIX OUTPUT
////////////////////////////////////////////
int CKeyHillBase::ord( const char ch )
{
   int modul = theApp.TextOptions.getAlphabet().GetLength();
	for(int i=0;i<modul;i++)
		if( theApp.TextOptions.getAlphabet()[i] == ch ) return (i + HillOptions.m_alphabetOffset) % modul;

	return -1;
}

char CKeyHillBase::chr( int u )
{
   int modul = theApp.TextOptions.getAlphabet().GetLength();
   if ( u < 0 || u >= modul )
      return -1; // ERROR

   if ( u < (int)HillOptions.m_alphabetOffset ) 
      u = u + modul - HillOptions.m_alphabetOffset;
   else
      u = u + HillOptions.m_alphabetOffset;
   return theApp.TextOptions.getAlphabet()[u];
}

void CKeyHillBase::syncAlphNum( unsigned long i, unsigned long j )
{
	if( matType == HILL_CHAR_MATRIX )
	{
		CString cs;
		HillAlphMat[i][j].GetWindowText(cs);

		// QUICK FIX: if user supplied MORE THAN ON CHARACTER, for example by using 
		// the copy/paste mechanism, throw away all characters except the first one
		if(cs.GetLength() > 1) {
			cs.Delete(1, cs.GetLength() - 1);
		}

		if (cs.GetLength() == 1 )
		{
			if ( ord(cs[0]) >= 0 )
			{
				CString str;
				str.Format("%02d", ord(cs[0]) );
				HillNumMat[i][j].SetWindowText(str);
				currentDialog->NextDlgCtrl();
			}
			else if ( theApp.TextOptions.getIgnoreCase() 
				      && MyIsLower(cs[0]) &&  ord(MyToUpper(cs[0])) >= 0 )
			{
				cs.SetAt(0,MyToUpper(cs[0]));
   			HillAlphMat[i][j].SetWindowText( cs );
			}
			else
			{
				cs.Empty();
			}
		}
	}
}

void CKeyHillBase::syncAlphNum ()
{
   unsigned long i, j, err = 0, o;
   CString cs;

   for ( i=0; i<dim; i++ )
      for ( j=0; j<dim; j++ )
      {
         HillAlphMat[i][j].GetWindowTextA( cs );
         if ( cs.GetLength() == 1 )
         {
            if ( theApp.TextOptions.getIgnoreCase() &&
				     MyIsLower(cs[0]) &&  ord(MyToUpper(cs[0])) >= 0 )
			   {
				   cs.SetAt(0,MyToUpper(cs[0]));
   			   HillAlphMat[i][j].SetWindowText( cs );
			   }

            o = ord( cs[0] );
            if ( o >= 0 )
               cs.Format( "%02d", o );
            HillNumMat[i][j].SetWindowTextA( cs );

         }
         else
            err++;
         if ( err )
            HillAlphMat[i][j].SetWindowTextA(_T(""));
      }  
}

void CKeyHillBase::formatNum( unsigned long i, unsigned long j )
{
	CString cs;
	HillNumMat[i][j].GetWindowText(cs);
	if(cs.GetLength() == 1)
	{
		int ord = _ttoi(cs);
		if( ord < (int)HillOptions.m_alphabetOffset || ord > theApp.TextOptions.getAlphabet().GetLength() + (int)HillOptions.m_alphabetOffset )
		{
			cs.Empty();
			HillNumMat[i][j].SetWindowText(cs);
		}
		else
		{
			cs.Insert(0,"0");
			HillNumMat[i][j].SetWindowText(cs);
		}
		currentDialog->PrevDlgCtrl(); //because Tab and UpdateFeld makes both NextDlgCtrl
	}
}

////////////////////////////////////////////
// CHARACTER MATRIX OUTPUT
////////////////////////////////////////////
void CKeyHillBase::syncNumAlph( unsigned long i, unsigned long j )
{
	if( matType == HILL_NUM_MATRIX )
	{
		CString cs;
		HillNumMat[i][j].GetWindowText(cs);

		if(cs.GetLength() == 2)
		{
         char c = chr( _ttoi(cs) );
			if( c < 0 )
				HillNumMat[i][j].SetWindowText(_T(""));
			else
			{
				HillAlphMat[i][j].SetWindowText( CString(c) ); 
				currentDialog->NextDlgCtrl();
			}
		}
	}
}

int CKeyHillBase::validEntries()
{
	ASSERT ((1 <= dim) && (dim <= HILL_MAX_DIM));

	unsigned long i, j;
	CString cs;
	for (i=0; i<dim; i++)
		for (j=0; j<dim; j++)
		{
			HillAlphMat[i][j].GetWindowText(cs);
			if ( (cs.GetLength() != 1) || 0 > ord(cs[0]) )
			{
				CString msg;
				msg.LoadStringA( IDS_HILL_BAD_KEY_NONVALID_CHAR );
				cs.LoadStringA ( IDS_STRING_ASYMKEY_ERR_INPUT_UNCOMPLETED );
            currentDialog->MessageBoxA(msg, cs, MB_ICONWARNING|MB_OK);
				return FALSE;
			}
		}

	return TRUE;
}

////////////////////////////////////////
// MATRIX ENTRY VALIDATION
////////////////////////////////////////
int  CKeyHillBase::isInvertable()
{
	if ( !validEntries() )
		return 0;

	unsigned long modul = theApp.TextOptions.getAlphabet().GetLength();
	CSquareMatrixModN *mat, *mat_inv;

	mat		= new CSquareMatrixModN( dim, modul );
	mat_inv	= new CSquareMatrixModN( dim, modul );

	SetHillMatrix( mat );

	int invertable = mat->invert(mat_inv);
	if ( !invertable )
	{
		CString msg, cs;
		cs.Format( "%dx%d", dim, dim );
		msg.Format( IDS_HILL_BAD_KEY_INV, cs, modul);
		cs.LoadStringA( IDS_HILL_BAD_KEY );
		currentDialog->MessageBoxA(msg, cs, MB_ICONWARNING|MB_OK);
	}

	delete mat;
	delete mat_inv;

	return invertable;
}

void CKeyHillBase::randomKey()
{
	CSquareMatrixModN mat( dim, theApp.TextOptions.getAlphabet().GetLength() );
	if (mat.zufaellige_invertierbare_matrix())
	{
		SetHillMatrix( &mat );
	}
	else
	{
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ERR_ON_WRONG_ALPHABET,pc_str,STR_LAENGE_STRING_TABLE);
		currentDialog->MessageBoxA(pc_str, NULL, MB_ICONERROR|MB_OK);
	}
}

////////////////////////////////////////////////////
// DIALOG CONTROL FUNCTIONS
////////////////////////////////////////////////////
void CKeyHillBase::activateMatrix  ( CEdit **mat )
{
	unsigned long i, j;
	for ( i=0; i<dim; i++ )
		for ( j=0; j<dim; j++ )
			mat[i][j].EnableWindow( TRUE );
}

void CKeyHillBase::deactivateMatrix( CEdit **mat )
{
	unsigned long i, j;
	for ( i=0; i<max_dim; i++ )
		for ( j=0; j<max_dim; j++ )
			mat[i][j].EnableWindow( FALSE );
}

void CKeyHillBase::selectActMatrix ()
{
	deactivateMatrix( (CEdit**)HillNumMat );
	deactivateMatrix( HillAlphMat );
	if ( matType == HILL_CHAR_MATRIX ) // Alphabet
	{
		 activateMatrix( HillAlphMat );
		 HillAlphMat[0][0].SetFocus();
		 HillAlphMat[0][0].SetSel(0, -1);
	}
	else
	{
		 activateMatrix( (CEdit**)HillNumMat );
		 HillNumMat[0][0].SetFocus();
		 HillNumMat[0][0].SetSel(0, -1);
	}
}

void CKeyHillBase::selectHillDimension( unsigned long new_dim )
{
	assert( 1 <= new_dim && new_dim <= max_dim );
	dim = new_dim;
	selectActMatrix();
}

void CKeyHillBase::selectMatType( HillEditType new_type )
{
	matType = new_type;
	selectActMatrix();
}

void CKeyHillBase::selectMultType( HillMultType new_type )
{
	multType = new_type;
}

void CKeyHillBase::setMatFont()
{
	CFont cf;
	cf.CreatePointFont( 80, "Courier" );
	unsigned long i, j;
	for ( i=0; i<max_dim; i++)
	{
		for ( j=0; j<max_dim; j++)
		{
			HillAlphMat[i][j].SetFont(&cf);
			HillNumMat[i][j].SetFont(&cf);
		}
	}
}

/////////////////////////////////////////////////
// COPY / PASTE KEY
/////////////////////////////////////////////////
void CKeyHillBase::pasteKey()
{
	CString cs;
	LoadString(AfxGetInstanceHandle(),IDS_CRYPT_HILL,pc_str,STR_LAENGE_STRING_TABLE);

	if ( PasteKey(pc_str,cs) )
	{
		int l = 0, laenge = cs.Find(HILLSTR_ALPHABETOFFSET);
		unsigned long i = 0, j, _dim = 0;

		while (l<laenge) if ( 0 <= ord( cs[l++] ) ) i++;
		if ( i <= max_dim*max_dim )
		{	
			i = j = l = 0;
 			while (l < laenge)
 			{
				if ( 0 <= ord(cs[l]) )
					HillAlphMat[i][j++].SetWindowTextA( CString(cs[l]) );
				else 
				{
					assert( i < _dim );			// FIXME
					assert( cs[l] == '\n' );	// FIXME 
					if ( _dim > 0 ) 
					{
						if ( _dim != j )
							assert( 0 );		// FIXME 
					}
					else
					{
						if ( j > max_dim )
							assert( 0 );		// FIXME 
						_dim = j;
					}
					i++;
					j = 0;
				}
				l++;
 			}
			dim = _dim;

			laenge += strlen(HILLSTR_ALPHABETOFFSET) +1;
			HillOptions.m_alphabetOffset = unsigned long(cs.GetAt(laenge) - '0');
			laenge = cs.Find(HILLSTR_MULTVARIANT);
			ASSERT(laenge > 0);
			laenge += strlen(HILLSTR_MULTVARIANT) +1;
			multType = (cs.GetAt(laenge) == '0') ? VECTOR_MATRIX : MATRIX_VECTOR;

         syncAlphNum();
		}
 		else
		{  
			// FIXME -- Message ... the stored Hill Key ...
		}
	}
}

void CKeyHillBase::copyKey()
{

}

////////////////////////////////////////////////////
// READ / WRITE REGISTRY
////////////////////////////////////////////////////
void CKeyHillBase::readRegistry()
{
	unsigned long _matType  = (unsigned long)HILL_CHAR_MATRIX;
   unsigned long _verbose  = FALSE;
   unsigned long _multType = (unsigned long)VECTOR_MATRIX;
	if(CT_OPEN_REGISTRY_SETTINGS(KEY_ALL_ACCESS, IDS_REGISTRY_SETTINGS, "Hill") == ERROR_SUCCESS)
	{
		CT_READ_REGISTRY_DEFAULT( _matType,  "EditKeyChrMatrix", _matType);   matType  = (HillEditType)_matType;
      CT_READ_REGISTRY_DEFAULT( dim,       "MatrixDimension" , 2 );     
      CT_READ_REGISTRY_DEFAULT( _verbose,  "ShowExample"     , _verbose);   verbose  = BOOL(_verbose );
      CT_READ_REGISTRY_DEFAULT( _multType, "MultType"        , _multType ); multType = (HillMultType)_multType; 
      CT_CLOSE_REGISTRY();
	}
   HillOptions.readRegistry();
}

void CKeyHillBase::writeRegistry()
{
	if ( CT_OPEN_REGISTRY_SETTINGS( KEY_WRITE, IDS_REGISTRY_SETTINGS, "Hill" ) == ERROR_SUCCESS )
	{
		CT_WRITE_REGISTRY( unsigned long(matType),  "EditKeyChrMatrix" );
      CT_WRITE_REGISTRY( dim,                     "MatrixDimension" );
      CT_WRITE_REGISTRY( unsigned long(verbose),  "ShowExample" );
      CT_WRITE_REGISTRY( unsigned long(multType), "MultType" );
		CT_CLOSE_REGISTRY();
	}
   HillOptions.writeRegistry();
}

/////////////////////////////////////////////
// RUN THE RESP HILL DIALOG
/////////////////////////////////////////////
int CKeyHillBase::run( )
{
   CDlgKeyHill5x5    dlgKeyHill5x5;
   CDlgKeyHill10x10  dlgKeyHill10x10;

   dlgKeyHill5x5.init  ( this );
   dlgKeyHill10x10.init( this );

   assert( key_range >= DLG_HILL_10x10 );

   readRegistry();
   if ( dim > 5 ) currDlg = DLG_HILL_10x10;
   else           currDlg = DLG_HILL_5x5;

   while ( currDlg > 1 )
   {
      if ( currDlg == DLG_HILL_5x5 ) 
      {
         max_dim = DIM_DLG_HILL_5x5;
         if ( dim > max_dim ) dim = max_dim;
         currentDialog = &dlgKeyHill5x5;
      }
      else
      {
         max_dim = DIM_DLG_HILL_10x10;
         if ( dim > max_dim ) dim = max_dim;
         currentDialog = &dlgKeyHill10x10;
      }
      if ( IDOK != currentDialog->DoModal() )
         return IDCANCEL;
   }

   return IDOK;
}

int CKeyHillBase::run_showKey( CString &keyStr )
{

   return IDCANCEL;
}

int CKeyHillBase::run_showKey( CSquareMatrixModN *mat, int alphabet_offset, int mult_direction )
{

   return IDCANCEL;
}

//////////////////////////////////////////////////////////////////////////////
// CHiEdit
//////////////////////////////////////////////////////////////////////////////


BEGIN_MESSAGE_MAP(CHiEdit, CEdit)
	//{{AFX_MSG_MAP(CHiEdit)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CHiEdit::OnLButtonUp(UINT nFlags, CPoint point )
{
	CEdit::OnLButtonUp(nFlags,point);
	SetSel(0, -1);
}

