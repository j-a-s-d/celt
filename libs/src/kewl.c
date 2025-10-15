/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "kewl.h"

#ifndef KEWL_DISABLE_DUMMIES
void noop(void) {
}

bool truthy(void) {
    return true;
}

bool falsy(void) {
    return false;
}
#endif

// INCLUDES

#include "kewl_polyfills-inc.c"

#ifndef KEWL_DISABLE_COMPONENT
#include "kewl_component-inc.c"
#endif

#ifndef KEWL_DISABLE_DEBUG
#include "kewl_debug-inc.c"
#endif

#ifndef KEWL_DISABLE_DATETIME
#include "kewl_datetime-inc.c"
#endif

#ifndef KEWL_DISABLE_FILESYSTEM
#include "kewl_filesystem-inc.c"
#endif

#ifndef KEWL_DISABLE_MATH
#include "kewl_math-inc.c"
#endif

#ifndef KEWL_DISABLE_TASK
#include "kewl_task-inc.c"
#endif

#ifndef KEWL_DISABLE_PTRHOLDER
#include "kewl_ptrholder-inc.c"
#endif

#ifndef KEWL_DISABLE_SAMPLEPROFILER
#include "kewl_sampleprofiler-inc.c"
#endif

#ifndef KEWL_DISABLE_STRHASHBAG
#include "kewl_strhashbag-inc.c"
#endif

#ifndef KEWL_DISABLE_STRHASHSET
#include "kewl_strhashset-inc.c"
#endif

#ifndef KEWL_DISABLE_STREAMS
#include "kewl_streams-inc.c"
#endif

#ifndef KEWL_DISABLE_STRINGS
#include "kewl_strings-inc.c"
#endif

#ifndef KEWL_DISABLE_CMDLINE
#include "kewl_cmdline-inc.c"
#endif

