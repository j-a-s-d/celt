/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_strhashset-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

/*
    This is a simple hash set for storing unique string tokens.
    Additionally tt also provides a stringify function.
*/

#ifndef KEWL_STRHASHSET_ALIGNMENT
    #define KEWL_STRHASHSET_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef KEWL_STRHASHSET_SIZE
    #define KEWL_STRHASHSET_SIZE 997
#endif

#ifndef KEWL_STRHASHSET_FUNCTION
    #define KEWL_STRHASHSET_FUNCTION djb2_hash
#endif

#ifndef KEWL_STRHASHSET_TYPE
    #define KEWL_STRHASHSET_TYPE uint32_t
#endif

typedef struct kewl_strhashset_node_dt *kewl_strhashset_dt;
typedef KEWL_STRHASHSET_TYPE (*kewl_strhashset_hash_fn)(const char* string, KEWL_STRHASHSET_TYPE size);

kewl_strhashset_dt* kewl_strhashset_create(kewl_strhashset_hash_fn hash_function);
static inline kewl_strhashset_dt* kewl_strhashset_make(void) {
    return kewl_strhashset_create(KEWL_STRHASHSET_FUNCTION);
}
bool kewl_strhashset_has(kewl_strhashset_dt* hs, const char* token);
bool kewl_strhashset_add(kewl_strhashset_dt* hs, const char* token);
bool kewl_strhashset_remove(kewl_strhashset_dt* hs, const char* token);
ssize_t kewl_strhashset_count(kewl_strhashset_dt* hs);
char* kewl_strhashset_stringify(kewl_strhashset_dt* hs, char separator);
void kewl_strhashset_clear(kewl_strhashset_dt* hs);
void kewl_strhashset_destroy(kewl_strhashset_dt* hs);

