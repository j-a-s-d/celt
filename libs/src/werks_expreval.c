/**
 * werks_expreval: simple expression evaulator supporting custom constants
 */

#include "werks_expreval.h"

// constants

struct WERKS_EXPREVAL_ALIGNMENT werks_expreval_constants_dt {
    char names[WERKS_EXPREVAL_CONST_MAX_COUNT][WERKS_EXPREVAL_CONST_MAX_NAME];
    WERKS_EXPREVAL_TYPE values[WERKS_EXPREVAL_CONST_MAX_COUNT];
};

werks_expreval_constants_dt* werks_expreval_constants_make() {
    return calloc(1, sizeof(werks_expreval_constants_dt));
}

static bool store_const(werks_expreval_constants_dt* const constants, int index, const char* name, WERKS_EXPREVAL_TYPE value) {
    strcpy(constants->names[index], name);
    constants->values[index] = value;
    return true;
}

ssize_t werks_expreval_constants_count(werks_expreval_constants_dt* const constants) {
    if (constants == NULL) return -1;
    ssize_t result = 0;
    for (int i = 0; i < WERKS_EXPREVAL_CONST_MAX_COUNT; i++)
        if (strlen(constants->names[i]) > 0)
            result++;
    return result;
}

bool werks_expreval_constants_drop(werks_expreval_constants_dt* const constants, const char* name) {
    if (assigned(constants) && has_content(name))
        for (int i = 0; i < WERKS_EXPREVAL_CONST_MAX_COUNT; i++)
            if (strcmp(constants->names[i], name) == 0)
                return store_const(constants, i, STRINGS_NOTHING, 0.0);
    return false;
}

bool werks_expreval_constants_drop_all(werks_expreval_constants_dt* const constants) {
    bool result;
    if ((result = assigned(constants)))
        for (int i = 0; i < WERKS_EXPREVAL_CONST_MAX_COUNT; i++)
            result &= store_const(constants, i, STRINGS_NOTHING, 0.0);
    return result;
}

bool werks_expreval_constants_has(werks_expreval_constants_dt* const constants, const char* name) {
    if (assigned(constants) && has_content(name))
        for (int i = 0; i < WERKS_EXPREVAL_CONST_MAX_COUNT; i++)
            if (strcmp(constants->names[i], name) == 0)
                return true;
    return false;
}

bool werks_expreval_constants_set(werks_expreval_constants_dt* const constants, const char* name, WERKS_EXPREVAL_TYPE value) {
    if (assigned(constants) && has_content(name)) {
        if (!werks_expreval_constants_has(constants, name)) {
            for (int i = 0; i < WERKS_EXPREVAL_CONST_MAX_COUNT; i++)
                if (strlen(constants->names[i]) == 0)
                    return store_const(constants, i, name, value);
        } else
            for (int i = 0; i < WERKS_EXPREVAL_CONST_MAX_COUNT; i++)
                if (strcmp(constants->names[i], name) == 0)
                    return store_const(constants, i, name, value);
    }
    return false;
}

bool werks_expreval_constants_set_all(werks_expreval_constants_dt* const constants, WERKS_EXPREVAL_TYPE value) {
    bool result;
    if ((result = assigned(constants)))
        for (int i = 0; i < WERKS_EXPREVAL_CONST_MAX_COUNT; i++)
            constants->values[i] = value;
    return result;
}

WERKS_EXPREVAL_TYPE werks_expreval_constants_get(werks_expreval_constants_dt* const constants, const char* name) {
    if (assigned(constants) && has_content(name))
        for (int i = 0; i < WERKS_EXPREVAL_CONST_MAX_COUNT; i++)
            if (strcmp(constants->names[i], name) == 0)
                return constants->values[i];
    return WERKS_EXPREVAL_NAN;
}

// evaluator

struct WERKS_EXPREVAL_ALIGNMENT werks_expreval_dt {
    werks_expreval_constants_dt* constants;
    const char* expression;
    ssize_t error;
};

werks_expreval_dt* werks_expreval_create(werks_expreval_constants_dt* const constants) {
    if (constants == NULL) return NULL;
    werks_expreval_dt* result = calloc(1, sizeof(werks_expreval_dt));
    result->constants = constants;
    return result;
}

void werks_expreval_destroy(werks_expreval_dt* const evaluator) {
    if (evaluator == NULL) return;
    free(evaluator->constants);
    free(evaluator);
}

