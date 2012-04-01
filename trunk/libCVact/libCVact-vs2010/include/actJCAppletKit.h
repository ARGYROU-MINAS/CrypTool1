// ---------------------------------------------------------------------------
// Name:      actAppletKit.h
// Product:   cv act library
// Purpose:   registry for factory functions to create JavaCard Applet
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:
// Date:	  02/10/2003
// ---------------------------------------------------------------------------

#ifndef ACT_AppletKit_h
#define ACT_AppletKit_h

#include "actBlob.h"

namespace act
{
	class IToken;
	class JavaCardOS;

	bool IsJCProfileApplet(JavaCardOS* os, const Blob& aid);					
	IToken* CreateJCProfileApplet(JavaCardOS* os, const Blob& aid);

} // namespace act

#endif	// ACT_AppletKit_h
