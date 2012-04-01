//////////////////////////////////////////////////////////////////////////////////
// Name:      actException.h
// Product:   cv act library
// Purpose:   exception hierarchy
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_Exception_h
#define ACT_Exception_h

#include <new>
#include <exception>

#include "actMove.h"
#include "actBlob.h"
#include "actLocation.h"

namespace act
{
	// ---------------------------------------------------------------------------
	enum ExceptionId
	{
		eiException												= 0,
			eiBadException										= eiException + 1,
				eiNullPointerException,
				eiOutOfRangeException,
					eiLeftOfRangeException,
					eiRightOfRangeException,

			eiBadCastException									= eiException + 10,
				eiBadNumericCast,
					eiNegativeOverflow,
					eiPositiveOverflow,

			eiRuntimeException									= eiException + 20,
				eiBadAllocException,
				eiOutOfMemoryException							= eiBadAllocException,
				eiNotSupportedException,
				eiNotImplementedException,
				eiNotInitializedException,
				eiAlreadyInitializedException,
				eiInvalidParameterException,
				eiInvalidSessionIdException,
				eiSynchronizationException,
				eiShutdownException,

			eiLogicalException									= eiException + 40,
				eiASN1Exception,
					eiIncompatibleVersionException,
				eiNoSuchDLLException,
				eiNoSuchMethodException,
				eiPasswordException,
				eiArithmeticException,
				eiMessageDigestException,
				eiPaddingException,
				eiSignatureException,

				eiAlgorithmException							= eiException + 80,
					eiInvalidAlgorithmParameterException,
					eiNoSuchAlgorithmException,

				eiCertificateException							= eiException + 80,
					eiInvalidCertificateException,
					eiCertificateEncodingException,
					eiCertificateExpiredException,
					eiCertificateNotYetValidException,
					eiCertificateParsingException,

				eiKeyException									= eiException + 100,
					eiInvalidKeyException,
					eiKeyManagementException,

				eiEACException									= eiException + 120,
					eiEACDataException,
						eiEACMRZException,
						eiEACCVCertException,

				eiSmartcardException							= eiException + 140,
					eiCardRemovedException,
					eiCardOutOfMemoryException,
					eiCardTransactionException,
					eiInvalidPinException,
					eiPinLockedException,
					eiPinExpiredException,
					eiPinLenRangeException,
					eiInvalidPinFormatException,
					eiInvalidCRKeyException,
					eiInvalidCardException,
					eiInvalidAuthException,
					eiInvalidAuthObjectException,
					eiAuthProtocolException,
					eiConstraintsViolationException,
						eiAuthConstraintsViolation,
						eiTokenFileConstraintsViolation,
					eiSecureMessagingException,
						eiSMWrapException,
						eiSMUnwrapException,
				
				eiSubsystemException							= eiException + 180,
					eiNoSuchSubsystemException,
	};

#ifndef UNDER_CE_30

	// --------------------------------------------------------------------------
	namespace exception
	{
		template<typename U>
		struct convert
		{
			template<typename V>
			void operator()(const U& source, V& dest) const
			{
				dest.code(source.code());
				dest.what(source.what());
				dest.where(source.where());
			}
		};

	} // namespace exception

	//
	// base class for all exceptions thrown by cv act library
	// ---------------------------------------------------------------------------
	class Exception
	{
	public:
		typedef Exception Type;

		explicit Exception(const char* msg = 0, const char* where = 0, ulong code = 0)
			: m_what(msg)
			, m_where(where)
			, m_code(code)
		{ }

		explicit Exception(const std::exception& other)
			: m_what(other.what())
			, m_where(0)
			, m_code(0)
		{ }

		template<typename T>
		explicit Exception(const T& other)
		{
			exception::convert<T>()(other, *this);
		}

		virtual ~Exception()
		{ }

		virtual Exception* Clone() const;
		virtual int		   GetId() const;
		virtual void	   Throw() const;

