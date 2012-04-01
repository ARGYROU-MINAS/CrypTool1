// ---------------------------------------------------------------------------
// Name:      actProfileGeneratorReg.h
// Product:   cv act library
// Purpose:   factory functions registry to create IProfileGenerator objects.
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  12/18/2009
// ---------------------------------------------------------------------------

#ifndef ACT_ProfileGeneratorReg_h
#define ACT_ProfileGeneratorReg_h

#include "actFactoryReg.h"

namespace act
{
	class IProfileGenerator;

	typedef IProfileGenerator* (*CreateProfileGeneratorPtr)(const char*);
	typedef FactoryMapEntry<CreateProfileGeneratorPtr> ProfileGeneratorMapEntry;

	typedef FactoryReg
	<	IProfileGenerator, CreateProfileGeneratorPtr, ProfileGeneratorMapEntry
	>	ProfileGeneratorReg;

} // namespace act

#endif // ACT_ProfileGeneratorReg_h
