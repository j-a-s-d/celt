const char* sys_ttycom_h_name = "sys/ttycom.h";

const char* sys_ttycom_h_globals[] = {
    // <sys/ttycom.h> defines ioctl request codes, constants, and structures related to terminal (tty) device control,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/ttycom.h
const char* sys_ttycom_h_types[] = {
    "struct winsize",    // Window size structure with members:
                         // unsigned short ws_row;    // rows, in characters
                         // unsigned short ws_col;    // columns, in characters
                         // unsigned short ws_xpixel; // horizontal size, pixels
                         // unsigned short ws_ypixel; // vertical size, pixels
    NULL
};

// Macros declared in sys/ttycom.h
const char* sys_ttycom_h_macros[] = {
    // ioctl commands (examples, actual list is extensive)
    "TIOCGWINSZ",       // Get window size
    "TIOCSWINSZ",       // Set window size
    "TIOCGPGRP",        // Get process group ID
    "TIOCSPGRP",        // Set process group ID
    "TIOCGETA",         // Get terminal attributes (historical, prefer termios)
    "TIOCSETA",         // Set terminal attributes (historical, prefer termios)
    "TIOCGETD",         // Get line discipline
    "TIOCSETD",         // Set line discipline
    "TIOCSBRK",         // Send break
    "TIOCCBRK",         // Clear break
    "TIOCGFLAGS",       // Get flags
    "TIOCSFLAGS",       // Set flags

    // More macros exist to control modem lines, input/output queues, etc.

    NULL
};

// Functions declared in sys/ttycom.h
const char* sys_ttycom_h_functions[] = {
    // None; tty control is done via ioctl() calls
    NULL
};

