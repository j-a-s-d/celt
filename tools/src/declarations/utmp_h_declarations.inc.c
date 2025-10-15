const char* utmp_h_name = "utmp.h";

const char* utmp_h_globals[] = {
    // <utmp.h> defines the utmp structure and related constants,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in utmp.h
const char* utmp_h_types[] = {
    "struct utmp",       // Structure describing a user accounting record
    "struct exit_status",// Embedded structure describing process exit status
    NULL
};

// Macros declared in utmp.h
const char* utmp_h_macros[] = {
    "UTMP_FILE",         // Path to utmp file (usually "/etc/utmp" or "/var/run/utmp")
    "WTMP_FILE",         // Path to wtmp file (usually "/var/adm/wtmp" or "/var/log/wtmp")
    "ILOG_FILE",         // Path to failed login file (e.g., "/etc/.ilog")

    // Values for ut_type field
    "EMPTY",             // 0: Record does not contain valid info
    "RUN_LVL",           // 1: Change in system run-level
    "BOOT_TIME",         // 2: Time of system boot
    "OLD_TIME",          // 3: Time before system clock change
    "NEW_TIME",          // 4: Time after system clock change
    "INIT_PROCESS",      // 5: Process spawned by init
    "LOGIN_PROCESS",     // 6: A "getty" process waiting for login
    "USER_PROCESS",      // 7: A user process (logged in)
    "DEAD_PROCESS",      // 8: Terminated process
    "ACCOUNTING",        // 9: Accounting record

    "UTMAXTYPE",         // Largest legal ut_type value (usually ACCOUNTING)

    // Special strings/formats for ut_line field (max 11 chars + null)
    "RUNLVL_MSG",        // "run-level %c"
    "BOOT_MSG",          // "system boot"
    "OTIME_MSG",         // "old time"
    "TIME_MSG",          // "new time"

    NULL
};

// Functions declared in utmp.h
const char* utmp_h_functions[] = {
    // Typically, no standard functions declared in <utmp.h>, but related functions exist in <utmpx.h> or libc:
    // setutent(), getutent(), getutid(), getutline(), pututline(), endutent(), utmpname()
    NULL
};

