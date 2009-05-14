/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

//////////////////////////////////////////////////////////////////
// C++ class for symmentric encryption/decryption with
// DESL, DESX and DESXL.
//
// Coded 2007 by Markus Diett (markus@diett-it.de)
// Communication Security Group 
// at the Ruhr-University Bochum  (http://www.crypto.rub.de)
//////////////////////////////////////////////////////////////////

#pragma once

#define BITNUM(a,b,c) (((a[(b)/8] >> (7 - (b%8))) & 0x01) << (c))

#define     ENCRYPT     0    
#define     DECRYPT     1    
#define     VAR_DESX    0
#define     VAR_DESL    1
#define     VAR_DESXL   2


class DESXL
{
 	char userkey[24]; //Vom Benutzer eingegebener Key
	unsigned char roundkey[16][6]; //DES Rundenschl�ssel
	char desxkey[2][8]; //Key f�r XORs bei DESX (0:StartXOR, 1:EndXOR)

	void cryptBlock(unsigned char *block,char mode,char variant); 
	void IP(unsigned char *block);
	void invIP(unsigned char *block);
	
    void PC1(unsigned char *in,unsigned char *out);
    void PC2(unsigned char *in,unsigned char *out);


   
public:
	DESXL(void);
	~DESXL(void);

	void createKey(char *userinput,int keyLen,char variant);
	void encrypt(unsigned char *input, int inputLen, unsigned char *outBuffer,char variant);
    void decrypt(unsigned char *input, int inputLen, unsigned char *outBuffer,char variant);

};

