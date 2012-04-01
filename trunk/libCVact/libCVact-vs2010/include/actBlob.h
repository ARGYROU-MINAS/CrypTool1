//////////////////////////////////////////////////////////////////////////////////
// Name:      actBlob.h
// Product:   cv act library
// Purpose:   The datatype Blob (Binary Large Object) is a universal type, which
//            can be used for any data. The class Blob almost behaves like 
//            std::vector<unsigned char> with the difference that freed memory 
//            is filled with zeros to enhance security.
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_Blob_h
#define ACT_Blob_h

#include "actMove.h"
#include "actBasics.h"
#include "actAllocator.h"

#ifndef UNDER_CE_30
#	include <iostream>
#endif // UNDER_CE_30

#ifndef NO_STL_SUPPORT
#	include <utility>	// used for reserve_iterator
#	include <string>	// used for string
#else
	// --------------------------------------------------------------------------------
	// if there is no STL support, we define reverse_iterator here.
	// --------------------------------------------------------------------------------
	namespace std
	{	
				// ITERATOR TAGS (from <iterator>)
		struct input_iterator_tag {};
		struct output_iterator_tag {};
		struct forward_iterator_tag
			: public input_iterator_tag {};
		struct bidirectional_iterator_tag
			: public forward_iterator_tag {};
		struct random_access_iterator_tag
			: public bidirectional_iterator_tag  {};

		// TEMPLATE CLASS iterator (from <iterator>)
		template<class _C, class _Ty, class _D = ptrdiff_t>
			struct iterator {
			typedef _C iterator_category;
			typedef _Ty value_type;
			typedef _D distance_type;
			};
		template<class _Ty, class _D>
			struct _Bidit : public iterator<bidirectional_iterator_tag,
				_Ty, _D> {};
		template<class _Ty, class _D>
			struct _Ranit : public iterator<random_access_iterator_tag,
				_Ty, _D> {};
		
		// TEMPLATE CLASS iterator_traits (from <iterator>)
		template<class _It>
			struct iterator_traits {
			typedef _It::iterator_category iterator_category;
			typedef _It::value_type value_type;
			typedef _It::distance_type distance_type;
			};

		
		// TEMPLATE CLASS reverse_iterator (from <iterator>)
		template<class _RI,
			class _Ty,
			class _Rt = _Ty&,
			class _Pt = _Ty *,
			class _D = int>
			class reverse_iterator : public _Ranit<_Ty, _D> {
		public:
			typedef reverse_iterator<_RI, _Ty, _Rt, _Pt, _D> _Myt;
			typedef _RI iter_type;
			typedef _Rt reference_type;
			typedef _Pt pointer_type;
			reverse_iterator()
				{}
			explicit reverse_iterator(_RI _X)
				: current(_X) {}
			_RI base() const
				{return(current); }
			_Rt operator*() const
				{return(*(current - 1)); }
		//	_Pt operator->() const
		//		{return(&**this); }
			_Myt& operator++()
				{--current;
				return(*this); }
			_Myt operator++(int)
				{_Myt _Tmp = *this;
				--current;
				return(_Tmp); }
			_Myt& operator--()
				{++current;
				return(*this); }
			_Myt operator--(int)
				{_Myt _Tmp = *this;
				++current;
				return(_Tmp); }
			_Myt& operator+=(_D _N)
				{current -= _N;
				return(*this); }
			_Myt operator+(_D _N) const
				{return(_Myt(current - _N)); }
			_Myt& operator-=(_D _N)
				{current += _N;
				return(*this); }
			_Myt operator-(_D _N) const
				{return(_Myt(current + _N)); }
			_Rt operator[](_D _N) const
				{return(*(*this + _N)); }
		protected:
			_RI current;
			};
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator==(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(get_base(_X) == get_base(_Y)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator!=(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(!(_X == _Y)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator<(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(get_base(_Y) < get_base(_X)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator>(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(_Y < _X); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator<=(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(!(_Y < _X)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			bool __cdecl operator>=(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(!(_X < _Y)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			_D __cdecl operator-(
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _X,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(get_base(_Y) - get_base(_X)); }
		template<class _RI, class _Ty, class _Rt, class _Pt,
			class _D> inline
			reverse_iterator<_RI, _Ty, _Rt, _Pt, _D> __cdecl operator+(_D _N,
				const reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>& _Y)
			{return(reverse_iterator<_RI, _Ty, _Rt, _Pt, _D>(
				get_base(_Y) - _N)); }
	}	// namespace std

#endif //NO_STL_SUPPORT

// --------------------------------------------------------------------------------
namespace act
{
	//
	// byte_array for fixed data
	struct byte_array
	{
		const act::byte*	value;
		const size_t		size;
	};

	inline byte_array make_array(const act::byte* value = 0, size_t size = 0)
	{
		const byte_array ba = { value, size };
		return ba;
	};

#ifndef ACT_NO_BYTE_ARRAY_MACROS
#	define _A(x) x.value, x.size
#	define _B(x) act::make_array(reinterpret_cast<const act::byte*>(x), sizeof(x) - sizeof(x[0]))
#	define _C(x) act::make_array(reinterpret_cast<const act::byte*>(x), sizeof(x))
#	define _H(x) { (const act::byte*) x, sizeof(x) - sizeof(x[0]) }
#endif

#if(_MSC_VER >= 1300)
	template
	<
		class _Ty,
		class _Diff,
		class _Pointer,
		class _Reference,
		class _Pointer2,
		class _Reference2
	>
	class _Ptrit : 
		public std::iterator<std::random_access_iterator_tag, _Ty, _Diff, _Pointer, _Reference>
	{	// wrap pointer as random-access iterator
	public:
		typedef _Ptrit<_Ty, _Diff, _Pointer, _Reference, _Pointer2, _Reference2> _Myt;

		_Ptrit()
		{	// construct with uninitialized wrapped pointer
		}

		_Ptrit(_Pointer _Ptr) : current(_Ptr)
		{	// construct wrapped pointer from _Ptr
		}

		_Ptrit(const _Ptrit<_Ty, _Diff, _Pointer2, _Reference2, _Pointer2, _Reference2>& _Iter)
			: current(_Iter.base())
		{	// const converter or copy constructor
		}

		_Pointer base() const
		{	// return wrapped pointer
			return current;
		}

		_Reference operator*() const
		{	// return designated value
			return *current;
		}

		_Pointer operator->() const
		{	// return pointer to class object
			return &**this;
		}

		_Myt& operator++()
		{	// preincrement
			++current;
			return *this;
		}

		_Myt operator++(int)
		{	// postincrement
			_Myt _Tmp = *this;
			++current;
			return _Tmp;
		}

		_Myt& operator--()
		{	// predecrement
			--current;
			return *this;
		}

		_Myt operator--(int)
		{	// postdecrement
			_Myt _Tmp = *this;
			--current;
			return _Tmp;
		}

		bool operator==(size_t _Right) const
		{	// test if wrapped pointer == integer (null pointer constant)
			return current == (_Pointer) _Right;
		}

		bool operator==(const _Myt& _Right) const
		{	// test for iterator equality
			return current == _Right.current;
		}

		bool operator!=(const _Myt& _Right) const
		{	// test for iterator inequality
			return !(*this == _Right);
		}

		_Myt& operator+=(_Diff _Off)
		{	// increment by integer
			current += _Off;
			return *this;
		}

		_Myt operator+(_Diff _Off) const
		{	// return this + integer
			return _Myt(current + _Off);
		}

		_Myt& operator-=(_Diff _Off)
		{	// decrement by integer
			current -= _Off;
			return *this;
		}

		_Myt operator-(_Diff _Off) const
		{	// return this - integer
			return _Myt(current - _Off);
		}

		_Reference operator[](_Diff _Off) const
		{	// subscript
			return *(*this + _Off);
		}

		bool operator<(const _Myt& _Right) const
		{	// test if this < _Right
			return current < _Right.current;
		}

		bool operator>(const _Myt& _Right) const
		{	// test if this > _Right
			return _Right < *this;
		}

		bool operator<=(const _Myt& _Right) const
		{	// test if this <= _Right
			return !(_Right < *this);
		}

		bool operator>=(const _Myt& _Right) const
		{	// test if this >= _Right
			return !(*this < _Right);
		}

		_Diff operator-(const _Myt& _Right) const
		{	// return difference of iterators
			return current - _Right.current;
		}

	protected:
		_Pointer current;	// the wrapped pointer
	};

#endif // _MSC_VER >= 1300

	//
	// Blob
	class Blob
	{
	protected:
		struct flags
		{
			byte copy_on_write:1;
			byte external_allocated:1;

			flags() throw()
				: copy_on_write(0)
				, external_allocated(0)
			{ }
		};

	public:
		typedef Allocator<byte, size_t>	_Alloc;
		typedef _Alloc					allocator_type;
		typedef _Alloc::size_type		size_type;
		typedef _Alloc::value_type		value_type;
		typedef value_type*				pointer;
		typedef value_type&				reference;
		typedef const value_type*		const_pointer;
		typedef const value_type&		const_reference;
		typedef ptrdiff_t				difference_type;

#if(_MSC_VER >= 1300)
		typedef _Ptrit
		<	value_type, difference_type, pointer, reference, pointer, reference
		>	iterator;

		typedef _Ptrit
		<	value_type, difference_type, const_pointer, const_reference, pointer, reference
		>	const_iterator;

		inline static pointer get_base(iterator it) { return it.base(); }
		inline static const_pointer get_base(const_iterator it) { return it.base(); }

#else
		typedef byte*		iterator;
		typedef const byte*	const_iterator;

		inline static pointer get_base(iterator it) { return it; }
		inline static const_pointer get_base(const_iterator it) { return it; }

#endif

#if (_MSC_VER >= 1200) && (_MSC_VER < 1300)
		typedef std::reverse_iterator
		<	iterator, value_type, reference, pointer, difference_type
		>	reverse_iterator;

		typedef std::reverse_iterator
		<	const_iterator, value_type, const_reference, const_pointer, difference_type
		>	const_reverse_iterator;

#else
		typedef std::reverse_iterator<iterator>	reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

#endif					
		// construct/copy/destroy
		Blob();

		explicit Blob(allocator_type* allocator);
		explicit Blob(const char* str, allocator_type* allocator = dAllocator);

#ifndef NO_STL_SUPPORT
		explicit Blob(std::string& str, allocator_type* allocator = dAllocator);
		explicit Blob(const std::string& str, allocator_type* allocator = dAllocator);
#endif // NO_STL_SUPPORT

		explicit Blob(const byte_array& ba, allocator_type* allocator = dAllocator);
		explicit Blob(size_type n, byte v = byte(0), allocator_type* allocator = dAllocator);

		template<class inputit>
		Blob(inputit f, inputit l, allocator_type* allocator = dAllocator)
			: mFirst(0), mLast(0), mEnd(0), mAllocator(allocator)
		{
			insert(begin(), f, l);			
		}

		Blob(move_from<Blob> other);
		Blob(const Blob& other);
		~Blob();

		Blob& operator=(const Blob& other);
		Blob& operator=(move_from<Blob> other);

		template<class inputit>
		void assign(inputit f, inputit l)
		{
			erase(begin(), end());
			insert(begin(), f, l); 
		}

		void assign(const byte_array& ba);
		void assign(size_type n, byte x = byte(0));

		// capacity
		bool			empty() const			{ return size() == 0;						}
		size_type		size() const			{ return mFirst == 0 ? 0 : mLast - mFirst;	}
		size_type		capacity() const		{ return mFirst == 0 ? 0 : mEnd - mFirst;	}
		size_type		max_size() const;
		void			reserve(size_type n);
		void			resize(size_type n, byte x = byte(0));

		// iterators
		iterator				begin()			{ return mFirst;							}
		const_iterator			begin() const	{ return const_iterator(mFirst);			}
		iterator				end()			{ return mLast;								}
		const_iterator			end() const		{ return const_iterator(mLast);				}
		reverse_iterator		rbegin()		{ return reverse_iterator(end());			}
		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator(end());		}
		reverse_iterator		rend()			{ return reverse_iterator(begin());			}
		const_reverse_iterator	rend() const	{ return const_reverse_iterator(begin());	}


		// element access:
		reference		at(size_type p);
		const_reference	at(size_type p) const;
		reference		operator[](size_type p)			{ return *(begin() + p);	}
		const_reference	operator[](size_type p) const	{ return *(begin() + p);	}

		reference		front()							{ return *begin();			}
		const_reference	front() const					{ return *begin();			}
		reference		back()							{ return *(end() - 1);		}
		const_reference	back() const					{ return *(end() - 1);		}

		// modifiers
		void			push_back(byte x)				{ insert(end(), x);			}
		void			pop_back()						{ erase(end() - 1);			}

		void insert(iterator p, size_type m, byte x);
		iterator insert(iterator p, byte x = byte(0));

		template<class inputit>
		void insert(iterator p, inputit f, inputit l)
		{
			size_type m = 0;
			_distance(f, l, m);
			if(size_type(mEnd - mLast) < m) 
			{
				size_type n = size();
				n = aligned_size(n + (m < n ? n : m));
				iterator s = allocate(n, (void*) 0);
				iterator q = ucopy(mFirst, p, s);
				q = ucopy(f, l, q);
				ucopy(p, mLast, q);
				_destroy(mFirst, mLast);
				deallocate(get_base(mFirst), mEnd - mFirst);
				mEnd = s + n;
				mLast = s + size() + m;
				mFirst = s; 
			}
			else if(size_type(mLast - p) < m) 
			{
				ucopy(p, mLast, p + m);
				ucopy(f + (mLast - p), l, mLast);
				copy(f, f + (mLast - p), p);
				mLast += m; 
			}
			else if(0 < m) 
			{
				ucopy(mLast - m, mLast, mLast);
				copy_backward(p, mLast - m, mLast);
				copy(f, l, p);
				mLast += m; 
			}
		}

		Blob& append(const Blob& x)
		{
			insert(end(), x.begin(), x.end());
			return *this;
		}

		Blob& append(size_type m, byte x)
		{
			insert(end(), m, x);
			return *this;
		}

		template<class inputit>
		Blob& append(inputit f, inputit l)
		{
			insert(end(), f, l);
			return *this;
		}

		void					clear();
		iterator				erase(iterator p);
		iterator				erase(iterator f, iterator l);

		void					swap(Blob& x);
		move_from<Blob>			move() { return act::move(*this); }

		// used by compare operators
		bool					_eq(const Blob& x) const;
		bool					_lt(const Blob& x) const;

		allocator_type* get_allocator() const { return mAllocator; }
		static allocator_type* set_default_allocator(allocator_type* allocator)
		{
			std::swap(dAllocator, allocator);
			return allocator;
		}

	private:
		template<typename inputit, typename outputit>
		outputit copy(inputit f, inputit l, outputit x)
		{
			for(; f != l; ++x, ++f)
				*x = *f;
			return x; 
		}

		iterator copy_backward(const_iterator f, const_iterator l, iterator  x);

		template<typename inputit, typename outputit>
		outputit ucopy(inputit f, inputit l, outputit p)
		{
			for(; f != l; ++p, ++f)
				construct(get_base(p), *f);
			return p; 
		}

		void fill(iterator f, const_iterator l, byte x);
		void ufill(iterator f, size_type n, byte x);

		size_type distance(const_iterator f, const_iterator l) const;

		template<typename inputit>
		void _distance(inputit f, inputit l, size_type& n) const
		{
			for(; f != l; ++f)
				++n;
		}

		bool equal(const_iterator f, const_iterator l, const_iterator x) const;
		bool lexicographical_compare(const_iterator f1, const_iterator l1, const_iterator f2, const_iterator l2) const;

		byte* allocate(size_type n, const void* hint);
		void deallocate(pointer p, size_type n);

		void construct(byte* p, const_reference v)	{ *p = v; }
		void destroy(byte* p)						{ *p = 0; }

		void _destroy(iterator f, iterator l);

		void outofrange() const;

		static size_type aligned_size(size_type size);

	protected:
		flags					mFlags;
		iterator				mFirst, mLast, mEnd;
		allocator_type*			mAllocator;
		static allocator_type*	dAllocator;
	};

#ifndef UNDER_CE_30
	std::ostream &operator<<(std::ostream& os, const Blob& blob);
#endif // UNDER_CE_30


	// --------------------------------------------------------------------------------
	inline bool operator==(const Blob& x, const Blob&y)
	{
		return x._eq(y);
	}

	inline bool operator!=(const Blob& x, const Blob&y)
	{
		return !(x._eq(y));
	}

	inline bool operator<(const Blob& x, const Blob&y)
	{
		return x._lt(y);
	}

	inline bool operator>=(const Blob& x, const Blob&y)
	{
		return !(x._lt(y));
	}

	inline bool operator<=(const Blob& x, const Blob&y)
	{
		return x._eq(y) || x._lt(y);
	}

	inline bool operator>(const Blob& x, const Blob&y)
	{
		return !(x._eq(y) || x._lt(y));
	}

} // namespace act

// --------------------------------------------------------------------------------
namespace std
{
	// ---------------------------------------------------------------------------
	inline void swap(act::Blob& left, act::Blob& right) { left.swap(right); }

} // namespace std

#endif // ACT_Blob_h
