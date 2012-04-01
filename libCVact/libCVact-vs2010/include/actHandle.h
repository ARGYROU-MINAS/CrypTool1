//////////////////////////////////////////////////////////////////////////
// Name:      actHandle.h
// Product:   cv act library
// Purpose:   Handle helper templates
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  07/27/2010
//////////////////////////////////////////////////////////////////////////

#ifndef ACT_Handle_h
#define ACT_Handle_h

#include "actMove.h"
#include "actException.h"

namespace act
{
	//
	// Handle
	class Handle
	{
	private:
		Handle(const Handle&);
		Handle& operator=(const Handle&);

	protected:
		Handle() { }

	public:
		virtual ~Handle() { /* essential */ }

		template<typename TypeT> TypeT* as() const;
		template<typename TypeT> TypeT& requiredAs() const;

		template<typename TypeT>
		friend inline TypeT& getPointer(const Handle& handle)
		{
			return handle.as<TypeT>();
		}

		template<typename TypeT>
		friend inline TypeT& getRef(const Handle& handle)
		{
			return handle.requiredAs<TypeT>();
		}
	};

	//
	// ValueHandle<>
	template<typename TypeT>
	class ValueHandle : public Handle
	{
	public:
		typedef TypeT value_type;

		ValueHandle() : m_val() { }
		explicit ValueHandle(const TypeT& other) : m_val(other) { }
		template<typename O> void operator=(const O& other)		{ m_val = other;	 }

		template<typename O>
		explicit ValueHandle(move_from<O> other) : m_val()		{ other.move(m_val); }
		template<typename O> void operator=(move_from<O> other) { other.move(m_val); }

		inline TypeT& valueRef() const		{ return m_val;		}

		inline operator TypeT&() const		{ return m_val;		}

		inline TypeT& operator*() const		{ return m_val;		}
		inline TypeT* operator->() const	{ return &m_val;	}

	private:
		mutable TypeT m_val;

	private:
		friend class Handle;
	};

	//
	// Handle::as<>
	template<typename TypeT>
	inline TypeT* Handle::as() const
	{
		const ValueHandle<TypeT>* self = dynamic_cast<const ValueHandle<TypeT>*>(this);
		return self != 0 ? &self->m_val : 0;
	}

	//
	// Handle::requiredAs<>
	template<typename TypeT>
	inline TypeT& Handle::requiredAs() const
	{
		TypeT* value = as<TypeT>();
		if(value != 0) return *value;
		throw NullPointerException("invalid handle value type");
	}

} // namespace act

#endif // ACT_Handle_h
