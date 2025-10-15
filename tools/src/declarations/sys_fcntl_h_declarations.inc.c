const char* sys_fcntl_h_name = "sys/fcntl.h";

const char* sys_fcntl_h_globals[] = {
    // <sys/fcntl.h> is a system header related to file control operations,
    // but it generally does NOT declare or define global variables with external linkage.
    NULL
};

// Types declared in sys/fcntl.h
const char* sys_fcntl_h_types[] = {
    "struct flock", // Structure describing a file lock with members:
                    // short l_type;    // Type of lock: F_RDLCK, F_WRLCK, F_UNLCK
                    // short l_whence;  // How to interpret l_start: SEEK_SET, SEEK_CUR, SEEK_END
                    // off_t l_start;   // Starting offset for lock
                    // off_t l_len;     // Number of bytes to lock (0 means until EOF)
                    // pid_t l_pid;     // PID of process holding lock (returned by F_GETLK)
    NULL
};

// Macros declared in sys/fcntl.h
const char* sys_fcntl_h_macros[] = {
    // Commands for fcntl()
    "F_DUPFD",       // Duplicate file descriptor
    "F_DUPFD_CLOEXEC", // Duplicate fd with FD_CLOEXEC flag set
    "F_GETFD",       // Get file descriptor flags
    "F_SETFD",       // Set file descriptor flags
    "F_GETFL",       // Get file status flags and access modes
    "F_SETFL",       // Set file status flags
    "F_GETLK",       // Get record locking information
    "F_SETLK",       // Set record locking information (non-blocking)
    "F_SETLKW",      // Set record locking information (blocking)
    "F_GETOWN",      // Get process or process group ID receiving SIGURG signals
    "F_SETOWN",      // Set process or process group ID receiving SIGURG signals

    // File descriptor flags
    "FD_CLOEXEC",    // Close file descriptor on exec()

    // Lock types for struct flock.l_type
    "F_RDLCK",       // Shared (read) lock
    "F_WRLCK",       // Exclusive (write) lock
    "F_UNLCK",       // Unlock

    // Flags for open() and fcntl()
    "O_RDONLY",      // Open for reading only
    "O_WRONLY",      // Open for writing only
    "O_RDWR",        // Open for reading and writing
    "O_CREAT",       // Create file if it does not exist
    "O_EXCL",        // Ensure exclusive creation
    "O_NOCTTY",      // Do not assign controlling terminal
    "O_TRUNC",       // Truncate file to zero length
    "O_APPEND",      // Append on each write
    "O_NONBLOCK",    // Non-blocking mode
    "O_DSYNC",       // Synchronized I/O data integrity completion
    "O_SYNC",        // Synchronized I/O file integrity completion
    "O_RSYNC",       // Synchronized read I/O operations
    "O_CLOEXEC",     // Set close-on-exec flag atomically on open

    "O_ACCMODE",     // Mask for file access modes

    NULL
};

// Functions declared in sys/fcntl.h
const char* sys_fcntl_h_functions[] = {
    "creat",         // int creat(const char *pathname, mode_t mode);
    "fcntl",         // int fcntl(int fd, int cmd, ...);
    "open",          // int open(const char *pathname, int flags, ...);
    "openat",        // int openat(int dirfd, const char *pathname, int flags, ...);
    NULL
};

