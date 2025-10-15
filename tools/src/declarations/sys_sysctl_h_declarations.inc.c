const char* sys_sysctl_h_name = "sys/sysctl.h";

const char* sys_sysctl_h_globals[] = {
    // <sys/sysctl.h> declares constants, structures, and the sysctl() function interface
    // for querying and setting kernel parameters via a hierarchical Management Information Base (MIB),
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/sysctl.h
const char* sys_sysctl_h_types[] = {
    "struct __sysctl_args",   // Structure used to pass arguments to the _sysctl() system call:
                              // int *name;        // Integer vector describing the variable to query or set
                              // int nlen;         // Length of the name vector
                              // void *oldval;     // Buffer to store old value (or NULL)
                              // size_t *oldlenp;  // Pointer to size of oldval buffer, updated with actual size
                              // void *newval;     // Buffer containing new value (or NULL)
                              // size_t newlen;    // Size of newval buffer
    NULL
};

// Macros declared in sys/sysctl.h
const char* sys_sysctl_h_macros[] = {
    // Typically none; header mainly declares the _sysctl() function and related constants
    NULL
};

// Functions declared in sys/sysctl.h
const char* sys_sysctl_h_functions[] = {
    "_sysctl",    // int _sysctl(struct __sysctl_args *args);
    NULL
};

