const char* ucontext_h_name = "ucontext.h";

const char* ucontext_h_globals[] = {
    NULL
};

const char* ucontext_h_types[] = {
    "ucontext_t",     // User context structure
    "mcontext_t",     // Machine-specific CPU context
    "sigset_t",     // Signal set (from <signal.h>)
    "stack_t",     // Stack information (from <signal.h>)
    NULL
};

const char* ucontext_h_macros[] = {
    NULL
};

const char* ucontext_h_functions[] = {
    "getcontext",     // Save current context
    "setcontext",     // Restore saved context
    "makecontext",     // Modify context to execute a function
    "swapcontext",     // Save current and switch to another context
    NULL
};