/*const unsigned int DESLSBox[8][64] = {
{
	14, 5, 5, 0, 7, 8, 2, 15, 11, 14, 8, 3, 1, 2, 15, 12,
	0, 11, 10, 7, 9, 6, 4, 9, 6, 13, 13, 4, 12, 1, 3, 10,
	4, 9, 9, 6, 2, 15, 14, 5, 8, 3, 7, 8, 13, 4, 0, 11,
	10, 7, 12, 1, 15, 12, 1, 2, 5, 0, 11, 14, 3, 10, 6, 13
},
{
	14, 5, 5, 0, 7, 8, 2, 15, 11, 14, 8, 3, 1, 2, 15, 12,
	0, 11, 10, 7, 9, 6, 4, 9, 6, 13, 13, 4, 12, 1, 3, 10,
	4, 9, 9, 6, 2, 15, 14, 5, 8, 3, 7, 8, 13, 4, 0, 11,
	10, 7, 12, 1, 15, 12, 1, 2, 5, 0, 11, 14, 3, 10, 6, 13
},
{
	14, 5, 5, 0, 7, 8, 2, 15, 11, 14, 8, 3, 1, 2, 15, 12,
	0, 11, 10, 7, 9, 6, 4, 9, 6, 13, 13, 4, 12, 1, 3, 10,
	4, 9, 9, 6, 2, 15, 14, 5, 8, 3, 7, 8, 13, 4, 0, 11,
	10, 7, 12, 1, 15, 12, 1, 2, 5, 0, 11, 14, 3, 10, 6, 13
},
{
	14, 5, 5, 0, 7, 8, 2, 15, 11, 14, 8, 3, 1, 2, 15, 12,
	0, 11, 10, 7, 9, 6, 4, 9, 6, 13, 13, 4, 12, 1, 3, 10,
	4, 9, 9, 6, 2, 15, 14, 5, 8, 3, 7, 8, 13, 4, 0, 11,
	10, 7, 12, 1, 15, 12, 1, 2, 5, 0, 11, 14, 3, 10, 6, 13
},
{
	14, 5, 5, 0, 7, 8, 2, 15, 11, 14, 8, 3, 1, 2, 15, 12,
	0, 11, 10, 7, 9, 6, 4, 9, 6, 13, 13, 4, 12, 1, 3, 10,
	4, 9, 9, 6, 2, 15, 14, 5, 8, 3, 7, 8, 13, 4, 0, 11,
	10, 7, 12, 1, 15, 12, 1, 2, 5, 0, 11, 14, 3, 10, 6, 13
},
{
	14, 5, 5, 0, 7, 8, 2, 15, 11, 14, 8, 3, 1, 2, 15, 12,
	0, 11, 10, 7, 9, 6, 4, 9, 6, 13, 13, 4, 12, 1, 3, 10,
	4, 9, 9, 6, 2, 15, 14, 5, 8, 3, 7, 8, 13, 4, 0, 11,
	10, 7, 12, 1, 15, 12, 1, 2, 5, 0, 11, 14, 3, 10, 6, 13
},
{
	14, 5, 5, 0, 7, 8, 2, 15, 11, 14, 8, 3, 1, 2, 15, 12,
	0, 11, 10, 7, 9, 6, 4, 9, 6, 13, 13, 4, 12, 1, 3, 10,
	4, 9, 9, 6, 2, 15, 14, 5, 8, 3, 7, 8, 13, 4, 0, 11,
	10, 7, 12, 1, 15, 12, 1, 2, 5, 0, 11, 14, 3, 10, 6, 13
},
{
	14, 5, 5, 0, 7, 8, 2, 15, 11, 14, 8, 3, 1, 2, 15, 12,
	0, 11, 10, 7, 9, 6, 4, 9, 6, 13, 13, 4, 12, 1, 3, 10,
	4, 9, 9, 6, 2, 15, 14, 5, 8, 3, 7, 8, 13, 4, 0, 11,
	10, 7, 12, 1, 15, 12, 1, 2, 5, 0, 11, 14, 3, 10, 6, 13
}
};*/
const unsigned int DESLSBox[8][64] = {
{
    8552448,   41943040,   41943040,          0,   42074112,      32768,     131072,   42106880,   33718272,    8552448,      32768,   33685504,   33554432,     131072,   42106880,    8421376,
          0,   33718272,     163840,   42074112,   33587200,    8519680,    8388608,   33587200,    8519680,   41975808,   41975808,    8388608,    8421376,   33554432,   33685504,     163840,
    8388608,   33587200,   33587200,    8519680,     131072,   42106880,    8552448,   41943040,      32768,   33685504,   42074112,      32768,   41975808,    8388608,          0,   33718272,
     163840,   42074112,    8421376,   33554432,   42106880,    8421376,   33554432,     131072,   41943040,          0,   33718272,    8552448,   33685504,     163840,    8519680,   41975808
},
{
  268437568,  272629760,  272629760,          0,  272629824,       2048,         64,  272631872,    4196416,  268437568,       2048,    4194368,    4194304,         64,  272631872,  268437504,
          0,    4196416,       2112,  272629824,    4196352,  268435520,  268435456,    4196352,  268435520,  272631808,  272631808,  268435456,  268437504,    4194304,    4194368,       2112,
  268435456,    4196352,    4196352,  268435520,         64,  272631872,  268437568,  272629760,       2048,    4194368,  272629824,       2048,  272631808,  268435456,          0,    4196416,
       2112,  272629824,  268437504,    4194304,  272631872,  268437504,    4194304,         64,  272629760,          0,    4196416,  268437568,    4194368,       2112,  268435520,  272631808
},
{
   67174656,        260,        260,          0,   67109124,      65536,   67108864,   67174660,   67174404,   67174656,      65536,   67108868,          4,   67108864,   67174660,      65792,
          0,   67174404,   67174400,   67109124,      65540,   67109120,        256,      65540,   67109120,      65796,      65796,        256,      65792,          4,   67108868,   67174400,
        256,      65540,      65540,   67109120,   67108864,   67174660,   67174656,        260,      65536,   67108868,   67109124,      65536,      65796,        256,          0,   67174404,
   67174400,   67109124,      65792,          4,   67174660,      65792,          4,   67108864,        260,          0,   67174404,   67174656,   67108868,   67174400,   67109120,      65796
},
{
 1074806784,    1048704,    1048704,          0,    1065088, 1073741824,      16384, 1074806912, 1073758336, 1074806784, 1073741824,      16512,        128,      16384, 1074806912, 1074790400,
          0, 1073758336, 1073758208,    1065088, 1073741952,    1064960,    1048576, 1073741952,    1064960, 1074790528, 1074790528,    1048576, 1074790400,        128,      16512, 1073758208,
    1048576, 1073741952, 1073741952,    1064960,      16384, 1074806912, 1074806784,    1048704, 1073741824,      16512,    1065088, 1073741824, 1074790528,    1048576,          0, 1073758336,
 1073758208,    1065088, 1074790400,        128, 1074806912, 1074790400,        128,      16384,    1048704,          0, 1073758336, 1074806784,      16512, 1073758208,    1064960, 1074790528
},
{
 2147484673,       1056,       1056,          0, 2147484704,          1, 2147483648, 2147484705, 2147483681, 2147484673,          1, 2147483680,         32, 2147483648, 2147484705,       1025,
          0, 2147483681, 2147483649, 2147484704,         33, 2147484672,       1024,         33, 2147484672,       1057,       1057,       1024,       1025,         32, 2147483680, 2147483649,
       1024,         33,         33, 2147484672, 2147483648, 2147484705, 2147484673,       1056,          1, 2147483680, 2147484704,          1,       1057,       1024,          0, 2147483681,
 2147483649, 2147484704,       1025,         32, 2147484705,       1025,         32, 2147483648,       1056,          0, 2147483681, 2147484673, 2147483680, 2147483649, 2147484672,       1057
},
{
  134225936,  136314880,  136314880,          0,  136323072,         16,       8192,  136323088,    2105360,  134225936,         16,    2105344,    2097152,       8192,  136323088,  134217744,
          0,    2105360,       8208,  136323072,    2097168,  134225920,  134217728,    2097168,  134225920,  136314896,  136314896,  134217728,  134217744,    2097152,    2105344,       8208,
  134217728,    2097168,    2097168,  134225920,       8192,  136323088,  134225936,  136314880,         16,    2105344,  136323072,         16,  136314896,  134217728,          0,    2105360,
       8208,  136323072,  134217744,    2097152,  136323088,  134217744,    2097152,       8192,  136314880,          0,    2105360,  134225936,    2105344,       8208,  134225920,  136314896
},
{
   17043456,       4098,       4098,          0,     266242,   16777216,     262144,   17043458,   17039362,   17043456,   16777216,     262146,          2,     262144,   17043458,   16781312,
          0,   17039362,   17039360,     266242,   16777218,     266240,       4096,   16777218,     266240,   16781314,   16781314,       4096,   16781312,          2,     262146,   17039360,
       4096,   16777218,   16777218,     266240,     262144,   17043458,   17043456,       4098,   16777216,     262146,     266242,   16777216,   16781314,       4096,          0,   17039362,
   17039360,     266242,   16781312,          2,   17043458,   16781312,          2,     262144,       4098,          0,   17039362,   17043456,     262146,   17039360,     266240,   16781314
},
{
  536871432,  537395200,  537395200,          0,  537395712,          8,        512,  537395720,     524808,  536871432,          8,     524800,     524288,        512,  537395720,  536870920,
          0,     524808,        520,  537395712,     524296,  536871424,  536870912,     524296,  536871424,  537395208,  537395208,  536870912,  536870920,     524288,     524800,        520,
  536870912,     524296,     524296,  536871424,        512,  537395720,  536871432,  537395200,          8,     524800,  537395712,          8,  537395208,  536870912,          0,     524808,
        520,  537395712,  536870920,     524288,  537395720,  536870920,     524288,        512,  537395200,          0,     524808,  536871432,     524800,        520,  536871424,  537395208
}
};

