const char* string_h_name = "string.h";

const char* string_h_globals[] = {
    // <string.h> does NOT define any global variables with external linkage.
    NULL
};

// Types declared in string.h
const char* string_h_types[] = {
    // None; string.h declares functions and macros but no new types
    NULL
};

// Macros declared in string.h
const char* string_h_macros[] = {
    "NULL",         // Null pointer constant (sometimes defined here)
    NULL
};

// Functions declared in string.h
const char* string_h_functions[] = {
    // Standard C functions
    "memcpy",          // void *memcpy(void *dest, const void *src, size_t n);
    "memmove",         // void *memmove(void *dest, const void *src, size_t n);
    "strcpy",          // char *strcpy(char *dest, const char *src);
    "strncpy",         // char *strncpy(char *dest, const char *src, size_t n);
    "strcat",          // char *strcat(char *dest, const char *src);
    "strncat",         // char *strncat(char *dest, const char *src, size_t n);
    "memcmp",          // int memcmp(const void *s1, const void *s2, size_t n);
    "strcmp",          // int strcmp(const char *s1, const char *s2);
    "strncmp",         // int strncmp(const char *s1, const char *s2, size_t n);
    "memchr",          // void *memchr(const void *s, int c, size_t n);
    "strchr",          // char *strchr(const char *s, int c);
    "strrchr",         // char *strrchr(const char *s, int c);
    "strspn",          // size_t strspn(const char *s, const char *accept);
    "strcspn",         // size_t strcspn(const char *s, const char *reject);
    "strpbrk",         // char *strpbrk(const char *s, const char *accept);
    "strstr",          // char *strstr(const char *haystack, const char *needle);
    "strlen",          // size_t strlen(const char *s);
    "memset",          // void *memset(void *s, int c, size_t n);
    "strerror",        // char *strerror(int errnum);
    "strtok",          // char *strtok(char *str, const char *delim);

    // POSIX and GNU extensions (may require feature test macros)
    "strxfrm",         // size_t strxfrm(char *dest, const char *src, size_t n);
    "memccpy",         // void *memccpy(void *dest, const void *src, int c, size_t n);
    "strdup",          // char *strdup(const char *s);
    "strndup",
    "memset_explicit",
    "strerror_r",      // int strerror_r(int errnum, char *buf, size_t buflen);
    "strchrnul",       // char *strchrnul(const char *s, int c);

    NULL
};

