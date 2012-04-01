// ---------------------------------------------------------------------------
// Name:      actTokenAuthProtocolKit.h
// Product:   cv act library
// Purpose:   Factory functions to create specific ITokenAuthProtocol objects.
//            
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  14/10/2008
// ---------------------------------------------------------------------------

#ifndef ACT_TokenAuthProtocolKit_h
#define ACT_TokenAuthProtocolKit_h

namespace act
{
	class ITokenAuthProtocol;

	ITokenAuthProtocol* CreateTokenAuthPACE(const char* name);	// EACv2-PACE
	ITokenAuthProtocol* CreateTokenAuthTA(const char* name);	// EACv2-TA
	ITokenAuthProtocol* CreateTokenAuthCA(const char* name);	// EACv2-CA

	ITokenAuthProtocol* CreateTokenAuthBAC(const char* name);	// EACv1-BAC

} // namespace act

#endif // ACT_TokenAuthProtocolKit_h
