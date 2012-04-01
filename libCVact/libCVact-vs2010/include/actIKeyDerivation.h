// ---------------------------------------------------------------------------
// Name:      actIKeyDerivation.h
// Product:   cv act library
// Purpose:   IKeyDerivation for general prupose
//
// Copyright: (c) 2003-2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Ulrich Birkenhauer
//			  Markus Tesche
// Date:	  07/05/2010
// ---------------------------------------------------------------------------

#ifndef ACT_IKeyDerivation_h
#define ACT_IKeyDerivation_h

#include "actMove.h"
#include "actMode.h"

#include "actIParam.h"
#include "actIRefCounted.h"

namespace act
{
	enum KDParam
	{
		KD_DATA			= SALT,
		KD_HASH			= HASH,
		KD_SERIAL		= SERIALNR,
		KD_DERIVATOR	= DERIVATOR,
		KD_MODE			= BCMODE,		// key configuration
		KD_PADDING		= PADDING,		// key configuration
	};

	enum KDMode
	{
		KD_MODE_DEFAULT = 0,
		KD_MODE_CARD_MANAGER,

		KD_MODE_LAST
	};

	class IKeyDerivation;
	class IBlockCipherKey;

	typedef void (*DerivationFunc)(IKeyDerivation* owner, const Blob& data,
		Blob& k_enc, Blob& k_mac, Blob& k_kek);

	//
	// IKeyDerivation
	class IKeyDerivation
		: public IParam
		, public IRefCounted
	{
	public:
		virtual Blob Derive(const Blob& deriveData) = 0;
		virtual void Derive(uint mode, const Blob& data, Blob& k_enc, Blob& k_mac) = 0;
		virtual void Derive(uint mode, const Blob& data, Blob& k_enc, Blob& k_mac, Blob& k_kek) = 0;

		virtual void SetKey(IBlockCipherKey* key) = 0;
		//
		// If mode already registered, it will be overwritten and the previous will be returned.
		virtual DerivationFunc Register(uint mode, DerivationFunc df) = 0;
	};

} // namespace act

#endif // ACT_IKeyDerivation_h