		template<typename ExceptionT_>
		ExceptionT_* TypedClone() const
		{
			return new ExceptionT_(m_what, m_where, m_code);
		}

		template<typename ExceptionT_, typename ParamT>
		ExceptionT_* TypedClone(const ParamT& param) const
		{
			return new ExceptionT_(m_what, m_where, param);
		}

		template<typename ExceptionT_>
		void TypedThrow() const { throw ExceptionT_(m_what, m_where, m_code); }

		template<typename ExceptionT_, typename ParamT>
		void TypedThrow(const ParamT& param) const { throw ExceptionT_(m_what, m_where, param); }

		const char* what() const				{ return m_what  != 0 ? m_what  : ""; }
		void		what(const char* what)		{ m_what = what;	}

		const char* where() const				{ return m_where != 0 ? m_where : ""; }
		void		where(const char* where)	{ m_where = where;	}

		ulong		code() const				{ return m_code;	}
		void		code(ulong code)			{ m_code = code;	}

	protected:
		const char* m_what;
		const char* m_where;
		ulong		m_code;
	};

	//
	// ExceptionType<>
	// ---------------------------------------------------------------------------
	template
	<
		const int exceptionId_,
		class	  ExceptionT,
		class	  BaseT,
		class	  OtherT = void
	>
	class ExceptionType : public BaseT, public OtherT
	{
	protected:
		typedef BaseT BaseType;
		typedef ExceptionT Type;
		typedef OtherT OtherType;
		enum { exceptionId = exceptionId_ };

	public:
		ExceptionType()
			: BaseType(0, 0, 0)
			, OtherT()
		{ }

		ExceptionType(const char* msg, const char* where, ulong code)
			: BaseType(msg, where, code)
			, OtherT()
		{ }

		ExceptionT& operator<<(const OtherType& other)
		{
			*static_cast<OtherType*>(this) = other;
			return *static_cast<ExceptionT*>(this);
		}

		template<typename ExceptionT_>
		ExceptionT_* TypedClone() const
		{
			ExceptionT_* e = new ExceptionT_(BaseType::m_what, BaseType::m_where, BaseType::m_code);
			if(e != 0) *e << *this;
			return e;
		}

		template<typename ExceptionT_, typename ParamT>
		ExceptionT_* TypedClone(const ParamT& param) const
		{
			ExceptionT_* e = new ExceptionT_(BaseType::m_what, BaseType::m_where, param);
			if(e != 0) *e << *this;
			return e;
		}

		virtual void Throw() const { throw Type() << *this;	}
		virtual int  GetId() const { return exceptionId;	}
	};

	template
	<
		const int exceptionId_,
		class	  ExceptionT,
		class	  BaseT
	>
	class ExceptionType<exceptionId_, ExceptionT, BaseT, void> : public BaseT
	{
	public:
		typedef BaseT BaseType;
		typedef ExceptionT Type;
		enum { exceptionId = exceptionId_ };

		ExceptionType()
			: BaseType(0, 0, 0)
		{ }

		ExceptionType(const char* msg, const char* where, ulong code = 0)
			: BaseType(msg, where, code)
		{ }

		ExceptionT& operator<<(const Exception& other)
		{
			BaseType::m_what  = other.what();
			BaseType::m_where = other.where();
			BaseType::m_code  = other.code();
			return *static_cast<ExceptionT*>(this);
		}

		template<typename ExceptionT_>
		void      TypedThrow() const { throw ExceptionT_() << *this;	}

		virtual void   Throw() const { throw Type() << *this;			}
		virtual int    GetId() const { return exceptionId;				}
	};

	// ---------------------------------------------------------------------------
	class BadException :
		public  ExceptionType<eiBadException, BadException, Exception>
	{
	public:
		typedef ExceptionType<eiBadException, BadException, Exception> BaseType;
		typedef BadException Type;
		using	BaseType::exceptionId;
		using	BaseType::operator<<;

		BadException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: BaseType(msg, where, code)
		{ }
	};

