// ---------------------------------------------------------------------------
// Name:      actITokenAuth.h
// Product:   cv act library
// Purpose:   The ITokenAuth interface represents a IToken authentication state
//			  using one the ITokenPIN objects owned by a token.
//
// Copyright: (c) 2007 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Markus Tesche (MTE)
// Date:	  11/09/2007
// ---------------------------------------------------------------------------

#ifndef ACT_ITokenAuth_h
#define ACT_ITokenAuth_h

#include "actBlob.h"
#include "actBasics.h"
#include "actIRefCounted.h"

namespace act
{
	class AuthInfo;

	class IToken;
	class ITokenPIN;
	class ITokenFile;
	class IAuthIdRef;
	class IAuthConstrained;

	enum AuthConstrainedType
	{
		AUTH_CONSTRAINED_ANY		= -1,

		// Logic operations
		AUTH_CONSTRAINED_ALWAYS		= 0,
		AUTH_CONSTRAINED_NOT		= 1,
		AUTH_CONSTRAINED_AND		= 2,
		AUTH_CONSTRAINED_OR			= 3,
		AUTH_CONSTRAINED_MASK		= 7,

		// Dependency bound, combineable
		AUTH_CONSTRAINED_BOUND_KEY	= 8,
	};

	//
	// IAuthFactory
	class IAuthFactory
	{
	public:
		virtual IAuthIdRef* CreateAuthIdRef(const Blob& authId, ITokenFile* path,
			byte constrained_mode = AUTH_CONSTRAINED_ALWAYS) = 0;

		virtual ITokenPIN* CreatePin(const AuthInfo& ai, byte objRef, ITokenFile* path,
			IAuthIdRef* authIdRef, IAuthIdRef* parentAuthIdRef) = 0;

		// TODO: MTE: deprecated, use CreatePin(const AuthInfo&...) instead
		virtual ITokenPIN* CreatePin(int type, int usage, byte objRef, IAuthIdRef* authIdRef,
			const char* name = 0) = 0;

	protected:
		virtual ~IAuthFactory() { }
	};


	//
	// IAuthIdRef
	class IAuthIdRef : public IRefCounted
	{
	public:
		virtual byte GetAuthIdByte() const = 0;
		virtual const Blob& GetAuthId() const = 0;
		virtual IAuthConstrained* GetAuthConstrained() = 0;

		virtual bool Equals(const Blob& authId) const = 0;
		virtual bool Equals(IAuthIdRef* authIdRef) const = 0;
	};

	//
	// IAuthIdRefIterator
	class IAuthIdRefIterator : public IRefCounted
	{
	public:
		virtual void Reset() = 0;
		virtual IAuthIdRef* Next() = 0;
	};


	//
	// ITokenAuthIterator
	class ITokenAuthIterator : public IRefCounted
	{
	public:
		virtual void Reset(ITokenFile* parent = 0) = 0;
		virtual ITokenPIN* Next() = 0;
	};

	//
	// ITokenAuth
	class ITokenAuth : public IRefCounted
	{
	public:
		virtual bool Login(ITokenPIN* auth_obj, const Blob& pin) = 0;

		virtual bool Logout() = 0;
		virtual bool Logout(const ITokenPIN* auth_obj) = 0;
		virtual bool LogoutEx(bool reset_security_state) = 0;

		virtual Blob GetChallenge(const ITokenPIN* auth_obj) = 0;

		virtual IToken* GetToken() const = 0;
		virtual ITokenPIN* GetAuthenticated() const = 0;
		virtual ITokenPIN* GetAuthenticated(size_t index) const = 0;

		virtual bool NeedsPINValue() const = 0;
		virtual bool HasChallenge() const = 0;
		virtual bool HasChallenge(const ITokenPIN* auth_obj) const = 0;
		virtual bool IsAuthenticated(const ITokenPIN* auth_obj) const = 0;
		virtual bool IsAuthenticated(bool verify_security_state = false) const = 0;

		/*!
		 * Clears the internal authentication state for given auth_obj.
		 *
		 * If auth_obj is not authenticated:
		 * - do nothing
		 * - return false
		 *
		 * If auth_obj is authenticated:
		 * - remove auth_obj from authenticated-list.
		 * - return true
		 *
		 * \note	does NOT reset the card's authentication state!
		 *
		 * \param	auth_obj \ref ITokenPIN 
		 * \return	true if succeeded, false if not
		 */
		virtual bool Invalidate(ITokenPIN* auth_obj) = 0;
		virtual bool ResetChallenge(const ITokenPIN* auth_obj) = 0;
		virtual bool Select(const ITokenPIN* auth_obj, bool force) = 0;

		virtual ITokenAuthIterator* Iterator(int type, const Blob& authId = Blob()) const = 0;
	};

} // namespace act

#endif	// ACT_ITokenAuth_h
