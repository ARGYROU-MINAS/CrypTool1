//////////////////////////////////////////////////////////////////////////
// Name:      actEnv.h
// Product:   cv act library
// Purpose:   Operating System environment
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  04/23/2009
//////////////////////////////////////////////////////////////////////////

#ifndef ACT_Env_h
#define ACT_Env_h

// 64Bit detection ...
#if		defined(_WIN64) || \
		defined(__LP64__) || \
		defined(__alpha__) || \
		defined(__ia64__) || \
		defined(__ppc64__) || \
		defined(__s390x__) || \
		defined(__x86_64__)
#		define	ACT_64
#endif

// cygwin
#if		defined(__CYGWIN__)
#		define  ACT_CYGWIN
#endif

// mingw
#if		defined(__MINGW32__)
#		define	ACT_MINGW
#endif

// Platform detection ...
#if		defined(ACT_WIN32) || \
		defined(ACT_POSIX) || \
		defined(ACT_SOLARIS) || \
		defined(ACT_MACOSX) || \
		defined(ACT_IOS) || \
		defined(ACT_WIN32_WCE)
//		do nothing

#elif	defined(_WIN32_WCE) && _WIN32_WCE >= 0x500
#		define  ACT_WIN32
#		define  ACT_WIN32_WCE

#elif	defined(WIN32) && !defined(__CYGWIN__)
#		define  ACT_WIN32

#elif	defined(_MSC_VER) || \
		defined(__BORLANDC__) || \
		defined(__BCPLUSPLUS__) || \
		defined(__MINGW32__)
#		define  ACT_WIN32

#elif	defined(__linux__) || \
		defined(__CYGWIN__) || \
		defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || \
		defined(__hpux) || \
		defined(__sgi)
#		define  ACT_POSIX

#elif	defined(_POSIX_SOURCE) || \
		defined(_XOPEN_SOURCE) 
#		define  ACT_POSIX

#elif	defined(__sun)
#		define	ACT_POSIX
#		define  ACT_SOLARIS

#elif	defined(__APPLE__) && defined(__MACH__)
#		define	ACT_POSIX
#		define  ACT_MACOSX

#else
#		error unable to deteced system environment

#endif

enum	timeout_t
		{
			WAIT_DONT_WAIT					=  0,
			WAIT_INFINITE					= -1,
			WAIT_FOR_REFRESH				=  1000,
			WAIT_FOR_SERVICE_START			=  1000,
			WAIT_FOR_THREAD_START			=  50,
			WAIT_FOR_THREAD_STOP			=  100,
		};

//
// Compiler definition
#if defined(_MSC_VER)
#	define		ACT_MSC
#	define		ACT_MSC_VER					_MSC_VER
#	if(_MSC_FULL_VER >= 140050320)
#		define	ACT_DEPRECATED(msg)			__declspec(deprecated("is deprecated: " msg))
#	else
#		define	ACT_DEPRECATED(msg)			__declspec(deprecated)
#	endif
#	define		ACT_STDEXT_NS				std
#	define		ACT_STDEXT_INC(file)		<file>

#elif defined(__GNUC__)
#	define		ACT_GCC
#	if(__GNUC__ > 3) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1)
#		define	ACT_DEPRECATED(msg)			__attribute__((__deprecated__))
#	endif
#	define		ACT_STDEXT_NS				__gnu_cxx
#	define		ACT_STDEXT_INC(file)		<ext/file>

#endif

#if !defined(ACT_DEPRECATED)
#	 define		ACT_DEPRECATED(msg)
#endif

//
// Calling conventions
#if defined(ACT_MSC)
#	define		ACT_CDECL					__cdecl
#	define		ACT_STDCALL					__stdcall

#else
#	define		ACT_CDECL
#	define		ACT_STDCALL

#endif

//
// Markers for API semantics, default enabled
#define			ACT_SAL_ENABLED				1
#define			ACT_SAL_DISABLED			0
#ifndef			ACT_SAL_DEFAULT
#	define		ACT_SAL_DEFAULT				ACT_SAL_ENABLED
#endif
#if				ACT_SAL_DEFAULT != ACT_SAL_ENABLED && \
				ACT_SAL_DEFAULT != ACT_SAL_DISABLED
