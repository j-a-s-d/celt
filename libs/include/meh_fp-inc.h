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
// NOTE: if you can't use the builtin isnan functions, you can write your own simply by comparing the value to itself (x != x).

#define float_signbit __builtin_signbitf
#define double_signbit __builtin_signbit
#define long_double_signbit __builtin_signbitl

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

// rounds the given float number (local alternative to: math.h, roundf, -lm)
static inline int float_round(float x) {
    return (int)(x < 0 ? x - 0.5f : x + 0.5f);
}

// rounds the given double number (local alternative to: math.h, round, -lm)
static inline int double_round(double x) {
    return (int)(x < 0 ? x - 0.5 : x + 0.5);
}

// rounds the given long double number (local alternative to: math.h, roundl, -lm)
static inline int long_double_round(long double x) {
    return (int)(x < 0 ? x - 0.5L : x + 0.5L);
}

// returns the max float value between the two provided
static inline double float_max(double a, double b) {
    if (float_isNaN(a)) return b;
    if (float_isNaN(b)) return a;
    if (a == 0.0f && b == 0.0f)
        return (!float_signbit(a) && float_signbit(b)) ? a : b;
    return a > b ? a : b;
}

// returns the max double value between the two provided
static inline double double_max(double a, double b) {
    if (double_isNaN(a)) return b;
    if (double_isNaN(b)) return a;
    if (a == 0.0 && b == 0.0)
        return (!double_signbit(a) && double_signbit(b)) ? a : b;
    return a > b ? a : b;
}

// returns the max long double value between the two provided
static inline long double long_double_max(double a, double b) {
    if (long_double_isNaN(a)) return b;
    if (long_double_isNaN(b)) return a;
    if (a == 0.0L && b == 0.0L)
        return (!long_double_signbit(a) && long_double_signbit(b)) ? a : b;
    return a > b ? a : b;
}

// returns the min float value between the two provided
static inline double float_min(double a, double b) {
    if (float_isNaN(a)) return b;
    if (float_isNaN(b)) return a;
    if (a == 0.0f && b == 0.0f)
        return float_signbit(b) ? b : a;
    return a < b ? a : b;
}

// returns the min double value between the two provided
static inline double double_min(double a, double b) {
    if (double_isNaN(a)) return b;
    if (double_isNaN(b)) return a;
    if (a == 0.0 && b == 0.0)
        return double_signbit(b) ? b : a;
    return a < b ? a : b;
}

// returns the min long double value between the two provided
static inline long double long_double_min(double a, double b) {
    if (long_double_isNaN(a)) return b;
    if (long_double_isNaN(b)) return a;
    if (a == 0.0f && b == 0.0f)
        return long_double_signbit(b) ? b : a;
    return a < b ? a : b;
}

#ifndef meh_fabsf
    #define meh_fabsf(x) float_abs(x)
#endif

#ifndef meh_fabs
    #define meh_fabs(x) double_abs(x)
#endif

#ifndef meh_fabsl
    #define meh_fabsl(x) long_double_abs(x)
#endif

#ifndef meh_roundf
    #define meh_roundf(x) float_round(x)
#endif

#ifndef meh_round
    #define meh_round(x) double_round(x)
#endif

#ifndef meh_roundl
    #define meh_roundl(x) long_double_round(x)
#endif

#ifndef meh_fmaxf
    #define meh_fmaxf(x) float_max(x)
#endif

#ifndef meh_fmax
    #define meh_fmax(x) double_max(x)
#endif

#ifndef meh_fmaxl
    #define meh_fmaxl(x) long_double_max(x)
#endif

#ifndef meh_fminf
    #define meh_fminf(x) float_min(x)
#endif

#ifndef meh_fmin
    #define meh_fmin(x) double_min(x)
#endif

#ifndef meh_fminl
    #define meh_fminl(x) long_double_min(x)
#endif

// returns true if the absolute difference between the two float numbers is smaller than a predefined small number (epsilon)
static inline bool float_equal(float a, float b, float epsilon) {
    return meh_fabsf(a - b) < epsilon;
}

// returns true if the absolute difference between the two double numbers is smaller than a predefined small number (epsilon)
static inline bool double_equal(double a, double b, double epsilon) {
    return meh_fabs(a - b) < epsilon;
}

// returns true if the absolute difference between the two long double numbers is smaller than a predefined small number (epsilon)
static inline bool long_double_equal(long double a, long double b, long double epsilon) {
    return meh_fabsl(a - b) < epsilon;
}

#undef MEH_COMPARE_ARRAY

#define MEH_COMPARE_FP_ARRAY(type, abs_func, tolerance) \
    if (arr1 == NULL || arr2 == NULL) return false; \
    for (size_t i = 0; i < size; i++) \
        if (abs_func(arr1[i] - arr2[i]) > tolerance) return false; \
    return true;

static inline bool float_array_equal(const float* arr1, const float* arr2, size_t size) {
    MEH_COMPARE_FP_ARRAY(float, meh_fabsf, MEH_FLOAT_EPSILON);
}

static inline bool double_array_equal(const double* arr1, const double* arr2, size_t size) {
    MEH_COMPARE_FP_ARRAY(double, meh_fabs, MEH_DOUBLE_EPSILON);
}

static inline bool long_double_array_equal(const long double* arr1, const long double* arr2, size_t size) {
    MEH_COMPARE_FP_ARRAY(long double, meh_fabsl, MEH_LONG_DOUBLE_EPSILON);
}

static inline bool float_array_equal_custom(const float* arr1, const float* arr2, size_t size, float epsilon) {
    MEH_COMPARE_FP_ARRAY(float, meh_fabsf, epsilon);
}

static inline bool double_array_equal_custom(const double* arr1, const double* arr2, size_t size, double epsilon) {
    MEH_COMPARE_FP_ARRAY(double, meh_fabs, epsilon);
}

static inline bool long_double_array_equal_custom(const long double* arr1, const long double* arr2, size_t size, long double epsilon) {
    MEH_COMPARE_FP_ARRAY(long double, meh_fabsl, epsilon);
}

#undef MEH_COMPARE_FP_ARRAY

