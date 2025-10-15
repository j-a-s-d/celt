const char* search_h_name = "search.h";

const char* search_h_globals[] = {
    // The <search.h> header does NOT define any global variables.
    // It defines types, enums, and declares functions for search and sorting.
    NULL
};

// Types declared in search.h
const char* search_h_types[] = {
    "ENTRY",       // Structure representing a key-value pair for search trees
    NULL
};

// Macros declared in search.h
const char* search_h_macros[] = {
    // Typically none; search.h mainly declares functions and the ENTRY type
    NULL
};

// Functions declared in search.h
const char* search_h_functions[] = {
    "tsearch",    // void *tsearch(const void *key, void **rootp, int (*compar)(const void *, const void *));
    "tfind",      // void *tfind(const void *key, void *const *rootp, int (*compar)(const void *, const void *));
    "tdelete",    // void *tdelete(const void *key, void **rootp, int (*compar)(const void *, const void *));
    "twalk",      // void twalk(const void *root, void (*action)(const void *, VISIT, int));
    "lfind",      // void *lfind(const void *key, const void *base, size_t *nmemb, size_t size, int (*compar)(const void *, const void *));
    "lsearch",    // void *lsearch(const void *key, void *base, size_t *nmemb, size_t size, int (*compar)(const void *, const void *));
    NULL
};

