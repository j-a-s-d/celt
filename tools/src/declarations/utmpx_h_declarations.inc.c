const char* utmpx_h_name = "utmpx.h";

const char* utmpx_h_globals[] = {
    // <utmpx.h> defines the utmpx structure and related constants,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in utmpx.h
const char* utmpx_h_types[] = {
    "struct utmpx",     // User accounting record structure with members:
                        // char ut_user[];   // User login name
                        // char ut_id[];     // Unspecified initialization process identifier
                        // char ut_line[];   // Device name (e.g., tty)
                        // pid_t ut_pid;     // Process ID
                        // short ut_type;    // Type of entry (e.g., USER_PROCESS)
                        // struct timeval ut_tv; // Time entry was made
    NULL
};

// Macros declared in utmpx.h
const char* utmpx_h_macros[] = {
    "EMPTY",            // No valid user accounting information
    "BOOT_TIME",        // Time of system boot
    "OLD_TIME",         // Time when system clock changed
    "NEW_TIME",         // Time after system clock changed
    "USER_PROCESS",     // A user process
    "INIT_PROCESS",     // Process spawned by init
    "LOGIN_PROCESS",    // Session leader of a logged-in user
    "DEAD_PROCESS",     // Session leader who has exited
    NULL
};

// Functions declared in utmpx.h
const char* utmpx_h_functions[] = {
    "endutxent",        // void endutxent(void);
    "getutxent",        // struct utmpx *getutxent(void);
    "getutxid",         // struct utmpx *getutxid(const struct utmpx *);
    "getutxline",       // struct utmpx *getutxline(const struct utmpx *);
    "pututxline",       // struct utmpx *pututxline(const struct utmpx *);
    "setutxent",        // void setutxent(void);
    NULL
};

