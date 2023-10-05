/*
 * Copyright (c) 2021 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef C2000WARE_LIBRARIES_H
#define C2000WARE_LIBRARIES_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

#include "board.h"
#include <stdlib.h>

//
// IMPORTANT NOTE: The standard is to use data types in the format as int32_t, but the structs
//                 as part of the stdlib.h file do not use these types, so their corresponding
//                 data types are used here.
//
// Return type is ldiv_t:
//
// typedef struct {
//        int32_t quot;
//        int32_t rem;
// } ldiv_t;
// 
// Example:
//      int32_t numerator = 2000000000;
//      int32_t denominator = -500;
//      ldiv_t result = FID_COMP_I16_BY_I16_T(numerator, denominator);
//      int32_t quotient = result.quot;
//      int32_t remainder = result.rem;
// 
#define FID_COMP_I16_BY_I16_T __traditional_div_i16byi16
#define FID_COMP_I32_BY_I32_T __traditional_div_i32byi32
#define FID_COMP_I32_BY_U32_T __traditional_div_i32byu32
#define FID_COMP_I32_BY_I16_T __traditional_div_i32byi16

#define FID_COMP_I16_BY_I16_M __modulo_div_i16byi16
#define FID_COMP_I32_BY_I32_M __modulo_div_i32byi32
#define FID_COMP_I32_BY_U32_M __modulo_div_i32byu32
#define FID_COMP_I32_BY_I16_M __modulo_div_i32byi16

#define FID_COMP_I16_BY_I16_E __euclidean_div_i16byi16
#define FID_COMP_I32_BY_I32_E __euclidean_div_i32byi32
#define FID_COMP_I32_BY_I16_E __euclidean_div_i32byi16



//
// Return type is __uldiv_t:
//
// typedef struct {
//     uint32_t quot;
//     uint32_t rem;
// }  __uldiv_t;
// 
// Example:
//      uint32_t numerator = 3000000000;
//      uint32_t denominator = 50000000;
//      __uldiv_t result = FID_COMP_U32_BY_U32_T(numerator, denominator);
//      uint32_t quotient = result.quot;
//      uint32_t remainder = result.rem;
// 
#define FID_COMP_U16_BY_U16_T __traditional_div_u16byu16
#define FID_COMP_U32_BY_U32_T __traditional_div_u32byu32
#define FID_COMP_U32_BY_U16_T __traditional_div_u32byu16



// 
// Return type is lldiv_t:
//
// typedef struct {
//     int64_t quot;
//     int64_t rem;
// } lldiv_t;
// 
// Example:
//      int64_t numerator = -2000000000000000000;
//      int64_t denominator = 500000000;
//      lldiv_t result = FID_COMP_I64_BY_I64_T(numerator, denominator);
//      int64_t quotient = result.quot;
//      int64_t remainder = result.rem;
//
#define FID_COMP_I64_BY_I64_T __traditional_div_i64byi64
#define FID_COMP_I64_BY_U64_T __traditional_div_i64byu64
#define FID_COMP_I64_BY_U32_T __traditional_div_i64byu32

#define FID_COMP_I64_BY_I64_M __modulo_div_i64byi64
#define FID_COMP_I64_BY_U64_M __modulo_div_i64byu64

#define FID_COMP_I64_BY_I64_E __euclidean_div_i64byi64
#define FID_COMP_I64_BY_U64_E __euclidean_div_i64byu64



// 
// Return type is __ulldiv_t:
//
// typedef struct {
//     uint64_t quot;
//     uint64_t rem;
// } __ulldiv_t;
// 
// Example:
//      uint64_t numerator = 18000000000000000000;
//      uint64_t denominator = 5000000000000;
//      __ulldiv_t result = FID_COMP_U64_BY_U64_T(numerator, denominator);
//      uint64_t quotient = result.quot;
//      uint64_t remainder = result.rem;
//
#define FID_COMP_U64_BY_U64_T __traditional_div_u64byu64



// 
// Return type is __llldiv_t:
//
// typedef struct {
//     int64_t quot;
//     int32_t rem;
// } __llldiv_t;
//
// Example:
//      int64_t numerator = -2000000000000000000;
//      int32_t denominator = -2000000000;
//      __llldiv_t result = FID_COMP_I64_BY_I32_T(numerator, denominator);
//      int64_t quotient = result.quot;
//      int32_t remainder = result.rem;
//
#define FID_COMP_I64_BY_I32_T __traditional_div_i64byi32

#define FID_COMP_I64_BY_I32_M __modulo_div_i64byi32
#define FID_COMP_I64_BY_U32_M __modulo_div_i64byu32

#define FID_COMP_I64_BY_I32_E __euclidean_div_i64byi32
#define FID_COMP_I64_BY_U32_E __euclidean_div_i64byu32



// 
// Return type is __ullldiv_t:
//
// typedef struct {
//     uint64_t quot;
//     uint32_t rem;
// } __ullldiv_t;
// 
// Example:
//      uint64_t numerator = 18000000000000000000;
//      uint32_t denominator = 3000000000;
//      __ullldiv_t result = FID_COMP_U64_BY_U32_T(numerator, denominator);
//      uint64_t quotient = result.quot;
//      uint32_t remainder = result.rem;
//
#define FID_COMP_U64_BY_U32_T __traditional_div_u64byu32


#include <C28x_FPU_FastRTS.h>
#include <fastrts.h>
#include "math.h"
#include <fpu32/C28x_FPU_FastRTS.h>

//
//  Functions available for FPU32 configuration:
//
//  float32_t acosf(float32_t X)
//  float32_t asinf(float32_t X)
//  float32_t atanf(float32_t X)
//  float32_t atan2f(float32_t Y, float32_t X)
//  float32_t cosf(float32_t X)
//  float32_t FS$$DIV(float32_t X, float32_t Y); call using '/' operator
//  float32_t expf(float32_t X)
//  float32_t isqrtf(float32_t X)
//  float32_t logf(float32_t X)
//  float32_t powf(float32_t X, float32_t Y)
//  float32_t sinf(float32_t X)
//  float32_t sqrtf(float32_t X)
//
void FFR_init();


void C2000Ware_libraries_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
