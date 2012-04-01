// ---------------------------------------------------------------------------
// Name:      actITokenAuthOwner.h
// Product:   cv act library
// Purpose:   The ITokenAuthOwner interface is used by objects which requires
//			  authentication like token keys.
//            
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  08/10/2008
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenAuthOwner_h
#define ACT_ITokenAuthOwner_h

namespace act
{
	class ITokenPIN;
	class IAuthIdRef;

	//
	// ITokenAuthOwner
	class ITokenAuthOwner
	{
	public:
		virtual void SetPin(ITokenPIN* pin) = 0;
		virtual ITokenPIN* GetPin() const = 0;
		virtual IAuthIdRef* GetAuthIdRef() const = 0;

	protected:
		virtual ~ITokenAuthOwner() { }
	};

} // namespace act

#endif	// ACT_ITokenAuthOwner_h