	class NullPointerException :
		public  ExceptionType<eiNullPointerException, NullPointerException, BadException, FileAndLine>
	{
	public:
		typedef ExceptionType<eiNullPointerException, NullPointerException, BadException, FileAndLine> BaseType;
		typedef NullPointerException Type;
		using	BaseType::exceptionId;
		using	BaseType::operator<<;

		NullPointerException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: BaseType(msg, where, code)
		{ }
	};

	class OutOfRangeException :
		public  ExceptionType<eiOutOfRangeException, OutOfRangeException, BadException>
	{
	public:
		typedef ExceptionType<eiOutOfRangeException, OutOfRangeException, BadException> BaseType;
		typedef OutOfRangeException Type;
		using	BaseType::exceptionId;
		using	BaseType::operator<<;

		OutOfRangeException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: BaseType(msg, where, code)
		{ }

		template<typename range_violation_type>
		void operator()(range_violation_type range_violation);
	};

	class LeftOfRangeException	: public ExceptionType<eiLeftOfRangeException,	LeftOfRangeException,	OutOfRangeException> { };
	class RightOfRangeException : public ExceptionType<eiRightOfRangeException, RightOfRangeException,	OutOfRangeException> { };

	template<typename type>
	void OutOfRangeException::operator()(type range_violation)
	{
		switch(exceptionId + range_violation)
		{
		case eiLeftOfRangeException:	TypedThrow<LeftOfRangeException>();
		case eiRightOfRangeException:	TypedThrow<RightOfRangeException>();
		default:						Throw();
		}
	}


	// ---------------------------------------------------------------------------
	class BadCastException :
		public  ExceptionType<eiBadCastException, BadCastException, Exception>
	{
	public:
		typedef ExceptionType<eiBadCastException, BadCastException, Exception> BaseType;
		typedef BadCastException Type;
		using	BaseType::exceptionId;

		BadCastException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: BaseType(msg, where, code)
		{ }
	};

	class BadNumericCast :
		public  ExceptionType<eiBadNumericCast, BadNumericCast, BadCastException>
	{
	public:
		typedef ExceptionType<eiBadNumericCast, BadNumericCast, BadCastException> BaseType;
		typedef BadNumericCast Type;
		using	BaseType::exceptionId;

		BadNumericCast(const char* msg = 0, const char* where = 0, ulong code = 0)
			: BaseType(msg, where, code)
		{ }

		template<typename overflow_type>
		void operator()(overflow_type overflow);
	};

	class NegativeOverflow : public ExceptionType<eiNegativeOverflow, NegativeOverflow,	BadNumericCast> { };
	class PositiveOverflow : public ExceptionType<eiPositiveOverflow, PositiveOverflow,	BadNumericCast> { };

	template<typename overflow_type>
	void BadNumericCast::operator()(overflow_type overflow)
	{
		switch(eiBadNumericCast + overflow)
		{
		case eiNegativeOverflow: TypedThrow<NegativeOverflow>();
		case eiPositiveOverflow: TypedThrow<PositiveOverflow>();
		default:				 Throw();
		}
	}

	// ---------------------------------------------------------------------------
	class RuntimeException :
		public  ExceptionType<eiRuntimeException, RuntimeException, Exception>
	{
	public:
		typedef ExceptionType<eiRuntimeException, RuntimeException, Exception> BaseType;
		typedef RuntimeException Type;
		using	BaseType::exceptionId;

		RuntimeException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: BaseType(msg, where, code)
		{ }
	};

	class BadAllocException :
		public  ExceptionType<eiBadAllocException, BadAllocException, RuntimeException>
	{
	public:
		typedef ExceptionType<eiBadAllocException, BadAllocException, RuntimeException> BaseType;
		typedef BadAllocException Type;
		using	BaseType::exceptionId;

		BadAllocException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: BaseType(msg, where, code)
		{ }
	};

	class OutOfMemoryException :
		public ExceptionType<eiOutOfMemoryException, OutOfMemoryException, RuntimeException>
	{ };

