// ---------------------------------------------------------------------------
// Name:      actSlotManager.h
// Product:   cv act library
// Purpose:   The class SlotManager detects and manages the subsystems and the slots
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang
//			  Markus Tesche
// Date:	  03/26/2002
// ---------------------------------------------------------------------------

#ifndef ACT_SlotManager_h
#define ACT_SlotManager_h

#include "actIEventMonitoring.h"
#include "actISubsystem.h"

namespace act
{
	class ISubsystem;
	class ISubsystemConfig;

	class ISlot;
	class ITokenConfig;

	//
	// SlotManager
	class SlotManager : public IEventMonitoring
	{
	private:
		struct SubsystemList
		{
			SubsystemList(ISubsystem* system, SubsystemList* next = 0);
			~SubsystemList();

			SubsystemList*	insert(SubsystemList* prev);
			SubsystemList*	remove(SubsystemList* prev);

			ISubsystem*		system;
			SubsystemList*	next;
		};

	public:
		SlotManager(ITokenConfig* tkcfg = 0);
		~SlotManager();

		bool			Install(ISubsystem* system);
		bool			Install(ISubsystemConfig* config);

		void			Refresh();
		void			Refresh(timeout_t timeout);

		void			Disconnect();
		ISubsystem*		GetSystem(size_t pos = 0) const;

		// SlotList
		int				GetSlotNumber() const;
		const ISlot*	GetSlot(int pos) const;
		ISlot*			CreateSlot(const char* name) const;

		void			SetParam(paramid_t id, intptr_t val);

		// IEventMonitoring functions
		virtual bool	IsMonitored() const;
		virtual void	StopMonitor(bool force = false);
		virtual void	StartMonitor(IEventHandler* cmd);

	protected:
		IEventHandler*	SetMonitor(SubsystemList* begin, IEventHandler* cmd, bool force);

	private:
		int				m_total;
		ITokenConfig*	m_tkcfg;
		SubsystemList*	m_begin;
		SubsystemList*	m_current;
		IEventHandler*	m_cmd_root;
		IEventHandler*	m_cmd_current;
	};

} // namespace act

#endif // ACT_SlotManager_h
