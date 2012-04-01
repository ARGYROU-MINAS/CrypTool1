// ---------------------------------------------------------------------------
// Name:      actTokenBase.h
// Product:   cv act library
// Purpose:   Declares common token enums and constants.
//
// Copyright: (c) 2010 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  03/24/2010
// ---------------------------------------------------------------------------

#ifndef ACT_TokenBase_h
#define ACT_TokenBase_h

#include "actBasics.h"

namespace act
{
	enum TokenError
	{
		TOKEN_SUCCESS					=  0,
		TOKEN_FUNCTION_NOT_SUPPORTED	= -1,
		TOKEN_FUNCTION_FAILED			= -2,
		TOKEN_LOCKED					= -3
	};

	enum TokenType
	{
		TOKEN_NOT_INITIALIZED			= -1,
		TOKEN_UNKNOWN					= 0x0000,

		TOKEN_RSA						= 0x0001,
		TOKEN_DSA						= 0x0002,
		TOKEN_DH						= 0x0004,
		TOKEN_ECDSA						= 0x0008,
		TOKEN_ECDH						= 0x0010,
		TOKEN_SECRET					= 0x0080,

		TOKEN_BAC						= 0x0100,
		TOKEN_EAC						= 0x0200,
		TOKEN_EPA						= 0x0400,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(TokenType);

	enum TokenStatusCode
	{
		TOKEN_EMPTY						= 0x0000,
		TOKEN_INITIALIZED				= 0x0001,
		TOKEN_PERSONALIZED				= 0x0002
	};

	enum TokenReset
	{
		TOKEN_RESET_LOGOUT				= 0x3F0C,
		TOKEN_RESET_CARD				= 0x95A6,
		TOKEN_RESET_DEFAULT				= TOKEN_RESET_LOGOUT,
	};

	enum ProfileType
	{
		PROFILE_EMPTY					= 0x00,
		PROFILE_CV						= 0x01,
		PROFILE_CNS						= 0x02,
		PROFILE_GDO						= 0x03,
		PROFILE_CVEC					= 0x04,
		PROFILE_SIGG					= 0x05,
		PROFILE_JC						= 0x06,
		PROFILE_MICARDOEC				= 0x07,
		PROFILE_SIGNTRUST				= 0x08,
		PROFILE_NETKEY					= 0x09,
		PROFILE_CVMOC					= 0x0a,

		PROFILE_PKCS15					= 0x0f,
		PROFILE_PKCS15_mEAC				= 0x10,		// includes PACE-Pin's
		PROFILE_PKCS15_mEAC_TA			= 0x11,		// includes PACE-Pin's and TA-IS, TA-ST, TA-AT

		PROFILE_BAC						= 0x80,
		PROFILE_EAC						= 0x81,
		PROFILE_EAC201					= 0x82,
		PROFILE_EPA						= 0x83,

		PROFILE_PKCS11					= 0xa0,
		PROFILE_CSP						= 0xa1,
		PROFILE_MD						= 0xa2,

		PROFILE_ANY						= 0xfe,
		PROFILE_UNKNOWN					= 0xff
	};

	// usage of key, pin
	enum KeyUsage
	{
		KEY_EMPTY						= 0x0000,
		SIGN_DATA						= 0x0001,
		DEC_DATA						= 0x0002,
		AGREE_KEY						= 0x0004,
		AUTH_DATA						= 0x0008,
		BLOCKCIPHER_KEY					= 0x0010,
		VERIFY_DATA						= 0x0020,
		ENC_DATA						= 0x0040,
		UNLOCK_PIN						= 0x0100,
		UPDATE_BINARY					= 0x0200,
		DELETE_BINARY					= 0x0400,
		ALL_USAGE						= 0xffff,

		// custom usage
		SIGN_HASH						= 0x00010000,
		CUSTOM_USAGE_MASK				= 0xffff0000,

		// combined usage
		ENC_DEC_DATA					= DEC_DATA | ENC_DATA,
		SIGN_DEC_DATA					= DEC_DATA | SIGN_DATA,
		SIGN_HASH_DATA					= SIGN_HASH | SIGN_DATA,
	};

	enum KeyType
	{	// NOTE: Never change (!), used for serialization.
		KEY_UNKNOWN						= 0xffff,

		KEY_RSA							= 0x0000,
		KEY_DSA							= 0x0001,
		KEY_DH							= 0x0002,
		KEY_ECDSA						= 0x0003,
		KEY_ECDH						= 0x0004,

		KEY_SECRET						= 0x0010,
		KEY_DES							= 0x0001 + KEY_SECRET,
		KEY_2DES						= 0x0002 + KEY_SECRET,
		KEY_3DES						= 0x0003 + KEY_SECRET,
		KEY_AES							= 0x0004 + KEY_SECRET,

		KEY_TYPE_MASK					= 0x001f
	};

	enum CertificateType
	{	// NOTE: Never change (!), used for serialization.
		CERT_UNKNOWN					= 0xffff,

		CERT_X509						= 0x0000,
		CERT_CV							= 0x0001
	};

	enum CertificateUsage
	{
		EMPTY_CERT						= 0x0000, 
		SIGN_CERT						= 0x0001, 
		DEC_CERT						= 0x0002, 
		ROOT_CERT						= 0x0004, 
		AUTH_CERT						= 0x0008, 
		CA_CERT							= 0x0010,
		SMARTCARD_LOGON_CERT			= 0x0100,	// lib version >= 1.5
		UNSPECIFIED_CERT				= 0xffff
	};

	enum SecStatus
	{
		SS_INVALID						= 0x0000,
		SS_AUTHENTICATED				= 0x0001,
		SS_UNKNOWN						= 0xffff,
	};

	enum AUTH_OBJ_TYPE
	{
		AUTH_OBJ_PIN					= 0xff,	// -1
		AUTH_OBJ_BIOMETRIC				= 0xfe,	// -2
	};

	typedef ulong	IDType;
	typedef ushort	FIDType;

	const IDType	ID_INVALID			=  0;
	const FIDType	FID_INVALID			=  0;
	const FIDType	FID_NOT_INITIALIZED	= ~0;

	const int		RC_UNKNOWN			= -1;

#	include "actPackOn.h"

	//
	// FileInfo
	struct FileInfo
	{
		explicit FileInfo(FIDType val_fid = FID_INVALID, IDType val_rec_nr = ID_INVALID)
			: fid(val_fid)
			, rec_nr(val_rec_nr)
		{ }

		FIDType	fid;
		IDType	rec_nr;
	};

	inline bool Equals(const FileInfo& left, const FileInfo& right)
	{
		return left.fid == right.fid
			&& left.rec_nr == right.rec_nr;
	}

	// LengthInfo
	struct LengthInfo
	{
		LengthInfo(ulong minLen_ = 0, ulong maxLen_ = 0, ulong storedLen_ = 0)
			: minLen(minLen_)
			, maxLen(maxLen_)
			, storedLen(storedLen_)
		{ }

		void swap(LengthInfo& other)
		{
			ulong val;
			val = other.minLen;    other.minLen = minLen;       minLen = val;
			val = other.maxLen;    other.maxLen = maxLen;       maxLen = val;
			val = other.storedLen; other.storedLen = storedLen; storedLen = val;
		}

		ulong minLen;
		ulong maxLen;
		ulong storedLen;
	};

#	include "actPackOff.h"

} // namespace act

#endif // ACT_TokenBase_h
