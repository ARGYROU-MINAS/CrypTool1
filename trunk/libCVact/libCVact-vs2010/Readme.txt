===============================================================================
Abstract
===============================================================================

   This directory contains the version 1.4.18 of the cv act library/pc.

   Copyright: (c) 2012 cv cryptovision gmbh, all rights reserved.
   Licence:   The conditions for the use of this software are regulated in the
   cv act library licence agreement.


===============================================================================
RELEASE NOTE
===============================================================================

   Version 1.4.18 is a custom build of the cv act library/pc. Do to major
   refactoring (EAC 2.01 functionality, BSI TR-03110), the SecureToken module
   of this version IS NOT FULLY TESTED.


===============================================================================
Content of directories
===============================================================================

   ./lib_VC_2010       > binaries for MS VC++ 2010 applications
   ./include           > interfaces
   ./doc               > cv act library/pc documentation

   Refer to subdir Readme files for details.



===============================================================================
Change history
===============================================================================


Version 1.4.18 compared to version 1.4.17
------------------------------------------

   - No functional changes.


Version 1.4.17 compared to version 1.4.16
-----------------------------------------

   - Added BSI X5.09 certificate signature algorithm OIDs.


Version 1.4.16 compared to version 1.4.15
-----------------------------------------

   - CMSSignedData modified (RFC3852 SignerIdentifier::subjectKeyIdentifier 
     decoding extended).


Version 1.4.15 compared to version 1.4.14
-----------------------------------------

   - FIPS186K4 modified according latest BSI/TÜV-It discussions.


Version 1.4.14 compared to version 1.4.13
-----------------------------------------

   - MS VC++ 2005 (Win32, Mobile 5.0) support.

   - Minor bug fixes.


Version 1.4.13 compared to version 1.4.10
-----------------------------------------

   - Added FIPS186(K4) with configurable hash function, default is SHA-256.

   - New default value for StrongRNG and FastRNG random number generators
     is FIPS186K4 (refer to actInit.h).

   - Added algorithm() function for act::NoSuchAlgorithmException, returning
     the algorithm identifier string.

   - Minor bug fixes.


Version 1.4.10 compared to version 1.4.9
----------------------------------------

   Added PKCS#7 and functionality according to requirments of the
   Bundesdruckerei GmbH.



Version 1.4.9 compared to version 1.4.8
---------------------------------------

   Added PKCS#7 and PKCS#12 functionality according to requirments of the
   Bundesdruckerei GmbH.



Version 1.4.8 compared to version 1.4.7
---------------------------------------

   Added EAC 2.01 functionality:

   1. EACKDF, iMAC3, CMAC algorithms

   2. TokenAuthProtocols for EAC: PACE, TA, CA

   3. CVCertificate handling

   4. ECC arithmetic primitives (only custom version)



Version 1.4.7 compared to version 1.4.6
---------------------------------------

   Minor bug fixes, no changes of the functionality.



Version 1.4.6 compared to version 1.4.5
---------------------------------------

   Minor bug fixes, no changes of the functionality.



Version 1.4.5 compared to version 1.4.4
---------------------------------------

   Added ECDSA SHA-2 algorithm OIDs for certificate verification.



Version 1.4.4 compared to version 1.4.3
---------------------------------------

   1. CRC-16/32 function added (actTools).

   2. Added conversion function for PKCS#3 DH Keys (actTools).



Version 1.4.3 compared to version 1.4.2
---------------------------------------

   Minor bug fixes, no changes of the functionality.



Version 1.4.2 compared to version 1.4.1
---------------------------------------

   1. New password based key derivation functions 'PBKDF1' and 'PBKDF2'
      according to PKCS#5. The PBKDF2 function is now used by default for
      password based key derivation in all symmetric key objects (e.g.
      BlockCipher key objects).

 

Version 1.4.1 compared to version 1.4.0
---------------------------------------

   1. New key derivation function 'X963KDF' according to ANSI X9.63-2001,
      Section 5.6.3. As example, X963KDF may be used in (EC-)DH schemes to
      derive keys of arbitrary length.

   2. (EC-)IES asymmetric encryption and decryption modifed according to ANSI
      X9.63-2001, Section 5.8. The modified (EC-)IES key object may be used to
      encrypt input data of arbitrary length.
      
      PLEASE NOTE: Not backwards compatible to version 1.4.0 and earlier.

   3. New block cipher operation modes according to NIST Special Publication 
      800-38A:
      -  'OFB' (Output Feedback Mode)
      -  'CTR' (Counter Mode)
