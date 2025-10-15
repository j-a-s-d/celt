/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: WeRKS DYNVOKE
 * File: werks_dynvoke.h
 * Brief: dynamic function invocation utilities
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WERKS_DYNVOKE_ALIGNMENT
    #define WERKS_DYNVOKE_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef WERKS_DYNVOKE_GROW_FACTOR
    #define WERKS_DYNVOKE_GROW_FACTOR 2.0f
#endif

#ifndef WERKS_DYNVOKE_GROW_PADDING
    #define WERKS_DYNVOKE_GROW_PADDING 0.0f
#endif

#if defined(__unix__) || defined(__APPLE__) || defined(_POSIX_VERSION)

#ifndef WERKS_DYNVOKE_DISALLOW_UNREGISTERED
    #define WERKS_DYNVOKE_ALLOW_UNREGISTERED
#endif

// NOTE: for this to work you need to compile with -rdynamic
// and also, in some systems and configurations, you will need -ldl
// and yet in some other setups you will need to add -D_GNU_SOURCE

#include <dlfcn.h>
#ifndef WERKS_DYNVOKE_UNREGISTERED_RTLD
    #ifdef RTLD_DEFAULT
        #define WERKS_DYNVOKE_UNREGISTERED_RTLD RTLD_DEFAULT
    #else
        #define WERKS_DYNVOKE_UNREGISTERED_RTLD NULL
    #endif
#endif

#endif

#include "kewl.h"

#define WERKS_DYNVOKE

// NOTE: the entry point is analog to the common main signature "int main(int argc, char* argv[])"

typedef struct WERKS_DYNVOKE_ALIGNMENT {
    const char* name;
    args_main_fn code;
    const void* data;
} dynvoke_function_registration_dt;

bool dynvoke_register_function(dynvoke_function_registration_dt new_reg);
bool dynvoke_has_function(const void* fn_code);
bool dynvoke_has_named_function(const char* fn_name);
bool dynvoke_set_function_data(const void* fn_code, const void* custom_data);
const void* dynvoke_get_function_data(const void* fn_code);
bool dynvoke_set_named_function_data(const char* fn_name, const void* custom_data);
const void* dynvoke_get_named_function_data(const char* fn_name);
void dynvoke_unregister_functions(void);

#define DYNVOKE_REGISTER(fn) dynvoke_register_function((dynvoke_function_registration_dt){#fn, fn, NULL})

typedef struct WERKS_DYNVOKE_ALIGNMENT {
    const char* error_message;
    int exit_value;
} dynvoke_function_result_dt;

dynvoke_function_result_dt dynvoke_execute_function(const char* cmd_str);
#ifdef WERKS_DYNVOKE_ALLOW_UNREGISTERED
dynvoke_function_result_dt dynvoke_execute_unregistered_function(const char* cmd_str);
#endif

static const struct {
    bool (*const register_function)(dynvoke_function_registration_dt new_reg);
    bool (*const has_function)(const void* fn_code);
    bool (*const has_named_function)(const char* fn_name);
    bool (*const set_function_data)(const void* fn_code, const void* custom_data);
    const void* (*const get_function_data)(const void* fn_code);
    bool (*const set_named_function_data)(const char* fn_name, const void* custom_data);
    const void* (*const get_named_function_data)(const char* fn_name);
    void (*const unregister_functions)(void);
    dynvoke_function_result_dt (*const execute_function)(const char* cmd_str);
    #ifdef WERKS_DYNVOKE_ALLOW_UNREGISTERED
    dynvoke_function_result_dt (*const execute_unregistered_function)(const char* cmd_str);
    #endif
} Dynvoke = {
    dynvoke_register_function,
    dynvoke_has_function,
    dynvoke_has_named_function,
    dynvoke_set_function_data,
    dynvoke_get_function_data,
    dynvoke_set_named_function_data,
    dynvoke_get_named_function_data,
    dynvoke_unregister_functions,
    dynvoke_execute_function,
    #ifdef WERKS_DYNVOKE_ALLOW_UNREGISTERED
    dynvoke_execute_unregistered_function
    #endif
};

#ifdef __cplusplus
}
#endif

