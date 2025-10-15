const char* sys_uio_h_name = "sys/uio.h";

const char* sys_uio_h_globals[] = {
    // <sys/uio.h> defines the iovec structure and declares functions for scatter/gather I/O,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/uio.h
const char* sys_uio_h_types[] = {
    "struct iovec",    // Structure for scatter/gather I/O with members:
                       // void *iov_base;   // Base address of a memory region for input or output
                       // size_t iov_len;   // Length of the memory region
    NULL
};

// Macros declared in sys/uio.h
const char* sys_uio_h_macros[] = {
    "IOV_MAX",        // Maximum number of iovec structures that can be used in a single readv/writev call (defined in <limits.h>)
    NULL
};

// Functions declared in sys/uio.h
const char* sys_uio_h_functions[] = {
    "readv",          // ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
    "writev",         // ssize_t writev(int fd, const struct iovec *iov, int iovcnt);
    NULL
};

