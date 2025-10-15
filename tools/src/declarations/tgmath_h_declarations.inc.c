const char* tgmath_h_name = "tgmath.h";

const char* tgmath_h_globals[] = {
    // <tgmath.h> provides type-generic macros for mathematical functions,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in tgmath.h
const char* tgmath_h_types[] = {
    // tgmath.h does not declare new types; it includes math.h and complex.h
    NULL
};

// Macros declared in tgmath.h
const char* tgmath_h_macros[] = {
    // Type-generic macros corresponding to many math.h and complex.h functions:
    "atan2",
    "cbrt",
    "ceil",
    "copysign",
    "erf",
    "erfc",
    "exp2",
    "expm1",
    "fdim",
    "floor",
    "fma",
    "fmax",
    "fmin",
    "fmod",
    "frexp",
    "hypot",
    "ilogb",
    "ldexp",
    "lgamma",
    "llrint",
    "llround",
    "log10",
    "log1p",
    "log2",
    "logb",
    "lrint",
    "lround",
    "nearbyint",
    "nextafter",
    "nexttoward",
    "remainder",
    "remquo",
    "rint",
    "round",
    "scalbn",
    "scalbln",
    "tgamma",
    "trunc",
    // Complex-only macros:
    "carg",
    "cimag",
    "conj",
    "cproj",
    "creal",
    NULL
};

// Functions declared in tgmath.h
const char* tgmath_h_functions[] = {
    // tgmath.h declares no functions itself; it provides type-generic macros that dispatch to math.h or complex.h functions
    NULL
};

