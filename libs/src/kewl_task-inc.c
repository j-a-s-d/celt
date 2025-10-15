/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_task-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "kewl_task-inc.h"

kewl_task_dt* kewl_task_create(const char* id_label) {
    RET_MALLOC(kewl_task_dt, {
        result->id_label = strdup(null_coalesce((void*)id_label, STRINGS_NOTHING));
        result->on_initialize = NULL;
        result->on_run = NULL;
        result->on_finalize = NULL;
        result->state = KEWL_TASK_UNINITIALIZED;
        result->execution_times = 0;
        result->exit_value = 0;
        result->context_data = NULL;
        result->input_data = NULL;
        result->output_data = NULL;
    });
}

void kewl_task_destroy(kewl_task_dt* const task) {
    if (task == NULL) return;
    ce_free(task->id_label);
    ce_free(task);
}

const char* kewl_task_get_id_label(kewl_task_dt* const task) {
    return task == NULL ?
        NULL : task->id_label;
}

void kewl_task_set_initializer(kewl_task_dt* const task, kewl_task_initializer_fn initializer) {
    if (task == NULL) return;
    task->on_initialize = initializer;
}

void kewl_task_set_routine(kewl_task_dt* const task, kewl_task_routine_fn main) {
    if (task == NULL) return;
    task->on_run = main;
}

void kewl_task_set_finalizer(kewl_task_dt* const task, kewl_task_finalizer_fn finalizer) {
    if (task == NULL) return;
    task->on_finalize = finalizer;
}

void kewl_task_set_context_data(kewl_task_dt* const task, void* data) {
    if (task == NULL) return;
    task->context_data = data;
}

void* kewl_task_get_context_data(kewl_task_dt* const task) {
    return task == NULL ?
        NULL : task->context_data;
}

void kewl_task_set_input_data(kewl_task_dt* const task, void* data) {
    if (task == NULL) return;
    task->input_data = data;
}

void* kewl_task_get_input_data(kewl_task_dt* const task) {
    return task == NULL ?
        NULL : task->input_data;
}

kewl_task_state_dt kewl_task_get_state(kewl_task_dt* const task) {
    return task == NULL ?
        KEWL_TASK_UNINITIALIZED : task->state;
}

void kewl_task_terminate(kewl_task_dt* const task) {
    if (assigned(task)) task->state = KEWL_TASK_FINALIZED;
}

bool kewl_task_execute(kewl_task_dt* const task) {
    if (task == NULL || (task->state != KEWL_TASK_UNINITIALIZED && task->state != KEWL_TASK_FINALIZED))
        return false;
    task->execution_times++;
    if (assigned(task->on_initialize)) {
        task->state = KEWL_TASK_INITIALIZING;
        task->on_initialize(task);
        if (task->state == KEWL_TASK_FINALIZED) return true;
        task->state = KEWL_TASK_INITIALIZED;
    }
    if (assigned(task->on_run)) {
        task->state = KEWL_TASK_RUNNING;
        task->exit_value = task->on_run(task);
        if (task->state == KEWL_TASK_FINALIZED) return true;
        task->state = KEWL_TASK_RUNNED;
    }
    if (assigned(task->on_finalize)) {
        task->state = KEWL_TASK_FINALIZING;
        task->on_finalize(task);
        task->state = KEWL_TASK_FINALIZED;
    }
    return true;
}

int kewl_task_get_execution_times(kewl_task_dt* const task) {
    return task == NULL ?
        -1 : task->execution_times;
}

int kewl_task_get_exit_value(kewl_task_dt* const task) {
    return task == NULL ?
        -1 : task->exit_value;
}

void* kewl_task_get_output_data(kewl_task_dt* const task) {
    return task == NULL ?
        NULL : task->output_data;
}

void kewl_task_set_output_data(kewl_task_dt* const task, void* data) {
    if (task == NULL) return;
    task->output_data = data;
}

