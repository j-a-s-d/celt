const char* syslog_h_name = "syslog.h";

const char* syslog_h_globals[] = {
    // <syslog.h> defines macros and declares functions for system logging,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in syslog.h
const char* syslog_h_types[] = {
    // syslog.h does not declare new types
    NULL
};

// Macros declared in syslog.h
const char* syslog_h_macros[] = {
    // Options for openlog()
    "LOG_PID",       // Log the process ID with each message
    "LOG_CONS",      // Log to system console on error
    "LOG_NDELAY",    // Connect to syslog daemon immediately
    "LOG_ODELAY",    // Delay open until syslog() is called
    "LOG_NOWAIT",    // Do not wait for child processes

    // Facilities for openlog()
    "LOG_KERN",      // Kernel messages
    "LOG_USER",      // User-level messages
    "LOG_MAIL",      // Mail system
    "LOG_NEWS",      // News system
    "LOG_UUCP",      // UUCP system
    "LOG_DAEMON",    // System daemons
    "LOG_AUTH",      // Security/authorization messages
    "LOG_CRON",      // Clock daemon
    "LOG_LPR",       // Printer subsystem
    "LOG_LOCAL0",    // Reserved for local use
    "LOG_LOCAL1",
    "LOG_LOCAL2",
    "LOG_LOCAL3",
    "LOG_LOCAL4",
    "LOG_LOCAL5",
    "LOG_LOCAL6",
    "LOG_LOCAL7",

    // Priority masks for setlogmask()
    "LOG_MASK", // Mask for priority pri

    // Priorities for syslog()
    "LOG_EMERG",     // System is unusable
    "LOG_ALERT",     // Action must be taken immediately
    "LOG_CRIT",      // Critical conditions
    "LOG_ERR",       // Error conditions
    "LOG_WARNING",   // Warning conditions
    "LOG_NOTICE",    // Normal but significant condition
    "LOG_INFO",      // Informational
    "LOG_DEBUG",     // Debug-level messages

    NULL
};

// Functions declared in syslog.h
const char* syslog_h_functions[] = {
    "openlog",     // void openlog(const char *ident, int option, int facility);
    "syslog",      // void syslog(int priority, const char *format, ...);
    "setlogmask",  // int setlogmask(int maskpri);
    "closelog",    // void closelog(void);
    NULL
};

