// ---------------------------------------------------------------------------
// Name:		actISubsystemConfig.h
// Product:		cv act library
// Purpose:		The Subsystem configuration.
//            
// Copyright:	(c) 2006 cv cryptovision GmbH 
//              all rights reserved.
// Licence:		The conditions for the use of this software are regulated 
//				in the cv act library licence agreement.
//
// Autor:		Markus Tesche (MTE)
// Date:		1/12/2006
// ---------------------------------------------------------------------------

#ifndef ACT_ISubsystemConfig_h
#define ACT_ISubsystemConfig_h

#include "actIRefCounted.h"

namespace act
{
	class ISubsystem;

	//
	// ISubsystemConfig
	class ISubsystemConfig : public IRefCounted
	{
	public:
		// Returns the Subsystem name.
		virtual const char* GetName() const = 0;

		// Configures the Subsystem, on error throws.
		virtual void ConfigureSubsystem(ISubsystem* system) = 0;

		// To be called for previuosly configured Subsystem, never throws!
		virtual void DestructSubsystem(ISubsystem* system) = 0;
	};

} // namespace act

#endif	// ACT_ISubsystemConfig_h
