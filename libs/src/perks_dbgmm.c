/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: PeRKS DBGMM
 * File: perks_dbgmm.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "kewl.h"
#include "perks_dbgmm_callbacks-inc.h"

unit_internal({ kewl_ptrholder_dt* dbgmm_pointers; }) = {NULL};

#define MAKE_FIELDS(name) \
    static CONCAT(name, _callback_fn) CONCAT(CONCAT(dbgmm_, name), _cb) = NULL; \
    static long CONCAT(CONCAT(dbgmm_, name), _counter) = 0
MAKE_FIELDS(report);
MAKE_FIELDS(alloca);
MAKE_FIELDS(aligned_alloca);
MAKE_FIELDS(malloc_success);
MAKE_FIELDS(malloc_failure);
MAKE_FIELDS(calloc_success);
MAKE_FIELDS(calloc_failure);
#ifdef __c11
MAKE_FIELDS(aligned_alloc_success);
MAKE_FIELDS(aligned_alloc_failure);
#endif
MAKE_FIELDS(realloc_success);
MAKE_FIELDS(realloc_failure);
MAKE_FIELDS(free_success);
MAKE_FIELDS(free_failure);
#undef MAKE_FIELDS

// AUDITING AND REPORTING

void dbgmm_audit(void) {
    if (internal_.dbgmm_pointers == NULL)
        internal_.dbgmm_pointers = kewl_ptrholder_create(PERKS_DBGMM_POINTERS_ARRAY_INITIAL_CAPACITY);
}

void dbgmm_deaudit(void) {
    if (assigned(internal_.dbgmm_pointers)) {
        kewl_ptrholder_destroy(internal_.dbgmm_pointers);
        internal_.dbgmm_pointers = NULL;
    }
}

long dbgmm_get_report_calls(void) {
    return dbgmm_report_counter;
}

report_callback_fn dbgmm_get_report_callback(void) {
    return dbgmm_report_cb;
}

void dbgmm_set_report_callback(report_callback_fn cb) {
    dbgmm_report_cb = cb;
}

void dbgmm_report(void) {
    if (assigned(internal_.dbgmm_pointers)) {
        dbgmm_report_counter++;
        AUTO_STRING(str, kewl_ptrholder_stringify(internal_.dbgmm_pointers, PERKS_DBGMM_POINTERS_ARRAY_STRINGIFY_SEPARATOR));
        safe_call(dbgmm_report_cb,
            kewl_ptrholder_get_size(internal_.dbgmm_pointers),
            str
        );
    }
}

// ALLOCA

long dbgmm_get_alloca_calls(void) {
    return dbgmm_alloca_counter;
}

alloca_callback_fn dbgmm_get_alloca_callback(void) {
    return dbgmm_alloca_cb;
}

void dbgmm_set_alloca_callback(alloca_callback_fn cb) {
    dbgmm_alloca_cb = cb;
}

void* dbgmm_fire_alloca_callback(size_t size, const char* file, int line, const char* func, void* new_ptr) {
    dbgmm_alloca_counter++;
    safe_call(dbgmm_alloca_cb, size, file, line, func, new_ptr);
    return new_ptr;
}

// ALIGNED_ALLOCA

long dbgmm_get_aligned_alloca_calls(void) {
    return dbgmm_aligned_alloca_counter;
}

aligned_alloca_callback_fn dbgmm_get_aligned_alloca_callback(void) {
    return dbgmm_aligned_alloca_cb;
}

void dbgmm_set_aligned_alloca_callback(aligned_alloca_callback_fn cb) {
    dbgmm_aligned_alloca_cb = cb;
}

void* dbgmm_fire_aligned_alloca_callback(size_t alignment, size_t size, const char* file, int line, const char* func, void* new_ptr) {
    dbgmm_aligned_alloca_counter++;
    safe_call(dbgmm_aligned_alloca_cb, alignment, size, file, line, func, new_ptr);
    return new_ptr;
}

// MALLOC

long dbgmm_get_malloc_success_calls(void) {
    return dbgmm_malloc_success_counter;
}

long dbgmm_get_malloc_failure_calls(void) {
    return dbgmm_malloc_failure_counter;
}

malloc_success_callback_fn dbgmm_get_malloc_success_callback(void) {
    return dbgmm_malloc_success_cb;
}

malloc_failure_callback_fn dbgmm_get_malloc_failure_callback(void) {
    return dbgmm_malloc_failure_cb;
}

void dbgmm_set_malloc_success_callback(malloc_success_callback_fn cb) {
    dbgmm_malloc_success_cb = cb;
}

void dbgmm_set_malloc_failure_callback(malloc_failure_callback_fn cb) {
    dbgmm_malloc_failure_cb = cb;
}

void* dbgmm_malloc(size_t size, const char* file, int line, const char* func) {
    void* p = ce_malloc(size);
    if (p == NULL) {
        dbgmm_malloc_failure_counter++;
        safe_call(dbgmm_malloc_failure_cb, size, file, line, func);
    } else {
        dbgmm_malloc_success_counter++;
        safe_call(dbgmm_malloc_success_cb, size, file, line, func, p);
    }
    if (assigned(internal_.dbgmm_pointers))
        UNUSED(kewl_ptrholder_add(internal_.dbgmm_pointers, (kewl_ptrholder_ptr_dt)p));
    return p;
}

// CALLOC

long dbgmm_get_calloc_success_calls(void) {
    return dbgmm_calloc_success_counter;
}

long dbgmm_get_calloc_failure_calls(void) {
    return dbgmm_calloc_failure_counter;
}

calloc_success_callback_fn dbgmm_get_calloc_success_callback(void) {
    return dbgmm_calloc_success_cb;
}

