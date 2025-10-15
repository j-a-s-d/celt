const char* alloca_h_name = "alloca.h";

const char* alloca_h_globals[] = {
    // <alloca.h> declares the alloca() function for stack allocation,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in alloca.h
const char* alloca_h_types[] = {
    // None; alloca.h only declares the alloca function (usually as a macro)
    NULL
};

// Macros declared in alloca.h
const char* alloca_h_macros[] = {
    "alloca",    // Typically defined as a macro wrapping __builtin_alloca or compiler intrinsic
    NULL
};

// Functions declared in alloca.h
const char* alloca_h_functions[] = {
    "alloca",    // void *alloca(size_t size); allocates memory on the stack frame of the caller
    NULL
};

