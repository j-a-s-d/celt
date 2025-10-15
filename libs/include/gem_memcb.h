/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: GeM MEMCB
 * File: gem_memcb.h
 * Brief: nemory callback for gcc/clang
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "ce.h"

#define GeM_MEMCB

// NOTE: GeM Memory Callback requires the BlocksRuntime library to compile under clang

/* GeM.MEMCB -- Memory Callback */

// Callback definition
#if defined(__clang__)

typedef void (^memcb_fn)(void *ptr);

#else

typedef void (*memcb_fn)(void* ptr);

#endif

// Callback proxy to call functions (only useful in clang)
#if defined(__clang__)

#define memcb_proxy(callback) ^(void* mem) { callback(mem); }

#else

#define memcb_proxy(callback) callback

#endif

#include <stdlib.h>

// Function to allocate memory of given size and to call the callback if allocation succeeds
static inline void memcallback(size_t size, memcb_fn callback) {
    if (callback == NULL) return;
    void* ptr = ce_malloc(size);
    if (ptr == NULL) return;
    callback(ptr);
    ce_free(ptr);
}

// Memory callback macros
#if defined(__clang__)

#define MEMCB(size, param_name, code_block) \
    void (^LINE_UNIQUE_NAME(memcb_handler_))(void*) = ^(void* param_name) { code_block; }; \
    memcallback(size, LINE_UNIQUE_NAME(memcb_handler_))

#define MEMCB_TYPED(size, param_type, param_name, code_block) \
    void (^LINE_UNIQUE_NAME(memcb_handler_))(void*) = ^(void* ptr) { param_type param_name = (param_type)(ptr); code_block; }; \
    memcallback(size, LINE_UNIQUE_NAME(memcb_handler_))

#define MEMCB_STRUCT(struct_type, param_name, code_block) \
    void (^LINE_UNIQUE_NAME(memcb_handler_))(void*) = ^(void* ptr) { struct_type* param_name = (struct_type*)(ptr); code_block; }; \
    memcallback(sizeof(struct_type), LINE_UNIQUE_NAME(memcb_handler_))

#else

#define MEMCB(size, param_name, code_block) \
    void LINE_UNIQUE_NAME(memcb_handler_)(void* param_name) { code_block; } \
    memcallback(size, LINE_UNIQUE_NAME(memcb_handler_))

#define MEMCB_TYPED(size, param_type, param_name, code_block) \
    void LINE_UNIQUE_NAME(memcb_handler_)(void* ptr) { param_type param_name = (param_type)(ptr); code_block; } \
    memcallback(size, LINE_UNIQUE_NAME(memcb_handler_))

#define MEMCB_STRUCT(struct_type, param_name, code_block) \
    void LINE_UNIQUE_NAME(memcb_handler_)(void* ptr) { struct_type* param_name = (struct_type*)(ptr); code_block; } \
    memcallback(sizeof(struct_type), LINE_UNIQUE_NAME(memcb_handler_))

#endif

#ifdef __cplusplus
}
#endif

