const char* sys_time_h_name = "sys/time.h";

const char* sys_time_h_globals[] = {
    // <sys/time.h> declares types, macros, and functions for manipulating time values,
    // including timeval structures, timers, and interval timers,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/time.h
const char* sys_time_h_types[] = {
    "timeval",       // struct timeval { time_t tv_sec; suseconds_t tv_usec; }
    "itimerval",     // struct itimerval { struct timeval it_interval; struct timeval it_value; }
    NULL
};

// Macros declared in sys/time.h
const char* sys_time_h_macros[] = {
    "ITIMER_REAL",     // decrements in real time
    "ITIMER_VIRTUAL",  // decrements in process virtual time
    "ITIMER_PROF",     // decrements in process virtual time and when system is running on behalf of process
    NULL
};

// Functions declared in sys/time.h
const char* sys_time_h_functions[] = {
    "getitimer",       // int getitimer(int which, struct itimerval *curr_value);
    "setitimer",       // int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
    "gettimeofday",    // int gettimeofday(struct timeval *restrict tp, void *restrict tzp);
    "select",          // int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict exceptfds, struct timeval *restrict timeout);
    "utimes",          // int utimes(const char *filename, const struct timeval times[2]); (LEGACY)
    NULL
};

