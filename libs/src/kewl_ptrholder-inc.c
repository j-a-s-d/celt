/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_ptrholder-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

struct KEWL_PTRHOLDER_ALIGNMENT kewl_ptrholder_dt {
    KEWL_PTRHOLDER_POINTER_TYPE* data;
    size_t size;
    size_t capacity;
    float capacity_grow_factor;
    float capacity_grow_padding;
};

kewl_ptrholder_dt* kewl_ptrholder_create(size_t initial_capacity) {
    if (initial_capacity <= 0) return NULL;
    RET_MALLOC(kewl_ptrholder_dt, {
        result->data = TYPE_MALLOC(KEWL_PTRHOLDER_POINTER_TYPE, initial_capacity);
        if (result->data == NULL) {
            ce_free(result);
            return NULL;
        }
        result->size = 0;
        result->capacity = initial_capacity;
        result->capacity_grow_factor = KEWL_PTRHOLDER_GROW_FACTOR;
        result->capacity_grow_padding = KEWL_PTRHOLDER_GROW_PADDING;
    });
}

size_t kewl_ptrholder_get_size(kewl_ptrholder_dt* const holder) {
    return holder == NULL ? 0 : holder->size;
}

size_t kewl_ptrholder_get_capacity(kewl_ptrholder_dt* const holder) {
    return holder == NULL ? 0 : holder->capacity;
}

float kewl_ptrholder_get_capacity_grow_factor(kewl_ptrholder_dt* const holder) {
    return holder == NULL ? 0.0f : holder->capacity_grow_factor;
}

float kewl_ptrholder_get_capacity_grow_padding(kewl_ptrholder_dt* const holder) {
    return holder == NULL ? 0.0f : holder->capacity_grow_padding;
}

void kewl_ptrholder_set_capacity_grow_factor(kewl_ptrholder_dt* const holder, float factor) {
    if (assigned(holder)) holder->capacity_grow_factor = factor;
}

void kewl_ptrholder_set_capacity_grow_padding(kewl_ptrholder_dt* const holder, float padding) {
    if (assigned(holder)) holder->capacity_grow_padding = padding;
}

static bool set_capacity(kewl_ptrholder_dt* const holder, size_t new_capacity)  {
    holder->capacity = new_capacity;
    KEWL_PTRHOLDER_POINTER_TYPE* tmp = TYPE_REALLOC(holder->data, KEWL_PTRHOLDER_POINTER_TYPE, holder->capacity);
    if (!tmp) {
        holder->size = 0;
        holder->capacity = 0;
        return false;
    }
    holder->data = tmp;
    return true;
}

bool kewl_ptrholder_grow_capacity(kewl_ptrholder_dt* const holder, float factor, float padding) {
    if (holder == NULL) return false;
    size_t new_capacity = (holder->capacity * factor) + padding;
    if (holder->capacity > new_capacity) new_capacity = holder->capacity + 1; // ensure growth
    return set_capacity(holder, new_capacity);
}

bool kewl_ptrholder_add(kewl_ptrholder_dt* const holder, KEWL_PTRHOLDER_POINTER_TYPE value) {
    if (holder == NULL) return false;
    if (holder->size == holder->capacity)
        if (!kewl_ptrholder_grow_capacity(holder, holder->capacity_grow_factor, holder->capacity_grow_padding)) return false;
    holder->data[holder->size++] = value;
    return true;
}

static size_t find_element(kewl_ptrholder_dt* const holder, KEWL_PTRHOLDER_POINTER_TYPE value) {
    for (size_t i = 0; i < holder->size; i++)
        if (holder->data[i] == value)
            return i;
    // NOTE: return size if not found (avoiding automatic conversion to MAX_SIZE since it's a size_t)
    return holder->size;
}

bool kewl_ptrholder_has(kewl_ptrholder_dt* const holder, KEWL_PTRHOLDER_POINTER_TYPE value) {
    if (holder == NULL || holder->size == 0) return false;
    return find_element(holder, value) != holder->size;
}

