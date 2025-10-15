/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: MeH
 * File: meh_array-inc.h
 * Brief: part of MeH
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef MEH
#warning This is intended to be part of the MeH C Library.
#endif

/* MeH.MATH -- Arrays Functions */

#define MEH_COPY_ARRAY(type)                            \
    type* copy = (type*)ce_malloc(size * sizeof(type)); \
    if (copy == NULL) return NULL;                      \
    memcpy(copy, arr, size * sizeof(type));             \
    return copy

static inline short* short_array_copy(const short* arr, size_t size) {
    MEH_COPY_ARRAY(short);
}

static inline unsigned short* unsigned_short_array_copy(const unsigned short* arr, size_t size) {
    MEH_COPY_ARRAY(unsigned short);
}

static inline int* int_array_copy(const int* arr, size_t size) {
    MEH_COPY_ARRAY(int);
}

static inline unsigned int* unsigned_int_array_copy(const unsigned int* arr, size_t size) {
    MEH_COPY_ARRAY(unsigned int);
}

static inline long* long_array_copy(const long* arr, size_t size) {
    MEH_COPY_ARRAY(long);
}

static inline unsigned long* unsigned_long_array_copy(const unsigned long* arr, size_t size) {
    MEH_COPY_ARRAY(unsigned long);
}

static inline long long* long_long_array_copy(const long long* arr, size_t size) {
    MEH_COPY_ARRAY(long long);
}

static inline unsigned long long* unsigned_long_long_array_copy(const unsigned long long* arr, size_t size) {
    MEH_COPY_ARRAY(unsigned long long);
}

static inline long double* long_double_array_copy(const long double* arr, size_t size) {
    MEH_COPY_ARRAY(long double);
}

static inline double* double_array_copy(const double* arr, size_t size) {
    MEH_COPY_ARRAY(double);
}

static inline float* float_array_copy(const float* arr, size_t size) {
    MEH_COPY_ARRAY(float);
}

static inline char* char_array_copy(const char* arr, size_t size) {
    MEH_COPY_ARRAY(char);
}

static inline signed char* signed_char_array_copy(const signed char* arr, size_t size) {
    MEH_COPY_ARRAY(signed char);
}

static inline unsigned char* unsigned_char_array_copy(const unsigned char* arr, size_t size) {
    MEH_COPY_ARRAY(unsigned char);
}

static inline int8_t* int8_array_copy(const int8_t* arr, size_t size) {
    MEH_COPY_ARRAY(int8_t);
}

static inline uint8_t* uint8_array_copy(const uint8_t* arr, size_t size) {
    MEH_COPY_ARRAY(uint8_t);
}

static inline int16_t* int16_array_copy(const int16_t* arr, size_t size) {
    MEH_COPY_ARRAY(int16_t);
}

static inline uint16_t* uint16_array_copy(const uint16_t* arr, size_t size) {
    MEH_COPY_ARRAY(uint16_t);
}

static inline int32_t* int32_array_copy(const int32_t* arr, size_t size) {
    MEH_COPY_ARRAY(int32_t);
}

static inline uint32_t* uint32_array_copy(const uint32_t* arr, size_t size) {
    MEH_COPY_ARRAY(uint32_t);
}

static inline int64_t* int64_array_copy(const int64_t* arr, size_t size) {
    MEH_COPY_ARRAY(int64_t);
}

static inline uint64_t* uint64_array_copy(const uint64_t* arr, size_t size) {
    MEH_COPY_ARRAY(uint64_t);
}

#undef MEH_COPY_ARRAY

#define MEH_TREAT_ARRAY(type, treater) \
    if (arr == NULL || treater == NULL) return false; \
    for (size_t i = 0; i < size; i++) \
        arr[i] = treater((type)arr[i]); \
    return true

static inline bool short_array_treat(short* arr, size_t size, trt_short_fn treater) {
    MEH_TREAT_ARRAY(short, treater);
}

static inline bool unsigned_short_array_treat(unsigned short* arr, size_t size, trt_unsigned_short_fn treater) {
    MEH_TREAT_ARRAY(unsigned short, treater);
}

static inline bool int_array_treat(int* arr, size_t size, trt_int_fn treater) {
    MEH_TREAT_ARRAY(int, treater);
}

static inline bool unsigned_int_array_treat(unsigned int* arr, size_t size, trt_unsigned_int_fn treater) {
    MEH_TREAT_ARRAY(unsigned int, treater);
}

static inline bool long_array_treat(long* arr, size_t size, trt_long_fn treater) {
    MEH_TREAT_ARRAY(long, treater);
}

static inline bool unsigned_long_array_treat(unsigned long* arr, size_t size, trt_unsigned_long_fn treater) {
    MEH_TREAT_ARRAY(unsigned long, treater);
}

static inline bool long_long_array_treat(long long* arr, size_t size, trt_long_long_fn treater) {
    MEH_TREAT_ARRAY(long long, treater);
}

static inline bool unsigned_long_long_array_treat(unsigned long long* arr, size_t size, trt_unsigned_long_long_fn treater) {
    MEH_TREAT_ARRAY(unsigned long long, treater);
}

static inline bool char_array_treat(char* arr, size_t size, trt_char_fn treater) {
    MEH_TREAT_ARRAY(char, treater);
}

static inline bool signed_char_array_treat(signed char* arr, size_t size, trt_signed_char_fn treater) {
    MEH_TREAT_ARRAY(signed char, treater);
}

