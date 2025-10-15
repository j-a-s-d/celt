/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: Ce
 * File: ce.h
 * Brief: only headers with macros and typedefs
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "ce_version-inc.h"

/* Ce -- Pragma Definitions */

#if defined(__GNUC__)
    #define CE_PRAGMA(x) _Pragma(#x)
    #define CE_MESSAGE(msg) CE_PRAGMA(message msg)
#endif

/* Ce -- Headers Inclusion */

#include "ce_platform-inc.h"
#include "ce_versions-inc.h"
#include "ce_attributes-inc.h"
#include "ce_memory-inc.h"
#include "ce_polyfills-inc.h"
#include "ce_pointers-inc.h"

/* Ce -- General-Purpose Macros */

#define ___STR_IMPL(x) #x
#define STR(x) ___STR_IMPL(x) /* just like cdefs.h's __STRING */
#define ___CONCAT_IMPL(x, y) x##y
#define CONCAT(x, y) ___CONCAT_IMPL(x, y) /* just like cdefs.h's CONCAT */
#define LINE_UNIQUE_NAME(base) CONCAT(base, __LINE__)
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0])) /* analog to Microsoft's _countof macro */
#define STR_LEN(S) (ARRAY_SIZE(S) - 1)
#define UNUSED(x) (void)(x)
#define NOOP_STATEMENT ((void)0)
#define EMPTY_BLOCK {}
#define NOOP_LOOP do EMPTY_BLOCK while(0)
#define EXPERIMENTAL 

#ifdef __cplusplus
}
#endif

