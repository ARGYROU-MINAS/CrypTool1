// ---------------------------------------------------------------------------
// Name:      actITokenBlockCipher.h
// Product:   cv act library
// Purpose:   The interface ITokenBlockCipher encapsulates operations using a
//			  symmetric key stored on a secure token.
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  05/15/2008
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenBlockCipher_h
#define ACT_ITokenBlockCipher_h

#include "actBlob.h"
#include "actIBlockCipher.h"

namespace act
{
	class IToken;
	class ITokenConfig;

	//
	// ITokenBlockCipher
	class ITokenBlockCipher : public IBlockCipher
	{
	public:
		virtual ITokenBlockCipher* Clone() const = 0;

		virtual void Configure(ITokenConfig* tkcfg) = 0;
		virtual Blob GetCipherName() const = 0;
		virtual Blob GetLabel() const = 0;

		virtual int GetKeyNumber() const = 0;

		virtual IToken* GetToken() const = 0;
	};

} // namespace act

#endif // ACT_ITokenBlockCipher_h