static inline bool unsigned_char_array_treat(unsigned char* arr, size_t size, trt_unsigned_char_fn treater) {
    MEH_TREAT_ARRAY(unsigned char, treater);
}

static inline bool int8_array_treat(int8_t* arr, size_t size, trt_int8_fn treater) {
    MEH_TREAT_ARRAY(int8_t, treater);
}

static inline bool uint8_array_treat(uint8_t* arr, size_t size, trt_uint8_fn treater) {
    MEH_TREAT_ARRAY(uint8_t, treater);
}

static inline bool int16_array_treat(int16_t* arr, size_t size, trt_int16_fn treater) {
    MEH_TREAT_ARRAY(int16_t, treater);
}

static inline bool uint16_array_treat(uint16_t* arr, size_t size, trt_uint16_fn treater) {
    MEH_TREAT_ARRAY(uint16_t, treater);
}

static inline bool int32_array_treat(int32_t* arr, size_t size, trt_int32_fn treater) {
    MEH_TREAT_ARRAY(int32_t, treater);
}

static inline bool uint32_array_treat(uint32_t* arr, size_t size, trt_uint32_fn treater) {
    MEH_TREAT_ARRAY(uint32_t, treater);
}

static inline bool int64_array_treat(int64_t* arr, size_t size, trt_int64_fn treater) {
    MEH_TREAT_ARRAY(int64_t, treater);
}

static inline bool uint64_array_treat(uint64_t* arr, size_t size, trt_uint64_fn treater) {
    MEH_TREAT_ARRAY(uint64_t, treater);
}

static inline bool float_array_treat(float* arr, size_t size, trt_float_fn treater) {
    MEH_TREAT_ARRAY(float, treater);
}

static inline bool double_array_treat(double* arr, size_t size, trt_double_fn treater) {
    MEH_TREAT_ARRAY(double, treater);
}

static inline bool long_double_array_treat(long double* arr, size_t size, trt_long_double_fn treater) {
    MEH_TREAT_ARRAY(long double, treater);
}

#undef MEH_TREAT_ARRAY

#define MEH_COMPARE_ARRAY(type) \
    if (arr1 == NULL || arr2 == NULL) return false; \
    for (size_t i = 0; i < size; i++) \
        if (arr1[i] != arr2[i]) return false; \
    return true

static inline bool short_array_equal(const short* arr1, const short* arr2, size_t size) {
    MEH_COMPARE_ARRAY(short);
}

static inline bool unsigned_short_array_equal(const unsigned short* arr1, const unsigned short* arr2, size_t size) {
    MEH_COMPARE_ARRAY(unsigned short);
}

static inline bool int_array_equal(const int* arr1, const int* arr2, size_t size) {
    MEH_COMPARE_ARRAY(int);
}

static inline bool unsigned_int_array_equal(const unsigned int* arr1, const unsigned int* arr2, size_t size) {
    MEH_COMPARE_ARRAY(unsigned int);
}

static inline bool long_array_equal(const long* arr1, const long* arr2, size_t size) {
    MEH_COMPARE_ARRAY(long);
}

static inline bool unsigned_long_array_equal(const unsigned long* arr1, const unsigned long* arr2, size_t size) {
    MEH_COMPARE_ARRAY(unsigned long);
}

static inline bool long_long_array_equal(const long long* arr1, const long long* arr2, size_t size) {
    MEH_COMPARE_ARRAY(long long);
}

static inline bool unsigned_long_long_array_equal(const unsigned long long* arr1, const unsigned long long* arr2, size_t size) {
    MEH_COMPARE_ARRAY(unsigned long long);
}

static inline bool char_array_equal(const char* arr1, const char* arr2, size_t size) {
    MEH_COMPARE_ARRAY(char);
}

static inline bool signed_char_array_equal(const signed char* arr1, const signed char* arr2, size_t size) {
    MEH_COMPARE_ARRAY(signed char);
}

static inline bool unsigned_char_array_equal(const unsigned char* arr1, const unsigned char* arr2, size_t size) {
    MEH_COMPARE_ARRAY(unsigned char);
}

static inline bool int8_array_equal(const int8_t* arr1, const int8_t* arr2, size_t size) {
    MEH_COMPARE_ARRAY(int8_t);
}

static inline bool uint8_array_equal(const uint8_t* arr1, const uint8_t* arr2, size_t size) {
    MEH_COMPARE_ARRAY(uint8_t);
}

static inline bool int16_array_equal(const int16_t* arr1, const int16_t* arr2, size_t size) {
    MEH_COMPARE_ARRAY(int16_t);
}

static inline bool uint16_array_equal(const uint16_t* arr1, const uint16_t* arr2, size_t size) {
    MEH_COMPARE_ARRAY(uint16_t);
}

static inline bool int32_array_equal(const int32_t* arr1, const int32_t* arr2, size_t size) {
    MEH_COMPARE_ARRAY(int32_t);
}

static inline bool uint32_array_equal(const uint32_t* arr1, const uint32_t* arr2, size_t size) {
    MEH_COMPARE_ARRAY(uint32_t);
}

static inline bool int64_array_equal(const int64_t* arr1, const int64_t* arr2, size_t size) {
    MEH_COMPARE_ARRAY(int64_t);
}

static inline bool uint64_array_equal(const uint64_t* arr1, const uint64_t* arr2, size_t size) {
    MEH_COMPARE_ARRAY(uint64_t);
}

#undef MEH_COMPARE_ARRAY

