const char* monetary_h_name = "monetary.h";

const char* monetary_h_globals[] = {
    // <monetary.h> declares types, macros, and functions related to monetary formatting,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in monetary.h
const char* monetary_h_types[] = {
    "struct lconv",
    NULL
};

// Macros declared in monetary.h
const char* monetary_h_macros[] = {
    // Typically none specific to monetary.h; macros may come from locale.h or other headers
    NULL
};

// Functions declared in monetary.h
const char* monetary_h_functions[] = {
    "localeconv",
    "strfmon",
    NULL
};

