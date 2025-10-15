const char* sys_resource_h_name = "sys/resource.h";

const char* sys_resource_h_globals[] = {
    // <sys/resource.h> declares types, constants, and functions for resource usage and limits,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/resource.h
const char* sys_resource_h_types[] = {
    "rlim_t",           // unsigned integral type for resource limits
    "struct rlimit",    // structure describing resource limits
    "struct rusage",    // structure describing resource usage
    NULL
};

// Macros declared in sys/resource.h
const char* sys_resource_h_macros[] = {
    // Values for 'which' argument of getpriority() and setpriority()
    "PRIO_PROCESS",     // who is a process ID
    "PRIO_PGRP",        // who is a process group ID
    "PRIO_USER",        // who is a user ID

    // Resource limit constants for getrlimit() and setrlimit()
    "RLIMIT_CORE",      // limit on core file size
    "RLIMIT_CPU",       // limit on CPU time per process
    "RLIMIT_DATA",      // limit on data segment size
    "RLIMIT_FSIZE",     // limit on file size
    "RLIMIT_NOFILE",    // limit on number of open files
    "RLIMIT_STACK",     // limit on stack size
    "RLIMIT_AS",        // limit on address space size

    // Special limit values
    "RLIM_INFINITY",    // no limit
    "RLIM_SAVED_MAX",   // unrepresentable saved hard limit
    "RLIM_SAVED_CUR",   // unrepresentable saved soft limit

    // Values for 'who' argument of getrusage()
    "RUSAGE_SELF",      // current process
    "RUSAGE_CHILDREN",  // children of current process

    NULL
};

// Functions declared in sys/resource.h
const char* sys_resource_h_functions[] = {
    "getpriority",      // int getpriority(int which, id_t who);
    "setpriority",      // int setpriority(int which, id_t who, int prio);
    "getrlimit",        // int getrlimit(int resource, struct rlimit *rlim);
    "setrlimit",        // int setrlimit(int resource, const struct rlimit *rlim);
    "getrusage",        // int getrusage(int who, struct rusage *usage);
    NULL
};

