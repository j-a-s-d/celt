const char* malloc_h_name = "malloc.h";

const char* malloc_h_globals[] = {
    "mem_malloc_start",  // Start address of the memory area managed by malloc
    "mem_malloc_end",    // End address of the memory area managed by malloc
    "mem_malloc_brk",    // Current break (end of allocated space) in the malloc area
    NULL
};

// Types declared in malloc.h
const char* malloc_h_types[] = {
    // None; malloc.h primarily declares functions and hook variables
    NULL
};

// Macros declared in malloc.h
const char* malloc_h_macros[] = {
    "_MALLOC_H",           // Include guard macro
    "__malloc_ptr_t",      // Defined as void *, used internally
    "__malloc_size_t",     // Defined as size_t
    "__malloc_ptrdiff_t",  // Defined as ptrdiff_t

    // mallopt options (may appear in some malloc.h)
    "M_TRIM_THRESHOLD",
    "M_TOP_PAD",
    "M_MMAP_THRESHOLD",
    "M_MMAP_MAX",
    "M_CHECK_ACTION",

    NULL
};

// Functions declared in malloc.h
const char* malloc_h_functions[] = {
    "malloc",                      // void *malloc(size_t size);
    "calloc",                      // void *calloc(size_t nmemb, size_t size);
    "realloc",                     // void *realloc(void *ptr, size_t size);
    "malloc_stats",                // void malloc_stats(void);
    "malloc_get_state",            // void *malloc_get_state(void);
    "malloc_set_state",            // int malloc_set_state(void *ptr);
    "malloc_trim",                 // int malloc_trim(size_t pad);
    "malloc_usable_size",          // size_t malloc_usable_size(void *ptr);

    // Hook variables (function pointers for debugging/customizing malloc)
    "__malloc_initialize_hook",   // void (*__malloc_initialize_hook)(void);
    "__free_hook",                 // void (*__free_hook)(void *ptr, const void *);
    "__malloc_hook",               // void *(*__malloc_hook)(size_t size, const void *);
    "__realloc_hook",              // void *(*__realloc_hook)(void *ptr, size_t size, const void *);
    "__memalign_hook",             // void *(*__memalign_hook)(size_t alignment, size_t size, const void *);
    "__after_morecore_hook",       // void (*__after_morecore_hook)(void);

    NULL
};