werks_expreval_constants_dt* werks_expreval_constants_get_constants(werks_expreval_dt* const evaluator) {
    return safe_fetch(evaluator, constants, NULL);
}

ssize_t werks_expreval_constants_get_error(werks_expreval_dt* const evaluator) {
    return safe_fetch(evaluator, error, WERKS_EXPREVAL_ERROR_INVALID);
}

static WERKS_EXPREVAL_TYPE parse_expression(werks_expreval_dt* const evaluator);

#define DEFINE_EXPREVAL_FN(name, body) static WERKS_EXPREVAL_TYPE name(werks_expreval_dt* const evaluator) { \
        const char** expr = &evaluator->expression; \
        WERKS_EXPREVAL_TYPE result = 0.0; \
        body \
        return result; \
    }

DEFINE_EXPREVAL_FN(parse_number, {
    if (**expr == CHARS_NULL) {
        evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
        return WERKS_EXPREVAL_NAN;
    }
    char* end;
    result = strtod(*expr, &end);
    if (*expr == end) {
        evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
        return WERKS_EXPREVAL_NAN;
    }
    *expr = end;
})

DEFINE_EXPREVAL_FN(parse_factor, {
    if (**expr == CHARS_PARENTHESES_OPEN) {
        (*expr)++;
        if (**expr == CHARS_NULL) {
            evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
            return WERKS_EXPREVAL_NAN;
        }
        result = parse_expression(evaluator);
        if (evaluator->error == WERKS_EXPREVAL_ERROR_NONE) {
            if (**expr != CHARS_PARENTHESES_CLOSE) {
                evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
                return WERKS_EXPREVAL_NAN;
            }
            (*expr)++; // skip ')'
        }
    } else if (**expr == WERKS_EXPREVAL_CONST_PREFIX) {
        (*expr)++;
        if (**expr == CHARS_NULL) {
            evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
            return WERKS_EXPREVAL_NAN;
        }
        char vn[WERKS_EXPREVAL_CONST_MAX_NAME];
        int i = 0;
        while (isalnum(**expr) || **expr == CHARS_UNDERSCORE) {
            vn[i++] = **expr;
            (*expr)++;
        }
        vn[i] = CHARS_NULL;
        if (!werks_expreval_constants_has(evaluator->constants, vn)) {
            evaluator->error = WERKS_EXPREVAL_ERROR_CONSTANT;
        } else
            result = werks_expreval_constants_get(evaluator->constants, vn);
    } else
        result = parse_number(evaluator);
})

DEFINE_EXPREVAL_FN(parse_term, {
    result = parse_factor(evaluator);
    if (evaluator->error == WERKS_EXPREVAL_ERROR_NONE)
        while (**expr == CHARS_ASTERISK || **expr == CHARS_SLASH) {
            char op = **expr;
            (*expr)++;
            if (**expr == CHARS_NULL) {
                evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
                return WERKS_EXPREVAL_NAN;
            }
            WERKS_EXPREVAL_TYPE factor = parse_factor(evaluator);
            if (evaluator->error == WERKS_EXPREVAL_ERROR_NONE) {
                if (op == CHARS_ASTERISK) {
                    result *= factor;
                } else if (op == CHARS_SLASH) {
                    result /= factor;
                } else {
                    evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
                    return WERKS_EXPREVAL_NAN;
                }
            }
        }
})

DEFINE_EXPREVAL_FN(parse_expression, {
    result = parse_term(evaluator);
    if (evaluator->error == WERKS_EXPREVAL_ERROR_NONE)
        while (**expr == CHARS_PLUS || **expr == CHARS_MINUS) {
            char op = **expr;
            (*expr)++;
            if (**expr == CHARS_NULL) {
                evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
                return WERKS_EXPREVAL_NAN;
            }
            WERKS_EXPREVAL_TYPE term = parse_term(evaluator);
            if (evaluator->error == WERKS_EXPREVAL_ERROR_NONE) {
                if (op == CHARS_PLUS) {
                    result += term;
                } else if (op == CHARS_MINUS) {
                    result -= term;
                } else {
                    evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
                    return WERKS_EXPREVAL_NAN;
                }
            }
        }
})

#undef DEFINE_EXPREVAL_FN

