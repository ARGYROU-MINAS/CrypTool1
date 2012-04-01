//////////////////////////////////////////////////////////////////////////////////
// Name:      actAllocator.h
// Product:   cv act library
// Purpose:   
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  09/29/2008
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_Allocator_h
#define ACT_Allocator_h

#include "actBasics.h"

// --------------------------------------------------------------------------------
namespace act
{
	//
	// Allocator<>
	template<typename TypeT, typename SizeT>
	class Allocator
	{
	public:
		typedef SizeT				size_type;
		typedef TypeT				value_type;
		typedef value_type*			pointer;
		typedef value_type&			reference;
		typedef const value_type*	const_pointer;
		typedef const value_type&	const_reference;

	protected:
		typedef Allocator<TypeT, SizeT>	ThisT;
		typedef pointer (*fptr_allocate)(ThisT*, size_type n, const void* hint);
		typedef void (*fptr_deallocate)(ThisT*, pointer p, size_type n);

	private:
		Allocator(const Allocator&);
		Allocator& operator=(const Allocator&);

	protected:
		Allocator(fptr_allocate pAllocate, fptr_deallocate pDeallocate) throw()
			: m_pAllocate(pAllocate)
			, m_pDeallocate(pDeallocate)
		{ }

	public:
		inline pointer allocate(size_type n, const void* hint)
		{
			return m_pAllocate(this, n, hint);
		}

		inline void deallocate(pointer p, size_type n)
		{
			if(p != 0) m_pDeallocate(this, p, n);
		}

	protected:
		fptr_allocate m_pAllocate;
		fptr_deallocate m_pDeallocate;
	};

	//
	// AllocatorImpl<>
	template
	<
		class AllocatorT,
		class BaseT = Allocator<typename AllocatorT::value_type, typename AllocatorT::size_type>
	>
	class AllocatorImpl : public BaseT
	{
	public:
		typedef typename BaseT::pointer		pointer;
		typedef typename BaseT::size_type	size_type;

	protected:
		typedef AllocatorImpl<AllocatorT, BaseT> ThisT;

	public:
		AllocatorImpl() throw()
			: BaseT(_allocate, _deallocate)
		{ }

		AllocatorT& ref_alloc() { return m_Alloc; }

	private:
		inline static pointer _allocate(BaseT* pThis, size_type n, const void* hint)
		{
			return static_cast<ThisT*>(pThis)->m_Alloc.allocate(n, hint);
		}

		inline static void _deallocate(BaseT* pThis, pointer p, size_type n)
		{
			static_cast<ThisT*>(pThis)->m_Alloc.deallocate(p, n);
		}

	private:
		AllocatorT m_Alloc;
	};

} // namespace act

#endif // ACT_Allocator_h
