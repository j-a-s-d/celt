/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: Ce
 * File: ce_attributes-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef CE
#warning This is intended to be part of the C Extra Library.
#endif

/* Ce.ATTRIBUTES -- Compiler Attributes */

#if defined(__GNUC__) || defined(__clang__) /* __GNUC__ is also defined by clang but included for clarity */
    #define __unused __attribute__((unused))
#else
    #define __unused
#endif

#if defined(__clang__)
  #define __unoptimizable __attribute__((optnone))
#elif defined(__GNUC__)
  #define __unoptimizable __attribute__((optimize("O0")))
#else
  #define __unoptimizable
#endif

#ifdef __c99
    #ifdef __c23
        #define __deprecated(...) [[deprecated(__VA_ARGS__)]]
    #else
        #if defined(__GNUC__) || defined(__clang__) /* __GNUC__ is also defined by clang but included for clarity */
            #define __deprecated(...) __attribute__((deprecated(__VA_ARGS__)))
        #else
            #define __deprecated()
        #endif
    #endif
#else
    #define __deprecated()
#endif

#ifdef __cplusplus
}
#endif

