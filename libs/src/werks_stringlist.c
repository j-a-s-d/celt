/**
 * werks_stringlist: general-purpose string list
 */

#include "werks_stringlist.h"

struct WERKS_STRINGLIST_ALIGNMENT werks_stringlist_dt {
    kewl_component_dt* component_instance;
    // array
    char** strings;
    // dimensions
    ssize_t size;
    ssize_t capacity;
    float capacity_grow_factor;
    float capacity_grow_padding;
    // events
    werks_stringlist_on_before_read_from_file_handler_fn on_before_read_from_file;
    werks_stringlist_on_before_write_to_file_handler_fn on_before_write_to_file;
    // flags
    bool frozen;
};

static inline void reset_dimensions(werks_stringlist_dt* const sl, ssize_t initial_capacity) {
    sl->size = 0;
    sl->capacity = initial_capacity;
    sl->capacity_grow_factor = WERKS_STRINGLIST_GROW_FACTOR;
    sl->capacity_grow_padding = WERKS_STRINGLIST_GROW_PADDING;
}

werks_stringlist_dt* werks_stringlist_create(ssize_t initial_capacity) {
    if (initial_capacity <= 0) return NULL;
    RET_MALLOC(werks_stringlist_dt, {
        result->strings = TYPE_MALLOC(char*, initial_capacity);
        if (result->strings == NULL) {
            ce_free(result);
            return NULL;
        }
        reset_dimensions(result, initial_capacity);
        result->on_before_read_from_file = NULL;
        result->on_before_write_to_file = NULL;
        result->frozen = false;
        result->component_instance = kewl_component_create(result, WERKS_STRINGLIST_TYPE_NAME);
    });
}

static inline bool is_dead(werks_stringlist_dt* const sl) {
    return sl == NULL || sl->strings == NULL;
}

static inline bool has_items(werks_stringlist_dt* const sl) {
    return sl->size > 0;
}

static inline bool is_oob(werks_stringlist_dt* const sl, ssize_t index) {
    return index < 0 || index >= sl->size;
}

void werks_stringlist_destroy(werks_stringlist_dt* const sl) {
    if (sl == NULL) return;
    if (assigned(sl->strings)) {
        for (ssize_t i = 0; i < sl->size; i++)
            ce_free(sl->strings[i]);
        ce_free(sl->strings);
        sl->strings = NULL;
    }
    reset_dimensions(sl, 0);
    kewl_component_destroy(sl->component_instance);
    sl->component_instance = NULL;
    ce_free(sl);
}

const kewl_component_dt* werks_stringlist_get_component(werks_stringlist_dt* const sl) {
    return sl == NULL ? NULL : sl->component_instance;
}

bool werks_stringlist_is_frozen(werks_stringlist_dt* const sl) {
    return is_dead(sl) ? 0 : sl->frozen;
}

void werks_stringlist_freeze(werks_stringlist_dt* const sl) {
    if (!is_dead(sl)) sl->frozen = true;
}

void werks_stringlist_unfreeze(werks_stringlist_dt* const sl) {
    if (!is_dead(sl)) sl->frozen = false;
}

ssize_t werks_stringlist_get_size(werks_stringlist_dt* const sl) {
    return is_dead(sl) ? 0 : sl->size;
}

ssize_t werks_stringlist_get_capacity(werks_stringlist_dt* const sl) {
    return is_dead(sl) ? 0 : sl->capacity;
}

float werks_stringlist_get_capacity_grow_factor(werks_stringlist_dt* const sl) {
    return sl == NULL ? 0.0f : sl->capacity_grow_factor;
}

float werks_stringlist_get_capacity_grow_padding(werks_stringlist_dt* const sl) {
    return sl == NULL ? 0.0f : sl->capacity_grow_padding;
}

void werks_stringlist_set_capacity_grow_factor(werks_stringlist_dt* const sl, float factor) {
    if (assigned(sl)) sl->capacity_grow_factor = factor;
}

void werks_stringlist_set_capacity_grow_padding(werks_stringlist_dt* const sl, float padding) {
    if (assigned(sl)) sl->capacity_grow_padding = padding;
}

static bool set_capacity(werks_stringlist_dt* const sl, ssize_t new_capacity)  {
    if (sl->capacity != new_capacity) {
        sl->capacity = new_capacity;
        char** tmp = TYPE_REALLOC(sl->strings, char*, sl->capacity);
        if (!tmp) {
            sl->size = 0;
            sl->capacity = 0;
            return false;
        }
        sl->strings = tmp;
    }
    return true;
}

bool werks_stringlist_grow_capacity(werks_stringlist_dt* const sl, float factor, float padding) {
    if (is_dead(sl)) return false;
    ssize_t new_capacity = (sl->capacity * factor) + padding;
    if (sl->capacity > new_capacity) new_capacity = sl->capacity + 1; // ensure growth
    return set_capacity(sl, new_capacity);
}

void werks_stringlist_pack(werks_stringlist_dt* const sl) {
    if (!is_dead(sl)) UNUSED(set_capacity(sl, sl->size));
}

werks_stringlist_on_before_read_from_file_handler_fn werks_stringlist_get_on_before_read_from_file(werks_stringlist_dt* const sl) {
    return assigned(sl) ? sl->on_before_read_from_file : NULL;
}

void werks_stringlist_set_on_before_read_from_file(werks_stringlist_dt* const sl, werks_stringlist_on_before_read_from_file_handler_fn handler) {
    if (assigned(sl)) sl->on_before_read_from_file = handler;
}

werks_stringlist_on_before_write_to_file_handler_fn werks_stringlist_get_on_before_write_to_file(werks_stringlist_dt* const sl) {
    return assigned(sl) ? sl->on_before_write_to_file : NULL;
}

void werks_stringlist_set_on_before_write_to_file(werks_stringlist_dt* const sl, werks_stringlist_on_before_write_to_file_handler_fn handler) {
    if (assigned(sl)) sl->on_before_write_to_file = handler;
}

static bool forget_string(werks_stringlist_dt* const sl, ssize_t index) {
    if (index != --sl->size) // move backwards
        memmove(sl->strings + index, sl->strings + (index + 1), (sl->size - index) * sizeof(*sl->strings));
    return true;
}

bool werks_stringlist_delete(werks_stringlist_dt* const sl, ssize_t index) {
    if (!is_dead(sl) && has_items(sl) && !is_oob(sl, index) && !sl->frozen) {
        ce_free(sl->strings[index]);
        return forget_string(sl, index);
    }
    return false;
}

void werks_stringlist_clear(werks_stringlist_dt* const sl) {
    if (!is_dead(sl) && has_items(sl) && !sl->frozen)
        for (ssize_t i = sl->size - 1; i >= 0; i--) {
            ce_free(sl->strings[i]);
            UNUSED(forget_string(sl, i));
        }
}

