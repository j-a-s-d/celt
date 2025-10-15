/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: GeM LAMBDA
 * File: gem_lambda.h
 * Brief: lambda functions for gcc/clang
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "ce.h"

#define GeM_LAMBDA

/* GeM.LAMBDA -- Lambda Functions */

#if defined(__clang__)

#include "gem_bkptrs-inc.h"

typedef oldbk_fn lambda_void_fn;
typedef oldbk_pointer_fn lambda_pointer_fn; 
typedef oldbk_intptr_fn lambda_intptr_fn;
typedef oldbk_uintptr_fn lambda_uintptr_fn;
typedef oldbk_string_fn lambda_string_fn;
typedef oldbk_char_fn lambda_char_fn;
typedef oldbk_unsigned_char_fn lambda_unsigned_char_fn;
typedef oldbk_int_fn lambda_int_fn;
typedef oldbk_unsigned_int_fn lambda_unsigned_int_fn;
typedef oldbk_long_fn lambda_long_fn;
typedef oldbk_unsigned_long_fn lambda_unsigned_long_fn;
typedef oldbk_long_long_fn lambda_long_long_fn;
typedef oldbk_unsigned_long_long_fn lambda_unsigned_long_long_fn;
typedef oldbk_int8_fn lambda_int8_fn;
typedef oldbk_uint8_fn lambda_uint8_fn;
typedef oldbk_int16_fn lambda_int16_fn;
typedef oldbk_uint16_fn lambda_uint16_fn;
typedef oldbk_int32_fn lambda_int32_fn;
typedef oldbk_uint32_fn lambda_uint32_fn;
typedef oldbk_int64_fn lambda_int64_fn;
typedef oldbk_uint64_fn lambda_uint64_fn;
typedef oldbk_float_fn lambda_float_fn;
typedef oldbk_double_fn lambda_double_fn;
typedef oldbk_long_double_fn lambda_long_double_fn;
typedef oldbk_bool_fn lambda_bool_fn;

#else

typedef oldprc_fn lambda_void_fn;
typedef oldfn_pointer_fn lambda_pointer_fn; 
typedef oldfn_intptr_fn lambda_intptr_fn;
typedef oldfn_uintptr_fn lambda_uintptr_fn;
typedef oldfn_string_fn lambda_string_fn;
typedef oldfn_char_fn lambda_char_fn;
typedef oldfn_unsigned_char_fn lambda_unsigned_char_fn;
typedef oldfn_int_fn lambda_int_fn;
typedef oldfn_unsigned_int_fn lambda_unsigned_int_fn;
typedef oldfn_long_fn lambda_long_fn;
typedef oldfn_unsigned_long_fn lambda_unsigned_long_fn;
typedef oldfn_long_long_fn lambda_long_long_fn;
typedef oldfn_unsigned_long_long_fn lambda_unsigned_long_long_fn;
typedef oldfn_int8_fn lambda_int8_fn;
typedef oldfn_uint8_fn lambda_uint8_fn;
typedef oldfn_int16_fn lambda_int16_fn;
typedef oldfn_uint16_fn lambda_uint16_fn;
typedef oldfn_int32_fn lambda_int32_fn;
typedef oldfn_uint32_fn lambda_uint32_fn;
typedef oldfn_int64_fn lambda_int64_fn;
typedef oldfn_uint64_fn lambda_uint64_fn;
typedef oldfn_float_fn lambda_float_fn;
typedef oldfn_double_fn lambda_double_fn;
typedef oldfn_long_double_fn lambda_long_double_fn;
typedef oldfn_bool_fn lambda_bool_fn;

#endif

// NOTE: in this macros, LINE_UNIQUE_NAME is not required to work but included as "best practice"
#if defined(__clang__)
    #define _LAMBDA_NAME_AND_ARGS(args_def) (^LINE_UNIQUE_NAME(lambda_))args_def = ^args_def
#else
    #define _LAMBDA_NAME_AND_ARGS(args_def) LINE_UNIQUE_NAME(lambda_) args_def
    #define __block
#endif

#define lambda(return_type, args_def, body_block) \
    ({ return_type _LAMBDA_NAME_AND_ARGS(args_def) { body_block }; LINE_UNIQUE_NAME(lambda_); })

#define lambda_once(return_type, args_def, body_block) \
    ({ __block bool _already_executed = false; return_type _LAMBDA_NAME_AND_ARGS(args_def) { if (!_already_executed) { _already_executed = true; body_block } }; LINE_UNIQUE_NAME(lambda_); })

