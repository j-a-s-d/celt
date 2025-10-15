const char* stdarg_h_name = "stdarg.h";

const char* stdarg_h_globals[] = {
    // stdarg.h defines macros and the type va_list,
    // but it does NOT define any global variables.
    NULL
};

// Types declared in stdarg.h
const char* stdarg_h_types[] = {
    "va_list",    // Type for iterating over variable argument lists
    NULL
};

// Macros declared in stdarg.h
const char* stdarg_h_macros[] = {
    "va_start",   // Initialize a va_list to retrieve the additional arguments
    "va_arg",     // Retrieve the next argument of a specified type from the va_list
    "va_end",     // Clean up the va_list when done
    "va_copy",    // Copy one va_list to another (since C99)
    NULL
};

// Functions declared in stdarg.h
const char* stdarg_h_functions[] = {
    // None; stdarg.h provides only macros and types for variadic argument handling
    NULL
};

