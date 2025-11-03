/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: WeRKS PROGRAM
 * File: werks_program.h
 * Brief: generalist program structure
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "kewl.h"

#define WERKS_PROGRAM

#define WERKS_PROGRAM_TYPE_NAME "werks_program_dt"

#ifndef WERKS_PROGRAM_ALIGNMENT
    #define WERKS_PROGRAM_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

struct werks_program_dt;

typedef bool (*werks_program_initializer_fn)(struct werks_program_dt* prg, int args_count, const char* args_values[]);
typedef int (*werks_program_routine_fn)(struct werks_program_dt* prg);
typedef void (*werks_program_finalizer_fn)(struct werks_program_dt* prg, int exit_value);

typedef struct WERKS_PROGRAM_ALIGNMENT werks_program_dt {
    kewl_component_dt* component_instance;
    char* created_timestamp;
    time_t started_time;
    time_t finished_time;
    werks_program_initializer_fn on_before_main;
    werks_program_routine_fn on_run_main;
    werks_program_finalizer_fn on_after_main;
    kewl_task_dt* program_task;
    int args_count;
    const char** args_values;
} werks_program_dt;

werks_program_dt* werks_program_create(void);
int werks_program_destroy(werks_program_dt* prg);
const kewl_component_dt* werks_program_get_component(werks_program_dt* prg);

bool werks_program_has_finished(werks_program_dt* prg);
const char* werks_program_get_created_timestamp(werks_program_dt* prg);
elapsed_time_dt werks_program_get_elapsed_time(werks_program_dt* const prg);

void werks_program_set_on_before_main(werks_program_dt* prg, werks_program_initializer_fn initializer);
static inline werks_program_initializer_fn werks_program_get_on_before_main(werks_program_dt* prg) {
    return prg ? prg->on_before_main : NULL;
}
void werks_program_set_main(werks_program_dt* prg, werks_program_routine_fn main);
static inline werks_program_routine_fn werks_program_get_main(werks_program_dt* prg) {
    return prg ? prg->on_run_main : NULL;
}
void werks_program_set_on_after_main(werks_program_dt* prg, werks_program_finalizer_fn finalizer);
static inline werks_program_finalizer_fn werks_program_get_on_after_main(werks_program_dt* prg) {
    return prg ? prg->on_after_main : NULL;
}

void werks_program_set_input_args(werks_program_dt* prg, int args_count, const char* args_values[]);
int werks_program_get_input_argc(werks_program_dt* prg);
const char** werks_program_get_input_argv(werks_program_dt* prg);

void werks_program_set_context(werks_program_dt* prg, void* ctx);
void* werks_program_get_context(werks_program_dt* prg);

int werks_program_get_exit_value(werks_program_dt* prg);
bool werks_program_run(werks_program_dt* prg);

#ifdef __cplusplus
}
#endif