	class NotSupportedException :
		public  ExceptionType<eiNotSupportedException, NotSupportedException, RuntimeException, FileAndLine>
	{
	public:
		typedef ExceptionType<eiNotSupportedException, NotSupportedException, RuntimeException, FileAndLine> BaseType;
		typedef NotSupportedException Type;
		using	BaseType::exceptionId;
		using	BaseType::operator<<;

		explicit NotSupportedException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: BaseType(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>(); }
	};

	class NotImplementedException :
		public  ExceptionType<eiNotImplementedException, NotImplementedException, RuntimeException, FileAndLine>
	{
	public:
		typedef ExceptionType<eiNotImplementedException, NotImplementedException, RuntimeException, FileAndLine> BaseType;
		typedef NotImplementedException Type;
		using	BaseType::exceptionId;
		using	BaseType::operator<<;

		NotImplementedException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: BaseType(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>(); }
	};

	class NotInitializedException     : public ExceptionType<eiNotInitializedException,     NotInitializedException,     RuntimeException, FileAndLine> { };
	class AlreadyInitializedException : public ExceptionType<eiAlreadyInitializedException, AlreadyInitializedException, RuntimeException, FileAndLine> { };
	class InvalidParameterException   : public ExceptionType<eiInvalidParameterException,   InvalidParameterException,   RuntimeException, FileAndLine> { };
	class InvalidSessionIdException   : public ExceptionType<eiInvalidSessionIdException,   InvalidSessionIdException,   RuntimeException, FileAndLine> { };
	class SynchronizationException    : public ExceptionType<eiSynchronizationException,    SynchronizationException,    RuntimeException, FileAndLine> { };

	// ---------------------------------------------------------------------------
	template<class NotifyPtrT = void>
	class ShutdownException :
		public	ExceptionType<eiShutdownException, ShutdownException<NotifyPtrT>, RuntimeException>
	{
	public:
		typedef ExceptionType<eiShutdownException, ShutdownException<NotifyPtrT>, RuntimeException> BaseType;
		typedef ShutdownException Type;
		using	BaseType::exceptionId;
		using	BaseType::operator<<;

		template<class OtherPtrT>
		Type& operator>>(OtherPtrT& notify)  { notify.swap(m_notify); return *this; }
		Type& operator<<(NotifyPtrT& notify) { m_notify.swap(notify); return *this; }

	protected:
		NotifyPtrT m_notify;
	};

	template<>
	class ShutdownException<void> :
		public	ExceptionType<eiShutdownException, ShutdownException<void>, RuntimeException>
	{ };


	// ---------------------------------------------------------------------------
	class LogicalException :
		public  ExceptionType<eiLogicalException, LogicalException, Exception, FileAndLine>
	{
	public:
		typedef ExceptionType<eiLogicalException, LogicalException, Exception, FileAndLine> BaseType;
		typedef LogicalException Type;
		using	BaseType::exceptionId;
		using	BaseType::operator<<;

		LogicalException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: BaseType(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>(); }
	};

	class ASN1Exception : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef ASN1Exception Type;
		using	BaseType::operator<<;