static inline bool add_string(werks_stringlist_dt* const sl, const char* value) {
    if (sl->size == sl->capacity)
        if (!werks_stringlist_grow_capacity(sl, sl->capacity_grow_factor, sl->capacity_grow_padding)) return false;
    sl->strings[sl->size++] = strdup(value);
    return true;
}

bool werks_stringlist_append(werks_stringlist_dt* const sl, const char* value) {
    return !is_dead(sl) && assigned(value) && !sl->frozen && add_string(sl, value);
}

static bool insert_string(werks_stringlist_dt* const sl, const char* value, ssize_t index) {
    if (sl->size == sl->capacity)
        if (!werks_stringlist_grow_capacity(sl, sl->capacity_grow_factor, sl->capacity_grow_padding)) return false;
    if (index < sl->size) // move forward
        memmove(sl->strings + (index + 1), sl->strings + index, (sl->size - index) * sizeof(*sl->strings));
    sl->strings[index] = strdup(value);
    sl->size++;
    return true;
}

bool werks_stringlist_insert(werks_stringlist_dt* const sl, const char* value, ssize_t index) {
    if (is_dead(sl) || value == NULL || index < 0 || index > sl->size || sl->frozen) return false;
    return insert_string(sl, value, index);
}

static inline bool compare_string(werks_stringlist_dt* const sl, ssize_t index, const char* value) {
    return strcmp(sl->strings[index], value) == 0;
}

static bool has_string(werks_stringlist_dt* const sl, const char* value) {
    for (ssize_t i = 0; i < sl->size; i++)
        if (compare_string(sl, i, value))
            return true;
    return false;
}

bool werks_stringlist_has(werks_stringlist_dt* const sl, const char* value) {
    return !is_dead(sl) && assigned(value) && has_items(sl) &&
        has_string(sl, value);
}

ssize_t werks_stringlist_index_of(werks_stringlist_dt* const sl, const char* value) {
    if (!is_dead(sl) && assigned(value) && has_items(sl))
        for (ssize_t i = 0; i < sl->size; i++)
            if (compare_string(sl, i, value))
                return i;
    return -1;
}

ssize_t werks_stringlist_last_index_of(werks_stringlist_dt* const sl, const char* value) {
    if (!is_dead(sl) && assigned(value) && has_items(sl))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (compare_string(sl, i, value))
                return i;
    return -1;
}

bool werks_stringlist_is_empty(werks_stringlist_dt* const sl) {
    return !is_dead(sl) && sl->size == 0;
}

const char* werks_stringlist_get(werks_stringlist_dt* const sl, ssize_t index) {
    return is_dead(sl) || is_oob(sl, index) ? NULL : sl->strings[index];
}

static inline void replace_string(werks_stringlist_dt* const sl, ssize_t index, const char* value) {
    ce_free(sl->strings[index]);
    sl->strings[index] = strdup(value);
}

bool werks_stringlist_set(werks_stringlist_dt* const sl, ssize_t index, const char* value) {
    if (is_dead(sl) || value == NULL || is_oob(sl, index) || sl->frozen) return false;
    replace_string(sl, index, value);
    return true;
}

bool werks_stringlist_formatted_set(werks_stringlist_dt* const sl, ssize_t index, const char* fmt, ...) {
    if (is_dead(sl) || fmt == NULL || is_oob(sl, index) || sl->frozen) return false;
    va_list args;
    va_start(args, fmt);
    ssize_t size = get_string_format_size(fmt, args);
    if (size < 0) {
        va_end(args);
        return false; // encoding error
    }
    char* value = perform_string_format(size, fmt, args);
    replace_string(sl, index, value);
    va_end(args);
    ce_free(value);
    return true;
}

static inline char* extract_string(werks_stringlist_dt* const sl, ssize_t index) {
    char* result = sl->strings[index];
    UNUSED(forget_string(sl, index));
    return result;
}

char* werks_stringlist_take(werks_stringlist_dt* const sl, ssize_t index) {
    if (is_dead(sl) || sl->frozen || !has_items(sl) || is_oob(sl, index)) return NULL;
    return extract_string(sl, index);
}

char* werks_stringlist_take_last(werks_stringlist_dt* const sl) {
    if (is_dead(sl) || sl->frozen || !has_items(sl)) return NULL;
    return extract_string(sl, sl->size - 1);
}

bool werks_stringlist_delete_last(werks_stringlist_dt* const sl) {
    if (is_dead(sl) || sl->frozen || !has_items(sl)) return false;
    ce_free(sl->strings[sl->size - 1]);
    return forget_string(sl, sl->size - 1);
}

bool werks_stringlist_drop_last(werks_stringlist_dt* const sl, ssize_t amount) {
    if (is_dead(sl) || sl->frozen || !has_items(sl)) return false;
    LOOP_TIMES(amount)
        if (sl->size > 0) {
            ce_free(sl->strings[sl->size - 1]);
            UNUSED(forget_string(sl, sl->size - 1));
        }
    return true;
}

bool werks_stringlist_drop_first(werks_stringlist_dt* const sl, ssize_t amount) {
    if (is_dead(sl) || sl->frozen || !has_items(sl)) return false;
    LOOP_TIMES(amount)
        if (sl->size > 0) {
            ce_free(sl->strings[0]);
            UNUSED(forget_string(sl, 0));
        }
    return true;
}

bool werks_stringlist_remove_once(werks_stringlist_dt* const sl, const char* value) {
    if (!is_dead(sl) && assigned(value) && has_items(sl) && !sl->frozen)
        for (ssize_t i = 0; i < sl->size; i++)
            if (compare_string(sl, i, value)) {
                ce_free(sl->strings[i]);
                return forget_string(sl, i);
            }
    return false;
}

static inline bool erase_string(werks_stringlist_dt* const sl, const char* value) {
    bool result = false;
    for (ssize_t i = sl->size - 1; i >= 0; i--)
        if (compare_string(sl, i, value)) {
            ce_free(sl->strings[i]);
            result |= forget_string(sl, i);
        }
    return result;
}

bool werks_stringlist_remove_all(werks_stringlist_dt* const sl, const char* value) {
    return (!is_dead(sl) && assigned(value) && has_items(sl) && !sl->frozen)
        && erase_string(sl, value);
}

bool werks_stringlist_remove_prefixed(werks_stringlist_dt* const sl, const char* prefix) {
    bool result = false;
    if (!is_dead(sl) && has_items(sl) && has_content(prefix))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (starts_with(sl->strings[i], prefix)) {
                ce_free(sl->strings[i]);
                UNUSED(forget_string(sl, i));
                result = true;
            }
    return result;
}

bool werks_stringlist_remove_not_prefixed(werks_stringlist_dt* const sl, const char* prefix) {
    bool result = false;
    if (!is_dead(sl) && has_items(sl) && has_content(prefix))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (!starts_with(sl->strings[i], prefix)) {
                ce_free(sl->strings[i]);
                UNUSED(forget_string(sl, i));
                result = true;
            }
    return result;
}

