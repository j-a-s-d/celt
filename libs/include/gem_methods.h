/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: GeM METHODS
 * File: gem_methods.h
 * Brief: struct methods for gcc/clang
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "ce.h"

#define GeM_METHODS

// NOTE: GeM Methods requires the BlocksRuntime library to compile under clang

/* GeM.METHODS -- Struct Methods */

#if defined(__clang__)

#include "gem_bkptrs-inc.h"

typedef oldbk_fn method_void_fn;
typedef oldbk_pointer_fn method_pointer_fn; 
typedef oldbk_intptr_fn method_intptr_fn;
typedef oldbk_uintptr_fn method_uintptr_fn;
typedef oldbk_string_fn method_string_fn;
typedef oldbk_char_fn method_char_fn;
typedef oldbk_unsigned_char_fn method_unsigned_char_fn;
typedef oldbk_int_fn method_int_fn;
typedef oldbk_unsigned_int_fn method_unsigned_int_fn;
typedef oldbk_long_fn method_long_fn;
typedef oldbk_unsigned_long_fn method_unsigned_long_fn;
typedef oldbk_long_long_fn method_long_long_fn;
typedef oldbk_unsigned_long_long_fn method_unsigned_long_long_fn;
typedef oldbk_int8_fn method_int8_fn;
typedef oldbk_uint8_fn method_uint8_fn;
typedef oldbk_int16_fn method_int16_fn;
typedef oldbk_uint16_fn method_uint16_fn;
typedef oldbk_int32_fn method_int32_fn;
typedef oldbk_uint32_fn method_uint32_fn;
typedef oldbk_int64_fn method_int64_fn;
typedef oldbk_uint64_fn method_uint64_fn;
typedef oldbk_float_fn method_float_fn;
typedef oldbk_double_fn method_double_fn;
typedef oldbk_long_double_fn method_long_double_fn;
typedef oldbk_bool_fn method_bool_fn;

#else

typedef oldprc_fn method_void_fn;
typedef oldfn_pointer_fn method_pointer_fn; 
typedef oldfn_intptr_fn method_intptr_fn;
typedef oldfn_uintptr_fn method_uintptr_fn;
typedef oldfn_string_fn method_string_fn;
typedef oldfn_char_fn method_char_fn;
typedef oldfn_unsigned_char_fn method_unsigned_char_fn;
typedef oldfn_int_fn method_int_fn;
typedef oldfn_unsigned_int_fn method_unsigned_int_fn;
typedef oldfn_long_fn method_long_fn;
typedef oldfn_unsigned_long_fn method_unsigned_long_fn;
typedef oldfn_long_long_fn method_long_long_fn;
typedef oldfn_unsigned_long_long_fn method_unsigned_long_long_fn;
typedef oldfn_int8_fn method_int8_fn;
typedef oldfn_uint8_fn method_uint8_fn;
typedef oldfn_int16_fn method_int16_fn;
typedef oldfn_uint16_fn method_uint16_fn;
typedef oldfn_int32_fn method_int32_fn;
typedef oldfn_uint32_fn method_uint32_fn;
typedef oldfn_int64_fn method_int64_fn;
typedef oldfn_uint64_fn method_uint64_fn;
typedef oldfn_float_fn method_float_fn;
typedef oldfn_double_fn method_double_fn;
typedef oldfn_long_double_fn method_long_double_fn;
typedef oldfn_bool_fn method_bool_fn;

#endif

// NOTE: in this macros, LINE_UNIQUE_NAME is not required to work but included as "best practice"
#if defined(__clang__)
    #define _METHOD_NAME_AND_ARGS(args_def) (^LINE_UNIQUE_NAME(method_))args_def = ^args_def
#else
    #define _METHOD_NAME_AND_ARGS(args_def) LINE_UNIQUE_NAME(method_) args_def
#endif

#define method_of(struct_instance, return_type, args_def, body_block) \
    ({ return_type _METHOD_NAME_AND_ARGS(args_def) { \
        __typeof__(struct_instance) this __unused; \
        UNUSED(this = struct_instance); \
        body_block \
    }; LINE_UNIQUE_NAME(method_); })

#define method(struct_instance, field_name, return_type, args_def, body_block) \
    struct_instance->field_name = method_of(struct_instance, return_type, args_def, body_block)

#ifdef __cplusplus
}
#endif

