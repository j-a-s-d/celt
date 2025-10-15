/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: GeM
 * File: gem_bkptrs-inc.h
 * Brief: part of GeM LAMBDA & METHODS, block pointers for clang
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// NOTE: This is included by GeM Methods which requires the BlocksRuntime library to compile under clang

#if defined(__clang__)

/* GeM.POINTERS -- Old/K&R Style Block Pointers for clang */

typedef void (^oldbk_fn)();
typedef void* (^oldbk_pointer_fn)();
typedef char* (^oldbk_string_fn)();
typedef char (^oldbk_char_fn)();
typedef signed char (^oldbk_signed_char_fn)();
typedef unsigned char (^oldbk_unsigned_char_fn)();
typedef int (^oldbk_int_fn)();
typedef unsigned int (^oldbk_unsigned_int_fn)();
typedef long (^oldbk_long_fn)();
typedef unsigned long (^oldbk_unsigned_long_fn)();
typedef float (^oldbk_float_fn)();
typedef double (^oldbk_double_fn)();
typedef long double (^oldbk_long_double_fn)();
#ifdef __c99
typedef long long (^oldbk_long_long_fn)();
typedef unsigned long long (^oldbk_unsigned_long_long_fn)();
typedef intptr_t (^oldbk_intptr_fn)();
typedef uintptr_t (^oldbk_uintptr_fn)();
typedef int8_t (^oldbk_int8_fn)();
typedef uint8_t (^oldbk_uint8_fn)();
typedef int16_t (^oldbk_int16_fn)();
typedef uint16_t (^oldbk_uint16_fn)();
typedef int32_t (^oldbk_int32_fn)();
typedef uint32_t (^oldbk_uint32_fn)();
typedef int64_t (^oldbk_int64_fn)();
typedef uint64_t (^oldbk_uint64_fn)();
typedef bool (^oldbk_bool_fn)();
#endif

#endif

#ifdef __cplusplus
}
#endif

