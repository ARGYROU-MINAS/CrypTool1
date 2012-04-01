// ---------------------------------------------------------------------------
// Name:		actIParam.h
// Product:		cv act library
// Purpose:		Declares act::IParam interface.
//            
// Copyright:	(c) 2006 cv cryptovision GmbH 
//              all rights reserved.
// Licence:		The conditions for the use of this software are regulated 
//				in the cv act library licence agreement.
//
// Autor:		Markus Tesche (MTE)
// Date:		3/1/2006
// ---------------------------------------------------------------------------

#ifndef ACT_IParam_h
#define ACT_IParam_h

#include "actBasics.h"

#if !defined(ACT_WIN32)
#	include <inttypes.h>
#endif

namespace act 
{
	class Blob;

	enum
	{
		PARAM_ANY				= -3,
		PARAM_UNKNOWN_SIZE		= -2,
		PARAM_INVALID_VALUE		= -1,
		PARAM_NULLPTR			=  0,
		PARAM_FALSE				=  0,
		PARAM_TRUE				=  1
	};

	static inline int param_bool(bool value)
	{
		return value ? PARAM_TRUE : PARAM_FALSE;
	}

	template<typename PointerT>
	inline PointerT param_intptr_to(intptr_t value)
	{
		return reinterpret_cast<PointerT>(0) + value;
	}

	template<typename PointerT>
	inline intptr_t param_to_intptr(PointerT value)
	{
		return intptr_t(value);
	}

	//
	// IParam
	class IParam
	{
	public:
		virtual ~IParam() { }

		virtual void SetParam(paramid_t id, int value) = 0;
		virtual void SetParam(paramid_t id, const char* value) = 0;
		virtual void SetParam(paramid_t id, const Blob& value) = 0;

		//
		// Get value for id, otherwise PARAM_INVALID_VALUE.
		// NOTE: May throws an act::Exception derived exception.
		virtual int GetParam(paramid_t id) const = 0;

		//
		// Get value for id, returns size[PARAM_UNKNOWN_SIZE|0-n] or PARAM_INVALID_VALUE.
		// NOTE: May throws an act::Exception derived exception.
		virtual size_t GetParam(paramid_t id, const char** value) const = 0;

		//
		// Get value for id, returns size[PARAM_UNKNOWN_SIZE|0-n] or PARAM_INVALID_VALUE.
		// NOTE: May throws an act::Exception derived exception.
		virtual size_t GetParam(paramid_t id, Blob& value) const = 0;
	};

} // namespace act

#endif // ACT_IParam_h
