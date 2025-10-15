const char* sys_eventfd_h_name = "sys/eventfd.h";

const char* sys_eventfd_h_globals[] = {
    // <sys/eventfd.h> declares the eventfd interface for event notification on Linux,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/eventfd.h
const char* sys_eventfd_h_types[] = {
    // Typically none; this header mainly declares the eventfd() function and related types
    NULL
};

// Macros declared in sys/eventfd.h
const char* sys_eventfd_h_macros[] = {
    "EFD_CLOEXEC",     // Set close-on-exec flag on the eventfd file descriptor
    "EFD_NONBLOCK",    // Set non-blocking mode on the eventfd file descriptor
    "EFD_SEMAPHORE",   // Provide semaphore-like semantics for reads
    NULL
};

// Functions declared in sys/eventfd.h
const char* sys_eventfd_h_functions[] = {
    "eventfd",         // int eventfd(unsigned int initval, int flags);
    "eventfd_read",    // int eventfd_read(int fd, uint64_t *value);
    "eventfd_write",   // int eventfd_write(int fd, uint64_t value);
    NULL
};

