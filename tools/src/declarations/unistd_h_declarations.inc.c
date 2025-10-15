const char* unistd_h_name = "unistd.h";

const char* unistd_h_globals[] = {
    // <unistd.h> declares many standard symbolic constants and functions for POSIX systems,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in unistd.h
const char* unistd_h_types[] = {
    NULL
};

// Macros declared in unistd.h
const char* unistd_h_macros[] = {
    "STDIN_FILENO",
    "STDOUT_FILENO",
    "STDERR_FILENO",

    "_PC_LINK_MAX",
    "_PC_MAX_CANON",
    "_PC_MAX_INPUT",
    "_PC_NAME_MAX",
    "_PC_PATH_MAX",
    "_PC_PIPE_BUF",
    "_PC_CHOWN_RESTRICTED",
    "_PC_NO_TRUNC",
    "_PC_VDISABLE",

    "_SC_ARG_MAX",
    "_SC_CHILD_MAX",
    "_SC_CLK_TCK",
    "_SC_NGROUPS_MAX",
    "_SC_OPEN_MAX",
    "_SC_JOB_CONTROL",
    "_SC_SAVED_IDS",
    "_SC_VERSION",
    "_SC_PAGESIZE",
    "_SC_PAGE_SIZE",
    "_SC_STREAM_MAX",
    "_SC_TZNAME_MAX",
    "_SC_MONOTONIC_CLOCK",
    NULL
};

// Functions declared in unistd.h
const char* unistd_h_functions[] = {
    // File and directory operations
    "access",
    "faccessat",
    "faccessat2",
    "chdir",
    "fchdir",
    "chown",
    "fchown",
    "lchown",
    "fchownat",
    "close",
    "dup",
    "dup2",
    "fsync",
    "fdatasync",
    "fpathconf",
    "pathconf",
    "ftruncate",
    "truncate",
    "getcwd",
    "getwd",
    "get_current_dir_name",
    "isatty",
    "link",
    "linkat",
    "lockf",
    "lseek",
    "pipe",
    "pipe2",
    "pread",
    "pwrite",
    "read",
    "readlink",
    "readlinkat",
    "rmdir",
    "symlink",
    "symlinkat",
    "sync",
    "syncfs",
    "ttyname",
    "ttyname_r",
    "unlink",
    "unlinkat",
    "write",

    // Process control
    "_exit",
    "execl",
    "execlp",
    "execle",
    "execv",
    "execvp",
    "execvpe",
    "fexecve",
    "fork",
    "getpid",
    "getppid",
    "getpgrp",
    "setpgid",
    "getpgid",
    "setsid",
    "getsid",
    "nice",
    "sleep",
    "alarm",
    "pause",
    "tcgetpgrp",
    "tcsetpgrp",

    // User and group IDs
    "getuid",
    "geteuid",
    "getgid",
    "getegid",
    "getgroups",
    "getlogin",
    "getlogin_r",
    "setuid",
    "seteuid",
    "setgid",
    "setegid",
    "setreuid",
    "setregid",

    // Other
    "crypt",
    "encrypt",
    "gethostname",
    "gethostid",
    "getopt",
    "swab",
    "sysconf",
    NULL
};

