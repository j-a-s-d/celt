const char* sys_conf_h_name = "sys/conf.h";

const char* sys_conf_h_globals[] = {
    // <sys/conf.h> is a system header used primarily in kernel and driver development,
    // defining device-related macros, constants, and function prototypes.
    // It does NOT declare or define any global variables with external linkage for user programs.
    NULL
};

// Types declared in sys/conf.h
const char* sys_conf_h_types[] = {
    // None; this header primarily defines macros/constants
    NULL
};

// Macros declared in sys/conf.h
const char* sys_conf_h_macros[] = {
    "_SC_ARG_MAX",           // Maximum length of arguments to exec functions
    "_SC_CHILD_MAX",         // Maximum number of simultaneous processes per user ID
    "_SC_CLK_TCK",           // Number of clock ticks per second
    "_SC_NGROUPS_MAX",       // Maximum number of supplementary group IDs
    "_SC_OPEN_MAX",          // Maximum number of open files per process
    "_SC_JOB_CONTROL",       // Whether job control is supported
    "_SC_SAVED_IDS",         // Whether saved set-user-ID and set-group-ID are supported
    "_SC_VERSION",           // POSIX version number
    "_SC_STREAM_MAX",        // Maximum number of streams that a process can have open
    "_SC_TZNAME_MAX",        // Maximum length of a timezone name
    "_SC_PAGESIZE",          // Size of a page in bytes
    "_SC_PAGE_SIZE",         // Alias for _SC_PAGESIZE
    "_SC_THREAD_THREADS_MAX",// Maximum number of threads per process
    "_SC_THREAD_STACK_MIN",  // Minimum stack size for threads
    "_SC_THREAD_KEYS_MAX",   // Maximum number of thread-specific data keys
    "_SC_THREAD_PRIORITY_SCHEDULING", // Whether thread priority scheduling is supported
    "_SC_THREAD_PRIO_INHERIT",         // Whether priority inheritance is supported
    "_SC_THREAD_PRIO_PROTECT",         // Whether priority protection is supported
    "_SC_THREAD_PROCESS_SHARED",       // Whether process-shared synchronization is supported
    NULL
};

// Functions declared in sys/conf.h
const char* sys_conf_h_functions[] = {
    // None declared here; sysconf() is declared in <unistd.h>
    NULL
};

