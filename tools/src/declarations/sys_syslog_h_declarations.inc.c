const char* sys_syslog_h_name = "sys/syslog.h";

const char* sys_syslog_h_globals[] = {
    // <sys/syslog.h> (commonly included as <syslog.h>) defines constants, macros, and function prototypes
    // for system error logging via the syslog facility,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/syslog.h
const char* sys_syslog_h_types[] = {
    // Typically none; this header mainly defines macros and function prototypes
    NULL
};

// Macros declared in sys/syslog.h
const char* sys_syslog_h_macros[] = {
    // Options for openlog()
    "LOG_PID",        // Log the process ID with each message
    "LOG_CONS",       // Log to the system console if unable to send to syslog daemon
    "LOG_NDELAY",     // Open the connection immediately
    "LOG_ODELAY",     // Delay open until first syslog() call (default)
    "LOG_NOWAIT",     // Do not wait for child processes

    // Facilities for openlog()
    "LOG_KERN",       // Kernel messages
    "LOG_USER",       // User-level messages
    "LOG_MAIL",       // Mail system
    "LOG_NEWS",       // News system
    "LOG_UUCP",       // UUCP subsystem
    "LOG_DAEMON",     // System daemons
    "LOG_AUTH",       // Security/authorization messages
    "LOG_CRON",       // Cron daemon
    "LOG_LPR",        // Printer subsystem
    "LOG_LOCAL0",     // Reserved for local use
    "LOG_LOCAL1",
    "LOG_LOCAL2",
    "LOG_LOCAL3",
    "LOG_LOCAL4",
    "LOG_LOCAL5",
    "LOG_LOCAL6",
    "LOG_LOCAL7",

    // Priorities for syslog()
    "LOG_EMERG",      // System is unusable
    "LOG_ALERT",      // Action must be taken immediately
    "LOG_CRIT",       // Critical conditions
    "LOG_ERR",        // Error conditions
    "LOG_WARNING",    // Warning conditions
    "LOG_NOTICE",     // Normal but significant condition
    "LOG_INFO",       // Informational messages
    "LOG_DEBUG",      // Debug-level messages

    // Macros for masks used with setlogmask()
    "LOG_MASK",  // Create a mask for priority pri
    "LOG_UPTO",  // Create a mask for all priorities up to pri

    NULL
};

// Functions declared in sys/syslog.h
const char* sys_syslog_h_functions[] = {
    "openlog",        // void openlog(const char *ident, int option, int facility);
    "syslog",         // void syslog(int priority, const char *format, ...);
    "closelog",       // void closelog(void);
    "setlogmask",     // int setlogmask(int maskpri);
    NULL
};

