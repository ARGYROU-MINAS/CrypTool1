//////////////////////////////////////////////////////////////////////////////////
// Name:      actICertificate.h
// Product:   cv act library
// Purpose:   The abstract class ICertificate enables access to a certificate, e.g.
//            its public key and the corresponding validity. 
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_ICertificate_h
#define ACT_ICertificate_h

#include "actBasics.h"
#include "actIParam.h"

namespace act
{
	class IKey;
	class Blob;

	class ICertificate : public IParam
	{
	public:
		virtual ~ICertificate() { };

		virtual ICertificate* Clone() const = 0;
		virtual void Import(const Blob& certblob) = 0;
		virtual void Export(Blob& certblob) const = 0;

		virtual void SetPublicKey(const IKey* pubkey) = 0;
		virtual IKey* CreatePublicKey(const char* = 0) const = 0;

		virtual void Sign(const IKey* privkey) = 0;
		virtual int Verify(const IKey* pubkey) const = 0;

		virtual void* GetCreatePointer() const = 0;
	};

} // namespace act

#endif // ACT_ICertificate_h