WERKS_EXPREVAL_TYPE eval_expr(werks_expreval_dt* const evaluator, const char* expression) {
    evaluator->expression = expression;
    evaluator->error = WERKS_EXPREVAL_ERROR_NONE;
    WERKS_EXPREVAL_TYPE result = parse_expression(evaluator);
    return evaluator->error != WERKS_EXPREVAL_ERROR_NONE ? WERKS_EXPREVAL_NAN : result;
}

WERKS_EXPREVAL_TYPE werks_expreval_evaluate_expression(werks_expreval_dt* const evaluator, const char* expression) {
    WERKS_EXPREVAL_TYPE result = WERKS_EXPREVAL_NAN;
    if (assigned(evaluator)) {
        if (assigned(evaluator->constants)) {
            if (has_content(expression)) {
                char* tmp = remove_whitespace(expression);
                result = eval_expr(evaluator, tmp);
                free(tmp);
                evaluator->expression = NULL;
            } else
                evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
        } else
            evaluator->error = WERKS_EXPREVAL_ERROR_INVALID;
    }            
    return result;
}

// list

typedef struct WERKS_EXPREVAL_LIST_ALIGNMENT {
    char* original;
    uint8_t checksum;
    werks_expreval_expressions_data_dt data;
} werks_expreval_expressions_entry_dt;

struct WERKS_EXPREVAL_LIST_ALIGNMENT werks_expreval_expressions_list_dt {
    kewl_ptrholder_dt* expressions_entries;
    ssize_t evaluation_rounds;
    werks_expreval_expressions_list_on_result_change_handler_fn on_result_change;
};

werks_expreval_expressions_list_dt* werks_expreval_expressions_list_make() {
    RET_MALLOC(werks_expreval_expressions_list_dt, {
        result->expressions_entries = kewl_ptrholder_create(WERKS_EXPREVAL_LIST_INITIAL_CAPACITY);
        kewl_ptrholder_set_capacity_grow_factor(result->expressions_entries, WERKS_EXPREVAL_LIST_GROW_FACTOR);
        kewl_ptrholder_set_capacity_grow_padding(result->expressions_entries, WERKS_EXPREVAL_LIST_GROW_PADDING);
        result->evaluation_rounds = 0;
        result->on_result_change = NULL;
    });
}

werks_expreval_expressions_list_on_result_change_handler_fn werks_expreval_expressions_list_get_on_result_change(werks_expreval_expressions_list_dt* const list) {
    return safe_fetch(list, on_result_change, NULL);
}

void werks_expreval_expressions_list_set_on_result_change(werks_expreval_expressions_list_dt* const list, werks_expreval_expressions_list_on_result_change_handler_fn handler) {
    if (assigned(list)) list->on_result_change = handler;
}

const werks_expreval_expressions_data_dt* werks_expreval_expressions_list_get(werks_expreval_expressions_list_dt* const list, const char* expression) {
    if (assigned(list) && has_content(expression)) {
        uint8_t checksum = crc8_string(expression);
        PTRHOLDER_EACH_CASTED(list->expressions_entries, werks_expreval_expressions_entry_dt, entry, {
            if (entry->checksum == checksum && strcmp(entry->original, expression) == 0)
                return &(entry->data);
        });
    }
    return NULL;
}

bool werks_expreval_expressions_list_add(werks_expreval_expressions_list_dt* const list, const char* expression) {
    if (list == NULL || !has_content(expression)) return false;
    uint8_t checksum = crc8_string(expression);
    PTRHOLDER_REVERSE_EACH_CASTED(list->expressions_entries, werks_expreval_expressions_entry_dt, entry, {
        if (entry->checksum == checksum && strcmp(entry->original, expression) == 0)
            return false;
    });
    VAR_MALLOC(entry, werks_expreval_expressions_entry_dt);
    entry->checksum = checksum;
    entry->original = strdup(expression);
    entry->data.expression = remove_whitespace(expression);
    entry->data.modified = false;
    entry->data.last = WERKS_EXPREVAL_NAN;
    entry->data.current = WERKS_EXPREVAL_NAN;
    return kewl_ptrholder_add(list->expressions_entries, (kewl_ptrholder_ptr_dt)entry);
}

bool werks_expreval_expressions_list_add_from_array_with_sentinel(werks_expreval_expressions_list_dt* list, const char** array) {
    if (list == NULL || array == NULL) return false;
    ssize_t size = string_array_find_null_sentinel(array, WERKS_EXPREVAL_SENTINEL_LIMIT);
    bool result = true;
    for (ssize_t i = 0; i < size; i++)
        result &= werks_expreval_expressions_list_add(list, array[i]);
    return result;
}

