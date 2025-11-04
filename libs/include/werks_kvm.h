/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: WeRKS KVM
 * File: werks_kvm.h
 * Brief: general-purpose key-value map
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*
    This general-purpose key-value map holds internally a structure of arrays (SoA) for better cache
    locality, improved iteration speed, fast serialization/deserialization, etc.
    It maps all the native c99 types plus strings (char*), buffers (where custom structs can be stored),
    and other kvms (allowing nested maps), with getters and setters for every type plus copying every
    value you set (to ensure full ownership).
    It has a soft/lazy/deferred-delete strategy for maximum performance while allowing empty slots
    reusage and letting the user decide when to perform the compaction (if required at all).
    It also features numerous global permission flags (set, retype, delete, pack, persistence, etc).
    To make fetching data easier, accessors (getters) support nested paths (other functions do not).
*/

#include "kewl.h"

#define WERKS_KVM

#define WERKS_KVM_TYPE_NAME "werks_kvm_dt"

#ifndef WERKS_KVM_INITIAL_CAPACITY
    #define WERKS_KVM_INITIAL_CAPACITY 128
#endif

#ifndef WERKS_KVM_ALIGNMENT
    #define WERKS_KVM_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef WERKS_KVM_KEY_MAX_LEN
    #define WERKS_KVM_KEY_MAX_LEN 256
#endif

#ifndef WERKS_KVM_KEY_XPATH_SEPARATOR
    #define WERKS_KVM_KEY_XPATH_SEPARATOR STRINGS_BACKSLASH
#endif

#ifndef WERKS_KVM_KEYVALUE_SEPARATOR
    #define WERKS_KVM_KEYVALUE_SEPARATOR STRINGS_EQUAL
#endif

#ifndef WERKS_KVM_ITEMS_SEPARATOR
    #define WERKS_KVM_ITEMS_SEPARATOR STRINGS_LF
#endif

#ifndef WERKS_KVM_MULTILINE_STRINGS_EOL
    #define WERKS_KVM_MULTILINE_STRINGS_EOL "\\n"
#endif

#ifndef WERKS_KVM_GROW_FACTOR
    #define WERKS_KVM_GROW_FACTOR 2.0f
#endif

#ifndef WERKS_KVM_GROW_PADDING
    #define WERKS_KVM_GROW_PADDING 0.0f
#endif

typedef struct werks_kvm_dt werks_kvm_dt;

typedef enum {
    WERKS_KVM_TYPE_NOTHING = 0,
    WERKS_KVM_TYPE_KVM = 1, // KVM type

    WERKS_KVM_TYPE_BUFFER = 10, // void*

    // char types
    WERKS_KVM_TYPE_CHAR = 20,
    WERKS_KVM_TYPE_SIGNED_CHAR,
    WERKS_KVM_TYPE_UNSIGNED_CHAR,
    WERKS_KVM_TYPE_STRING,

    // floating-point types
    WERKS_KVM_TYPE_FLOAT = 30,
    WERKS_KVM_TYPE_DOUBLE,
    WERKS_KVM_TYPE_LONG_DOUBLE,

    // integer types
    WERKS_KVM_TYPE_SHORT = 40,
    WERKS_KVM_TYPE_UNSIGNED_SHORT,
    WERKS_KVM_TYPE_INT,
    WERKS_KVM_TYPE_UNSIGNED_INT,
    WERKS_KVM_TYPE_LONG,
    WERKS_KVM_TYPE_UNSIGNED_LONG,
    WERKS_KVM_TYPE_LONG_LONG, // c99
    WERKS_KVM_TYPE_UNSIGNED_LONG_LONG, // c99

    // fixed-width integer types (from stdint.h since c99)
    WERKS_KVM_TYPE_INT8 = 50,
    WERKS_KVM_TYPE_UINT8,
    WERKS_KVM_TYPE_INT16,
    WERKS_KVM_TYPE_UINT16,
    WERKS_KVM_TYPE_INT32,
    WERKS_KVM_TYPE_UINT32,
    WERKS_KVM_TYPE_INT64,
    WERKS_KVM_TYPE_UINT64,

    // boolean type (from stdbool.h since c99 & type since c23)
    WERKS_KVM_TYPE_BOOL = 60
} werks_kvm_type_dt;

// life-cycle

