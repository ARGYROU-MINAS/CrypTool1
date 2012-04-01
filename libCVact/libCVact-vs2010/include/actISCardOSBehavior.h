// ---------------------------------------------------------------------------
// Name:      actISCardOSBehavior.h
// Product:   cv act library
// Purpose:   ISCardOSBehavior interface, encapsulates CardOS specific logic
//			  for security operations.
//
// Copyright: (c) 2002-2008 cv cryptovision GmbH all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  06/03/2008
// ---------------------------------------------------------------------------

#ifndef ACT_ISCardOSBehavior_h
#define ACT_ISCardOSBehavior_h

#include "actBasics.h"
#include "actIRefCounted.h"

namespace act
{
	class Blob;
	class IEMSAAlg;
	class ISCardOS;
	class ITokenPIN;

	enum OSBehavior
	{
		NONE_BEHAVIOR				= 0x00000000,

		// algorithm behaviors
		SIGN_BEHAVIOR				= 0x00000001,
		VERIFY_BEHAVIOR				= 0x00000002,
		DECRYPT_BEHAVIOR			= 0x00000004,
		ENCRYPT_BEHAVIOR			= 0x00000008,
		AGREEMENT_BEHAVIOR			= 0x00000010,
		ALGORITHM_BEHAVIOR_MASK		= 0x000000FF,

		// key behaviors
		GENERATE_KEY_BEHAVIOR		= 0x00000100,
		IMPORT_KEY_BEHAVIOR			= 0x00000200,
		DELETE_PRIVKEY_BEHAVIOR		= 0x00000400,
		KEY_BEHAVIOR_MASK			= 0x0000FF00,

		// PIN behaviors
		VERIFY_PIN_BEHAVIOR			= 0x00010000,
		CHANGE_PIN_BEHAVIOR			= 0x00020000,
		SET_PIN_BEHAVIOR			= 0x00040000,
		INIT_PIN_BEHAVIOR			= 0x00080000,
		PIN_BEHAVIOR_MASK			= 0x00FF0000
	};

	ACT_DEFINE_ENUM_FLAG_OPERATORS(OSBehavior);

	//
	// ISCardOSBehavior
	class ISCardOSBehavior : public IRefCounted
	{
	public:
		virtual bool Supports(OSBehavior behavior) const = 0;

		virtual Blob ComputeDigitalSignature(ISCardOS* os, const Blob& data, int mode) = 0;
		virtual Blob ComputeDigitalSignature(ISCardOS* os, IEMSAAlg* emsa, int mode) = 0;
		virtual Blob Encipher(ISCardOS* os, const Blob& plaintext, int mode) = 0;
		virtual Blob Decipher(ISCardOS* os, const Blob& encrypted_data, int mode) = 0;
		virtual Blob AgreeKey(ISCardOS* os, const Blob& pubkey) = 0;

		virtual void GenerateRSAKeyPair(ISCardOS* os, byte key_num, size_t key_size) = 0;
		virtual void ImportRSAKeyPair(ISCardOS* os, int key_id, const Blob& p, const Blob& q, const Blob& priv_exp, Blob& pubkey) = 0;
		virtual void DeletePrivateKeyObj(ISCardOS* os, unsigned short fid) = 0;

		virtual void doVerifyPinCmd(const ITokenPIN* token_pin, const Blob& pin_value) = 0;
		virtual void doChangePinCmd(const ITokenPIN* token_pin, const Blob& oldnew_value) = 0;
		virtual void doSetPinValueCmd(const ITokenPIN* token_pin, const Blob& newpin_value) = 0;
		virtual void InitPin(const ITokenPIN* token_pin, const Blob& new_pin) = 0;
	};

} // namespace act

#endif // ACT_ISCardOSBehavior_h
