// ---------------------------------------------------------------------------
// Name:      actIKeyFactory.h
// Product:   cv act library
// Purpose:   IKeyFactory and IKeyFactoryChain interface
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  05/18/2008
// ---------------------------------------------------------------------------

#ifndef ACT_IKeyFactory_h
#define ACT_IKeyFactory_h

#include "actTokenBase.h"

namespace act
{
	class ITokenKey;
	class ITokenBlockCipher;
	class ITokenBlockCipherKey;

	class IKeyFactory
	{
	protected:
		virtual ~IKeyFactory()
		{ }

	public:
		virtual ITokenKey* CreateKey(int type, FileInfo& fi, int usage, bool cleartoken) = 0;

		virtual ITokenBlockCipher* CreateBlockCipher(FileInfo& fi) = 0;
		virtual ITokenBlockCipherKey* CreateBlockCipherKey(ITokenBlockCipher* cipher, bool cleartoken) = 0;
		virtual ITokenBlockCipherKey* CreateBlockCipherAndKey(FileInfo& fi, bool cleartoken) = 0;
	};

	class IKeyFactoryChain : public IKeyFactory
	{
	public:
		virtual void SetNext(IKeyFactoryChain* next) = 0;
	};

} // namespace act

#endif // ACT_IKeyFactory_h
