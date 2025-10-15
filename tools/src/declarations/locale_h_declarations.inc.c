const char* locale_h_name = "locale.h";

const char* locale_h_globals[] = {
    // <locale.h> declares the global variable 'localeconv' function,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in locale.h
const char* locale_h_types[] = {
    "lconv",
    "locale_t",
    NULL
};

// Macros declared in locale.h
const char* locale_h_macros[] = {
    "LC_ALL",
    "LC_COLLATE",
    "LC_CTYPE",
    "LC_MONETARY",
    "LC_NUMERIC",
    "LC_TIME",
    "LC_MESSAGES",
    "LC_ALL_MASK",
    "LC_COLLATE_MASK",
    "LC_CTYPE_MASK",
    "LC_MONETARY_MASK",
    "LC_NUMERIC_MASK",
    "LC_TIME_MASK",
    "LC_MESSAGES_MASK",
    "LC_GLOBAL_LOCALE",
    "NULL",
    NULL
};

// Functions declared in locale.h
const char* locale_h_functions[] = {
    "setlocale",
    "localeconv",
    "newlocale",
    "duplocale",
    "freelocale",
    "uselocale",
    NULL
};

