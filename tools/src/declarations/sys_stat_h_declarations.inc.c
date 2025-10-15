const char* sys_stat_h_name = "sys/stat.h";

const char* sys_stat_h_globals[] = {
    // <sys/stat.h> declares structures, constants, and function prototypes related to file status,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/stat.h
const char* sys_stat_h_types[] = {
    "struct stat",
    NULL
};

// Macros declared in sys/stat.h
const char* sys_stat_h_macros[] = {
    // File type macros (test st_mode)
    "S_IFMT",     // bit mask for the file type bit fields
    "S_IFDIR",    // directory
    "S_IFCHR",    // character device
    "S_IFBLK",    // block device
    "S_IFREG",    // regular file
    "S_IFIFO",    // FIFO (named pipe)
    "S_IFLNK",    // symbolic link
    "S_IFSOCK",   // socket

    // File mode bits
    "S_ISUID",    // set-user-ID bit
    "S_ISGID",    // set-group-ID bit
    "S_ISVTX",    // sticky bit

    // Macros to test file type from mode_t value
    "S_ISREG",
    "S_ISDIR",
    "S_ISCHR",
    "S_ISBLK",
    "S_ISFIFO",
    "S_ISLNK",
    "S_ISSOCK",

    // Additional macros for utimensat() and futimens()
    "UTIME_NOW",
    "UTIME_OMIT",

    NULL
};

// Functions declared in sys/stat.h
const char* sys_stat_h_functions[] = {
    "chmod",       // change file mode
    "fchmod",      // change mode of open file descriptor
    "fchmodat",    // change mode relative to directory fd
    "fstat",       // get file status from fd
    "fstatat",     // get file status relative to directory fd
    "lstat",       // get status of a symbolic link
    "mkdir",       // create directory
    "mkdirat",     // create directory relative to fd
    "mkfifo",      // create FIFO special file
    "mkfifoat",    // create FIFO relative to fd
    "mknod",       // create special or ordinary file
    "mknodat",     // create special or ordinary file relative to fd
    "stat",        // get file status
    "umask",       // set file mode creation mask
    "utimensat",   // change file timestamps with nanosecond precision
    "futimens",    // change timestamps of open file descriptor
    NULL
};

