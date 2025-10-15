/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: PeRKS DBGMM
 * File: perks_dbgmm_callbacks-inc.h
 * Brief: part of PeRKS DBGMM
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifndef PERKS_DBGMM_POINTERS_ARRAY_INITIAL_CAPACITY
    #define PERKS_DBGMM_POINTERS_ARRAY_INITIAL_CAPACITY 1024
#endif

#ifndef PERKS_DBGMM_POINTERS_ARRAY_STRINGIFY_SEPARATOR
    #define PERKS_DBGMM_POINTERS_ARRAY_STRINGIFY_SEPARATOR '\n'
#endif

typedef void (*report_callback_fn)(size_t size, const char* stringified_pointers);
typedef void (*alloca_callback_fn)(size_t size, const char* file, int line, const char* func, void* new_ptr);
typedef void (*aligned_alloca_callback_fn)(size_t alignment, size_t size, const char* file, int line, const char* func, void* new_ptr);
typedef void (*malloc_success_callback_fn)(size_t size, const char* file, int line, const char* func, void* new_ptr);
typedef void (*malloc_failure_callback_fn)(size_t size, const char* file, int line, const char* func);
typedef void (*calloc_success_callback_fn)(size_t num, size_t size, const char* file, int line, const char* func, void* new_ptr);
typedef void (*calloc_failure_callback_fn)(size_t num, size_t size, const char* file, int line, const char* func);
#ifdef __c11
typedef void (*aligned_alloc_success_callback_fn)(size_t alignment, size_t size, const char* file, int line, const char* func, void* new_ptr);
typedef void (*aligned_alloc_failure_callback_fn)(size_t alignment, size_t size, const char* file, int line, const char* func);
#endif
typedef void (*realloc_success_callback_fn)(void* ptr, size_t size, const char* file, int line, const char* func, void* new_ptr);
typedef void (*realloc_failure_callback_fn)(void* ptr, size_t size, const char* file, int line, const char* func);
typedef void (*free_success_callback_fn)(void* ptr, const char* file, int line, const char* func);
typedef void (*free_failure_callback_fn)(const char* file, int line, const char* func);

#ifdef __cplusplus
}
#endif