#define lambda_void(args, body) lambda(void, args, body)
#define lambda_pointer(args, body) lambda(void*, args, body)
#define lambda_intptr(args, body) lambda(intptr_t, args, body)
#define lambda_uintptr(args, body) lambda(uintptr_t, args, body)
#define lambda_string(args, body) lambda(char*, args, body)
#define lambda_char(args, body) lambda(char, args, body)
#define lambda_unsigned_char(args, body) lambda(unsigned char, args, body)
#define lambda_int(args, body) lambda(int, args, body)
#define lambda_unsigned_int(args, body) lambda(unsigned int, args, body)
#define lambda_long(args, body) lambda(long, args, body)
#define lambda_unsigned_long(args, body) lambda(unsigned long, args, body)
#define lambda_long_long(args, body) lambda(long long, args, body)
#define lambda_unsigned_long_long(args, body) lambda(unsigned long long, args, body)
#define lambda_float(args, body) lambda(float, args, body)
#define lambda_double(args, body) lambda(double, args, body)
#define lambda_long_double(args, body) lambda(long double, args, body)
#define lambda_bool(args, body) lambda(bool, args, body)
#define lambda_int8(args, body) lambda(int8_t, args, body)
#define lambda_uint8(args, body) lambda(uint8_t, args, body)
#define lambda_int16(args, body) lambda(int16_t, args, body)
#define lambda_uint16(args, body) lambda(uint16_t, args, body)
#define lambda_int32(args, body) lambda(int32_t, args, body)
#define lambda_uint32(args, body) lambda(uint32_t, args, body)
#define lambda_int64(args, body) lambda(int64_t, args, body)
#define lambda_uint64(args, body) lambda(uint64_t, args, body)

// lambda-like for statement expression (redundant in most cases)
#define lambda_(return_type, args_def, statement_expression) \
    lambda(return_type, args_def, { return statement_expression; })

#if defined(__GNUC__) && !defined(__clang__)

// NOTE: the lambda$ macros are specific for GCC and allow to use a more universal approach
//       allowing a more lambda writing style "() {}" instead of "(), {}"

#define lambda$(return_type, args_and_body) \
    ({ return_type LINE_UNIQUE_NAME(lambda_) args_and_body LINE_UNIQUE_NAME(lambda_); })

#define lambda$void(args_and_body) lambda$(void, args_and_body)
#define lambda$pointer(args_and_body) lambda$(void*, args_and_body)
#define lambda$intptr(args_and_body) lambda$(intptr_t, args_and_body)
#define lambda$uintptr(args_and_body) lambda$(uintptr_t, args_and_body)
#define lambda$string(args_and_body) lambda$(char*, args_and_body)
#define lambda$char(args_and_body) lambda$(char, args_and_body)
#define lambda$unsigned_char(args_and_body) lambda$(unsigned char, args_and_body)
#define lambda$int(args_and_body) lambda$(int, args_and_body)
#define lambda$unsigned_int(args_and_body) lambda$(unsigned int, args_and_body)
#define lambda$long(args_and_body) lambda$(long, args_and_body)
#define lambda$unsigned_long(args_and_body) lambda$(unsigned long, args_and_body)
#define lambda$long_long(args_and_body) lambda$(long long, args_and_body)
#define lambda$unsigned_long_long(args_and_body) lambda$(unsigned long long, args_and_body)
#define lambda$float(args_and_body) lambda$(float, args_and_body)
#define lambda$double(args_and_body) lambda$(double, args_and_body)
#define lambda$long_double(args_and_body) lambda$(long double, args_and_body)
#define lambda$bool(args_and_body) lambda$(bool, args_and_body)
#define lambda$int8(args_and_body) lambda$(int8_t, args_and_body)
#define lambda$uint8(args_and_body) lambda$(uint8_t, args_and_body)
#define lambda$int16(args_and_body) lambda$(int16_t, args_and_body)
#define lambda$uint16(args_and_body) lambda$(uint16_t, args_and_body)
#define lambda$int32(args_and_body) lambda$(int32_t, args_and_body)
#define lambda$uint32(args_and_body) lambda$(uint32_t, args_and_body)
#define lambda$int64(args_and_body) lambda$(int64_t, args_and_body)
#define lambda$uint64(args_and_body) lambda$(uint64_t, args_and_body)

// lambda-like for statement expression (redundant in most cases)
#define lambda$_(return_type, args_def, statement_expression) \
    lambda$(return_type, args_def { return statement_expression; })

#endif

#ifdef __cplusplus
}
#endif

