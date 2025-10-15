/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: PeRKS DBGMM
 * File: perks_dbgmm.h
 * Brief: memory management debugging
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define KEWL_PTRHOLDER_PTRTYPE void*
#define KEWL_PTRHOLDER_STRFORMAT "%p%c"
#include "kewl.h"

#define PERKS_DBGMM

#include "perks_dbgmm_callbacks-inc.h"

void dbgmm_audit(void);
void dbgmm_deaudit(void);
long dbgmm_get_report_calls(void);
report_callback_fn dbgmm_get_report_callback(void);
void dbgmm_set_report_callback(report_callback_fn cb);
void dbgmm_report(void);

long dbgmm_get_alloca_calls(void);
alloca_callback_fn dbgmm_get_alloca_callback(void);
void dbgmm_set_alloca_callback(alloca_callback_fn cb);
void* dbgmm_fire_alloca_callback(size_t size, const char* file, int line, const char* func, void* new_ptr);
#ifdef alloca
    #undef alloca
#endif
#define alloca(X) dbgmm_fire_alloca_callback(X, __FILE__, __LINE__, __FUNCTION__, (void*)__builtin_alloca(X))

long dbgmm_get_aligned_alloca_calls(void);
aligned_alloca_callback_fn dbgmm_get_aligned_alloca_callback(void);
void dbgmm_set_aligned_alloca_callback(aligned_alloca_callback_fn cb);
void* dbgmm_fire_aligned_alloca_callback(size_t alignment, size_t size, const char* file, int line, const char* func, void* new_ptr);
#ifdef aligned_alloca
    #undef aligned_alloca
#endif
#define aligned_alloca(X, Y) dbgmm_fire_aligned_alloca_callback(X, Y, __FILE__, __LINE__, __FUNCTION__, (void*)__builtin_alloca_with_align(Y, X * CHAR_BIT))

long dbgmm_get_malloc_success_calls(void);
long dbgmm_get_malloc_failure_calls(void);
malloc_success_callback_fn dbgmm_get_malloc_success_callback(void);
malloc_failure_callback_fn dbgmm_get_malloc_failure_callback(void);
void dbgmm_set_malloc_success_callback(malloc_success_callback_fn cb);
void dbgmm_set_malloc_failure_callback(malloc_failure_callback_fn cb);
void* dbgmm_malloc(size_t size, const char* file, int line, const char* func);
#define malloc(X) dbgmm_malloc(X, __FILE__, __LINE__, __FUNCTION__)

long dbgmm_get_calloc_success_calls(void);
long dbgmm_get_calloc_failure_calls(void);
calloc_success_callback_fn dbgmm_get_calloc_success_callback(void);
calloc_failure_callback_fn dbgmm_get_calloc_failure_callback(void);
void dbgmm_set_calloc_success_callback(calloc_success_callback_fn cb);
void dbgmm_set_calloc_failure_callback(calloc_failure_callback_fn cb);
void* dbgmm_calloc(size_t num, size_t size, const char* file, int line, const char* func);
#define calloc(X, Y) dbgmm_calloc(X, Y, __FILE__, __LINE__, __FUNCTION__)

#ifdef __c11
long dbgmm_get_aligned_alloc_success_calls(void);
long dbgmm_get_aligned_alloc_failure_calls(void);
aligned_alloc_success_callback_fn dbgmm_get_aligned_alloc_success_callback(void);
aligned_alloc_failure_callback_fn dbgmm_get_aligned_alloc_failure_callback(void);
void dbgmm_set_aligned_alloc_success_callback(aligned_alloc_success_callback_fn cb);
void dbgmm_set_aligned_alloc_failure_callback(aligned_alloc_failure_callback_fn cb);
void* dbgmm_aligned_alloc(size_t alignment, size_t size, const char* file, int line, const char* func);
#define aligned_alloc(X, Y) dbgmm_aligned_alloc(X, Y, __FILE__, __LINE__, __FUNCTION__)
#endif

long dbgmm_get_realloc_success_calls(void);
long dbgmm_get_realloc_failure_calls(void);
realloc_success_callback_fn dbgmm_get_realloc_success_callback(void);
realloc_failure_callback_fn dbgmm_get_realloc_failure_callback(void);
void dbgmm_set_realloc_success_callback(realloc_success_callback_fn cb);
void dbgmm_set_realloc_failure_callback(realloc_failure_callback_fn cb);
void* dbgmm_realloc(void* ptr, size_t size, const char* file, int line, const char* func);
#define realloc(X, Y) dbgmm_realloc(X, Y, __FILE__, __LINE__, __FUNCTION__)

long dbgmm_get_free_success_calls(void);
long dbgmm_get_free_failure_calls(void);
free_success_callback_fn dbgmm_get_free_success_callback(void);
free_failure_callback_fn dbgmm_get_free_failure_callback(void);
void dbgmm_set_free_success_callback(free_success_callback_fn cb);
void dbgmm_set_free_failure_callback(free_failure_callback_fn cb);
void dbgmm_free(void* ptr, const char* file, int line, const char* func);
#define free(X) dbgmm_free(X, __FILE__, __LINE__, __FUNCTION__)

#ifdef __cplusplus
}
#endif

