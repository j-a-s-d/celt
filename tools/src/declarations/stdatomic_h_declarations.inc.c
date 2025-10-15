const char* stdatomic_h_name = "stdatomic.h";

const char* stdatomic_h_globals[] = {
    // stdatomic.h defines atomic types and operations as macros and typedefs,
    // but it does NOT define any global variables.
    NULL
};

// Types declared in stdatomic.h
const char* stdatomic_h_types[] = {
    "atomic_flag",          // structure type for atomic flag (test-and-set)
    "atomic_bool",          // _Atomic _Bool
    "atomic_char",          // _Atomic char
    "atomic_schar",         // _Atomic signed char
    "atomic_uchar",         // _Atomic unsigned char
    "atomic_short",         // _Atomic short
    "atomic_ushort",        // _Atomic unsigned short
    "atomic_int",           // _Atomic int
    "atomic_uint",          // _Atomic unsigned int
    "atomic_long",          // _Atomic long
    "atomic_ulong",         // _Atomic unsigned long
    "atomic_llong",         // _Atomic long long
    "atomic_ullong",        // _Atomic unsigned long long
    "atomic_intptr_t",      // _Atomic intptr_t
    "atomic_uintptr_t",     // _Atomic uintptr_t
    "atomic_size_t",        // _Atomic size_t
    "atomic_ptrdiff_t",     // _Atomic ptrdiff_t
    "atomic_intmax_t",      // _Atomic intmax_t
    "atomic_uintmax_t",     // _Atomic uintmax_t
    "memory_order",         // enum for memory ordering
    NULL
};

// Macros declared in stdatomic.h
const char* stdatomic_h_macros[] = {
    "ATOMIC_FLAG_INIT",         // initializer for atomic_flag (clear state)
    "ATOMIC_VAR_INIT",   // initializer for atomic variables (deprecated)
    "ATOMIC_BOOL_LOCK_FREE",    // lock-free property macros (0,1,2)
    "ATOMIC_CHAR_LOCK_FREE",
    "ATOMIC_CHAR16_T_LOCK_FREE",
    "ATOMIC_CHAR32_T_LOCK_FREE",
    "ATOMIC_WCHAR_T_LOCK_FREE",
    "ATOMIC_SHORT_LOCK_FREE",
    "ATOMIC_INT_LOCK_FREE",
    "ATOMIC_LONG_LOCK_FREE",
    "ATOMIC_LLONG_LOCK_FREE",
    "ATOMIC_POINTER_LOCK_FREE",
    NULL
};

// Functions declared in stdatomic.h
const char* stdatomic_h_functions[] = {
    "atomic_init",                      // initialize atomic object
    "atomic_is_lock_free",              // test if atomic object is lock-free
    "atomic_store",                     // store value into atomic object
    "atomic_store_explicit",            // store with memory order
    "atomic_load",                      // load value from atomic object
    "atomic_load_explicit",             // load with memory order
    "atomic_exchange",                  // atomic exchange
    "atomic_exchange_explicit",         // exchange with memory order
    "atomic_compare_exchange_strong",  // compare and swap (strong)
    "atomic_compare_exchange_weak",    // compare and swap (weak)
    "atomic_compare_exchange_strong_explicit",
    "atomic_compare_exchange_weak_explicit",
    "atomic_fetch_add",                 // atomic fetch and add
    "atomic_fetch_add_explicit",
    "atomic_fetch_sub",                 // atomic fetch and subtract
    "atomic_fetch_sub_explicit",
    "atomic_fetch_or",                  // atomic fetch and OR
    "atomic_fetch_or_explicit",
    "atomic_fetch_xor",                 // atomic fetch and XOR
    "atomic_fetch_xor_explicit",
    "atomic_fetch_and",                 // atomic fetch and AND
    "atomic_fetch_and_explicit",
    "atomic_flag_test_and_set",         // test and set atomic_flag
    "atomic_flag_test_and_set_explicit",
    "atomic_flag_clear",                // clear atomic_flag
    "atomic_flag_clear_explicit",
    "atomic_thread_fence",              // thread fence
    "atomic_signal_fence",              // signal fence
    "kill_dependency",                  // terminates dependency chain
    NULL
};

