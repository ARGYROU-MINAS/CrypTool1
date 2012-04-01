//////////////////////////////////////////////////////////////////////////////////
// Name:      actIKey.h
// Product:   cv act library
// Purpose:   IKey is an abstract base class. All concrete Key-classes are 
//            derived from IKey.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_IKey_h
#define ACT_IKey_h

#include "actIParam.h"
#include "actBlob.h"

namespace act
{
	class IAlgorithm;
	class IRNGAlg;

	class IKey : public IParam
	{
	public:
		virtual ~IKey() { }

		virtual IKey* Clone() const = 0;

		virtual void Import(const Blob& keyblob) = 0;
		virtual void Export(Blob& keyblob, export_t type = DEFAULT) const = 0;

		virtual void Generate(IRNGAlg* prng = 0) = 0;
		virtual void Derive(const Blob& data, const Blob& salt = Blob()) = 0;

		virtual IAlgorithm* CreateAlgorithm(mode_t Mode) const = 0;
		virtual IAlgorithm* CreateAlgorithm(mode_t Mode, const Blob& data) const = 0;

		virtual void* GetCreatePointer() const = 0;
	};

} // namespace act

#endif // ACT_IKey_h
