const char* gnu_libc_lock_h_name = "libc-lock.h";

const char* gnu_libc_lock_h_globals[] = {
    // <libc-lock.h> is an internal GNU C Library header providing lock (mutex) types,
    // macros, and inline functions for thread synchronization within glibc.
    // It does NOT declare or define any global variables with external linkage for user programs.
    NULL
};

// Types declared in libc-lock.h
const char* gnu_libc_lock_h_types[] = {
    "__libc_lock_t",             // Basic lock type, typically wrapping pthread_mutex_t or internal lock structure
    "__libc_lock_recursive_t",   // Recursive lock type allowing the same thread to lock multiple times
    NULL
};

// Macros declared in libc-lock.h
const char* gnu_libc_lock_h_macros[] = {
    "__libc_lock_define",                      // Define an uninitialized lock variable with storage class CLASS
    "__libc_lock_define_initialized",          // Define an initialized lock variable with storage class CLASS
    "__libc_lock_define_recursive",            // Define an uninitialized recursive lock variable
    "__libc_lock_define_initialized_recursive",// Define an initialized recursive lock variable
    "__libc_lock_init",                                // Initialize a lock variable
    "__libc_lock_init_recursive",                      // Initialize a recursive lock variable
    "__libc_lock_destroy",                             // Destroy a lock variable
    "__libc_lock_destroy_recursive",                   // Destroy a recursive lock variable
    "__libc_lock_lock",                                // Lock a lock variable (blocking)
    "__libc_lock_lock_recursive",                      // Lock a recursive lock variable (blocking)
    "__libc_lock_trylock",                             // Try to lock a lock variable (non-blocking)
    "__libc_lock_trylock_recursive",                   // Try to lock a recursive lock variable (non-blocking)
    "__libc_lock_unlock",                              // Unlock a lock variable
    "__libc_lock_unlock_recursive",                    // Unlock a recursive lock variable
    NULL
};

// Functions declared in libc-lock.h
const char* gnu_libc_lock_h_functions[] = {
    "__libc_lock_init",            // Initialize a lock (may be macro or function)
    "__libc_lock_init_recursive", // Initialize a recursive lock
    "__libc_lock_destroy",         // Destroy a lock
    "__libc_lock_destroy_recursive", // Destroy a recursive lock
    "__libc_lock_lock",            // Lock a lock
    "__libc_lock_lock_recursive", // Lock a recursive lock
    "__libc_lock_trylock",         // Try to lock a lock
    "__libc_lock_trylock_recursive", // Try to lock a recursive lock
    "__libc_lock_unlock",          // Unlock a lock
    "__libc_lock_unlock_recursive",// Unlock a recursive lock
    NULL
};

