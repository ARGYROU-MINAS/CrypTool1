// ---------------------------------------------------------------------------
// Name:      actITokenBlockCipherKey.h
// Product:   cv act library
// Purpose:   The interface ITokenBlockCipherKey enables access to a key stored 
//			  on a secure token.
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  05/15/2008
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenBlockCipherKey_h
#define ACT_ITokenBlockCipherKey_h

#include "actTokenBase.h"

#include "actIBlockCipherKey.h"

#include "actITokenAuthOwner.h"
#include "actITokenFileOwner.h"
#include "actITokenBlockCipher.h"

namespace act
{
	class IToken;
	class ITokenConfig;

	//
	// ITokenBlockCipherKey
	class ITokenBlockCipherKey 
		: public IBlockCipherKey
		, public ITokenAuthOwner
		, public ITokenFileOwner
	{
	public:
		virtual ITokenBlockCipherKey* Clone() const = 0;

		virtual ITokenBlockCipher* GetCipher() = 0;
		virtual const ITokenBlockCipher* GetCipher() const = 0;

		virtual KeyType GetType() const = 0;
		virtual IToken* GetToken() const = 0;
		virtual const char* GetName() const = 0;
		virtual void Configure(ITokenConfig* tkcfg) = 0;

		virtual void SetRawKey(const Blob& raw_key) = 0;
		virtual void GetRawKey(Blob& raw_key) const = 0;

		virtual void SetMode(const char* modename) = 0;
		virtual void SetPadding(const char* padname) = 0;
	};

} // namespace act

#endif // ACT_ITokenBlockCipherKey_h
