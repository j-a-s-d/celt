const char* signal_h_name = "signal.h";

const char* signal_h_globals[] = {
    // <signal.h> does NOT define any global variables with external linkage.
    NULL
};

// Types declared in signal.h
const char* signal_h_types[] = {
    "sig_atomic_t",   // integer type accessed atomically in signal handlers
    "siginfo_t",      // structure with detailed signal information (POSIX)
    "sigset_t",       // signal set type (POSIX)
    "sigevent",       // structure for asynchronous notification (POSIX)
    "stack_t",        // structure for alternate signal stack (POSIX)
    NULL
};

// Macros declared in signal.h
const char* signal_h_macros[] = {
    // Signal handling macros
    "SIG_DFL",        // default signal handling
    "SIG_IGN",        // ignore signal
    "SIG_ERR",        // error return from signal()

    // Signals defined by ISO C and POSIX (examples)
    "SIGABRT",        // abnormal termination
    "SIGFPE",         // floating-point exception
    "SIGILL",         // illegal instruction
    "SIGINT",         // interrupt (e.g., Ctrl-C)
    "SIGSEGV",        // invalid memory reference
    "SIGTERM",        // termination request
    "SIGKILL",        // kill signal (cannot be caught or ignored)
    "SIGSTOP",        // stop process (cannot be caught or ignored)

    // Real-time signals (POSIX)
    "SIGRTMIN",
    "SIGRTMAX",

    // Signal set manipulation macros (POSIX)
    "SIG_BLOCK",
    "SIG_UNBLOCK",
    "SIG_SETMASK",

    // Signal action flags (POSIX)
    "SA_NOCLDSTOP",
    "SA_ONSTACK",
    "SA_RESETHAND",
    "SA_RESTART",
    "SA_SIGINFO",
    "SA_NOCLDWAIT",

    NULL
};

// Functions declared in signal.h
const char* signal_h_functions[] = {
    "signal",         // set a signal handler
    "raise",          // send a signal to the current process
    "kill",           // send a signal to a process (POSIX)
    "sigaction",      // examine and change signal action (POSIX)
    "sigaddset",      // add signal to signal set (POSIX)
    "sigdelset",      // remove signal from signal set (POSIX)
    "sigemptyset",    // initialize signal set to empty (POSIX)
    "sigfillset",     // initialize signal set to full (POSIX)
    "sigismember",    // test for membership in signal set (POSIX)
    "sigprocmask",    // examine or change blocked signals (POSIX)
    "sigsuspend",     // wait for a signal (POSIX)
    "sigpending",     // examine pending signals (POSIX)
    "sigwait",        // wait synchronously for a signal (POSIX)
    "sigwaitinfo",    // wait for signal and get info (POSIX)
    "sigtimedwait",   // wait for signal with timeout (POSIX)
    "psignal",        // print signal description (POSIX)
    "pthread_sigmask",// change signal mask in threads (POSIX)
    NULL
};

