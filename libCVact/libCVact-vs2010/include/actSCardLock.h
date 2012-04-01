// ---------------------------------------------------------------------------
// Name:      actSCardLock.h
// Product:   cv act library
// Purpose:   Smartcard transaction lock
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  07/10/2009
// ---------------------------------------------------------------------------

#ifndef ACT_SCardLock_H
#define ACT_SCardLock_H

#include "actEnv.h"

#if defined(ACT_64)
#	define	LOCK_SIZE 32
#else
#	define	LOCK_SIZE 16
#endif

namespace act
{
	class ISCardOS;

	class SCardLock
	{
	private:
		SCardLock() { }
		SCardLock(const SCardLock&) { }

	public:
		SCardLock(ISCardOS* os);
		~SCardLock();

		void Reset();
		void Attach(ISCardOS* os);

		void Lock(ISCardOS* os);
		void Unlock();

	private:
		byte m_lock[LOCK_SIZE];
	};

} // namespace act

#undef LOCK_SIZE

#endif // ACT_SCardLock_H
