const char* gnu_mcount_h_name = "gnu-mcount.h";

const char* gnu_mcount_h_globals[] = {
    // The header "gnu-mcount.h" is an internal GNU C Library header related to profiling support,
    // typically used to implement function call counting (mcount) for profiling tools.
    // It does NOT declare or define any global variables with external linkage intended for user programs.
    NULL
};

// Types declared in gnu/gnu-mcount.h
const char* gnu_mcount_h_types[] = {
    // None; this header primarily defines macros and function declarations related to profiling
    NULL
};

// Macros declared in gnu/gnu-mcount.h
const char* gnu_mcount_h_macros[] = {
    "__mcount",          // Macro or function used internally for profiling hooks
    NULL
};

// Functions declared in gnu/gnu-mcount.h
const char* gnu_mcount_h_functions[] = {
    "__mcount",          // Low-level profiling function called on function entry (used by -pg)
    NULL
};

