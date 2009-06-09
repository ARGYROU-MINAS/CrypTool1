/* gmp-mparam.h -- Compiler/machine parameter header file.

Copyright 1991, 1993, 1994, 1999, 2000, 2001, 2002 Free Software Foundation,
Inc.

This file is part of the GNU MP Library.

The GNU MP Library is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The GNU MP Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
for more details.

You should have received a copy of the GNU Lesser General Public License along
with the GNU MP Library; see the file COPYING.LIB.  If not, write to the Free
Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
USA. */

#define BITS_PER_MP_LIMB 64
#define BYTES_PER_MP_LIMB 8

/* These values were measured on a PA8500 using the system compiler version
   B.11.11.04.  Measurements on PA8000 with system compiler version A.10.32.30
   give very similar values, GCC 3.1 will probably give somewhat different
   results (earlier GCC versions do not support HPPA in 64-bit mode).  */

/* Generated by tuneup.c, 2002-03-26, system compiler */

#define MUL_KARATSUBA_THRESHOLD          23
#define MUL_TOOM3_THRESHOLD             131

#define SQR_BASECASE_THRESHOLD            5
#define SQR_KARATSUBA_THRESHOLD          64
#define SQR_TOOM3_THRESHOLD             149

#define DIV_SB_PREINV_THRESHOLD           0  /* always */
#define DIV_DC_THRESHOLD                124
#define POWM_THRESHOLD                  206

#define GCD_ACCEL_THRESHOLD               3
#define GCDEXT_THRESHOLD                  0  /* always */
#define JACOBI_BASE_METHOD                2

#define DIVREM_1_NORM_THRESHOLD           0  /* always */
#define DIVREM_1_UNNORM_THRESHOLD         0  /* always */
#define MOD_1_NORM_THRESHOLD              0  /* always */
#define MOD_1_UNNORM_THRESHOLD            0  /* always */
#define USE_PREINV_DIVREM_1               1
#define USE_PREINV_MOD_1                  1
#define DIVREM_2_THRESHOLD                0  /* always */
#define DIVEXACT_1_THRESHOLD              0  /* always */
#define MODEXACT_1_ODD_THRESHOLD          0  /* always */

#define GET_STR_DC_THRESHOLD             21
#define GET_STR_PRECOMPUTE_THRESHOLD     23
#define SET_STR_THRESHOLD             14423

#define MUL_FFT_TABLE  { 560, 1184, 2752, 5376, 11264, 36864, 0 }
#define MUL_FFT_MODF_THRESHOLD          360
#define MUL_FFT_THRESHOLD              2816

#define SQR_FFT_TABLE  { 560, 1184, 2752, 5888, 13312, 28672, 0 }
#define SQR_FFT_MODF_THRESHOLD          408
#define SQR_FFT_THRESHOLD              2912