werks_kvm_dt* werks_kvm_create(ssize_t initial_capacity);
static inline werks_kvm_dt* werks_kvm_make(void) {
    return werks_kvm_create(WERKS_KVM_INITIAL_CAPACITY);
}
werks_kvm_dt* werks_kvm_clone(werks_kvm_dt* map);
void werks_kvm_destroy(werks_kvm_dt* map);
const kewl_component_dt* werks_kvm_get_component(werks_kvm_dt* map);

// dimensions

ssize_t werks_kvm_get_size(werks_kvm_dt* map);
ssize_t werks_kvm_get_capacity(werks_kvm_dt* map);
float werks_kvm_get_capacity_grow_factor(werks_kvm_dt* map);
float werks_kvm_get_capacity_grow_padding(werks_kvm_dt* map);
void werks_kvm_set_capacity_grow_factor(werks_kvm_dt* map, float factor);
void werks_kvm_set_capacity_grow_padding(werks_kvm_dt* map, float padding);
bool werks_kvm_is_packable(werks_kvm_dt* map);
bool werks_kvm_pack(werks_kvm_dt* map);

// copy

bool werks_kvm_read_items(werks_kvm_dt* map, werks_kvm_dt* source_map);
bool werks_kvm_copy_item(werks_kvm_dt* map, const char* key, werks_kvm_dt* destination_map, const char* destination_key);
bool werks_kvm_copy_typed_items(werks_kvm_dt* map, werks_kvm_type_dt type, werks_kvm_dt* destination_map);
bool werks_kvm_copy_not_typed_items(werks_kvm_dt* map, werks_kvm_type_dt type, werks_kvm_dt* destination_map);
bool werks_kvm_copy_prefixed_items(werks_kvm_dt* map, const char* prefix, werks_kvm_dt* destination_map);
bool werks_kvm_copy_not_prefixed_items(werks_kvm_dt* map, const char* prefix, werks_kvm_dt* destination_map);
bool werks_kvm_copy_suffixed_items(werks_kvm_dt* map, const char* suffix, werks_kvm_dt* destination_map);
bool werks_kvm_copy_not_suffixed_items(werks_kvm_dt* map, const char* suffix, werks_kvm_dt* destination_map);
bool werks_kvm_include_items(werks_kvm_dt* map, werks_kvm_dt* source_map);

// transfer

bool werks_kvm_transfer_item(werks_kvm_dt* map, const char* key, werks_kvm_dt* destination_map, const char* destination_key);
bool werks_kvm_transfer_typed_items(werks_kvm_dt* map, werks_kvm_type_dt type, werks_kvm_dt* destination_map);
bool werks_kvm_transfer_not_typed_items(werks_kvm_dt* map, werks_kvm_type_dt type, werks_kvm_dt* destination_map);
bool werks_kvm_transfer_prefixed_items(werks_kvm_dt* map, const char* prefix, werks_kvm_dt* destination_map);
bool werks_kvm_transfer_not_prefixed_items(werks_kvm_dt* map, const char* prefix, werks_kvm_dt* destination_map);
bool werks_kvm_transfer_suffixed_items(werks_kvm_dt* map, const char* suffix, werks_kvm_dt* destination_map);
bool werks_kvm_transfer_not_suffixed_items(werks_kvm_dt* map, const char* suffix, werks_kvm_dt* destination_map);

// deletion

void werks_kvm_clear(werks_kvm_dt* map);
bool werks_kvm_delete_item(werks_kvm_dt* map, const char* key);
bool werks_kvm_delete_typed_items(werks_kvm_dt* map, werks_kvm_type_dt t);
bool werks_kvm_delete_not_typed_items(werks_kvm_dt* map, werks_kvm_type_dt t);
bool werks_kvm_delete_prefixed_items(werks_kvm_dt* map, const char* prefix);
bool werks_kvm_delete_not_prefixed_items(werks_kvm_dt* map, const char* prefix);
bool werks_kvm_delete_suffixed_items(werks_kvm_dt* map, const char* suffix);
bool werks_kvm_delete_not_suffixed_items(werks_kvm_dt* map, const char* suffix);
bool werks_kvm_exclude_items_of(werks_kvm_dt* map, werks_kvm_dt* source_map);
bool werks_kvm_exclude_typed_items_of(werks_kvm_dt* map, werks_kvm_dt* source_map);
bool werks_kvm_keep_items_of(werks_kvm_dt* map, werks_kvm_dt* source_map);
bool werks_kvm_keep_typed_items_of(werks_kvm_dt* map, werks_kvm_dt* source_map);

// keys

