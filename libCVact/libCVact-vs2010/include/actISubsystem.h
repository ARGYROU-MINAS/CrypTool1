// ---------------------------------------------------------------------------
// Name:      actISubsystem.h
// Product:   cv act library
// Purpose:   The class ISubsystem detects and manages the slots
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/26/2002
// ---------------------------------------------------------------------------

#ifndef ACT_ISubsystem_h
#define ACT_ISubsystem_h

#include "actMode.h"
#include "actBasics.h"
#include "actIRefCounted.h"
#include "actISynchronize.h"
#include "actIGlobalCache.h"
#include "actIEventMonitoring.h"

namespace act
{
	class ISlot;
	class ITokenConfig;
	class ISubsystem;
	class ISubsystemConfig;

	// ---------------------------------------------------------------------------
	enum subsystem_paramid_t
	{
		SUBSYSTEM_PARAM_BEGIN				= 0,
		SUBSYSTEM_PARAM_END					= SUBSYSTEM_RANGE_SIZE - 1,
		// Parameter
		SUBSYSTEM_READERNAME				/**< Allowed reader name. */ = SUBSYSTEM_PARAM_BEGIN,
		SUBSYSTEM_READERLIST,				//!< Double 0-terminated list of allowed reader names.
		SUBSYSTEM_SHARE_CONTEXT,			//!< Set to \ref PARAM_TRUE to share context with \ref PCSCMonitor.
		SUBSYSTEM_TRANSACTION_RETRIES,		//!< Number of retries to enter transaction.
		SUBSYSTEM_TRANSACTION_RETRY_DELAY,	//!< Milliseconds to wait for the next attempt to enter transaction.
		// RFU							: 5 - 7
		// Custom						: 8 - 15
	};

	//
	// ISubsystem
	// ---------------------------------------------------------------------------
	class ISubsystem 
		: public IRefCounted
		, public ISynchronize
		, public IGlobalCache
		, public IEventMonitoring
	{
	protected:
		virtual ~ISubsystem()		{ }

	public:
		virtual ISubsystem*			Clone() const = 0;
		virtual bool				IsValid() const = 0;
		virtual const char*			GetName() const = 0;
		virtual ISubsystemConfig*	GetConfig() const = 0;

		virtual bool				Install(size_t port) = 0;
		virtual bool				Disconnect() = 0;
		virtual void				Refresh(timeout_t timeout) = 0;
		virtual void				Refresh() = 0;

		// SlotList
		virtual int					GetSlotNumber() const = 0;
		virtual int					GetSlotId(const ISlot* slot) const = 0;
		virtual const ISlot*		GetSlot(int pos) const = 0;
		virtual ISlot*				CreateSlot(const char* name) = 0;

		virtual void				SetTokenConfig(ITokenConfig* tkcfg) = 0;

		virtual void				SetParam(subsystem_paramid_t id, intptr_t) = 0;
		virtual intptr_t			GetParam(subsystem_paramid_t id) const = 0;

		static subsystem_paramid_t	Param(paramid_t id, const ISubsystem* reserved = 0);
		static paramid_t			Param(subsystem_paramid_t id, const ISubsystem* reserved = 0);
	};

} // namespace act

#endif	// ACT_ISubsystem_h
