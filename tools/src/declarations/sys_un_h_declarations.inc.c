const char* sys_un_h_name = "sys/un.h";

const char* sys_un_h_globals[] = {
    // <sys/un.h> defines the sockaddr_un structure used for UNIX domain sockets,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/un.h
const char* sys_un_h_types[] = {
    "struct sockaddr_un",  // UNIX domain socket address structure with members:
                          // sa_family_t sun_family;  // Address family (AF_UNIX)
                          // char sun_path[];         // Socket pathname (size varies by implementation)
    NULL
};

// Macros declared in sys/un.h
const char* sys_un_h_macros[] = {
    // Typically none defined specifically in <sys/un.h>; constants like AF_UNIX are defined in <sys/socket.h>
    NULL
};

// Functions declared in sys/un.h
const char* sys_un_h_functions[] = {
    // None declared in this header; socket functions are declared in <sys/socket.h>
    NULL
};

