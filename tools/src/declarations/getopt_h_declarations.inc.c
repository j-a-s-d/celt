const char* getopt_h_name = "getopt.h";

const char* getopt_h_globals[] = {
    "optarg",
    "optind",
    "opterr",
    "optopt",
    "optreset",  // GNU extension, not always present
    NULL
};

const char* getopt_h_types[] = {
    "struct option",
    NULL
};

const char* getopt_h_macros[] = {
    "no_argument",
    "required_argument",
    "optional_argument",
    NULL
};

const char* getopt_h_functions[] = {
    "getopt",
    "getopt_long",
    "getopt_long_only",
    NULL
};