bool werks_stringlist_remove_suffixed(werks_stringlist_dt* const sl, const char* suffix) {
    bool result = false;
    if (!is_dead(sl) && has_items(sl) && has_content(suffix))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (ends_with(sl->strings[i], suffix)) {
                ce_free(sl->strings[i]);
                UNUSED(forget_string(sl, i));
                result = true;
            }
    return result;
}

bool werks_stringlist_remove_not_suffixed(werks_stringlist_dt* const sl, const char* suffix) {
    bool result = false;
    if (!is_dead(sl) && has_items(sl) && has_content(suffix))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (!ends_with(sl->strings[i], suffix)) {
                ce_free(sl->strings[i]);
                UNUSED(forget_string(sl, i));
                result = true;
            }
    return result;
}

bool werks_stringlist_remove_containing(werks_stringlist_dt* const sl, const char* text) {
    bool result = false;
    if (!is_dead(sl) && has_items(sl) && has_content(text))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (contains_string(sl->strings[i], text)) {
                ce_free(sl->strings[i]);
                UNUSED(forget_string(sl, i));
                result = true;
            }
    return result;
}

bool werks_stringlist_remove_not_containing(werks_stringlist_dt* const sl, const char* text) {
    bool result = false;
    if (!is_dead(sl) && has_items(sl) && has_content(text))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (!contains_string(sl->strings[i], text)) {
                ce_free(sl->strings[i]);
                UNUSED(forget_string(sl, i));
                result = true;
            }
    return result;
}

static inline bool insert_strings(werks_stringlist_dt* sl, werks_stringlist_dt* ns, ssize_t index) {
    for (ssize_t i = ns->size - 1; i >= 0; i--)
        UNUSED(insert_string(sl, ns->strings[i], index));
    return true;
}

bool werks_stringlist_insert_all(werks_stringlist_dt* const sl, werks_stringlist_dt* const ns, ssize_t index) {
    if (ptreq(sl, ns) || is_dead(sl) || is_dead(ns) || !has_items(ns) || is_oob(sl, index) || sl->frozen) return false;
    return insert_strings(sl, ns, index);
}

bool werks_stringlist_append_all(werks_stringlist_dt* const sl, werks_stringlist_dt* const ns) {
    if (ptreq(sl, ns) || is_dead(sl) || is_dead(ns) || !has_items(ns) || sl->frozen) return false;
    for (ssize_t i = 0; i < ns->size; i++)
        UNUSED(add_string(sl, ns->strings[i]));
    return true;
}

bool werks_stringlist_prepend_all(werks_stringlist_dt* const sl, werks_stringlist_dt* const ns) {
    if (ptreq(sl, ns) || is_dead(sl) || is_dead(ns) || !has_items(ns) || sl->frozen) return false;
    return insert_strings(sl, ns, 0);
}

bool werks_stringlist_prepend(werks_stringlist_dt* const sl, const char* value) {
    return werks_stringlist_insert(sl, value, 0);
}

bool werks_stringlist_formatted_append(werks_stringlist_dt* const sl, const char* fmt, ...) {
    if (is_dead(sl) || fmt == NULL || sl->frozen) return false;
    va_list args;
    va_start(args, fmt);
    ssize_t size = get_string_format_size(fmt, args);
    if (size < 0) {
        va_end(args);
        return false; // encoding error
    }
    char* value = perform_string_format(size, fmt, args);
    bool result = add_string(sl, value);
    va_end(args);
    ce_free(value);
    return result;
}

bool werks_stringlist_formatted_prepend(werks_stringlist_dt* const sl, const char* fmt, ...) {
    if (is_dead(sl) || fmt == NULL || sl->frozen) return false;
    va_list args;
    va_start(args, fmt);
    ssize_t size = get_string_format_size(fmt, args);
    if (size < 0) {
        va_end(args);
        return false; // encoding error
    }
    char* value = perform_string_format(size, fmt, args);
    bool result = insert_string(sl, value, 0);
    va_end(args);
    ce_free(value);
    return result;
}

bool werks_stringlist_swap(werks_stringlist_dt* const sl, ssize_t index1, ssize_t index2) {
    if (is_dead(sl) || is_oob(sl, index1) || is_oob(sl, index2) || sl->frozen) return false;
    char* tmp1 = sl->strings[index1];
    char* tmp2 = sl->strings[index2];
    if (tmp1 == NULL || tmp2 == NULL) return false;
    sl->strings[index1] = tmp2;
    sl->strings[index2] = tmp1;
    return true;
}

bool werks_stringlist_move_first(werks_stringlist_dt* const sl, ssize_t index) {
    if (is_dead(sl) || is_oob(sl, index) || sl->frozen) return false;
    if (index == 0) return true;
    char* s = extract_string(sl, index);
    if (s == NULL) return false;
    bool result = werks_stringlist_insert(sl, s, 0);
    ce_free(s);
    return result;
}

bool werks_stringlist_move_up(werks_stringlist_dt* const sl, ssize_t index) {
    if (is_dead(sl) || is_oob(sl, index) || sl->frozen) return false;
    if (index == 0) return true;
    char* s = extract_string(sl, index);
    if (s == NULL) return false;
    bool result = werks_stringlist_insert(sl, s, index - 1);
    ce_free(s);
    return result;
}

bool werks_stringlist_move_down(werks_stringlist_dt* const sl, ssize_t index) {
    if (is_dead(sl) || sl->frozen || index < 0 || index + 1 > sl->size - 1) return false;
    if (index == sl->size - 1) return true;
    char* s = extract_string(sl, index);
    if (s == NULL) return false;
    bool result = werks_stringlist_insert(sl, s, index + 1);
    ce_free(s);
    return result;
}

bool werks_stringlist_move_last(werks_stringlist_dt* const sl, ssize_t index) {
    if (is_dead(sl) || is_oob(sl, index) || sl->frozen) return false;
    if (index == sl->size - 1) return true;
    char* s = extract_string(sl, index);
    if (s == NULL) return false;
    bool result = add_string(sl, s);
    ce_free(s);
    return result;
}

bool werks_stringlist_reverse(werks_stringlist_dt* const sl) {
    bool result = !is_dead(sl) && has_items(sl) && !sl->frozen;
    if (result) {
        ssize_t z = sl->size;
        werks_stringlist_dt* t = werks_stringlist_create(z);
        result = !is_dead(t);
        if (result) {
            for (ssize_t i = 0; i < z; i++) {
                char* s = extract_string(sl, 0);
                result = insert_string(t, s, 0);
                ce_free(s);
                if (!result) break;
            }
            if (result)
                for (ssize_t i = 0; i < z; i++) {
                    result = add_string(sl, werks_stringlist_get(t, i));
                    if (!result) break;
                }
            werks_stringlist_destroy(t);
        }
    }
    return result;
}