calloc_failure_callback_fn dbgmm_get_calloc_failure_callback(void) {
    return dbgmm_calloc_failure_cb;
}

void dbgmm_set_calloc_success_callback(calloc_success_callback_fn cb) {
    dbgmm_calloc_success_cb = cb;
}

void dbgmm_set_calloc_failure_callback(calloc_failure_callback_fn cb) {
    dbgmm_calloc_failure_cb = cb;
}

void* dbgmm_calloc(size_t num, size_t size, const char* file, int line, const char* func) {
    void* p = ce_calloc(num, size);
    if (p == NULL) {
        dbgmm_calloc_failure_counter++;
        safe_call(dbgmm_calloc_failure_cb, num, size, file, line, func);
    } else {
        dbgmm_calloc_success_counter++;
        safe_call(dbgmm_calloc_success_cb, num, size, file, line, func, p);
    }
    if (assigned(internal_.dbgmm_pointers))
        UNUSED(kewl_ptrholder_add(internal_.dbgmm_pointers, (kewl_ptrholder_ptr_dt)p));
    return p;
}

#ifdef __c11

// ALIGNED ALLOC

long dbgmm_get_aligned_alloc_success_calls(void) {
    return dbgmm_aligned_alloc_success_counter;
}

long dbgmm_get_aligned_alloc_failure_calls(void) {
    return dbgmm_aligned_alloc_failure_counter;
}

aligned_alloc_success_callback_fn dbgmm_get_aligned_alloc_success_callback(void) {
    return dbgmm_aligned_alloc_success_cb;
}

aligned_alloc_failure_callback_fn dbgmm_get_aligned_alloc_failure_callback(void) {
    return dbgmm_aligned_alloc_failure_cb;
}

void dbgmm_set_aligned_alloc_success_callback(aligned_alloc_success_callback_fn cb) {
    dbgmm_aligned_alloc_success_cb = cb;
}

void dbgmm_set_aligned_alloc_failure_callback(aligned_alloc_failure_callback_fn cb) {
    dbgmm_aligned_alloc_failure_cb = cb;
}

void* dbgmm_aligned_alloc(size_t alignment, size_t size, const char* file, int line, const char* func) {
    void* p = ce_aligned_alloc(alignment, size);
    if (p == NULL) {
        dbgmm_aligned_alloc_failure_counter++;
        safe_call(dbgmm_aligned_alloc_failure_cb, alignment, size, file, line, func);
    } else {
        dbgmm_aligned_alloc_success_counter++;
        safe_call(dbgmm_aligned_alloc_success_cb, alignment, size, file, line, func, p);
    }
    if (assigned(internal_.dbgmm_pointers))
        UNUSED(kewl_ptrholder_add(internal_.dbgmm_pointers, (kewl_ptrholder_ptr_dt)p));
    return p;
}

#endif

// REALLOC

long dbgmm_get_realloc_success_calls(void) {
    return dbgmm_realloc_success_counter;
}

long dbgmm_get_realloc_failure_calls(void) {
    return dbgmm_realloc_failure_counter;
}

realloc_success_callback_fn dbgmm_get_realloc_success_callback(void) {
    return dbgmm_realloc_success_cb;
}

realloc_failure_callback_fn dbgmm_get_realloc_failure_callback(void) {
    return dbgmm_realloc_failure_cb;
}

void dbgmm_set_realloc_success_callback(realloc_success_callback_fn cb) {
    dbgmm_realloc_success_cb = cb;
}

void dbgmm_set_realloc_failure_callback(realloc_failure_callback_fn cb) {
    dbgmm_realloc_failure_cb = cb;
}

void* dbgmm_realloc(void* ptr, size_t size, const char* file, int line, const char* func) {
    void* p = ce_realloc(ptr, size);
    if (p == NULL) {
        dbgmm_realloc_failure_counter++;
        safe_call(dbgmm_realloc_failure_cb, ptr, size, file, line, func);
    } else {
        dbgmm_realloc_success_counter++;
        safe_call(dbgmm_realloc_success_cb, ptr, size, file, line, func, p);
    }
    if (assigned(internal_.dbgmm_pointers))
        UNUSED(kewl_ptrholder_replace_once(internal_.dbgmm_pointers, (kewl_ptrholder_ptr_dt)ptr, (kewl_ptrholder_ptr_dt)p));
    return p;
}

// FREE

long dbgmm_get_free_success_calls(void) {
    return dbgmm_free_success_counter;
}

free_success_callback_fn dbgmm_get_free_success_callback(void) {
    return dbgmm_free_success_cb;
}

long dbgmm_get_free_failure_calls(void) {
    return dbgmm_free_failure_counter;
}

free_failure_callback_fn dbgmm_get_free_failure_callback(void) {
    return dbgmm_free_failure_cb;
}

void dbgmm_set_free_success_callback(free_success_callback_fn cb) {
    dbgmm_free_success_cb = cb;
}

void dbgmm_set_free_failure_callback(free_failure_callback_fn cb) {
    dbgmm_free_failure_cb = cb;
}

void dbgmm_free(void* ptr, const char* file, int line, const char* func) {
    if (ptr == NULL) {
        dbgmm_free_failure_counter++;
        safe_call(dbgmm_free_failure_cb, file, line, func);
    } else {
        ce_free(ptr);
        dbgmm_free_success_counter++;
        safe_call(dbgmm_free_success_cb, ptr, file, line, func);
        if (assigned(internal_.dbgmm_pointers))
            UNUSED(kewl_ptrholder_delete_once(internal_.dbgmm_pointers, (kewl_ptrholder_ptr_dt)ptr));
    }
}

