const char* sys_filio_h_name = "sys/filio.h";

const char* sys_filio_h_globals[] = {
    // <sys/filio.h> is a system header that defines ioctl command constants
    // related to file I/O operations, particularly for socket and terminal control.
    // It does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/filio.h
const char* sys_filio_h_types[] = {
    // Typically none; this header mainly defines ioctl-related macros
    NULL
};

// Macros declared in sys/filio.h
const char* sys_filio_h_macros[] = {
    "FIOCLEX",      // Set close-on-exec flag on a file descriptor
    "FIONCLEX",     // Clear close-on-exec flag on a file descriptor
    "FIONREAD",     // Get number of bytes available to read
    "FIONBIO",      // Enable/disable non-blocking I/O
    "FIOASYNC",     // Enable/disable asynchronous I/O
    "FIOSETOWN",    // Set owner (for SIGIO signals)
    "FIOGETOWN",    // Get owner (for SIGIO signals)
    NULL
};

// Functions declared in sys/filio.h
const char* sys_filio_h_functions[] = {
    // None; this header does not declare functions
    NULL
};

