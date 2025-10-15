const char* stdalign_h_name = "stdalign.h";

const char* stdalign_h_globals[] = {
    // stdalign.h defines the alignas and alignof macros,
    // but does NOT define any global variables.
    NULL
};

// Types declared in stdalign.h
const char* stdalign_h_types[] = {
    // stdalign.h does not declare any types
    NULL
};

// Macros declared in stdalign.h
const char* stdalign_h_macros[] = {
    "alignas",             // expands to _Alignas, specifies alignment of variables or types
    "alignof",             // expands to _Alignof, queries alignment requirement of a type
    "__alignas_is_defined",// expands to integer constant 1, indicates alignas is defined
    "__alignof_is_defined",// expands to integer constant 1, indicates alignof is defined
    NULL
};

// Functions declared in stdalign.h
const char* stdalign_h_functions[] = {
    // stdalign.h declares no functions
    NULL
};

