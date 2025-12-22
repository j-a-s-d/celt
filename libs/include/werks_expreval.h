/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: WeRKS EXPREVAL
 * File: werks_expreval.h
 * Brief: simple expression evaulator supporting custom constants
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "kewl.h"

#define WERKS_EXPREVAL

#define WERKS_EXPREVAL_TYPE_NAME "werks_expreval_dt"

#ifndef WERKS_EXPREVAL_ALIGNMENT
    #define WERKS_EXPREVAL_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef WERKS_EXPREVAL_LIST_INITIAL_CAPACITY
    #define WERKS_EXPREVAL_LIST_INITIAL_CAPACITY 128
#endif

#ifndef WERKS_EXPREVAL_LIST_ALIGNMENT
    #define WERKS_EXPREVAL_LIST_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef WERKS_EXPREVAL_LIST_GROW_FACTOR
    #define WERKS_EXPREVAL_LIST_GROW_FACTOR 2.0f
#endif

#ifndef WERKS_EXPREVAL_LIST_GROW_PADDING
    #define WERKS_EXPREVAL_LIST_GROW_PADDING 0.0f
#endif

#ifndef WERKS_EXPREVAL_CONST_MAX_COUNT
    #define WERKS_EXPREVAL_CONST_MAX_COUNT 64
#endif

#ifndef WERKS_EXPREVAL_CONST_MAX_NAME
    #define WERKS_EXPREVAL_CONST_MAX_NAME 8
#endif

#ifndef WERKS_EXPREVAL_CONST_PREFIX
    #define WERKS_EXPREVAL_CONST_PREFIX '$'
#endif

#ifndef WERKS_EXPREVAL_TYPE
    #define WERKS_EXPREVAL_TYPE double // other values: float and long double
#endif

#ifndef WERKS_EXPREVAL_NAN
    #define WERKS_EXPREVAL_NAN double_NaN // other values: float_NaN and long_double_NaN
#endif

#ifndef WERKS_EXPREVAL_ISNAN
    #define WERKS_EXPREVAL_ISNAN double_isNaN // other values: float_isNaN and long_double_isNaN
#endif

#ifndef WERKS_EXPREVAL_EQUAL
    #define WERKS_EXPREVAL_EQUAL double_equal // other values: float_equal and long_double_equal
#endif

#ifndef WERKS_EXPREVAL_EPSILON
    #define WERKS_EXPREVAL_EPSILON MEH_DOUBLE_EPSILON // other values: MEH_FLOAT_EPSILON and MEH_LONG_DOUBLE_EPSILON
#endif

#ifndef WERKS_EXPREVAL_FORMAT
    #define WERKS_EXPREVAL_FORMAT double_string_format // other values: float_string_format and long_double_string_format
#endif

#ifndef WERKS_EXPREVAL_TREATER_TYPE
    #define WERKS_EXPREVAL_TREATER_TYPE trt_double_fn // other values: trt_float_fn and trt_long_double_fn
#endif

#ifndef WERKS_EXPREVAL_SENTINEL_LIMIT
    #define WERKS_EXPREVAL_SENTINEL_LIMIT MEH_DEFAULT_SENTINEL_LIMIT
#endif

#define WERKS_EXPREVAL_ERROR_INVALID -1
#define WERKS_EXPREVAL_ERROR_NONE 0
#define WERKS_EXPREVAL_ERROR_EXPRESSION 1
#define WERKS_EXPREVAL_ERROR_CONSTANT 2

// constants

typedef struct werks_expreval_constants_dt werks_expreval_constants_dt;

werks_expreval_constants_dt* werks_expreval_constants_make();
ssize_t werks_expreval_constants_count(werks_expreval_constants_dt* constants);
bool werks_expreval_constants_drop(werks_expreval_constants_dt* constants, const char* name);
bool werks_expreval_constants_drop_all(werks_expreval_constants_dt* const constants);
bool werks_expreval_constants_has(werks_expreval_constants_dt* constants, const char* name);
bool werks_expreval_constants_set(werks_expreval_constants_dt* constants, const char* name, WERKS_EXPREVAL_TYPE value);
bool werks_expreval_constants_set_all(werks_expreval_constants_dt* const constants, WERKS_EXPREVAL_TYPE value);
WERKS_EXPREVAL_TYPE werks_expreval_constants_get(werks_expreval_constants_dt* constants, const char* name);

