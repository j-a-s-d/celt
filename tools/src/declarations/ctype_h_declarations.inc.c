const char* ctype_h_name = "ctype.h";

const char* ctype_h_globals[] = {
    // <ctype.h> declares functions and macros for character classification and conversion,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in ctype.h
const char* ctype_h_types[] = {
    "locale_t",  // defined in <locale.h>, used in *_l functions
    NULL
};

// Macros declared in ctype.h
const char* ctype_h_macros[] = {
    "_toupper",
    "_tolower",
    "NULL",
    NULL
};

// Functions declared in ctype.h
const char* ctype_h_functions[] = {
    "isalnum",
    "isalnum_l",
    "isalpha",
    "isalpha_l",
    "isascii",
    "isblank",
    "isblank_l",
    "iscntrl",
    "iscntrl_l",
    "isdigit",
    "isdigit_l",
    "isgraph",
    "isgraph_l",
    "islower",
    "islower_l",
    "isprint",
    "isprint_l",
    "ispunct",
    "ispunct_l",
    "isspace",
    "isspace_l",
    "isupper",
    "isupper_l",
    "isxdigit",
    "isxdigit_l",
    "toascii",
    "tolower",
    "tolower_l",
    "toupper",
    "toupper_l",
    NULL
};

