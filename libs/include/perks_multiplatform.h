/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: PeRKS MULTIPLATFORM
 * File: perks_multiplatform.h
 * Brief: utilities to ease porting foreign code to c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "kewl.h"

#define PERKS_MULTIPLATFORM

// PeRKS.MULTIPLATFORM -- Basic Windows-style typedefs for portability

#include <wchar.h>

typedef int BOOL;               /* BOOL is signed int in Windows */
typedef uint32_t DWORD;         /* DWORD is 32-bit unsigned */
typedef void VOID;              /* VOID is void */
typedef unsigned char BYTE;     /* BYTE is 8-bit unsigned */
typedef uint16_t WORD;          /* WORD is 16-bit unsigned */
typedef wchar_t WCHAR;          /* WCHAR is wide char (16-bit or 32-bit depending on platform) */

typedef WCHAR *LPWSTR;          /* Pointer to wide string */
typedef const WCHAR *LPCWSTR;   /* Pointer to const wide string */

typedef char CHAR;              /* ANSI char */
typedef CHAR *LPSTR;            /* Pointer to ANSI string */
typedef const CHAR *LPCSTR;     /* Pointer to const ANSI string */

typedef void *HANDLE;           /* HANDLE is void pointer */
typedef HANDLE HWND;            /* Window handle (opaque pointer) */

typedef unsigned char BOOLEAN; /* BOOLEAN is unsigned char */

typedef int32_t LONG;           /* LONG is signed 32-bit */
typedef uint64_t DWORDLONG;     /* 64-bit unsigned */

#define TRUE 1
#define FALSE 0

// PeRKS.MULTIPLATFORM -- Pascal C-types and operators analogs

#include <iso646.h> // and, or, xor, etc (present since c94)

#define ppointer void**
#define pchar char*
#define ppchar char**
#define boolean bool
#define byte uint8_t
#define shortint signed char
#define smallint short
#define integer long int
#define cardinal unsigned long int
#define real float
#define nil NULL
#define halt(code) exit(code)
#define freeAndNil(ptr) (do { ce_free(ptr); (ptr) = NULL; } while(0))

// PeRKS.MULTIPLATFORM -- Console

// Perl/Ruby/Haskell/BCPL/etc unless analog
#define unless(condition) if (!(condition))

// Java/Kotlin/Julia/Rust/etc println analog
#define println() printf("\n")

// PeRKS.MULTIPLATFORM -- Echo

#ifndef __c11
#error "perks_multiplatform requires the C11 or higher to work."
#endif

// Shells/PHP/etc echo analog (only for C11 or newer code)
void echo_ptr(const void* x);
void echo_int(int x);
void echo_long_int(long int x);
void echo_long_long_int(long long int x);
void echo_unsigned_int(unsigned int x);
void echo_unsigned_long_int(unsigned long int x);
void echo_unsigned_long_long_int(unsigned long long int x);
void echo_float(float x);
void echo_double(double x);
void echo_long_double(long double x);
void echo_char(char x);
void echo_signed_char(signed char x);
void echo_unsigned_char(unsigned char x);
void echo_short(short x);
void echo_unsigned_short(unsigned short x);
void echo_str(const char* x);
void echo_bool(bool x);
void echo_float_complex(float _Complex x);
void echo_double_complex(double _Complex x);
void echo_long_double_complex(long double _Complex x);
#define echo(x) _Generic((x), \
    char: echo_char, \
    signed char: echo_signed_char, \
    unsigned char: echo_unsigned_char, \
    short: echo_short, \
    unsigned short: echo_unsigned_short, \
    int: echo_int, \
    unsigned int: echo_unsigned_int, \
    long int: echo_long_int, \
    unsigned long int: echo_unsigned_long_int, \
    long long int: echo_long_long_int, \
    unsigned long long int: echo_unsigned_long_long_int, \
    float: echo_float, \
    double: echo_double, \
    long double: echo_long_double, \
    float _Complex: echo_float_complex, \
    double _Complex: echo_double_complex, \
    long double _Complex: echo_long_double_complex, \
    _Bool: echo_bool, \
    char*: echo_str, \
    const char*: echo_str, \
    void*: echo_ptr, \
    const void*: echo_ptr \
)(x)

// JavaScript typeof analog
#define typename(x) _Generic((x), \
    char: "char", \
    signed char: "signed char", \
    unsigned char: "unsigned char", \
    short: "short", \
    unsigned short: "unsigned short", \
    int: "int", \
    unsigned int: "unsigned int", \
    long int: "long int", \
    unsigned long int: "unsigned long int", \
    long long int: "long long int", \
    unsigned long long int: "unsigned long long int", \
    float: "float", \
    double: "double", \
    long double: "long double", \
    float _Complex: "float complex", \
    double _Complex: "double complex", \
    long double _Complex: "long double complex", \
    _Bool: "_Bool", \
    char*: "char*", \
    const char*: "const char*", \
    void*: "void*", \
    const void*: "const void*", \
    default: "unknown")

/**
 * If it is in DEVELOPMENT mode, it echoes the specified value, or does nothing otherwise.
 * In any case, it returns the specified value.
 * It's behaviour allows you to intercept values on assignment (ex. x = debug(getX())).
 */
#define debug(X) ({ \
    __typeof__(X) _x = (X); \
    (DEVELOPMENT) ? (echo(_x), _x) : _x; \
})

#ifdef __cplusplus
}
#endif

