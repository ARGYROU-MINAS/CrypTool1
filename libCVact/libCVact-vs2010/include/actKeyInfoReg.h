// ---------------------------------------------------------------------------
// Name:      actKeyInfoReg.h
// Product:   cv act library
// Purpose:   Registry for IKeyInfo factory functions.
//            
// Copyright: (c) 2011 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  07/31/2011
// ---------------------------------------------------------------------------

#ifndef ACT_KeyInfoReg_h
#define ACT_KeyInfoReg_h

#include "actFactoryReg.h"

namespace act
{
	class IKeyInfo;

	typedef IKeyInfo* (*CreateKeyInfoPtr)();
	typedef FactoryMapEntry<CreateKeyInfoPtr> KeyInfoMapEntry;

	typedef FactoryReg
	<	IKeyInfo, CreateKeyInfoPtr, KeyInfoMapEntry
	>	KeyInfoReg;

} // namespace act

#endif // ACT_KeyInfoReg_h
