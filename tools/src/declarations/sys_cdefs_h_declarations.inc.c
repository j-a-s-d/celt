const char* sys_cdefs_h_name = "cdefs.h";

const char* sys_cdefs_h_globals[] = {
    // <cdefs.h> is a system/internal header used to define compiler and platform-specific macros,
    // such as attribute macros, calling conventions, and visibility controls.
    // It does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/cdefs.h
const char* sys_cdefs_h_types[] = {
    // None; this header mainly defines macros for compiler and language features
    NULL
};

// Macros declared in sys/cdefs.h
const char* sys_cdefs_h_macros[] = {
    "__P",          // Macro for function prototypes, supports old-style K&R and ANSI C
    "__BEGIN_DECLS",        // Begin extern "C" block for C++ compatibility
    "__END_DECLS",          // End extern "C" block
    "__CONCAT",        // Concatenate two tokens (x ## y)
    "__STRING",          // Convert token x to string literal
    "__const",              // Define 'const' keyword for compatibility
    "__volatile",           // Define 'volatile' keyword for compatibility
    "__inline",             // Define 'inline' keyword for compatibility
    "__attribute__",     // Compiler-specific attribute support (GCC style)
    "__THROW",              // Function attribute indicating no exceptions thrown
    "__noreturn",           // Function attribute indicating function does not return
    "__dead",               // Synonym for __noreturn
    "__printflike", // Attribute to enable printf format string checking
    "__scanflike",  // Attribute to enable scanf format string checking
    "__GNUC_PREREQ__",             // Macro to check GCC version >= ma.mi
    "__DEPRECATED",          // Attribute to mark deprecated functions
    "__UNUSED",              // Attribute to mark unused variables or functions
    "__packed",              // Attribute to pack structure members
    "__aligned",          // Attribute to specify alignment
    "__section",       // Attribute to place object in specific section
    "__weak",                // Attribute to declare weak symbols
    "__nonnull",     // Attribute to specify non-null parameters
    "__unreachable_ok_push", // Compiler pragma to suppress unreachable code warnings
    "__unreachable_ok_pop",  // Compiler pragma to restore warnings
    "__COPYRIGHT",        // Macro to embed copyright string
    "__RCSID",            // Macro to embed RCS version string
    "__SCCSID",           // Macro to embed SCCS version string
    "__IDSTRING", // Define static const string with name and content
    NULL
};

// Functions declared in sys/cdefs.h
const char* sys_cdefs_h_functions[] = {
    // None; this header only defines macros
    NULL
};

