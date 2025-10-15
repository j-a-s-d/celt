/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: Ce
 * File: ce_memory-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef CE
#warning This is intended to be part of the C Extra Library.
#endif

#include <malloc.h>
#include <alloca.h>

/* Ce.MEMORY -- Allocation Overrides */

#ifndef ce_malloc
    #define ce_malloc(size) malloc(size)
#endif
#ifndef ce_alloca
    #define ce_alloca(size) alloca(size)
#endif
#ifndef ce_calloc
    #define ce_calloc(nmemb, size) calloc(nmemb, size)
#endif
#ifndef ce_aligned_alloc
    #define ce_aligned_alloc(algn, size) aligned_alloc(algn, size)
#endif
#ifndef ce_realloc
    #define ce_realloc(ptr, size) realloc(ptr, size)
#endif
#ifndef ce_free
    #define ce_free(ptr) free(ptr)
#endif

/* Ce.MEMORY -- Allocation Definitions */

#define TYPE_MALLOC(type, count) (type*)ce_malloc(sizeof(type) * count)

#define TYPE_CALLOC(type, count) ((type*)ce_calloc(count, sizeof(type)))

#define TYPE_ALLOCA(type, count) (type*)ce_alloca(sizeof(type) * count)

#define TYPE_REALLOC(name, type, count) (type*)ce_realloc(name, sizeof(type) * count)

#define VAR_MALLOC(name, type) type* name = TYPE_MALLOC(type, 1)

#define VAR_CALLOC(name, type, count) type* name = TYPE_CALLOC(type, count)

#define VAR_ALLOCA(name, type) type* name = TYPE_ALLOCA(type, 1)

#define VAR_MALLOC_SIZE(name, type, size) type* name = (type*)ce_malloc(size)

#define VAR_ALLOCA_SIZE(name, type, size) type* name = (type*)ce_alloca(size)

#define STR_MALLOC(name, size) VAR_MALLOC_SIZE(name, char, size)

#define STR_ALLOCA(name, size) VAR_ALLOCA_SIZE(name, char, size)

/* Ce.MEMORY -- Default Values */

#define DEFAULT_POINTER ((void*) NULL)
#define DEFAULT_STRING ((char*) "")
#define DEFAULT_CHAR ((char) '\0')
#define DEFAULT_SIGNED_CHAR ((signed char) 0)
#define DEFAULT_UNSIGNED_CHAR ((unsigned char) 0)
#define DEFAULT_BOOL ((bool) 0)
#define DEFAULT_SHORT ((short) 0)
#define DEFAULT_UNSIGNED_SHORT ((unsigned short) 0)
#define DEFAULT_INT ((int) 0)
#define DEFAULT_UNSIGNED_INT ((unsigned int) 0U)
#define DEFAULT_LONG ((long) 0L)
#define DEFAULT_UNSIGNED_LONG ((unsigned long) 0UL)
#define DEFAULT_LONG_LONG ((long long) 0LL)
#define DEFAULT_UNSIGNED_LONG_LONG ((unsigned long long) 0ULL)
#define DEFAULT_FLOAT ((float) 0.0f)
#define DEFAULT_DOUBLE ((double) 0.0)
#define DEFAULT_LONG_DOUBLE ((long double) 0.0L)

/* Ce.MEMORY -- Alignment Definitions */

/* macros to align to the specified boundaries (in bytes) */
#if defined(__GNUC__) || defined(__clang__) || defined(__ARMCOMPILER_VERSION) || defined(__ARMCLANG_COMPILER_VERSION) || defined(__TI_ARM_CLANG__)
    #define ALIGN_4 __attribute__((aligned(4)))
    #define ALIGN_8 __attribute__((aligned(8)))
    #define ALIGN_16 __attribute__((aligned(16)))
    #define ALIGN_32 __attribute__((aligned(32)))
    #define ALIGN_64 __attribute__((aligned(64)))
    #define ALIGN_128 __attribute__((aligned(128)))
    #define ALIGN_256 __attribute__((aligned(256)))
    #define ALIGN_512 __attribute__((aligned(512)))
#elif defined(_MSC_VER)
    #define ALIGN_4 __declspec(align(4))
    #define ALIGN_8 __declspec(align(8))
    #define ALIGN_16 __declspec(align(16))
    #define ALIGN_32 __declspec(align(32))
    #define ALIGN_64 __declspec(align(64))
    #define ALIGN_128 __declspec(align(128))
    #define ALIGN_256 __declspec(align(256))
    #define ALIGN_512 __declspec(align(512))
#else /* no alignment specified in other compilers */
    #define ALIGN_4
    #define ALIGN_8
    #define ALIGN_16
    #define ALIGN_32
    #define ALIGN_64
    #define ALIGN_128
    #define ALIGN_256
    #define ALIGN_512
#endif

/* Ce.MEMORY -- Sizes Definitions */

#define NIBBLE_BITS 4
#define BYTE_BITS 8

#define KILOBYTE (1024)
#define MEGABYTE (1024 * KILOBYTE)
#define GIGABYTE (1024 * MEGABYTE)
#define TERABYTE (1024 * GIGABYTE)
#define PETABYTE (1024 * TERABYTE)
#define EXABYTE  (1024 * PETABYTE)

