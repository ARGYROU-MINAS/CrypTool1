//////////////////////////////////////////////////////////////////////////////////
// Name:      actKeyKit.h
// Product:   cv act library
// Purpose:   declaration of all factory functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_KeyKit_h
#define ACT_KeyKit_h

namespace act
{
	class IKey;

	IKey* CreateBlockCipherKey();

	IKey* CreateStreamCipherKey();

	IKey* CreateHashMACKey();
	IKey* CreateCBCMACKey();
	IKey* CreateSecretKeyMACKey();
	IKey* CreateRetailCFBMACKey();
	IKey* Create_iMAC3Key();
	IKey* CreateCMACKey();

	IKey* CreateRSAKey();

	IKey* CreateDSAKey();
	IKey* CreateECDSAKey();
	IKey* CreateECGDSAKey();

	IKey* CreateDHKey();
	IKey* CreateECDHKey();

	IKey* CreateIESKey();

} // namespace act

#endif // ACT_KeyKit_h
