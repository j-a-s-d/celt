const char* glob_h_name = "glob.h";

const char* glob_h_globals[] = {
    // The POSIX <glob.h> header declares the glob_t structure and functions for pathname pattern matching,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in glob.h
const char* glob_h_types[] = {
    "glob_t",
    NULL
};

// Macros declared in glob.h
const char* glob_h_macros[] = {
    "GLOB_APPEND",
    "GLOB_DOOFFS",
    "GLOB_ERR",
    "GLOB_MARK",
    "GLOB_NOCHECK",
    "GLOB_NOESCAPE",
    "GLOB_NOSORT",
    "GLOB_ABORTED",
    "GLOB_NOMATCH",
    "GLOB_NOSPACE",
    NULL
};

// Functions declared in glob.h
const char* glob_h_functions[] = {
    "glob",
    "globfree",
    NULL
};

