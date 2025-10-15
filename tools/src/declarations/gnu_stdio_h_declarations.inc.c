const char* gnu_stdio_h_name = "stdio.h";

const char* gnu_stdio_h_globals[] = {
    // The GNU C Library <stdio.h> declares standard I/O functions and some global variables,
    // but it generally does NOT declare or define modifiable global variables with external linkage for user programs.
    NULL
};

// Types declared in gnu/stdio.h
const char* gnu_stdio_h_types[] = {
    "struct obstack",   // Forward declaration used for obstack-related functions
    NULL
};

// Macros declared in gnu/stdio.h
const char* gnu_stdio_h_macros[] = {
    // Typically none unique to this header; standard stdio macros are in <stdio.h>
    NULL
};

// Functions declared in gnu/stdio.h
const char* gnu_stdio_h_functions[] = {
    "ctermid",           // char *ctermid(char *s); returns the name of the controlling terminal
    "cuserid",           // char *cuserid(char *s); returns the username (X/Open, deprecated)
    "obstack_printf",    // int obstack_printf(struct obstack *obstack, const char *format, ...);
    "obstack_vprintf",   // int obstack_vprintf(struct obstack *obstack, const char *format, __gnuc_va_list args);
    "flockfile",         // void flockfile(FILE *stream); lock a FILE stream for thread-safe access
    "ftrylockfile",      // int ftrylockfile(FILE *stream); try to lock a FILE stream without blocking
    "funlockfile",       // void funlockfile(FILE *stream); unlock a FILE stream
    NULL
};

