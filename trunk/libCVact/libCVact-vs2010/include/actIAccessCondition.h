// ---------------------------------------------------------------------------
// Name:      actIAccessConditions.h
// Product:   cv act library
// Purpose:   The IAccessCondition interface is used to map access conditions for
//			  Files, Keys etc. on specific smartcard's
//
// Copyright: (c) 2008 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  10/29/2008
// ---------------------------------------------------------------------------

#ifndef ACT_IAccessConditions_h
#define ACT_IAccessConditions_h

#include "actBlob.h"
#include "actIRefCounted.h"

namespace act
{
	class IToken;
	class ISCardOS;

	enum
	{
		AC_AUTH_ID_MASK			= 0x7f,
	};

	enum ACType
	{
		AC_TYPE_UNKNOWN			= 0,
		AC_TYPE_RAW				= 1,	// Already transformed for specific OS
		AC_TYPE_GENERIC			= 2		// OS independant, requires to be transformed before used
	};

	// SCard object specific rights by type
	enum ACObjType
	{									// { AC_TOKEN_USER, AC_TOKEN_SO, AC_TOKEN_USER_OR_SO }
		AC_OBJ_MAP				= 0x00,	// Used for access condition (f.e. tag 0x86)
		AC_OBJREF_MAP			= 0x01,	// Used as object reference for access condition
		//
		AC_OBJ_ANY				= 0x01,	// Access Rights not further defined
		AC_RIGHTS_EF			= 0x02, // Access Rights for EF's
		AC_RIGHTS_DF			= 0x03, // Access Rights for DF's
		AC_RIGHTS_KEY			= 0x04, // Access Rights for Key Objects
		AC_RIGHTS_AUTH			= 0x05, // Access Rights for Authentication Objects
		AC_RIGHTS_DO			= 0x06, // Access Rights for Data Objects
		// ... add additional types here
	};

	// SCard specific rights
	enum ACSCard
	{
		AC_ALWAYS				= 0x00,
		// Any other from 0x01..0x7f
		AC_NEVER				= 0xff
	};

	// Token specific rights
	enum ACToken
	{
		AC_TOKEN_USER			= 0x80,
		AC_TOKEN_SO				= 0x81,
		AC_TOKEN_USER_OR_SO		= 0x82,
		AC_TOKEN_USER_AND_SO	= 0x83,
		AC_TOKEN_ADMIN			= 0x84,

		AC_TOKEN_FLAG			= 0x80,
	};

	// AuthId Index
	enum AIIndex
	{
		AI_INVALID				= -1,
		AI_USER					= AC_TOKEN_USER			& ~AC_TOKEN_FLAG,
		AI_SO					= AC_TOKEN_SO			& ~AC_TOKEN_FLAG,
		AI_USER_OR_SO			= AC_TOKEN_USER_OR_SO	& ~AC_TOKEN_FLAG,
		AI_USER_AND_SO			= AC_TOKEN_USER_AND_SO	& ~AC_TOKEN_FLAG,
		AI_ADMIN				= AC_TOKEN_ADMIN		& ~AC_TOKEN_FLAG,
	};

	enum ACOperation
	{
		AC_OR					= 0x00,
		AC_AND					= 0x01,
	};

	enum ACMode
	{
		AC_MODE_READ			= 0,
		AC_MODE_UPDATE			= 1,
		AC_MODE_EXECUTE			= 2,
		AC_MODE_DELETE			= 3,
	};

	enum ACRight
	{
		// Used for EF/DF
		AC_READ					= 0x00,
		AC_WRITE				= 0x01,
		AC_UPDATE				= 0x01,
		AC_APPEND				= 0x02,
		AC_DEACTIVATE			= 0x03,
		AC_LOCK					= 0x03,
		AC_ACTIVATE				= 0x04,
		AC_UNLOCK				= 0x04,
		AC_DELETE				= 0x05,
		AC_ADMIN				= 0x06,
		AC_CREATE				= 0x07,
		AC_INCREASE				= 0x08,
		AC_DECREASE				= 0x09,
		AC_TERMINATE			= 0x0a,

		// Used for Objects
		AC_USE					= 0x00,
		AC_CHANGE				= 0x01,
		AC_UNBLOCK				= 0x02,
		AC_GENKEY				= 0x07,
		AC_SIGN					= 0x08,
		AC_DEC					= 0x09,
		AC_ENC					= 0x0a,
	};

	enum ACRange
	{
		AC_FIRST				= AC_READ,
		AC_LAST					= AC_ENC,
	};

	//
	// IAccessCondition
	class IAccessCondition : public IRefCounted
	{
	public:
		virtual IAccessCondition*	Clone() const = 0;

		virtual const char*			GetName() const = 0;
		virtual ACType				GetAcType() const = 0;
		virtual ACObjType			GetAcObjType() const = 0;
		virtual const Blob&			GetAccessRights() const = 0;

		virtual IAccessCondition*	SetAccessRights(move_from<Blob> ac, ACObjType acObjType) = 0;
		virtual IAccessCondition*	ConvertAc(const IToken* token, ACType acType) const = 0;
	};

	//
	// IAcConverter
	class IAcConverter
	{
	protected:
		virtual ~IAcConverter() { }

	public:
		virtual IAccessCondition*	ConvertAc(const Blob& ac) const = 0;
		virtual Blob				ConvertAc(const IAccessCondition* ac) const = 0;
		virtual IAccessCondition*	ConvertAc(const IAccessCondition* ac, ACType acType) const = 0;
	};

} // namespace act

#endif	// ACT_IAccessConditions_h