static void remove_element(kewl_ptrholder_dt* const holder, size_t index) {
    for (size_t i = index; i < holder->size - 1; i++)
        holder->data[i] = holder->data[i + 1];
    holder->size--;
}

bool kewl_ptrholder_delete_once(kewl_ptrholder_dt* const holder, KEWL_PTRHOLDER_POINTER_TYPE value) {
    if (holder == NULL || holder->size == 0) return false;
    size_t index = find_element(holder, value);
    if (index != holder->size) {
        remove_element(holder, index);
        return true;
    }
    return false;
}

bool kewl_ptrholder_delete_every(kewl_ptrholder_dt* const holder, KEWL_PTRHOLDER_POINTER_TYPE value) {
    if (holder == NULL || holder->size == 0) return false;
    for (ssize_t i = holder->size - 1; i >= 0; i--)
        if (holder->data[i] == value)
            remove_element(holder, i);
    return true;
}

bool kewl_ptrholder_replace_once(kewl_ptrholder_dt* const holder, KEWL_PTRHOLDER_POINTER_TYPE old_value, KEWL_PTRHOLDER_POINTER_TYPE new_value) {
    if (holder == NULL || holder->size == 0) return false;
    size_t index = find_element(holder, old_value);
    if (index != holder->size) {
        holder->data[index] = new_value;
        return true;
    }
    return false;
}

bool kewl_ptrholder_replace_every(kewl_ptrholder_dt* const holder, KEWL_PTRHOLDER_POINTER_TYPE old_value, KEWL_PTRHOLDER_POINTER_TYPE new_value) {
    if (holder == NULL || holder->size == 0) return false;
    for (size_t i = 0; i < holder->size; i++)
        if (holder->data[i] == old_value)
            holder->data[i] = new_value;
    return true;
}

size_t kewl_ptrholder_count_every(kewl_ptrholder_dt* const holder, KEWL_PTRHOLDER_POINTER_TYPE value) {
    if (holder == NULL || holder->size == 0) return false;
    size_t result = 0;
    for (size_t i = 0; i < holder->size; i++)
        if (holder->data[i] == value)
            result++;
    return result;
}

KEWL_PTRHOLDER_POINTER_TYPE kewl_ptrholder_get(kewl_ptrholder_dt* const holder, size_t index) {
    if (holder == NULL || holder->size == 0 || index >= holder->size) return (KEWL_PTRHOLDER_POINTER_TYPE)NULL;
    return holder->data[index];
}

char* kewl_ptrholder_stringify(kewl_ptrholder_dt* const holder, char separator) {
    if (holder == NULL || holder->size == 0) return strdup(STRINGS_NOTHING);
    char* result = TYPE_MALLOC(char, (holder->size * KEWL_PTRHOLDER_POINTER_LENGTH) + 1);
    if (assigned(result)) {
        result[0] = CHARS_NULL;
        for (size_t i = 0; i < holder->size; i++) {
            char temp[KEWL_PTRHOLDER_POINTER_LENGTH];
            snprintf(temp, sizeof(temp), KEWL_PTRHOLDER_POINTER_FORMAT, holder->data[i], separator);
            strcat(result, temp);
        }
        result[strlen(result) - 1] = CHARS_NULL;
    }
    return result;
}

void kewl_ptrholder_loop(kewl_ptrholder_dt* const holder, kewl_ptr_item_callback_fn cb) {
    if (assigned(holder))
        for (size_t i = 0; i < holder->size; i++)
            cb(holder, holder->data[i]);
}

void kewl_ptrholder_loop_with_reference(kewl_ptrholder_dt* const holder, kewl_ptr_item_with_reference_callback_fn cb, void* ref) {
    if (assigned(holder))
        for (size_t i = 0; i < holder->size; i++)
            cb(holder, holder->data[i], ref);
}

void kewl_ptrholder_clear(kewl_ptrholder_dt* const holder) {
    if (assigned(holder)) holder->size = 0;
}

void kewl_ptrholder_destroy(kewl_ptrholder_dt* const holder) {
    if (holder == NULL) return;
    ce_free(holder->data);
    holder->data = NULL;
    holder->size = 0;
    holder->capacity = 0;
    ce_free(holder);
}

