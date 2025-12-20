/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: MeH
 * File: meh_memory-inc.h
 * Brief: part of MeH
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef MEH
#warning This is intended to be part of the MeH C Library.
#endif

#define MEH_DEFAULT_BUFFER_SIZE (1 * KILOBYTE)
#define MEH_DEFAULT_SENTINEL_LIMIT (1 * KILOBYTE)

/* MeH.MEMORY -- Alignment Definitions */

// checks if the pointer is aligned with the specified alignment (in bytes)
static inline bool is_byte_aligned(const void* const ptr, const size_t alignment) {
    if (alignment == 0 || (alignment & (alignment - 1)) != 0) return false; // alignment must be power of two
    return ((uintptr_t)ptr & (alignment - 1)) == 0; // same as ((uintptr_t)ptr % alignment) == 0
}

// checks if the pointer is aligned with the specified alignment (in bits)
static inline bool is_bit_aligned(const void* const ptr, const size_t alignment) {
    // alignment must be a power of two and a multiple of 8 (byte-aligned)
    if (alignment == 0 || (alignment & (alignment - 1)) != 0 || (alignment % 8) != 0) return false;
    size_t byte_alignment = alignment / 8;
    return ((uintptr_t)ptr & (byte_alignment - 1)) == 0;
}

/* MeH.MEMORY -- Automatic Cleanup */

#define __auto __attribute__((cleanup(_auto_cleanup)))

// automatic cleanup for simple pointers
__attribute__((always_inline))
inline void _auto_cleanup(void* ptr) {
    ce_free(*(void**)ptr);
}

#define AUTO_STRING(name, value) __auto char* name = value

#define AUTO_STRDUP(name, value) AUTO_STRING(name, strdup(value))

#define AUTO_STRHEAP(name, value) \
    __auto STR_MALLOC(name, strlen(value) + 1); \
    strcpy(name, value)

#define AUTO_BYTES(name, size) __auto uint8_t* name = TYPE_MALLOC(uint8_t, size)

#define AUTO_TYPE(name, type) __auto VAR_MALLOC(name, type)

/* MeH.MEMORY -- Automatic Return */

#define RET_MALLOC(type, code) \
    VAR_MALLOC(result, type); \
    if (assigned(result)) { code } \
    return result;

#define RET_MALLOC_SIZE(type, size, code) \
    VAR_MALLOC_SIZE(result, type, size); \
    if (assigned(result)) { code } \
    return result;

#define RET_CALLOC(type, count, code) \
    VAR_CALLOC(result, type, count); \
    if (assigned(result)) { code } \
    return result;

/* MeH.MEMORY -- Deallocation Utilities */

static inline void zero_free(void* ptr, size_t size) {
    if (ptr == NULL) return;
    memset(ptr, 0, size);
    ce_free(ptr);
}

static inline void safe_free(void* ptr, size_t size, unsigned char byte) {
    if (ptr == NULL) return;
    for (size_t i = 0; i < size; i++) ((unsigned char*)ptr)[i] = byte;
    ce_free(ptr);
}

static inline void free_and_null_array_items(void** arr, size_t size) {
    if (assigned(arr))
        for (size_t i = 0; i < size; i++) {
            ce_free(arr[i]);
            arr[i] = NULL;
        }
}

#define FREE_ARRAY_ITEMS(arr, size) free_and_null_array_items((void**)arr, size)

/* MeH.MEMORY -- Function Pointers */

/* checks if the function is assigned, and if so it calls it with the specified parameters */
#define safe_call(fn, ...) do { if (assigned(fn)) (fn)(__VA_ARGS__); } while(0)

/* MeH.MEMORY -- struct-related Definitions */

/* retrieves the heap struct member if the struct is assigned or the default value otherwise */
#define safe_fetch(stc, fld, def) (stc == NULL ? def : stc->fld)

