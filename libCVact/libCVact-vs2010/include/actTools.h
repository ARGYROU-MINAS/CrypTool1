//////////////////////////////////////////////////////////////////////////////////
// Name:      actTools.h
// Product:   cv act library
// Purpose:   useful global functions
//
// Copyright: (c) 2000 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_Tools_h
#define ACT_Tools_h

#include "actMode.h"
#include "actBlob.h"

namespace act
{
	class IKey;
	class IHashAlg;

	// Functions for RSA public key and private key operation.
	// Both functions return the plain result of the modular
	// exponentiation using the public or private exponent.
	//
	// 1) Calculate m^e mod n, where e is the public exponent
	Blob RSAPublicKeyOperation(IKey* rsa_key, const Blob& m); 
	// 2) Calculate c^d mod n, where d is the private exponent
	Blob RSAPrivateKeyOperation(IKey* rsa_key, const Blob& c); 


	// Function for PKCS#3 Diffie-Hellman.
	// The function initializes an act::IKey Diffie-Hellman key object
	// from PKCS#3 DH parameters p and g (prime and generator).
	void PKCS3DHKeyToDHKey(const Blob& prime, const Blob& generator, IKey *dhKey); 


	// Read pfx file and get private key
	Blob getPKCS8Key(const Blob& pfx_data, const char* password);
	// Read pfx file and get the own (user) certificate
	Blob getOwnCertificateFromPfx(const Blob& pfx_data, const char* password);


	// PKCS#1 Mask Generation Function 1 (MGF1)
	Blob MGF1(const Blob& seed, const size_t maskLen, IHashAlg* hash);


	// Function to encode an ASN1 object identifier in binary form
	// example EncodeOID("0.2.262.1.10.1.3.8") = { 0x02, 0x82, 0x06, 0x01, 0x0A, 0x01, 0x03, 0x08 }
	Blob EncodeOID(const char* oid);


	// Converts a signed decimal number or hexadecimal number (with prefix "0x" / "-0x")
	// into a Blob (Twos-Complement representation for negative numbers)
	Blob EncodeNumber(const char* number);
	Blob EncodeNumber(int number);


	// CRC functions

	// CRC-16   (direct mode, no zero bit augmentation)
	//
	// Poly   : 0x8005   (x^16 + x^15 + x^2 + 1)
	// RefIn  : True     (bit reflection on the input bytes)
	// RefOut : True     (bit reflection on the final CRC value)
	// XorOut : 0x0000   (no XOR on the returned CRC value)
	unsigned long CalculateCRC16(const act::byte* message, size_t message_len, 
		unsigned long crc_init_value = 0x0000);
	unsigned long CalculateCRC16(const act::Blob& message, 
		unsigned long crc_init_value = 0x0000);

	// CRC-16 CCIT   (direct mode, no zero bit augmentation)
	//
	// Poly   : 0x1021   (x^16 + x^12 + x^5 + 1)
	// RefIn  : False    (no bit reflection on the input bytes)
	// RefOut : False    (no bit reflection on the final CRC value)
	// XorOut : 0x0000   (no XOR on the returned CRC value)
	unsigned long CalculateCRC16CCITT(const act::byte* message, size_t message_len,
		unsigned long crc_init_value = 0xFFFF);
	unsigned long CalculateCRC16CCITT(const act::Blob& message, 
		unsigned long crc_init_value = 0xFFFF);

	// CRC-32   (direct mode, no zero bit augmentation)
	//
	// Poly   : 0x04C11DB7   (x^32 + x^26 +  x^23 + x^22 + x^16 + x^12 + x^11 + ...
	//                         ... + x^10 + x^8 + x^7 + x^5 + x^4 + x^2 + x^ + 1)
	// RefIn  : True         (bit reflection on the input bytes)
	// RefOut : True         (bit reflection on the final CRC value)
	// XorOut : 0xFFFFFFFF   (XOR on the returned CRC value)
	unsigned long CalculateCRC32(const act::byte* message, size_t message_len,
		unsigned long crc_init_value = 0xFFFFFFFF);
	unsigned long CalculateCRC32(const act::Blob& message, 
		unsigned long crc_init_value = 0xFFFFFFFF);

} // namespace act

#endif // ACT_Tools_h
