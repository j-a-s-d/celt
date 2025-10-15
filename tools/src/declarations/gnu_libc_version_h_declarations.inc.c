const char* gnu_libc_version_h_name = "gnu/libc-version.h";

const char* gnu_libc_version_h_globals[] = {
    // <gnu/libc-version.h> declares the following functions to get glibc version info,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in gnu/libc-version.h
const char* gnu_libc_version_h_types[] = {
    // None; this header only declares functions
    NULL
};

// Macros declared in gnu/libc-version.h
const char* gnu_libc_version_h_macros[] = {
    // None; no macros defined in this header
    NULL
};

// Functions declared in gnu/libc-version.h
const char* gnu_libc_version_h_functions[] = {
    "gnu_get_libc_version",   // const char *gnu_get_libc_version(void);
    "gnu_get_libc_release",   // const char *gnu_get_libc_release(void);
    NULL
};