char* werks_stringlist_join(werks_stringlist_dt* const sl, const char* separator) {
    return is_dead(sl) ? NULL : string_array_join_range(
        sl->size, (const char**)sl->strings, 0, sl->size - 1, separator
    );
}

werks_stringlist_dt* werks_stringlist_split(const char* value, const char* separator) {
    if (value == NULL || separator == NULL) return NULL;
    werks_stringlist_dt* result = werks_stringlist_make();
    if (!is_dead(result)) {
        char* value_copy = strdup(value);
        if (assigned(value_copy)) {
            char* token = strtok(value_copy, separator);
            if (token == NULL && strlen(value) == strlen(value_copy)) {
                UNUSED(add_string(result, value));
            } else while (assigned(token)) { // loop
                UNUSED(add_string(result, token));
                token = strtok(NULL, separator);
            }
            ce_free(value_copy);
        }
    }
    return result;
}

void werks_stringlist_loop(werks_stringlist_dt* const sl, werks_stringlist_loop_handler_fn handler) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl))
        for (ssize_t i = 0; i < sl->size; i++)
            handler(sl, i, werks_stringlist_get(sl, i)); // use the getter since the list can be manipulated outside
}

void werks_stringlist_reverse_loop(werks_stringlist_dt* const sl, werks_stringlist_loop_handler_fn handler) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            handler(sl, i, werks_stringlist_get(sl, i)); // use the getter since the list can be manipulated outside
}

void werks_stringlist_loop_prefixed(werks_stringlist_dt* const sl, const char* prefix, werks_stringlist_loop_handler_fn handler) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && has_content(prefix))
        for (ssize_t i = 0; i < sl->size; i++) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            if (starts_with(o, prefix))
                handler(sl, i, o);
        }
}

void werks_stringlist_reverse_loop_prefixed(werks_stringlist_dt* const sl, const char* prefix, werks_stringlist_loop_handler_fn handler) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && has_content(prefix))
        for (ssize_t i = sl->size - 1; i >= 0; i--) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            if (starts_with(o, prefix))
                handler(sl, i, o);
        }
}

void werks_stringlist_loop_suffixed(werks_stringlist_dt* const sl, const char* suffix, werks_stringlist_loop_handler_fn handler) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && has_content(suffix))
        for (ssize_t i = 0; i < sl->size; i++) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            if (ends_with(o, suffix))
                handler(sl, i, o);
        }
}

void werks_stringlist_reverse_loop_suffixed(werks_stringlist_dt* const sl, const char* suffix, werks_stringlist_loop_handler_fn handler) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && has_content(suffix))
        for (ssize_t i = sl->size - 1; i >= 0; i--) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            if (ends_with(o, suffix))
                handler(sl, i, o);
        }
}

void werks_stringlist_loop_from_to(werks_stringlist_dt* const sl, ssize_t from_index, ssize_t to_index, werks_stringlist_loop_handler_fn handler) {
    if (is_dead(sl) || handler == NULL || !has_items(sl) || is_oob(sl, from_index) || is_oob(sl, to_index) || sl->frozen) return;
    for (ssize_t i = from_index; i <= to_index; i++)
        handler(sl, i, werks_stringlist_get(sl, i)); // use the getter since the list can be manipulated outside
}

void werks_stringlist_loop_from_to_with_reference(werks_stringlist_dt* const sl, ssize_t from_index, ssize_t to_index, werks_stringlist_loop_with_reference_handler_fn handler, void* ref) {
    if (is_dead(sl) || handler == NULL || !has_items(sl) || is_oob(sl, from_index) || is_oob(sl, to_index) || sl->frozen) return;
    for (ssize_t i = from_index; i <= to_index; i++)
        handler(sl, i, werks_stringlist_get(sl, i), ref); // use the getter since the list can be manipulated outside
}

void werks_stringlist_loop_with_reference(werks_stringlist_dt* const sl, werks_stringlist_loop_with_reference_handler_fn handler, void* ref) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl))
        for (ssize_t i = 0; i < sl->size; i++)
            handler(sl, i, werks_stringlist_get(sl, i), ref); // use the getter since the list can be manipulated outside
}

void werks_stringlist_reverse_loop_with_reference(werks_stringlist_dt* const sl, werks_stringlist_loop_with_reference_handler_fn handler, void* ref) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            handler(sl, i, werks_stringlist_get(sl, i), ref); // use the getter since the list can be manipulated outside
}

void werks_stringlist_loop_prefixed_with_reference(werks_stringlist_dt* const sl, const char* prefix, werks_stringlist_loop_with_reference_handler_fn handler, void* ref) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && has_content(prefix))
        for (ssize_t i = 0; i < sl->size; i++) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            if (starts_with(o, prefix))
                handler(sl, i, o, ref);
        }
}

void werks_stringlist_reverse_loop_prefixed_with_reference(werks_stringlist_dt* const sl, const char* prefix, werks_stringlist_loop_with_reference_handler_fn handler, void* ref) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && has_content(prefix))
        for (ssize_t i = sl->size - 1; i >= 0; i--) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            if (starts_with(o, prefix))
                handler(sl, i, o, ref);
        }
}

void werks_stringlist_loop_suffixed_with_reference(werks_stringlist_dt* const sl, const char* suffix, werks_stringlist_loop_with_reference_handler_fn handler, void* ref) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && has_content(suffix))
        for (ssize_t i = 0; i < sl->size; i++) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            if (ends_with(o, suffix))
                handler(sl, i, o, ref);
        }
}

void werks_stringlist_reverse_loop_suffixed_with_reference(werks_stringlist_dt* const sl, const char* suffix, werks_stringlist_loop_with_reference_handler_fn handler, void* ref) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && has_content(suffix))
        for (ssize_t i = sl->size - 1; i >= 0; i--) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            if (ends_with(o, suffix))
                handler(sl, i, o, ref);
        }
}

void werks_stringlist_reverse_loop_from_to(werks_stringlist_dt* const sl, ssize_t from_index, ssize_t to_index, werks_stringlist_loop_handler_fn handler) {
    if (is_dead(sl) || handler == NULL || !has_items(sl) || is_oob(sl, from_index) || is_oob(sl, to_index) || sl->frozen) return;
    for (ssize_t i = to_index; i >= from_index; i--)
        handler(sl, i, werks_stringlist_get(sl, i)); // use the getter since the list can be manipulated outside
}

