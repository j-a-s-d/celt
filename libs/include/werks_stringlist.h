/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: WeRKS STRINGLIST
 * File: werks_stringlist.h
 * Brief: general-purpose string list
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "kewl.h"

#define WERKS_STRINGLIST

#define WERKS_STRINGLIST_TYPE_NAME "werks_stringlist_dt"

#ifndef WERKS_STRINGLIST_INITIAL_CAPACITY
    #define WERKS_STRINGLIST_INITIAL_CAPACITY 128
#endif

#ifndef WERKS_STRINGLIST_ALIGNMENT
    #define WERKS_STRINGLIST_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef WERKS_STRINGLIST_GROW_FACTOR
    #define WERKS_STRINGLIST_GROW_FACTOR 2.0f
#endif

#ifndef WERKS_STRINGLIST_GROW_PADDING
    #define WERKS_STRINGLIST_GROW_PADDING 0.0f
#endif

#ifndef WERKS_STRINGLIST_SENTINEL_LIMIT
    #define WERKS_STRINGLIST_SENTINEL_LIMIT MEH_DEFAULT_SENTINEL_LIMIT
#endif

typedef struct werks_stringlist_dt werks_stringlist_dt;

// life-cycle

werks_stringlist_dt* werks_stringlist_create(ssize_t initial_capacity);
static inline werks_stringlist_dt* werks_stringlist_make(void) {
    return werks_stringlist_create(WERKS_STRINGLIST_INITIAL_CAPACITY);
}
werks_stringlist_dt* werks_stringlist_clone(werks_stringlist_dt* sl);
werks_stringlist_dt* werks_stringlist_concatenate(werks_stringlist_dt* sl1, werks_stringlist_dt* sl2);
void werks_stringlist_destroy(werks_stringlist_dt* sl);
const kewl_component_dt* werks_stringlist_get_component(werks_stringlist_dt* sl);

// dimensions

ssize_t werks_stringlist_get_size(werks_stringlist_dt* sl);
ssize_t werks_stringlist_get_capacity(werks_stringlist_dt* sl);
float werks_stringlist_get_capacity_grow_factor(werks_stringlist_dt* sl);
float werks_stringlist_get_capacity_grow_padding(werks_stringlist_dt* sl);
void werks_stringlist_set_capacity_grow_factor(werks_stringlist_dt* sl, float factor);
void werks_stringlist_set_capacity_grow_padding(werks_stringlist_dt* sl, float padding);
bool werks_stringlist_grow_capacity(werks_stringlist_dt* sl, float factor, float padding);
void werks_stringlist_pack(werks_stringlist_dt* sl);

// basic

const char* werks_stringlist_get(werks_stringlist_dt* sl, ssize_t index);
bool werks_stringlist_set(werks_stringlist_dt* sl, ssize_t index, const char* value);
bool werks_stringlist_formatted_set(werks_stringlist_dt* sl, ssize_t index, const char* fmt, ...);

// addition

bool werks_stringlist_append(werks_stringlist_dt* sl, const char* value);
bool werks_stringlist_insert(werks_stringlist_dt* sl, const char* value, ssize_t index);
bool werks_stringlist_insert_all(werks_stringlist_dt* sl, werks_stringlist_dt* nl, ssize_t index);
bool werks_stringlist_append_all(werks_stringlist_dt* sl, werks_stringlist_dt* nl);
bool werks_stringlist_prepend_all(werks_stringlist_dt* sl, werks_stringlist_dt* nl);
bool werks_stringlist_prepend(werks_stringlist_dt* sl, const char* value);
bool werks_stringlist_include_all(werks_stringlist_dt* sl, werks_stringlist_dt* nl);
bool werks_stringlist_include(werks_stringlist_dt* sl, const char* value);
bool werks_stringlist_formatted_append(werks_stringlist_dt* sl, const char* fmt, ...);
bool werks_stringlist_formatted_prepend(werks_stringlist_dt* sl, const char* fmt, ...);

// deletion

