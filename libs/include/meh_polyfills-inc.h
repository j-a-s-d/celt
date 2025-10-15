/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: MeH
 * File: meh_polyfills-inc.h
 * Brief: part of MeH
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef MEH
#warning This is intended to be part of the MeH C Library.
#endif

/* MeH.POLYFILLS -- strdup Routine */

#ifndef __posix08
/* strdup is not part of the ISO C99 standard (but POSIX.1-2001, and exposed in POSIX.1-2008) */
static inline char* __strdup(const char* s) {
    size_t z = strlen(s) + 1;
    char* p = ce_malloc(z);
    if (assigned(p)) memcpy(p, s, z);
    return p;
}
/* same for strndup */
static inline char* __strndup(const char* src, size_t size) {
    size_t i;
    // Find the minimum between the string length and 'size'
    for (i = 0; i < size && src[i]; ++i)
        ;
    char* dest = ce_malloc(i + 1); // +1 for the null terminator
    if (dest == NULL) return NULL;
    for (size_t j = 0; j < i; ++j)
        dest[j] = src[j];
    dest[i] = '\0';
    return dest;
}
#define strdup __strdup
#define strndup __strndup
#else
    #ifndef __c23
        #define __strdup strdup
        #define __strndup strndup
    #endif
#endif

/* MeH.POLYFILLS -- Other Macros */

#ifndef __FUNCTION__
    /* not in gcc nor clang or running -pedantic */
    #define __FUNCTION__ __func__
#endif

