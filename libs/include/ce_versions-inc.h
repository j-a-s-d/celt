/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: Ce
 * File: ce_versions-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef CE
#warning This is intended to be part of the C Extra Library.
#endif

/* Ce.VERSIONS -- C Version Shothand Definitions */

#if defined(__STDC__)
    /* C89/C90 compatible */
    #define __c89 /* ANSI */
    #define __c90 /* ISO */
#endif

#if defined(__STDC_VERSION__)
    #if __STDC_VERSION__ >= 199409L
        /* C94/C95 compatible */
        #define __c94
        #define __c95
    #endif
    #if __STDC_VERSION__ >= 199901L
        /* C99 compatible */
        #define __c99
    #endif
    #if __STDC_VERSION__ >= 201112L
        /* C11 compatible */
        #define __c11
    #endif
    #if __STDC_VERSION__ >= 201710L
        /* C17/C18 compatible */
        #define __c17
        #define __c18
    #endif
    #if __STDC_VERSION__ >= 202311L
        /* C23 compatible */
        #define __c23
    #endif
#endif

/* Ce.VERSIONS -- POSIX Version Shothand Definitions */

#if defined(_POSIX_C_SOURCE)
    #define __posix_compliant
    #if (_POSIX_C_SOURCE >= 1)
        /* POSIX.1-1990 (Original Standard) compatible */
        #define __posix90
    #endif
    #if (_POSIX_C_SOURCE >= 199309L)
        /* POSIX.1b-1993 (Real-time Extensions) compatible */
        #define __posix93
    #endif
    #if (_POSIX_C_SOURCE >= 199506L)
        /* POSIX.1c-1995 (Threads) compatible */
        #define __posix95
    #endif
    #if (_POSIX_C_SOURCE >= 200112L)
        /* POSIX.1-2001 (SUSv3) compatible */
        #define __posix01
    #endif
    #if (_POSIX_C_SOURCE >= 200809L)
        /* POSIX.1-2008 (SUSv4) or later (including 2017/2024) compatible */
        #define __posix08
    #endif
#endif