void werks_stringlist_clear(werks_stringlist_dt* sl);
bool werks_stringlist_delete(werks_stringlist_dt* sl, ssize_t index);
bool werks_stringlist_delete_last(werks_stringlist_dt* sl);
bool werks_stringlist_delete_from_to(werks_stringlist_dt* sl, ssize_t from_index, ssize_t to_index);
bool werks_stringlist_drop_last(werks_stringlist_dt* sl, ssize_t amount);
bool werks_stringlist_drop_first(werks_stringlist_dt* sl, ssize_t amount);
bool werks_stringlist_remove_once(werks_stringlist_dt* sl, const char* value);
bool werks_stringlist_remove_all(werks_stringlist_dt* sl, const char* value);
bool werks_stringlist_remove_prefixed(werks_stringlist_dt* sl, const char* prefix);
bool werks_stringlist_remove_not_prefixed(werks_stringlist_dt* sl, const char* prefix);
bool werks_stringlist_remove_suffixed(werks_stringlist_dt* sl, const char* suffix);
bool werks_stringlist_remove_not_suffixed(werks_stringlist_dt* sl, const char* suffix);
bool werks_stringlist_remove_containing(werks_stringlist_dt* sl, const char* text);
bool werks_stringlist_remove_not_containing(werks_stringlist_dt* sl, const char* text);
bool werks_stringlist_remove_all_containing_any(werks_stringlist_dt* sl, werks_stringlist_dt* nl);
bool werks_stringlist_remove_all_not_containing_any(werks_stringlist_dt* sl, werks_stringlist_dt* nl);
bool werks_stringlist_exclude_all(werks_stringlist_dt* sl, werks_stringlist_dt* nl);
bool werks_stringlist_keep_all(werks_stringlist_dt* sl, werks_stringlist_dt* nl);

// extraction

char* werks_stringlist_take(werks_stringlist_dt* sl, ssize_t index);
char* werks_stringlist_take_last(werks_stringlist_dt* sl);
werks_stringlist_dt* werks_stringlist_extract_first(werks_stringlist_dt* sl, ssize_t amount);
werks_stringlist_dt* werks_stringlist_extract_last(werks_stringlist_dt* sl, ssize_t amount);
werks_stringlist_dt* werks_stringlist_extract_from_to(werks_stringlist_dt* sl, ssize_t from_index, ssize_t to_index);
werks_stringlist_dt* werks_stringlist_extract_prefixed(werks_stringlist_dt* sl, const char* prefix);
werks_stringlist_dt* werks_stringlist_extract_not_prefixed(werks_stringlist_dt* sl, const char* prefix);
werks_stringlist_dt* werks_stringlist_extract_suffixed(werks_stringlist_dt* sl, const char* suffix);
werks_stringlist_dt* werks_stringlist_extract_not_suffixed(werks_stringlist_dt* sl, const char* suffix);

// stack

FUNC_ALIAS_DECL(bool, werks_stringlist_push, (werks_stringlist_dt* sl, const char* value));
FUNC_ALIAS_DECL(char*, werks_stringlist_pop, (werks_stringlist_dt* sl));

// inspection

bool werks_stringlist_is_empty(werks_stringlist_dt* sl);
ssize_t werks_stringlist_index_of(werks_stringlist_dt* sl, const char* value);
ssize_t werks_stringlist_last_index_of(werks_stringlist_dt* sl, const char* value);
bool werks_stringlist_has(werks_stringlist_dt* sl, const char* value);
ssize_t werks_stringlist_count_occurrences(werks_stringlist_dt* sl, const char* value);
ssize_t werks_stringlist_count_prefixed(werks_stringlist_dt* sl, const char* prefix);
ssize_t werks_stringlist_count_suffixed(werks_stringlist_dt* sl, const char* suffix);

// freeze

bool werks_stringlist_is_frozen(werks_stringlist_dt* sl);
void werks_stringlist_freeze(werks_stringlist_dt* sl); // prevents from modifications
void werks_stringlist_unfreeze(werks_stringlist_dt* sl); // reallows modificactions

// ordering

bool werks_stringlist_swap(werks_stringlist_dt* sl, ssize_t index1, ssize_t index2);
bool werks_stringlist_move_first(werks_stringlist_dt* sl, ssize_t index);
bool werks_stringlist_move_up(werks_stringlist_dt* sl, ssize_t index);
bool werks_stringlist_move_down(werks_stringlist_dt* sl, ssize_t index);
bool werks_stringlist_move_last(werks_stringlist_dt* sl, ssize_t index);
bool werks_stringlist_reverse(werks_stringlist_dt* sl);
void werks_stringlist_sort(werks_stringlist_dt* sl); // Sorts the strings list in place
void werks_stringlist_shuffle(werks_stringlist_dt* sl, fn_int_fn rand_func); // Randomizes the order of the strings list

// iteration

