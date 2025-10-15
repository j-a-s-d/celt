const char* strings_h_name = "strings.h";

const char* strings_h_globals[] = {
    // <strings.h> typically provides additional non-standard string functions,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in strings.h
const char* strings_h_types[] = {
    NULL
};

// Macros declared in strings.h
const char* strings_h_macros[] = {
    NULL  // strings.h typically does not define macros
};

// Functions declared in strings.h
const char* strings_h_functions[] = {
    "bcmp",           // int bcmp(const void *s1, const void *s2, size_t n);
    "bcopy",          // void bcopy(const void *src, void *dest, size_t n);
    "bzero",          // void bzero(void *s, size_t n);
    "index",          // char *index(const char *s, int c); (same as strchr)
    "rindex",         // char *rindex(const char *s, int c); (same as strrchr)
    "ffs",            // int ffs(int i); find first bit set (1-based)
    "strcasecmp",     // int strcasecmp(const char *s1, const char *s2);
    "strncasecmp",    // int strncasecmp(const char *s1, const char *s2, size_t n);
    "strcasecmp_l",   // int strcasecmp_l(const char *s1, const char *s2, locale_t locale);
    "strncasecmp_l",  // int strncasecmp_l(const char *s1, const char *s2, size_t n, locale_t locale);
    NULL
};

