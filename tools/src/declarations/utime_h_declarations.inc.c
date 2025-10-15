const char* utime_h_name = "utime.h";

const char* utime_h_globals[] = {
    // <utime.h> declares the struct utimbuf used to specify file access and modification times,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in utime.h
const char* utime_h_types[] = {
    "struct utimbuf",   // Structure holding file access and modification times
    NULL
};

// Macros declared in utime.h
const char* utime_h_macros[] = {
    // Typically no macros mandated by POSIX in <utime.h>
    NULL
};

// Functions declared in utime.h
const char* utime_h_functions[] = {
    "utime",            // int utime(const char *pathname, const struct utimbuf *times);
    NULL
};

