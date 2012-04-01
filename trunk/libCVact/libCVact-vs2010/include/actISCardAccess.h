// ---------------------------------------------------------------------------
// Name:      actISCardAccess.h
// Product:   cv act library
// Purpose:   The class ISCardAccess manages the operations with the smartcards and readers
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/21/2002
// ---------------------------------------------------------------------------

#ifndef ACT_ISCardAccess_h
#define ACT_ISCardAccess_h

#include "actBlob.h"
#include "actObserver.h"
#include "actTokenBase.h"

#include "actISynchronize.h"
#include "actIEventHandler.h"

namespace act
{
	class SyncObject;

	const ushort RESPONSE_MAXLEN	= 2048;

	enum SCardReturnCode
	{
		APDU_RESPONSE_MASK			= 0xffff,
		APDU_NO_RETRY_MASK			= 0xfff0,

		APDU_OK						= 0x9000,
		APDU_OK1					= 0x9001,

		// error codes defined in ISO7816-4
		APDU_STATE_UNCHANGED		= 0x6200,
		APDU_RETURN_CORRUPTED		= 0x6281,
		APDU_END_REACHED			= 0x6282,
		APDU_SELECTFILE_INVALID		= 0x6283,
		APDU_FCI_FORMAT				= 0x6284,

		APDU_AUTHEN_FAILED			= 0x6300,
		APDU_RETRY_COUNTER			= 0x63C0,
		APDU_FILE_FILLED_UP			= 0x6381,

		APDU_STATE_UNCHANGED2		= 0x6400,

		APDU_STATE_CHANGED			= 0x6500,
		APDU_MEMORY_FAILURE			= 0x6581,

		APDU_SECURITY_ERROR			= 0x6600,	// not defined in ISO7816

		APDU_WRONG_LEN				= 0x6700,

		APDU_NO_CLA_FUNCTION		= 0x6800,
		APDU_NO_LOGICAL_CHANNEL		= 0x6881,
		APDU_NO_SM					= 0x6882,

		APDU_CMD_NOT_ALLOWED		= 0x6900,
		APDU_CMD_INCOMPATIBLE		= 0x6981,
		APDU_SECURITY_STATE			= 0x6982,
		APDU_AUTHEN_BLOCKED			= 0x6983,
		APDU_REF_DATA_INVALID		= 0x6984,
		APDU_NO_CONDITION			= 0x6985,
		APDU_CMD_EF_NOT_ALLOWED		= 0x6986,
		APDU_SM_DATA_MISSING		= 0x6987,
		APDU_SM_DATA_INCORRECT		= 0x6988,

		APDU_WRONG_PARAMETER		= 0x6A00,
		APDU_WRONG_DATA				= 0x6A80,
		APDU_FUNCTION_NOT_SUPPORTED	= 0x6A81,
		APDU_FILE_NOT_FOUND			= 0x6A82,
		APDU_RECORD_NOT_FOUND		= 0x6A83,
		APDU_NOT_ENOUGH_MEMORY		= 0x6A84,
		APDU_LC_TLV_INCONSISTENT	= 0x6A85,
		APDU_INVALID_P1P2			= 0x6A86,
		APDU_LC_P1P2_INCONSISTENT	= 0x6A87,
		APDU_REF_DATA_NOT_FOUND		= 0x6A88,
		APDU_FILE_ALREADY_EXISTS	= 0x6A89,

		APDU_WRONG_PARAMETER2		= 0x6B00,

		APDU_WRONG_LE				= 0x6C00,

		APDU_INS_INVALID			= 0x6D00,

		APDU_CLA_INVALID			= 0x6E00,

		APDU_TECHNICAL_ERROR		= 0x6F00,


		// other error codes depend on card OS
		APDU_NO_ICC					= 0x64A1,
		APDU_PROTOCOL_ERROR			= 0x64A8,
		
		APDU_NO_AC_RIGHT			= 0x6982,
		APDU_PIN_LOCKED				= 0x6983,
		APDU_PIN_FORMAT_ERROR		= 0x6984,

		APDU_OBJECT_NOT_FOUND		= 0x6A88,

		APDU_KEYGEN_FAILED			= 0x6F83, // ACOS


		// JavaCardOS
		APDU_MORE_DATA_AVAILABLE	 = 0x6310,	
		APDU_APPLET_SELECTION_FAILED = 0x6999,
		APDU_PIN_FAILED 			 = 0x69C0,
		APDU_ASSERT					 = 0x6FFF,
		APDU_ASSERT_NOTRANSACTION	 = 0x6FFE,
	};

	enum SCardSyncMode
	{
		None,
		Transact,
		Recurse,
	};

	enum ScopeType
	{
		SCOPE_INVALID				= -1,
		SCOPE_USER					=  0,		//!< Equals SCARD_SCOPE_USER
		SCOPE_TERMINAL				=  1,		//!< Equals SCARD_SCOPE_TERMINAL
		SCOPE_SYSTEM				=  2,		//!< Equals SCARD_SCOPE_SYSTEM
	};

