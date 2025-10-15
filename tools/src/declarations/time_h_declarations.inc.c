const char* time_h_name = "time.h";

const char* time_h_globals[] = {
    // <time.h> defines types, macros, and declares functions for time manipulation,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in time.h
const char* time_h_types[] = {
    "clock_t",
    "time_t",
    "struct tm",
    "clockid_t",      // POSIX
    "timer_t",        // POSIX
    NULL
};

// Macros declared in time.h
const char* time_h_macros[] = {
    "CLOCKS_PER_SEC",
    "TIME_UTC",       // C11
    NULL
};

// Functions declared in time.h
const char* time_h_functions[] = {
    "clock",
    "difftime",
    "mktime",
    "time",
    "asctime",
    "ctime",
    "gmtime",
    "localtime",
    "strftime",
    // POSIX extensions
    "nanosleep",
    "clock_getres",
    "clock_gettime",
    "clock_settime",
    "timer_create",
    "timer_delete",
    "timer_getoverrun",
    "timer_gettime",
    "timer_settime",
    // c23
    "gmtime_r",
    "localtime_r",
    "timegm",
    "timespec_getres",
    NULL
};