#define FETCH_POINTER_MEMBER(stc, fld) ((void*)safe_fetch(stc, fld, DEFAULT_POINTER))
#define FETCH_STRING_MEMBER(stc, fld) ((char*)safe_fetch(stc, fld, DEFAULT_STRING))
#define FETCH_CHAR_MEMBER(stc, fld) ((char)safe_fetch(stc, fld, DEFAULT_CHAR))
#define FETCH_SIGNED_CHAR_MEMBER(stc, fld) ((signed char)safe_fetch(stc, fld, DEFAULT_SIGNED_CHAR))
#define FETCH_UNSIGNED_CHAR_MEMBER(stc, fld) ((unsigned char)safe_fetch(stc, fld, DEFAULT_UNSIGNED_CHAR))
#define FETCH_BOOL_MEMBER(stc, fld) ((bool)safe_fetch(stc, fld, DEFAULT_BOOL))
#define FETCH_SHORT_MEMBER(stc, fld) ((short)safe_fetch(stc, fld, DEFAULT_SHORT))
#define FETCH_UNSIGNED_SHORT_MEMBER(stc, fld) ((unsigned short)safe_fetch(stc, fld, DEFAULT_UNSIGNED_SHORT))
#define FETCH_INT_MEMBER(stc, fld) ((int)safe_fetch(stc, fld, DEFAULT_INT))
#define FETCH_UNSIGNED_INT_MEMBER(stc, fld) ((unsigned int)safe_fetch(stc, fld, DEFAULT_UNSIGNED_INT))
#define FETCH_LONG_MEMBER(stc, fld) ((long)safe_fetch(stc, fld, DEFAULT_LONG))
#define FETCH_UNSIGNED_LONG_MEMBER(stc, fld) ((unsigned long)safe_fetch(stc, fld, DEFAULT_UNSIGNED_LONG))
#define FETCH_LONG_LONG_MEMBER(stc, fld) ((long long)safe_fetch(stc, fld, DEFAULT_LONG_LONG))
#define FETCH_UNSIGNED_LONG_LONG_MEMBER(stc, fld) ((unsigned long long)safe_fetch(stc, fld, DEFAULT_UNSIGNED_LONG_LONG))
#define FETCH_FLOAT_MEMBER(stc, fld) ((float)safe_fetch(stc, fld, DEFAULT_FLOAT))
#define FETCH_DOUBLE_MEMBER(stc, fld) ((double)safe_fetch(stc, fld, DEFAULT_DOUBLE))
#define FETCH_LONG_DOUBLE_MEMBER(stc, fld) ((long double)safe_fetch(stc, fld, DEFAULT_LONG_DOUBLE))

// copies the provided struct into the stack
#define STACK_STRUCT_COPY(sas, newvar)    \
    __typeof__(sas) newvar;               \
    memcpy(&newvar, &sas, sizeof(newvar))

// copies the provided struct into the heap
#define HEAP_STRUCT_COPY(ptr, newptr)                       \
    __typeof__(*(ptr))* newptr = ce_malloc(sizeof(*(ptr))); \
    if (newptr) memcpy(newptr, (ptr), sizeof(*(ptr)));

/* MeH.MEMORY -- Bit-rotation Operations */

// rotates an unsigned integer of 8 bits to the left
static inline uint8_t rol8(uint8_t x, unsigned int n) {
    n &= 7;
    return (x << n) | (x >> (8 - n));
}

// rotates an unsigned integer of 8 bits to the right
static inline uint8_t ror8(uint8_t x, unsigned int n) {
    n &= 7;
    return (x >> n) | (x << (8 - n));
}

// rotates an unsigned integer of 16 bits to the left
static inline uint16_t rol16(uint16_t x, unsigned int n) {
    n &= 15;
    return (x << n) | (x >> (16 - n));
}

// rotates an unsigned integer of 16 bits to the right
static inline uint16_t ror16(uint16_t x, unsigned int n) {
    n &= 15;
    return (x >> n) | (x << (16 - n));
}

// rotates an unsigned integer of 32 bits to the left
static inline uint32_t rol32(uint32_t x, unsigned int n) {
    n &= 31;
    return (x << n) | (x >> (32 - n));
}

// rotates an unsigned integer of 32 bits to the right
static inline uint32_t ror32(uint32_t x, unsigned int n) {
    n &= 31;
    return (x >> n) | (x << (32 - n));
}

