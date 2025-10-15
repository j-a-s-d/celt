/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: MeH
 * File: meh_tule-inc.h
 * Brief: part of MeH
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef MEH
#warning This is intended to be part of the MeH C Library.
#endif

/* MeH.TULE -- Translation Unit Life-cycle Execution macros */

// NOTE: first in the execution order of initializers
#define unit_initialization(block) __attribute__((constructor(101))) void ule_initialization(void) block

// NOTE: second in the execution order of initializers
#define unit_initializer(block) __attribute__((constructor(102))) void LINE_UNIQUE_NAME(tule_ini_)(void) block

// NOTE: last in the execution order of initializers
#define unit_initialize(block) __attribute__((constructor(65535))) void ule_initialize(void) block

// NOTE: first in the execution order of finalizers
#define unit_finalize(block) __attribute__((destructor(65535))) void ule_finalize(void) block

// NOTE: second in the execution order of finalizers
#define unit_finalizer(block) __attribute__((destructor(65534))) void LINE_UNIQUE_NAME(tule_fin_)(void) block

// NOTE: last in the execution order of finalizers
#define unit_finalization(block) __attribute__((destructor(101))) void ule_finalization(void) block

/* MeH.TULE -- Internal/Private Fields */

#ifndef MEH_DISABLE_INTERNAL

#ifndef MEH_INTERNAL_ALIGN
    #define MEH_INTERNAL_ALIGN MEH_DEFAULT_ALIGNMENT
#endif

// NOTE: specially useful when you need several different containers in a single .c file
#define unit_container(name, block) static struct MEH_INTERNAL_ALIGN block name

// NOTE: the internal_ private container is usually enough for a common .c file
#define unit_internal(block) unit_container(internal_, block)

#endif

