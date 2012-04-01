//////////////////////////////////////////////////////////////////////////
// Name:      actDebug.h
// Product:   cv act library
// Purpose:   Integration of globally available debug macros and functions
//
// Copyright: (c) 2005 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  12/15/2005
//////////////////////////////////////////////////////////////////////////

#ifndef ACT_Debug_h
#define ACT_Debug_h

#include "actEnv.h"
#include "actBasics.h"
#include "actLocation.h"

#include <cstdarg>

#ifdef _DEBUG
#	define		ACT_DEBUG								_DEBUG
#endif

//
// ACT_NOOP use for semicolon terminated non operating macros.
#ifdef ACT_MSC_VER
#	if ACT_MSC_VER >= 1210
#		define	ACT_NOOP								__noop
#	else
#		define	ACT_NOOP								((void) 0)
#	endif
// MSVC specific
#	if !defined(ACT_DEBUG_NEW)
#		if defined(ACT_DEBUG) && !defined(ACT_WIN32_WCE)
#			include <crtdbg.h>
#			define	ACT_DEBUG_MEMORY_TYPE				0xAFEC
#			define	ACT_DEBUG_MEMORY_BLOCK				((ACT_DEBUG_MEMORY_TYPE << 16) | _CLIENT_BLOCK)
#			define	ACT_DEBUG_NEW						new(ACT_DEBUG_MEMORY_BLOCK, __FILE__, __LINE__)
#		else
#			define	ACT_DEBUG_NEW						new
#		endif
#	endif
#else
#	define		ACT_NOOP								((void) 0)
#	define		ACT_DEBUG_NEW							new
#endif

//
// Declare all debug macros for release builds.
#ifdef ACT_DEBUG
#	ifdef ACT_UNDER_CE
#		define	ACT_ASSERT								ACT_NOOP
#		define	ACT_ASSERT_ALWAYS(msg, line, file)		ACT_NOOP
#	endif
#	define		ACT_DEBUG_PARAM(p)						p
#	define		ACT_DEBUG_SOURCE()						act::FileAndLine(__FILE__, __LINE__)
#	define		ACT_NOT_IMPLEMENTED(msg, where)			throw act::NotImplementedException(msg, where) << ACT_DEBUG_SOURCE()
#else
#	define		ACT_DEBUG_SOURCE()						act::FileAndLine()
#	define		ACT_NOT_IMPLEMENTED(msg, where)			throw act::NotImplementedException(msg, where)
#	if defined(ACT_MSC_VER) && ACT_MSC_VER < 1210
#		define	ACT_DEBUG_PARAM(p)						p
#		define	ACT_TRACE								ACT_NOOP
#		define	ACT_TRACELOG							ACT_NOOP
#		define	ACT_TRACELOC							ACT_NOOP
#		define	ACT_ASSERT								ACT_NOOP
#	else
#		define	ACT_DEBUG_PARAM(p)
#		define	ACT_TRACE(...)							ACT_NOOP
#		define	ACT_TRACELOG(...)						ACT_NOOP
#		define	ACT_TRACELOC(...)						ACT_NOOP
#		define	ACT_ASSERT(e)							ACT_NOOP
#	endif
#	define		ACT_ASSERT_ALWAYS(msg, line, file)		ACT_NOOP
#	define		ACT_ASSERT_ON_THROW(msg)				ACT_NOOP
#	define		ACT_ASSERT_ON_THROW_NAMED(name, msg)	ACT_NOOP
#endif // _DEBUG

//
// ACT_ASSERT
#ifndef ACT_ASSERT
#	if defined(ACT_MSC)
#		include <crtdbg.h>
#		define	ACT_ASSERT								_ASSERTE
#	else
#		include <assert.h>
#		define	ACT_ASSERT								assert
#	endif
#endif // ACT_ASSERT