const unsigned int SBox[8][64] = {
{
    8552448,          0,    8388608,   42106880,   41975808,   42074112,   33554432,    8388608,     131072,    8552448,   42106880,     131072,   33718272,   41975808,      32768,   33554432,
   33685504,     163840,     163840,    8519680,    8519680,    8421376,    8421376,   33718272,   41943040,   33587200,   33587200,   41943040,          0,   33685504,   42074112,      32768,
    8388608,   42106880,   33554432,    8421376,    8552448,      32768,      32768,     131072,   41975808,    8388608,    8519680,   33587200,     131072,   33554432,   33718272,   42074112,
   42106880,   41943040,    8421376,   33718272,   33587200,   33685504,   42074112,    8552448,   33685504,     163840,     163840,          0,   41943040,    8519680,          0,   41975808
},
{
  272631872,    4194368,    4194304,  272631808,       2048,  268435456,  268437568,  272629824,  268435520,  272631872,    4196416,         64,    4194368,       2048,  268435456,  268437568,
    4196352,  268437504,  272629824,          0,         64,    4194304,  272631808,       2112,  268437504,  268435520,          0,    4196352,  272629760,    4196416,       2112,  272629760,
          0,  272631808,  268437568,       2048,  272629824,       2112,    4196416,    4194304,       2112,    4194368,  268435456,  272631872,  272631808,  268435456,    4194304,         64,
  272629760,    4196416,       2048,  268435520,  268437504,  272629824,  268435520,  268437504,    4196352,          0,    4194368,  272629760,         64,  268437568,  272631872,    4196352
},
{
   67174400,      65796,          0,   67109124,      65540,          0,   67174656,      65540,   67109120,   67108868,   67108868,        256,   67174660,   67109120,        260,   67174400,
          4,   67108864,      65796,      65536,      65792,        260,   67109124,   67174656,   67174404,      65792,        256,   67174404,   67108864,   67174660,      65536,          4,
      65796,          4,   67109120,   67174400,        256,      65796,      65540,          0,      65536,   67109120,   67174660,      65540,   67108868,      65536,          0,   67109124,
   67174404,        256,          4,   67174660,   67108864,   67174656,      65792,   67108868,        260,   67174404,   67174400,        260,   67174656,   67108864,   67109124,      65792
},
{
    1065088, 1074790528, 1074790528, 1073741824, 1074806784, 1073758336,      16512,    1048704,          0,    1064960,    1064960, 1074806912, 1073741952,          0, 1073758208,      16512,
        128,    1048576,      16384,    1065088, 1073741824,      16384,    1048704, 1074790400, 1073758336,        128, 1074790400, 1073758208,    1048576, 1074806784, 1074806912, 1073741952,
 1073758208,      16512,    1064960, 1074806912, 1073741952,          0,          0,    1064960, 1074790400, 1073758208, 1073758336,        128,    1065088, 1074790528, 1074790528, 1073741824,
 1074806912, 1073741952,        128,    1048576,      16512,    1048704, 1074806784, 1073758336,    1048704, 1074790400,      16384,    1065088, 1073741824,      16384,    1048576, 1074806784
},
{
 2147483648, 2147484673,       1025, 2147483681,       1024, 2147483648,         32,       1025, 2147484704,       1024, 2147483649, 2147484704, 2147483681,       1057, 2147484672,         32,
          1,       1056,       1056,          0, 2147483680, 2147484705, 2147484705, 2147483649,       1057, 2147483680,          0,         33, 2147484673,          1,         33, 2147484672,
       1024, 2147483681, 2147483648,          1,         32,       1025, 2147483681, 2147484704, 2147483649,         32,       1057, 2147484673, 2147484704, 2147483648,          1,       1057,
 2147484705, 2147484672,         33, 2147484705,       1025,          0,       1056,         33, 2147484672, 2147483649, 2147483680,       1024,          0,       1056, 2147484673, 2147483680
},
{
  134217744,       8208,    2097152,  136323088,       8208,  134217728,  136323088,       8192,    2097168,  136323072,       8192,  134217744,  134225920,    2097168,         16,  136314880,
          0,  134225920,  136314896,    2097152,    2105344,  136314896,  134217728,  134225936,  134225936,          0,  136323072,    2105360,  136314880,    2105344,    2105360,         16,
    2097168,  134217728,  134225936,    2105344,  136323088,       8192,  136314880,  134217744,       8192,    2097168,         16,  136314880,  134217744,  136323088,    2105344,       8208,
  136323072,    2105360,          0,  134225936,  134217728,    2097152,       8208,  136323072,    2097152,  134225920,  136314896,          0,    2105360,         16,  134225920,  136314896
},
{
       4096,   16781314,   17039362,          0,     262144,   17039362,   17043456,     266242,   17043458,       4096,          0,   16777218,   16777216,          2,   16781314,   17039360,
     262146,   17043456,   16781312,     262146,   16777218,       4098,     266242,   16781312,       4098,     262144,   17039360,   17043458,     266240,   16777216,          2,     266240,
          2,     266240,       4096,   17039362,   17039362,   16781314,   16781314,   16777216,   16781312,          2,     262146,       4096,     266242,   17039360,   17043456,     266242,
   17039360,   16777218,   17043458,       4098,     266240,          0,   16777216,   17043458,          0,   17043456,       4098,     262144,   16777218,     262146,     262144,   16781312
},
{
  537395208,     524288,        512,  537395720,          8,  537395208,  536870912,          8,  536871424,        520,  537395720,     524800,     524808,  537395712,     524288,  536870912,
        520,  536870920,     524296,  537395200,     524800,  536871424,  536871432,     524808,  537395200,          0,          0,  536871432,  536870920,     524296,  537395712,        512,
  537395712,        512,     524808,     524288,  536870912,  536871432,     524288,  537395712,     524296,  536870912,  536870920,        520,  536871432,          8,        512,  537395208,
          0,  537395720,  536871424,  536870920,        520,     524296,  537395208,          0,  537395720,     524800,     524800,  537395200,  537395200,  536871424,          8,     524808
}
};

