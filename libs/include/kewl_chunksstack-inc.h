/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_chunksstack-inc.h
 * Copyright (c) 2025-2026 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

/*
    This is a fixed-size memory chunks stack that grows when required.
*/

#ifndef KEWL_CHUNKSSTACK_ALIGNMENT
    #define KEWL_CHUNKSSTACK_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef KEWL_CHUNKSSTACK_GROW_FACTOR
    #define KEWL_CHUNKSSTACK_GROW_FACTOR 2.0f
#endif

#ifndef KEWL_CHUNKSSTACK_GROW_PADDING
    #define KEWL_CHUNKSSTACK_GROW_PADDING 0.0f
#endif

typedef struct kewl_chunksstack_dt kewl_chunksstack_dt;

kewl_chunksstack_dt* kewl_chunksstack_create(size_t initial_capacity, size_t chunk_size);
void kewl_chunksstack_destroy(kewl_chunksstack_dt* stack);

size_t kewl_chunksstack_get_capacity(kewl_chunksstack_dt* stack);
float kewl_chunksstack_get_capacity_grow_factor(kewl_chunksstack_dt* stack);
float kewl_chunksstack_get_capacity_grow_padding(kewl_chunksstack_dt* stack);
void kewl_chunksstack_set_capacity_grow_factor(kewl_chunksstack_dt* stack, float factor);
void kewl_chunksstack_set_capacity_grow_padding(kewl_chunksstack_dt* stack, float padding);
size_t kewl_chunksstack_get_chunks_count(kewl_chunksstack_dt* stack);
size_t kewl_chunksstack_get_chunk_size(kewl_chunksstack_dt* stack);
size_t kewl_chunksstack_get_buffer_size(kewl_chunksstack_dt* stack);
void* kewl_chunksstack_get_buffer_pointer(kewl_chunksstack_dt* stack);

bool kewl_chunksstack_push(kewl_chunksstack_dt* stack, const void* source);
bool kewl_chunksstack_pop(kewl_chunksstack_dt* stack, void* destination);

bool kewl_chunksstack_delete(kewl_chunksstack_dt* stack, size_t index);
void kewl_chunksstack_clear(kewl_chunksstack_dt* stack);
bool kewl_chunksstack_pack(kewl_chunksstack_dt* stack);

void* kewl_chunksstack_get(kewl_chunksstack_dt* stack, size_t index);
bool kewl_chunksstack_set(kewl_chunksstack_dt* stack, size_t index, const void* source);

typedef void (*kewl_chunksstack_callback_fn)(void* chunk, size_t index);
void kewl_chunksstack_loop(kewl_chunksstack_dt* stack, kewl_chunksstack_callback_fn cb);

typedef void (*kewl_chunksstack_callback_with_reference_fn)(void* chunk, size_t index, void* ref);
void kewl_chunksstack_loop_with_reference(kewl_chunksstack_dt* stack, kewl_chunksstack_callback_with_reference_fn cb, void* ref);

