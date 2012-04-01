//////////////////////////////////////////////////////////////////////////////////
// Name:      actIKeyInfo.h
// Product:   cv act library
// Purpose:   Interface to access encoded (f.e. PKCS#8) key information.
//
// Copyright: (c) 2011 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  07/31/2011
//////////////////////////////////////////////////////////////////////////

#ifndef ACT_IKeyInfo_h
#define ACT_IKeyInfo_h

#include "actBlob.h"

namespace act
{
	class IKeyInfo
	{
	public:
		virtual ~IKeyInfo() { }

		virtual IKeyInfo* Clone() const = 0;
		virtual void* GetCreatePointer() const = 0;

		virtual const char* GetAlgorithm(const Blob& keyblob) = 0;
	};

} // namespace act

#endif // ACT_IKeyInfo_h
