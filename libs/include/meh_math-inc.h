/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: MeH
 * File: meh_math-inc.h
 * Brief: part of MeH
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef MEH
#warning This is intended to be part of the MeH C Library.
#endif

/* MeH.MATH -- Common Constants */

// independent set of common math constants
#define VALUE_PI 3.14159265358979323846
#define VALUE_E 2.718281828459045 // euler's number (alternative: exp(1.0))
#define VALUE_LOG2E 1.4426950408889634 // log_2 e
#define VALUE_LOG10E 0.4342944819 // log10 e (alternative: 1.0 / log(10.0))
#define VALUE_LNPI 1.1447298858494001 // log_e pi
#define VALUE_INVERSE_PI (1.0 / VALUE_PI)
#define VALUE_2PI (2.0 * VALUE_PI)
#define VALUE_TAU VALUE_2PI
#define VALUE_PIDIV2 (VALUE_PI / 2.0)
#define VALUE_PIDIV4 (VALUE_PI / 4.0)
#define VALUE_1DIVPI (1.0 / VALUE_PI)
#define VALUE_2DIVPI (2.0 / VALUE_PI)
#define VALUE_SQRTPI 1.772453850905516 // alternative: sqrt(VALUE_PI)
#define VALUE_INVERSE_SQRTPI (1.0 / VALUE_SQRTPI)
#define VALUE_2SQRTPI (2.0 / VALUE_SQRTPI)
#define VALUE_SQRT2 1.414213562373095 // alternative: sqrt(2.0)
#define VALUE_SQRT3 1.732050807568877 // alternative: sqrt(3.0)
#define VALUE_INVERSE_SQRT3 (1.0 / VALUE_SQRT3)
#define VALUE_1DIVSQRT2 (1.0 / VALUE_SQRT2) // silver ratio
#define VALUE_PHI 1.6180339887498948 // golden ratio
#define VALUE_INVERSE_PHI (1.0 / VALUE_PHI)
#define VALUE_EULER_MASCHERONI 0.5772156649015328 // gamma
#define VALUE_ALPHA 0.0072992700729927 // fine-structure constant (alternative: 1/137)

#define VALUE_DEGREES_TO_RADIANS (VALUE_PI / 180) // ~ 0.0174533
#define VALUE_RADIANS_TO_DEGREES (180 / VALUE_PI) // ~ 57.2958

// array of the prime numbers up to 1000
static const int PRIMES_UP_TO_1000[] = {
      2,   3,   5,   7,  11,
     13,  17,  19,  23,  29,
     31,  37,  41,  43,  47,
     53,  59,  61,  67,  71,
     73,  79,  83,  89,  97,
    101, 103, 107, 109, 113,
    127, 131, 137, 139, 149,
    151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199,
    211, 223, 227, 229, 233,
    239, 241, 251, 257, 263,
    269, 271, 277, 281, 283, 293,
    307, 311, 313, 317, 331,
    337, 347, 349, 353, 359,
    367, 373, 379, 383, 389, 397,
    401, 409, 419, 421, 431,
    433, 439, 443, 449, 457,
    461, 463, 467, 479, 487, 491, 499,
    503, 509, 521, 523, 541,
    547, 557, 563, 569, 571,
    577, 587, 593, 599,
    601, 607, 613, 617, 619,
    631, 641, 643, 647, 653,
    659, 661, 673, 677, 683, 691,
    701, 709, 719, 727, 733,
    739, 743, 751, 757, 761,
    769, 773, 787, 797,
    809, 811, 821, 823, 827,
    829, 839, 853, 857, 859,
    863, 877, 881, 883, 887,
    907, 911, 919, 929, 937,
    941, 947, 953, 967, 971,
    977, 983, 991, 997
};

/* MeH.MATH -- Various Utilities */

// returns the greater of two values
#define MAX(a, b) ({        \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a > _b ? _a : _b;      \
})

// returns the lesser of two values
#define MIN(a, b) ({        \
    __typeof__(a) _a = (a); \
    __typeof__(b) _b = (b); \
    _a < _b ? _a : _b;      \
})

// returns the square of a number
#define SQUARE(x) ({        \
    __typeof__(x) _x = (x); \
    _x * _x;                \
})

// returns the cube of a number
#define CUBE(x) ({          \
    __typeof__(x) _x = (x); \
    _x * _x * _x;           \
})

// returns the integer part of a floating-point number
#define TRUNC(x) ((int)(x))

// returns the fractional part of a floating-point number
#define FRAC(x) ((x) - TRUNC(x))

// returns the negative value
#define NEG(x) (-(x))

// returns the absolute value
#define ABS(x) ({           \
    __typeof__(x) _x = (x); \
    _x < 0 ? -_x : _x;      \
})

// returns the restricted value to a given range
#define CLAMP(x, lo, hi) ({                 \
    __typeof__(x) _x = (x);                 \
    __typeof__(lo) _lo = (lo);              \
    __typeof__(hi) _hi = (hi);              \
    _x < _lo ? _lo : (_x > _hi ? _hi : _x); \
})

// returns true if the value is inside the provided boundaries (inclusive)
#define IN_RANGE(x, min, max) (((x) >= (min)) && ((x) <= (max)))

// same as IN_RANGE but bitwise optimized for signed integers and performance-critical code
#define IN_RANGE_FAST(x, min, max) ((((x) - (min)) | ((max) - (x))) >= 0) // if x is outside the range, one of the subtractions will be negative, setting the sign bit

// determines if the provided value is an even number
static inline bool is_even(intmax_t num) {
    return num % 2 == 0 ? true : false;
}

// determines if the provided value is an odd number
static inline bool is_odd(intmax_t num) {
    return num % 2 != 0 ? true : false;
}

// determines if the first provided value is divisible by the second provided value
static inline bool is_divisible_by(intmax_t number, intmax_t factor) {
    return number % factor == 0;
}

// converts the provided value from degrees to radians
static inline double degrees_to_radians(double degrees) {
    return degrees * VALUE_DEGREES_TO_RADIANS;
}

// converts the provided value from radians to degrees
static inline double radians_to_degrees(double radians) {
    return radians * VALUE_RADIANS_TO_DEGREES;
}

