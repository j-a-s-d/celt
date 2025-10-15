const char* sys_ioccom_h_name = "sys/ioccom.h";

const char* sys_ioccom_h_globals[] = {
    // <sys/ioccom.h> is a system header primarily found on BSD-derived systems,
    // defining macros used to construct ioctl command codes.
    // It does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/ioccom.h
const char* sys_ioccom_h_types[] = {
    // Typically none; this header defines macros for ioctl command encoding
    NULL
};

// Macros declared in sys/ioccom.h
const char* sys_ioccom_h_macros[] = {
    "IOCPARM_MASK",    // Mask for parameter length (usually 0x1fff)
    "IOCPARM_LEN",  // Extract parameter length from ioctl command
    "IOCBASECMD",   // Extract base command number (without parameter length)
    "IOCGROUP",     // Extract ioctl group (magic number)

    "IOCPARM_MAX",     // Maximum size of ioctl parameters (often PAGE_SIZE)

    "IOC_VOID",        // No parameters
    "IOC_OUT",         // Copy parameters out (kernel to user)
    "IOC_IN",          // Copy parameters in (user to kernel)
    "IOC_INOUT",       // Copy parameters in and out
    "IOC_DIRMASK",     // Mask for direction bits

    "_IOC",  // Compose ioctl command number with direction, group, number, and length

    "_IO",       // No parameter ioctl command
    "_IOR",   // Read ioctl command (copy out)
    "_IOW",   // Write ioctl command (copy in)
    "_IOWR",  // Read/write ioctl command (copy in and out)

    NULL
};

// Functions declared in sys/ioccom.h
const char* sys_ioccom_h_functions[] = {
    // None; this header defines only macros
    NULL
};

