const char* sys_sendfile_h_name = "sys/sendfile.h";

const char* sys_sendfile_h_globals[] = {
    // <sys/sendfile.h> does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/sendfile.h
const char* sys_sendfile_h_types[] = {
    // Typically none declared directly; the header declares the sendfile() function prototype
    NULL
};

// Macros declared in sys/sendfile.h
const char* sys_sendfile_h_macros[] = {
    // Typically none defined; feature test macros may affect declaration
    NULL
};

// Functions declared in sys/sendfile.h
const char* sys_sendfile_h_functions[] = {
    "sendfile",   // ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
    "sendfile64", // ssize_t sendfile64(int out_fd, int in_fd, __off64_t *offset, size_t count); (if large file support enabled)
    NULL
};

