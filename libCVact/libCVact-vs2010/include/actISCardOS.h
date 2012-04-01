// ---------------------------------------------------------------------------
// Name:      actISCardOS.h
// Product:   cv act library
// Purpose:   The class ISCardOS accesses the card operating system
//
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  03/21/2002
// ---------------------------------------------------------------------------

#ifndef ACT_ISCardOS_h
#define ACT_ISCardOS_h

#include "actITokenPIN.h"
#include "actITokenConfig.h"
#include "actITokenInitializer.h"

#include "actIRefCounted.h"
#include "actIAccessCondition.h"

#include "actBlob.h"
#include "actTokenBase.h"
#include "actSCardOSReg.h"

namespace act
{
	class IKey;
	class IEMSAAlg;
	class IKeyDerivation;
	class ITokenFile;
	class ISCardOS;
	class ISCardAccess;
	class ISCardOSBehavior;

	class EFDIR;

	const FIDType	FID_EF_DIR				= 0x2F00;
	const FIDType	FID_EF_ATR				= 0x2F01;

	const ushort	SIZE_NOT_INITIALIZED	= ushort(-1);

	//
	// ISO 7816-4
	enum SCardFileType
	{
		UNKNOWN_FILE_TYPE					= 0x00,

		// EF types
		BINARY								= 0x01,
		LINEAR_FIXED						= 0x02,
		LINEAR_FIXED_TLV					= 0x03,
		LINEAR_VARIABLE						= 0x04,
		LINEAR_TLV							= 0x05,
		CYCLIC_FIXED						= 0x06,

		// DF type
		DF									= 0x38,

		// additional masks and flags
		EF_TYPE_MASK						= 0x07,
		EF_LOCAL							= 0x10,
		EF_SECURITY_RELATED					= 0x20,
		SHAREABLE							= 0x40,
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(SCardFileType);

	//
	// ISO 7816-4
	enum SCardRecordMode
	{
		ABSOLUTE_MODE						= 0x04
	};

	//
	// ISO 7816-4
	enum SCardSelectType
	{
		MFType								= 0x00,
		DFType								= 0x01,
		EFType								= 0x02,
		AIDType								= 0x04,
		PathType							= 0x08
	};

	//
	// ISO 7816-9
	enum SCardDeleteType
	{
		CURRENT_FILE						= 0x00,
		CHILD_DF							= DFType,
		CHILD_EF							= EFType
	};

	enum SCardSelectMode
	{
		FCI									= 0x00,	//!< FCI template
		FCP									= 0x04,	//!< FCP template
		FMD									= 0x08,	//!< FMD template
		NoData								= 0x0c,	//!< No response data
	};

	enum SCardError
	{
		SCARD_SUCCESS						=  0,
		SCARD_FUNCTION_NOT_SUPPORTED		= -1,
		SCARD_FUNCTION_FAILED				= -2
	};

	// ---------------------------------------------------------------------------
	struct OSFileInfo
	{
		OSFileInfo()
			: type(UNKNOWN_FILE_TYPE)
			, size(SIZE_NOT_INITIALIZED)
			, readSize(SIZE_NOT_INITIALIZED)
			, records(SIZE_NOT_INITIALIZED)
			, recordSize(SIZE_NOT_INITIALIZED)
		{ }

		void reset();
		void swap(OSFileInfo& other);

		ushort	size;
		ushort	readSize;			//!< may differ from size for logical end of file support
		ushort	records;
		ushort	recordSize;
		byte	type;
	};

	// ---------------------------------------------------------------------------
	bool IsTransacted(const ISCardOS* os);
	bool IsTokenPresent(const ISCardOS* os);
	const ISCardAccess* GetAccess(const ISCardOS* os);