bool werks_expreval_expressions_list_add_from_array_with_size(werks_expreval_expressions_list_dt* list, const char** array, ssize_t size) {
    if (list == NULL || array == NULL || size < 0) return false;
    bool result = true;
    for (ssize_t i = 0; i < size; i++)
        result &= werks_expreval_expressions_list_add(list, array[i]);
    return result;
}

static bool remove_entry(kewl_ptrholder_dt* expressions_entries, werks_expreval_expressions_entry_dt* entry) {
    if (expressions_entries == NULL || entry == NULL) return false;
    ce_free(entry->original);
    ce_free(entry->data.expression);
    ce_free(entry);
    return kewl_ptrholder_delete_once(expressions_entries, (kewl_ptrholder_ptr_dt)entry);
}

bool werks_expreval_expressions_list_delete(werks_expreval_expressions_list_dt* const list, const char* expression) {
    if (assigned(list) && has_content(expression)) {
        uint8_t checksum = crc8_string(expression);
        PTRHOLDER_REVERSE_EACH_CASTED(list->expressions_entries, werks_expreval_expressions_entry_dt, entry, {
            if (entry->checksum == checksum && strcmp(entry->original, expression) == 0)
                return remove_entry(list->expressions_entries, entry);
        });
    }
    return false;
}

void werks_expreval_expressions_list_reevaluate(werks_expreval_expressions_list_dt* const list, werks_expreval_dt* const evaluator) {
    if (list == NULL || evaluator == NULL) return;
    list->evaluation_rounds++;
    PTRHOLDER_EACH_CASTED(list->expressions_entries, werks_expreval_expressions_entry_dt, entry, {
        entry->data.last = entry->data.current;
        entry->data.current = eval_expr(evaluator, entry->data.expression);
        entry->data.error = evaluator->error;
        if ((entry->data.modified = (evaluator->error == WERKS_EXPREVAL_ERROR_NONE) && !WERKS_EXPREVAL_EQUAL(entry->data.current, entry->data.last, WERKS_EXPREVAL_EPSILON)))
            if (assigned(list->on_result_change))
                list->on_result_change(list, &entry->data);
    });
}

void werks_expreval_expressions_list_treat(werks_expreval_expressions_list_dt* const list, WERKS_EXPREVAL_TREATER_TYPE treater) {
    if (list == NULL || treater == NULL) return;
    PTRHOLDER_EACH_CASTED(list->expressions_entries, werks_expreval_expressions_entry_dt, entry, {
        entry->data.current = treater(entry->data.current);
    });
}

ssize_t werks_expreval_expressions_list_get_rounds(werks_expreval_expressions_list_dt* const list) {
    return safe_fetch(list, evaluation_rounds, -1);
}

size_t werks_expreval_expressions_list_get_count(werks_expreval_expressions_list_dt* const list) {
    return assigned(list) ? kewl_ptrholder_get_size(list->expressions_entries) : 0;
}

void werks_expreval_expressions_list_loop(werks_expreval_expressions_list_dt* const list, werks_expreval_expressions_list_loop_handler_fn handler) {
    if (assigned(list) && assigned(handler))
        PTRHOLDER_EACH_CASTED(list->expressions_entries, werks_expreval_expressions_entry_dt, entry, {
            handler(list, &entry->data);
        });
}

void werks_expreval_expressions_list_reverse_loop(werks_expreval_expressions_list_dt* const list, werks_expreval_expressions_list_loop_handler_fn handler) {
    if (assigned(list) && assigned(handler))
        PTRHOLDER_REVERSE_EACH_CASTED(list->expressions_entries, werks_expreval_expressions_entry_dt, entry, {
            handler(list, &entry->data);
        });
}

void werks_expreval_expressions_list_loop_with_reference(werks_expreval_expressions_list_dt* const list, werks_expreval_expressions_list_loop_with_reference_handler_fn handler, void* reference) {
    if (assigned(list) && assigned(handler))
        PTRHOLDER_EACH_CASTED(list->expressions_entries, werks_expreval_expressions_entry_dt, entry, {
            handler(list, &entry->data, reference);
        });
}

void werks_expreval_expressions_list_reverse_loop_with_reference(werks_expreval_expressions_list_dt* const list, werks_expreval_expressions_list_loop_with_reference_handler_fn handler, void* reference) {
    if (assigned(list) && assigned(handler))
        PTRHOLDER_REVERSE_EACH_CASTED(list->expressions_entries, werks_expreval_expressions_entry_dt, entry, {
            handler(list, &entry->data, reference);
        });
}

