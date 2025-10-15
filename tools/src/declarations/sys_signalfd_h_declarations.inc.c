const char* sys_signalfd_h_name = "sys/signalfd.h";

const char* sys_signalfd_h_globals[] = {
    // <sys/signalfd.h> does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/signalfd.h
const char* sys_signalfd_h_types[] = {
    "struct signalfd_siginfo",  // Structure describing signal information read from signalfd:
                                // uint32_t ssi_signo;   // Signal number
                                // int32_t  ssi_errno;   // Error number
                                // int32_t  ssi_code;    // Signal code
                                // uint32_t ssi_pid;     // PID of sender
                                // uint32_t ssi_uid;     // Real UID of sender
                                // int32_t  ssi_fd;      // File descriptor (SIGIO)
                                // uint32_t ssi_tid;     // Timer ID (POSIX timers)
                                // uint32_t ssi_band;    // Band event (SIGPOLL)
                                // uint32_t ssi_overrun; // Timer overrun count
                                // uint32_t ssi_trapno;  // Trap number that caused signal
                                // int32_t  ssi_status;  // Exit status or signal (SIGCHLD)
                                // int32_t  ssi_int;     // Integer sent by sigqueue(3)
                                // uint64_t ssi_ptr;     // Pointer sent by sigqueue(3)
                                // uint64_t ssi_utime;   // User CPU time consumed (SIGCHLD)
                                // uint64_t ssi_stime;   // System CPU time consumed (SIGCHLD)
                                // uint64_t ssi_addr;    // Address that generated signal (for hardware-generated signals)
    NULL
};

// Macros declared in sys/signalfd.h
const char* sys_signalfd_h_macros[] = {
    "SFD_NONBLOCK",    // Set O_NONBLOCK flag on the signalfd file descriptor
    "SFD_CLOEXEC",     // Set close-on-exec (FD_CLOEXEC) flag on the signalfd file descriptor
    NULL
};

// Functions declared in sys/signalfd.h
const char* sys_signalfd_h_functions[] = {
    "signalfd",        // int signalfd(int fd, const sigset_t *mask, int flags);
    NULL
};