void werks_stringlist_reverse_loop_from_to_with_reference(werks_stringlist_dt* const sl, ssize_t from_index, ssize_t to_index, werks_stringlist_loop_with_reference_handler_fn handler, void* ref) {
    if (is_dead(sl) || handler == NULL || !has_items(sl) || is_oob(sl, from_index) || is_oob(sl, to_index) || sl->frozen) return;
    for (ssize_t i = to_index; i >= from_index; i--)
        handler(sl, i, werks_stringlist_get(sl, i), ref); // use the getter since the list can be manipulated outside
}

void werks_stringlist_treat(werks_stringlist_dt* const sl, werks_stringlist_treat_handler_fn handler) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && !sl->frozen)
        for (ssize_t i = 0; i < sl->size; i++) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            char* tmp = handler(sl, i, o);
            if (o == tmp) // leave if the string returned is the original
                continue;
            UNUSED(werks_stringlist_set(sl, i, tmp));
            ce_free(tmp);
        }
}

void werks_stringlist_treat_with_reference(werks_stringlist_dt* const sl, werks_stringlist_treat_with_reference_handler_fn handler, void* reference) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && !sl->frozen)
        for (ssize_t i = 0; i < sl->size; i++) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            char* tmp = handler(sl, i, o, reference);
            if (o == tmp) // leave if the string returned is the original
                continue;
            UNUSED(werks_stringlist_set(sl, i, tmp));
            ce_free(tmp);
        }
}

void werks_stringlist_reverse_treat(werks_stringlist_dt* const sl, werks_stringlist_treat_handler_fn handler) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && !sl->frozen)
        for (ssize_t i = sl->size - 1; i >= 0; i--) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            char* tmp = handler(sl, i, o);
            if (o == tmp) // leave if the string returned is the original
                continue;
            UNUSED(werks_stringlist_set(sl, i, tmp));
            ce_free(tmp);
        }
}

void werks_stringlist_reverse_treat_with_reference(werks_stringlist_dt* const sl, werks_stringlist_treat_with_reference_handler_fn handler, void* reference) {
    if (!is_dead(sl) && assigned(handler) && has_items(sl) && !sl->frozen)
        for (ssize_t i = sl->size - 1; i >= 0; i--) {
            const char* o = werks_stringlist_get(sl, i); // use the getter since the list can be manipulated outside
            char* tmp = handler(sl, i, o, reference);
            if (o == tmp) // leave if the string returned is the original
                continue;
            UNUSED(werks_stringlist_set(sl, i, tmp));
            ce_free(tmp);
        }
}

static void werks_stringlist_insertion_callback(const char* str, const void* ref) {
    UNUSED(werks_stringlist_append((werks_stringlist_dt*)ref, str));
}

bool werks_stringlist_read_from_string(werks_stringlist_dt* const sl, const char* data, const char* separator) {
    return assigned(sl) && !sl->frozen && has_content(data) && has_content(separator) &&
        parse_separated_values_with_reference(data, separator, werks_stringlist_insertion_callback, sl);
}

char* werks_stringlist_write_to_string(werks_stringlist_dt* const sl, char separator) {
    const char* sep = strchar(separator);
    return werks_stringlist_join(sl, sep);
}

bool werks_stringlist_read_from_file(werks_stringlist_dt* const sl, const char* filename) {
    if (is_dead(sl) || sl->frozen || filename == NULL) return false;
    if (assigned(sl->on_before_read_from_file))
        if (!sl->on_before_read_from_file(sl, filename))
            return false;
    FILE* file = fopen(filename, "r");
    if (file == NULL) return false;
    char* line;
    while (assigned((line = read_line_from_stream(file)))) {
        UNUSED(add_string(sl, line));
        ce_free(line);
    }
    fclose(file);
    return true;
}

werks_stringlist_dt* werks_stringlist_load_from_file(const char* filename) {
    if (filename == NULL) return NULL;
    werks_stringlist_dt* result = werks_stringlist_make();
    if (!werks_stringlist_read_from_file(result, filename)) {
        werks_stringlist_destroy(result);
        return NULL;
    }
    return result;
}

bool werks_stringlist_save_to_file(werks_stringlist_dt* const sl, const char* filename) {
    if (is_dead(sl) || filename == NULL) return false;
    if (assigned(sl->on_before_write_to_file))
        if (!sl->on_before_write_to_file(sl, filename))
            return false;
    FILE* file = fopen(filename, "w");
    if (file == NULL) return false;
    char* content = werks_stringlist_join(sl, STRINGS_LF);
    fwrite(content, 1, strlen(content), file);
    fwrite(STRINGS_LF, 1, 1, file);
    fflush(file);
    fclose(file);
    ce_free(content);
    return true;
}

bool werks_stringlist_append_to_file(werks_stringlist_dt* const sl, const char* filename) {
    if (is_dead(sl) || filename == NULL) return false;
    if (assigned(sl->on_before_write_to_file))
        if (!sl->on_before_write_to_file(sl, filename))
            return false;
    FILE* file = fopen(filename, "a");
    if (file == NULL) return false;
    char* content = werks_stringlist_join(sl, STRINGS_LF);
    fwrite(content, 1, strlen(content), file);
    fwrite(STRINGS_LF, 1, 1, file);
    fflush(file);
    fclose(file);
    ce_free(content);
    return true;
}

// NOTE: in very large lists this is faster than using count_empties == 0
bool werks_stringlist_has_empties(werks_stringlist_dt* const sl) {
    if (!is_dead(sl) && has_items(sl))
        for (ssize_t i = 0; i < sl->size; i++)
            if (strlen(sl->strings[i]) == 0)
                return true;
    return false;
}

ssize_t werks_stringlist_count_empties(werks_stringlist_dt* const sl) {
    if (is_dead(sl)) return -1;
    ssize_t result = 0;
    for (ssize_t i = 0; i < sl->size; i++)
        if (strlen(sl->strings[i]) == 0)
            result++;
    return result;
}

ssize_t werks_stringlist_count_not_empties(werks_stringlist_dt* const sl) {
    if (is_dead(sl)) return -1;
    ssize_t result = 0;
    for (ssize_t i = 0; i < sl->size; i++)
        if (strlen(sl->strings[i]) > 0)
            result++;
    return result;
}

bool werks_stringlist_remove_empties(werks_stringlist_dt* const sl) {
    if (is_dead(sl) || sl->frozen || !has_items(sl)) return false;
    for (ssize_t i = sl->size - 1; i > -1; i--)
        if (strlen(sl->strings[i]) == 0) {
            ce_free(sl->strings[i]);
            UNUSED(forget_string(sl, i));
        }
    return true;
}

// NOTE: in very large lists this is faster than using count_duplicates == 0
bool werks_stringlist_has_duplicates(werks_stringlist_dt* const sl) {
    if (is_dead(sl) || !has_items(sl)) return false;
    for (ssize_t i = 0; i < sl->size - 1; i++) {
        const char* v = sl->strings[i];
        for (ssize_t j = i + 1; j < sl->size; j++)
            if (strcmp(v, sl->strings[j]) == 0)
                return true;
    }
    return false;
}

