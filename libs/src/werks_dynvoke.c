/**
 * werks_dynvoke: dynamic function invocation
 */

#include "werks_dynvoke.h"

typedef struct WERKS_DYNVOKE_ALIGNMENT {
    dynvoke_function_registration_dt* data;
    size_t size; // Number of elements currently in the array
    size_t capacity; // Allocated capacity
} dynvoke_registered_functions_dt;

#define DYNVOKE_INITIAL_STATE ((dynvoke_registered_functions_dt) {NULL, 0, 0})

unit_internal({ dynvoke_registered_functions_dt registered_functions; }) = {DYNVOKE_INITIAL_STATE};

// FUNCTION REGISTRATION

void dynvoke_unregister_functions(void) {
    if (assigned(internal_.registered_functions.data)) {
        ce_free(internal_.registered_functions.data);
        internal_.registered_functions.data = NULL;
    }
    internal_.registered_functions = DYNVOKE_INITIAL_STATE;
}

static inline bool increase_capacity(void) {
    size_t new_capacity = internal_.registered_functions.capacity == 0 ? 2 : (internal_.registered_functions.capacity * WERKS_DYNVOKE_GROW_FACTOR) + WERKS_DYNVOKE_GROW_PADDING;
    dynvoke_function_registration_dt* tmp = TYPE_REALLOC(internal_.registered_functions.data, dynvoke_function_registration_dt, new_capacity);
    if (!tmp) return false;
    internal_.registered_functions.data = tmp;
    internal_.registered_functions.capacity = new_capacity;
    return true;
}

bool dynvoke_register_function(dynvoke_function_registration_dt new_reg) {
    if (!new_reg.name || !*new_reg.name || !new_reg.code) return false;
    if (internal_.registered_functions.size == internal_.registered_functions.capacity)
        if (!increase_capacity()) return false;
    internal_.registered_functions.data[internal_.registered_functions.size++] = new_reg;
    return true;
}

// FUNCTION OPERATION

bool dynvoke_has_function(const void* fn_code) {
    if (assigned(fn_code))
        for (size_t i = 0; i < internal_.registered_functions.size; i++)
            if ((void*)internal_.registered_functions.data[i].code == fn_code)
                return true;
    return false;
}

bool dynvoke_has_named_function(const char* fn_name) {
    if (has_content(fn_name))
        for (size_t i = 0; i < internal_.registered_functions.size; i++)
            if (strcmp(internal_.registered_functions.data[i].name, fn_name) == 0)
                return true;
    return false;
}

bool dynvoke_set_function_data(const void* fn_code, const void* custom_data) {
    if (assigned(fn_code))
        for (size_t i = 0; i < internal_.registered_functions.size; i++)
            if ((void*)internal_.registered_functions.data[i].code == fn_code) {
                internal_.registered_functions.data[i].data = custom_data;
                return true;
            }
    return false;
}

const void* dynvoke_get_function_data(const void* fn_code) {
    if (assigned(fn_code))
        for (size_t i = 0; i < internal_.registered_functions.size; i++)
            if ((void*)internal_.registered_functions.data[i].code == fn_code)
                return internal_.registered_functions.data[i].data;
    return NULL;
}

bool dynvoke_set_named_function_data(const char* fn_name, const void* custom_data) {
    if (has_content(fn_name))
        for (size_t i = 0; i < internal_.registered_functions.size; i++)
            if (strcmp(internal_.registered_functions.data[i].name, fn_name) == 0) {
                internal_.registered_functions.data[i].data = custom_data;
                return true;
            }
    return false;
}

const void* dynvoke_get_named_function_data(const char* fn_name) {
    if (has_content(fn_name))
        for (size_t i = 0; i < internal_.registered_functions.size; i++)
            if (strcmp(internal_.registered_functions.data[i].name, fn_name) == 0)
                return internal_.registered_functions.data[i].data;
    return NULL;
}

// FUNCTION EXECUTION

typedef struct WERKS_DYNVOKE_ALIGNMENT {
    char* func_name;
    char** args;
    int args_count;
} dynvoke_function_call_dt;

static dynvoke_function_call_dt split_function_string(const char* input) {
#define loop_tokens(block) while (assigned(token)) { token = strtok(NULL, " "); if (assigned(token)) block; }
    dynvoke_function_call_dt result = {NULL, NULL, 0};
    if (has_content(input)) {
        char* tmp = strdup(input);
        char* token = strtok(tmp, " ");
        result.func_name = strdup(token);
        result.args_count = 0;
        loop_tokens({ result.args_count++; });
        result.args = ce_malloc(result.args_count * sizeof(char*));
        strcpy(tmp, input); // reset strtok
        token = strtok(tmp, " ");
        int index = 0;
        loop_tokens({ result.args[index++] = strdup(token); });
        ce_free(tmp);
    }
    return result;
#undef loop_tokens
}

void dynvoke_function_call_destroy(dynvoke_function_call_dt fc) {
    for (ssize_t i = 0; i < fc.args_count; i++)
        ce_free(fc.args[i]);
    ce_free(fc.args);
    ce_free(fc.func_name);
}

static inline int dynvoke_invoke_registered_function(const char* name, int argc, char* argv[]) {
    if (has_content(name))
        for (size_t i = 0; i < internal_.registered_functions.size; i++) {
            dynvoke_function_registration_dt fr = internal_.registered_functions.data[i];
            if (!strcmp(fr.name, name) && assigned(fr.code))
                return fr.code(argc, argv);
        }
    return -1;
}

dynvoke_function_result_dt dynvoke_execute_function(const char* cmd_str) {
    dynvoke_function_result_dt result = {NULL, -1};
    if (has_content(cmd_str)) {
        dynvoke_function_call_dt fc = split_function_string(cmd_str);
        result.exit_value = dynvoke_invoke_registered_function(fc.func_name, fc.args_count, fc.args);
        dynvoke_function_call_destroy(fc);
    }
    return result;
}

#ifdef WERKS_DYNVOKE_ALLOW_UNREGISTERED
dynvoke_function_result_dt dynvoke_execute_unregistered_function(const char* cmd_str) {
    dynvoke_function_result_dt result = {NULL, -1};
    if (has_content(cmd_str)) {
        dynvoke_function_call_dt fc = split_function_string(cmd_str);
        dlerror(); // clear any existing errors
        void* sym = dlsym(WERKS_DYNVOKE_UNREGISTERED_RTLD, fc.func_name);
        if ((result.error_message = dlerror()) == NULL)
            if (assigned(sym)) {
                args_main_fn fn = (args_main_fn)sym;
                result.exit_value = fn(fc.args_count, fc.args);
            }
        dynvoke_function_call_destroy(fc);
    }
    return result;
}
#endif

#undef DYNVOKE_INITIAL_STATE

