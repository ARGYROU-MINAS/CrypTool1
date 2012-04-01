// ---------------------------------------------------------------------------
// Name:      actITokenPIN.h
// Product:   cv act library
// Purpose:   The class ITokenPIN defines the interfaces of the PIN operations
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  04/05/2002
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenPIN_h
#define ACT_ITokenPIN_h

#include "actBasics.h"
#include "actDate.h"
#include "actBlob.h"

#include "actITokenAuth.h"
#include "actITokenFileOwner.h"
#include "actIRefCounted.h"

#include "actTokenBase.h"

namespace act
{
	enum PINType
	{
		UNKNOWN_PIN				= 0x0000,
		SO_PIN					= 0x0001, 
		USER_PIN				= 0x0002,
		UNBLOCK_PIN				= 0x0003,

		PIN_MASK				= 0x000F, 

		EXAUTH_PIN				= 0x0010,
		BIOMETRIC_PIN			= 0x0020,
		CERTBASED_PIN			= 0x0040,

		BAC_PIN					= 0x0100,
		ICAO_PIN				= 0x0200,

		EAC_PACE_PIN			= 0x0400,
		EAC_TA_PIN				= 0x0800,
		EAC_CA_PIN				= 0x1000,

		PIN_TYPE_MASK			= 0x7fff,

		AUTHENTICATED_PIN		= 0x8000,	// Current authenticated PIN

		// combined types
		EXAUTH_SO_PIN			= EXAUTH_PIN | SO_PIN,
		EXAUTH_UNBLOCK_PIN		= EXAUTH_PIN | UNBLOCK_PIN,

		BIOMETRIC_USER_PIN		= BIOMETRIC_PIN | USER_PIN,
		BIOMETRIC_SO_PIN		= BIOMETRIC_PIN | SO_PIN,

		EAC_PACE_UNKNOWN_PIN	= EAC_PACE_PIN | UNKNOWN_PIN,
		EAC_PACE_SO_PIN			= EAC_PACE_PIN | SO_PIN,
		EAC_PACE_USER_PIN		= EAC_PACE_PIN | USER_PIN,
		EAC_PACE_UNBLOCK_PIN	= EAC_PACE_PIN | UNBLOCK_PIN,

		EAC_TA_UNKNOWN_PIN		= EAC_TA_PIN | UNKNOWN_PIN,
		EAC_TA_USER_PIN			= EAC_TA_PIN | USER_PIN,

		EAC_CA_UNKNOWN_PIN		= EAC_CA_PIN | UNKNOWN_PIN,
		EAC_CA_USER_PIN			= EAC_CA_PIN | USER_PIN,
	};

	enum PINFlags
	{
		PIN_INITIALIZED			= (1 <<  0),
		PIN_IS_LOCAL			= (1 <<  1),
		PIN_CASE_SENSITIVE		= (1 <<  2),
		PIN_CHANGE_DISABLED		= (1 <<  3),
		PIN_UNBLOCK_DISABLED	= (1 <<  4),
		PIN_DISABLE_ALLOWED		= (1 <<  5),
		PIN_NEEDS_PADDING		= (1 <<  6),
		PIN_NEEDS_UPDATE		= (1 <<  7),
		PIN_REQUIRES_SM			= (1 <<  8),
		PIN_REQUIRES_NO_DATA	= (1 <<  9),
		PIN_REQUIRES_ENCRYPTION	= (1 << 10),
		PIN_CHANGE_REQUIRES_OLD	= (1 << 11),
		PIN_IS_DEFAULT			= (1 << 12),	// marks the one and only default pin

		PIN_FLAGS_MASK			= (1 << 13) - 1,

		// combined flags
		PIN_FLAGS				= PIN_INITIALIZED | PIN_IS_LOCAL | PIN_CASE_SENSITIVE,
		PIN_FLAGS_DEFAULT		= PIN_IS_DEFAULT  | PIN_FLAGS,
		PIN_FLAGS_SO			= PIN_INITIALIZED | PIN_IS_LOCAL | PIN_CASE_SENSITIVE | PIN_UNBLOCK_DISABLED,
		PIN_FLAGS_EXAUTH		= PIN_INITIALIZED | PIN_IS_LOCAL,
		PIN_FLAGS_BIOMETRIC		= PIN_INITIALIZED | PIN_IS_LOCAL,
		PIN_FLAGS_CERTBASED		= PIN_INITIALIZED | PIN_IS_LOCAL | PIN_REQUIRES_NO_DATA | PIN_CHANGE_DISABLED | PIN_UNBLOCK_DISABLED,
	};