ssize_t werks_stringlist_count_duplicates(werks_stringlist_dt* const sl) {
    if (is_dead(sl)) return -1;
    ssize_t result = 0;
    for (ssize_t i = 0; i < sl->size - 1; i++) {
        const char* v = sl->strings[i];
        for (ssize_t j = i + 1; j < sl->size; j++)
            if (strcmp(v, sl->strings[j]) == 0) {
                result++;
                break;
            }
    }
    return result;
}

bool werks_stringlist_remove_duplicates(werks_stringlist_dt* const sl) {
    if (is_dead(sl) || sl->frozen || !has_items(sl)) return false;
    for (ssize_t i = 0; i < sl->size - 1; i++) {
        const char* v = sl->strings[i];
        for (ssize_t j = sl->size - 1; j > i; j--)
            if (strcmp(v, sl->strings[j]) == 0) {
                ce_free(sl->strings[j]);
                UNUSED(forget_string(sl, j));
            }
    }
    return true;
}

werks_stringlist_dt* werks_stringlist_list_duplicates(werks_stringlist_dt* const sl) {
    if (is_dead(sl)) return NULL;
    werks_stringlist_dt* result = werks_stringlist_make();
    if (!is_dead(result))
        for (ssize_t i = 0; i < sl->size - 1; i++) {
            const char* v = sl->strings[i];
            for (ssize_t j = i + 1; j < sl->size; j++)
                if (strcmp(v, sl->strings[j]) == 0)
                    UNUSED(add_string(result, v));
        }
    return result;
}

werks_stringlist_dt* werks_stringlist_clone(werks_stringlist_dt* const sl) {
    if (is_dead(sl)) return NULL;
    werks_stringlist_dt* result = werks_stringlist_create(sl->size);
    if (!is_dead(result))
        for (ssize_t i = 0; i < sl->size; i++)
            UNUSED(add_string(result, sl->strings[i]));
    return result;
}

werks_stringlist_dt* werks_stringlist_concatenate(werks_stringlist_dt* sl1, werks_stringlist_dt* sl2) {
    if (is_dead(sl1) || is_dead(sl2)) return NULL;
    werks_stringlist_dt* result = werks_stringlist_create(sl1->size + sl2->size);
    if (!is_dead(result)) {
        for (ssize_t i = 0; i < sl1->size; i++)
            UNUSED(add_string(result, sl1->strings[i]));
        for (ssize_t i = 0; i < sl2->size; i++)
            UNUSED(add_string(result, sl2->strings[i]));
    }
    return result;
}

ssize_t werks_stringlist_count_occurrences(werks_stringlist_dt* const sl, const char* value) {
    if (!is_dead(sl) && has_items(sl) && has_content(value))
        for (ssize_t i = 0; i < sl->size; i++)
            if (strcmp(sl->strings[i], value) == 0)
                return true;
    return false;
}

ssize_t werks_stringlist_count_prefixed(werks_stringlist_dt* const sl, const char* prefix) {
    if (!is_dead(sl) && has_items(sl) && has_content(prefix))
        for (ssize_t i = 0; i < sl->size; i++)
            if (starts_with(sl->strings[i], prefix))
                return true;
    return false;
}

ssize_t werks_stringlist_count_suffixed(werks_stringlist_dt* const sl, const char* suffix) {
    if (!is_dead(sl) && has_items(sl) && has_content(suffix))
        for (ssize_t i = 0; i < sl->size; i++)
            if (ends_with(sl->strings[i], suffix))
                return true;
    return false;
}

static inline bool print_string(werks_stringlist_dt* const sl, ssize_t index, const char* format) {
    ssize_t sz = snprintf(NULL, 0, format, sl->strings[index]) + 1;
    char* sv = TYPE_MALLOC(char, sz);
    snprintf(sv, sz, format, sl->strings[index]);
    ce_free(sl->strings[index]);
    sl->strings[index] = sv;
    return true;
}

bool werks_stringlist_format(werks_stringlist_dt* const sl, ssize_t index, const char* format) {
    if (is_dead(sl) || sl->frozen || !has_items(sl) || format == NULL || is_oob(sl, index)) return false;
    return print_string(sl, index, format);
}

bool werks_stringlist_format_all(werks_stringlist_dt* const sl, const char* format) {
    if (is_dead(sl) || sl->frozen || !has_items(sl) || format == NULL) return false;
    for (ssize_t i = 0; i < sl->size; i++)
        UNUSED(print_string(sl, i, format));
    return true;
}

bool werks_stringlist_prefix(werks_stringlist_dt* const sl, ssize_t index, const char* prefix) {
    if (is_dead(sl) || !has_content(prefix) || !has_items(sl) || is_oob(sl, index) || sl->frozen) return false;
    char* tmp = strprepend(sl->strings[index], prefix);
    if (assigned(tmp)) {
        sl->strings[index] = tmp;
        return true;
    }
    return false;
}

bool werks_stringlist_prefix_all(werks_stringlist_dt* const sl, const char* prefix) {
    if (is_dead(sl) || sl->frozen || !has_items(sl) || !has_content(prefix)) return false;
    for (ssize_t i = 0; i < sl->size; i++) {
        char* tmp = strprepend(sl->strings[i], prefix);
        if (tmp == NULL) return false;
        sl->strings[i] = tmp;
    }
    return true;
}

bool werks_stringlist_suffix(werks_stringlist_dt* const sl, ssize_t index, const char* suffix) {
    if (is_dead(sl) || !has_content(suffix) || !has_items(sl) || is_oob(sl, index) || sl->frozen) return false;
    char* tmp = strappend(sl->strings[index], suffix);
    if (assigned(tmp)) {
        sl->strings[index] = tmp;
        return true;
    }
    return false;
}

bool werks_stringlist_suffix_all(werks_stringlist_dt* const sl, const char* suffix) {
    if (is_dead(sl) || sl->frozen || !has_items(sl) || !has_content(suffix)) return false;
    for (ssize_t i = 0; i < sl->size; i++) {
        char* tmp = strappend(sl->strings[i], suffix);
        if (tmp == NULL) return false;
        sl->strings[i] = tmp;
    }
    return true;
}

bool werks_stringlist_remove_all_containing_any(werks_stringlist_dt* const sl, werks_stringlist_dt* nl) {
    if (ptreq(sl, nl) || is_dead(sl) || is_dead(nl) || !has_items(nl) || sl->frozen) return false;
    bool result = false;
    for (ssize_t i = 0; i < nl->size; i++)
        if (has_content(nl->strings[i]))
            for (ssize_t h = sl->size - 1; h >= 0; h--)
                if (contains_string(sl->strings[h], nl->strings[i])) {
                    ce_free(sl->strings[h]);
                    UNUSED(forget_string(sl, h));
                    result = true;
                }
    return result;
}

