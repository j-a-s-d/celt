/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_task-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

/*
    This is basic and generic task container featuring execution state, execution counter,
    task label, exit value, custom data pointers (context, input and output), etc.
*/

struct kewl_task_dt;

typedef void (*kewl_task_initializer_fn)(struct kewl_task_dt* self);
typedef int (*kewl_task_routine_fn)(struct kewl_task_dt* self);
typedef void (*kewl_task_finalizer_fn)(struct kewl_task_dt* self);

typedef enum {
    KEWL_TASK_UNINITIALIZED,
    KEWL_TASK_INITIALIZING,
    KEWL_TASK_INITIALIZED,
    KEWL_TASK_RUNNING,
    KEWL_TASK_RUNNED,
    KEWL_TASK_FINALIZING,
    KEWL_TASK_FINALIZED
} kewl_task_state_dt;

typedef struct ALIGN_64 kewl_task_dt {
    char* id_label;
    kewl_task_initializer_fn on_initialize;
    kewl_task_routine_fn on_run;
    kewl_task_finalizer_fn on_finalize;
    kewl_task_state_dt state;
    void* context_data;
    void* input_data;
    void* output_data;
    int exit_value;
    int execution_times;
} kewl_task_dt;

kewl_task_dt* kewl_task_create(const char* id_label);
void kewl_task_destroy(kewl_task_dt* task);
const char* kewl_task_get_id_label(kewl_task_dt* task);
void kewl_task_set_initializer(kewl_task_dt* task, kewl_task_initializer_fn initializer);
void kewl_task_set_routine(kewl_task_dt* task, kewl_task_routine_fn main);
void kewl_task_set_finalizer(kewl_task_dt* task, kewl_task_finalizer_fn finalizer);
kewl_task_state_dt kewl_task_get_state(kewl_task_dt* task);
void kewl_task_set_context_data(kewl_task_dt* task, void* data);
void* kewl_task_get_context_data(kewl_task_dt* task);
void kewl_task_set_input_data(kewl_task_dt* task, void* data);
void* kewl_task_get_input_data(kewl_task_dt* task);
void kewl_task_set_output_data(kewl_task_dt* task, void* data);
void* kewl_task_get_output_data(kewl_task_dt* task);
int kewl_task_get_exit_value(kewl_task_dt* task);
int kewl_task_get_execution_times(kewl_task_dt* task);
bool kewl_task_execute(kewl_task_dt* task);
void kewl_task_terminate(kewl_task_dt* task);

