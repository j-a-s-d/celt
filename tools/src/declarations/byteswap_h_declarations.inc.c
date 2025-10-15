const char* byteswap_h_name = "byteswap.h";

const char* byteswap_h_globals[] = {
    // <byteswap.h> defines macros and inline functions for byte order swapping,
    // such as bswap_16, bswap_32, and bswap_64,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in byteswap.h
const char* byteswap_h_types[] = {
    // None; this header defines macros and inline functions only
    NULL
};

// Macros declared in byteswap.h
const char* byteswap_h_macros[] = {
    "__bswap_constant_16",   // Macro to swap bytes in a 16-bit integer constant
    "__bswap_constant_32",   // Macro to swap bytes in a 32-bit integer constant
    "__bswap_constant_64",   // Macro to swap bytes in a 64-bit integer constant
    NULL
};

// Functions declared in byteswap.h
const char* byteswap_h_functions[] = {
    "__bswap_16",            // Inline function to swap bytes in a 16-bit integer
    "__bswap_32",            // Inline function to swap bytes in a 32-bit integer
    "__bswap_64",            // Inline function to swap bytes in a 64-bit integer
    "bswap_16",              // Function to swap bytes in a 16-bit integer (GNU extension)
    "bswap_32",              // Function to swap bytes in a 32-bit integer (GNU extension)
    "bswap_64",              // Function to swap bytes in a 64-bit integer (GNU extension)
    NULL
};

