// ---------------------------------------------------------------------------
// Name:      actISlotMonitor.h
// Product:   cv act library
// Purpose:   The class SlotMonitor notifies the slot events
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  05/27/2002
// ---------------------------------------------------------------------------

#ifndef ACT_ISlotMonitor_h
#define ACT_ISlotMonitor_h

#include "actIRefCounted.h"

namespace act
{
	class IEventHandler;

	//
	// ISlotMonitor
	class ISlotMonitor : public IRefCounted
	{
	public:
		virtual void Stop() = 0;
		virtual void Start(IEventHandler* cmd) = 0;
		virtual bool Interrupted() const = 0;
	};

} // namespace act

#endif	// ACT_ISlotMonitor_h
