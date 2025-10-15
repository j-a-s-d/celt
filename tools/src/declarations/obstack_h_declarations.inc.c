const char* obstack_h_name = "obstack.h";

const char* obstack_h_globals[] = {
    "obstack_exit_failure",  // int indicating exit failure status used internally by obstack functions
    "_obstack_compat",       // struct obstack* used for backward compatibility in GNU C Library
    NULL
};

// Types declared in obstack.h
const char* obstack_h_types[] = {
    "struct obstack",   // Opaque structure representing an obstack (object stack)
    NULL
};

// Macros declared in obstack.h
const char* obstack_h_macros[] = {
    "obstack_chunk_alloc",   // Macro or function to allocate memory chunks (user-defined)
    "obstack_chunk_free",    // Macro or function to free memory chunks (user-defined)
    "obstack_init",          // Initialize an obstack object
    "obstack_alloc",         // Allocate memory in an obstack
    "obstack_free",          // Free memory in an obstack
    "obstack_base",          // Get base address of current object
    "obstack_next_free",     // Get pointer to next free byte in current chunk
    "obstack_room",          // Get number of bytes left in current chunk
    "obstack_blank",         // Allocate uninitialized space in an obstack
    "obstack_grow",          // Append data to current object
    "obstack_grow0",         // Append zero-terminated data to current object
    "obstack_finish",        // Finish current object and return pointer to it
    NULL
};

// Functions declared in obstack.h
const char* obstack_h_functions[] = {
    "obstack_init",          // void obstack_init(struct obstack *obstack);
    "obstack_alloc",         // void *obstack_alloc(struct obstack *obstack, size_t size);
    "obstack_free",          // void obstack_free(struct obstack *obstack, void *ptr);
    "obstack_base",          // void *obstack_base(struct obstack *obstack);
    "obstack_next_free",     // void *obstack_next_free(struct obstack *obstack);
    "obstack_room",          // size_t obstack_room(struct obstack *obstack);
    "obstack_blank",         // void *obstack_blank(struct obstack *obstack, size_t size);
    "obstack_grow",          // void obstack_grow(struct obstack *obstack, const void *data, size_t size);
    "obstack_grow0",         // void obstack_grow0(struct obstack *obstack, const void *data, size_t size);
    "obstack_finish",        // void *obstack_finish(struct obstack *obstack);
    NULL
};

