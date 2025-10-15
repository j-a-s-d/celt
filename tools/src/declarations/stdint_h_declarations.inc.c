const char* stdint_h_name = "stdint.h";

const char* stdint_h_globals[] = {
    // stdint.h defines fixed-width integer types and macros,
    // but it does NOT define any global variables.
    NULL
};

// Types declared in stdint.h
const char* stdint_h_types[] = {
    // Exact-width integer types
    "int8_t",      // Signed 8-bit integer
    "uint8_t",     // Unsigned 8-bit integer
    "int16_t",     // Signed 16-bit integer
    "uint16_t",    // Unsigned 16-bit integer
    "int32_t",     // Signed 32-bit integer
    "uint32_t",    // Unsigned 32-bit integer
    "int64_t",     // Signed 64-bit integer
    "uint64_t",    // Unsigned 64-bit integer

    // Minimum-width integer types
    "int_least8_t",    // Signed integer type with at least 8 bits
    "uint_least8_t",   // Unsigned integer type with at least 8 bits
    "int_least16_t",
    "uint_least16_t",
    "int_least32_t",
    "uint_least32_t",
    "int_least64_t",
    "uint_least64_t",

    // Fastest minimum-width integer types
    "int_fast8_t",     // Fastest signed integer type with at least 8 bits
    "uint_fast8_t",    // Fastest unsigned integer type with at least 8 bits
    "int_fast16_t",
    "uint_fast16_t",
    "int_fast32_t",
    "uint_fast32_t",
    "int_fast64_t",
    "uint_fast64_t",

    // Greatest-width integer types
    "intmax_t",        // Greatest signed integer type
    "uintmax_t",       // Greatest unsigned integer type

    // Integer types capable of holding object pointers
    "intptr_t",        // Signed integer type capable of holding a pointer
    "uintptr_t",       // Unsigned integer type capable of holding a pointer

    NULL
};

// Macros declared in stdint.h
const char* stdint_h_macros[] = {
    "INT8_MIN",
    "INT8_MAX",
    "UINT8_MAX",
    "INT16_MIN",
    "INT16_MAX",
    "UINT16_MAX",
    "INT32_MIN",
    "INT32_MAX",
    "UINT32_MAX",
    "INT64_MIN",
    "INT64_MAX",
    "UINT64_MAX",
    "INT_LEAST8_MIN",
    "INT_LEAST8_MAX",
    "UINT_LEAST8_MAX",
    "INT_LEAST16_MIN",
    "INT_LEAST16_MAX",
    "UINT_LEAST16_MAX",
    "INT_LEAST32_MIN",
    "INT_LEAST32_MAX",
    "UINT_LEAST32_MAX",
    "INT_LEAST64_MIN",
    "INT_LEAST64_MAX",
    "UINT_LEAST64_MAX",
    "INT_FAST8_MIN",
    "INT_FAST8_MAX",
    "UINT_FAST8_MAX",
    "INT_FAST16_MIN",
    "INT_FAST16_MAX",
    "UINT_FAST16_MAX",
    "INT_FAST32_MIN",
    "INT_FAST32_MAX",
    "UINT_FAST32_MAX",
    "INT_FAST64_MIN",
    "INT_FAST64_MAX",
    "UINT_FAST64_MAX",
    "INTPTR_MIN",
    "INTPTR_MAX",
    "UINTPTR_MAX",
    "INTMAX_MIN",
    "INTMAX_MAX",
    "UINTMAX_MAX",
    "PTRDIFF_MIN",
    "PTRDIFF_MAX",
    "SIZE_MAX",
    "WCHAR_MIN",
    "WCHAR_MAX",
    "SIG_ATOMIC_MIN",
    "SIG_ATOMIC_MAX",
    "UINTPTR_MAX",
    "INT8_C",
    "UINT8_C",
    "INT16_C",
    "UINT16_C",
    "INT32_C",
    "UINT32_C",
    "INT64_C",
    "UINT64_C",
    "INTMAX_C",
    "UINTMAX_C",
    NULL
};

// Functions declared in stdint.h
const char* stdint_h_functions[] = {
    // None; stdint.h declares types and macros but no functions
    NULL
};

