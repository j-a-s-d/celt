/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_chunksstack-inc.c
 * Copyright (c) 2025-2026 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

struct KEWL_CHUNKSSTACK_ALIGNMENT kewl_chunksstack_dt {
    unsigned char* data;
    size_t chunk_size;
    size_t count;
    size_t capacity;
    float capacity_grow_factor;
    float capacity_grow_padding;
};

static bool kewl_chunksstack_resize(kewl_chunksstack_dt* const stack, size_t new_capacity) {
    if (stack == NULL) return false;
    size_t old_capacity = stack->capacity;
    void* new_data = realloc(stack->data, new_capacity * stack->chunk_size);
    if (new_data == NULL && new_capacity > 0) return false;
    stack->data = (unsigned char*) new_data;
    stack->capacity = new_capacity;
    if (new_capacity > old_capacity) // clear manually the new allocated space
        memset(stack->data + (old_capacity * stack->chunk_size), 0, (new_capacity - old_capacity) * stack->chunk_size);
    return true;
}

kewl_chunksstack_dt* kewl_chunksstack_create(size_t initial_capacity, size_t chunk_size) {
    if (initial_capacity <= 0) return NULL;
    RET_MALLOC(kewl_chunksstack_dt, {
        result->data = calloc(initial_capacity, chunk_size);
        if (result->data == NULL && initial_capacity > 0) {
            free(result);
            return NULL;
        }
        result->chunk_size = chunk_size;
        result->capacity = initial_capacity;
        result->capacity_grow_factor = KEWL_CHUNKSSTACK_GROW_FACTOR;
        result->capacity_grow_padding = KEWL_CHUNKSSTACK_GROW_PADDING;
        result->count = 0;
    });
}

void* kewl_chunksstack_get(kewl_chunksstack_dt* const stack, size_t index) {
    if (stack == NULL || index >= stack->count) return NULL;
    return stack->data + (index * stack->chunk_size);
}

bool kewl_chunksstack_set(kewl_chunksstack_dt* const stack, size_t index, const void* source) {
    if (stack == NULL || index >= stack->capacity) return false;
    void* dest = stack->data + (index * stack->chunk_size);
    memcpy(dest, source, stack->chunk_size);
    return true;
}

bool kewl_chunksstack_push(kewl_chunksstack_dt* const stack, const void* source) {
    if (stack == NULL) return false;
    if (stack->count >= stack->capacity) {
        size_t new_capacity = stack->capacity == 0 ? 1 : (stack->capacity * stack->capacity_grow_factor) + stack->capacity_grow_padding;
        if (!kewl_chunksstack_resize(stack, new_capacity)) return false;
    }
    if (kewl_chunksstack_set(stack, stack->count, source)) {
        stack->count++;
        return true;
    }
    return false;
}

bool kewl_chunksstack_pop(kewl_chunksstack_dt* const stack, void* destination) {
    if (stack == NULL || stack->count == 0) return false;
    void* last = kewl_chunksstack_get(stack, stack->count - 1);
    if (both_assigned(destination, last)) memcpy(destination, last, stack->chunk_size);
    stack->count--;
    return true;
}

bool kewl_chunksstack_delete(kewl_chunksstack_dt* const stack, size_t index) {
    if (stack == NULL || index >= stack->count) return false;
    if (index < stack->count - 1) {
        void* dest = stack->data + (index * stack->chunk_size);
        void* src = stack->data + ((index + 1) * stack->chunk_size);
        size_t bytes_to_move = (stack->count - index - 1) * stack->chunk_size;
        memmove(dest, src, bytes_to_move);
    }
    stack->count--;
    return true;
}

bool kewl_chunksstack_pack(kewl_chunksstack_dt* const stack) {
    if (stack == NULL) return false;
    if (stack->count == stack->capacity) return true;
    return kewl_chunksstack_resize(stack, stack->count);
}

void kewl_chunksstack_clear(kewl_chunksstack_dt* const stack) {
    if (stack != NULL && stack->data != NULL) {
        zeromem(stack->data, stack->capacity * stack->chunk_size);
        stack->count = 0;
    }
}

void* kewl_chunksstack_get_buffer_pointer(kewl_chunksstack_dt* stack) {
    if (stack == NULL || stack->data == NULL) return NULL;
    return stack->data;
}

size_t kewl_chunksstack_get_buffer_size(kewl_chunksstack_dt* const stack) {
    return stack == NULL ? 0 : stack->chunk_size * stack->count;
}

size_t kewl_chunksstack_get_chunks_count(kewl_chunksstack_dt* const stack) {
    return stack == NULL ? 0 : stack->count;
}

size_t kewl_chunksstack_get_chunk_size(kewl_chunksstack_dt* const stack) {
    return stack == NULL ? 0 : stack->chunk_size;
}

size_t kewl_chunksstack_get_capacity(kewl_chunksstack_dt* const stack) {
    return stack == NULL ? 0 : stack->capacity;
}

float kewl_chunksstack_get_capacity_grow_factor(kewl_chunksstack_dt* const stack) {
    return stack == NULL ? 0.0f : stack->capacity_grow_factor;
}

float kewl_chunksstack_get_capacity_grow_padding(kewl_chunksstack_dt* const stack) {
    return stack == NULL ? 0.0f : stack->capacity_grow_padding;
}

void kewl_chunksstack_set_capacity_grow_factor(kewl_chunksstack_dt* const stack, float factor) {
    if (assigned(stack)) stack->capacity_grow_factor = factor;
}

void kewl_chunksstack_set_capacity_grow_padding(kewl_chunksstack_dt* const stack, float padding) {
    if (assigned(stack)) stack->capacity_grow_padding = padding;
}

void kewl_chunksstack_loop(kewl_chunksstack_dt* const stack, kewl_chunksstack_callback_fn cb) {
    if (stack == NULL || cb == NULL) return;
    for (size_t i = 0; i < stack->count; i++)
        cb(kewl_chunksstack_get(stack, i), i);
}

void kewl_chunksstack_loop_with_reference(kewl_chunksstack_dt* const stack, kewl_chunksstack_callback_with_reference_fn cb, void* ref) {
    if (stack == NULL || cb == NULL) return;
    for (size_t i = 0; i < stack->count; i++)
        cb(kewl_chunksstack_get(stack, i), i, ref);
}

void kewl_chunksstack_destroy(kewl_chunksstack_dt* const stack) {
    if (stack != NULL) {
        free(stack->data);
        free(stack);
    }
}

