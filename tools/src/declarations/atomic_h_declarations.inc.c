const char* atomic_h_name = "atomic.h";

const char* atomic_h_globals[] = {
    // <atomic.h> in defines macros and inline functions for atomic operations,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in atomic.h
const char* atomic_h_types[] = {
    // None explicitly declared; atomic.h provides macros for atomic operations
    NULL
};

// Macros declared in atomic.h
const char* atomic_h_macros[] = {
    // Atomic arithmetic and logic operations macros, all prefixed with "atomic_"
    "atomic_add",               // Atomic addition
    "atomic_sub",               // Atomic subtraction
    "atomic_and",               // Atomic bitwise AND
    "atomic_or",                // Atomic bitwise OR
    "atomic_xor",               // Atomic bitwise XOR
    "atomic_compare_and_exchange", // Atomic compare and exchange
    "atomic_load_acquire",      // Atomic load with acquire semantics
    "atomic_store_release",     // Atomic store with release semantics
    "atomic_thread_fence_acquire", // Memory fence acquire
    "atomic_thread_fence_release", // Memory fence release
    "atomic_thread_fence_seq_cst", // Sequential consistency fence
    // Conditionally atomic operations prefixed with "catomic_" (non-atomic if safe)
    "catomic_add",
    "catomic_sub",
    "catomic_and",
    "catomic_or",
    "catomic_xor",
    // Other support macros for barriers and low-level atomic primitives
    NULL
};

// Functions declared in atomic.h
const char* atomic_h_functions[] = {
    // None; atomic operations are provided as macros or inline functions
    NULL
};

