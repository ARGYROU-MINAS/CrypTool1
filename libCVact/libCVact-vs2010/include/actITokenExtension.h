// ---------------------------------------------------------------------------
// Name:      actITokenExtension.h
// Product:   cv act library
// Purpose:   ITokenExtension interface provides functionality to register
//            extensions to IToken derived objects.
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  12/02/2008
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenExtension_h
#define ACT_ITokenExtension_h

#include "actIRefCounted.h"

namespace act
{
	class IToken;

	//
	// ITokenExtension
	class ITokenExtension : public IRefCounted
	{
	protected:
		virtual ~ITokenExtension() { }

	public:
		virtual void const* GetCreatePtr() const    = 0;
		virtual bool		Register(IToken* token) = 0;
	};

} // namespace act

#endif // ACT_ITokenExtension_h