bool werks_kvm_rename_item(werks_kvm_dt* map, const char* key, const char* new_key);
bool werks_kvm_prefix_keys(werks_kvm_dt* map, const char* prefix);
bool werks_kvm_suffix_keys(werks_kvm_dt* map, const char* suffix);
bool werks_kvm_unprefix_keys(werks_kvm_dt* map, const char* prefix);
bool werks_kvm_unsuffix_keys(werks_kvm_dt* map, const char* suffix);
char* werks_kvm_get_joined_keys(werks_kvm_dt* map, const char* separator);

// inspection

bool werks_kvm_has_item(werks_kvm_dt* map, const char* key);
bool werks_kvm_has_typed_item(werks_kvm_dt* map, const char* key, werks_kvm_type_dt type);
bool werks_kvm_has_items_typed(werks_kvm_dt* map, werks_kvm_type_dt type);
bool werks_kvm_has_items_not_typed(werks_kvm_dt* map, werks_kvm_type_dt type);
bool werks_kvm_has_items_prefixed(werks_kvm_dt* map, const char* prefix);
bool werks_kvm_has_items_not_prefixed(werks_kvm_dt* map, const char* prefix);
bool werks_kvm_has_items_suffixed(werks_kvm_dt* map, const char* suffix);
bool werks_kvm_has_items_not_suffixed(werks_kvm_dt* map, const char* suffix);
ssize_t werks_kvm_count_typed_items(werks_kvm_dt* map, werks_kvm_type_dt type);
ssize_t werks_kvm_count_not_typed_items(werks_kvm_dt* map, werks_kvm_type_dt type);
ssize_t werks_kvm_count_prefixed_items(werks_kvm_dt* map, const char* prefix);
ssize_t werks_kvm_count_not_prefixed_items(werks_kvm_dt* map, const char* prefix);
ssize_t werks_kvm_count_suffixed_items(werks_kvm_dt* map, const char* suffix);
ssize_t werks_kvm_count_not_suffixed_items(werks_kvm_dt* map, const char* suffix);
ssize_t werks_kvm_get_items_count(werks_kvm_dt* map);
werks_kvm_type_dt werks_kvm_get_item_type(werks_kvm_dt* map, const char* key);
char* werks_kvm_render_value_as_string(werks_kvm_dt* map, const char* key);

// comparison

bool werks_kvm_same_keys(werks_kvm_dt* map, werks_kvm_dt* map2);
bool werks_kvm_same_typed_keys(werks_kvm_dt* map, werks_kvm_dt* map2);
bool werks_kvm_contains_all_keys_of(werks_kvm_dt* map, werks_kvm_dt* map2);
bool werks_kvm_contains_all_typed_keys_of(werks_kvm_dt* map, werks_kvm_dt* map2);

// nesting

bool werks_kvm_is_top(werks_kvm_dt* map);
werks_kvm_dt* werks_kvm_get_parent(werks_kvm_dt* map);
bool werks_kvm_filiate_to(werks_kvm_dt* map, werks_kvm_dt* new_parent, const char* as_key);

// permission flags

void werks_kvm_enable_set(werks_kvm_dt* map);
void werks_kvm_disable_set(werks_kvm_dt* map);
bool werks_kvm_is_set_allowed(werks_kvm_dt* map);

void werks_kvm_enable_retype(werks_kvm_dt* map);
void werks_kvm_disable_retype(werks_kvm_dt* map);
bool werks_kvm_is_retype_allowed(werks_kvm_dt* map);

void werks_kvm_enable_rename(werks_kvm_dt* map);
void werks_kvm_disable_rename(werks_kvm_dt* map);
bool werks_kvm_is_rename_allowed(werks_kvm_dt* map);

void werks_kvm_enable_delete(werks_kvm_dt* map);
void werks_kvm_disable_delete(werks_kvm_dt* map);
bool werks_kvm_is_delete_allowed(werks_kvm_dt* map);

void werks_kvm_enable_transfer(werks_kvm_dt* map);
void werks_kvm_disable_transfer(werks_kvm_dt* map);
bool werks_kvm_is_transfer_allowed(werks_kvm_dt* map);

void werks_kvm_enable_copy(werks_kvm_dt* map);
void werks_kvm_disable_copy(werks_kvm_dt* map);
bool werks_kvm_is_copy_allowed(werks_kvm_dt* map);

void werks_kvm_enable_pack(werks_kvm_dt* map);
void werks_kvm_disable_pack(werks_kvm_dt* map);
bool werks_kvm_is_pack_allowed(werks_kvm_dt* map);

