/**
 * werks_program: generalist program structure for c
 */

#include "werks_program.h"

static void task_initializer(kewl_task_dt* task) {
    werks_program_dt* prg = (werks_program_dt*)kewl_task_get_input_data(task);
    if (assigned(prg->on_before_main)) 
        if (!prg->on_before_main(prg, prg->args_count, prg->args_values))
            kewl_task_terminate(task);
}

static int task_routine(kewl_task_dt* task) {
    werks_program_dt* prg = (werks_program_dt*)kewl_task_get_input_data(task);
    return prg->on_run_main(prg);
}

static void task_finalizer(kewl_task_dt* task) {
    werks_program_dt* prg = (werks_program_dt*)kewl_task_get_input_data(task);
    if (assigned(prg->on_after_main))
        prg->on_after_main(prg, task->exit_value);
}

static void reset_fields(werks_program_dt* prg) {
    prg->component_instance = NULL;
    prg->created_timestamp = NULL;
    prg->program_task = NULL;
    prg->started_time = 0;
    prg->finished_time = 0;
    prg->on_before_main = NULL;
    prg->on_run_main = NULL;
    prg->on_after_main = NULL;
    prg->args_count = 0;
    prg->args_values = NULL;
}

werks_program_dt* werks_program_create(void) {
    RET_MALLOC(werks_program_dt, {
        reset_fields(result);
        result->created_timestamp = get_timestamp();
        result->program_task = kewl_task_create(result->created_timestamp);
        kewl_task_set_input_data(result->program_task, (void*)result);
        kewl_task_set_initializer(result->program_task, task_initializer);
        kewl_task_set_routine(result->program_task, task_routine);
        kewl_task_set_finalizer(result->program_task, task_finalizer);
        result->component_instance = kewl_component_create(result, WERKS_PROGRAM_TYPE_NAME);
    });
}

int werks_program_destroy(werks_program_dt* const prg) {
    if (prg == NULL) return -1;
    int result = prg->program_task == NULL ? -1 : prg->program_task->exit_value;
    kewl_task_destroy(prg->program_task);
    kewl_component_destroy(prg->component_instance);
    ce_free(prg->created_timestamp);
    reset_fields(prg);
    ce_free(prg);
    return result;
}

const kewl_component_dt* werks_program_get_component(werks_program_dt* const prg) {
    return prg == NULL ? NULL : prg->component_instance;
}

const char* werks_program_get_created_timestamp(werks_program_dt* const prg) {
    return prg == NULL ? NULL : prg->created_timestamp;
}

void werks_program_set_on_before_main(werks_program_dt* const prg, werks_program_initializer_fn on_before_main) {
    if (prg == NULL) return;
    prg->on_before_main = on_before_main;
}

void werks_program_set_main(werks_program_dt* const prg, werks_program_routine_fn main) {
    if (prg == NULL) return;
    prg->on_run_main = main;
}

void werks_program_set_on_after_main(werks_program_dt* const prg, werks_program_finalizer_fn on_after_main) {
    if (prg == NULL) return;
    prg->on_after_main = on_after_main;
}

void werks_program_set_input_args(werks_program_dt* const prg, int args_count, const char* args_values[]) {
    if (prg == NULL) return;
    prg->args_count = args_count;
    prg->args_values = args_values;
}

int werks_program_get_input_argc(werks_program_dt* const prg) {
    return prg == NULL ?
        -1 : prg->args_count;
}

const char** werks_program_get_input_argv(werks_program_dt* const prg) {
    return prg == NULL ?
        NULL : prg->args_values;
}

bool werks_program_has_finished(werks_program_dt* const prg) {
    return prg == NULL || prg->program_task == NULL ?
        false : prg->program_task->state == KEWL_TASK_FINALIZED;
}

int werks_program_get_exit_value(werks_program_dt* const prg) {
    return prg == NULL || prg->program_task == NULL ?
        -1 : prg->program_task->exit_value;
}

void werks_program_set_context(werks_program_dt* prg, void* ctx) {
    if (prg == NULL || prg->program_task == NULL) return;
    prg->program_task->context_data = ctx;
}

void* werks_program_get_context(werks_program_dt* prg) {
    return prg == NULL || prg->program_task == NULL ?
        NULL : prg->program_task->context_data;
}

elapsed_time_dt werks_program_get_elapsed_time(werks_program_dt* const prg) {
    if (prg == NULL || prg->started_time == 0) return DEFAULT_ELAPSED_TIME;
    return get_elapsed_time(prg->started_time, prg->finished_time == 0 ? time(NULL) : prg->finished_time);
}

bool werks_program_run(werks_program_dt* const prg) {
    if (prg == NULL || prg->program_task == NULL || prg->on_run_main == NULL) return false;
    prg->started_time = time(NULL);
    bool result = kewl_task_execute(prg->program_task);
    prg->finished_time = time(NULL);
    return result;
}

