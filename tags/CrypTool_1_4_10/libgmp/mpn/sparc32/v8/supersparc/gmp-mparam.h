/* SuperSPARC gmp-mparam.h -- Compiler/machine parameter header file.

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

/* These numbers were obtained on kotov.sics.se, a 40 MHz SuperSPARC system */

/* Generated by tuneup.c, 2001-11-26, gcc 2.95 */

#define MUL_KARATSUBA_THRESHOLD       14
#define MUL_TOOM3_THRESHOLD          105

#define SQR_BASECASE_THRESHOLD         5
#define SQR_KARATSUBA_THRESHOLD       28
#define SQR_TOOM3_THRESHOLD          113

#define DIV_SB_PREINV_THRESHOLD            0
#define DIV_DC_THRESHOLD                  44
#define POWM_THRESHOLD               104

#define GCD_ACCEL_THRESHOLD            3
#define GCDEXT_THRESHOLD              13

#define DIVREM_1_NORM_THRESHOLD        0
#define DIVREM_1_UNNORM_THRESHOLD  MP_SIZE_T_MAX
#define MOD_1_NORM_THRESHOLD           0
#define MOD_1_UNNORM_THRESHOLD     MP_SIZE_T_MAX
#define USE_PREINV_MOD_1               1
#define DIVREM_2_THRESHOLD             0
#define DIVEXACT_1_THRESHOLD           0
#define MODEXACT_1_ODD_THRESHOLD       0

#define MUL_FFT_TABLE  { 432, 1056, 1664, 4608, 14336, 40960, 0 }
#define MUL_FFT_MODF_THRESHOLD       448
#define MUL_FFT_THRESHOLD           3840

#define SQR_FFT_TABLE  { 432, 992, 1664, 4608, 14336, 40960, 0 }
#define SQR_FFT_MODF_THRESHOLD       448
#define SQR_FFT_THRESHOLD           3840
