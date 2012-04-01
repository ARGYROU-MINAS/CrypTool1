//////////////////////////////////////////////////////////////////////////////////
// Name:      actInit.h
// Product:   cv act library
// Purpose:   initialize the map entries of the objects
//
// Copyright: (c) 2007 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
// remarks:
//			  declare NO_SMARTCARD: no smartcard support required. 
//////////////////////////////////////////////////////////////////////////////////

#ifndef actInit_h
#define actInit_h

#include "actEnv.h"
#include "actKeyKit.h"
#include "actKeyReg.h"
#include "actKeyInfoKit.h"
#include "actKeyInfoReg.h"
#include "actBlockCipherKit.h"
#include "actBlockCipherReg.h"
#include "actBlockCipherModeReg.h"
#include "actBlockCipherModeKit.h"
#include "actStreamCipherKit.h"
#include "actStreamCipherReg.h"
#include "actHashKit.h"
#include "actHashReg.h"
#include "actEMSAReg.h"
#include "actEMSAKit.h"
#include "actDerivatorReg.h"
#include "actDerivatorKit.h"
#include "actPaddingReg.h"
#include "actPaddingKit.h"
#include "actCertificateReg.h"
#include "actCertificateKit.h"
#include "actX509KeyReg.h"
#include "actX509SignReg.h"
#include "actX509SignHashReg.h"
#include "actX509Kit.h"
#include "actDefaultRNG.h"
#include "actRNGKit.h"

#ifndef NO_SMARTCARD
//	NOTE: To Enable support for additional smartcards / profiles define:
#	if 0
#		define ACT_SUPPORT_TCOS_NETKEY30
#		define ACT_SUPPORT_SIGNTRUST_SC32
#	endif
#	include "actSCardOSReg.h"
#	include "actSCardOSKit.h"
#	include "actSCardTokenReg.h"
#	include "actSCardTokenKit.h"
#	include "actSubsystemReg.h"
#	include "actSubsystemKit.h"
#	include "actSlotMonitorReg.h"
#	include "actSlotMonitorKit.h"
#	include "actTokenExtensionReg.h"
#	include "actTokenExtensionKit.h"
#	include "actTokenInitializerReg.h"
#	include "actTokenInitializerKit.h"
#	include "actTokenAuthProtocolReg.h"
#	include "actTokenAuthProtocolKit.h"
#	include "actJCAppletKit.h"
#	include "actJCAppletReg.h"
#	include "actPKCS15BehaviorReg.h"
#	include "actPKCS15BehaviorKit.h"
#	include "actProfileGeneratorReg.h"
#	include "actProfileGeneratorKit.h"
#endif // NO_SMARTCARD

#if defined(ACT_WIN32) && !defined(ACT_MINGW)
#	define  ACT_INIT_MS_CAPI
#endif

