const char* sys_timerfd_h_name = "sys/timerfd.h";

const char* sys_timerfd_h_globals[] = {
    // <sys/timerfd.h> declares constants, types, and function prototypes related to Linux timerfd API,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/timerfd.h
const char* sys_timerfd_h_types[] = {
    "struct itimerspec",   // Structure specifying timer intervals and expiration times:
                           // struct timespec it_interval;  // Timer interval for periodic timers
                           // struct timespec it_value;     // Initial expiration
    NULL
};

// Macros declared in sys/timerfd.h
const char* sys_timerfd_h_macros[] = {
    "TFD_NONBLOCK",           // Set O_NONBLOCK flag on the timer file descriptor
    "TFD_CLOEXEC",            // Set close-on-exec flag on the timer file descriptor
    "TFD_TIMER_ABSTIME",      // Interpret timer expiration time as absolute (CLOCK_REALTIME)
    "TFD_TIMER_CANCEL_ON_SET",// Cancel timer if system clock changes discontinuously (since Linux 4.10)
    NULL
};

// Functions declared in sys/timerfd.h
const char* sys_timerfd_h_functions[] = {
    "timerfd_create",         // int timerfd_create(int clockid, int flags);
    "timerfd_settime",        // int timerfd_settime(int fd, int flags, const struct itimerspec *new_value, struct itimerspec *old_value);
    "timerfd_gettime",        // int timerfd_gettime(int fd, struct itimerspec *curr_value);
    NULL
};

