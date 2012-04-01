// ---------------------------------------------------------------------------
// Name:		actIEventMonitoring.h
// Product:		cv act library
// Purpose:		Interface for event monitoring enabled objects.
//
// Copyright:	(c) 2010 cv cryptovision GmbH 
//              all rights reserved.
// Licence:		The conditions for the use of this software are regulated 
//				in the cv act library licence agreement.
//
// Autor:		Markus Tesche (MTE)
// Date:		08/20/2010
// ---------------------------------------------------------------------------

#ifndef ACT_IEventMonitoring_h
#define ACT_IEventMonitoring_h

namespace act
{
	class IEventHandler;

	//
	// IEventMonitoring
	class IEventMonitoring
	{
	public:
		virtual ~IEventMonitoring() { }

		virtual bool IsMonitored() const = 0;
		virtual void StopMonitor(bool force = false) = 0;
		virtual void StartMonitor(IEventHandler* cmd) = 0;
	};

} // namespace act

#endif // ACT_IEventMonitoring_h
