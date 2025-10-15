const char* stdbit_h_name = "stdbit.h";

const char* stdbit_h_globals[] = {
    // stdbit.h (introduced in C23) provides bit manipulation functions as macros or inline functions,
    // but it does NOT define any global variables.
    NULL
};

// Types declared in stdbit.h
const char* stdbit_h_types[] = {
    // No new types are declared in <stdbit.h>
    NULL
};

// Macros declared in stdbit.h
const char* stdbit_h_macros[] = {
    // No macros are defined in <stdbit.h>
    NULL
};

// Functions declared in stdbit.h
const char* stdbit_h_functions[] = {
    // Bit manipulation functions introduced in C23

    "bit_ceil",       // Returns the smallest power of two greater than or equal to the argument
    "bit_floor",      // Returns the largest power of two less than or equal to the argument
    "bit_width",      // Returns the number of bits needed to represent the argument
    "countl_zero",    // Counts the number of leading zero bits
    "countl_one",     // Counts the number of leading one bits
    "countr_zero",    // Counts the number of trailing zero bits
    "countr_one",     // Counts the number of trailing one bits
    "popcount",       // Counts the number of set bits (population count)

    NULL
};

