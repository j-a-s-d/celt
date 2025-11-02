/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_math-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#define _SQRT_IMPL(typ, nam, nan, fab) \
    typ nam(typ x) { \
        if (x < 0) return nan; \
        if (x == 0 || x == 1) return x; \
        typ y = x; \
        typ z = (y + x / y) / 2; \
        while (fab(y - z) >= 0.00001) { /* iterate until precision of 5 decimal places */ \
            y = z; \
            z = (y + x / y) / 2; \
        } \
        return z; \
    }

_SQRT_IMPL(float, float_sqrt, float_NaN, float_abs)
_SQRT_IMPL(double, double_sqrt, double_NaN, double_abs)
_SQRT_IMPL(long double, long_double_sqrt, long_double_NaN, long_double_abs)

#undef _SQRT_IMPL

float float_interpolate_custom(float value, float input_min, float input_max, float output_min, float output_max, float epsilon) {
    float input_span = input_max - input_min;
    if (input_min == input_max /* logical equality */
    || input_span == 0.0f /* arithmetic equality */
    || float_abs(input_span) <= epsilon /* near-zero check (fabsf alternative function) */
    ) return float_NaN;
    float output_span = output_max - output_min;
    float scaled_value = (value - input_min) / input_span;
    return output_min + (scaled_value * output_span);
}

double double_interpolate_custom(double value, double input_min, double input_max, double output_min, double output_max, double epsilon) {
    double input_span = input_max - input_min;
    if (input_min == input_max /* logical equality */
    || input_span == 0.0f /* arithmetic equality */
    || double_abs(input_span) <= epsilon /* near-zero check (fasb alternative function) */
    ) return double_NaN;
    double output_span = output_max - output_min;
    double scaled_value = (value - input_min) / input_span;
    return output_min + (scaled_value * output_span);
}

void decimal_degrees_to_dms(double decimal_degrees, int* degrees, int* minutes, double* seconds) {
    *degrees = (int)decimal_degrees;
    double fractional = double_abs(decimal_degrees - *degrees) * 60.0;
    *minutes = (int)fractional;
    *seconds = (fractional - *minutes) * 60.0;
    if (*seconds >= 59.9999) {
        *seconds = 0;
        (*minutes)++;
    }
    if (*minutes >= 60) {
        *minutes = 0;
        if (decimal_degrees >= 0)
            (*degrees)++;
        else
            (*degrees)--;
    }
}

uint8_t* get_histogram(uint8_t* buffer, size_t length) {
    if (buffer == NULL || length == 0) return NULL;
    RET_CALLOC(uint8_t, 256, {
        for (size_t i = 0; i < length; ++i)
            result[buffer[i]]++;
    });
}

