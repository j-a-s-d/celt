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
    if (**expr == '(') {
        (*expr)++;
        if (**expr == CHARS_NULL) {
            evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
            return WERKS_EXPREVAL_NAN;
        }
        result = parse_expression(evaluator);
        if (evaluator->error == WERKS_EXPREVAL_ERROR_NONE) {
            if (**expr != ')') {
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
        while (isalnum(**expr) || **expr == '_') {
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
        while (**expr == '*' || **expr == '/') {
            char op = **expr;
            (*expr)++;
            if (**expr == CHARS_NULL) {
                evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
                return WERKS_EXPREVAL_NAN;
            }
            WERKS_EXPREVAL_TYPE factor = parse_factor(evaluator);
            if (evaluator->error == WERKS_EXPREVAL_ERROR_NONE) {
                if (op == '*') {
                    result *= factor;
                } else if (op == '/') {
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
        while (**expr == '+' || **expr == '-') {
            char op = **expr;
            (*expr)++;
            if (**expr == CHARS_NULL) {
                evaluator->error = WERKS_EXPREVAL_ERROR_EXPRESSION;
                return WERKS_EXPREVAL_NAN;
            }
            WERKS_EXPREVAL_TYPE term = parse_term(evaluator);
            if (evaluator->error == WERKS_EXPREVAL_ERROR_NONE) {
                if (op == '+') {
                    result += term;
                } else if (op == '-') {
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

void werks_expreval_expressions_list_destroy(werks_expreval_expressions_list_dt* const list) {
    if (list == NULL) return;
    PTRHOLDER_REVERSE_EACH_CASTED(list->expressions_entries, werks_expreval_expressions_entry_dt, entry, {
        remove_entry(list->expressions_entries, entry);
    });
    kewl_ptrholder_destroy(list->expressions_entries);
    free(list);
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