static int experssions_entries_ascending_sorter(const void* a, const void* b) {
    const werks_expreval_expressions_entry_dt* entry1 = *(const void**)a;
    const werks_expreval_expressions_entry_dt* entry2 = *(const void**)b;
    WERKS_EXPREVAL_TYPE v1 = entry1->data.current;
    WERKS_EXPREVAL_TYPE v2 = entry2->data.current;
    if (v1 < v2) return -1;
    else if (v1 > v2) return 1;
    else return 0;
}

static int experssions_entries_descending_sorter(const void* a, const void* b) {
    const werks_expreval_expressions_entry_dt* entry1 = *(const void**)a;
    const werks_expreval_expressions_entry_dt* entry2 = *(const void**)b;
    WERKS_EXPREVAL_TYPE v1 = entry1->data.current;
    WERKS_EXPREVAL_TYPE v2 = entry2->data.current;
    if (v1 < v2) return 1;
    else if (v1 > v2) return -1;
    else return 0;
}

void werks_expreval_expressions_list_sort_by_value_ascending(werks_expreval_expressions_list_dt* list) {
    if (assigned(list))
        kewl_ptrholder_sort(list->expressions_entries, experssions_entries_ascending_sorter);
}

void werks_expreval_expressions_list_sort_by_value_descending(werks_expreval_expressions_list_dt* list) {
    if (assigned(list))
        kewl_ptrholder_sort(list->expressions_entries, experssions_entries_descending_sorter);
}

void werks_expreval_expressions_list_destroy(werks_expreval_expressions_list_dt* const list) {
    if (list == NULL) return;
    PTRHOLDER_REVERSE_EACH_CASTED(list->expressions_entries, werks_expreval_expressions_entry_dt, entry, {
        remove_entry(list->expressions_entries, entry);
    });
    kewl_ptrholder_destroy(list->expressions_entries);
    free(list);
}

werks_expreval_custom_fn werks_expreval_find_custom_function(const werks_expreval_custom_function_dt* registry, const char* name) {
    if (assigned(registry) && has_content(name))
        for (int i = 0; registry[i].name != NULL; i++)
            if (strcmp(registry[i].name, name) == 0)
                return registry[i].routine;
    return NULL;
}

static WERKS_EXPREVAL_TYPE werks_expreval_internal_direct_eval_with_custom_functions(werks_expreval_dt* evaluator, const werks_expreval_custom_function_dt* registry, const char* expression) {
    // remove whitespace
    while (*expression && isspace((unsigned char)*expression)) expression++;
    // verify if text starts with a valid function name (A-Z, a-z)
    if (isalpha((unsigned char)*expression)) {
        const char* p = expression;
        while (isalnum((unsigned char)*p) || *p == CHARS_UNDERSCORE) p++;
        if (*p == CHARS_PARENTHESES_OPEN) {
            int name_len = p - expression;
            char* func_name = (char*)ce_malloc(name_len + 1);
            strncpy(func_name, expression, name_len);
            func_name[name_len] = CHARS_NULL;
            werks_expreval_custom_fn func = werks_expreval_find_custom_function(registry, func_name);
            ce_free(func_name);
            if (assigned(func)) {
                // find balanced parenthesis
                const char* start_args = p + 1;
                const char* curr = start_args;
                int open_parentheses = 1;
                while (*curr && open_parentheses > 0) {
                    if (*curr == CHARS_PARENTHESES_OPEN) open_parentheses++;
                    if (*curr == CHARS_PARENTHESES_CLOSE) open_parentheses--;
                    if (open_parentheses > 0) curr++;
                }
                if (*curr == CHARS_PARENTHESES_CLOSE) {
                    // extract arguments
                    int args_len = curr - start_args;
                    char* args_text = (char*)ce_malloc(args_len + 1);
                    strncpy(args_text, start_args, args_len);
                    args_text[args_len] = CHARS_NULL;
                    // separate arguments
                    WERKS_EXPREVAL_TYPE* evaluated_args = NULL;
                    int arg_count = 0;
                    const char* arg_start = args_text;
                    int inner_paren = 0;
                    int i = 0;
                    LOOP_FOREVER() {
                        if (args_text[i] == CHARS_PARENTHESES_OPEN) inner_paren++;
                        if (args_text[i] == CHARS_PARENTHESES_CLOSE) inner_paren--;
                        if ((args_text[i] == CHARS_COMMA && inner_paren == 0) || args_text[i] == CHARS_NULL) {
                            int single_arg_len = &args_text[i] - arg_start;
                            if (single_arg_len > 0 || arg_count > 0) {
                                char* single_arg_text = (char*)ce_malloc(single_arg_len + 1);
                                strncpy(single_arg_text, arg_start, single_arg_len);
                                single_arg_text[single_arg_len] = CHARS_NULL;
                                // recursive evaluation
                                WERKS_EXPREVAL_TYPE val = werks_expreval_evaluate_expression_with_custom_functions(evaluator, registry, single_arg_text);
                                ce_free(single_arg_text);
                                evaluated_args = (WERKS_EXPREVAL_TYPE*)ce_realloc(evaluated_args, (arg_count + 1) * sizeof(WERKS_EXPREVAL_TYPE));
                                evaluated_args[arg_count] = val;
                                arg_count++;
                            }
                            arg_start = &args_text[i] + 1;
                        }
                        if (args_text[i] == CHARS_NULL) break;
                        i++;
                    }
                    // execute custom function
                    WERKS_EXPREVAL_TYPE result = func(evaluated_args, arg_count);
                    ce_free(evaluated_args);
                    ce_free(args_text);
                    // if there is extra text after ')' (ex: "ROUND(1.5) * 10") we add it
                    if (*(curr + 1) != CHARS_NULL) {
                        // stringify and eval
                        char buffer[512];
                        snprintf(buffer, sizeof(buffer), "%f%s", result, curr + 1);
                        return werks_expreval_evaluate_expression_with_custom_functions(evaluator, registry, buffer);
                    }
                    return result;
                }
            }
            return WERKS_EXPREVAL_NAN;
        }
    }
    return werks_expreval_evaluate_expression(evaluator, expression);
}

