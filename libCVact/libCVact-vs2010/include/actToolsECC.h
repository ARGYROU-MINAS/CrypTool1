//////////////////////////////////////////////////////////////////////////////////
// Name:      actToolsECC.h
// Product:   cv act library
// Purpose:   useful ECC functions
//
// Copyright: (c) 2009 cv cryptovision GmbH
//            all rights reserved
// Licence:   The conditions for the use of this software are regulated 
//            in the cv act library licence agreement.
//////////////////////////////////////////////////////////////////////////////////

#ifndef ACT_ToolsECC_h
#define ACT_ToolsECC_h

#include "actMode.h"
#include "actBlob.h"
#include "actIKey.h"

namespace act
{
	// Functions for ECC scalar multiplication, addition of points.
	// Input points must be in ASN.1 point representation (uncompressed,
	// compressed or hybrid). The output point will be in ASN.1 representation
	// as indicated in 'output_format'. 
	//
	// 1) Calculate s * Q, s unsigned in ASN.1 OCTET STRING representation
	// (leading zeros will be ignored)
	Blob ECMultiplyPoint(IKey* ec_key, const Blob& s, const Blob& Q,
		int output_format = UNCOMPRESSED); 
	// 2) Calculate Q1 + Q2
	Blob ECAddPoints(IKey* ec_key, const Blob& Q1, const Blob& Q2, 
		int output_format = UNCOMPRESSED);


	// Functions to encode an (EC-)DSA signature (r, s) in ASN1 format and backwards.
	//
	// 1) Plain signature I/O as string
	//	  - for encode: r and s must be in hex notation
	//	  - for decode: the user has to allocate r and s buffers
	void EncodeSignature(const char* r, const char* s, Blob& signature_ASN1);
	void DecodeSignature(const Blob& signature_ASN1, char* r, char* s);
	// 2) Plain signature I/O as byte array (Blob)
	//	  - r and s I/O in big endian representation
	void EncodeSignature(const Blob& r, const Blob& s, Blob& signature_ASN1);
	void DecodeSignature(const Blob& signature_ASN1, Blob& r, Blob& s);
	// 3) Plain signature I/O as byte array (Blob)
	//	  - r_s length even, left haft = r, right half = s
	//	  - if order_bytes is non zero, decode output length is 2 * order_bytes
	void EncodeSignature(const Blob& r_s, Blob& signature_ASN1);
	void DecodeSignature(const Blob& signature_ASN1, Blob& r_s, size_t order_bytes = 0);


	// Tools for elliptic curves over GF(P).
	// The basepoint can be given by it's coordinates (Gx, Gy) or as
	// COMPRESSED, UNCOMPRESSED or HYBRID octetstring G corresponding
	// to ANSI X9.62/63 standard.
	// By default, the basepoint will be encoded in UNCOMPRESSED format.

	Blob EncodePrimeCurveParam(const Blob& p, const Blob& a, const Blob& b, 
		const Blob& Gx, const Blob& Gy, const Blob& n, const Blob& h, 
		int output_type = UNCOMPRESSED);

	Blob EncodePrimeCurveParam(const Blob& p, const Blob& a, const Blob& b, 
		const Blob& G, const Blob& n, const Blob& h, int output_type = UNCOMPRESSED);

	// dto. for elliptic curves over GF(2^m), tri- or pentanomial basis.

	// tri- or pentanomial in hex presentation
	Blob EncodeGF2CurveParam(const Blob& p, const Blob& a, const Blob& b, 
		const Blob& Gx, const Blob& Gy, const Blob& n, const Blob& h, 
		int output_type = UNCOMPRESSED);

	// tri- or pentanomial in hex presentation
	Blob EncodeGF2CurveParam(const Blob& p, const Blob& a, const Blob& b, 
		const Blob& G, const Blob& n, const Blob& h, int output_type = UNCOMPRESSED);

	// f(t) = t^m + t^k + 1
	Blob EncodeTrinomialCurveParam(const int m, const int k, 
		const Blob& a, const Blob& b, const Blob& Gx, const Blob& Gy,
		const Blob& n, const Blob& h, int output_type = UNCOMPRESSED);

	// f(t) = t^m + t^k + 1
	Blob EncodeTrinomialCurveParam(const int m, const int k,
		const Blob& a, const Blob& b, const Blob& G, const Blob& n,
		const Blob& h, int output_type = UNCOMPRESSED);

	// f(t) = t^m + t^k3 + t^k2 + t^k1 + 1
	Blob EncodePentanomialCurveParam(const int m, const int k3, const int k2,
		const int k1, const Blob& a, const Blob& b, const Blob& Gx, const Blob& Gy,
		const Blob& n, const Blob& h, int output_type = UNCOMPRESSED);

	// f(t) = t^m + t^k3 + t^k2 + t^k1 + 1
	Blob EncodePentanomialCurveParam(const int m, const int k3, const int k2,
		const int k1, const Blob& a, const Blob& b, const Blob& G,
		const Blob& n, const Blob& h, int output_type = UNCOMPRESSED);

} // namespace act

#endif // ACT_ToolsECC_h
