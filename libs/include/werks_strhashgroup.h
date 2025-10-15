/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: WeRKS STRHASHGROUP
 * File: werks_strhashgroup.h
 * Brief: string hash group
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
    This is a string hash collection with optional duplicates, events and more.
*/

#include "kewl.h"

#define WERKS_STRHASHGROUP

#define WERKS_STRHASHGROUP_TYPE_NAME "werks_strhashgroup_dt"

#ifndef WERKS_STRHASHGROUP_ALIGNMENT
    #define WERKS_STRHASHGROUP_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

typedef struct werks_strhashgroup_dt werks_strhashgroup_dt;

typedef bool (*werks_strhashgroup_on_before_insertion_handler_fn)(werks_strhashgroup_dt* group, const char* token);
typedef bool (*werks_strhashgroup_on_before_deletion_handler_fn)(werks_strhashgroup_dt* group, const char* token);

werks_strhashgroup_dt* werks_strhashgroup_create(bool accept_duplicates);
void werks_strhashgroup_destroy(werks_strhashgroup_dt* group);
const kewl_component_dt* werks_strhashgroup_get_component(werks_strhashgroup_dt* group);

void werks_strhashgroup_set_on_before_insertion(werks_strhashgroup_dt* group, werks_strhashgroup_on_before_insertion_handler_fn handler);
werks_strhashgroup_on_before_insertion_handler_fn werks_strhashgroup_get_on_before_insertion(werks_strhashgroup_dt* group);
void werks_strhashgroup_set_on_before_deletion(werks_strhashgroup_dt* group, werks_strhashgroup_on_before_deletion_handler_fn handler);
werks_strhashgroup_on_before_deletion_handler_fn werks_strhashgroup_get_on_before_deletion(werks_strhashgroup_dt* group);

bool werks_strhashgroup_has(werks_strhashgroup_dt* group, const char* token);
bool werks_strhashgroup_add(werks_strhashgroup_dt* group, const char* token);
bool werks_strhashgroup_remove_once(werks_strhashgroup_dt* group, const char* token);
bool werks_strhashgroup_remove_every(werks_strhashgroup_dt* group, const char* token);
ssize_t werks_strhashgroup_count_total(werks_strhashgroup_dt* group);
ssize_t werks_strhashgroup_count_every(werks_strhashgroup_dt* group, const char* token);
bool werks_strhashgroup_read_from_string(werks_strhashgroup_dt* group, const char* data, const char* separator);
char* werks_strhashgroup_write_to_string(werks_strhashgroup_dt* group, char separator);
void werks_strhashgroup_clear(werks_strhashgroup_dt* group);

#ifdef __cplusplus
}
#endif


