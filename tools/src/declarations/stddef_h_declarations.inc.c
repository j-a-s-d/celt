const char* stddef_h_name = "stddef.h";

const char* stddef_h_globals[] = {
    // stddef.h defines macros and types like size_t, ptrdiff_t, offsetof,
    // but it does NOT define any global variables.
    NULL
};

// Types declared in stddef.h
const char* stddef_h_types[] = {
    "ptrdiff_t",    // Signed integer type for pointer differences
    "size_t",       // Unsigned integer type for sizes
    "wchar_t",      // Wide character type (may be a typedef or built-in)
    "max_align_t",  // Type with the maximum alignment requirement (since C11)
    NULL
};

// Macros declared in stddef.h
const char* stddef_h_macros[] = {
    "NULL",         // Null pointer constant
    "offsetof",     // Macro to compute offset of a member within a struct
    NULL
};

// Functions declared in stddef.h
const char* stddef_h_functions[] = {
    // None; stddef.h declares types and macros but no functions
    NULL
};

