/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl.h
 * Brief: more headers and some .c files to add a bunch of useful functions and data types
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define KEWL

#include "meh.h"

#ifndef __c99
#error "This code requires C99 or a later standard. Please compile with -std=c99 or higher."
#endif

#include <stdio.h>
#include <inttypes.h>

#ifndef KEWL_DISABLE_DUMMIES
// does nothing
void noop(void);

// returns true
bool truthy(void);

// returns false
bool falsy(void);
#endif

// INCLUDES

#include "kewl_polyfills-inc.h"

#ifndef KEWL_DISABLE_COMPONENT
#include "kewl_component-inc.h"
#endif

#ifndef KEWL_DISABLE_DEBUG
#include "kewl_debug-inc.h"
#endif

#ifndef KEWL_DISABLE_DATETIME
#include "kewl_datetime-inc.h"
#endif

#ifndef KEWL_DISABLE_FILESYSTEM
#include "kewl_filesystem-inc.h"
#endif

#ifndef KEWL_DISABLE_MATH
#include "kewl_math-inc.h"
#endif

#ifndef KEWL_DISABLE_TASK
#include "kewl_task-inc.h"
#endif

#ifndef KEWL_DISABLE_PTRHOLDER
#include "kewl_ptrholder-inc.h"
#endif

#ifndef KEWL_DISABLE_SAMPLEPROFILER
#include "kewl_sampleprofiler-inc.h"
#endif

#ifndef KEWL_DISABLE_STRHASHBAG
#include "kewl_strhashbag-inc.h"
#endif

#ifndef KEWL_DISABLE_STRHASHSET
#include "kewl_strhashset-inc.h"
#endif

#ifndef KEWL_DISABLE_STREAMS
#include "kewl_streams-inc.h"
#endif

#ifndef KEWL_DISABLE_STRINGS
#include "kewl_strings-inc.h"
#endif

#ifndef KEWL_DISABLE_CMDLINE
#include "kewl_cmdline-inc.h"
#endif

#ifdef __cplusplus
}
#endif

