const char* wordexp_h_name = "wordexp.h";

const char* wordexp_h_globals[] = {
    // <wordexp.h> defines the structure wordexp_t and symbolic constants for word expansion,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in wordexp.h
const char* wordexp_h_types[] = {
    "wordexp_t",
    NULL
};

// Macros declared in wordexp.h
const char* wordexp_h_macros[] = {
    "WRDE_APPEND",
    "WRDE_DOOFFS",
    "WRDE_NOCMD",
    "WRDE_REUSE",
    "WRDE_SHOWERR",
    "WRDE_UNDEF",

    "WRDE_BADCHAR",
    "WRDE_BADVAL",
    "WRDE_CMDSUB",
    "WRDE_NOSPACE",
    "WRDE_NOSYS",
    "WRDE_SYNTAX",
    NULL
};

// Functions declared in wordexp.h
const char* wordexp_h_functions[] = {
    "wordexp",
    "wordfree",
    NULL
};

