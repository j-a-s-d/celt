const char* complex_h_name = "complex.h";

const char* complex_h_globals[] = {
    // <complex.h> provides types and functions for complex number arithmetic,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in complex.h
const char* complex_h_types[] = {
    "float _Complex",
    "double _Complex",
    "long double _Complex",
    NULL
};

// Macros declared in complex.h
const char* complex_h_macros[] = {
    "complex",       // expands to _Complex
    "_Complex_I",    // constant of type const float _Complex representing imaginary unit
    "imaginary",     // expands to _Imaginary (optional)
    "_Imaginary_I",  // constant of type const float _Imaginary representing imaginary unit (optional)
    "I",             // usually defined as _Complex_I for convenience
    NULL
};

// Functions declared in complex.h
const char* complex_h_functions[] = {
    "cabs",      // magnitude of complex number (double)
    "cabsf",     // magnitude (float)
    "cabsl",     // magnitude (long double)
    "carg",      // phase angle (double)
    "cargf",     // phase angle (float)
    "cargl",     // phase angle (long double)
    "creal",     // real part (double)
    "crealf",    // real part (float)
    "creall",    // real part (long double)
    "cimag",     // imaginary part (double)
    "cimagf",    // imaginary part (float)
    "cimagl",    // imaginary part (long double)
    "conj",      // complex conjugate (double)
    "conjf",     // complex conjugate (float)
    "conjl",     // complex conjugate (long double)
    "cproj",     // projection on Riemann sphere (double)
    "cprojf",    // projection (float)
    "cprojl",    // projection (long double)
    "cpow",      // power function (double)
    "cpowf",     // power function (float)
    "cpowl",     // power function (long double)
    "cexp",      // exponential (double)
    "cexpf",     // exponential (float)
    "cexpl",     // exponential (long double)
    "clog",      // natural logarithm (double)
    "clogf",     // natural logarithm (float)
    "clogl",     // natural logarithm (long double)
    "csin",      // sine (double)
    "csinf",     // sine (float)
    "csinl",     // sine (long double)
    "ccos",      // cosine (double)
    "ccosf",     // cosine (float)
    "ccosl",     // cosine (long double)
    "ctan",      // tangent (double)
    "ctanf",     // tangent (float)
    "ctanl",     // tangent (long double)
    "casin",     // arc sine (double)
    "casinf",    // arc sine (float)
    "casinl",    // arc sine (long double)
    "cacos",     // arc cosine (double)
    "cacosf",    // arc cosine (float)
    "cacosl",    // arc cosine (long double)
    "catan",     // arc tangent (double)
    "catanf",    // arc tangent (float)
    "catanl",    // arc tangent (long double)
    "csinh",     // hyperbolic sine (double)
    "csinhf",    // hyperbolic sine (float)
    "csinhl",    // hyperbolic sine (long double)
    "ccosh",     // hyperbolic cosine (double)
    "ccoshf",    // hyperbolic cosine (float)
    "ccoshl",    // hyperbolic cosine (long double)
    "ctanh",     // hyperbolic tangent (double)
    "ctanhf",    // hyperbolic tangent (float)
    "ctanhl",    // hyperbolic tangent (long double)
    NULL
};