	enum AuthDataEncoding
	{
		PIN_ENCODING_UNKNOWN	= -1,
		PIN_ENCODING_BINARY		=  0,
		PIN_ENCODING_ASCII_NUMERIC,
		PIN_ENCODING_UTF8,
		PIN_ENCODING_BCD,
		PIN_ENCODING_HALF_NIBBLE_BCD,
		PIN_ENCODING_ISO9564_1,

		PIN_ENCODING			= PIN_ENCODING_ASCII_NUMERIC,
	};

	enum AuthId
	{
		AUTHID_INVALID			= 0x00,
	};

	enum BioFinger
	{
		FINGER_UNKNOWN			= 0,
		FINGER_RIGHT_THUMB		= 1,
		FINGER_RIGHT_INDEX		= 2,
		FINGER_RIGHT_MIDDLE		= 3,
		FINGER_RIGHT_RING		= 4,
		FINGER_RIGHT_LITTLE		= 5,
		FINGER_LEFT_THUMB		= 6,
		FINGER_LEFT_INDEX		= 7,
		FINGER_LEFT_MIDDLE		= 8,
		FINGER_LEFT_RING		= 9,
		FINGER_LEFT_LITTLE		= 10
	};

	class IKey;
	class IToken;
	class ISCardOS;
	class AuthInfo;
	class IAuthIdRef;
	class ITokenFile;

	//
	// ITokenPIN
	class ITokenPIN 
		: public IRefCounted
		, public ITokenFileOwner
	{
	public:
		virtual ITokenPIN* Clone() const = 0;
		virtual bool Equals(const ITokenPIN* other) const = 0;
		virtual int Compare(const ITokenPIN* other) const = 0;

		// TODO: MTE: Tempoaray only (!) removed if respective constraint is implemented!
		virtual bool CheckConstraints(const IKey* key) = 0;

		virtual int GetType() const = 0;
		virtual int GetUsage() const = 0;
		virtual byte GetObjRef() const = 0;
		virtual IToken* GetToken() const = 0;
		virtual const char* GetName() const = 0;
		virtual AuthDataEncoding GetEncoding() const = 0;

		virtual const AuthInfo* GetInfo() const  = 0;
		virtual void SetInfo(const AuthInfo* ai) = 0;

		virtual void SetDefault(bool is_default) = 0;
		virtual bool IsDefault() const = 0;

		virtual bool IsInitialized() const = 0;
		virtual bool IsAuthenticated() const = 0;

		virtual bool NeedsUpdate() const = 0;
		virtual bool NeedsPINValue() const = 0;

		virtual bool GetLengthInfo(LengthInfo& info) const = 0;
		virtual bool CheckPinLength(const Blob& pin) const = 0;
		virtual bool GetLastChange(Date& date, bool& supported) const = 0;

		virtual int GetTriesRemaining() const = 0;

		virtual void VerifyPin(const Blob& pin) = 0;

		// NOTE: ChangePin preserves the authentication state if successfull
		// TODO: MTE: Describe in detail!
		virtual void ChangePin(const Blob& oldpin, const Blob& newpin) = 0;

		// NOTE: UnlockPin preserves the authentication state if successfull
		// TODO: MTE: Describe in detail!
		virtual void UnlockPin(ITokenPIN* so, const Blob& pin, const Blob& newpin) = 0;

		// NOTE: SetPinValue preserves the authentication state if successfull
		// TODO: MTE: Describe in detail!
		virtual void SetPinValue(ITokenPIN* so, const Blob& so_pin, const Blob& newpin) = 0;

		virtual void Select(ISCardOS* os = 0) const = 0;

		virtual ITokenPIN* GetParent() const = 0;

		virtual IAuthIdRef* GetAuthIdRef() const = 0;
		virtual IAuthIdRef* GetParentAuthIdRef() const = 0;

		// Bio extensions
		virtual byte GetFinger() const = 0;
		virtual bool GetBioHeader(Blob& bioheader) = 0;

		// ExternalAuth Key extensions
		virtual Blob GetChallenge() const = 0;
		virtual void ResetChallenge() = 0;
		virtual Blob ComputeResponse(const Blob& auth_key, const Blob& challenge) const = 0;

		// Certificate based authentication extensions
		virtual void SetCHAT(const Blob& chat) = 0;
		virtual void SetCHAT(move_from<Blob> chat) = 0;
		virtual Blob GetCHAT() const = 0;

	protected:
		// SCard Functionality
		virtual Blob doGetChallenge() const = 0;
		virtual void doResetChallenge() const = 0;
		virtual void doVerify(const Blob& pin) const = 0;
		
		// Get security status if possible, will NEVER (!) change the current selected file or path!
		virtual SecStatus doGetSecurityStatus(Blob& context) const = 0;

	private:
		friend class TokenAuth;
	};

} // namespace act

#endif	// ACT_ITokenPIN_h
