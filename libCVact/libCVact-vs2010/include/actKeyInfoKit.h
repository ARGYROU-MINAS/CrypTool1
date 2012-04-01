// ---------------------------------------------------------------------------
// Name:      actKeyInfoKit.h
// Product:   cv act library
// Purpose:   IKeyInfo factory functions.
//            
// Copyright: (c) 2011 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  07/31/2011
// ---------------------------------------------------------------------------

#ifndef ACT_KeyInfoKit_h
#define ACT_KeyInfoKit_h

#include <string>

namespace act
{
	class IKeyInfo;

	IKeyInfo* CreatePKCS8();

} // namespace act

#endif // ACT_KeyInfoKit_h
