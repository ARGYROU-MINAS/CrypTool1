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

// ComputerList.cpp: implementation of the CComputerList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComputerList.h"
#include "ScenarioObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComputerList::CComputerList()
{
	clearList();
}

CComputerList::~CComputerList()
{

}

void CComputerList::clearList()
{
	list.RemoveAll();
}

void CComputerList::addComputer(CComputer& computer)
{
	//list.AddTail(&computer); //??? Compilerfehler
}

CComputer& CComputerList::getComputer(int i)
{
	return (CComputer&)(list.GetAt(list.FindIndex(i)));
}
