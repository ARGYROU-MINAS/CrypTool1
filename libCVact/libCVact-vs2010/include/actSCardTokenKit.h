// ---------------------------------------------------------------------------
// Name:      actSCardTokenKit.h
// Product:   cv act library
// Purpose:   registry for factory functions to create SCardOS and SCardToken objects
//            
// Copyright: (c) 2002 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//
// Autor:	  Dr. Xiangdong Wang (XWG)
// Date:	  05/14/2002
// ---------------------------------------------------------------------------

#ifndef ACT_SCardTokenKit_h
#define ACT_SCardTokenKit_h

namespace act
{
	class ISCardOS;
	class SCardToken;

	bool IsV4cvProfile(ISCardOS* os);
	SCardToken* CreateV4cvProfile(ISCardOS* os);

	bool IsV4cvECProfile(ISCardOS* os);
	SCardToken* CreateV4cvECProfile(ISCardOS* os);

	bool IsNetKey30Token(ISCardOS* os);
	SCardToken* CreateNetKey30Token(ISCardOS* os);

	bool IsSigntrustToken(ISCardOS* os);
	SCardToken* CreateSigntrustToken(ISCardOS* os);

	bool IsM4cvProfile(ISCardOS* os);
	SCardToken* CreateM4cvProfile(ISCardOS* os);

	bool IsACOScvProfile(ISCardOS* os);
	SCardToken* CreateACOScvProfile(ISCardOS* os);

	bool IsM4cvECProfile(ISCardOS* os);
	SCardToken* CreateM4cvECProfile(ISCardOS* os);

	bool IsM4cvMoCProfile(ISCardOS* os);
	SCardToken* CreateM4cvMoCProfile(ISCardOS* os);

	bool IsJavaCardAppletManager(ISCardOS* os);
	SCardToken* CreateJavaCardAppletManager(ISCardOS* os);

	bool IsJCProfile(ISCardOS* os);
	SCardToken* CreateJCProfile(ISCardOS* os);

	// PKCS#15 Profiles
	bool IsM4PKCS15Profile(ISCardOS* os);
	SCardToken* CreateM4PKCS15Profile(ISCardOS* os);

	bool IsV4PKCS15Profile(ISCardOS* os);
	SCardToken* CreateV4PKCS15Profile(ISCardOS* os);

	bool IsV4PKCS15ECProfile(ISCardOS* os);
	SCardToken* CreateV4PKCS15ECProfile(ISCardOS* os);

	bool IsJCPKCS15Profile(ISCardOS* os);
	SCardToken* CreateJCPKCS15Profile(ISCardOS* os);

	bool IsJCPKCS15ECProfile(ISCardOS* os);
	SCardToken* CreateJCPKCS15ECProfile(ISCardOS* os);

	bool IsACOSPKCS15Profile(ISCardOS* os);
	SCardToken* CreateACOSPKCS15Profile(ISCardOS* os);

	bool IsStarCOSPKCS15Profile(ISCardOS* os);
	SCardToken* CreateStarCOSPKCS15Profile(ISCardOS* os);

	//bool IsSECCOSPKCS15Profile(ISCardOS* os);
	//SCardToken* CreateSECCOSPKCS15Profile(ISCardOS* os);

	bool IsStudentCardProfile(ISCardOS* os);
	SCardToken* CreateStudentCardProfile(ISCardOS* os);

	// Passport
	bool IsEPAProfile(ISCardOS* os);
	SCardToken* CreateEPAProfile(ISCardOS* os);

#if 0
	// deprecated tokens
	bool IsStarCOSToken(ISCardOS* os);					
	SCardToken* CreateStarCOSToken(ISCardOS* os);

	bool IsV4CNSProfile(ISCardOS* os);
	SCardToken* CreateV4CNSProfile(ISCardOS* os);

	bool IsNetKey2000Token(ISCardOS* os);
	SCardToken* CreateNetKey2000Token(ISCardOS* os);

	bool IsNetKeyE4Token(ISCardOS* os);
	SCardToken* CreateNetKeyE4Token(ISCardOS* os);

	bool IsNetKeyPKSToken(ISCardOS* os);
	SCardToken* CreateNetKeyPKSToken(ISCardOS* os);

	bool IsNetKeyOldToken(ISCardOS* os);
	SCardToken* CreateNetKeyOldToken(ISCardOS* os);

	bool IseTrustToken(ISCardOS* os);
	SCardToken* CreateeTrustToken(ISCardOS* os);

	bool IsMicardoECToken(ISCardOS* os);
	SCardToken* CreateMicardoECToken(ISCardOS* os);

	bool IsM4SiemensProfile(ISCardOS* os);
	SCardToken* CreateM4SiemensProfile(ISCardOS* os);

#endif

} // namespace act

#endif // ACT_SCardTokenKit_h
