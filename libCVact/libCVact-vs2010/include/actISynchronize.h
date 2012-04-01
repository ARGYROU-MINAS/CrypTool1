//////////////////////////////////////////////////////////////////////////
// Name:      actISynchronize.h
// Product:   cv act library
// Purpose:   Implemented by types supporting multithreading synchronization.
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  07/27/2010
//////////////////////////////////////////////////////////////////////////

#ifndef ACT_ISynchronize_h
#define ACT_ISynchronize_h

namespace act
{
	class Handle;

	//
	// ISynchronize
	class ISynchronize
	{
	protected:
		virtual ~ISynchronize() { }

	public:
		virtual void Lock() = 0;
		virtual void Unlock() = 0;
		virtual long LockCount() const = 0;

		virtual const Handle& syncHandle() const = 0;
	};

	inline void Lock(ISynchronize& object)			  { object.Lock();			   }
	inline void Unlock(ISynchronize& object)		  { object.Unlock();		   }
	inline long LockCount(const ISynchronize& object) { return object.LockCount(); }

} // namespace act

#endif // ACT_ISynchronize_h
