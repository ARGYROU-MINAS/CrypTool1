// ---------------------------------------------------------------------------
// Name:      actPKCS15BehaviorReg.h
// Product:   cv act library
// Purpose:   Registry for factory functions to create specific PKCS15Behavior objects.
//            
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  06/02/2008
// ---------------------------------------------------------------------------

#ifndef ACT_PKCS15BehaviorReg_h
#define ACT_PKCS15BehaviorReg_h

#include "actFactoryReg.h"

namespace act
{
	class IToken;
	class IPKCS15Behavior;

	typedef IPKCS15Behavior* (*CreatePKCS15BehaviorPtr)(const char* mid, IToken* token);
	typedef FactoryMapEntry<CreatePKCS15BehaviorPtr> PKCS15BehaviorMapEntry;

	typedef FactoryReg
	<	IPKCS15Behavior, CreatePKCS15BehaviorPtr, PKCS15BehaviorMapEntry
	>	PKCS15BehaviorReg;

} // namespace act

#endif // ACT_PKCS15BehaviorReg_h
