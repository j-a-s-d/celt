const char* pthread_h_name = "pthread.h";

const char* pthread_h_globals[] = {
    // <pthread.h> itself does not define global variables.
    NULL
};

// Types declared in pthread.h
const char* pthread_h_types[] = {
    "pthread_t",             // thread identifier type
    "pthread_attr_t",        // thread attributes object
    "pthread_mutex_t",       // mutex type
    "pthread_mutexattr_t",   // mutex attributes object
    "pthread_cond_t",        // condition variable type
    "pthread_condattr_t",    // condition variable attributes object
    "pthread_rwlock_t",      // read-write lock type
    "pthread_rwlockattr_t",  // read-write lock attributes object
    "pthread_spinlock_t",    // spinlock type
    "pthread_barrier_t",     // barrier type
    "pthread_barrierattr_t", // barrier attributes object
    "pthread_key_t",         // thread-specific data key type
    "pthread_once_t",        // one-time initialization control type
    NULL
};

// Macros declared in pthread.h
const char* pthread_h_macros[] = {
    // Thread creation and cancellation
    "PTHREAD_CREATE_JOINABLE",
    "PTHREAD_CREATE_DETACHED",

    // Thread cancellation states and types
    "PTHREAD_CANCEL_ENABLE",
    "PTHREAD_CANCEL_DISABLE",
    "PTHREAD_CANCEL_DEFERRED",
    "PTHREAD_CANCEL_ASYNCHRONOUS",
    "PTHREAD_CANCELED",

    // Mutex types
    "PTHREAD_MUTEX_NORMAL",
    "PTHREAD_MUTEX_ERRORCHECK",
    "PTHREAD_MUTEX_RECURSIVE",
    "PTHREAD_MUTEX_DEFAULT",
    "PTHREAD_MUTEX_STALLED",
    "PTHREAD_MUTEX_ROBUST",

    // Condition variable initializers
    "PTHREAD_COND_INITIALIZER",

    // Mutex initializer
    "PTHREAD_MUTEX_INITIALIZER",

    // Read-write lock initializer
    "PTHREAD_RWLOCK_INITIALIZER",

    // One-time initialization macro
    "PTHREAD_ONCE_INIT",

    // Barrier initializers
    "PTHREAD_BARRIER_SERIAL_THREAD",

    // Scheduling policies and priorities
    "PTHREAD_EXPLICIT_SCHED",
    "PTHREAD_INHERIT_SCHED",
    "PTHREAD_PRIO_NONE",
    "PTHREAD_PRIO_INHERIT",
    "PTHREAD_PRIO_PROTECT",

    // Process sharing
    "PTHREAD_PROCESS_PRIVATE",
    "PTHREAD_PROCESS_SHARED",

    // Thread scope
    "PTHREAD_SCOPE_SYSTEM",
    "PTHREAD_SCOPE_PROCESS",

    NULL
};

// Functions declared in pthread.h
const char* pthread_h_functions[] = {
    // Thread management
    "pthread_create",
    "pthread_exit",
    "pthread_join",
    "pthread_detach",
    "pthread_self",
    "pthread_equal",
    "pthread_yield",          // or pthread_yield_np on some systems
    "pthread_once",

    // Thread cancellation
    "pthread_cancel",
    "pthread_testcancel",
    "pthread_setcancelstate",
    "pthread_setcanceltype",

    // Thread-specific data
    "pthread_key_create",
    "pthread_key_delete",
    "pthread_getspecific",
    "pthread_setspecific",

    // Mutex functions
    "pthread_mutex_init",
    "pthread_mutex_destroy",
    "pthread_mutex_lock",
    "pthread_mutex_trylock",
    "pthread_mutex_timedlock",
    "pthread_mutex_unlock",
    "pthread_mutex_consistent",
    "pthread_mutexattr_init",
    "pthread_mutexattr_destroy",
    "pthread_mutexattr_getpshared",
    "pthread_mutexattr_setpshared",
    "pthread_mutexattr_gettype",
    "pthread_mutexattr_settype",
    "pthread_mutexattr_getrobust",
    "pthread_mutexattr_setrobust",

    // Condition variables
    "pthread_cond_init",
    "pthread_cond_destroy",
    "pthread_cond_wait",
    "pthread_cond_timedwait",
    "pthread_cond_signal",
    "pthread_cond_broadcast",
    "pthread_condattr_init",
    "pthread_condattr_destroy",
    "pthread_condattr_getpshared",
    "pthread_condattr_setpshared",
    "pthread_condattr_getclock",
    "pthread_condattr_setclock",

    // Read-write locks
    "pthread_rwlock_init",
    "pthread_rwlock_destroy",
    "pthread_rwlock_rdlock",
    "pthread_rwlock_tryrdlock",
    "pthread_rwlock_timedrdlock",
    "pthread_rwlock_wrlock",
    "pthread_rwlock_trywrlock",
    "pthread_rwlock_timedwrlock",
    "pthread_rwlock_unlock",
    "pthread_rwlockattr_init",
    "pthread_rwlockattr_destroy",
    "pthread_rwlockattr_getpshared",
    "pthread_rwlockattr_setpshared",

    // Spinlocks
    "pthread_spin_init",
    "pthread_spin_destroy",
    "pthread_spin_lock",
    "pthread_spin_trylock",
    "pthread_spin_unlock",

    // Barriers
    "pthread_barrier_init",
    "pthread_barrier_destroy",
    "pthread_barrier_wait",
    "pthread_barrierattr_init",
    "pthread_barrierattr_destroy",
    "pthread_barrierattr_getpshared",
    "pthread_barrierattr_setpshared",

    // Scheduling
    "pthread_getschedparam",
    "pthread_setschedparam",
    "pthread_getconcurrency",
    "pthread_setconcurrency",

    // CPU affinity (non-portable, POSIX extensions)
    "pthread_getcpuclockid",

    NULL
};

