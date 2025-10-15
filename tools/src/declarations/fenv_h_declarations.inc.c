const char* fenv_h_name = "fenv.h";

const char* fenv_h_globals[] = {
    NULL
};

// Types declared in fenv.h
const char* fenv_h_types[] = {
    "fenv_t", // Represents the entire floating-point environment
    "fexcept_t", // Represents the floating-point status flags collectively
    "femode_t", // Represents floating-point environment modes (new in C23)
    NULL
};

// Macros declared in fenv.h
const char* fenv_h_macros[] = {
    // Floating-point exceptions
    "FE_DIVBYZERO",
    "FE_INEXACT",
    "FE_INVALID",
    "FE_OVERFLOW",
    "FE_UNDERFLOW",
    "FE_ALL_EXCEPT",
    // Rounding modes
    "FE_TONEAREST",
    "FE_DOWNWARD",
    "FE_UPWARD",
    "FE_TOWARDZERO",
    "FE_TONEARESTFROMZERO", // new in C23
    // Default environment
    "FE_DFL_ENV", // Pointer to the default floating-point environment at program startup
    "FE_DFL_MODE", // Represents the default floating-point environment mode (new in C23)
    // Decimal floating-point rounding modes (optional, implementation-defined)
    "FE_DEC_TONEAREST",
    "FE_DEC_TONEARESTFROMZERO",
    "FE_DEC_DOWNWARD",
    "FE_DEC_UPWARD",
    "FE_DEC_TOWARDZERO",
    // These are from implementations supporting decimal FP, e.g., IBM
    "_FE_DEC_AWAYFROMZERO",
    "_FE_DEC_PREPAREFORSHORTER",
    "_FE_DEC_TONEARESTTOWARDZERO",
    // Other
    "FE_DFL_ENV", // A macro expanding to a pointer to the default floating-point environment object
    "FENV_ROUND", // Controls rounding mode pragmatically
    NULL
};

// Functions declared in fenv.h
const char* fenv_h_functions[] = {
    "feclearexcept", // Clear specified floating-point exceptions
    "fegetexceptflag", // Store specified exception flags into flagp
    "feraiseexcept", // Raise specified floating-point exceptions
    "fesetexceptflag", // Set exception flags from flagp
    "fetestexcept", // Test which specified exceptions are currently set
    "fegetround", // Get current rounding mode
    "fesetround", // Set rounding mode
    "fegetenv", // Store current floating-point environment in envp
    "feholdexcept", // Save current environment in envp and clear exceptions
    "fesetenv", // Restore floating-point environment from envp
    "feupdateenv", // Restore environment from envp and raise saved exceptions
    // New in C23
    "fegetmode", // Get current floating-point environment mode
    "fesetmode", // Set floating-point environment mode
    "fesetexcept", // Set specified exceptions (more fine-grained control)
    "fetestexceptflag", // Test exception flags from flagp
    NULL
};