#	undef		ACT_SAL_DEFAULT
#	define		ACT_SAL_DEFAULT				ACT_SAL_DISABLED
#endif
#if	defined(ACT_MSC_VER) && ACT_MSC_VER >= 1400
#	if !defined(_USE_ATTRIBUTES_FOR_SAL)
#		define	_USE_ATTRIBUTES_FOR_SAL		ACT_SAL_DEFAULT
#	endif
#	include		<sal.h>
#	define		ACT_SAL						_USE_ATTRIBUTES_FOR_SAL
#	if  defined(ACT_SAL)
#		pragma	warning						(disable : 6011 6246)
#	endif
#	define		ACT_IN						__in
#	define		ACT_OUT						__out
#	define		ACT_INOUT					__inout
#	define		ACT_IN_OPT					__in_opt
#	define		ACT_OUT_OPT					__out_opt
#	define		ACT_INOUT_OPT				__inout_opt
#	define		ACT_IN_BC(size)				__in_bcount(size)
#	define		ACT_IN_BC_OPT(size)			__in_bcount_opt(size)
#	define		ACT_IN_EC_OPT(size)			__in_ecount_opt(size)
#	define		ACT_OUT_BC(size)			__out_bcount(size)
#	define		ACT_OUT_BC_OPT(size)		__out_bcount_opt(size)
#	define		ACT_OUT_EC_OPT(size)		__out_ecount_opt(size)
#	define		ACT_INOUT_BC(size)			__inout_bcount(size)
#	define		ACT_INOUT_BC_OPT(size)		__inout_bcount_opt(size)
#	define		ACT_INOUT_EC_OPT(size)		__inout_ecount_opt(size)
#	define		ACT_RESERVED				__reserved
#	define		ACT_NULL_TERMINATED			__nullnullterminated
#	if defined(_Printf_format_string_)
#		define	ACT_PRINTF_FORMAT_STRING	_Printf_format_string_
#	else
#		define	ACT_PRINTF_FORMAT_STRING	__format_string
#	endif
#else
#	define		ACT_SAL						ACT_SAL_DISABLED
#	define		ACT_IN
#	define		ACT_OUT
#	define		ACT_INOUT
#	define		ACT_IN_OPT
#	define		ACT_OUT_OPT
#	define		ACT_INOUT_OPT
#	define		ACT_IN_BC(size)
#	define		ACT_IN_BC_OPT(size)
#	define		ACT_IN_EC_OPT(size)
#	define		ACT_OUT_BC(size)
#	define		ACT_OUT_BC_OPT(size)
#	define		ACT_OUT_EC_OPT(size)
#	define		ACT_INOUT_BC(size)
#	define		ACT_INOUT_BC_OPT(size)
#	define		ACT_INOUT_EC_OPT(size)
#	define		ACT_RESERVED
#	define		ACT_NULL_TERMINATED
#	define		ACT_PRINTF_FORMAT_STRING
#endif

//
// DLL/Shared Object symbol export/import attribte
#if defined(ACT_MSC)
#	define		ACT_DYNLIB_EXPORT			_declspec(dllexport)
#	define		ACT_DYNLIB_IMPORT			_declspec(dllimport)

#elif defined(ACT_GCC) && !defined(ACT_MINGW)
#	define		ACT_DYNLIB_EXPORT			__attribute__((visibility("default")))
#	define		ACT_DYNLIB_IMPORT

#else
#	define		ACT_DYNLIB_EXPORT
#	define		ACT_DYNLIB_IMPORT

#endif

#if  defined(__cplusplus)
#if !defined(ACT_DEFINE_ENUM_FLAG_OPERATORS)
//
// Origin	: winnt.h
// Name		: DEFINE_ENUM_FLAG_OPERATORS
// Since	: Microsoft Windows SDK for Windows 7
//
// Define operator overloads to enable bit operations on enum values that are 
// used to define flags. Use ACT_DEFINE_ENUM_FLAG_OPERATORS(YOUR_TYPE) to enable
// these operators on YOUR_TYPE.
#		define	ACT_DEFINE_ENUM_FLAG_OPERATORS(enum_t) \
		extern "C++" \
		{ \
			inline enum_t  operator |  (enum_t  a, enum_t b) { return  enum_t(((int) a)    |  ((int) b)); } \
			inline enum_t& operator |= (enum_t& a, enum_t b) { return (enum_t&)(((int&) a) |= ((int) b)); } \
			inline enum_t  operator &  (enum_t  a, enum_t b) { return  enum_t(((int) a)    &  ((int) b)); } \
			inline enum_t& operator &= (enum_t& a, enum_t b) { return (enum_t&)(((int&) a) &= ((int) b)); } \
			inline enum_t  operator ^  (enum_t  a, enum_t b) { return  enum_t(((int) a)    ^  ((int) b)); } \
			inline enum_t& operator ^= (enum_t& a, enum_t b) { return (enum_t&)(((int&) a) ^= ((int) b)); } \
			inline enum_t  operator ~  (enum_t  a) { return  enum_t(~((int) a)); } \
		}
#	endif

#else
#	if !defined(ACT_DEFINE_ENUM_FLAG_OPERATORS)
#		define	ACT_DEFINE_ENUM_FLAG_OPERATORS(enum_t)
#	endif

#endif	// __cplusplus
#endif	// ACT_Env_h
