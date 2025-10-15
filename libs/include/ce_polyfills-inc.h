/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: Ce
 * File: ce_polyfills-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef CE
#warning This is intended to be part of the C Extra Library.
#endif

#include <stddef.h>

/* Ce.POLYFILLS -- aligned_alloca Function */

#include <limits.h>

/* allocates memory at the stack with the specified alignment
   NOTE: this is analog to c11's aligned_alloc for the heap (for which can not
     be created a direct polyfill easily due to the original pointer issue) */
#if !defined(aligned_alloca)
    #if defined(__has_builtin)
        #if __has_builtin(__builtin_alloca_with_align)
            #define aligned_alloca(alignment, size) \
                __builtin_alloca_with_align(size, alignment * CHAR_BIT)
        #endif
    #endif
    #if !defined(aligned_alloca)
        #define aligned_alloca(alignment, size) \
            ((void*)(((unsigned long)(ce_alloca((size) + (alignment) - 1)) + (alignment) - 1) & ~((alignment) - 1)))
    #endif
#endif

/* Ce.POLYFILLS -- bool Type */

/* ensures the bool type is always present (from c89 to c23) */
#if defined(__c99)
    #if !defined(__c23)
        #include <stdbool.h>
    #endif
#elif !defined(__bool_true_false_are_defined)
    #ifdef _Bool
        #define bool _Bool
    #else
        #define bool int
    #endif
    #define true 1
    #define false 0
    #define __bool_true_false_are_defined 1
#elif !defined(__cplusplus) && !defined(bool)
    typedef enum { false = 0, true = 1 } bool; /* shim style */
#endif

