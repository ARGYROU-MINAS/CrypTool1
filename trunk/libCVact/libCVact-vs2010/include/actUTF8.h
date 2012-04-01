//////////////////////////////////////////////////////////////////////////////////
// Name:      actUTF8.h
// Product:   cv act library
// Purpose:   UTF8 conversion functions
//
// Copyright: (c) 2000-2011 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_UTF8_h
#define ACT_UTF8_h

#include "actBlob.h"

#include <string>

namespace act
{
#	if defined(__GNUC__) && (__GNUC__ < 4)
		typedef std::basic_string<wchar_t> wstring;
#	else
		using std::wstring;
#	endif

	bool wstr2utf8(const wchar_t* str, std::string& utf8);

	bool utf82wstr(const char* utf8, wstring& wstr);
	bool utf82wstr(Blob::const_iterator utf8, const Blob::const_iterator& end, wstring& wstr);

} //namespace act

#endif // ACT_UTF8_h
