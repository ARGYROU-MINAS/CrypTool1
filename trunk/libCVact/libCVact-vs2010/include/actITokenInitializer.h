// ---------------------------------------------------------------------------
// Name:      actITokenInitializer.h
// Product:   cv act library
// Purpose:   ITokenInitializer interface declares common token profile initialization functionality.
//            
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  04/20/2009
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenInitializer_h
#define ACT_ITokenInitializer_h

#include "actBlob.h"
#include "actTokenBase.h"
#include "actIRefCounted.h"

// TODO: MTE: *** Replace std::vector<> by simple Range<TIData>(begin, end).
#include <vector>

namespace act
{
	extern const byte PIN_PAD_CHAR;

	enum NamedAC
	{
		// AC
		/* Blob   */ ac_u_so		= 64,	//!< AC Update for SO.
		/* Blob   */ ac_ua_so,				//!< AC Update|Append for SO.
		/* Blob   */ ac_ua_user,			//!< AC Update|Append for User.
		/* Blob   */ ac_ua_user_or_so,		//!< AC Update|Append for User or SO.

		// AC-DO
		/* Blob   */ ac_do_ro,				//!< AC-DO ReadOnly.
		/* Blob   */ ac_do_u_so,			//!< AC-DO Update for SO.
		/* Blob   */ ac_do_u_user_or_so,	//!< AC-DO Update for User or SO.

		// AC-??
		// NOTE: Add more access conditions ...

		/* Last   */ ac_last		= 127,
	};

#	include "actPackOn.h"

	// Token Initializer Data.
	struct TIData
	{
	private:
		TIData(const TIData&) throw();
		TIData& operator=(const TIData&) throw();

	public:
		struct DO		{
			NamedAC		ac;
			Blob		tag;
			Blob		data;
		};

		typedef std::vector<DO>::iterator		do_iterator;
		typedef std::vector<DO>::const_iterator const_do_iterator;

	public:
		TIData(const char* profile_name_ = 0)
			: profile_name(profile_name_)
			, profile_type(PROFILE_UNKNOWN)
			, retry_counter(3)
			, pin_pad_byte(PIN_PAD_CHAR)
			, profile_privileges(0)
			, enable(0)
			, load(0)
		{ }

		Blob			atr_historical_bytes;
		Blob			atr_historical_bytes_suffix;
		Blob			serial_number;

		Blob			card_pin;
		Blob			so_pin;
		Blob			user_pin;
		Blob			last_update_pin_utc;
		Blob			challenge_response_key;

		Blob			pin_policy;
		Blob			binary_data;
		std::vector<DO>	array_of_do;					//!< Array of Data Objects (DO)

		Blob			profile_id;	
		Blob			profile_label;
		Blob			profile_domain_id;	
		Blob			profile_package_id;
		const char*		profile_name;

		ProfileType		profile_type;
		byte			profile_privileges;
		byte			pin_pad_byte;
		short			retry_counter;
		union  {
			struct {
				ushort	enable_pin_padding		: 1;	// bit 0
				ushort	enable_pin_pce_so		: 1;	// bit 1
				ushort	enable_pin_pce_user		: 1;	// bit 2
				ushort	enable_minidriver		: 1;	// bit 3
				ushort	enable_minidriver_pnp	: 1;	// bit 4
				ushort	enable_biometric		: 1;	// bit 5
				ushort	enable_biometric_pins	: 1;	// bit 6
				//		...
			};
			ushort		enable;
		};
		union  {
			struct {
				ushort	load_only				: 1;	// bit 0	
				ushort	load_package_MoC		: 1;	// bit 1
				ushort	load_package_2048		: 1;	// bit 2
				ushort	load_package_ecc		: 1;	// bit 3
				//		...
			};
			ushort		load;
		};
	};

	struct TITokenInfo
	{
		TITokenInfo(size_t pin_len_max, size_t pin_len_min, size_t _key_len_cr)
			: serial_number_len(16)
			, key_len_cr(_key_len_cr)
		{
			pin_len_max_admin = pin_len_max_so = pin_len_max_user = pin_len_max;
			pin_len_min_admin = pin_len_min_so = pin_len_min_user = pin_len_min;
		}

		size_t serial_number_len;

		size_t key_len_cr;

		size_t pin_len_max_admin;
		size_t pin_len_max_so;
		size_t pin_len_max_user;

		size_t pin_len_min_admin;
		size_t pin_len_min_so;
		size_t pin_len_min_user;
	};

#	include "actPackOff.h"

	// Forward declarations
	class ISCardOS;
	class IProfileGenerator;
	class ISCardCmdObserver;

	//
	// ITokenInitializer
	// -----------------------------------------------------------------------
	class ITokenInitializer : public IRefCounted
	{
	public:
		virtual ISCardOS* GetOS() const = 0;
		virtual const TITokenInfo& GetTokenInfo() const = 0;
		virtual const ProfileType* GetSupportedProfileList() const = 0;

		virtual bool SupportsProfile(ProfileType profile_type) const = 0;
		virtual void SetGenerator(IProfileGenerator* generator) = 0;
		virtual void SetObserver(ISCardCmdObserver* observer) = 0;

		virtual bool EraseProfile(const Blob& card_pin) = 0;
		virtual bool ExistProfile(bool& is_pkcs15, bool& requires_adminpin) = 0;
		virtual void CreateProfile(TIData& data, ProfileType profile_type) = 0;
		virtual void FinalizeProfile(TIData& data) = 0;

		virtual void PinChangeReminder(TIData& data, bool enable) = 0;
	};

} // namespace act

#endif // ACT_ITokenInitializer_h
