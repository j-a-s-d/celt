/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: Ce
 * File: ce_pointers-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef CE
#warning This is intended to be part of the C Extra Library.
#endif

/* Ce.POINTERS -- General-Purpose Utilities */

/* checks if the pointer is assigned */
#define assigned(ptr) ((ptr) != NULL)

/* checks if the both pointers are assigned */
#define both_assigned(a, b) (assigned(a) && assigned(b))

/* Ce.POINTERS -- Function Aliases/Pointers */

/* creates a function alias */
/* NOTE: for newbies, use FUNC_ALIAS_DECL in the .h file and FUNC_ALIAS_IMPL in the .c file */
#if defined(__GNUC__) || defined(__clang__) /* __GNUC__ is also defined by clang but included for clarity */
    #define FUNC_ALIAS_DECL(return_type, func_name, func_args) return_type func_name func_args
    #define FUNC_ALIAS_IMPL(return_type, func_name, func_args, orig_func) return_type func_name func_args __attribute__((alias(STR(orig_func))))
#else
    #define FUNC_ALIAS_DECL(return_type, func_name, func_args) extern return_type (*func_name)func_args
    #define FUNC_ALIAS_IMPL(return_type, func_name, func_args, orig_func) return_type (*func_name)func_args = orig_func
#endif

/* Ce.POINTERS -- Main Function Pointers */

typedef int (*old_main_fn)();
typedef int (*void_main_fn)(void);
typedef int (*args_main_fn)(int argc, char** argv); /* char* argv[] analog */
typedef int (*env_main_fn)(int argc, char** argv, char** envp);

typedef void (*msold_main_fn)();
typedef void (*msvoid_main_fn)(void);
typedef void (*msargs_main_fn)(int argc, char** argv); /* char* argv[] analog */
typedef void (*msenv_main_fn)(int argc, char** argv, char** envp);

#ifdef __c99
#include <stdint.h>
#endif

/* Ce.POINTERS -- Old/K&R Style (C23 Parameter-less) Function Pointers */

typedef void (*oldprc_fn)();
typedef void* (*oldfn_pointer_fn)();
typedef char* (*oldfn_string_fn)();
typedef char (*oldfn_char_fn)();
typedef signed char (*oldfn_signed_char_fn)();
typedef unsigned char (*oldfn_unsigned_char_fn)();
typedef short (*oldfn_short_fn)();
typedef unsigned short (*oldfn_unsigned_short_fn)();
typedef int (*oldfn_int_fn)();
typedef unsigned int (*oldfn_unsigned_int_fn)();
typedef long (*oldfn_long_fn)();
typedef unsigned long (*oldfn_unsigned_long_fn)();
typedef float (*oldfn_float_fn)();
typedef double (*oldfn_double_fn)();
typedef long double (*oldfn_long_double_fn)();
#ifdef __c99
typedef long long (*oldfn_long_long_fn)();
typedef unsigned long long (*oldfn_unsigned_long_long_fn)();
typedef intptr_t (*oldfn_intptr_fn)();
typedef uintptr_t (*oldfn_uintptr_fn)();
typedef int8_t (*oldfn_int8_fn)();
typedef uint8_t (*oldfn_uint8_fn)();
typedef int16_t (*oldfn_int16_fn)();
typedef uint16_t (*oldfn_uint16_fn)();
typedef int32_t (*oldfn_int32_fn)();
typedef uint32_t (*oldfn_uint32_fn)();
typedef int64_t (*oldfn_int64_fn)();
typedef uint64_t (*oldfn_uint64_fn)();
typedef bool (*oldfn_bool_fn)();
#endif

/* Ce.POINTERS -- Parameter-less Function Pointers */