static WERKS_EXPREVAL_TYPE werks_expreval_internal_evaluate_with_custom_functions(werks_expreval_dt* evaluator, const werks_expreval_custom_function_dt* registry, const char* expression) {
    char* text = trim(expression);
    int len = strlen(text);
    if (starts_with(text, STRINGS_PARENTHESES_OPEN) && ends_with(text, STRINGS_PARENTHESES_CLOSE)) {
        text[len - 1] = CHARS_NULL;
        text++;
        WERKS_EXPREVAL_TYPE result = werks_expreval_internal_evaluate_with_custom_functions(evaluator, registry, text);
        ce_free(text - 1);
        return result;
    }
    int open_parentheses = 0;
    for (int i = len - 1; i >= 0; i--) {
        if (text[i] == CHARS_PARENTHESES_OPEN) open_parentheses++;
        if (text[i] == CHARS_PARENTHESES_CLOSE) open_parentheses--;
        if (open_parentheses == 0) {
            if (text[i] == CHARS_PLUS || text[i] == CHARS_MINUS || text[i] == CHARS_ASTERISK || text[i] == CHARS_SLASH) {
                char* left_part = (char*)ce_malloc(i + 1);
                strncpy(left_part, text, i);
                left_part[i] = CHARS_NULL;
                const char* right_part = text + i + 1;
                double left_val = werks_expreval_internal_evaluate_with_custom_functions(evaluator, registry, left_part);
                double right_val = werks_expreval_internal_evaluate_with_custom_functions(evaluator, registry, right_part);
                char op = text[i];
                ce_free(left_part);
                if (op == CHARS_PLUS) return left_val + right_val;
                if (op == CHARS_MINUS) return left_val - right_val;
                if (op == CHARS_ASTERISK) return left_val * right_val;
                if (op == CHARS_SLASH) return left_val / right_val;
                return WERKS_EXPREVAL_NAN;
            }
        }
    }
    WERKS_EXPREVAL_TYPE result = werks_expreval_internal_direct_eval_with_custom_functions(evaluator, registry, text);
    ce_free(text);
    return result;
}

WERKS_EXPREVAL_TYPE werks_expreval_evaluate_expression_with_custom_functions(werks_expreval_dt* evaluator, const werks_expreval_custom_function_dt* registry, const char* expression) {
    return both_assigned(evaluator, registry) && has_content(expression) ?
        werks_expreval_internal_evaluate_with_custom_functions(evaluator, registry, expression) : WERKS_EXPREVAL_NAN;
}

