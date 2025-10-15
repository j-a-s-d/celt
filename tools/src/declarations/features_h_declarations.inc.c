const char* features_h_name = "features.h";

const char* features_h_globals[] = {
    // The <features.h> header is a GNU C Library internal header used to control feature test macros
    // and configuration of available features; it does NOT declare or define any global variables.
    NULL
};

// Types declared in features.h
const char* features_h_types[] = {
    // None; <features.h> primarily defines macros controlling feature test macros and GNU extensions
    NULL
};

// Macros declared in features.h
const char* features_h_macros[] = {
    "__GLIBC__",            // Major version of the GNU C Library
    "__GLIBC_MINOR__",      // Minor version of the GNU C Library
    "__GLIBC_PREREQ", // Macro to check glibc version >= maj.min

    "__USE_POSIX",          // Internal macro indicating POSIX features enabled
    "__USE_POSIX2",         // POSIX.2 features
    "__USE_XOPEN",          // X/Open features enabled
    "__USE_XOPEN2K",        // X/Open 2000 features
    "__USE_XOPEN2K8",       // X/Open 2008 features
    "__USE_GNU",            // GNU extensions enabled
    "__USE_MISC",           // Miscellaneous BSD and SVID extensions
    "__USE_BSD",            // BSD-specific features
    "__USE_SVID",           // System V Interface Definition features
    "__USE_LARGEFILE64",    // Large file support macros

    // Feature test macros that control which features are exposed
    "_POSIX_C_SOURCE",
    "_XOPEN_SOURCE",
    "_GNU_SOURCE",
    "_DEFAULT_SOURCE",
    "_BSD_SOURCE",
    "_SVID_SOURCE",

    NULL
};

// Functions declared in features.h
const char* features_h_functions[] = {
    // None declared; this header only defines macros
    NULL
};

