/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_polyfills-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

/* POLYFILLS -- ssize_t Type */

#ifndef __posix08
    #if SIZE_MAX == USHRT_MAX
        typedef short ssize_t;
        #define SSIZE_MIN  SHRT_MIN
        #define SSIZE_MAX  SHRT_MAX
    #elif SIZE_MAX == UINT_MAX
        typedef int ssize_t;
        #define SSIZE_MIN  INT_MIN
        #define SSIZE_MAX  INT_MAX
    #elif SIZE_MAX == ULONG_MAX
        typedef long ssize_t;
        #define SSIZE_MIN  LONG_MIN
        #define SSIZE_MAX  LONG_MAX
    #elif SIZE_MAX == ULLONG_MAX
        typedef long long ssize_t;
        #define SSIZE_MIN  LLONG_MIN
        #define SSIZE_MAX  LLONG_MAX
    #else /*SIZE_MAX == UINTMAX_MAX*/
        typedef intmax_t ssize_t;
        #define SSIZE_MIN  INTMAX_MIN
        #define SSIZE_MAX  INTMAX_MAX
    #endif
#endif

/* POLYFILLS -- getline Routine */

#ifndef __posix08

ssize_t getline(char** lineptr, size_t* n, FILE* stream);

#endif

