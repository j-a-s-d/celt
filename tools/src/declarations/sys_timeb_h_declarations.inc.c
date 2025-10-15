const char* sys_timeb_h_name = "sys/timeb.h";

const char* sys_timeb_h_globals[] = {
    // <sys/timeb.h> defines the struct timeb and declares the legacy function ftime(),
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/timeb.h
const char* sys_timeb_h_types[] = {
    "struct timeb",    // Structure representing time with members:
                       // time_t time;          // Seconds since the epoch
                       // unsigned short millitm; // Milliseconds past the second
                       // short timezone;      // Minutes west of Greenwich
                       // short dstflag;       // Nonzero if daylight savings time is in effect
    NULL
};

// Macros declared in sys/timeb.h
const char* sys_timeb_h_macros[] = {
    // None standardized; typically no macros defined
    NULL
};

// Functions declared in sys/timeb.h
const char* sys_timeb_h_functions[] = {
    "ftime",          // int ftime(struct timeb *tp);
    NULL
};

