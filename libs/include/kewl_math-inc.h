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

// FLOATING-POINT

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
 * Calculates the cosine of the given float number.
 * Analog functionality to: math.h, cosf, -lm.
 */
float float_cos(float x);

/**
 * Calculates the cosine of the given double number.
 * Analog functionality to: math.h, cos, -lm.
 */
double double_cos(double x);

/**
 * Calculates the cosine of the given long double number.
 * Analog functionality to: math.h, cosl, -lm.
 */
long double long_double_cos(long double x);

/**
 * Calculates the sine of the given float number.
 * Analog functionality to: math.h, sinf, -lm.
 */
float float_sin(float x);

/**
 * Calculates the sine of the given double number.
 * Analog functionality to: math.h, sin, -lm.
 */
double double_sin(double x);

/**
 * Calculates the sine of the given long double number.
 * Analog functionality to: math.h, sinl, -lm.
 */
long double long_double_sin(long double x);

/**
 * Calculates the calculates the arc tangent (inverse tangent) of the given float number.
 * Analog functionality to: math.h, atanf, -lm.
 */
float float_atan(float z);

/**
 * Calculates the calculates the arc tangent (inverse tangent) of the given double number.
 * Analog functionality to: math.h, atan, -lm.
 */
double double_atan(double z);

/**
 * Calculates the calculates the arc tangent (inverse tangent) of the given double number.
 * Analog functionality to: math.h, atanl, -lm.
 */
long double long_double_atan(long double z);

/**
 * Calculates the four-quadrant inverse tangent of the given point's float coordinates (y, x), returning the angle in [radians] between the positive x-axis and the point.
 * Analog functionality to: math.h, atan2f, -lm.
 */
float float_atan2(float y, float x);

/**
 * Calculates the four-quadrant inverse tangent of the given point's double coordinates (y, x), returning the angle in [radians] between the positive x-axis and the point.
 * Analog functionality to: math.h, atan2, -lm.
 */
double double_atan2(double y, double x);

/**
 * Calculates the four-quadrant inverse tangent of the given point's long double coordinates (y, x), returning the angle in [radians] between the positive x-axis and the point.
 * Analog functionality to: math.h, atan2l, -lm.
 */
long double long_double_atan2(long double y, long double x);

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

// CONVERSION

/**
 * Converts decimal degrees to degrees, minutes, seconds.
 */
void decimal_degrees_to_dms(double decimal_degrees, int* degrees, int* minutes, double* seconds, bool* negative);

/**
 * Converts degrees, minutes, seconds to decimal degrees.
 */
static inline double dms_to_decimal_degrees(int degrees, int minutes, double seconds, bool negative) {
    double decimal_degrees = abs(degrees) + (minutes / 60.0) + (seconds / 3600.0);
    if (negative) decimal_degrees = -decimal_degrees;
    return decimal_degrees;
}

// GEOMETRY

/**
 * Normalizes the provided float value to be within -PI and PI.
 */
static inline float float_normalize_pi_range(float x) {
    while (x > VALUE_PI) x -= 2.0 * VALUE_PI;
    while (x < -VALUE_PI) x += 2.0 * VALUE_PI;
    return x;
}

/**
 * Normalizes the provided double value to be within -PI and PI.
 */
static inline double double_normalize_pi_range(double x) {
    while (x > VALUE_PI) x -= 2.0 * VALUE_PI;
    while (x < -VALUE_PI) x += 2.0 * VALUE_PI;
    return x;
}

/**
 * Normalizes the provided long double value to be within -PI and PI.
 */
static inline long double long_double_normalize_pi_range(long double x) {
    while (x > VALUE_PI) x -= 2.0 * VALUE_PI;
    while (x < -VALUE_PI) x += 2.0 * VALUE_PI;
    return x;
}

/**
 * Normalizes the angle to be within 0 and 360.
 */
static inline double normalize_circular_angle(double angle) {
    while (angle < 0.0) angle += 360.0;
    while (angle >= 360.0) angle -= 360.0;
    return angle;
}

/**
 * Gets the opposite point in a circle.
 */
static inline double get_circular_opposite_point(double value) {
    value = normalize_circular_angle(value);
    return value >= 180.0 ? value - 180.0 : value + 180.0;
}

/**
 * Checks if 'point' angle is between 'start' and 'end' angles on a circle (inclusive).
 */
static inline bool is_circular_point_between(double point, double start, double end) {
    point = normalize_circular_angle(point);
    start = normalize_circular_angle(start);
    end = normalize_circular_angle(end);
    return start <= end
        ? ((point >= start) && (point < end)) // normal interval (no wrap-around)
        : ((point >= start) || (point < end)); // wrap-around interval (e.g. start=350, end=10)
}

/**
 * Calculates the circular distance moving clockwise from 'from' to 'to'. Results will be always positive.
 */
static inline double get_circular_distance(double from, double to) {
    double result = normalize_circular_angle(to) - normalize_circular_angle(from);
    if (result < 0.0) result += 360.0;
    return result;
}

/**
 * Calculates the shortest circular offset between 'from' and 'to'. Results will be always between -180.0 and 180.0.
 */
static inline double get_circular_shortest_offset(double from, double to) {
    double angle = normalize_circular_angle(to - from);
    return angle <= 180.0 ? angle : angle - 360.0;
}

/**
 * Calculates the offset percentage of 'point' between 'start' and 'end'.
 */
static inline double get_circular_offset_percentage_between(double point, double start, double end) {
    return (get_circular_distance(start, point) / get_circular_distance(start, end)) * 100.0;
}

/**
 * Checks if 'point1' angle is before 'point2'.
 */
static inline bool is_circular_point_before(double point1, double point2) {
    return get_circular_shortest_offset(point1, point2) > 0.0;
}

// STATISTICS

/**
 * Calculates the histogram (frequency) of each byte in the provided buffer.
 */
uint8_t* get_histogram(uint8_t* buffer, size_t length);

