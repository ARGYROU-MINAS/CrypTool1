// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "Trapezeditor.h"

/////////////////////////////////////////////////////////////////////////////
// CTrapezEditor

IMPLEMENT_DYNCREATE(CTrapezEditor, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CTrapezEditor properties

BOOL CTrapezEditor::GetDisplayColorTable()
{
	BOOL result;
	GetProperty(0x1, VT_BOOL, (void*)&result);
	return result;
}

void CTrapezEditor::SetDisplayColorTable(BOOL propVal)
{
	SetProperty(0x1, VT_BOOL, propVal);
}

LPUNKNOWN CTrapezEditor::GetColortable()
{
	LPUNKNOWN result;
	GetProperty(0x4, VT_UNKNOWN, (void*)&result);
	return result;
}

void CTrapezEditor::SetColortable(LPUNKNOWN propVal)
{
	SetProperty(0x4, VT_UNKNOWN, propVal);
}

long CTrapezEditor::GetResolution()
{
	long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}

void CTrapezEditor::SetResolution(long propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}

float CTrapezEditor::GetHistScale()
{
	float result;
	GetProperty(0x2, VT_R4, (void*)&result);
	return result;
}

void CTrapezEditor::SetHistScale(float propVal)
{
	SetProperty(0x2, VT_R4, propVal);
}

LPUNKNOWN CTrapezEditor::GetHistogram()
{
	LPUNKNOWN result;
	GetProperty(0x6, VT_UNKNOWN, (void*)&result);
	return result;
}

void CTrapezEditor::SetHistogram(LPUNKNOWN propVal)
{
	SetProperty(0x6, VT_UNKNOWN, propVal);
}

short CTrapezEditor::GetDrawstyle()
{
	short result;
	GetProperty(0x7, VT_I2, (void*)&result);
	return result;
}

void CTrapezEditor::SetDrawstyle(short propVal)
{
	SetProperty(0x7, VT_I2, propVal);
}

BOOL CTrapezEditor::GetDisplayHistogram()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void CTrapezEditor::SetDisplayHistogram(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CTrapezEditor operations