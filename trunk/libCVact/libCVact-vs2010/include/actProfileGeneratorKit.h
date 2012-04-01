// ---------------------------------------------------------------------------
// Name:      actProfileGeneratorKit.h
// Product:   cv act library
// Purpose:   Factory functions for smartcard profile generators.
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  12/18/2009
// ---------------------------------------------------------------------------

#ifndef ACT_ProfileGeneratorKit_h
#define ACT_ProfileGeneratorKit_h

namespace act
{
	class IProfileGenerator;

	IProfileGenerator* CreateJCPKCS15Generator(const char* name);

} // namespace act

#endif // ACT_ProfileGeneratorKit_h