void werks_kvm_enable_loop(werks_kvm_dt* map);
void werks_kvm_disable_loop(werks_kvm_dt* map);
bool werks_kvm_is_loop_allowed(werks_kvm_dt* map);

void werks_kvm_enable_persistence(werks_kvm_dt* map);
void werks_kvm_disable_persistence(werks_kvm_dt* map);
bool werks_kvm_is_persistence_allowed(werks_kvm_dt* map);

void werks_kvm_enable_events(werks_kvm_dt* map);
void werks_kvm_disable_events(werks_kvm_dt* map);
bool werks_kvm_are_events_allowed(werks_kvm_dt* map);

// setters (that copies the data passed to take ownership) return true on success, false on failure

bool werks_kvm_set_char(werks_kvm_dt* map, const char* key, char value);
bool werks_kvm_set_signed_char(werks_kvm_dt* map, const char* key, signed char value);
bool werks_kvm_set_unsigned_char(werks_kvm_dt* map, const char* key, unsigned char value);
bool werks_kvm_set_short(werks_kvm_dt* map, const char* key, short value);
bool werks_kvm_set_unsigned_short(werks_kvm_dt* map, const char* key, unsigned short value);
bool werks_kvm_set_int(werks_kvm_dt* map, const char* key, int value);
bool werks_kvm_set_unsigned_int(werks_kvm_dt* map, const char* key, unsigned int value);
bool werks_kvm_set_long(werks_kvm_dt* map, const char* key, long value);
bool werks_kvm_set_unsigned_long(werks_kvm_dt* map, const char* key, unsigned long value);
bool werks_kvm_set_long_long(werks_kvm_dt* map, const char* key, long long value);
bool werks_kvm_set_unsigned_long_long(werks_kvm_dt* map, const char* key, unsigned long long value);
bool werks_kvm_set_float(werks_kvm_dt* map, const char* key, float value);
bool werks_kvm_set_double(werks_kvm_dt* map, const char* key, double value);
bool werks_kvm_set_long_double(werks_kvm_dt* map, const char* key, long double value);
bool werks_kvm_set_bool(werks_kvm_dt* map, const char* key, bool value);
bool werks_kvm_set_string(werks_kvm_dt* map, const char* key, const char* value);
bool werks_kvm_set_buffer(werks_kvm_dt* map, const char* key, const void* data, ssize_t size);
bool werks_kvm_set_int8(werks_kvm_dt* map, const char* key, int8_t value);
bool werks_kvm_set_uint8(werks_kvm_dt* map, const char* key, uint8_t value);
bool werks_kvm_set_int16(werks_kvm_dt* map, const char* key, int16_t value);
bool werks_kvm_set_uint16(werks_kvm_dt* map, const char* key, uint16_t value);
bool werks_kvm_set_int32(werks_kvm_dt* map, const char* key, int32_t value);
bool werks_kvm_set_uint32(werks_kvm_dt* map, const char* key, uint32_t value);
bool werks_kvm_set_int64(werks_kvm_dt* map, const char* key, int64_t value);
bool werks_kvm_set_uint64(werks_kvm_dt* map, const char* key, uint64_t value);
bool werks_kvm_set_kvm(werks_kvm_dt* map, const char* key);

// getters return pointer to stored data or NULL if not found

char* werks_kvm_get_char(werks_kvm_dt* map, const char* key);
signed char* werks_kvm_get_signed_char(werks_kvm_dt* map, const char* key);
unsigned char* werks_kvm_get_unsigned_char(werks_kvm_dt* map, const char* key);
short* werks_kvm_get_short(werks_kvm_dt* map, const char* key);
unsigned short* werks_kvm_get_unsigned_short(werks_kvm_dt* map, const char* key);
int* werks_kvm_get_int(werks_kvm_dt* map, const char* key);
unsigned int* werks_kvm_get_unsigned_int(werks_kvm_dt* map, const char* key);
long* werks_kvm_get_long(werks_kvm_dt* map, const char* key);
unsigned long* werks_kvm_get_unsigned_long(werks_kvm_dt* map, const char* key);
long long* werks_kvm_get_long_long(werks_kvm_dt* map, const char* key);
unsigned long long* werks_kvm_get_unsigned_long_long(werks_kvm_dt* map, const char* key);
float* werks_kvm_get_float(werks_kvm_dt* map, const char* key);
double* werks_kvm_get_double(werks_kvm_dt* map, const char* key);
long double* werks_kvm_get_long_double(werks_kvm_dt* map, const char* key);
bool* werks_kvm_get_bool(werks_kvm_dt* map, const char* key);
char* werks_kvm_get_string(werks_kvm_dt* map, const char* key);
void* werks_kvm_get_buffer_pointer(werks_kvm_dt* map, const char* key);
ssize_t werks_kvm_get_buffer_size(werks_kvm_dt* map, const char* key);
int8_t* werks_kvm_get_int8(werks_kvm_dt* map, const char* key);
uint8_t* werks_kvm_get_uint8(werks_kvm_dt* map, const char* key);
int16_t* werks_kvm_get_int16(werks_kvm_dt* map, const char* key);
uint16_t* werks_kvm_get_uint16(werks_kvm_dt* map, const char* key);
int32_t* werks_kvm_get_int32(werks_kvm_dt* map, const char* key);
uint32_t* werks_kvm_get_uint32(werks_kvm_dt* map, const char* key);
int64_t* werks_kvm_get_int64(werks_kvm_dt* map, const char* key);
uint64_t* werks_kvm_get_uint64(werks_kvm_dt* map, const char* key);
werks_kvm_dt* werks_kvm_get_kvm(werks_kvm_dt* map, const char* key);