		ASN1Exception(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiASN1Exception; }
	};

	class IncompatibleVersionException
		: public ExceptionType<eiIncompatibleVersionException, IncompatibleVersionException, ASN1Exception>
	{ };

	class NoSuchDLLException	: public ExceptionType<eiNoSuchDLLException,	NoSuchDLLException,		LogicalException> { };
	class NoSuchMethodException : public ExceptionType<eiNoSuchMethodException, NoSuchMethodException,	LogicalException> { };

	class PasswordException : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef PasswordException Type;
		using	BaseType::operator<<;

		PasswordException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiPasswordException;			}
	};

	class ArithmeticException : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef ArithmeticException Type;
		using	BaseType::operator<<;

		ArithmeticException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiArithmeticException;			}
	};

	class MessageDigestException : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef MessageDigestException Type;
		using	BaseType::operator<<;

		MessageDigestException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiMessageDigestException;		}
	};

	class PaddingException : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef PaddingException Type;
		using	BaseType::operator<<;

		PaddingException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiPaddingException;			}
	};

	class SignatureException : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef SignatureException Type;
		using	BaseType::operator<<;

		SignatureException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiSignatureException;			}
	};

	// ---------------------------------------------------------------------------
	class AlgorithmException : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef AlgorithmException Type;
		using	BaseType::operator<<;

		AlgorithmException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiAlgorithmException;			}
	};

	class InvalidAlgorithmParameterException : public AlgorithmException
	{
	public:
		typedef AlgorithmException BaseType;
		typedef InvalidAlgorithmParameterException Type;
		using	BaseType::operator<<;

		InvalidAlgorithmParameterException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: AlgorithmException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();					}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);			}
		virtual int   GetId() const { return eiInvalidAlgorithmParameterException;	}
	};

	class NoSuchAlgorithmException : public AlgorithmException
	{
	public:
		typedef AlgorithmException BaseType;
		typedef NoSuchAlgorithmException Type;
		using	BaseType::operator<<;

		NoSuchAlgorithmException(const char* msg = 0, const char* where = 0, const char* algorithm = 0)
			: AlgorithmException(msg, where)
			, m_algorithm(algorithm)
		{
			m_algorithm.push_back(0);
		}

		// GCC 4.2.1 whats to have it
		virtual ~NoSuchAlgorithmException()
		{ }

		virtual Type* Clone() const { return TypedClone<Type>(algorithm());		}
		virtual void  Throw() const { throw Type(m_what, m_where, algorithm()); }
		virtual int   GetId() const { return eiNoSuchAlgorithmException;		}

		const char* algorithm() const { return reinterpret_cast<const char*>(&m_algorithm[0]); }

	protected:
		mutable Blob m_algorithm;
	};

	// ---------------------------------------------------------------------------
	class CertificateException : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef CertificateException Type;
		using	BaseType::operator<<;

		CertificateException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiCertificateException;		}
	};

	class InvalidCertificateException : public CertificateException
	{
	public:
		typedef CertificateException BaseType;
		typedef InvalidCertificateException Type;
		using	BaseType::operator<<;

		InvalidCertificateException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: CertificateException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiInvalidCertificateException; }
	};

	class CertificateEncodingException : public CertificateException
	{
	public:
		typedef CertificateException BaseType;
		typedef CertificateEncodingException Type;
		using	BaseType::operator<<;

		CertificateEncodingException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: CertificateException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiCertificateEncodingException; }
	};

	class CertificateExpiredException : public CertificateException
	{
	public:
		typedef CertificateException BaseType;
		typedef CertificateExpiredException Type;
		using	BaseType::operator<<;

		CertificateExpiredException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: CertificateException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiCertificateExpiredException; }
	};

	class CertificateNotYetValidException : public CertificateException
	{
	public:
		typedef CertificateException BaseType;
		typedef CertificateNotYetValidException Type;
		using	BaseType::operator<<;

		CertificateNotYetValidException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: CertificateException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiCertificateNotYetValidException; }
	};

	class CertificateParsingException : public CertificateException
	{
	public:
		typedef CertificateException BaseType;
		typedef CertificateParsingException Type;
		using	BaseType::operator<<;

		CertificateParsingException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: CertificateException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiCertificateParsingException; }
	};

	// ---------------------------------------------------------------------------
	class KeyException : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef KeyException Type;
		using	BaseType::operator<<;

		KeyException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiKeyException;				}
	};

	class InvalidKeyException : public KeyException
	{
	public:
		typedef KeyException BaseType;
		typedef InvalidKeyException Type;
		using	BaseType::operator<<;

		InvalidKeyException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: KeyException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiInvalidKeyException;			}
	};

	class KeyManagementException : public KeyException
	{
	public:
		typedef KeyException BaseType;
		typedef KeyManagementException Type;
		using	BaseType::operator<<;

		KeyManagementException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: KeyException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiKeyManagementException;		}
	};

	// ---------------------------------------------------------------------------
	class EACException : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef EACException Type;
		using	BaseType::operator<<;

		EACException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiEACException;				}
	};

	class EACDataException : public EACException
	{
	public:
		typedef EACException BaseType;
		typedef EACDataException Type;
		using	BaseType::operator<<;

		EACDataException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: EACException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiEACDataException;			}
	};

	class EACMRZException : public EACDataException
	{
	public:
		typedef EACDataException BaseType;
		typedef EACMRZException Type;
		using	BaseType::operator<<;

		EACMRZException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: EACDataException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiEACMRZException;				}
	};

	class EACCVCertException : public EACDataException
	{
	public:
		typedef EACDataException BaseType;
		typedef EACCVCertException Type;
		using	BaseType::operator<<;

		EACCVCertException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: EACDataException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiEACCVCertException;			}
	};

	// ---------------------------------------------------------------------------
	class SmartcardException : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef SmartcardException Type;
		using	BaseType::operator<<;

		SmartcardException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiSmartcardException;			}
	};

	class CardRemovedException : public ExceptionType<eiCardRemovedException, CardRemovedException, SmartcardException> { };
	class CardOutOfMemoryException : public ExceptionType<eiCardOutOfMemoryException, CardOutOfMemoryException, SmartcardException> { };
	class CardTransactionException : public ExceptionType<eiCardTransactionException, CardTransactionException, SmartcardException> { };

	class InvalidPinException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef InvalidPinException Type;
		using	BaseType::operator<<;

		InvalidPinException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiInvalidPinException;			}
	};

	class PinLockedException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef PinLockedException Type;
		using	BaseType::operator<<;

		PinLockedException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int GetId() const { return eiPinLockedException;			}
	};

	class PinExpiredException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef PinExpiredException Type;
		using	BaseType::operator<<;

		PinExpiredException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int GetId() const { return eiPinExpiredException;			}
	};

	class PinLenRangeException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef PinLenRangeException Type;
		using	BaseType::operator<<;

		PinLenRangeException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiPinLenRangeException;		}
	};

	class InvalidPinFormatException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef InvalidPinFormatException Type;
		using	BaseType::operator<<;

		InvalidPinFormatException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiInvalidPinFormatException;			}
	};

	class InvalidCRKeyException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef InvalidCRKeyException Type;
		using	BaseType::operator<<;

		InvalidCRKeyException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiInvalidCRKeyException;		}
	};

	class InvalidCardException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef InvalidCardException Type;
		using	BaseType::operator<<;

		InvalidCardException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiInvalidCardException;		}
	};

	class InvalidAuthException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef InvalidAuthException Type;
		using	BaseType::operator<<;

		InvalidAuthException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiInvalidAuthException;		}
	};

	class InvalidAuthObjectException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef InvalidAuthObjectException Type;
		using	BaseType::operator<<;

		InvalidAuthObjectException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiInvalidAuthObjectException;	}
	};

	class AuthProtocolException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef AuthProtocolException Type;
		using	BaseType::operator<<;

		AuthProtocolException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiAuthProtocolException;		}
	};

	//
	// Constraints violations
	class ConstraintsViolationException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef ConstraintsViolationException Type;
		using	BaseType::operator<<;

		ConstraintsViolationException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();				}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);		}
		virtual int   GetId() const { return eiConstraintsViolationException;	}
	};

	class AuthConstraintsViolation
		: public ExceptionType<eiAuthConstraintsViolation, AuthConstraintsViolation, ConstraintsViolationException>
	{ };

	class TokenFileConstraintsViolation
		: public ExceptionType<eiTokenFileConstraintsViolation, TokenFileConstraintsViolation, ConstraintsViolationException>
	{ };

	//
	// Secure Messaging
	class SecureMessagingException : public SmartcardException
	{
	public:
		typedef SmartcardException BaseType;
		typedef SecureMessagingException Type;
		using	BaseType::operator<<;

		SecureMessagingException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SmartcardException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiSecureMessagingException;	}
	};

	class SMWrapException : public SecureMessagingException
	{
	public:
		typedef SecureMessagingException BaseType;
		typedef SMWrapException Type;
		using	BaseType::operator<<;

		SMWrapException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SecureMessagingException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiSMWrapException;				}
	};

	class SMUnwrapException : public SecureMessagingException
	{
	public:
		typedef SecureMessagingException BaseType;
		typedef SMUnwrapException Type;
		using	BaseType::operator<<;

		SMUnwrapException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SecureMessagingException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiSMUnwrapException;			}
	};

	// ---------------------------------------------------------------------------
	class SubsystemException : public LogicalException
	{
	public:
		typedef LogicalException BaseType;
		typedef SubsystemException Type;
		using	BaseType::operator<<;

		SubsystemException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: LogicalException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiSubsystemException;			}
	};

	class NoSuchSubsystemException : public SubsystemException
	{
	public:
		typedef SubsystemException BaseType;
		typedef NoSuchSubsystemException Type;
		using	BaseType::operator<<;

		NoSuchSubsystemException(const char* msg = 0, const char* where = 0, ulong code = 0)
			: SubsystemException(msg, where, code)
		{ }

		virtual Type* Clone() const { return TypedClone<Type>();			}
		virtual void  Throw() const { throw Type(m_what, m_where, m_code);	}
		virtual int   GetId() const { return eiNoSuchSubsystemException;	}
	};