	// ---------------------------------------------------------------------------
	class ISCardOS
		: public IRefCounted
		, public IAcConverter
	{
	public:
		virtual ~ISCardOS() { }

		// ISCardOS
		virtual ISCardOS* Clone() const = 0;
		virtual CreateSCardOSPtr GetCreatePtr() const = 0;

		virtual bool IsMoC() = 0;
		virtual ushort GetVersion() const = 0;
		virtual const char* GetName() const = 0;
		virtual Blob GetSerialNumber(bool refresh = false) const = 0; //!< hardware serial number, nothrow!

		virtual Blob GetCardId(ushort fid_card_id) = 0;
		virtual Blob GetCardCF(ushort fid_card_cf) = 0;
		virtual FIDType GetKnownFID(FIDType fid) const = 0;

		virtual IToken* CreateToken() = 0;
		virtual ISCardAccess* GetAccess() const = 0;

		virtual Blob ComputeDigitalSignature(const Blob& data, int mode = SIGN_DATA) = 0;
		virtual Blob ComputeDigitalSignature(IEMSAAlg* emsa, int mode = SIGN_DATA) = 0;
		virtual Blob Encipher(const Blob& plaintext, int mode = ENC_DATA) = 0;
		virtual Blob Decipher(const Blob& ciphertext, int mode = DEC_DATA) = 0;
		virtual Blob AgreeKey(const Blob& pubkey) = 0;

		virtual void ComputeECDigitalSignature(const Blob& data, Blob& signature) = 0;

		virtual Blob SelectFile(const int filetype, const char* filepath) = 0;	// return file control information
		virtual Blob SelectFile(const int filetype, const Blob& filepath) = 0;	// return file control information
		virtual Blob SelectFile(const int filetype, FIDType fid) = 0;			// return file control information
		virtual Blob SelectApp(const Blob& aid, SCardSelectMode mode = NoData) = 0;

		// EF.DIR
		virtual EFDIR* GetEFDIR(ushort fid = FID_INVALID) = 0;

		virtual int GetEFSize(FIDType fid, bool readSize) = 0;
		virtual int GetEFSize(const Blob& filepath, bool readSize, Blob& fci) = 0;

		virtual void GetFCI(FIDType fid, Blob& fci) = 0;
		virtual Blob GetFCIValue(const Blob& fci, const byte tag) = 0;
		virtual void GetFileInfo(const Blob& fc_data, OSFileInfo& file_info) = 0;

		// select and read binary
		virtual Blob ReadBinary(const char* filepath) = 0;
		virtual Blob ReadBinary(const Blob& filepath) = 0;
		virtual Blob ReadBinary(FIDType fid) = 0;

		// read/update binary, file is selected, file size is known
		virtual Blob ReadSelectedBinary(size_t file_size, ushort offset = 0) = 0;
		virtual void UpdateSelectedBinary(const Blob& data, ushort offset = 0) = 0;

		// select and update binary
		virtual void UpdateBinary(const Blob& filepath, const Blob& data, ushort offset = 0) = 0;
		virtual void UpdateBinary(FIDType fid, const Blob& data, ushort offset = 0) = 0;

		// read binary with XL-APDUs
		virtual Blob ReadBinaryX(const char* filepath) = 0;
		virtual Blob ReadBinaryX(const Blob& filepath) = 0;
		virtual Blob ReadBinaryX(FIDType fid) = 0;
		virtual Blob ReadSelectedBinaryX(size_t file_size, ushort offset = 0) = 0;

		// update binary with XL-APDUs
		virtual void UpdateBinaryX(const Blob& filepath, const Blob& data, ushort offset = 0) = 0;
		virtual void UpdateBinaryX(FIDType fid, const Blob& data, ushort offset = 0) = 0;
		virtual void UpdateSelectedBinaryX(const Blob& data, ushort offset = 0) = 0;

		// record read/write (file must be selected)
		virtual Blob ReadRecord(byte mode) = 0;										// p2
		virtual Blob ReadRecord(byte rec_id, byte mode) = 0;						// p1, p2
		virtual void UpdateRecord(const Blob& data, byte rec_id, byte mode) = 0;	// data, p1, p2
		virtual void AppendRecord(const Blob& data, byte ef_id = 0) = 0;			// data, p2

		// record write (includes file selection and resize)
		virtual void UpdateRecord(const Blob& filepath, const Blob& data, byte rec_id, byte mode) = 0;
		virtual void AppendRecord(const Blob& filepath, const Blob& data) = 0;

		virtual void DeleteFileObj(SCardDeleteType mode, const Blob& fid = Blob()) = 0;
		virtual void DeleteFileObj(SCardDeleteType mode, FIDType fid) = 0;

		virtual void DeleteEF(const Blob& fid) = 0;
		virtual void DeleteEF(FIDType fid) = 0;

		virtual void CreateEF(const Blob& fcp) = 0;
		virtual void CreateEF(const Blob& fid, ushort len, bool secure = false) = 0;
		virtual void CreateEF(FIDType fid, ushort len, bool secure = false) = 0;

		virtual void CreateEF_TLV(FIDType fid, ushort len, ushort num_of_records = 1) = 0;
		virtual void CreateEF_TLV(const Blob& fid, ushort len, ushort num_of_records = 1) = 0;

		virtual ushort GetOSFileOffset() const = 0;

		// get/put data
		virtual Blob GetData(ushort tag, ushort le = 0) const = 0;	// INS=CA
		virtual void PutData(ushort tag, const Blob& data) = 0;		// INS=DA

		// MSE/PSO functions
		virtual void ManageSecurityEnvironment(byte p1, byte p2, const Blob& data = Blob()) = 0;
		virtual void GenerateAsymmetricKeyPair(byte p1, byte p2, const Blob& data = Blob()) = 0;
		virtual void PerformSecurityOperation(Blob& response, byte p1, byte p2, const Blob& data, bool chaining = false) = 0;
		virtual void PerformSecurityOperationX(Blob& response, byte p1, byte p2, const Blob& data) = 0; // explicit extended APDU

		// ISO authentication functions
		virtual void ExternalAuthenticate(byte key_id, const Blob& response, bool odd_INS = false) = 0;	// INS=82/83, P1=00, P2=key_id
		virtual Blob InternalAuthenticate(byte key_id, const Blob& challenge, bool odd_INS = false) = 0; // INS=88/89, P1=00, P2=key_id
		virtual Blob MutualAuthenticate(byte key_id, const Blob& auth_data, bool odd_INS = false) = 0; // INS=82/83, P1=00, P2=key_id
		virtual Blob GeneralAuthenticate(byte key_id, const Blob& auth_data, bool chaining = false, bool odd_INS = false) = 0; // INS=86/87, P1=00, P2=key_id

		virtual void ResetRetryCounter(byte p1, byte p2, const Blob& data) = 0;
		virtual void Verify(byte p1, byte p2, const Blob& data, bool odd_INS = false) = 0; // INS=20/21

		// random functions
		virtual Blob GetChallenge(byte le = byte(8)) const = 0;
		virtual Blob GetRandom(const ulong count) const = 0;

		// token type / config
		virtual ProfileType GetProfileType(bool refresh = false) = 0;

		virtual void SetTokenConfig(ITokenConfig* tkcfg) = 0;
		virtual ITokenConfig* GetTokenConfig() const = 0;

		// set/get behavior
		virtual void SetBehavior(ISCardOSBehavior* behave) = 0;
		virtual ISCardOSBehavior* GetBehavior() = 0;

		// access rights
		virtual void SetAccessRights(const Blob& access_rights) = 0;
		virtual void SetAccessRights(move_from<Blob> access_rights) = 0;
		virtual void SetExplicitRights(IAccessCondition* ac, size_t ac_cnt = 1) = 0;

		virtual bool HasExplicitRights() const = 0;

		virtual Blob GetAccessRights() = 0;
		virtual IAccessCondition* GetAccessRights(const Blob& fci) = 0;
		virtual Blob GetAccessRights(ACObjType ac_obj_type, bool tagged) const = 0;

		// selected path
		virtual void SetSelectedPath(ITokenFile* selected_path) const = 0;
		virtual ITokenFile* GetSelectedPath() const = 0;

		// key derivation
		virtual void SetKeyDerivation(IKeyDerivation* key_derivation) = 0;
		virtual IKeyDerivation* GetKeyDerivation() const = 0;

		// key handling
		virtual void GenerateRSAKeyPair(int key_id,	size_t key_size, // in bits
			Blob& pubkey) = 0;

		virtual void ImportRSAKeyPair(int key_id, const Blob& prime_p,
			const Blob& prime_q, const Blob& priv_exp, Blob& pubkey) = 0;

		virtual void GenerateECKeyPair(Blob& pubkey) = 0;

		virtual void GenerateECKeyPair(int key_id, const Blob& curve_oid,
			const Blob& curve_param, Blob& pubkey) = 0;

		virtual void ImportECKeyPair(int key_nr, const Blob& curve_oid,
			const Blob& curve_param, const Blob& privkey, const Blob& pubkey) = 0;

		virtual void ImportDESKey(int key_id, const Blob& keyblob) = 0;

		virtual void DeletePrivateKeyObj(FIDType fid) = 0;
		virtual void DeleteECPrivateKeyObj(FIDType fid) = 0;
		virtual void DeleteBlockCipherKeyObj(FIDType fid) = 0;
		virtual void SelectKey(int key_id) = 0;

		// authentication functions
		virtual Blob ComputeResponse(const Blob& auth_key, const Blob& challenge) const = 0;
		virtual void UpdateExternalAuthenticateKey(byte key_id, const Blob& auth_key) = 0;

		virtual void ResetSecurityStatus() = 0;
		virtual int GetTriesRemaining(const ITokenPIN* pin) const = 0;

		// NOTE: GetSecurityStatus never changes the current path
		virtual SecStatus GetSecurityStatus(const ITokenPIN* pin, Blob& context, int& tries_remaining) const = 0;

		// token initialization
		virtual void SetDefaultLabel(move_from<Blob> label) = 0;
		virtual ITokenInitializer* GetTokenInitializer() = 0;
	};

} // namespace act

#endif	// ACT_ISCardOS_h