bool werks_stringlist_remove_all_not_containing_any(werks_stringlist_dt* const sl, werks_stringlist_dt* nl) {
    if (ptreq(sl, nl) || is_dead(sl) || is_dead(nl) || !has_items(nl) || sl->frozen) return false;
    bool result = false;
    for (ssize_t h = sl->size - 1; h >= 0; h--) {
        bool keep = false;
        for (ssize_t i = 0; i < nl->size; i++)
            if (has_content(nl->strings[i]))
                if (contains_string(sl->strings[h], nl->strings[i])) {
                    keep = true;
                    break;
                }
        if (!keep) {
            ce_free(sl->strings[h]);
            UNUSED(forget_string(sl, h));
            result = true;
        }
    }
    return result;
}

bool werks_stringlist_exclude_all(werks_stringlist_dt* const sl, werks_stringlist_dt* const ns) {
    if (ptreq(sl, ns) || is_dead(sl) || is_dead(ns) || !has_items(ns) || sl->frozen) return false;
    for (ssize_t i = 0; i < ns->size; i++)
        if (has_string(sl, ns->strings[i]))
            UNUSED(erase_string(sl, ns->strings[i]));
    return true;
}

bool werks_stringlist_keep_all(werks_stringlist_dt* const sl, werks_stringlist_dt* const ns) {
    if (ptreq(sl, ns) || is_dead(sl) || is_dead(ns) || !has_items(ns) || sl->frozen) return false;
    bool result = false;
    for (ssize_t i = sl->size - 1; i >= 0; i--)
        if (!has_string(ns, sl->strings[i])) {
            ce_free(sl->strings[i]);
            result |= forget_string(sl, i);
        }
    return result;
}

bool werks_stringlist_include(werks_stringlist_dt* const sl, const char* value) {
    if (is_dead(sl) || sl->frozen || !assigned(value)) return false;
    return !has_string(sl, value) && add_string(sl, value);
}

bool werks_stringlist_include_all(werks_stringlist_dt* const sl, werks_stringlist_dt* const ns) {
    if (ptreq(sl, ns) || is_dead(sl) || is_dead(ns) || !has_items(ns) || sl->frozen) return false;
    for (ssize_t i = 0; i < ns->size; i++)
        if (!has_string(sl, ns->strings[i]))
            UNUSED(add_string(sl, ns->strings[i]));
    return true;
}

FUNC_ALIAS_IMPL(bool, werks_stringlist_push, (werks_stringlist_dt* const sl, const char* value), werks_stringlist_append);
FUNC_ALIAS_IMPL(char*, werks_stringlist_pop, (werks_stringlist_dt* const sl), werks_stringlist_take_last);

bool werks_stringlist_replace_first_occurrence(werks_stringlist_dt* const sl, const char* target, const char* value) {
    if (!is_dead(sl) && assigned(target) && assigned(value) && has_items(sl) && !sl->frozen)
        for (ssize_t i = 0; i < sl->size; i++)
            if (compare_string(sl, i, target)) {
                replace_string(sl, i, value);
                return true;
            }
    return false;
}

bool werks_stringlist_replace_last_occurrence(werks_stringlist_dt* const sl, const char* target, const char* value) {
    if (!is_dead(sl) && assigned(target) && assigned(value) && has_items(sl) && !sl->frozen)
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (compare_string(sl, i, target)) {
                replace_string(sl, i, value);
                return true;
            }
    return false;
}

bool werks_stringlist_replace_occurrences(werks_stringlist_dt* const sl, const char* target, const char* value) {
    bool result = false;
    if (!is_dead(sl) && assigned(target) && assigned(value) && has_items(sl) && !sl->frozen)
        for (ssize_t i = 0; i < sl->size; i++)
            if (compare_string(sl, i, target)) {
                replace_string(sl, i, value);
                result |= true;
            }
    return result;
}

bool werks_stringlist_replace_first_occurrence_with(werks_stringlist_dt* const sl, const char* target, werks_stringlist_dt* dl) {
    if (!is_dead(sl) && assigned(target) && has_items(sl) && !sl->frozen && assigned(dl))
        for (ssize_t i = 0; i < sl->size; i++)
            if (compare_string(sl, i, target)) {
                ce_free(sl->strings[i]);
                UNUSED(forget_string(sl, i));
                return insert_strings(sl, dl, i);
            }
    return false;
}

bool werks_stringlist_replace_last_occurrence_with(werks_stringlist_dt* const sl, const char* target, werks_stringlist_dt* dl) {
    if (!is_dead(sl) && assigned(target) && has_items(sl) && !sl->frozen && assigned(dl))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (compare_string(sl, i, target)) {
                ce_free(sl->strings[i]);
                UNUSED(forget_string(sl, i));
                return insert_strings(sl, dl, i);
            }
    return false;
}

bool werks_stringlist_replace_occurrences_with(werks_stringlist_dt* const sl, const char* target, werks_stringlist_dt* dl) {
    bool result = false;
    if (!is_dead(sl) && assigned(target) && has_items(sl) && !sl->frozen && assigned(dl))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (compare_string(sl, i, target)) {
                ce_free(sl->strings[i]);
                UNUSED(forget_string(sl, i));
                result |= insert_strings(sl, dl, i);
            }
    return result;
}

bool werks_stringlist_replace_from_to_with(werks_stringlist_dt* sl, ssize_t from_index, ssize_t to_index, werks_stringlist_dt* ns) {
    if (ptreq(sl, ns) || is_dead(sl) || !has_items(sl) || is_oob(sl, from_index) || is_oob(sl, to_index) || sl->frozen || is_dead(ns)) return false;
    for (ssize_t i = to_index; i >= from_index; i--) { // delete from to + insert all approach
        ce_free(sl->strings[i]);
        UNUSED(forget_string(sl, i));
    }
    return insert_strings(sl, ns, from_index);
}

werks_stringlist_dt* werks_stringlist_from_array_with_size(const char* arr[], ssize_t size) {
    werks_stringlist_dt* result = werks_stringlist_create(size);
    if (!is_dead(result))
        for (ssize_t i = 0; i < size; i++)
            UNUSED(add_string(result, arr[i]));
    return result;
}

werks_stringlist_dt* werks_stringlist_from_array_with_sentinel(const char* arr[]) {
    ssize_t size = string_array_find_null_sentinel(arr, WERKS_STRINGLIST_SENTINEL_LIMIT);
    werks_stringlist_dt* result = werks_stringlist_create(size);
    if (!is_dead(result))
        for (ssize_t i = 0; i < size; i++)
            UNUSED(add_string(result, arr[i]));
    return result;
}

