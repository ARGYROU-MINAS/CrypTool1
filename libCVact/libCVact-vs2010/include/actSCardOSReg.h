// ---------------------------------------------------------------------------
// Name:      actSCardOSReg.h
// Product:   cv act library
// Purpose:   factory functions registry to create SCardOS objects.
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  04/09/2002
// ---------------------------------------------------------------------------

#ifndef ACT_SCardOSReg_h
#define ACT_SCardOSReg_h

#include "actBlob.h"
#include "actFactoryReg.h"

namespace act
{
#	define ACT_ISO7816OS_NAME	"ISO7816OS"

	class ISCardOS;
	class ISCardAccess;

	typedef ISCardOS* (*CreateSCardOSPtr)(ISCardAccess*);
	typedef bool      (*DetectSCardOSPtr)(const Blob&, const ISCardAccess*);

	struct SCardOSMapEntry
	{
		const char*		 Name;
		CreateSCardOSPtr CreatePtr;
	};

	struct SCardOSFactoryEntry
	{
		DetectSCardOSPtr DetectPtr;
		CreateSCardOSPtr CreatePtr;
	};

	class SCardOSReg
	{
	public:
		static ISCardOS* CreateSCardOS(const Blob& atr, ISCardAccess* ac);
		static CreateSCardOSPtr GetCreatePointer(const Blob& atr, const ISCardAccess* ac);
		static CreateSCardOSPtr GetCreatePointer(const char* name);
		static const char* GetName(void* createptr);
		static const char* GetNextName(const char* name);
		static void Insert(const char* name, CreateSCardOSPtr createptr);
		static void Insert(const SCardOSMapEntry* entry);
		static void Insert(const SCardOSFactoryEntry* entry);
	};

	// ---------------------------------------------------------------------------
	typedef ISCardOS* (*DeriveSCardOSPtr)(ISCardOS*);
	typedef FactoryMapEntry<DeriveSCardOSPtr> SCardOSDerivationMapEntry;

	typedef FactoryReg
	<	ISCardOS, DeriveSCardOSPtr, SCardOSDerivationMapEntry
	>	SCardOSDerivationReg;

} // namespace act

#endif // ACT_SCardOSReg_h
