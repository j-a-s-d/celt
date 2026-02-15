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

#define _ATAN_IMPL(typ, nam) \
    typ nam(typ z) { /* aproximation to the arctan for |z| <= 1 */ \
        if (z > 1.0) return (VALUE_PI / 2.0) - float_atan(1.0 / z); \
        if (z < -1.0) return (-VALUE_PI / 2.0) - float_atan(1.0 / z); \
        /* Taylor series (first terms for an aceptable precision) */ \
        /* atan(z) ≈ z - z^3/3 + z^5/5 - z^7/7... */ \
        typ z2 = z * z; \
        return z * (1.0 - z2 * (0.3333333 - z2 * (0.2 - z2 * (0.1428571 - z2 * 0.1111111)))); \
    }

_ATAN_IMPL(float, float_atan)
_ATAN_IMPL(double, double_atan)
_ATAN_IMPL(long double, long_double_atan)

#undef _ATAN_IMPL

/* NOTE: for more precision you will need to implement other solutions like:
double double_atan(double z) { // minimax approximation
    double abs_z = double_abs(z); 
    double res;
    if (abs_z <= 1.0) {
        // optimized coeficients for the range [0, 1]
        res = (abs_z * (1.0 + 0.55913709 * abs_z * abs_z)) / 
              (1.0 + 0.89246305 * abs_z * abs_z);
        // or a more polynomic but precise way
        //res = abs_z * (0.9998660 - 0.3302995*abs_z*abs_z + 0.1801410*abs_z*abs_z*abs_z*abs_z);
    } else {
        double inv_z = 1.0 / abs_z;
        res = (VALUE_PI / 2.0) - (inv_z * (1.0 + 0.55913709 * inv_z * inv_z)) / 
              (1.0 + 0.89246305 * inv_z * inv_z);
    }
    return (z < 0) ? -res : res;
}
*/

#define _ATAN2_IMPL(typ, nam, ata) \
    typ nam(typ y, typ x) { \
        if (x > 0) { \
            return ata(y / x); \
        } else if (x < 0) { \
            if (y >= 0) \
                return ata(y / x) + VALUE_PI; \
            else \
                return ata(y / x) - VALUE_PI; \
        } else { /* x == 0 */ \
            if (y > 0) return VALUE_PI / 2.0; \
            if (y < 0) return -VALUE_PI / 2.0; \
        } \
        return 0.0; /* undefined */ \
    }
    
_ATAN2_IMPL(float, float_atan2, float_atan)
_ATAN2_IMPL(double, double_atan2, double_atan)
_ATAN2_IMPL(long double, long_double_atan2, long_double_atan)

#undef _ATAN2_IMPL

#define _COS_IMPL(typ, nam, nor) \
    typ nam(typ x) { \
        x = nor(x); \
        typ x2 = x * x; \
        /* Taylor aproximation of 5 terms */ \
        return 1.0 - (x2 / 2.0) + (x2 * x2 / 24.0) - (x2 * x2 * x2 / 720.0) + (x2 * x2 * x2 * x2 / 40320.0); \
    }

_COS_IMPL(float, float_cos, float_normalize_pi_range)
_COS_IMPL(double, double_cos, double_normalize_pi_range)
_COS_IMPL(long double, long_double_cos, long_double_normalize_pi_range)

#undef _COS_IMPL

#define _SIN_IMPL(typ, nam, nor) \
    typ nam(typ x) { \
        x = nor(x); \
        typ x2 = x * x; \
        /* Taylor aproximation of 5 terms */ \
        return x * (1.0 - (x2 / 6.0) + (x2 * x2 / 120.0) - (x2 * x2 * x2 / 5040.0) + (x2 * x2 * x2 * x2 / 362880.0)); \
    }

_SIN_IMPL(float, float_sin, float_normalize_pi_range)
_SIN_IMPL(double, double_sin, double_normalize_pi_range)
_SIN_IMPL(long double, long_double_sin, long_double_normalize_pi_range)

#undef _SIN_IMPL

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

void decimal_degrees_to_dms(double decimal_degrees, int* degrees, int* minutes, double* seconds, bool* negative) {
    *negative = decimal_degrees < 0.0;
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

