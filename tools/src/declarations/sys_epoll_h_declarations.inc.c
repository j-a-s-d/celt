const char* sys_epoll_h_name = "sys/epoll.h";

const char* sys_epoll_h_globals[] = {
    // <sys/epoll.h> declares types, constants, and functions for the Linux epoll API,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/epoll.h
const char* sys_epoll_h_types[] = {
    "union epoll_data",    // Union holding user data associated with an event:
                          // void *ptr;
                          // int fd;
                          // uint32_t u32;
                          // uint64_t u64;
    "struct epoll_event",  // epoll event structure with members:
                          // uint32_t events;    // Epoll events mask
                          // epoll_data_t data;  // User data variable
    NULL
};

// Macros declared in sys/epoll.h
const char* sys_epoll_h_macros[] = {
    // Event types
    "EPOLLIN",             // Available for read
    "EPOLLPRI",            // Urgent data available
    "EPOLLOUT",            // Available for write
    "EPOLLRDNORM",         // Normal data available for read
    "EPOLLRDBAND",         // Priority data available for read
    "EPOLLWRNORM",         // Normal data available for write
    "EPOLLWRBAND",         // Priority data available for write
    "EPOLLMSG",            // Message available (unused)
    "EPOLLERR",            // Error condition
    "EPOLLHUP",            // Hang up
    "EPOLLRDHUP",          // Stream socket peer closed connection or shut down writing half
    "EPOLLONESHOT",        // One-shot behavior: event is disabled after being triggered
    "EPOLLET",             // Edge-triggered behavior

    // Control operations for epoll_ctl()
    "EPOLL_CTL_ADD",       // Add a file descriptor to the epoll instance
    "EPOLL_CTL_DEL",       // Remove a file descriptor from the epoll instance
    "EPOLL_CTL_MOD",       // Modify the settings associated with a file descriptor

    NULL
};

// Functions declared in sys/epoll.h
const char* sys_epoll_h_functions[] = {
    "epoll_create",        // int epoll_create(int size);
    "epoll_create1",       // int epoll_create1(int flags);
    "epoll_ctl",           // int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
    "epoll_wait",          // int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
    "epoll_pwait",         // int epoll_pwait(int epfd, struct epoll_event *events, int maxevents, int timeout, const sigset_t *sigmask);
    NULL
};

