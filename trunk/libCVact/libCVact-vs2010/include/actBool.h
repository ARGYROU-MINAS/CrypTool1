// ---------------------------------------------------------------------------
// Name:      actBool.h
// Product:   cv act library
// Purpose:   Simple boolean which supports not initialized.
//
// Copyright: (c) 2012 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  03/19/2012
// ---------------------------------------------------------------------------

#ifndef ACT_Bool_h
#define ACT_Bool_h

#include "actLocation.h"

namespace act
{
	enum BOOLean
	{
		BOOL_NOT_INITIALIZED	= -1,
		BOOL_FALSE				=  0,
		BOOL_TRUE				=  1
	};

	template<typename OnError, typename T>
	bool BOOLval(BOOLean value, const Location<T>& location)
	{
		if(BOOL_NOT_INITIALIZED == value) OnError::Throw(location, "not initialized");
		if(BOOL_TRUE == value) return true;
		return false;
	}

	template<typename OnError>
	bool BOOLval(BOOLean value)
	{
		if(BOOL_NOT_INITIALIZED == value) OnError::Throw("not initialized");
		if(BOOL_TRUE == value) return true;
		return false;
	}

	inline BOOLean BOOLval(bool value)    { return value ? BOOL_TRUE : BOOL_FALSE; }
	inline BOOLean BOOLval(BOOLean value) { return value; }

} // namspace act

#endif // ACT_Bool_h