/* const unsigned int SBox[8][64] =
  {
    {  /* S0 
    14,  0,  4, 15, 13,  7,  1,  4,  2, 14, 15,  2, 11, 13,  8,  1,
     3, 10, 10,  6,  6, 12, 12, 11,  5,  9,  9,  5,  0,  3,  7,  8,
     4, 15,  1, 12, 14,  8,  8,  2, 13,  4,  6,  9,  2,  1, 11,  7,
    15,  5, 12, 11,  9,  3,  7, 14,  3, 10, 10,  0,  5,  6,  0, 13
    },
    {  /* S1 
    15,  3,  1, 13,  8,  4, 14,  7,  6, 15, 11,  2,  3,  8,  4, 14,
     9, 12,  7,  0,  2,  1, 13, 10, 12,  6,  0,  9,  5, 11, 10,  5,
     0, 13, 14,  8,  7, 10, 11,  1, 10,  3,  4, 15, 13,  4,  1,  2,
     5, 11,  8,  6, 12,  7,  6, 12,  9,  0,  3,  5,  2, 14, 15,  9
    },
    {  /* S2 
    10, 13,  0,  7,  9,  0, 14,  9,  6,  3,  3,  4, 15,  6,  5, 10,
     1,  2, 13,  8, 12,  5,  7, 14, 11, 12,  4, 11,  2, 15,  8,  1,
    13,  1,  6, 10,  4, 13,  9,  0,  8,  6, 15,  9,  3,  8,  0,  7,
    11,  4,  1, 15,  2, 14, 12,  3,  5, 11, 10,  5, 14,  2,  7, 12
    },
    {  /* S3 
     7, 13, 13,  8, 14, 11,  3,  5,  0,  6,  6, 15,  9,  0, 10,  3,
     1,  4,  2,  7,  8,  2,  5, 12, 11,  1, 12, 10,  4, 14, 15,  9,
    10,  3,  6, 15,  9,  0,  0,  6, 12, 10, 11,  1,  7, 13, 13,  8,
    15,  9,  1,  4,  3,  5, 14, 11,  5, 12,  2,  7,  8,  2,  4, 14
    },
    {  /* S4 
     2, 14, 12, 11,  4,  2,  1, 12,  7,  4, 10,  7, 11, 13,  6,  1,
     8,  5,  5,  0,  3, 15, 15, 10, 13,  3,  0,  9, 14,  8,  9,  6,
     4, 11,  2,  8,  1, 12, 11,  7, 10,  1, 13, 14,  7,  2,  8, 13,
    15,  6,  9, 15, 12,  0,  5,  9,  6, 10,  3,  4,  0,  5, 14,  3
    },
    {  /* S5 
    12, 10,  1, 15, 10,  4, 15,  2,  9,  7,  2, 12,  6,  9,  8,  5,
     0,  6, 13,  1,  3, 13,  4, 14, 14,  0,  7, 11,  5,  3, 11,  8,
     9,  4, 14,  3, 15,  2,  5, 12,  2,  9,  8,  5, 12, 15,  3, 10,
     7, 11,  0, 14,  4,  1, 10,  7,  1,  6, 13,  0, 11,  8,  6, 13
    },
    {  /* S6 
     4, 13, 11,  0,  2, 11, 14,  7, 15,  4,  0,  9,  8,  1, 13, 10,
     3, 14, 12,  3,  9,  5,  7, 12,  5,  2, 10, 15,  6,  8,  1,  6,
     1,  6,  4, 11, 11, 13, 13,  8, 12,  1,  3,  4,  7, 10, 14,  7,
    10,  9, 15,  5,  6,  0,  8, 15,  0, 14,  5,  2,  9,  3,  2, 12
    },
    {  /* S7 
    13,  1,  2, 15,  8, 13,  4,  8,  6, 10, 15,  3, 11,  7,  1,  4,
    10, 12,  9,  5,  3,  6, 14, 11,  5,  0,  0, 14, 12,  9,  7,  2,
     7,  2, 11,  1,  4, 14,  1,  7,  9,  4, 12, 10, 14,  8,  2, 13,
     0, 15,  6, 12, 10,  9, 13,  0, 15,  3,  3,  5,  5,  6,  8, 11
    }
  };
*/