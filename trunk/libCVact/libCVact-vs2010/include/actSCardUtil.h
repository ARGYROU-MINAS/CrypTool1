//////////////////////////////////////////////////////////////////////////////////
// Name:      actSCardUtil.h
// Product:   cv act library
// Purpose:   useful global functions
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef actSCardUtil_h
#define actSCardUtil_h

namespace act
{
	// ---------------------------------------------------------------------------
	template<class BlobT>
	inline BlobT short2blob(unsigned short n)
	{
		byte data[2] = { byte((n >> 8) & 0xff), byte(n & 0xff) };
		return BlobT(&data[0], &data[0] + sizeof(data));
	}

} // namespace act

#endif // actSCardUtil_h
