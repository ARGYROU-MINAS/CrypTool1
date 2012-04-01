// ---------------------------------------------------------------------------
// Name:      actTokenConfig.h
// Product:   cv act library
// Purpose:   Declares all availabl param_id's for ITokenCofing.
//            
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  05/07/2009
// ---------------------------------------------------------------------------

#ifndef ACT_TokenConfig_h
#define ACT_TokenConfig_h

#include "actMode.h"
#include "actIParam.h"

namespace act
{
	// according to ISO 24727-3, definition of supported Data Set's
	enum DataSetList
	{
		DATA_SET_NONE						= 0,
		DATA_SET_PUBLIC_DATA				= (1 << 0),
		DATA_SET_PRIVATE_DATA				= (1 << 1),
		DATA_SET_CERTIFICATES				= (1 << 2),
		DATA_SET_USEFUL_CERTIFICATES		= (1 << 3),
		DATA_SET_TRUSTED_CERTIFICATES		= (1 << 4),
		DATA_SET_TRUSTED_PUBLIC_KEYS		= (1 << 5),
		//
		// ...
		DATA_SET_NEXT						= (1 << 6),
		DATA_SET_MASK						= DATA_SET_NEXT - 1,
		DATA_SET_ALL						= PARAM_INVALID_VALUE,
	};

	enum ObjectTypeList
	{
		OBJECT_TYPE_NONE					= 0,
		OBJECT_TYPE_KEY_DES					= (1 << 0),
		OBJECT_TYPE_KEY_2DES				= (1 << 1),
		OBJECT_TYPE_KEY_3DES				= (1 << 2),
		OBJECT_TYPE_KEY_AES					= (1 << 3),
		OBJECT_TYPE_KEY_RSA					= (1 << 4),
		OBJECT_TYPE_KEY_DSA					= (1 << 5),
		OBJECT_TYPE_KEY_DH					= (1 << 6),
		OBJECT_TYPE_KEY_ECC					= (1 << 7),
		OBJECT_TYPE_DATA					= (1 << 8),
		OBJECT_TYPE_CERTIFICATE				= (1 << 9),
		OBJECT_TYPE_USEFUL_CERTIFICATE		= (1 << 10),
		OBJECT_TYPE_TRUSTED_CERTIFICATE		= (1 << 11),
		OBJECT_TYPE_TRUSTED_PUBLIC_KEY		= (1 << 12),
		//
		// Mark an object as private
		OBJECT_TYPE_PRVIVATE				= (1 << 13),
		//
		// ...
		OBJECT_TYPE_NEXT					= (1 << 14),
		OBJECT_TYPE_MASK					= OBJECT_TYPE_NEXT - 1,
		OBJECT_TYPE_ALL						= PARAM_INVALID_VALUE,
	};

	enum ObjectAttributeList
	{
		OBJECT_ATTR_LABEL_P					= OBJECT_TYPE_NEXT,
		OBJECT_ATTR_LABEL_P_PUB				= OBJECT_ATTR_LABEL_P,
		OBJECT_ATTR_LABEL_P_PRV				= OBJECT_ATTR_LABEL_P | OBJECT_TYPE_PRVIVATE,
	};

	enum
	{
		TC_TYPE								= TOKEN_CONFIG,
		TC_HAS_TOKEN_CAPABILITIES,
		TC_HAS_WRITABLE_AODF,
		TC_IS_MOC_ENABLED,
		TC_IS_MINIDRIVER_ENABLED,
		TC_IS_PROFILE_ERASABLE,
		TC_PINPAD_CHAR,
		TC_DATA_SET_LIST,
		TC_OBJECT_TYPE_LIST,

		TC_DISABLE_CHECK_X509_CERTIFICATE,	// set to PARAM_TRUE to disable verfication during token read/write.
		TC_DISABLE_CHECK_CV_CERTIFICATE,

		//
		// Object naming - Label Prefix
		TC_LABEL_P_PRV_DES					= OBJECT_ATTR_LABEL_P_PRV + OBJECT_TYPE_KEY_DES,
		TC_LABEL_P_PRV_2DES					= OBJECT_ATTR_LABEL_P_PRV + OBJECT_TYPE_KEY_2DES,
		TC_LABEL_P_PRV_3DES					= OBJECT_ATTR_LABEL_P_PRV + OBJECT_TYPE_KEY_3DES,
		TC_LABEL_P_PRV_AES					= OBJECT_ATTR_LABEL_P_PRV + OBJECT_TYPE_KEY_AES,
		TC_LABEL_P_PUB_RSA					= OBJECT_ATTR_LABEL_P_PUB + OBJECT_TYPE_KEY_RSA,
		TC_LABEL_P_PRV_RSA					= OBJECT_ATTR_LABEL_P_PRV + OBJECT_TYPE_KEY_RSA,
		TC_LABEL_P_PUB_ECC					= OBJECT_ATTR_LABEL_P_PUB + OBJECT_TYPE_KEY_ECC,
		TC_LABEL_P_PRV_ECC					= OBJECT_ATTR_LABEL_P_PRV + OBJECT_TYPE_KEY_ECC,
		TC_LABEL_P_PUB_DATA					= OBJECT_ATTR_LABEL_P_PUB + OBJECT_TYPE_DATA,
		TC_LABEL_P_PRV_DATA					= OBJECT_ATTR_LABEL_P_PRV + OBJECT_TYPE_DATA,
		TC_LABEL_P_PUB_CERTIFICATE			= OBJECT_ATTR_LABEL_P_PUB + OBJECT_TYPE_CERTIFICATE,
		TC_LABEL_P_PUB_USEFUL_CERTIFICATE	= OBJECT_ATTR_LABEL_P_PUB + OBJECT_TYPE_USEFUL_CERTIFICATE,
		TC_LABEL_P_PUB_TRUSTED_CERTIFICATE	= OBJECT_ATTR_LABEL_P_PUB + OBJECT_TYPE_TRUSTED_CERTIFICATE,
		TC_LABEL_P_PUB_TRUSTED_PUBLIC_KEY	= OBJECT_ATTR_LABEL_P_PUB + OBJECT_TYPE_TRUSTED_PUBLIC_KEY,
	};

} // namespace act

#endif // ACT_TokenConfig_h
