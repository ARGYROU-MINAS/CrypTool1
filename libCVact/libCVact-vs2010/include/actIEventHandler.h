// ---------------------------------------------------------------------------
// Name:      actIEventHandler.h
// Product:   cv act library
// Purpose:   Interfaces required to receive token, slot or subsystem events
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
//			  Markus Tesche
// Date:	  03/26/2002
// ---------------------------------------------------------------------------

#ifndef ACT_IEventHandler_h
#define ACT_IEventHandler_h

#include "actTypeTags.h"
#include "actIRefCounted.h"

namespace act
{
	enum EventCode
	{
		TOKEN_RECONNECT		= 0x00000008,
		TOKEN_REMOVED		= 0x00000010,
		TOKEN_INSERTED		= 0x00000020,
		SLOT_REMOVED		= 0x00000040,
		SLOT_INSERTED		= 0x00000080,
		SUBSYSTEM_STOPPED	= 0x00000100,
		SUBSYSTEM_STARTED	= 0x00000200,
		MONITORING_STOPPED	= 0x00000400,
		MONITORING_STARTED	= 0x00000800,
		MONITORING_ERROR	= 0x80000000,
		THREAD_SHUTDOWN		= 0xAFFEDEAD,
	};

	class ISubsystem;
	class IEventMonitoring;

	//
	// IEventHandler
	class IEventHandler : public IRefCounted
	{
	public:
		virtual IEventHandler* Clone() = 0;
		virtual void Source(IEventMonitoring* source) = 0;
		virtual void OnEvent(int event, ISubsystem* source) = 0;
	};

	typedef TypeTag<IEventHandler> TagIEH;

} // namespace act

#endif	// ACT_IEventHandler_h