#define werks_kvm_get_value(map, typ, nam, def) ({ \
    if (map == NULL) return def; \
    typ* tmp = werks_kvm_get_##typ(map, nam); \
    assigned(tmp) ? *tmp : def; \
})

// iteration

typedef void (*werks_kvm_callback_fn)(werks_kvm_type_dt type, char* key, void* data);
void werks_kvm_loop_items(werks_kvm_dt* map, werks_kvm_callback_fn cb);
void werks_kvm_loop_typed_items(werks_kvm_dt* map, werks_kvm_type_dt t, werks_kvm_callback_fn cb);
void werks_kvm_loop_not_typed_items(werks_kvm_dt* map, werks_kvm_type_dt t, werks_kvm_callback_fn cb);
void werks_kvm_loop_prefixed_items(werks_kvm_dt* map, const char* prefix, werks_kvm_callback_fn cb);
void werks_kvm_loop_not_prefixed_items(werks_kvm_dt* map, const char* prefix, werks_kvm_callback_fn cb);
void werks_kvm_loop_suffixed_items(werks_kvm_dt* map, const char* suffix, werks_kvm_callback_fn cb);
void werks_kvm_loop_not_suffixed_items(werks_kvm_dt* map, const char* suffix, werks_kvm_callback_fn cb);

typedef void (*werks_kvm_callback_with_reference_fn)(werks_kvm_type_dt type, char* key, void* data, void* reference);
void werks_kvm_loop_items_with_reference(werks_kvm_dt* map, werks_kvm_callback_with_reference_fn cb, void* reference);
void werks_kvm_loop_typed_items_with_reference(werks_kvm_dt* map, werks_kvm_type_dt t, werks_kvm_callback_with_reference_fn cb, void* reference);
void werks_kvm_loop_not_typed_items_with_reference(werks_kvm_dt* map, werks_kvm_type_dt t, werks_kvm_callback_with_reference_fn cb, void* reference);
void werks_kvm_loop_prefixed_items_with_reference(werks_kvm_dt* map, const char* prefix, werks_kvm_callback_with_reference_fn cb, void* reference);
void werks_kvm_loop_not_prefixed_items_with_reference(werks_kvm_dt* map, const char* prefix, werks_kvm_callback_with_reference_fn cb, void* reference);
void werks_kvm_loop_suffixed_items_with_reference(werks_kvm_dt* map, const char* suffix, werks_kvm_callback_with_reference_fn cb, void* reference);
void werks_kvm_loop_not_suffixed_items_with_reference(werks_kvm_dt* map, const char* suffix, werks_kvm_callback_with_reference_fn cb, void* reference);

// array

const char** werks_kvm_keys_to_array_with_size(werks_kvm_dt* map, ssize_t* size);
const char** werks_kvm_keys_to_array_with_sentinel(werks_kvm_dt* map);
char** werks_kvm_get_keys_as_sorted_array_with_size(werks_kvm_dt* map, ssize_t* size);
char** werks_kvm_get_keys_as_sorted_array_with_sentinel(werks_kvm_dt* map);

// persistence

const char* werks_kvm_get_eol_replacement(werks_kvm_dt* map);
void werks_kvm_set_eol_replacement(werks_kvm_dt* map, const char* eol);

char* werks_kvm_save_to_string(werks_kvm_dt* map);
bool werks_kvm_read_from_string(werks_kvm_dt* map, const char* props);
werks_kvm_dt* werks_kvm_load_from_string(const char* props);

