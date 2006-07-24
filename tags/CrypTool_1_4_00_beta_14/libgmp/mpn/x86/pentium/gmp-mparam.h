/* Intel P54 gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1999, 2000, 2001, 2002 Free Software Foundation,
Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MP Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston,
MA 02111-1307, USA. */


#define BITS_PER_MP_LIMB 32
#define BYTES_PER_MP_LIMB 4


/* For mpn/x86/pentium/mod_1.asm */
#define COUNT_LEADING_ZEROS_NEED_CLZ_TAB


/* 166MHz P54, gcc 2.95.2 */

/* Generated by tuneup.c, 2001-11-28, gcc 2.95 */

#define MUL_KARATSUBA_THRESHOLD       16
#define MUL_TOOM3_THRESHOLD          188

#define SQR_BASECASE_THRESHOLD         0
#define SQR_KARATSUBA_THRESHOLD       26
#define SQR_TOOM3_THRESHOLD          171

#define DIV_SB_PREINV_THRESHOLD        MP_SIZE_T_MAX
#define DIV_DC_THRESHOLD                  52
#define POWM_THRESHOLD                71

#define GCD_ACCEL_THRESHOLD            3
#define GCDEXT_THRESHOLD              16

#define USE_PREINV_MOD_1               1  /* (native) */
#define DIVREM_2_THRESHOLD             7
#define DIVEXACT_1_THRESHOLD           0
#define MODEXACT_1_ODD_THRESHOLD       0

#define MUL_FFT_TABLE  { 496, 928, 1920, 5632, 14336, 40960, 0 }
#define MUL_FFT_MODF_THRESHOLD       512
#define MUL_FFT_THRESHOLD           3840

#define SQR_FFT_TABLE  { 624, 928, 1920, 5632, 10240, 40960, 0 }
#define SQR_FFT_MODF_THRESHOLD       568
#define SQR_FFT_THRESHOLD           2496
