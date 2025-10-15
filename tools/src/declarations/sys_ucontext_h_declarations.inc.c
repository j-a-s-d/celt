const char* sys_ucontext_h_name = "sys/ucontext.h";

const char* sys_ucontext_h_globals[] = {
    // <sys/ucontext.h> defines the machine-specific context type mcontext_t and related structures,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/ucontext.h
const char* sys_ucontext_h_types[] = {
    "mcontext_t",       // Machine-specific saved context type (opaque or struct)
    "ucontext_t",       // User context structure with members:
                        // ucontext_t *uc_link;       // pointer to next context to resume
                        // sigset_t uc_sigmask;       // signals blocked in this context
                        // stack_t uc_stack;          // stack used by this context
                        // mcontext_t uc_mcontext;    // machine-specific saved context
    NULL
};

// Macros declared in sys/ucontext.h
const char* sys_ucontext_h_macros[] = {
    // Typically none standardized; some platforms may define internal macros
    NULL
};

// Functions declared in sys/ucontext.h
const char* sys_ucontext_h_functions[] = {
    "getcontext",       // int getcontext(ucontext_t *ucp);
    "setcontext",       // int setcontext(const ucontext_t *ucp);
    "makecontext",      // void makecontext(ucontext_t *ucp, void (*func)(), int argc, ...);
    "swapcontext",      // int swapcontext(ucontext_t *oucp, const ucontext_t *ucp);
    NULL
};

