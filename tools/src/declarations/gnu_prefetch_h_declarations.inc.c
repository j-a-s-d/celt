const char* gnu_prefetch_h_name = "prefetch.h";

const char* gnu_prefetch_h_globals[] = {
    // <prefetch.h> declares prefetching functions like prefetch_range,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in gnu/prefetch.h
const char* gnu_prefetch_h_types[] = {
    // None; this header primarily defines macros and inline functions for cache prefetching
    NULL
};

// Macros declared in gnu/prefetch.h
const char* gnu_prefetch_h_macros[] = {
    "prefetch",           // Macro to prefetch a memory address for reading
    "prefetchw",          // Macro to prefetch a memory address for writing
    "spin_lock_prefetch", // Macro to prefetch a spinlock variable
    "PREFETCH_STRIDE",    // Macro defining the stride size for prefetching streamed operations
    NULL
};

// Functions declared in gnu/prefetch.h
const char* gnu_prefetch_h_functions[] = {
    "prefetch_range",     // Inline function to prefetch a range of memory addresses
    NULL
};

