// ---------------------------------------------------------------------------
// Name:      actSlotMonitorReg.h
// Product:   cv act library
// Purpose:   factory functions registry to create Slot-Monitor objects.
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  04/12/2009
// ---------------------------------------------------------------------------

#ifndef ACT_SlotMonitoReg_h
#define ACT_SlotMonitoReg_h

#include "actFactoryReg.h"

namespace act
{
	class ISubsystem;
	class ISlot;
	class ISlotMonitor;

	typedef ISlotMonitor* (*CreateSlotMonitorPtr)(ISlot*);
	typedef ISlotMonitor* (*CreateSystemSlotMonitorPtr)(ISubsystem*);

	struct SlotMonitorRegCreatePtr
	{
		ISlotMonitor* operator()(const char*, ISlot* slot) const
		{
			return createSlotMonitor != 0 ? createSlotMonitor(slot) : 0;
		}

		ISlotMonitor* operator()(const char*, ISubsystem* system) const
		{
			return createSystemSlotMonitor != 0 ? createSystemSlotMonitor(system) : 0;
		}

		CreateSlotMonitorPtr		createSlotMonitor;
		CreateSystemSlotMonitorPtr	createSystemSlotMonitor;
	};


	typedef FactoryMapEntry<SlotMonitorRegCreatePtr> SlotMonitorRegEntry;

	typedef FactoryReg
	<	ISlotMonitor, SlotMonitorRegCreatePtr, SlotMonitorRegEntry
	>	SlotMonitorReg;

} // namespace act

#endif // ACT_SlotMonitoReg_h
