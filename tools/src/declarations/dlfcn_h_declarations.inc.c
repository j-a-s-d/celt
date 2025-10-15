const char* dlfcn_h_name = "dlfcn.h";

const char* dlfcn_h_globals[] = {
    // <dlfcn.h> declares functions and macros for dynamic linking,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in dlfcn.h
const char* dlfcn_h_types[] = {
    // None; dlfcn.h declares functions and macros but no new types
    NULL
};

// Macros declared in dlfcn.h
const char* dlfcn_h_macros[] = {
    "RTLD_LAZY",     // Perform relocations at an implementation-dependent time (lazy)
    "RTLD_NOW",      // Perform relocations when the object is loaded (immediate)
    "RTLD_GLOBAL",   // Make symbols available for relocation of other modules
    "RTLD_LOCAL",    // Symbols are not made available for relocation of other modules
    "RTLD_DEFAULT",  // (GNU extension) Special handle for default symbol search
    "RTLD_NEXT",     // (GNU extension) Special handle to search subsequent objects
    NULL
};

// Functions declared in dlfcn.h
const char* dlfcn_h_functions[] = {
    "dlopen",    // void *dlopen(const char *filename, int flag);
    "dlsym",     // void *dlsym(void *handle, const char *symbol);
    "dlclose",   // int dlclose(void *handle);
    "dlerror",   // char *dlerror(void);
    NULL
};

