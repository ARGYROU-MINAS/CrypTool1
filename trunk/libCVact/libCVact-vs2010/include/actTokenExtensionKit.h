// ---------------------------------------------------------------------------
// Name:      actTokenExtensionKit.h
// Product:   cv act library
// Purpose:   Factory functions to create specific ITokenExtension objects.
//            
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  12/02/2008
// ---------------------------------------------------------------------------

#ifndef ACT_TokenExtensionKit_h
#define ACT_TokenExtensionKit_h

namespace act
{
	class IToken;
	class ITokenExtension;

	ITokenExtension* CreateMDProfileExt(const char* name, IToken*);		// Minidriver
	ITokenExtension* CreateEACTAwithCAPI(const char* name, IToken*);	// EACv2-TA with CAPI

} // namespace act

#endif // ACT_TokenExtensionKit_h
