// ---------------------------------------------------------------------------
// Name:      actSlotMonitorKit.h
// Product:   cv act library
// Purpose:   registry for factory functions to create slot monitors
//            
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  04/12/2009
// ---------------------------------------------------------------------------

#ifndef ACT_SlotMonitorKit_h
#define ACT_SlotMonitorKit_h

namespace act
{
	class ISubsystem;
	class ISlot;
	class ISlotMonitor;

	// default polling slot monitor
	ISlotMonitor* CreateSlotMonitor(ISlot*);

	ISlotMonitor* CreatePCSCSlotMonitor(ISlot*);
	ISlotMonitor* CreatePCSCSystemSlotMonitor(ISubsystem*);

} // namespace act

#endif	// ACT_SlotMonitorKit_h
