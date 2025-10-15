const char* stdlib_h_name = "stdlib.h";

const char* stdlib_h_globals[] = {
    // The C standard library's stdlib.h does not publish any global variables
    // with external linkage (not macros). Most entities are functions or macros.
    NULL
};

// Types declared in stdlib.h
const char* stdlib_h_types[] = {
    "div_t",
    "ldiv_t",
    "wchar_t",
    NULL
};

// Macros declared in stdlib.h
const char* stdlib_h_macros[] = {
    "EXIT_FAILURE",
    "EXIT_SUCCESS",
    "NULL",
    "RAND_MAX",
    "MB_CUR_MAX",
    "WNOHANG",
    "WUNTRACED",
    "WEXITSTATUS",
    "WIFEXITED",
    "WIFSIGNALED",
    "WIFSTOPPED",
    "WSTOPSIG",
    "WTERMSIG",
    NULL
};

// Functions declared in stdlib.h
const char* stdlib_h_functions[] = {
    "a64l",
    "abort",
    "abs",
    "atexit",
    "atof",
    "atoi",
    "atol",
    "bsearch",
    "calloc",
    "div",
    "drand48",
    "ecvt",
    "erand48",
    "exit",
    "fcvt",
    "free",
    "gcvt",
    "getenv",
    "getsubopt",
    "grantpt",
    "initstate",
    "jrand48",
    "l64a",
    "labs",
    "lcong48",
    "ldiv",
    "lrand48",
    "malloc",
    "mblen",
    "mbstowcs",
    "mbtowc",
    "mktemp",
    "mkstemp",
    "mrand48",
    "nrand48",
    "ptsname",
    "putenv",
    "qsort",
    "rand",
    "rand_r",
    "realloc",
    "realpath",
    "seed48",
    "setkey",
    "setstate",
    "srand",
    "srand48",
    "srandom",
    "strtod",
    "strtol",
    "strtoul",
    "system",
    "ttyslot",
    "unlockpt",
    "valloc",
    "wcstombs",
    "wctomb",
    // c23 string conversions from floats
    "strfromd",
    "strfromf",
    "strfroml",
    // c23 memory deallocation with size info
    "free_sized",
    "free_aligned_sized",
    // c23 query memory alignment
    "memalignment",
    NULL
};

