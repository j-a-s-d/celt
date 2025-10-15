const char* pthread_np_h_name = "pthread_np.h";

const char* pthread_np_h_globals[] = {
    // <pthread_np.h> provides non-portable (non-POSIX) pthread extensions,
    // such as pthread_setname_np() and pthread_getname_np() for setting/getting thread names.
    // It does NOT define any global variables with external linkage.
    NULL
};

// Types declared in pthread_np.h
const char* pthread_np_h_types[] = {
    // Typically none; pthread_np.h mainly declares nonstandard pthread functions
    NULL
};

// Macros declared in pthread_np.h
const char* pthread_np_h_macros[] = {
    // Usually none; extensions are provided as functions
    NULL
};

// Functions declared in pthread_np.h
const char* pthread_np_h_functions[] = {
    "pthread_setname_np",   // int pthread_setname_np(pthread_t thread, const char *name);
    "pthread_getname_np",   // int pthread_getname_np(pthread_t thread, char *name, size_t len);
    // Other nonportable pthread extensions may be declared here depending on the system
    NULL
};

