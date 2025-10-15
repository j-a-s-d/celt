const char* errno_h_name = "errno.h";

const char* errno_h_globals[] = {
    "errno"  // The global error number variable, typically defined as a macro expanding to a thread-local int
};

// Types declared in errno.h
const char* errno_h_types[] = {
    // errno.h does not declare new types, only the errno variable (macro)
    NULL
};

// Macros declared in errno.h
const char* errno_h_macros[] = {
    "EDOM",       // Domain error (e.g. sqrt(-1))
    "ERANGE",     // Range error (e.g. result out of range)
    "EILSEQ",     // Illegal byte sequence
    "EACCES",     // Permission denied
    "EAGAIN",     // Resource temporarily unavailable
    "EBADF",      // Bad file descriptor
    "EEXIST",     // File exists
    "EINTR",      // Interrupted function call
    "EINVAL",     // Invalid argument
    "EIO",        // I/O error
    "EISDIR",     // Is a directory
    "EMFILE",     // Too many open files
    "ENFILE",     // File table overflow
    "ENOENT",     // No such file or directory
    "ENOMEM",     // Not enough space
    "ENOSPC",     // No space left on device
    "ENOTDIR",    // Not a directory
    "EPERM",      // Operation not permitted
    "ESPIPE",     // Illegal seek
    "ETIMEDOUT",  // Connection timed out
    // ... many other platform-dependent error macros may be defined
    NULL
};

// Functions declared in errno.h
const char* errno_h_functions[] = {
    // errno.h itself declares no functions; strerror() and perror() are declared in string.h and stdio.h respectively
    NULL
};

