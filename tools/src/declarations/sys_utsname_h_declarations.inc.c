const char* sys_utsname_h_name = "sys/utsname.h";

const char* sys_utsname_h_globals[] = {
    // <sys/utsname.h> defines the struct utsname and declares the uname() function,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/utsname.h
const char* sys_utsname_h_types[] = {
    "struct utsname",   // structure holding system information
    NULL
};

// Macros declared in sys/utsname.h
const char* sys_utsname_h_macros[] = {
    // None mandated by POSIX in <sys/utsname.h>
    NULL
};

// Functions declared in sys/utsname.h
const char* sys_utsname_h_functions[] = {
    "uname",           // int uname(struct utsname *buf);
    NULL
};

