const char* regex_h_name = "regex.h";

const char* regex_h_globals[] = {
    // <regex.h> declares types, macros, and functions for POSIX regular expressions,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in regex.h
const char* regex_h_types[] = {
    "regex_t",      // Compiled regular expression structure
    "regmatch_t",   // Structure for substring match offsets
    "regoff_t",     // Signed integer type for offsets
    NULL
};

// Macros declared in regex.h
const char* regex_h_macros[] = {
    // Flags for regcomp()
    "REG_EXTENDED",   // Use Extended Regular Expressions
    "REG_ICASE",      // Ignore case in matching
    "REG_NOSUB",      // Do not report substring matches
    "REG_NEWLINE",    // Change handling of newline characters

    // Flags for regexec()
    "REG_NOTBOL",     // ^ does not match start of string
    "REG_NOTEOL",     // $ does not match end of string

    // Error codes returned by regex functions
    "REG_NOMATCH",    // No match found
    "REG_BADPAT",     // Invalid pattern
    "REG_ECOLLATE",   // Invalid collating element
    "REG_ECTYPE",     // Invalid character class
    "REG_EESCAPE",    // Trailing backslash
    "REG_ESUBREG",    // Invalid backreference number
    "REG_EBRACK",     // Unmatched '['
    "REG_EPAREN",     // Unmatched '('
    "REG_EBRACE",     // Unmatched '{'
    "REG_BADBR",      // Invalid contents of '{}'
    "REG_ERANGE",     // Invalid range endpoint
    "REG_ESPACE",     // Out of memory
    "REG_BADRPT",     // Invalid repetition operator (?, *, +)
    "REG_ENOSYS",     // Function not supported
    NULL
};

// Functions declared in regex.h
const char* regex_h_functions[] = {
    "regcomp",    // Compile a regular expression
    "regexec",    // Execute a regular expression match
    "regerror",   // Convert error code to human-readable string
    "regfree",    // Free compiled regular expression
    NULL
};