// evaluator

typedef struct werks_expreval_dt werks_expreval_dt;

werks_expreval_dt* werks_expreval_create(werks_expreval_constants_dt* constants);
static inline werks_expreval_dt* werks_expreval_make() {
    return werks_expreval_create(werks_expreval_constants_make());
}
werks_expreval_constants_dt* werks_expreval_constants_get_constants(werks_expreval_dt* evaluator);
ssize_t werks_expreval_constants_get_error(werks_expreval_dt* evaluator);
WERKS_EXPREVAL_TYPE werks_expreval_evaluate_expression(werks_expreval_dt* evaluator, const char* expression);
void werks_expreval_destroy(werks_expreval_dt* instance);

// list

typedef struct werks_expreval_expressions_list_dt werks_expreval_expressions_list_dt;

typedef struct WERKS_EXPREVAL_LIST_ALIGNMENT {
    WERKS_EXPREVAL_TYPE current;
    WERKS_EXPREVAL_TYPE last;
    ssize_t error;
    bool modified;
    char* expression;
} werks_expreval_expressions_data_dt;

werks_expreval_expressions_list_dt* werks_expreval_expressions_list_make();
const werks_expreval_expressions_data_dt* werks_expreval_expressions_list_get(werks_expreval_expressions_list_dt* list, const char* expression);
static inline WERKS_EXPREVAL_TYPE werks_expreval_expressions_list_get_current_value(werks_expreval_expressions_list_dt* list, const char* expression, WERKS_EXPREVAL_TYPE default_value) {
    const werks_expreval_expressions_data_dt* data = werks_expreval_expressions_list_get(list, expression);
    return assigned(data) ? data->current : default_value;
}
bool werks_expreval_expressions_list_add(werks_expreval_expressions_list_dt* list, const char* expression);
bool werks_expreval_expressions_list_add_from_array_with_sentinel(werks_expreval_expressions_list_dt* list, const char** array);
bool werks_expreval_expressions_list_add_from_array_with_size(werks_expreval_expressions_list_dt* list, const char** array, ssize_t size);
bool werks_expreval_expressions_list_delete(werks_expreval_expressions_list_dt* list, const char* expression);
size_t werks_expreval_expressions_list_get_count(werks_expreval_expressions_list_dt* list);
void werks_expreval_expressions_list_reevaluate(werks_expreval_expressions_list_dt* list, werks_expreval_dt* evaluator);
void werks_expreval_expressions_list_treat(werks_expreval_expressions_list_dt* list, WERKS_EXPREVAL_TREATER_TYPE treater);
ssize_t werks_expreval_expressions_list_get_rounds(werks_expreval_expressions_list_dt* list);
void werks_expreval_expressions_list_destroy(werks_expreval_expressions_list_dt* list);

typedef void (*werks_expreval_expressions_list_on_result_change_handler_fn)(werks_expreval_expressions_list_dt* list, werks_expreval_expressions_data_dt* data);
werks_expreval_expressions_list_on_result_change_handler_fn werks_expreval_expressions_list_get_on_result_change(werks_expreval_expressions_list_dt* list);
void werks_expreval_expressions_list_set_on_result_change(werks_expreval_expressions_list_dt* list, werks_expreval_expressions_list_on_result_change_handler_fn handler);

typedef void (*werks_expreval_expressions_list_loop_handler_fn)(werks_expreval_expressions_list_dt* list, werks_expreval_expressions_data_dt* data);
void werks_expreval_expressions_list_loop(werks_expreval_expressions_list_dt* list, werks_expreval_expressions_list_loop_handler_fn handler);
void werks_expreval_expressions_list_reverse_loop(werks_expreval_expressions_list_dt* list, werks_expreval_expressions_list_loop_handler_fn handler);

typedef void (*werks_expreval_expressions_list_loop_with_reference_handler_fn)(werks_expreval_expressions_list_dt* list, werks_expreval_expressions_data_dt* data, void* reference);
void werks_expreval_expressions_list_loop_with_reference(werks_expreval_expressions_list_dt* list, werks_expreval_expressions_list_loop_with_reference_handler_fn handler, void* reference);
void werks_expreval_expressions_list_reverse_loop_with_reference(werks_expreval_expressions_list_dt* list, werks_expreval_expressions_list_loop_with_reference_handler_fn handler, void* reference);

#ifdef __cplusplus
}
#endif

