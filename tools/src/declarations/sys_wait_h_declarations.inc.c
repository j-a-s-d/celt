const char* sys_wait_h_name = "sys/wait.h";

const char* sys_wait_h_globals[] = {
    // <sys/wait.h> declares macros, constants, types, and function prototypes
    // related to process waiting and status retrieval,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/wait.h
const char* sys_wait_h_types[] = {
    "idtype_t",      // enumeration type for waitid() specifying type of ID (e.g., P_ALL, P_PID, P_PGID)
    NULL
};

// Macros declared in sys/wait.h
const char* sys_wait_h_macros[] = {
    // Options for waitpid()
    "WNOHANG",       // return immediately if no child has exited
    "WUNTRACED",     // report status of stopped child processes
    "WCONTINUED",    // report status of continued child processes (XSI extension)

    // Macros to analyze process status returned by wait functions
    "WEXITSTATUS",  // extract exit status of child
    "WIFEXITED",    // child exited normally
    "WIFSIGNALED",  // child terminated by signal
    "WIFSTOPPED",   // child currently stopped
    "WSTOPSIG",     // signal number that caused child to stop
    "WTERMSIG",     // signal number that caused child termination
    "WIFCONTINUED", // child was resumed by delivery of SIGCONT (XSI extension)

    // Options for waitid()
    "WEXITED",       // wait for processes that have exited
    "WSTOPPED",      // report status for stopped children
    "WCONTINUED",    // report status for continued children
    "WNOWAIT",       // keep process in waitable state after returning status

    // idtype_t enumeration values (at least)
    "P_ALL",         // wait for any child
    "P_PID",         // wait for specific process ID
    "P_PGID",        // wait for process group ID

    NULL
};

// Functions declared in sys/wait.h
const char* sys_wait_h_functions[] = {
    "wait",          // pid_t wait(int *status);
    "waitpid",       // pid_t waitpid(pid_t pid, int *status, int options);
    "waitid",        // int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);
    NULL
};