typedef void (*werks_stringlist_loop_handler_fn)(werks_stringlist_dt* sl, ssize_t index, const char* string);
void werks_stringlist_loop(werks_stringlist_dt* sl, werks_stringlist_loop_handler_fn handler);
void werks_stringlist_reverse_loop(werks_stringlist_dt* sl, werks_stringlist_loop_handler_fn handler);
void werks_stringlist_loop_prefixed(werks_stringlist_dt* sl, const char* prefix, werks_stringlist_loop_handler_fn handler);
void werks_stringlist_reverse_loop_prefixed(werks_stringlist_dt* sl, const char* prefix, werks_stringlist_loop_handler_fn handler);
void werks_stringlist_loop_suffixed(werks_stringlist_dt* sl, const char* suffix, werks_stringlist_loop_handler_fn handler);
void werks_stringlist_reverse_loop_suffixed(werks_stringlist_dt* sl, const char* suffix, werks_stringlist_loop_handler_fn handler);
void werks_stringlist_loop_from_to(werks_stringlist_dt* sl, ssize_t from_index, ssize_t to_index, werks_stringlist_loop_handler_fn handler);
void werks_stringlist_reverse_loop_from_to(werks_stringlist_dt* sl, ssize_t from_index, ssize_t to_index, werks_stringlist_loop_handler_fn handler);

typedef char* (*werks_stringlist_treat_handler_fn)(werks_stringlist_dt* sl, ssize_t index, const char* string);
void werks_stringlist_treat(werks_stringlist_dt* sl, werks_stringlist_treat_handler_fn handler);
void werks_stringlist_reverse_treat(werks_stringlist_dt* sl, werks_stringlist_treat_handler_fn handler);

typedef void (*werks_stringlist_loop_with_reference_handler_fn)(werks_stringlist_dt* sl, ssize_t index, const char* string, void* reference);
void werks_stringlist_loop_with_reference(werks_stringlist_dt* sl, werks_stringlist_loop_with_reference_handler_fn handler, void* reference);
void werks_stringlist_reverse_loop_with_reference(werks_stringlist_dt* sl, werks_stringlist_loop_with_reference_handler_fn handler, void* reference);
void werks_stringlist_loop_prefixed_with_reference(werks_stringlist_dt* sl, const char* prefix, werks_stringlist_loop_with_reference_handler_fn handler, void* reference);
void werks_stringlist_reverse_loop_prefixed_with_reference(werks_stringlist_dt* sl, const char* prefix, werks_stringlist_loop_with_reference_handler_fn handler, void* reference);
void werks_stringlist_loop_suffixed_with_reference(werks_stringlist_dt* sl, const char* suffix, werks_stringlist_loop_with_reference_handler_fn handler, void* reference);
void werks_stringlist_reverse_loop_suffixed_with_reference(werks_stringlist_dt* sl, const char* suffix, werks_stringlist_loop_with_reference_handler_fn handler, void* reference);
void werks_stringlist_loop_from_to_with_reference(werks_stringlist_dt* sl, ssize_t from_index, ssize_t to_index, werks_stringlist_loop_with_reference_handler_fn handler, void* reference);
void werks_stringlist_reverse_loop_from_to_with_reference(werks_stringlist_dt* sl, ssize_t from_index, ssize_t to_index, werks_stringlist_loop_with_reference_handler_fn handler, void* reference);

typedef char* (*werks_stringlist_treat_with_reference_handler_fn)(werks_stringlist_dt* sl, ssize_t index, const char* string, void* reference);
void werks_stringlist_treat_with_reference(werks_stringlist_dt* sl, werks_stringlist_treat_with_reference_handler_fn handler, void* reference);
void werks_stringlist_reverse_treat_with_reference(werks_stringlist_dt* sl, werks_stringlist_treat_with_reference_handler_fn handler, void* reference);

#if defined(__GNUC__) && !defined(__clang__)
    #define werks_stringlist_each(l, parameter, code_block) \
        void LINE_UNIQUE_NAME(loop_handler_)(__unused werks_stringlist_dt*, __unused ssize_t, __unused const char* parameter) { code_block; } \
        werks_stringlist_loop(l, LINE_UNIQUE_NAME(loop_handler_));
    #define werks_stringlist_each_with_reference(l, parameter, reference, code_block, ref) \
        void LINE_UNIQUE_NAME(loop_with_reference_handler_)(__unused werks_stringlist_dt*, __unused ssize_t, __unused const char* parameter, __unused void* reference) { code_block; } \
        werks_stringlist_loop_with_reference(l, LINE_UNIQUE_NAME(loop_with_reference_handler_), ref);
    #define werks_stringlist_meach(l, parameter, code_block) \
        char* LINE_UNIQUE_NAME(treat_handler_)(__unused werks_stringlist_dt*, __unused ssize_t, __unused const char* parameter) { code_block; } \
        werks_stringlist_treat(l, LINE_UNIQUE_NAME(treat_handler_));
    #define werks_stringlist_meach_with_reference(l, parameter, reference, code_block, ref) \
        char* LINE_UNIQUE_NAME(treat_with_reference_handler_)(__unused werks_stringlist_dt*, __unused ssize_t, __unused const char* parameter, __unused void* reference) { code_block; } \
        werks_stringlist_treat_with_reference(l, LINE_UNIQUE_NAME(treat_with_reference_handler_), ref);
