// ---------------------------------------------------------------------------
// Name:      actISlot.h
// Product:   cv act library
// Purpose:   The class ISlot manages the Tokens
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/26/2002
// ---------------------------------------------------------------------------

#ifndef ACT_ISlot_h
#define ACT_ISlot_h

#include "actMode.h"
#include "actBasics.h"
#include "actBlob.h"

#include "actIRefCounted.h"
#include "actISynchronize.h"
#include "actIEventMonitoring.h"

namespace act
{
	class IToken;
	class ITokenConfig;
	class ISCardOS;
	class ISCardAccess;
	class ISubsystem;
	class ISlot;

	// ---------------------------------------------------------------------------
	enum slot_paramid_t
	{
		SLOT_PARAM_BEGIN		= 0,
		SLOT_PARAM_END			= SLOT_RANGE_SIZE,
		// Parameter
		SLOT_PARAM_FEATURE		= SLOT_PARAM_BEGIN,
		// RFU					: 1 - 7
		// Custom				: 7 - 15
	};

	//
	// ISlot
	// ---------------------------------------------------------------------------
	class ISlot
		: public IRefCounted
		, public ISynchronize
		, public IEventMonitoring
	{
	protected:
		virtual ~ISlot() { }

	public:
		virtual ISlot*			Clone() const = 0;

		virtual Blob			GetATR() const = 0;
		virtual const char*		GetName() const = 0;
		virtual ISubsystem*		GetSystem() const = 0;
		virtual const char*		GetReaderName() const = 0;
		virtual Blob			GetHistoricalBytes() const = 0;

		virtual bool			IsTokenPresent() const = 0;

		virtual IToken*			CreateToken(ISCardOS* os = 0) = 0;
		virtual IToken*			CreateToken(ISCardOS* os) const = 0;

		virtual ISCardOS*		CreateOS(const Blob& historical_bytes = Blob()) = 0;
		virtual ISCardOS*		CreateOS(ISCardAccess* ac, const Blob& historical_bytes = Blob()) const = 0;

		virtual ISCardAccess*	CreateAccess() = 0;

		virtual void			SetTokenConfig(ITokenConfig* tkcfg) = 0;

		virtual bool			HasSecurePinEntry(ISCardAccess* ac = 0) const = 0;
		virtual bool			HasSecurePinChange(ISCardAccess* ac = 0) const = 0;

		virtual void			SetParam(paramid_t id, int val) = 0;
		virtual int				GetParam(paramid_t id) const = 0;

		static paramid_t		Param(slot_paramid_t id, int slot);
		static paramid_t		Param(slot_paramid_t id, const ISlot* slot);
	};

	// ---------------------------------------------------------------------------
	struct ATRCardInfo
	{
		const char* name;
		const char* atr;
		const char* atr_mask;
	};

	// ---------------------------------------------------------------------------
	void				InitCardInfoMap(const ATRCardInfo* mapCardInfo);
	const ATRCardInfo*	GetATRCardInfo(const Blob& atr);
	const char*			GetOSName(const Blob& atr);
	Blob				GetHistoricalBytes(const Blob& atr);
	size_t				GetHistoricalBytes(const Blob& atr, Blob& historical_bytes);
	bool				GetATRStructInfo(const Blob& atr, size_t& his_pos, size_t& his_len, bool& has_tck);

} // namespace act

#endif	// ACT_ISlot_h
