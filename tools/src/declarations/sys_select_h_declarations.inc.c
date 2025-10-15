const char* sys_select_h_name = "sys/select.h";

const char* sys_select_h_globals[] = {
    // <sys/select.h> does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/select.h
const char* sys_select_h_types[] = {
    "fd_set",       // file descriptor set type
    "timeval",      // struct timeval { time_t tv_sec; suseconds_t tv_usec; }
    NULL
};

// Macros declared in sys/select.h
const char* sys_select_h_macros[] = {
    "FD_SETSIZE",   // maximum number of descriptors in fd_set
    NULL
};

// Functions declared in sys/select.h
const char* sys_select_h_functions[] = {
    "FD_CLR",       // void FD_CLR(int fd, fd_set *fdset);
    "FD_ISSET",     // int FD_ISSET(int fd, fd_set *fdset);
    "FD_SET",       // void FD_SET(int fd, fd_set *fdset);
    "FD_ZERO",      // void FD_ZERO(fd_set *fdset);
    "pselect",      // int pselect(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict exceptfds, const struct timespec *restrict timeout, const sigset_t *restrict sigmask);
    "select",       // int select(int nfds, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict exceptfds, struct timeval *restrict timeout);
    NULL
};


