// ButtonControl.cpp

#include "ButtonControl.h"

// Klasse BitmapButton
BitmapButton::BitmapButton()
{
	this->bIsActionPerformed = false;
	this->bIsActive = false;
	this->bStatusChanged = true;
}

BitmapButton::~BitmapButton()
{

}

void BitmapButton::Init(const ButtonResourceStruct res, CWnd *parent)
{
	this->ResourceID = res.Resource;

	// ROTE Ressourcen zuweisen...
	this->StatusRUP = res.BitmapName[0];
	this->StatusRDOWN = res.BitmapName[1];
	this->StatusRFOCUS = res.BitmapName[2];
	this->StatusRDISABLED = res.BitmapName[3];
	// GR�NE Ressourcen zuweisen...
	this->StatusGUP = res.BitmapName[4];
	this->StatusGDOWN = res.BitmapName[5];
	this->StatusGFOCUS = res.BitmapName[6];
	this->StatusGDISABLED = res.BitmapName[7];
	
	this->pParent = parent;
	
	this->Button.AutoLoad(this->ResourceID, this->pParent);
}

void BitmapButton::ShowBitmaps()
{
	// Je nach internem Zustand (ausgef�hrt oder nicht) gr�ne oder rote Bitmaps laden
	IsActionPerformed() ? this->Button.LoadBitmaps(StatusGUP, StatusGDOWN, StatusGFOCUS, StatusGDISABLED) : this->Button.LoadBitmaps(StatusRUP, StatusRDOWN, StatusRFOCUS, StatusRDISABLED);
	
	this->Button.ShowWindow(SW_HIDE);
	this->Button.ShowWindow(SW_SHOW);
}

// Klasse BitmapButtonControl
BitmapButtonControl::BitmapButtonControl()
{

}

BitmapButtonControl::~BitmapButtonControl()
{

}
