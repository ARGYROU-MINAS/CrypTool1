// ---------------------------------------------------------------------------
// Name:		actITokenConfig.h
// Product:		cv act library
// Purpose:		IToken configuration.
//
// Copyright:	(c) 2008 cv cryptovision GmbH 
//              all rights reserved.
// Licence:		The conditions for the use of this software are regulated 
//				in the cv act library licence agreement.
//
// Autor:		Markus Tesche
// Date:		11/07/2008
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenConfig_h
#define ACT_ITokenConfig_h

#include "actIParam.h"
#include "actIRefCounted.h"

namespace act
{
	class ISlot;
	class ISCardOS;
	class ISCardAccess;

	class IToken;
	class ITokenPIN;
	class ITokenAuth;
	class ITokenKey;
	class ITokenBlockCipher;
	class ITokenBlockCipherKey;
	class ITokenFileMap;
	class ITokenFileCache;
	class ITokenDFHandler;

	//
	// ITokenConfig
	class ITokenConfig
		: public IParam
		, virtual public IRefCounted
	{
	public:
		virtual ITokenConfig* Clone() const = 0;

		// Individual card detection
		virtual bool IsSupported(ISCardOS* os) const = 0;

		// Configures supporting (non token) instances, if fails throws an Exception
		virtual void Configure(ISlot* slot) const = 0;
		virtual void Configure(ISCardAccess* access) const = 0;
		virtual void Configure(ISCardOS* os) const = 0;

		// Configures the token, if fails throws an Exception
		virtual void Configure(IToken* token) const = 0;
		virtual void Configure(ITokenPIN* auth_obj) const = 0;
		virtual void Configure(ITokenKey* key) const = 0;
		virtual void Configure(ITokenBlockCipher* cipher) const = 0;
		virtual void Configure(ITokenBlockCipherKey* key) const = 0;

		virtual const ITokenConfig& Configure(ITokenDFHandler* df_handler) const = 0;

		// Factory's for token helper objects
		virtual ITokenAuth* CreateAuth(IToken* token) = 0;
		virtual ITokenFileMap* CreateFileMap(const IToken* token) = 0;
		virtual ITokenFileCache* CreateFileCache(IToken* token) = 0;
	};

} // namespace act

#endif	// ACT_ITokenConfig_h