typedef void (*prc_fn)(void); /* same used by atexit() -c89- and at_quick_exit() -c11- */
typedef void* (*fn_pointer_fn)(void);
typedef char* (*fn_string_fn)(void);
typedef char (*fn_char_fn)(void);
typedef signed char (*fn_signed_char_fn)(void);
typedef unsigned char (*fn_unsigned_char_fn)(void);
typedef short (*fn_short_fn)(void);
typedef unsigned short (*fn_unsigned_short_fn)(void);
typedef int (*fn_int_fn)(void);
typedef unsigned int (*fn_unsigned_int_fn)(void);
typedef long (*fn_long_fn)(void);
typedef unsigned long (*fn_unsigned_long_fn)(void);
typedef float (*fn_float_fn)(void);
typedef double (*fn_double_fn)(void);
typedef long double (*fn_long_double_fn)(void);
#ifdef __c99
typedef long long (*fn_long_long_fn)(void);
typedef unsigned long long (*fn_unsigned_long_long_fn)(void);
typedef intptr_t (*fn_intptr_fn)(void);
typedef uintptr_t (*fn_uintptr_fn)(void);
typedef int8_t (*fn_int8_fn)(void);
typedef uint8_t (*fn_uint8_fn)(void);
typedef int16_t (*fn_int16_fn)(void);
typedef uint16_t (*fn_uint16_fn)(void);
typedef int32_t (*fn_int32_fn)(void);
typedef uint32_t (*fn_uint32_fn)(void);
typedef int64_t (*fn_int64_fn)(void);
typedef uint64_t (*fn_uint64_fn)(void);
typedef bool (*fn_bool_fn)(void);
#endif

/* Ce.POINTERS -- Single-parameter Result-less Function Pointers */

typedef void (*prc_pointer_fn)(void*);
typedef void (*prc_string_fn)(char*);
typedef void (*prc_char_fn)(char);
typedef void (*prc_signed_char_fn)(signed char);
typedef void (*prc_unsigned_char_fn)(unsigned char);
typedef void (*prc_short_fn)(short);
typedef void (*prc_unsigned_short_fn)(unsigned short);
typedef void (*prc_int_fn)(int);
typedef void (*prc_unsigned_int_fn)(unsigned int);
typedef void (*prc_long_fn)(long);
typedef void (*prc_unsigned_long_fn)(unsigned long);
typedef void (*prc_float_fn)(float);
typedef void (*prc_double_fn)(double);
typedef void (*prc_long_double_fn)(long double);
#ifdef __c99
typedef void (*prc_long_long_fn)(long long);
typedef void (*prc_unsigned_long_long_fn)(unsigned long long);
typedef void (*prc_intptr_fn)(intptr_t);
typedef void (*prc_uintptr_fn)(uintptr_t);
typedef void (*prc_int8_fn)(int8_t);
typedef void (*prc_uint8_fn)(uint8_t);
typedef void (*prc_int16_fn)(int16_t);
typedef void (*prc_uint16_fn)(uint16_t);
typedef void (*prc_int32_fn)(int32_t);
typedef void (*prc_uint32_fn)(uint32_t);
typedef void (*prc_int64_fn)(int64_t);
typedef void (*prc_uint64_fn)(uint64_t);
typedef void (*prc_bool_fn)(bool);
#endif

/* Ce.POINTERS -- Single-parameter Same-result Treater-like Function Pointers */

typedef void* (*trt_pointer_fn)(void*);
typedef char* (*trt_string_fn)(char*);
typedef char (*trt_char_fn)(char);
typedef signed char (*trt_signed_char_fn)(signed char);
typedef unsigned char (*trt_unsigned_char_fn)(unsigned char);
typedef short (*trt_short_fn)(short);
typedef unsigned short (*trt_unsigned_short_fn)(unsigned short);
typedef int (*trt_int_fn)(int);
typedef unsigned int (*trt_unsigned_int_fn)(unsigned int);
typedef long (*trt_long_fn)(long);
typedef unsigned long (*trt_unsigned_long_fn)(unsigned long);
typedef float (*trt_float_fn)(float);
typedef double (*trt_double_fn)(double);
typedef long double (*trt_long_double_fn)(long double);
#ifdef __c99
typedef long long (*trt_long_long_fn)(long long);
typedef unsigned long long (*trt_unsigned_long_long_fn)(unsigned long long);
typedef intptr_t (*trt_intptr_fn)(intptr_t);
typedef uintptr_t (*trt_uintptr_fn)(uintptr_t);
typedef int8_t (*trt_int8_fn)(int8_t);
typedef uint8_t (*trt_uint8_fn)(uint8_t);
typedef int16_t (*trt_int16_fn)(int16_t);
typedef uint16_t (*trt_uint16_fn)(uint16_t);
typedef int32_t (*trt_int32_fn)(int32_t);
typedef uint32_t (*trt_uint32_fn)(uint32_t);
typedef int64_t (*trt_int64_fn)(int64_t);
typedef uint64_t (*trt_uint64_fn)(uint64_t);
typedef bool (*trt_bool_fn)(bool);
#endif

