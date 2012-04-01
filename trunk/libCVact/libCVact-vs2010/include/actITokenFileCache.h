// ---------------------------------------------------------------------------
// Name:		actITokenFileCache.h
// Product:		cv act library
// Purpose:		Interface used for FID based binary cache.
//            
// Copyright:	(c) 2008 cv cryptovision GmbH 
//              all rights reserved.
// Licence:		The conditions for the use of this software are regulated 
//				in the cv act library licence agreement.
//
// Autor:		Markus Tesche
// Date:		11/07/2008
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenFileCache_h
#define ACT_ITokenFileCache_h

#include "actIRefCounted.h"

#include <map>

namespace act
{
	class Blob;
	class IToken;

	//
	// ITokenFileCache
	class ITokenFileCache : public IRefCounted
	{
	protected:
		typedef std::map<Blob, Blob> CacheMap;

	public:
		virtual bool InitCache(IToken* token) = 0;
		virtual Blob GetCache(const Blob& filepath) const = 0;
		virtual void PutCache(const Blob& filepath, const Blob& memory) const = 0;
	};

} // namespace act

#endif // ACT_ITokenFileCache_h
