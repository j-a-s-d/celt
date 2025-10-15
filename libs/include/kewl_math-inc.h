/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_math-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

/**
 * Calculates the square root of the given float number.
 * Analog functionality to: math.h, sqrtf, -lm.
 */
float float_sqrt(float x);

/**
 * Calculates the square root of the given double number.
 * Analog functionality to: math.h, sqrt, -lm.
 */
double double_sqrt(double x);

/**
 * Calculates the square root of the given long double number.
 * Analog functionality to: math.h, sqrtl, -lm.
 */
long double long_double_sqrt(long double x);

/**
 * Translates the value from the input range margins to the output range margins.
 * Returns NAN if input range is invalid in some way: logical equality, arithmetic equality
 * or near-zero check (it accepts a custom epsilon value, for ex. you can use the strictest
 * float.h's FLT_EPSILON).
 */
float float_interpolate_custom(float value, float input_min, float input_max, float output_min, float output_max, float epsilon);

/**
 * Translates the value from the input range margins to the output range margins.
 * Returns NAN if input range is invalid in some way: logical equality, arithmetic equality
 * or near-zero check (it uses a safe-enough epsilon tolerance value of 1e-7f by default).
 */
static inline float float_interpolate(float value, float input_min, float input_max, float output_min, float output_max) {
    return float_interpolate_custom(value, input_min, input_max, output_min, output_max, MEH_FLOAT_EPSILON);
}

/**
 * Translates the value from the input range margins to the output range margins.
 * Returns NAN if input range is invalid in some way: logical equality, arithmetic equality
 * or near-zero check (it accepts a custom epsilon value, for ex. you can use the strictest
 * float.h's DBL_EPSILON).
 */
double double_interpolate_custom(double value, double input_min, double input_max, double output_min, double output_max, double epsilon);

/**
 * Translates the value from the input range margins to the output range margins.
 * Returns NAN if input range is invalid in some way: logical equality, arithmetic equality
 * or near-zero check (it uses a safe-enough epsilon tolerance value of 1e-12 by default).
 */
static inline double double_interpolate(double value, double input_min, double input_max, double output_min, double output_max) {
    return double_interpolate_custom(value, input_min, input_max, output_min, output_max, MEH_DOUBLE_EPSILON);
}

/**
 * Calculates the histogram (frequency) of each byte in the provided buffer.
 */
uint8_t* get_histogram(uint8_t* buffer, size_t length);