const char** werks_stringlist_to_array_with_size(werks_stringlist_dt* const sl, ssize_t* const size) {
    if (is_dead(sl) || !has_items(sl)) return NULL;
    VAR_MALLOC_SIZE(result, const char*, sl->size * sizeof(char*));
    if (assigned(result)) {
        for (ssize_t i = 0; i < sl->size; i++)
            result[i] = sl->strings[i];
        if (assigned(size)) *size = sl->size;
    }
    return result;
}

const char** werks_stringlist_to_array_with_sentinel(werks_stringlist_dt* const sl) {
    if (is_dead(sl) || !has_items(sl)) return NULL;
    VAR_MALLOC_SIZE(result, const char*, (sl->size + 1) * sizeof(char*));
    if (assigned(result)) {
        for (ssize_t i = 0; i < sl->size; i++)
            result[i] = sl->strings[i];
        result[sl->size] = NULL;
    }
    return result;
}

bool werks_stringlist_delete_from_to(werks_stringlist_dt* const sl, ssize_t from_index, ssize_t to_index) {
    if (is_dead(sl) || !has_items(sl) || is_oob(sl, from_index) || is_oob(sl, to_index) || sl->frozen) return false;
    for (ssize_t i = to_index; i >= from_index; i--) {
        ce_free(sl->strings[i]);
        UNUSED(forget_string(sl, i));
    }
    return true;
}

static inline void transfer_items_from_to(werks_stringlist_dt* const sl, ssize_t from_index, ssize_t to_index, werks_stringlist_dt* const dl) {
    for (ssize_t i = to_index; i >= from_index; i--) {
        char* s = extract_string(sl, i);
        UNUSED(insert_string(dl, s, 0));
        ce_free(s);
    }
}

werks_stringlist_dt* werks_stringlist_extract_from_to(werks_stringlist_dt* const sl, ssize_t from_index, ssize_t to_index) {
    ssize_t size = to_index - from_index + 1;
    if (is_dead(sl) || sl->frozen || !has_items(sl) || is_oob(sl, from_index) || is_oob(sl, to_index) || size <= 0) return NULL;
    werks_stringlist_dt* result = werks_stringlist_create(size);
    if (!is_dead(result))
        transfer_items_from_to(sl, from_index, to_index, result);
    return result;
}

werks_stringlist_dt* werks_stringlist_extract_first(werks_stringlist_dt* const sl, ssize_t amount) {
    ssize_t to_index = amount - 1;
    if (is_dead(sl) || sl->frozen || !has_items(sl) || is_oob(sl, to_index)) return NULL;
    werks_stringlist_dt* result = werks_stringlist_create(amount);
    if (!is_dead(result))
        transfer_items_from_to(sl, 0, to_index, result);
    return result;
}

werks_stringlist_dt* werks_stringlist_extract_last(werks_stringlist_dt* const sl, ssize_t amount) {
    ssize_t from_index = sl->size - amount;
    if (is_dead(sl) || sl->frozen || !has_items(sl) || amount <= 0 || from_index < 0) return NULL;
    werks_stringlist_dt* result = werks_stringlist_create(amount);
    if (!is_dead(result))
        transfer_items_from_to(sl, from_index, from_index + amount - 1, result);
    return result;
}

werks_stringlist_dt* werks_stringlist_extract_prefixed(werks_stringlist_dt* sl, const char* prefix) {
    if (is_dead(sl) || sl->frozen || !has_items(sl) || !has_content(prefix)) return NULL;
    werks_stringlist_dt* result = werks_stringlist_make();
    if (!is_dead(result))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (starts_with(sl->strings[i], prefix)) {
                char* s = extract_string(sl, i);
                UNUSED(insert_string(result, s, 0));
                ce_free(s);
            }
    return result;
}

werks_stringlist_dt* werks_stringlist_extract_not_prefixed(werks_stringlist_dt* sl, const char* prefix) {
    if (is_dead(sl) || sl->frozen || !has_items(sl) || !has_content(prefix)) return NULL;
    werks_stringlist_dt* result = werks_stringlist_make();
    if (!is_dead(result))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (!starts_with(sl->strings[i], prefix)) {
                char* s = extract_string(sl, i);
                UNUSED(insert_string(result, s, 0));
                ce_free(s);
            }
    return result;
}

werks_stringlist_dt* werks_stringlist_extract_suffixed(werks_stringlist_dt* sl, const char* suffix) {
    if (is_dead(sl) || sl->frozen || !has_items(sl) || !has_content(suffix)) return NULL;
    werks_stringlist_dt* result = werks_stringlist_make();
    if (!is_dead(result))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (ends_with(sl->strings[i], suffix)) {
                char* s = extract_string(sl, i);
                UNUSED(insert_string(result, s, 0));
                ce_free(s);
            }
    return result;
}

werks_stringlist_dt* werks_stringlist_extract_not_suffixed(werks_stringlist_dt* sl, const char* suffix) {
    if (is_dead(sl) || sl->frozen || !has_items(sl) || !has_content(suffix)) return NULL;
    werks_stringlist_dt* result = werks_stringlist_make();
    if (!is_dead(result))
        for (ssize_t i = sl->size - 1; i >= 0; i--)
            if (!ends_with(sl->strings[i], suffix)) {
                char* s = extract_string(sl, i);
                UNUSED(insert_string(result, s, 0));
                ce_free(s);
            }
    return result;
}

void werks_stringlist_sort(werks_stringlist_dt* const sl) {
    if (!is_dead(sl) && !sl->frozen && has_items(sl))
        string_array_sort(sl->size, sl->strings);
}

void werks_stringlist_shuffle(werks_stringlist_dt* const sl, fn_int_fn const rand_func) {
    if (!is_dead(sl) && !sl->frozen && has_items(sl))
        string_array_shuffle(sl->size, sl->strings, rand_func);
}

char* werks_stringlist_write_to_json_array_string(werks_stringlist_dt* const sl) {
    if (is_dead(sl)) return NULL;
    ssize_t tot_len = 2;
    for (ssize_t i = 0; i < sl->size; i++)
        tot_len += strlen(sl->strings[i]) + 3;
    RET_MALLOC_SIZE(char, tot_len + 1, {
        result[0] = CHARS_BRACKETS_OPEN;
        result[1] = CHARS_NULL;
        for (ssize_t i = 0; i < sl->size; i++) {
            if (i > 0) strcat(result, STRINGS_COMMA);
            strcat(result, STRINGS_QUOTE);
            strcat(result, sl->strings[i]);
            strcat(result, STRINGS_QUOTE);
        }
        strcat(result, STRINGS_BRACKETS_CLOSE);
    });
}

static void add_json_string(const char* value, const void* reference) {
    add_string((werks_stringlist_dt*)reference, value);
}

bool werks_stringlist_read_from_json_array_string(werks_stringlist_dt* const sl, const char* data) {
    return !is_dead(sl) && !sl->frozen && has_content(data) &&
        parse_json_strings_array_with_reference(data, add_json_string, sl);
}