//
// ACT_ASSERT_ALWAYS
#ifndef ACT_ASSERT_ALWAYS
#	if defined(ACT_MSC)
#		include <crtdbg.h>
#		define	ACT_ASSERT_ALWAYS(msg, file, line)		_RPT_BASE((_CRT_ASSERT, file, line, 0, msg))
#	else
#		include <assert.h>
#		define	ACT_ASSERT_ALWAYS(msg, file, line)		assert(f == 0)
#	endif
#endif // ACT_ASSERT_ALWAYS

//
// ACT_ENABLE_TRACE
#ifdef ACT_ENABLE_TRACE
#	ifdef		ACT_TRACE
#		undef	ACT_TRACE
#	endif
#	ifdef		ACT_TRACELOG
#		undef	ACT_TRACELOG
#	endif
#	ifdef		ACT_TRACELOC
#		undef	ACT_TRACELOC
#	endif
#endif // ACT_ENABLE_TRACE

//
// ACT_TRACE
#ifndef ACT_TRACE
#	if !defined(ACT_POSIX) \
	&& !defined(ACT_WIN32) \
	&& !defined(ACT_WIN32_WCE)
#		error	act::Trace not implemented for this platform
#	endif
#	ifndef		ACT_TRACE_BUFFER						// default trace output buffer size
#		define	ACT_TRACE_BUFFER						1024
#	endif
#	ifndef		ACT_ASSERT_ON_THROW
#		define	ACT_ASSERT_ON_THROW(msg)				ACT_ASSERT_ON_THROW_NAMED(act_dbg_check_for_nothrow__, msg)
#		define	ACT_ASSERT_ON_THROW_NAMED(name, msg)	act::CheckForNoThrow name(msg, __FILE__, __LINE__)
#	endif
#	define		ACT_TRACE								act::TraceFileAndLine(__FILE__, __LINE__)
#	define		ACT_TRACELOG							act::TraceFileAndLine()
#	define		ACT_TRACELOC							act::TraceFileAndLine
#endif // ACT_TRACE

namespace act
{
	class Exception;

	struct TraceContext
	{
		ushort		flags;
		ushort		indent;
		ulong		sid;
		ulong		pid;
		ulong		tid;
		const char*	name;
		char*		szBuf;
		size_t		leBuf;
		void*		owner;
		void		(*notify)(const TraceContext*);
	};

	class Trace
	{
	public:
		Trace();

		Trace& operator()(TraceContext* context);
		void ACT_CDECL operator()(ACT_PRINTF_FORMAT_STRING const char* format, va_list ptr,
				const char* file = 0, int line = 0) const;

		typedef TraceContext*	(*ContextProvider)();
		static ContextProvider	SetContextProvider(ContextProvider provider);

	private:
		TraceContext* mContext;
	};

	class TraceFileAndLine : public FileAndLine
	{
	public:
		TraceFileAndLine() { }
		TraceFileAndLine(const FileAndLine& fl) : FileAndLine(fl) { }
		TraceFileAndLine(const char * file, int line) : FileAndLine(file, line) { }

		inline void setFileAndLine(const FileAndLine* fl)
		{
			if(fl != 0) *static_cast<FileAndLine*>(this) = *fl;
		}

		inline TraceFileAndLine& operator<<(const FileAndLine& fl)
		{
			*static_cast<FileAndLine*>(this) = fl;
			return *this;
		}

		// default va_list based trace.
		void operator()(ACT_PRINTF_FORMAT_STRING const char* format, ...);
		void operator()(TraceContext* context, ACT_PRINTF_FORMAT_STRING const char* format, ...);

		// exception trace.
		void operator()(const Exception& e);
		void operator()(const Exception& e, const char* where);
	};

	class CheckForNoThrow : public FileAndLine
	{
	private:
		CheckForNoThrow(const CheckForNoThrow&) throw();
		CheckForNoThrow& operator=(const CheckForNoThrow&) throw();
		
	public:
		CheckForNoThrow(const char* msg, const char* file = 0, int line = 0);
		~CheckForNoThrow();

	private:
		const char* m_msg;
		const bool	m_state;
	};

}	// namespace act

#endif // ACT_Debug_h
