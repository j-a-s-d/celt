const char* sys_termio_h_name = "sys/termio.h";

const char* sys_termio_h_globals[] = {
    // <sys/termio.h> defines the termio structure and related constants for terminal I/O control,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/termio.h
const char* sys_termio_h_types[] = {
    "struct termio",   // Terminal I/O structure with members:
                      // unsigned short c_iflag;   // Input modes
                      // unsigned short c_oflag;   // Output modes
                      // unsigned short c_cflag;   // Control modes
                      // unsigned short c_lflag;   // Local modes
                      // unsigned char  c_line;    // Line discipline
                      // unsigned char  c_cc[NCC]; // Control characters array
    NULL
};

// Macros declared in sys/termio.h
const char* sys_termio_h_macros[] = {
    // Input mode flags (c_iflag)
    "IGNBRK", "BRKINT", "IGNPAR", "PARMRK", "INPCK", "ISTRIP", "INLCR",
    "IGNCR", "ICRNL", "IXON", "IXOFF",

    // Output mode flags (c_oflag)
    "OPOST", "ONLCR", "OCRNL", "ONOCR", "ONLRET",

    // Control mode flags (c_cflag)
    "CSIZE", "CS5", "CS6", "CS7", "CS8", "CSTOPB", "CREAD", "PARENB", "PARODD",

    // Local mode flags (c_lflag)
    "ISIG", "ICANON", "ECHO", "ECHOE", "ECHOK", "ECHONL", "NOFLSH", "TOSTOP",

    // Special control characters indices (c_cc array)
    "VINTR", "VQUIT", "VERASE", "VKILL", "VEOF", "VEOL", "VEOL2", "VSTART",
    "VSTOP", "VSUSP", "VDSUSP", "VREPRINT", "VDISCARD", "VWERASE", "VLNEXT",

    // Number of control characters
    "NCC",

    NULL
};

// Functions declared in sys/termio.h
const char* sys_termio_h_functions[] = {
    // Typically none declared directly; terminal I/O is controlled via ioctl() with TCGETA, TCSETA, etc.
    NULL
};

