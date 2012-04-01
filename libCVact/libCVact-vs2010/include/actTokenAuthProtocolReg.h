// ---------------------------------------------------------------------------
// Name:      actTokenAuthProtocolReg.h
// Product:   cv act library
// Purpose:   factory functions registry to create ITokenAuthProtocol objects.
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  14/10/2009
// ---------------------------------------------------------------------------

#ifndef ACT_TokenAuthProtocolReg_h
#define ACT_TokenAuthProtocolReg_h

#include "actFactoryReg.h"

namespace act
{
	class ITokenAuthProtocol;

	typedef ITokenAuthProtocol* (*CreateTokenAuthProtocolPtr)(const char*);
	typedef FactoryMapEntry<CreateTokenAuthProtocolPtr> TokenAuthProtocolMapEntry;

	typedef FactoryReg
	<	ITokenAuthProtocol, CreateTokenAuthProtocolPtr, TokenAuthProtocolMapEntry
	>	TokenAuthProtocolReg;

} // namespace act

#endif // ACT_TokenAuthProtocolReg_h
