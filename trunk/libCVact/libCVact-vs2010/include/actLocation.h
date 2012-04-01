// ---------------------------------------------------------------------------
// Name:      actLocation.h
// Product:   cv act library
// Purpose:   Location provides basic info where (file, line) something ...
//
// Copyright: (c) 2011 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  12/08/2011
// ---------------------------------------------------------------------------

#ifndef ACT_Location_h
#define ACT_Location_h

namespace act
{
	// ---------------------------------------------------------------------------
	class FileAndLine
	{
	public:
		FileAndLine(const char* file = 0, int line = 0)
			: m_line(line)
			, m_file(file)
		{ }

		FileAndLine(const FileAndLine& other)
			: m_line(other.m_line)
			, m_file(other.m_file)
		{ }

		int         line() const { return m_line; }
		const char* file() const { return m_file; }

		// assignment operators.
		FileAndLine& operator=(const FileAndLine& other)
		{
			m_line = other.m_line;
			m_file = other.m_file;
			return *this;
		}
		
	private:
		int			m_line;
		const char* m_file;
	};

	// ---------------------------------------------------------------------------
	template<typename SourceT = void>
	class Location : public FileAndLine
	{
	public:
		typedef SourceT		source_type;
		typedef SourceT*	source_pointer;

		Location(const char* where, const char* file = 0, int line = 0)
			: FileAndLine(file, line)
			, m_where(where)
			, m_source(0)
		{ }

		Location(const char* where, const FileAndLine& fl)
			: FileAndLine(fl)
			, m_where(where)
			, m_source(0)
		{ }

		Location(const Location& other)
			: FileAndLine(other)
			, m_where(other.m_where)
			, m_source(other.m_source)
		{ }

		const char*		where()  const	{ return m_where;	}
		source_pointer	source() const	{ return m_source;	}
		void source(source_pointer sp)	{ m_source = sp;	}

		// conversion operators.
		operator const char*()   const	{ return m_where;	}

		// assignment operators.
		Location& operator=(const Location& other)
		{
			*static_cast<FileAndLine*>(this) = other;
			m_source = other.m_source;
			m_where = other.m_where;
			return *this;
		}

	private:
		const char*		m_where;
		source_pointer	m_source;
	};

}	// namespace act
#	if defined(ACT_DEBUG)
#		define	 LOCATION_FROM_HERE(where)				::act::Location<void>(where, __FILE__, __LINE__)
#		define	 LOCATION_FROM_HERE_WITH(where, type)	::act::Location<type>(where, __FILE__, __LINE__)
#	else
#		define	 LOCATION_FROM_HERE(where)				::act::Location<void>(where, 0, 0)
#		define	 LOCATION_FROM_HERE_WITH(where, type)	::act::Location<type>(where, 0, 0)
#	endif
#	define BOOST_LOCATION_FROM_HERE_WITH(type)			LOCATION_FROM_HERE(BOOST_CURRENT_FUNCTION, type)
#	define BOOST_LOCATION_FROM_HERE						LOCATION_FROM_HERE(BOOST_CURRENT_FUNCTION)
#endif	// ACT_Location_h