#else

	#define throw(_x)	_exit(_x)

	int Exception(const char* msg = 0, const char* where = 0, ulong code = 0);
		int BadException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	NullPointerException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	OutOfRangeException(const char* msg = 0, const char* where = 0, ulong code = 0);
		int BadCastException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int BadNumericCast(const char* msg = 0, const char* where = 0, ulong code = 0);
		int	RuntimeException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int BadAllocException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int OutOfMemoryException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int NotSupportedException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int NotImplementedException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int NotInitializedException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int AlreadyInitializedException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int InvalidParameterException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int InvalidSessionIdException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int SynchronizationException(const char* msg = 0, const char* where = 0, ulong code = 0);
		int	LogicalException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	ASN1Exception(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	IncompatibleVersionException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	NoSuchDLLException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int NoSuchMethodException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	PasswordException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	ArithmeticException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	MessageDigestException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	PaddingException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	SignatureException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	AlgorithmException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	InvalidAlgorithmParameterException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	NoSuchAlgorithmException(const char* msg = 0, const char* where = 0, const char* algorithm);
			int ArithmeticException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	CertificateException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	CertificateEncodingException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	CertificateExpiredException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	CertificateNotYetValidException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	CertificateParsingException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	KeyException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	InvalidKeyException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int	KeyManagementException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	MessageDigestException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int	PaddingException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int SignatureException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int EACException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int EACDataException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int EACMRZException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int EACCVCertException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int SmartcardException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int CardRemovedException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int CardOutOfMemoryException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int CardTransactionException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int InvalidPinException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int InvalidPinFormatException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int InvalidCardException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int InvalidAuthObjectException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int AuthProtocolException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int ConstraintsViolationException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int AuthConstraintsViolation(const char* msg = 0, const char* where = 0, ulong code = 0);
					int TokenFileConstraintsViolation(const char* msg = 0, const char* where = 0, ulong code = 0);
				int SecureMessagingException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int SMWrapException(const char* msg = 0, const char* where = 0, ulong code = 0);
					int SMUnwrapException(const char* msg = 0, const char* where = 0, ulong code = 0);
			int SubsystemException(const char* msg = 0, const char* where = 0, ulong code = 0);
				int NoSuchSubsystemException(const char* msg = 0, const char* where = 0, ulong code = 0);

#endif	// UNDER_CE_30

} // namespace act

#endif // ACT_Exception_h