#endif

// empties

bool werks_stringlist_has_empties(werks_stringlist_dt* sl);
ssize_t werks_stringlist_count_empties(werks_stringlist_dt* sl);
ssize_t werks_stringlist_count_not_empties(werks_stringlist_dt* sl);
bool werks_stringlist_remove_empties(werks_stringlist_dt* sl);

// duplicates

bool werks_stringlist_has_duplicates(werks_stringlist_dt* sl);
ssize_t werks_stringlist_count_duplicates(werks_stringlist_dt* sl);
bool werks_stringlist_remove_duplicates(werks_stringlist_dt* sl);
werks_stringlist_dt* werks_stringlist_list_duplicates(werks_stringlist_dt* sl);

// replacing

bool werks_stringlist_replace_first_occurrence(werks_stringlist_dt* sl, const char* target, const char* value);
bool werks_stringlist_replace_last_occurrence(werks_stringlist_dt* sl, const char* target, const char* value);
bool werks_stringlist_replace_occurrences(werks_stringlist_dt* sl, const char* target, const char* value);
bool werks_stringlist_replace_first_occurrence_with(werks_stringlist_dt* sl, const char* target, werks_stringlist_dt* dl);
bool werks_stringlist_replace_last_occurrence_with(werks_stringlist_dt* sl, const char* target, werks_stringlist_dt* dl);
bool werks_stringlist_replace_occurrences_with(werks_stringlist_dt* sl, const char* target, werks_stringlist_dt* dl);
bool werks_stringlist_replace_from_to_with(werks_stringlist_dt* sl, ssize_t from_index, ssize_t to_index, werks_stringlist_dt* dl);

// formating

bool werks_stringlist_format_all(werks_stringlist_dt* sl, const char* format);
bool werks_stringlist_format(werks_stringlist_dt* sl, ssize_t index, const char* format);

// prefixing

bool werks_stringlist_prefix_all(werks_stringlist_dt* sl, const char* prefix);
bool werks_stringlist_prefix(werks_stringlist_dt* sl, ssize_t index, const char* prefix);

// suffixing

bool werks_stringlist_suffix_all(werks_stringlist_dt* sl, const char* suffix);
bool werks_stringlist_suffix(werks_stringlist_dt* sl, ssize_t index, const char* suffix);

// separated-values

char* werks_stringlist_join(werks_stringlist_dt* sl, const char* separator);
werks_stringlist_dt* werks_stringlist_split(const char* value, const char* separator);
char* werks_stringlist_write_to_string(werks_stringlist_dt* sl, char separator);
bool werks_stringlist_read_from_string(werks_stringlist_dt* sl, const char* data, const char* separator);

// array

werks_stringlist_dt* werks_stringlist_from_array_with_size(const char** arr, ssize_t size);
werks_stringlist_dt* werks_stringlist_from_array_with_sentinel(const char** arr); // Create a new string list from a sentinel (NULL) terminated array with a copy (strdup) of all the values
const char** werks_stringlist_to_array_with_size(werks_stringlist_dt* sl, ssize_t* size);
const char** werks_stringlist_to_array_with_sentinel(werks_stringlist_dt* sl); // Create a new sentinel (NULL) terminated array with a copy (strdup) of all the values

// files

werks_stringlist_dt* werks_stringlist_load_from_file(const char* filename);
bool werks_stringlist_read_from_file(werks_stringlist_dt* sl, const char* filename);
bool werks_stringlist_save_to_file(werks_stringlist_dt* sl, const char* filename);
bool werks_stringlist_append_to_file(werks_stringlist_dt* sl, const char* filename);

typedef bool (*werks_stringlist_on_before_read_from_file_handler_fn)(werks_stringlist_dt* sl, const char* filename);
typedef bool (*werks_stringlist_on_before_write_to_file_handler_fn)(werks_stringlist_dt* sl, const char* filename);
void werks_stringlist_set_on_before_read_from_file(werks_stringlist_dt* sl, werks_stringlist_on_before_read_from_file_handler_fn handler);
werks_stringlist_on_before_read_from_file_handler_fn werks_stringlist_get_on_before_read_from_file(werks_stringlist_dt* sl);
void werks_stringlist_set_on_before_write_to_file(werks_stringlist_dt* sl, werks_stringlist_on_before_write_to_file_handler_fn handler);
werks_stringlist_on_before_write_to_file_handler_fn werks_stringlist_get_on_before_write_to_file(werks_stringlist_dt* sl);

// json

char* werks_stringlist_write_to_json_array_string(werks_stringlist_dt* sl);
bool werks_stringlist_read_from_json_array_string(werks_stringlist_dt* sl, const char* data);

#ifdef __cplusplus
}
#endif

