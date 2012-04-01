// ---------------------------------------------------------------------------
// Name:      actPKCS15BehaviorKit.h
// Product:   cv act library
// Purpose:   Factory functions to create specific PKCS15Behavior objects.
//            
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  06/02/2008
// ---------------------------------------------------------------------------

#ifndef ACT_PKCS15BehaviorKit_h
#define ACT_PKCS15BehaviorKit_h

#include <string>

namespace act
{
	class IToken;
	class IPKCS15Behavior;

	// default behavior, does nothing
	IPKCS15Behavior* CreatePKCS15Behavior(const char* mid, IToken* token);

	// specialized behavior
	IPKCS15Behavior* CreateJCPKCS15Behavior(const char* mid, IToken* token);
		IPKCS15Behavior* CreateJCPKCS15EACBehavior(const char* mid, IToken* token);
	IPKCS15Behavior* CreateV4PKCS15Behavior(const char* mid, IToken* token);
	IPKCS15Behavior* CreateACOSPKCS15Behavior(const char* mid, IToken* token);
	IPKCS15Behavior* CreateStarCOSPKCS15Behavior(const char* mid, IToken* token);
	//IPKCS15Behavior* CreateSECCOSPKCS15Behavior(const char* mid, IToken* token); // to be released

	// third party behavior
	IPKCS15Behavior* CreateSafeSignBehavior(const char* mid, IToken* token);
		IPKCS15Behavior* CreateTCTCSafeSignBehavior(const char* mid, IToken* token);

	IPKCS15Behavior* CreateStarSignBehavior(const char* mid, IToken* token);

	IPKCS15Behavior* CreateHiPathBehavior(const char* mid, IToken* token);

	IPKCS15Behavior* CreateNexusBehavior(const char* mid, IToken* token);
		IPKCS15Behavior* CreateVWBehavior(const char* mid, IToken* token);		// Nexus derived
		IPKCS15Behavior* CreateDTRUSTBehavior(const char* mid, IToken* token);	// Nexus derived

	IPKCS15Behavior* CreateStudentCardBehavior(const char* label, IToken* token);

	IPKCS15Behavior* CreateECHBehavior(const char* mid, IToken* token);

} // namespace act

#endif // ACT_PKCS15BehaviorKit_h
