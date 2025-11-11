/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: MeH
 * File: meh_fp-inc.h
 * Brief: part of MeH
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef MEH
#warning This is intended to be part of the MeH C Library.
#endif

/* MeH.FP -- Floating-Point Functionalities */

#ifndef MEH_FLOAT_EPSILON
    #define MEH_FLOAT_EPSILON 1e-7f
#endif
#ifndef MEH_DOUBLE_EPSILON
    #define MEH_DOUBLE_EPSILON 1e-12
#endif
#ifndef MEH_LONG_DOUBLE_EPSILON
    #define MEH_LONG_DOUBLE_EPSILON 1e-12L
#endif

#define float_NaN __builtin_nanf("")
#define double_NaN __builtin_nan("")
#define long_double_NaN __builtin_nanl("")

#define float_isNaN __builtin_isnanf
#define double_isNaN __builtin_isnan
#define long_double_isNaN __builtin_isnanl

#define float_string_format "%f"
#define double_string_format "%f"
#define long_double_string_format "%Lf"

// returns the absolute value for the given float number (local alternative to: math.h, fabsf, -lm)
static inline float float_abs(float x) {
    return (x < 0) ? -x : x;
}

// returns the absolute value for the given double number (local alternative to: math.h, fabs, -lm)
static inline double double_abs(double x) {
    return (x < 0) ? -x : x;
}

// returns the absolute value for the given long double number (local alternative to: math.h, fabsl, -lm)
static inline long double long_double_abs(long double x) {
    return (x < 0) ? -x : x;
}

// rounds the given float number
static inline int float_round(float x) {
    return (int)(x < 0 ? x - 0.5f : x + 0.5f);
}

// rounds the given double number
static inline int double_round(double x) {
    return (int)(x < 0 ? x - 0.5 : x + 0.5);
}

// rounds the given long double number
static inline int long_double_round(long double x) {
    return (int)(x < 0 ? x - 0.5L : x + 0.5L);
}

// returns true if the absolute difference between the two float numbers is smaller than a predefined small number (epsilon)
static inline bool float_equal(float a, float b, float epsilon) {
    return float_abs(a - b) < epsilon;
}

// returns true if the absolute difference between the two double numbers is smaller than a predefined small number (epsilon)
static inline bool double_equal(double a, double b, double epsilon) {
    return double_abs(a - b) < epsilon;
}

// returns true if the absolute difference between the two long double numbers is smaller than a predefined small number (epsilon)
static inline bool long_double_equal(long double a, long double b, long double epsilon) {
    return long_double_abs(a - b) < epsilon;
}

#undef MEH_COMPARE_ARRAY

#define MEH_COMPARE_FP_ARRAY(type, abs_func, tolerance) \
    if (arr1 == NULL || arr2 == NULL) return false; \
    for (size_t i = 0; i < size; i++) \
        if (abs_func(arr1[i] - arr2[i]) > tolerance) return false; \
    return true;

static inline bool float_array_equal(const float* arr1, const float* arr2, size_t size) {
    MEH_COMPARE_FP_ARRAY(float, float_abs, MEH_FLOAT_EPSILON);
}

static inline bool double_array_equal(const double* arr1, const double* arr2, size_t size) {
    MEH_COMPARE_FP_ARRAY(double, double_abs, MEH_DOUBLE_EPSILON);
}

static inline bool long_double_array_equal(const long double* arr1, const long double* arr2, size_t size) {
    MEH_COMPARE_FP_ARRAY(long double, long_double_abs, MEH_LONG_DOUBLE_EPSILON);
}

static inline bool float_array_equal_custom(const float* arr1, const float* arr2, size_t size, float epsilon) {
    MEH_COMPARE_FP_ARRAY(float, float_abs, epsilon);
}

static inline bool double_array_equal_custom(const double* arr1, const double* arr2, size_t size, double epsilon) {
    MEH_COMPARE_FP_ARRAY(double, double_abs, epsilon);
}

static inline bool long_double_array_equal_custom(const long double* arr1, const long double* arr2, size_t size, long double epsilon) {
    MEH_COMPARE_FP_ARRAY(long double, long_double_abs, epsilon);
}

#undef MEH_COMPARE_FP_ARRAY

