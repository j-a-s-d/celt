const char* sched_h_name = "sched.h";

const char* sched_h_globals[] = {
    // sched.h primarily defines functions and types for process scheduling,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in sched.h
const char* sched_h_types[] = {
    "struct sched_param",// scheduling parameters structure
    NULL
};

// Macros declared in sched.h
const char* sched_h_macros[] = {
    "SCHED_FIFO",        // first-in, first-out real-time scheduling policy
    "SCHED_RR",          // round-robin real-time scheduling policy
    "SCHED_SPORADIC",    // sporadic server scheduling policy (optional)
    "SCHED_OTHER",       // default (non-real-time) scheduling policy
    NULL
};

// Functions declared in sched.h
const char* sched_h_functions[] = {
    "sched_get_priority_max",   // int sched_get_priority_max(int policy);
    "sched_get_priority_min",   // int sched_get_priority_min(int policy);
    "sched_getparam",           // int sched_getparam(pid_t pid, struct sched_param *param);
    "sched_getscheduler",       // int sched_getscheduler(pid_t pid);
    "sched_rr_get_interval",    // int sched_rr_get_interval(pid_t pid, struct timespec *interval);
    "sched_setparam",           // int sched_setparam(pid_t pid, const struct sched_param *param);
    "sched_setscheduler",       // int sched_setscheduler(pid_t pid, int policy, const struct sched_param *param);
    "sched_yield",              // int sched_yield(void);
    NULL
};

