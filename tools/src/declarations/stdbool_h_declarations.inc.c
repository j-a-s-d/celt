const char* stdbool_h_name = "stdbool.h";

const char* stdbool_h_globals[] = {
    // stdbool.h defines the macros: bool, true, and false,
    // but it does NOT define any global variables.
    NULL
};

// Types declared in stdbool.h
const char* stdbool_h_types[] = {
    // stdbool.h does not declare new types, but defines bool as a macro for _Bool
    NULL
};

// Macros declared in stdbool.h
const char* stdbool_h_macros[] = {
    "bool",                         // expands to _Bool
    "true",                         // expands to integer constant 1
    "false",                        // expands to integer constant 0
    "__bool_true_false_are_defined",// expands to 1
    NULL
};

// Functions declared in stdbool.h
const char* stdbool_h_functions[] = {
    // stdbool.h declares no functions
    NULL
};