bool werks_kvm_save_to_file(werks_kvm_dt* map, const char* filename);
bool werks_kvm_append_to_file(werks_kvm_dt* map, const char* filename);
bool werks_kvm_read_from_file(werks_kvm_dt* map, const char* filename);
werks_kvm_dt* werks_kvm_load_from_file(const char* filename);

// events

typedef bool (*werks_kvm_on_before_read_from_file_handler_fn)(werks_kvm_dt* map, const char* filename);
void werks_kvm_set_on_before_read_from_file(werks_kvm_dt* map, werks_kvm_on_before_read_from_file_handler_fn handler);
werks_kvm_on_before_read_from_file_handler_fn werks_kvm_get_on_before_read_from_file(werks_kvm_dt* map);

typedef bool (*werks_kvm_on_before_write_to_file_handler_fn)(werks_kvm_dt* map, const char* filename);
void werks_kvm_set_on_before_write_to_file(werks_kvm_dt* map, werks_kvm_on_before_write_to_file_handler_fn handler);
werks_kvm_on_before_write_to_file_handler_fn werks_kvm_get_on_before_write_to_file(werks_kvm_dt* map);

typedef bool (*werks_kvm_on_before_read_from_string_handler_fn)(werks_kvm_dt* map, const char* props);
void werks_kvm_set_on_before_read_from_string(werks_kvm_dt* map, werks_kvm_on_before_read_from_string_handler_fn handler);
werks_kvm_on_before_read_from_string_handler_fn werks_kvm_get_on_before_read_from_string(werks_kvm_dt* map);

typedef bool (*werks_kvm_on_before_write_to_string_handler_fn)(werks_kvm_dt* map);
void werks_kvm_set_on_before_write_to_string(werks_kvm_dt* map, werks_kvm_on_before_write_to_string_handler_fn handler);
werks_kvm_on_before_write_to_string_handler_fn werks_kvm_get_on_before_write_to_string(werks_kvm_dt* map);

typedef bool (*werks_kvm_on_before_store_item_handler_fn)(werks_kvm_dt* map, const char* key, werks_kvm_type_dt type, void* value);
void werks_kvm_set_on_before_store_item(werks_kvm_dt* map, werks_kvm_on_before_store_item_handler_fn handler);
werks_kvm_on_before_store_item_handler_fn werks_kvm_get_on_before_store_item(werks_kvm_dt* map);

typedef bool (*werks_kvm_on_before_rename_item_handler_fn)(werks_kvm_dt* map, const char* key, const char* new_key);
void werks_kvm_set_on_before_rename_item(werks_kvm_dt* map, werks_kvm_on_before_rename_item_handler_fn handler);
werks_kvm_on_before_rename_item_handler_fn werks_kvm_get_on_before_rename_item(werks_kvm_dt* map);

typedef bool (*werks_kvm_on_before_delete_item_handler_fn)(werks_kvm_dt* map, const char* key);
void werks_kvm_set_on_before_delete_item(werks_kvm_dt* map, werks_kvm_on_before_delete_item_handler_fn handler);
werks_kvm_on_before_delete_item_handler_fn werks_kvm_get_on_before_delete_item(werks_kvm_dt* map);

typedef bool (*werks_kvm_on_before_transfer_item_handler_fn)(werks_kvm_dt* map, const char* key, werks_kvm_dt* destination_map, const char* destination_key);
void werks_kvm_set_on_before_transfer_item(werks_kvm_dt* map, werks_kvm_on_before_transfer_item_handler_fn handler);
werks_kvm_on_before_transfer_item_handler_fn werks_kvm_get_on_before_transfer_item(werks_kvm_dt* map);

typedef bool (*werks_kvm_on_before_copy_item_handler_fn)(werks_kvm_dt* map, const char* key, werks_kvm_dt* destination_map, const char* destination_key);
void werks_kvm_set_on_before_copy_item(werks_kvm_dt* map, werks_kvm_on_before_copy_item_handler_fn handler);
werks_kvm_on_before_copy_item_handler_fn werks_kvm_get_on_before_copy_item(werks_kvm_dt* map);

// utilities

char* werks_kvm_export_to_json_object_string(werks_kvm_dt* map);
char* werks_kvm_get_type_name(const werks_kvm_type_dt t);
werks_kvm_type_dt werks_kvm_get_type_by_name(const char* n);

#ifdef __cplusplus
}
#endif