	enum ProtocolType
	{
		PROTOCOL_UNDEFINED			= 0x00000,	//!< There is no active protocol.
		PROTOCOL_T0					= 0x00001,	//!< T=0 is the active protocol.
		PROTOCOL_T1					= 0x00002,	//!< T=1 is the active protocol.
		PROTOCOL_ANY				= PROTOCOL_T0 | PROTOCOL_T1,
		PROTOCOL_RAW				= 0x10000	//!< Raw is the active protocol.
	};

	enum DispositionType
	{
		LEAVE_CARD					= 0x0000,	//!< Don't do anything special. 
		RESET_CARD					= 0x0001,	//!< Reset the card. 
		UNPOWER_CARD				= 0x0002,	//!< Power down the card. 
		EJECT_CARD					= 0x0003,	//!< Eject the card.

		DISPOSITION_MASK			= 0x000f,	//!< Mask to remove the disposition flags.
		DISPOSITION_SHUTDOWN		= 0x0010	//!< Shutdown Bit 
	};

	inline bool APDUSUCCESS(word sw1sw2)
	{
		return sw1sw2 == act::APDU_OK
			|| sw1sw2 == act::APDU_OK1;
	}

	//
	// extract status word
	template<typename ExceptionT>
	inline word apdu_response(const ExceptionT& e)
	{
		return word(e.code() & APDU_RESPONSE_MASK);
	}

	//
	// VerifyInfo
	struct VerifyInfo
	{
		VerifyInfo(const LengthInfo& _lengthInfo, byte _encoding)
			: lengthInfo(_lengthInfo)
			, encoding(_encoding)
		{ }

		void swap(VerifyInfo& other)
		{
			std::swap(lengthInfo, other.lengthInfo);
			std::swap(encoding, other.encoding);
		}

		LengthInfo	lengthInfo;
		byte		encoding;
	};

	class ISlot;
	class ISCardSM;
	class ISCardAccess;

	// ---------------------------------------------------------------------------
	enum SCAOption
	{
		SCAO_None		= 0,
		SCAO_Abort		= 1,
		SCAO_Retry		= 2,
		SCAO_Handled	= 4,
	};

	// ---------------------------------------------------------------------------
	struct SCAEvent
	{
		template<typename T>
		SCAEvent(EventCode type_, SCAOption option_, const Location<T>& location_)
			: type(type_)
			, option(option_)
			, location(location_)
		{ }

		const EventCode		type;
		const SCAOption		option;
		const Location<>	location;
	};

	// ---------------------------------------------------------------------------
	class ISCAEventHandler : public Observer<ISCardAccess, SCAEvent, SCAOption>
	{
	public:
		virtual const char* GetName() const = 0;		
	};

	// ---------------------------------------------------------------------------
	bool IsTransacted(const ISCardAccess* ac);

	// ---------------------------------------------------------------------------
	class ISCardAccess
		: public IRefCounted
		, public ISynchronize
		, public Observable<ISCardAccess, SCAEvent, SCAOption>
	{
	public:
		virtual ~ISCardAccess()
		{ }

		virtual ProtocolType	GetProtocol() const = 0;
		virtual void			SetProtocol(ProtocolType protocol) = 0;

		virtual ulong			GetTimeout() const = 0;
		virtual bool			SetTimeout(ulong timeout_msec) = 0;

		virtual SCardSyncMode	GetReconnectMode() const = 0;
		virtual void			SetReconnectMode(SCardSyncMode reconnect_mode) = 0;

		virtual bool			IsTokenPresent() const = 0;

		virtual void			Open() = 0;
		virtual void			Close() = 0;
		virtual void			Reset() = 0;
		virtual ulong			Cancel() = 0;
		virtual ulong			Reconnect(DispositionType initialization) = 0;

		virtual ulong			BeginTransaction() = 0;
		virtual ulong			EndTransaction(DispositionType disposition = LEAVE_CARD) = 0;
		virtual ulong			GetTransactionDepth() const = 0;
		virtual uint32			GetAccessChangeCount() const = 0;

		virtual ISlot*			GetSlot() const = 0;

		virtual Blob			GetResponse() const = 0;
		virtual Blob&			GetResponse(Blob& response) const = 0;
		virtual size_t			GetResponseSize() const = 0;
		
		virtual word			SendCard(const Blob& cmd, Blob& response, ushort response_len = RESPONSE_MAXLEN) = 0;

		virtual word			Send(const Blob& cmd) = 0;
		virtual word			Send(const Blob& header, const Blob& data) = 0;
		virtual word			Send(const Blob& header, const Blob& data, byte le) = 0;

		// extended APDU
		virtual word			SendX(const Blob& header, const Blob& data) = 0;
		virtual word			SendX(const Blob& header, const Blob& data, ushort le) = 0;

		// secure pin entry
		virtual word			SendVerifyToReader(const Blob& apdu, const VerifyInfo& info) = 0;

		// secure messaging
		virtual ISCardSM*		GetSM() const = 0;
		virtual void			SetSM(ISCardSM* sm) = 0;
	};

} // namespace act

#endif	// ACT_ISCardAccess_h