namespace act
{
	// ------------------------------------------------------------------------
	const KeyMapEntry KeyMap[] =
	{
		{ "BlockCipher", CreateBlockCipherKey },
		{ "StreamCipher", CreateStreamCipherKey },

		{ "IES", CreateIESKey },
		{ "DSA", CreateDSAKey }, 
		{ "RSA", CreateRSAKey },
		{ "ECDSA", CreateECDSAKey },
		{ "ECGDSA", CreateECGDSAKey },

		{ "DH",	CreateDHKey },
		{ "ECDH",	CreateECDHKey },
	
		{ "HashMAC", CreateHashMACKey },
		{ "CBCMAC", CreateCBCMACKey },
		{ "SecretKeyMAC", CreateSecretKeyMACKey },
		{ "RetailCFBMAC", CreateRetailCFBMACKey },
		{ "iMAC3", Create_iMAC3Key },				// ISO9797-1 M2 Alg 3 MAC8
		{ "CMAC", CreateCMACKey },					// NIST 800-38B CMAC
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const KeyInfoMapEntry KeyInfoMap[] =
	{
		{ "PKCS8", CreatePKCS8 },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const BlockCipherMapEntry BlockCipherMap[] = 
	{
		{ "AES", CreateRijndael },
		{ "DES", CreateDES },
		{ "TripleDES", CreateTripleDES },
		{ "CAST128", CreateCAST128 },
		{ "BlowFish", CreateBlowFish },
		{ "Mars", CreateMars },
		{ "Serpent", CreateSerpent },
		{ "Rijndael", CreateRijndael },
		{ "TwoFish", CreateTwoFish },
		{ "RC2", CreateRC2 },
		//{ "RC6", CreateRC6 },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const BlockCipherModeMapEntry BlockCipherModeMap[] = 
	{
		{ "ECB", CreateECBMode },
		{ "CBC", CreateCBCMode },
		{ "CFB", CreateCFBMode },
		{ "OFB", CreateOFBMode },
		{ "CTR", CreateCTRMode },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const StreamCipherMapEntry StreamCipherMap[] = 
	{
		{ "ARC4", CreateARC4 },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const HashMapEntry HashMap[] = 
	{
		{ "MD2", CreateMD2 },
		{ "MD4", CreateMD4 },
		{ "MD5", CreateMD5 },
		{ "RIPEMD128", CreateRipemd128 },
		{ "RIPEMD160", CreateRipemd160 },
		// { "SHA0", CreateSHA0 },					// deprecated
		{ "SHA1", CreateSHA1 },
		{ "SHA224", CreateSHA224 },
		{ "SHA256", CreateSHA256 },					// needed for seed polling of any PRNG
		{ "SHA384", CreateSHA384 },
		{ "SHA512", CreateSHA512 },
		{ "DummyHash", CreateDummyHash },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const EMSAMapEntry EMSAMap[] = 
	{
		{ "EMSA1", CreateEMSA1 },
		{ "PKCS1V1_5EMSA", CreatePKCS1V1_5EMSA },
		{ "TLS_EMSA", CreateTLS_EMSA},
		{ "PKCS1_PSS_EMSA", CreatePKCS1_PSS_EMSA },
		{ "DummyEMSA", CreateDummyEMSA },			// Used for "Hash on Card"
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const DerivatorMapEntry DerivatorMap[] = 
	{
		{ "KDF1", CreateKDF1 },						// IEEE P1363 KDF1
		{ "KDF2", CreateX963KDF },					// IEEE P1363 KDF2 (= X963KDF)
		{ "X963KDF", CreateX963KDF },				// ANSI X9.63 KDF
		{ "PBKDF1", CreatePBKDF1 },					// PKCS#5 PBKDF1
		{ "PBKDF2", CreatePBKDF2 },					// PKCS#5 PBKDF2
		{ "EACKDF", CreateEACKDF },					// EAC 2.01, BSI TR-03110 A.2.3
		{ "SessionKDF", CreateEACKDF },				// BSI TR-03111 (= EACKDF)
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const PaddingMapEntry PaddingMap[] = 
	{
		{ "PKCS5", CreatePKCS5Pad },
		{ "RSAES", CreatePKCS1V1_5EMEPad },
		{ "ISO", CreateOneAndZerosPad },
		{ "ISO9796", CreateISO9796Pad },
		{ "NOPAD", CreateNoPad },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const CertificateMapEntry CertificateMap[] = 
	{
		{ "X509", CreateX509Certificate },
		{ "CV", CreateCVCertificate },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const CRLMapEntry CRLMap[] = 
	{
		{ "X509", CreateX509CRL },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const X509KeyMapEntry X509KeyMap[] =
	{
		{ "1.2.840.113549.1.1.1", CreateRSAKey, X509ToRSA, RSAToX509 },		// rsaEncryption
		//{ "1.2.840.113549.1.1.7", CreateRSAKey, X509ToRSA, RSAToX509 },	// id-RSAES-OAEP (tbd)
		{ "1.2.840.113549.1.1.10", CreateRSAKey, X509ToRSA, RSAToX509 },	// id-RSASSA-PSS
		{ "2.5.8.1.1", CreateRSAKey, X509ToRSA, RSAToX509 },				// id-ea-rsa 
		{ "1.2.840.10040.4.1", CreateDSAKey, X509ToDSA, DSAToX509 },
		{ "1.3.14.3.2.20", CreateDSAKey, X509ToDSA, DSAToX509 },
		{ "1.3.14.3.2.12", CreateDSAKey, X509ToDSA, DSAToX509 },			// secude DSA oid
		{ "1.2.840.10046.2.1", CreateDHKey, X509ToDH, DHToX509 },
		{ "1.2.840.10045.2.1", CreateECDSAKey, X509ToECDSA, ECDSAToX509 },
		{ "1.2.840.10045.2.1", CreateECDHKey, X509ToECDSA, ECDSAToX509 },
		{ 0, 0, 0, 0 }
	};

	// ------------------------------------------------------------------------
	const X509SignMapEntry X509SignMap[] =
	{
		{ CreateRSAKey, RSAGetAlgID, RSASetAlgID },
		{ CreateDSAKey, DSAGetAlgID, DSASetAlgID },
		{ CreateECDSAKey, ECDSAGetAlgID, ECDSASetAlgID },
		{ CreateDHKey, DHGetAlgID, DHSetAlgID },
		{ CreateECDHKey, ECDHGetAlgID, ECDHSetAlgID },
		{ 0, 0, 0 }
	};

	// ------------------------------------------------------------------------
	const X509SignHashMapEntry X509SignHashMap[] =
	{
		// RSA
		{ "1.2.840.113549.1.1.2",	"MD2",			"RSA" },	// md2WithRSAEncryption
		{ "1.2.840.113549.1.1.3",	"MD4",			"RSA" },	// md4WithRSAEncryption
		{ "1.2.840.113549.1.1.4",	"MD5",			"RSA" },	// md5WithRSAEncryption
		{ "1.2.840.113549.1.1.5",	"SHA1",			"RSA" },	// shaWithRSAEncryption
		{ "1.3.14.3.2.29",			"SHA1",			"RSA" },
		{ "1.2.840.113549.1.1.11",	"SHA256",		"RSA" },	// sha256WithRSAEncryption
		{ "1.2.840.113549.1.1.12",	"SHA384",		"RSA" },	// sha384WithRSAEncryption
		{ "1.2.840.113549.1.1.13",	"SHA512",		"RSA" },	// sha512WithRSAEncryption
		{ "1.2.840.113549.1.1.14",	"SHA224",		"RSA" },	// sha224WithRSAEncryption
		{ "1.3.36.3.3.1.2",			"RIPEMD160",	"RSA" },
		{ "1.3.36.3.3.1.3",			"RIPEMD128",	"RSA" },
		// DSA
		{ "1.2.840.10040.4.3",		"SHA1",			"DSA" },
		{ "1.3.14.3.2.28",			"SHA1",			"DSA" },
		{ "1.3.14.3.2.27",			"SHA1",			"DSA" },	// secude DSA oid
		// ECDSA
		{ "1.2.840.10045.4.1",		"SHA1",			"ECDSA" },	// ecdsa-with-Sha1
		{ "1.2.840.10045.2.1",		"SHA1",			"ECDSA" },	// ecdsa-with-Sha1 (deprecated)
		{ "1.2.840.10045.4.3.1",	"SHA224",		"ECDSA" },	// ecdsa-with-Sha224
		{ "1.2.840.10045.4.3.2",	"SHA256",		"ECDSA" },	// ecdsa-with-Sha256
		{ "1.2.840.10045.4.3.3",	"SHA384",		"ECDSA" },	// ecdsa-with-Sha384
		{ "1.2.840.10045.4.3.4",	"SHA512",		"ECDSA" },	// ecdsa-with-Sha512

		{ "0.4.0.127.0.7.4.1.1",	"SHA1",			"ECDSA" },	// BSI
		{ "0.4.0.127.0.7.4.1.2",	"SHA224",		"ECDSA" },	// 
		{ "0.4.0.127.0.7.4.1.3",	"SHA256",		"ECDSA" },	// 
		{ "0.4.0.127.0.7.4.1.4",	"SHA384",		"ECDSA" },	// 
		{ "0.4.0.127.0.7.4.1.5",	"SHA512",		"ECDSA" },	// 
		// DH
		{ "1.3.6.1.5.5.7.6.4",		"SHA1",			"DH" },		// DH-POP
		// ECDH
		{ "1.2.840.10045.2.1",		"SHA1",			"ECDH" },	// "ECDH-POP"
		{ 0, 0, 0 }
	};

#ifndef NO_SMARTCARD
	// ------------------------------------------------------------------------
	const SCardOSMapEntry SCardOSMap[] = 
	{
		// NOTE: Only lower case historical bytes !
		/*
		{ "0064050a020131809000", CreateTCOS },						// NetKey (TCOS V2R1)
		{ "00640560020331809000", CreateTCOS },						// NetKey (TCOS V2R3)
		{ "0064057b020331809000", CreateTCOS },						// NetKey (TCOS V2R?)
		{ "00640514020231809000", CreateTCOS },						// etrust (TCOS V2R2)
		{ "00640561020331809000", CreateTCOS },						// TCOS USB Crypt Token
		{ "0068d276000028ff051e3180009000", CreateMicardOS },		// Micardo P2.1
		{ "4d4943323045", CreateMicardo20E },						// Micardo EC 2.0
		{ "0068d276000028ff05233180009000", CreateMicardo23E },		// Micardo EC 2.3
		*/

		// ACOS
		{ "454d56203033202006", CreateACOS_D01 },					// Austria Card ACOS EMV-D01
		{ "44492030324d", CreateACOS_D01 },							// Austria Card ACOS EMV-D01 contactless
		{ "455041000000000228505900000000", CreateACOS_A04 },		// Austria Card ACOS EMV-A04/A05
		{ "455041000000000000000000000000", CreateACOS_A04 },		// Austria Card ACOS EMV-A04/A05

		// CardOS
		{ "c802", CreateCardOS_M4 },								// CardOS M4.0		siemens profile
		{ "c803", CreateCardOS_M4 },								// CardOS M4.01		siemens profile
		{ "c804", CreateCardOS_M4 },								// CardOS M4.01a	siemens profile
		{ "4d346376", CreateCardOS_M4 },							// CardOS M4.01(a)	cv profile
		{ "4d3463765f4d", CreateCardOS_M4_MoC },					// CardOS M4.01_M cv profile
		{ "4d3463765f45", CreateCardOS_M4_ECC },					// CardOS M4.01_E cv profile
		{ "c806", CreateCardOS_V4 },								// CardOS V4.2
		{ "c807", CreateCardOS_V4 },								// CardOS V4.3
		{ "c808", CreateCardOS_V4 },								// CardOS V4.3B
		{ "c809", CreateCardOS_V4 },								// CardOS V4.2B
		{ "c80a", CreateCardOS_V4 },								// CardOS V4.2B DI
		{ "0000c80a3381b100", CreateCardOS_V4 },					// CardOS V4.2B DI contactless
		{ "c80b", CreateCardOS_V4 },								// CardOS V4.2C
		{ "c80d", CreateCardOS_V4 },								// CardOS V4.4
		{ "56346376", CreateCardOS_V4 },							// CardOS V4.2/4.3/4.3B	cv profile
		{ "563432626376", CreateCardOS_V4 },						// CardOS V4.2b	cv profile
		{ "5634326244496376", CreateCardOS_V4 },					// CardOS V4.2b	DI cv profile
		{ "563432636376", CreateCardOS_V4 },						// CardOS V4.2c	cv profile
		{ "5634346376", CreateCardOS_V4 },							// CardOS V4.4 cv profile
		{ "563463765f45", CreateCardOS_V4_ECC },					// CardOS V4.3B	ECC cv profile
		{ "006b0508c806012101434e53103180", CreateCardOS_V4 },		// CardOS V4.2	CNS profile, 2004.02.20
		{ "006b0508c807012101434e53103180", CreateCardOS_V4 },		// CardOS V4.3	CNS profile, 2004.02.20
		{ "006b0508c808012101434e53103180", CreateCardOS_V4 },		// CardOS V4.3B	CNS profile, 2004.02.20
		{ "006b0508c806011101434e53103180", CreateCardOS_V4 },		// CardOS V4.2	CNS profile, 2005.03.11
		{ "006b0508c807011101434e53103180", CreateCardOS_V4 },		// CardOS V4.3	CNS profile, 2005.03.11
		{ "006b0508c808011101434e53103180", CreateCardOS_V4 },		// CardOS V4.3B	CNS profile, 2005.03.11
		{ "006b0508c808011101434e53103180", CreateCardOS_V4 },		// CardOS V4.3B	CNS profile, 2005.03.11
		{ "4b53776973735369676e", CreateCardOS_V4 },				// CardOS V4.3B/V4.4 ATR by SwissSign

		// STARCOS
		{ "53504b32339000", CreateStarCOS_2_3},						// G&D STARCOS SPK 2.3
		{ "53504b32349000", CreateStarCOS_2_4},						// G&D STARCOS SPK 2.4
		{ "80670412b0030300008101", CreateStarCOS_3_0 },			// G&D STARCOS 3.0 (creational state)
		{ "80670412b0030300008105", CreateStarCOS_3_0 },			// G&D STARCOS 3.0
		{ "80670412b003030000", CreateStarCOS_3_0 },				// G&D STARCOS 3.0 contactless
		{ "80655343010d067394211b8101", CreateStarCOS_3_1 },		// G&D STARCOS 3.1 (creational state)
		{ "80655343010d067394211b8105", CreateStarCOS_3_1 },		// G&D STARCOS 3.1
		{ "0064051eb20031b0739621db019000", CreateStarCOS_3_2 },	// G&D STARCOS 3.2 (creational state)
		{ "0064051eb20031b0739621db059000", CreateStarCOS_3_2 },	// G&D STARCOS 3.2

		{ "8064041bb42a8105", CreateStarCOS_3_4 },					// G&D STARCOS 3.4 (Health Card), VKplus 2010/12
		{ "8067041bb42200c0818105", CreateStarCOS_3_4 },			// G&D STARCOS 3.4 (Health Card), VKplus 2012 (test card 1)
		{ "8031b052010364041bb4228105", CreateStarCOS_3_4 },		// G&D STARCOS 3.4 (Health Card), VKplus 2012 (test card 2)
		{ "8067041bb42a000a028105", CreateStarCOS_3_4 },			// G&D STARCOS 3.4 (Health Card), VKplus 2012 (test card 3)
		   
		// SECCOS (NOTE: used for sc/i card registry mapping)
		{ "6563110c5302500010ab0b21230650", CreateSECCOS_6 },		// SECCOS 6
		{ "8031c073d621c0", CreateSECCOS_6 },						// SECCOS 6 contactless 

		// TCOS
#ifdef	ACT_SUPPORT_TCOS_NETKEY30
		{ "00640411030131c073f701d0009000", CreateTCOS_3_0 },		// NetKey (TCOS 3.0)
#endif
		// JavaCards
		{ "8073002113574a544861314a00", CreateJavaCardOS_2_2 },		// G&D SmartCafe Expert 64  (cfg1)
		{ "8073002113574a544861314700", CreateJavaCardOS_2_2 },		// G&D SmartCafe Expert 64  (cfg2)
		{ "8073002113574a544861314800", CreateJavaCardOS_2_2 },		// G&D SmartCafe Expert 64  (cfg3)
		{ "8073002113574a544861314b00", CreateJavaCardOS_2_2 },		// G&D SmartCafe Expert 64  (cfg4)
		{ "8073002113574a544861314c00", CreateJavaCardOS_2_2 },		// G&D SmartCafe Expert 64  (cfg5)
		{ "8073002113574a544861314900", CreateJavaCardOS_2_2 },		// G&D SmartCafe Expert 64  (cfg8)
		{ "404d4f504153530000000000000000", CreateJavaCardOS_2_2 },	// G&D SmartCafe Expert 64  (XMC2)

		{ "534653452d43583332322d56180308", CreateJavaCardOS_2_1_1 },// G&D SmartCafe Expert 2.0
		{ "0073c84013009000", CreateJavaCardOS_2_2_1 },				// G&D SmartCafe Expert 3.0 / 3.1 / 3.1 contactless
		{ "4138004133b1020073c840130090", CreateJavaCardOS_2_2_1 },	// G&D SmartCafe Expert 3.1 contactless (SCM SDI010, Firmware V6.28)
		{ "4138004133b10073c84013009000", CreateJavaCardOS_2_2_1 },	// G&D SmartCafe Expert 3.1 contactless (SCM SDI010, Firmware V6.32)
		{ "73667465206364313434", CreateJavaCardOS_2_2_1 },			// G&D SmartCafe Expert 3.2 PIV 144 KB
		{ "736674652D6364303830", CreateJavaCardOS_2_2_1 },			// G&D SmartCafe Expert 3.2 PIV 80 KB
		{ "73667465", CreateJavaCardOS_2_2_1 },						// G&D SmartCafe Expert 3.2 (sfte)
		{ "736674652d6e66", CreateJavaCardOS_2_2_1 },				// G&D SmartCafe Expert 3.2 (sfte-nf)
		{ "73c840130090009b", CreateJavaCardOS_2_2_1 },				// G&D SmartCafe Expert 3.2 USB Token
		{ "736674652063643038302d6e66", CreateJavaCardOS_2_2_1 },	// G&D SmartCafe Expert 3.2 (sfte cd080-nf)
		{ "736674652063643134342d6e66", CreateJavaCardOS_2_2_1 },	// G&D SmartCafe Expert 3.2 (sfte cd144-nf)
		{ "53462d3443432d3031", CreateJavaCardOS_2_2_1 },			// G&D SmartCafe Expert 5.0
		{ "53504b323544499000", CreateJavaCardOS_2_2_1 },			// G&D Mobile Security Card 3.x
		{ "4d5343", CreateJavaCardOS_2_2_1 },						// G&D Mobile Security Card 3.x

		{ "43475346533032", CreateJavaCardOS_2_2_2 },				// certgate microSD (G&D SmartCafe Expert 5.0)

		//{ "4a434f503230", CreateJavaCardOS_2_1 },					// JCOP 20
		{ "4a434f503231563232", CreateJavaCardOS_2_2_1 },			// JCOP 21 V2.2
		{ "4a434f50323156323331", CreateJavaCardOS_2_2_1 },			// JCOP 21 V2.3.1
		{ "4a434f50323156323431", CreateJavaCardOS_2_2_2 },			// JCOP 21 V2.4.1
		{ "4a434f503331563231", CreateJavaCardOS_2_1 },				// JCOP 31 V2.1
		{ "4a434f503331563232", CreateJavaCardOS_2_2_1 },			// JCOP 31 V2.2
		{ "4a434f50333156323331", CreateJavaCardOS_2_2_1 },			// JCOP 31 V2.3.1
		{ "4a434f503331563234", CreateJavaCardOS_2_2_1 },			// JCOP 31 V2.4
		{ "4a434f50333156323431", CreateJavaCardOS_2_2_2 },			// JCOP 31 V2.4.1
		//{ "4a434f5033313336474454", CreateJavaCardOS_2_2_1 },		// JCOP 31 36GDT
		{ "4a434f503431563232", CreateJavaCardOS_2_2_1 },			// JCOP 41 V2.2 / V2.2 contactless
		{ "4128001133b04a434f5034315632", CreateJavaCardOS_2_2_1 },	// JCOP 41 V2.2 contactless (SCM SDI010, Firmware V6.32)
		{ "4a434f50343156323231", CreateJavaCardOS_2_2_1 },			// JCOP 41 V2.2.1
		{ "4138001133b04a434f5034315632", CreateJavaCardOS_2_2_1 },	// JCOP 41 V2.2.1 contactless
		{ "4a434f50343156323331", CreateJavaCardOS_2_2_1 },			// JCOP 41 V2.3.1
		{ "4a434f50343156323332", CreateJavaCardOS_2_1_1 },			// JCOP 41 V2.3.2
		{ "4a434f503431563234", CreateJavaCardOS_2_2_1 },			// JCOP 41 V2.4
		{ "4a434f50343156323431", CreateJavaCardOS_2_2_2 },			// JCOP 41 V2.4.1
		{ "434f50343156323231ff", CreateJavaCardOS_2_2_1 },			// JCOP 41 V2.2.1 (IDptoken 200)
		{ "4a434f507632343262657461", CreateJavaCardOS_2_2_2 },		// JCOP v2.4.2 beta
		{ "0073c84000009000", CreateJavaCardOS_2_1_1 },				// JCOP V2.3.2

		{ "4a434f50563231", CreateJavaCardOS_2_1 },					// JCOP V2.1
		{ "4a434f50563232", CreateJavaCardOS_2_2_1 },				// JCOP V2.2
		{ "4a434f5056323231", CreateJavaCardOS_2_2_1 },				// JCOP V2.2.1
		{ "4a434f50563233", CreateJavaCardOS_2_2_1 },				// JCOP V2.3
		{ "4a434f5056323331", CreateJavaCardOS_2_2_1 },				// JCOP V2.3.1
		{ "4a434f5056323332", CreateJavaCardOS_2_1_1 },				// JCOP V2.3.2
		{ "4a434f50563234", CreateJavaCardOS_2_2_1 },				// JCOP V2.4
		{ "4a434f5056323431", CreateJavaCardOS_2_2_2 },				// JCOP V2.4.1
		{ "4a434f5076323431", CreateJavaCardOS_2_2_2 },				// JCOP v2.4.1 (yes, lowercase 'v')
		{ "4a434f5056323432", CreateJavaCardOS_2_2_2 },				// JCOP V2.4.2

		{ "454f4e436172645631", CreateJavaCardOS_2_2_2 },			// EONCardV1 (JCOP V2.4.1)

		{ "4a434f5033314d34", CreateJavaCardOS_2_2_1 },				// Austriacard JCOP31M4
		{ "4a434f5032315632325f", CreateJavaCardOS_2_2_1 },			// AustriaCard JCOP 21 V2.2, T0, T1
		{ "4a434f5033315632325f", CreateJavaCardOS_2_2_1 },			// AustriaCard JCOP 31 V2.2, T0, T1
		{ "4a434f5034315632345f", CreateJavaCardOS_2_2_1 },			// AustriaCard JCOP 41 V2.4, T0, T1
		{ "4a434f50563234314143", CreateJavaCardOS_2_2_1 },			// AustriaCard JCOP V2.4.1, T0, T1
		
		{ "5257414e44415f4944", CreateJavaCardOS_2_2_1 },			// AustriaCard JCOP V2.4.1 'RWANDA_ID'
		{ "44654c61527565", CreateJavaCardOS_2_2_1 },				// AustriaCard JCOP V2.4.1 'DeLaRue'

		{ "803180664090a4561b1183019000", CreateJavaCardOS_2_2_1 },	// Infineon JCLX80 jTOP 20ID
		{ "803180664090a4162ae283019000", CreateJavaCardOS_2_2_1 },	// Infineon JCLX80 jTOP 20ID v2
		{ "000000007783b300", CreateJavaCardOS_2_2_1 },				// Infineon JCLX80 jTOP 20ID v2 contactless
		{ "803180664090a2162c1283019000", CreateJavaCardOS_2_2_1 },	// Infineon JCLX80 jTOP 20ID v3
		{ "803180664090a2162c0183019000", CreateJavaCardOS_2_2_1 },	// Infineon JCLX80 jTOP 20ID v3 contactless

		{ "80318065b0831148c883009000", CreateJavaCardOS_2_2_1 },	// Gemalto TOP IM GX4
		//{ "80318065b08301029083009000", CreateJavaCardOS_2_2_1 },	// Gemalto I-DENTITY CARD
		{ "8065b08301017483009000", CreateJavaCardOS_2_1_1 },		// Gemplus GemXpresso Pro R3
		{ "8065b08301037483009000", CreateJavaCardOS_2_1_1 },		// Gemplus GemXpresso Pro R3
		//{ "8065a20101013d72d643", CreateJavaCardOS_2_1_1 },		// Gemplus GemXpresso Pro R3 E32 PK

		{ "0031c06477e30300829000", CreateJavaCardOS_2_1_1 },		// Oberthur CosmopolIC 64K v5.2D

		{ "8059017f4849444a43327300011b", CreateJavaCardOS_2_2_2 },	// HID Crescendo C700 (JC2s) ("Standard JavaCard, T0/1, Platform Default Packages")
		{ "804f0ca0000003060a001d00000000", CreateJavaCardOS_2_2_2 },// HID Crescendo C700 (JC2s) contactless

		{ ACT_ISO7816OS_NAME, CreateISO7816OS },					// use act::ISO7816OS as fallback
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const SCardOSFactoryEntry SCardOSMapEx[] = 
	{
		{ DetectSECCOS_6, CreateSECCOS_6 },
		{ DetectSECCOS_5, CreateSECCOS_5 },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const SCardOSDerivationMapEntry SCardOSDerivationMap[] =
	{
		{ "JavaCardOS_ECC", DeriveJavaCardOS_ECC },
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const SCardTokenMapEntry SCardTokenMap[] = 
	{
		// Passport
		{ IsEPAProfile, CreateEPAProfile },

		// PKCS#15
		{ IsM4PKCS15Profile, CreateM4PKCS15Profile },
		{ IsV4PKCS15ECProfile, CreateV4PKCS15ECProfile },
		{ IsV4PKCS15Profile, CreateV4PKCS15Profile },
		{ IsJCPKCS15ECProfile, CreateJCPKCS15ECProfile },
		{ IsJCPKCS15Profile, CreateJCPKCS15Profile },
		{ IsACOSPKCS15Profile, CreateACOSPKCS15Profile },
		{ IsStarCOSPKCS15Profile, CreateStarCOSPKCS15Profile },
		//{ IsSECCOSPKCS15Profile, CreateSECCOSPKCS15Profile },

		// ACOS
		{ IsACOScvProfile, CreateACOScvProfile },

		// CardOS
		{ IsM4cvMoCProfile, CreateM4cvMoCProfile },
		{ IsM4cvECProfile, CreateM4cvECProfile },
		{ IsV4cvECProfile, CreateV4cvECProfile },
		{ IsV4cvProfile, CreateV4cvProfile },
		{ IsM4cvProfile, CreateM4cvProfile },
		// { IsV4CNSProfile, CreateV4CNSProfile },

		// JavaCardOS
		{ IsJCProfile, CreateJCProfile },
		// { IsJavaCardAppletManager, CreateJavaCardAppletManager },

		// third party profiles
		{ IsStudentCardProfile, CreateStudentCardProfile },						// SECCOS
#ifdef	ACT_SUPPORT_TCOS_NETKEY30
		{ IsNetKey30Token, CreateNetKey30Token },								// TCOS
#endif
#ifdef	ACT_SUPPORT_SIGNTRUST_SC32
		{ IsSigntrustToken, CreateSigntrustToken },								// STARCOS
#endif
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const TokenExtensionMapEntry TokenExtensionMap[] =
	{
		{ "MDProfileExt",						CreateMDProfileExt			},	// Minidriver FS Profile Extension

#		if defined(ACT_INIT_MS_CAPI)
		{ "EAC 2.01 TA",						CreateEACTAwithCAPI			},

#		endif
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const TokenInitializerMapEntry TokenInitializerMap[] =
	{
		{ "CardOS M4",							CreateCardOS_M4_Initializer	},
		{ "CardOS M4.01",						CreateCardOS_M4_Initializer	},
		{ "CardOS M4.01a",						CreateCardOS_M4_Initializer	},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const TokenAuthProtocolMapEntry TokenAuthProtocolMap[] =
	{
		{ "EAC 2.01 PACE",						CreateTokenAuthPACE			},
		{ "EAC 2.01 TA",						CreateTokenAuthTA			},
		{ "EAC 2.01 CA",						CreateTokenAuthCA			},
		{ "BAC",								CreateTokenAuthBAC			},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const ProfileGeneratorMapEntry ProfileGeneratorMap[] =
	{
		{ "JavaCardOS",							CreateJCPKCS15Generator		},
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const PKCS15BehaviorMapEntry PKCS15BehaviorMap[] =
	{
		{ "cv cryptovision gmbh (c) v1.0j",		CreateJCPKCS15Behavior		},
		{ "cv cryptovision gmbh (c) v1.0jEAC",	CreateJCPKCS15EACBehavior	},
		{ "cv cryptovision gmbh (c) v1.0ns",	CreateStarCOSPKCS15Behavior	},
		{ "cv cryptovision gmbh (c) v1.0n",		CreateV4PKCS15Behavior		},
		{ "cv cryptovision gmbh (c) v1.0na",	CreateACOSPKCS15Behavior	},

		// cryptovision derived (or equal to) behavior
		{ "Dexa Systems, Inc. (c) v 1.0 cf",	CreateJCPKCS15Behavior		},
		{ "Swiss Post (c) VKplus G2",			CreateECHBehavior			},

		// third party behavior
		{ "A.E.T. Europe B.V.",					CreateSafeSignBehavior		},
		{ "TC TrustCenter",						CreateTCTCSafeSignBehavior	},
		{ "Giesecke&Devrient GmbH",				CreateStarSignBehavior		},
		{ "D-TRUST GmbH (C)",					CreateDTRUSTBehavior		},
		{ "Siemens AG (C)",						CreateHiPathBehavior		},
		{ "SwissSign",							CreateHiPathBehavior		},
		{ "Technology Nexus",					CreateNexusBehavior			},
		{ "Volkswagen AG",						CreateVWBehavior			},
		{ "Signature Application",				CreateStudentCardBehavior	}, // use token label

		{ "",									CreatePKCS15Behavior		}, // default
		{ 0, 0 }
	};

	// ------------------------------------------------------------------------
	const SubsystemMapEntry SubsystemMap[] = 
	{
		{ "PCSC",	CreatePCSCSystem,	CreatePCSCSystemEx },
#	if !defined(ACT_IOS)
		{ "CTAPI",	CreateCTAPISystem,	0 },
		{ "PKCS11",	CreatePKCS11System, 0 },
#			if defined(ACT_INIT_MS_CAPI)
			{ "CSP",	CreateCSPSystem,	0 },
#			endif
#		endif
		{ 0, 0, 0 }
	};

	// ------------------------------------------------------------------------
	const SlotMonitorRegEntry SlotMonitorMap[] = 
	{
#	if !defined(ACT_IOS)

		{ "PCSC",   { CreatePCSCSlotMonitor, CreatePCSCSystemSlotMonitor } },
		{ "CTAPI",  { CreateSlotMonitor,	 0 } },
		{ "PKCS11",	{ CreateSlotMonitor,	 0 } },

#			if defined(ACT_INIT_MS_CAPI)
			{ "CSP",	{ CreateSlotMonitor,	 0 } },
#			endif
#		endif
		{ 0, { 0, 0 } }
	};

	// ------------------------------------------------------------------------
	const JCardAppletEntry JCardAppletMap[] = 
	{
		// AID if it is equal to 0 then all AID are able
		//     function  returns true if the Applet can used
		//                  creates an new applet
		//                                 number of PIN's Key's Certificate's
		//  if they are -1 then it will be checked
		//  if they are biger or equal to 0 they are const
		{ "D276000098C00000", IsJCProfileApplet, CreateJCProfileApplet, 1, 1, 0 },
		{ 0, 0, 0, 0, 0, 0 }
	};
#endif // NO_SMARTCARD

	// ------------------------------------------------------------------------
	const char* GetVersion();

	// ------------------------------------------------------------------------
	inline void Init(bool bAlwaysInit = false)
	{
		static bool loaded = false;
		if(loaded == true && bAlwaysInit == false)
			return;

		KeyReg::Insert(KeyMap);
		KeyInfoReg::Insert(KeyInfoMap);
		BlockCipherReg::Insert(BlockCipherMap);
		BlockCipherModeReg::Insert(BlockCipherModeMap);
		StreamCipherReg::Insert(StreamCipherMap);
		HashReg::Insert(HashMap);
		EMSAReg::Insert(EMSAMap);
		DerivatorReg::Insert(DerivatorMap);
		PaddingReg::Insert(PaddingMap);
		CertificateReg::Insert(CertificateMap);
		CRLReg::Insert(CRLMap);
		X509KeyReg::Insert(X509KeyMap);
		X509SignReg::Insert(X509SignMap);
		X509SignHashReg::Insert(X509SignHashMap);

#ifndef NO_SMARTCARD
		SubsystemReg::Insert(SubsystemMap);
		SlotMonitorReg::Insert(SlotMonitorMap);
		SCardOSReg::Insert(SCardOSMap);
		SCardOSReg::Insert(SCardOSMapEx);
		SCardOSDerivationReg::Insert(SCardOSDerivationMap);
		SCardTokenReg::Insert(SCardTokenMap);
		TokenExtensionReg::Insert(TokenExtensionMap);
		TokenInitializerReg::Insert(TokenInitializerMap);
		TokenAuthProtocolReg::Insert(TokenAuthProtocolMap);
		ProfileGeneratorReg::Insert(ProfileGeneratorMap);
		PKCS15BehaviorReg::Insert(PKCS15BehaviorMap);
		JCardAppletReg::Insert(JCardAppletMap);
#endif
		CreateFastRNG = CreateFIPS186;
		CreateStrongRNG = CreateFIPS186K4;
		loaded = true;
	}

} // namespace act 

#endif // actInit_h
