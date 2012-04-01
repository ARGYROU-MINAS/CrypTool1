// ---------------------------------------------------------------------------
// Name:		actIRefCounted.h
// Product:		cv act library
// Purpose:		The IRefCounted interface.
//            
// Copyright:	(c) 2006 cv cryptovision GmbH 
//              all rights reserved.
// Licence:		The conditions for the use of this software are regulated 
//				in the cv act library licence agreement.
//
// Autor:		Markus Tesche (MTE)
// Date:		1/18/2006
// ---------------------------------------------------------------------------

#ifndef ACT_IRefCounted_h
#define ACT_IRefCounted_h

namespace act
{
	//
	// IRefCounted, methods for reference counting.
	class IRefCounted
	{
	public:
		virtual ~IRefCounted() { }

		virtual void AddRef() = 0;
		virtual void Release() = 0;
	};

} // namespace act

#endif	// ACT_IRefCounted_h
