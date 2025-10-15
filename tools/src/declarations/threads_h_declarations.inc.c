const char* threads_h_name = "threads.h";

const char* threads_h_globals[] = {
    // <threads.h> (C11) defines types, macros, and functions for threading support,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in threads.h
const char* threads_h_types[] = {
    "thrd_t",        // thread identifier type
    "mtx_t",         // mutex type
    "cnd_t",         // condition variable type
    "tss_t",         // thread-specific storage key type
    "once_flag",     // flag for one-time initialization
    "thrd_start_t",  // function pointer type for thread start routines
    "tss_dtor_t",    // destructor function type for thread-specific storage
    NULL
};

// Macros declared in threads.h
const char* threads_h_macros[] = {
    "thread_local",  // expands to _Thread_local for thread-local storage
    "thrd_success",  // success return code
    "thrd_busy",     // thread busy return code
    "thrd_error",    // error return code
    "thrd_nomem",    // out of memory return code
    "mtx_plain",     // mutex type: plain (non-recursive, non-timed)
    "mtx_timed",     // mutex type: supports timed lock
    "mtx_recursive", // mutex type: recursive
    NULL
};

// Functions declared in threads.h
const char* threads_h_functions[] = {
    "thrd_create",       // create a new thread
    "thrd_current",      // get current thread id
    "thrd_equal",        // compare two thread ids
    "thrd_detach",       // detach a thread
    "thrd_join",         // wait for a thread to finish
    "thrd_sleep",        // sleep for a specified time
    "thrd_yield",        // yield execution to another thread
    "thrd_exit",         // terminate current thread
    "mtx_init",          // initialize a mutex
    "mtx_lock",          // lock a mutex
    "mtx_timedlock",     // lock a mutex with timeout
    "mtx_trylock",       // try to lock a mutex without blocking
    "mtx_unlock",        // unlock a mutex
    "mtx_destroy",       // destroy a mutex
    "cnd_init",          // initialize a condition variable
    "cnd_destroy",       // destroy a condition variable
    "cnd_signal",        // unblock one thread waiting on condition variable
    "cnd_broadcast",     // unblock all threads waiting on condition variable
    "cnd_wait",          // wait on condition variable
    "cnd_timedwait",     // wait on condition variable with timeout
    "call_once",         // call a function once, thread-safe
    "tss_create",        // create thread-specific storage key
    "tss_delete",        // delete thread-specific storage key
    "tss_set",           // set value for thread-specific storage key
    "tss_get",           // get value for thread-specific storage key
    NULL
};