/* Ce.POINTERS -- Pointer-parameter Getter-like Function Pointers */

typedef void* (*getter_pointer_fn)(void*);
typedef char* (*getter_string_fn)(void*);
typedef char (*getter_char_fn)(void*);
typedef signed char (*getter_signed_char_fn)(void*);
typedef unsigned char (*getter_unsigned_char_fn)(void*);
typedef short (*getter_short_fn)(void*);
typedef unsigned short (*getter_unsigned_short_fn)(void*);
typedef int (*getter_int_fn)(void*);
typedef unsigned int (*getter_unsigned_int_fn)(void*);
typedef long (*getter_long_fn)(void*);
typedef unsigned long (*getter_unsigned_long_fn)(void*);
typedef float (*getter_float_fn)(void*);
typedef double (*getter_double_fn)(void*);
typedef long double (*getter_long_double_fn)(void*);
#ifdef __c99
typedef long long (*getter_long_long_fn)(void*);
typedef unsigned long long (*getter_unsigned_long_long_fn)(void*);
typedef intptr_t (*getter_intptr_fn)(void*);
typedef uintptr_t (*getter_uintptr_fn)(void*);
typedef int8_t (*getter_int8_fn)(void*);
typedef uint8_t (*getter_uint8_fn)(void*);
typedef int16_t (*getter_int16_fn)(void*);
typedef uint16_t (*getter_uint16_fn)(void*);
typedef int32_t (*getter_int32_fn)(void*);
typedef uint32_t (*getter_uint32_fn)(void*);
typedef int64_t (*getter_int64_fn)(void*);
typedef uint64_t (*getter_uint64_fn)(void*);
typedef bool (*getter_bool_fn)(void*);
#endif

/* Ce.POINTERS -- Setter-like Result-less Function Pointers */

typedef void (*setter_pointer_fn)(void*, void*);
typedef void (*setter_string_fn)(void*, char*);
typedef void (*setter_char_fn)(void*, char);
typedef void (*setter_signed_char_fn)(void*, signed char);
typedef void (*setter_unsigned_char_fn)(void*, unsigned char);
typedef void (*setter_short_fn)(void*, short);
typedef void (*setter_unsigned_short_fn)(void*, unsigned short);
typedef void (*setter_int_fn)(void*, int);
typedef void (*setter_unsigned_int_fn)(void*, unsigned int);
typedef void (*setter_long_fn)(void*, long);
typedef void (*setter_unsigned_long_fn)(void*, unsigned long);
typedef void (*setter_float_fn)(void*, float);
typedef void (*setter_double_fn)(void*, double);
typedef void (*setter_long_double_fn)(void*, long double);
#ifdef __c99
typedef void (*setter_long_long_fn)(void*, long long);
typedef void (*setter_unsigned_long_long_fn)(void*, unsigned long long);
typedef void (*setter_intptr_fn)(void*, intptr_t);
typedef void (*setter_uintptr_fn)(void*, uintptr_t);
typedef void (*setter_int8_fn)(void*, int8_t);
typedef void (*setter_uint8_fn)(void*, uint8_t);
typedef void (*setter_int16_fn)(void*, int16_t);
typedef void (*setter_uint16_fn)(void*, uint16_t);
typedef void (*setter_int32_fn)(void*, int32_t);
typedef void (*setter_uint32_fn)(void*, uint32_t);
typedef void (*setter_int64_fn)(void*, int64_t);
typedef void (*setter_uint64_fn)(void*, uint64_t);
typedef void (*setter_bool_fn)(void*, bool);
#endif

