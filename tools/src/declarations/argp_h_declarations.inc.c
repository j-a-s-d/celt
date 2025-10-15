const char* argp_h_name = "argp.h";

const char* argp_h_globals[] = {
    "argp_program_version",       // const char* used to provide a version string for --version option
    "argp_program_version_hook",  // function pointer for custom version printing hook
    "argp_program_bug_address",   // const char* used to provide a bug-reporting address in --help output
    NULL
};

// Types declared in argp.h
const char* argp_h_types[] = {
    "struct argp_option",   // Describes a single command-line option
    "struct argp",          // Defines an argp parser with options and parser function
    "struct argp_state",    // Represents the current state of argument parsing
    "struct argp_child",    // Represents a child parser for hierarchical parsing
    NULL
};

// Macros declared in argp.h
const char* argp_h_macros[] = {
    "ARGP_NO_ARGS",         // Flag indicating no arguments are accepted
    "ARGP_NO_HELP",         // Flag to disable automatic help option
    "ARGP_NO_EXIT",         // Flag to prevent argp from exiting on errors
    "ARGP_HELP_PRE_DOC",    // Help output flag to print pre-documentation
    "ARGP_HELP_POST_DOC",   // Help output flag to print post-documentation
    "ARGP_HELP_STD_HELP",   // Help output flag to print standard help message
    "ARGP_HELP_STD_ERR",    // Help output flag to print standard error message
    "ARGP_HELP_BUG_ADDR",   // Help output flag to print bug report address
    "ARGP_KEY_ARG",         // Special key for positional arguments
    "ARGP_KEY_END",         // Special key indicating end of options
    NULL
};

// Functions declared in argp.h
const char* argp_h_functions[] = {
    "argp_parse",           // int argp_parse(const struct argp *argp, int argc, char **argv, unsigned flags, int *arg_index, void *input);
    "argp_help",            // void argp_help(const struct argp *argp, FILE *stream, unsigned flags, char *name);
    "argp_usage",           // void argp_usage(struct argp_state *state);
    "argp_error",           // int argp_error(struct argp_state *state, const char *fmt, ...);
    NULL
};

