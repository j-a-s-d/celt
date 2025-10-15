const char* uchar_h_name = "uchar.h";

const char* uchar_h_globals[] = {
    // <uchar.h> defines types and declares functions for Unicode character handling,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in uchar.h
const char* uchar_h_types[] = {
    NULL
};

// Macros declared in uchar.h
const char* uchar_h_macros[] = {
    "__STD_UTF_16__",    // If defined, char16_t has UTF-16 encoding (C11, expands to 1 when defined)[2]
    "__STD_UTF_32__",    // If defined, char32_t has UTF-32 encoding (C11, expands to 1 when defined)[2]
    NULL
};

// Functions declared in uchar.h
const char* uchar_h_functions[] = {
    "mbrtoc8",      // support for char8_t type
    "c8rtomb",
    "c16rtomb",     // size_t c16rtomb(char *restrict s, char16_t c16, mbstate_t *restrict ps);[6]
    "c32rtomb",     // size_t c32rtomb(char *restrict s, char32_t c32, mbstate_t *restrict ps);[6]
    "mbrtoc16",     // size_t mbrtoc16(char16_t *restrict pc16, const char *restrict s, size_t n, mbstate_t *restrict ps);[6]
    "mbrtoc32",     // size_t mbrtoc32(char32_t *restrict pc32, const char *restrict s, size_t n, mbstate_t *restrict ps);[6]
    NULL
};

