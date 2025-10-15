/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: GeST PFSSYSNFO
 * File: gest_pfssysnfo.h
 * Brief: proc pseudo-filesystem system information utilities
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "meh.h"

#if !defined(__unix_like)
#error "GeST PfsSysNfo requires the a Unix-like system to work."
#endif

#define GeST_PFSSYSNFO

#include <unistd.h>

// GeST.FILES

int count_open_files(pid_t pid);

// GeST.MEMORY

typedef struct {
    unsigned long total_memory;
    unsigned long free_memory;
    unsigned long available_memory;
    float free_percentage;
    float available_percentage;
    bool error;
} pfs_memory_info_dt;

pfs_memory_info_dt get_memory_info(void);

// GeST.CPU

float get_cpu_usage(void);

#ifdef __cplusplus
}
#endif

