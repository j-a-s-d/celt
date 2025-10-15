const char* poll_h_name = "poll.h";

const char* poll_h_globals[] = {
    // <poll.h> declares the pollfd structure and the poll() function,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in poll.h
const char* poll_h_types[] = {
    "struct pollfd",  // structure describing a file descriptor to poll
    "nfds_t",         // unsigned integer type for number of file descriptors
    NULL
};

// Macros declared in poll.h
const char* poll_h_macros[] = {
    "POLLIN",      // Data other than high-priority data may be read without blocking
    "POLLRDNORM",  // Normal data may be read without blocking
    "POLLRDBAND",  // Priority data may be read without blocking
    "POLLPRI",     // High priority data may be read without blocking
    "POLLOUT",     // Normal data may be written without blocking (equivalent to POLLWRNORM)
    "POLLWRNORM",  // Normal data may be written without blocking
    "POLLWRBAND",  // Priority data may be written without blocking
    "POLLERR",     // Error condition (only in revents)
    "POLLHUP",     // Hang up (only in revents)
    "POLLNVAL",    // Invalid fd (only in revents)
    NULL
};

// Functions declared in poll.h
const char* poll_h_functions[] = {
    "poll",        // int poll(struct pollfd fds[], nfds_t nfds, int timeout);
    NULL
};

