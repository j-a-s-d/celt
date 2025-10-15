const char* sys_ioctl_h_name = "sys/ioctl.h";

const char* sys_ioctl_h_globals[] = {
    // <sys/ioctl.h> declares the ioctl() system call function prototype,
    // and defines numerous macros, constants, and types used to construct ioctl request codes.
    // It does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/ioctl.h
const char* sys_ioctl_h_types[] = {
    // sys/ioctl.h typically does not declare new types; types used come from other headers like <sys/types.h>
    NULL
};

// Macros declared in sys/ioctl.h
const char* sys_ioctl_h_macros[] = {
    "FIONBIO",     // Set/clear non-blocking I/O
    "FIONREAD",    // Get number of bytes available to read
    // Various ioctl command macros are defined, often device or driver specific,
    // and macros to construct ioctl request codes like _IO, _IOR, _IOW, _IOWR are usually defined in <asm/ioctl.h> or included indirectly
    NULL
};

// Functions declared in sys/ioctl.h
const char* sys_ioctl_h_functions[] = {
    "ioctl",       // int ioctl(int fd, unsigned long request, ...);
    NULL
};

