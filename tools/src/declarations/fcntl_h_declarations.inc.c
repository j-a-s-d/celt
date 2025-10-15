const char* fcntl_h_name = "fcntl.h";

const char* fcntl_h_globals[] = {
    // The <fcntl.h> header defines constants, structures, and declares functions for file control,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in fcntl.h
const char* fcntl_h_types[] = {
    NULL
};

// Macros declared in fcntl.h
const char* fcntl_h_macros[] = {
    // File access modes (for open, openat, fcntl)
    "O_RDONLY",
    "O_WRONLY",
    "O_RDWR",

    // File creation flags
    "O_CREAT",
    "O_EXCL",
    "O_NOCTTY",
    "O_TRUNC",
    "O_APPEND",
    "O_NONBLOCK",
    "O_DSYNC",
    "O_SYNC",
    "O_RSYNC",

    // Additional flags (may vary by system)
    "O_CLOEXEC",
    "O_DIRECTORY",
    "O_NOFOLLOW",
    "O_TMPFILE",

    // fcntl commands
    "F_DUPFD",
    "F_GETFD",
    "F_SETFD",
    "F_GETFL",
    "F_SETFL",
    "F_GETLK",
    "F_SETLK",
    "F_SETLKW",

    // File lock types
    "F_RDLCK",
    "F_WRLCK",
    "F_UNLCK",

    // Advice flags for posix_fadvise()
    "POSIX_FADV_NORMAL",
    "POSIX_FADV_RANDOM",
    "POSIX_FADV_SEQUENTIAL",
    "POSIX_FADV_WILLNEED",
    "POSIX_FADV_DONTNEED",
    "POSIX_FADV_NOREUSE",

    // Flags for *at() functions
    "AT_FDCWD",             // special value for current working directory
    "AT_EACCESS",           // use effective IDs for access checks
    "AT_SYMLINK_NOFOLLOW",  // do not follow symbolic links
    "AT_SYMLINK_FOLLOW",    // follow symbolic links
    "AT_REMOVEDIR",         // remove directory instead of file

    NULL
};

// Functions declared in fcntl.h
const char* fcntl_h_functions[] = {
    "creat",           // int creat(const char *path, mode_t mode);
    "fcntl",           // int fcntl(int fd, int cmd, ...);
    "open",            // int open(const char *pathname, int flags, ...);
    "openat",          // int openat(int dirfd, const char *pathname, int flags, ...);
    "posix_fadvise",   // int posix_fadvise(int fd, off_t offset, off_t len, int advice);
    "posix_fallocate", // int posix_fallocate(int fd, off_t offset, off_t len);

    NULL
};

