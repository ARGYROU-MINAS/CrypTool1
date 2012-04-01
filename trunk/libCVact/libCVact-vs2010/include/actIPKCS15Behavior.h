// ---------------------------------------------------------------------------
// Name:      actIPKCS15Behavior.h
// Product:   cv act library
// Purpose:   IPKCS15Behavior interface, encapsulates Manufacturer specific logic
//			  for PKCS15 to cvProfile mapping.
//
// Copyright: (c) 2002-2008 cv cryptovision GmbH all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche
// Date:	  06/02/2008
// ---------------------------------------------------------------------------

#ifndef ACT_IPKCS15Behavior_h
#define ACT_IPKCS15Behavior_h

#include "actLocation.h"
#include "actISCardOSBehavior.h"

namespace act
{
	class IAuthIdRef;

	class IToken;
	class ITokenPIN;
	class ITokenKey;
	class ITokenFile;
	class ITokenFileMap;
	class ISecurityManager;
	class ITokenBlockCipherKey;

	class PKCS15Container;
		struct PKCS15Path;
		struct PKCS15Object;

	//
	// IPKCS15Behavior
	// ---------------------------------------------------------------------------
	class IPKCS15Behavior : public ISCardOSBehavior
	{
	public:
		virtual void		Init(IToken* token, const Location<>& location) = 0;
		virtual bool		IsReadOnly() const = 0;

		virtual const Blob&	GetMID() const = 0;
		virtual bool		GetNativePubKeySupport() const = 0;
		virtual int			GetTokenType(const IToken* token) const = 0;
		virtual void		GetProfileCapabilities(ITokenConfig* tkcfg) const = 0;

		// Returns a valid instance or throws !
		virtual ITokenFile*	GetPath() const  = 0;
		virtual ITokenFile*	GetTokenFile(const Blob& p15path) = 0;
		virtual ITokenFile*	GetTokenFile(const PKCS15Path& p15path) = 0;
		virtual ITokenFile*	GetAuthTokenFile(const PKCS15Path& p15path) = 0;

		virtual ITokenPIN*	GetPin(IToken* token, const PKCS15Object& p15object, bool use_obj_ref = false) = 0;

		// NOTE: If one of these functions return false, the object gets destroyed
		// and is not added to the corresponding collection, therefore not accessable!
		virtual bool		InitTokenPIN(ITokenPIN* pin, const PKCS15Object& p15object, const Location<>&) = 0;
		virtual bool		InitTokenKey(ITokenKey* key, const FileInfo& fi, int usage, const PKCS15Object& p15object, const Location<>&) = 0;
		virtual bool		InitTokenKey(ITokenBlockCipherKey* key, const FileInfo& fi, const PKCS15Object& p15object, const Location<>&) = 0;

		virtual FIDType		GetFirstFID(byte obj_type, size_t key_size = 0) const = 0;
		virtual void		GetObjectInfo(FIDType fid, Blob& object_path, byte* obj_ref, byte obj_type, size_t key_size = 0) const = 0;
		
		virtual FIDType		TransformKeyReference(FIDType id, bool to_on_card_reference = false, bool* bReference = 0) const = 0;

		virtual void		GetRelativeFilePath(Blob& absolute_filepath) const = 0;

		virtual const Blob&	GetACTokenRights() const = 0;
		virtual Blob		GetAccessRights(const ITokenPIN* pin, byte obj_type) const = 0;
		virtual Blob		GetAccessRights(IAuthIdRef* authIdRef, IAuthIdRef* parentAuthIdRef, byte obj_type) const = 0;

		virtual ISecurityManager* SecurityManager(IToken* token, int authManagerType) const = 0;
		virtual void		CreateAuthObj(ITokenPIN* pin, byte obj_type) const = 0;

		virtual Blob		ReadNativePublicKey(ISCardOS* os, FIDType fid) const = 0;
		virtual Blob		ReadNativeECPublicKey(ISCardOS* os, FIDType fid) const = 0;
		virtual FIDType		GetNativePubKeyInfo(FIDType priv_key_fid, PKCS15Object& p15object) const = 0;
	};

} // namespace act

#endif // ACT_IPKCS15Behavior_h
