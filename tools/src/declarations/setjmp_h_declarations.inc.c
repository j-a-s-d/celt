const char* setjmp_h_name = "setjmp.h";

const char* setjmp_h_globals[] = {
    // setjmp.h defines the type jmp_buf (an array type for environment storage),
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in setjmp.h
const char* setjmp_h_types[] = {
    "jmp_buf",
    "sigjmp_buf",   // POSIX extension for signal masks
    NULL
};

// Macros declared in setjmp.h
const char* setjmp_h_macros[] = {
    "setjmp",       // macro saving the calling environment
    "sigsetjmp",    // POSIX macro saving environment and optionally signal mask
    NULL
};

// Functions declared in setjmp.h
const char* setjmp_h_functions[] = {
    "longjmp",      // restores environment saved by setjmp
    "siglongjmp",   // POSIX version restoring environment and signal mask
    "_setjmp",      // non-standard variant without saving signal mask
    "_longjmp",     // non-standard variant corresponding to _setjmp
    NULL
};

