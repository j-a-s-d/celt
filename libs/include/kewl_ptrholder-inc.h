/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_ptrholder-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

/*
    This is a transparent, generic and handy pointer array.
    It's main purpose is to hold pointers (allowing null),
    allow a basic looping functionality and provide with a
    separator-customizable stringify functionality.
*/

#ifndef KEWL_PTRHOLDER_ALIGNMENT
    #define KEWL_PTRHOLDER_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef KEWL_PTRHOLDER_GROW_FACTOR
    #define KEWL_PTRHOLDER_GROW_FACTOR 2.0f
#endif

#ifndef KEWL_PTRHOLDER_GROW_PADDING
    #define KEWL_PTRHOLDER_GROW_PADDING 0.0f
#endif

#ifndef KEWL_PTRHOLDER_POINTER_TYPE
    #define KEWL_PTRHOLDER_POINTER_TYPE void* // you can use otherwise like: uintptr_t
#endif

#ifndef KEWL_PTRHOLDER_POINTER_FORMAT
    #define KEWL_PTRHOLDER_POINTER_FORMAT "%p%c" // you can use otherwise like: "%" PRIxPTR "%c"
#endif

#ifndef KEWL_PTRHOLDER_POINTER_LENGTH
    #define KEWL_PTRHOLDER_POINTER_LENGTH 19 // this means pointer string is up to 19 chars long (64-bit hex and the separator)
#endif

typedef struct kewl_ptrholder_dt kewl_ptrholder_dt;

typedef KEWL_PTRHOLDER_POINTER_TYPE kewl_ptrholder_ptr_dt;

typedef qsort_comparator_fn kewl_ptrholder_sorter_fn;

typedef void (*kewl_ptr_item_callback_fn)(kewl_ptrholder_dt* holder, kewl_ptrholder_ptr_dt ptr);
typedef void (*kewl_ptr_item_with_reference_callback_fn)(kewl_ptrholder_dt* holder, kewl_ptrholder_ptr_dt ptr, void* ref);

kewl_ptrholder_dt* kewl_ptrholder_create(size_t initial_capacity);
size_t kewl_ptrholder_get_size(kewl_ptrholder_dt* holder);
size_t kewl_ptrholder_get_capacity(kewl_ptrholder_dt* holder);
float kewl_ptrholder_get_capacity_grow_factor(kewl_ptrholder_dt* holder);
float kewl_ptrholder_get_capacity_grow_padding(kewl_ptrholder_dt* holder);
void kewl_ptrholder_set_capacity_grow_factor(kewl_ptrholder_dt* holder, float factor);
void kewl_ptrholder_set_capacity_grow_padding(kewl_ptrholder_dt* holder, float padding);
bool kewl_ptrholder_grow_capacity(kewl_ptrholder_dt* holder, float factor, float padding);
bool kewl_ptrholder_add(kewl_ptrholder_dt* holder, kewl_ptrholder_ptr_dt value);
bool kewl_ptrholder_replace_once(kewl_ptrholder_dt* holder, kewl_ptrholder_ptr_dt old_value, kewl_ptrholder_ptr_dt new_value);
bool kewl_ptrholder_replace_every(kewl_ptrholder_dt* holder, kewl_ptrholder_ptr_dt old_value, kewl_ptrholder_ptr_dt new_value);
size_t kewl_ptrholder_count_every(kewl_ptrholder_dt* const arr, kewl_ptrholder_ptr_dt value);
bool kewl_ptrholder_delete_once(kewl_ptrholder_dt* holder, kewl_ptrholder_ptr_dt value);
bool kewl_ptrholder_delete_every(kewl_ptrholder_dt* holder, kewl_ptrholder_ptr_dt value);
bool kewl_ptrholder_has(kewl_ptrholder_dt* holder, kewl_ptrholder_ptr_dt value);
kewl_ptrholder_ptr_dt kewl_ptrholder_get(kewl_ptrholder_dt* holder, size_t index);
char* kewl_ptrholder_stringify(kewl_ptrholder_dt* holder, char separator);
void kewl_ptrholder_loop(kewl_ptrholder_dt* holder, kewl_ptr_item_callback_fn cb);
void kewl_ptrholder_loop_with_reference(kewl_ptrholder_dt* holder, kewl_ptr_item_with_reference_callback_fn cb, void* ref);
void kewl_ptrholder_sort(kewl_ptrholder_dt* holder, kewl_ptrholder_sorter_fn comparator);
void kewl_ptrholder_reverse(kewl_ptrholder_dt* holder);
void kewl_ptrholder_clear(kewl_ptrholder_dt* holder);
void kewl_ptrholder_destroy(kewl_ptrholder_dt* holder);

#define PTRHOLDER_EACH_CASTED(holder, type, var, block) { \
    size_t sz = kewl_ptrholder_get_size(holder); \
    for (size_t i = 0; i < sz; i++) { \
        type* var = (type*)kewl_ptrholder_get(holder, i); \
        if (assigned(var)) block; } \
    }
#define PTRHOLDER_REVERSE_EACH_CASTED(holder, type, var, block) { \
    size_t sz = kewl_ptrholder_get_size(holder); \
    for (ssize_t i = sz - 1; i >= 0; i--) { \
        type* var = (type*)kewl_ptrholder_get(holder, i); \
        if (assigned(var)) block; } \
    }

