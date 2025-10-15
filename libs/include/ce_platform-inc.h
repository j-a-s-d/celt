/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: Ce
 * File: ce_platform-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef CE
#warning This is intended to be part of the C Extra Library.
#endif

/* Ce.PLATFORM -- Architecture Definitions */

#if defined(__x86_64__) || defined(_M_X64)
    #define __64bits
    #define __x86
#elif defined(__i386__) || defined(i386) || defined(_M_IX86)
    #define __32bits
    #define __x86
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define __64bits
    #define __arm
#elif defined(__arm__) || defined(_M_ARM)
    #define __32bits
    #define __arm
#endif

/* Ce.PLATFORM -- OS Definitions */

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) || defined(__linux__)
    /* good enough for code that will be running on unixes, linux (including android), macosx, etc. */
    #define __unix_like
    #define CTL_TERM "/dev/tty"
#elif defined(_WIN32) || defined(_WIN64)
    /* good enough for code that will be running on Windows 32-bits/64-bits, ReactOS, Wine, etc. */
    #define __windows_like
    #define CTL_TERM "CON"
#endif

#ifdef __cplusplus
}
#endif

