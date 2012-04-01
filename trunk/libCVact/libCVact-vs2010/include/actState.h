//////////////////////////////////////////////////////////////////////////////////
// Name:      actState.h
// Product:   cv act library
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_State_h
#define ACT_State_h

namespace act
{
	const int READY				= 0;
	const int SIGNATURE_OK		= 1;
	const int IS_FINALIZED		= 2;
	const int DECRYPT_ERROR		= 3;
	const int CERTIFICATE_OK	= 4;
	const int CERTIFICATE_ERROR	= 5;
	const int VERIFY_ERROR		= 6;

} // namspace act

#endif // ACT_State_h
