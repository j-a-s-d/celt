/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_strhashbag-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

/*
    This is a simple hash bag for storing string tokens allowing duplicates.
    Additionally tt also provides a stringify function.
*/

#ifndef KEWL_STRHASHBAG_ALIGNMENT
    #define KEWL_STRHASHBAG_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef KEWL_STRHASHBAG_SIZE
    #define KEWL_STRHASHBAG_SIZE 997
#endif

#ifndef KEWL_STRHASHBAG_FUNCTION
    #define KEWL_STRHASHBAG_FUNCTION djb2_hash
#endif

#ifndef KEWL_STRHASHBAG_TYPE
    #define KEWL_STRHASHBAG_TYPE uint32_t
#endif

typedef struct kewl_strhashbag_node_dt *kewl_strhashbag_dt;
typedef KEWL_STRHASHBAG_TYPE (*kewl_strhashbag_hash_fn)(const char* string, KEWL_STRHASHBAG_TYPE size);

kewl_strhashbag_dt* kewl_strhashbag_create(kewl_strhashbag_hash_fn hash_function);
static inline kewl_strhashbag_dt* kewl_strhashbag_make(void) {
    return kewl_strhashbag_create(KEWL_STRHASHBAG_FUNCTION);
}
bool kewl_strhashbag_has(kewl_strhashbag_dt* hb, const char* token);
bool kewl_strhashbag_add(kewl_strhashbag_dt* hb, const char* token);
bool kewl_strhashbag_remove_once(kewl_strhashbag_dt* hb, const char* token);
bool kewl_strhashbag_remove_every(kewl_strhashbag_dt* hb, const char* token);
ssize_t kewl_strhashbag_count_total(kewl_strhashbag_dt* hb);
ssize_t kewl_strhashbag_count_every(kewl_strhashbag_dt* hb, const char* token);
char* kewl_strhashbag_stringify(kewl_strhashbag_dt* hb, char separator);
void kewl_strhashbag_clear(kewl_strhashbag_dt* hb);
void kewl_strhashbag_destroy(kewl_strhashbag_dt* hb);

