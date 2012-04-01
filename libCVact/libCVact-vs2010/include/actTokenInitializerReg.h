// ---------------------------------------------------------------------------
// Name:      actTokenInitializerReg.h
// Product:   cv act library
// Purpose:   Registry for ITokenInitializer factory functions.
//
// Copyright: (c) 2012 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  03/21/2012
// ---------------------------------------------------------------------------

#ifndef ACT_TokenInitializerReg_h
#define ACT_TokenInitializerReg_h

#include "actFactoryReg.h"

namespace act
{
	class ISCardOS;
	class ITokenInitializer;

	typedef ITokenInitializer* (*CreateTokenInitializerPtr)(ISCardOS*);
	typedef FactoryMapEntry<CreateTokenInitializerPtr> TokenInitializerMapEntry;

	typedef FactoryReg
		<	ITokenInitializer, CreateTokenInitializerPtr, TokenInitializerMapEntry
		>	TokenInitializerReg;

} // namespace act

#endif // ACT_TokenExtensionReg_h
