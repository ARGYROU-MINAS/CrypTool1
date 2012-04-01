// ---------------------------------------------------------------------------
// Name:      actTokenExtensionReg.h
// Product:   cv act library
// Purpose:   Registry for ITokenExtension factory functions.
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  12/02/2008
// ---------------------------------------------------------------------------

#ifndef ACT_TokenExtensionReg_h
#define ACT_TokenExtensionReg_h

#include "actFactoryReg.h"

namespace act
{
	class IToken;
	class ITokenExtension;

	typedef ITokenExtension* (*CreateTokenExtensionPtr)(const char*, IToken*);
	typedef FactoryMapEntry<CreateTokenExtensionPtr> TokenExtensionMapEntry;

	typedef FactoryReg
		<	ITokenExtension, CreateTokenExtensionPtr, TokenExtensionMapEntry
		>	TokenExtensionReg;

} // namespace act

#endif // ACT_TokenExtensionReg_h
