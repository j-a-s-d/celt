const char* limits_h_name = "limits.h";

const char* limits_h_globals[] = {
    // <limits.h> defines only macros for integral type limits,
    // it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in limits.h
const char* limits_h_types[] = {
    // limits.h does not declare types, only macros
    NULL
};

// Macros declared in limits.h
const char* limits_h_macros[] = {
    "CHAR_BIT",      // Number of bits in a char (byte)
    "SCHAR_MIN",     // Minimum value for signed char
    "SCHAR_MAX",     // Maximum value for signed char
    "UCHAR_MAX",     // Maximum value for unsigned char
    "CHAR_MIN",      // Minimum value for char (same as SCHAR_MIN or 0)
    "CHAR_MAX",      // Maximum value for char (same as SCHAR_MAX or UCHAR_MAX)
    "MB_LEN_MAX",    // Maximum number of bytes in a multibyte character
    "SHRT_MIN",      // Minimum value for short int
    "SHRT_MAX",      // Maximum value for short int
    "USHRT_MAX",     // Maximum value for unsigned short int
    "INT_MIN",       // Minimum value for int
    "INT_MAX",       // Maximum value for int
    "UINT_MAX",      // Maximum value for unsigned int
    "LONG_MIN",      // Minimum value for long int
    "LONG_MAX",      // Maximum value for long int
    "ULONG_MAX",     // Maximum value for unsigned long int
    "LLONG_MIN",     // Minimum value for long long int (C99)
    "LLONG_MAX",     // Maximum value for long long int (C99)
    "ULLONG_MAX",    // Maximum value for unsigned long long int (C99)
    NULL
};

// Functions declared in limits.h
const char* limits_h_functions[] = {
    // limits.h declares no functions
    NULL
};