// rotates an unsigned integer of 64 bits to the left
static inline uint64_t rol64(uint64_t x, unsigned int n) {
    n &= 63;
    return (x << n) | (x >> (64 - n));
}

// rotates an unsigned integer of 64 bits to the right
static inline uint64_t ror64(uint64_t x, unsigned int n) {
    n &= 63;
    return (x >> n) | (x << (64 - n));
}

/* MeH.MEMORY -- Byte-packing Operations */

// pack 2 bytes into uint16_t in little endian order
static inline uint16_t pack_little_endian_16(const uint8_t bytes[2]) {
    return ((uint16_t)bytes[0]) |
           ((uint16_t)bytes[1] << 8);
}

// pack 2 bytes into uint16_t in big endian order
static inline uint16_t pack_big_endian_16(const uint8_t bytes[2]) {
    return ((uint16_t)bytes[0] << 8) |
           ((uint16_t)bytes[1]);
}

// pack 4 bytes into uint32_t in little endian order
static inline uint32_t pack_little_endian_32(const uint8_t bytes[4]) {
    return ((uint32_t)bytes[0]) |
           ((uint32_t)bytes[1] << 8) |
           ((uint32_t)bytes[2] << 16) |
           ((uint32_t)bytes[3] << 24);
}

// pack 4 bytes into uint32_t in big endian order
static inline uint32_t pack_big_endian_32(const uint8_t bytes[4]) {
    return ((uint32_t)bytes[0] << 24) |
           ((uint32_t)bytes[1] << 16) |
           ((uint32_t)bytes[2] << 8) |
           ((uint32_t)bytes[3]);
}

// pack 8 bytes into uint64_t in little endian order
static inline uint64_t pack_little_endian_64(const uint8_t bytes[8]) {
    return ((uint64_t)bytes[0]) |
           ((uint64_t)bytes[1] << 8) |
           ((uint64_t)bytes[2] << 16) |
           ((uint64_t)bytes[3] << 24) |
           ((uint64_t)bytes[4] << 32) |
           ((uint64_t)bytes[5] << 40) |
           ((uint64_t)bytes[6] << 48) |
           ((uint64_t)bytes[7] << 56);
}

// pack 8 bytes into uint64_t in big endian order
static inline uint64_t pack_big_endian_64(const uint8_t bytes[8]) {
    return ((uint64_t)bytes[0] << 56) |
           ((uint64_t)bytes[1] << 48) |
           ((uint64_t)bytes[2] << 40) |
           ((uint64_t)bytes[3] << 32) |
           ((uint64_t)bytes[4] << 24) |
           ((uint64_t)bytes[5] << 16) |
           ((uint64_t)bytes[6] << 8) |
           ((uint64_t)bytes[7]);
}

/* MeH.MEMORY -- Exchange Utilities */

// exchanges the values with a temporary variable of the same type
#define xchg(a, b) do { \
    __typeof__(a) _tmp = (a); \
    (a) = (b); \
    (b) = _tmp; \
} while (0)

// exchanges the values via xor operations
#define xorxchg(a, b) (a ^= b, b ^= a, a ^=b)

// exchanges the values with memory operations using the specified size
static inline void memxchg(void* a, void* b, const size_t size) {
    void* tmp = ce_malloc(size);
    if (assigned(tmp)) {
        memcpy(tmp, a, size);
        memcpy(a, b, size);
        memcpy(b, tmp, size);
        ce_free(tmp);
    }
}

/* MeH.MEMORY -- Pointer Functions */

// write a value through a volatile pointer to prevent the compiler from optimizing away the write
#define VOLATILE_WRITE(var, val) do { \
        volatile __typeof__(var) *p = &(var); \
        *p = (val); \
    } while (0)

// returns the first value if it's assigned, otherwise the second (usually the default value) -- an idiomatic a?:b
#define ensure(ref, def) ({ \
        __typeof__(ref) _x = ref; \
        __typeof__(def) _y = def; \
        assigned(_x) ? _x : _y; \
    })

// same functionality as the ensure macro
static inline void* null_coalesce(void* x, void* y) {
    return assigned(x) ? x : y;
}

// checks if the two pointers refer to the same address
static inline bool ptreq(const void* const a, const void* const b) {
    return a == b;
}

