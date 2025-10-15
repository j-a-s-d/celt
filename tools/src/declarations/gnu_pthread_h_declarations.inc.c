const char* gnu_pthread_h_name = "pthread.h";

const char* gnu_pthread_h_globals[] = {
    // <pthread.h> declares types, constants, and functions for POSIX threads,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in gnu/pthread.h
const char* gnu_pthread_h_types[] = {
    "pthread_t",                  // Thread identifier type
    "pthread_attr_t",             // Thread attributes object
    "pthread_mutex_t",            // Mutex object
    "pthread_mutexattr_t",        // Mutex attributes object
    "pthread_cond_t",             // Condition variable object
    "pthread_condattr_t",         // Condition variable attributes object
    "pthread_key_t",              // Thread-specific data key
    "pthread_once_t",             // One-time initialization control
    "pthread_rwlock_t",           // Read-write lock object
    "pthread_rwlockattr_t",       // Read-write lock attributes object
    "pthread_barrier_t",          // Barrier synchronization object
    "pthread_barrierattr_t",      // Barrier attributes object
    NULL
};

// Macros declared in gnu/pthread.h
const char* gnu_pthread_h_macros[] = {
    "PTHREAD_CREATE_JOINABLE",    // Thread creation state: joinable
    "PTHREAD_CREATE_DETACHED",   // Thread creation state: detached
    "PTHREAD_MUTEX_INITIALIZER", // Static initializer for mutex
    "PTHREAD_COND_INITIALIZER",  // Static initializer for condition variable
    "PTHREAD_ONCE_INIT",         // Static initializer for once control
    "PTHREAD_RWLOCK_INITIALIZER",// Static initializer for read-write lock
    "PTHREAD_BARRIER_SERIAL_THREAD", // Barrier return value for serial thread
    "PTHREAD_PROCESS_PRIVATE",   // Process-shared attribute value
    "PTHREAD_PROCESS_SHARED",    // Process-shared attribute value
    NULL
};

// Functions declared in gnu/pthread.h
const char* gnu_pthread_h_functions[] = {
    "pthread_create",             // Create a new thread
    "pthread_exit",               // Terminate calling thread
    "pthread_join",               // Wait for thread termination
    "pthread_detach",             // Detach a thread
    "pthread_self",               // Get calling thread ID
    "pthread_equal",              // Compare two thread IDs
    "pthread_mutex_init",         // Initialize a mutex
    "pthread_mutex_destroy",      // Destroy a mutex
    "pthread_mutex_lock",         // Lock a mutex
    "pthread_mutex_trylock",      // Try to lock a mutex
    "pthread_mutex_unlock",       // Unlock a mutex
    "pthread_cond_init",          // Initialize a condition variable
    "pthread_cond_destroy",       // Destroy a condition variable
    "pthread_cond_wait",          // Wait on a condition variable
    "pthread_cond_timedwait",     // Timed wait on a condition variable
    "pthread_cond_signal",        // Signal a condition variable
    "pthread_cond_broadcast",     // Broadcast to all waiting threads
    "pthread_key_create",         // Create thread-specific data key
    "pthread_key_delete",         // Delete thread-specific data key
    "pthread_setspecific",        // Set thread-specific data
    "pthread_getspecific",        // Get thread-specific data
    "pthread_once",               // One-time initialization
    "pthread_rwlock_init",        // Initialize a read-write lock
    "pthread_rwlock_destroy",     // Destroy a read-write lock
    "pthread_rwlock_rdlock",      // Acquire read lock
    "pthread_rwlock_wrlock",      // Acquire write lock
    "pthread_rwlock_tryrdlock",   // Try read lock
    "pthread_rwlock_trywrlock",   // Try write lock
    "pthread_rwlock_unlock",      // Unlock read-write lock
    "pthread_barrier_init",       // Initialize a barrier
    "pthread_barrier_destroy",    // Destroy a barrier
    "pthread_barrier_wait",       // Wait at a barrier
    // GNU extensions (non-POSIX)
    "pthread_setname_np",         // Set thread name (GNU extension)
    "pthread_getname_np",         // Get thread name (GNU extension)
    "pthread_tryjoin_np",         // Non-portable try join (GNU extension)
    "pthread_timedjoin_np",       // Timed join (GNU extension)
    NULL
};

