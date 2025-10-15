/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: MeH
 * File: meh.h
 * Brief: only headers with macros and static inline functions
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "ce.h"

#define MEH

#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

/* MeH -- General Definitions */

#ifndef __c99
#error "This code requires C99 or a later standard. Please compile with -std=c99 or higher."
#endif

#define MEH_DEFAULT_ALIGNMENT ALIGN_16

/* MeH -- Headers Inclusion */

#ifndef MEH_DISABLE_POLYFILLS
#include "meh_polyfills-inc.h"
#endif

#ifndef MEH_DISABLE_MEMORY
#include "meh_memory-inc.h"
#endif

#ifndef MEH_DISABLE_LITERALS
#include "meh_literals-inc.h"
#endif

#ifndef MEH_DISABLE_LOOPS
#include "meh_loops-inc.h"
#endif

#ifndef MEH_DISABLE_HASH
#include "meh_hash-inc.h"
#endif

#ifndef MEH_DISABLE_MATH
#include "meh_math-inc.h"
#endif

#ifndef MEH_DISABLE_ARRAY
#include "meh_array-inc.h"
#endif

#ifndef MEH_DISABLE_FP
#include "meh_fp-inc.h"
#endif

#ifndef MEH_DISABLE_TULE
#include "meh_tule-inc.h"
#endif

#ifdef __cplusplus
}
#endif

