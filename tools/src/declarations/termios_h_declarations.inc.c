const char* termios_h_name = "termios.h";

const char* termios_h_globals[] = {
    // <termios.h> defines types, macros, and functions for terminal I/O control,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in termios.h
const char* termios_h_types[] = {
    "struct termios",   // structure describing terminal I/O settings
    "tcflag_t",         // unsigned integer type for terminal flags
    "cc_t",             // type for control characters
    "speed_t",          // type for terminal baud rates
    NULL
};

// Macros declared in termios.h
const char* termios_h_macros[] = {
    // Actions for tcsetattr()
    "TCSANOW",      // change attributes immediately
    "TCSADRAIN",    // change after output has drained
    "TCSAFLUSH",    // change after output drained and flush input

    // Flush queue selectors for tcflush()
    "TCIFLUSH",     // flush pending input
    "TCOFLUSH",     // flush untransmitted output
    "TCIOFLUSH",    // flush both input and output

    // Flow control actions for tcflow()
    "TCIOFF",       // transmit STOP character, suspend input
    "TCION",        // transmit START character, restart input
    "TCOOFF",       // suspend output
    "TCOON",        // restart output

    // c_lflag flags (local modes)
    "ECHO",         // enable echo
    "ECHOE",        // echo erase character as backspace
    "ECHOK",        // echo KILL character
    "ECHONL",       // echo newline
    "ICANON",       // canonical input (line buffering)
    "IEXTEN",       // enable implementation-defined input processing
    "ISIG",         // enable signals (INTR, QUIT, SUSP)
    "NOFLSH",       // disable flush after interrupt or quit
    "TOSTOP",       // send SIGTTOU for background output

    // Special control characters indices (c_cc array)
    "VINTR",        // interrupt character
    "VQUIT",        // quit character
    "VERASE",       // erase character
    "VKILL",        // kill line character
    "VEOF",         // end-of-file character
    "VTIME",        // timeout in deciseconds for noncanonical read
    "VMIN",         // minimum number of characters for noncanonical read
    "VSWTC",        // switch character (rarely used)
    "VSTART",       // start character (usually Ctrl-Q)
    "VSTOP",        // stop character (usually Ctrl-S)
    "VSUSP",        // suspend character
    "VEOL",         // end-of-line character
    "VREPRINT",     // reprint line character
    "VDISCARD",     // discard output character
    "VWERASE",      // word erase character
    "VLNEXT",       // literal next character

    NULL
};

// Functions declared in termios.h
const char* termios_h_functions[] = {
    "cfgetispeed",  // speed_t cfgetispeed(const struct termios *);
    "cfgetospeed",  // speed_t cfgetospeed(const struct termios *);
    "cfsetispeed",  // int cfsetispeed(struct termios *, speed_t);
    "cfsetospeed",  // int cfsetospeed(struct termios *, speed_t);
    "tcdrain",      // int tcdrain(int);
    "tcflow",       // int tcflow(int, int);
    "tcflush",      // int tcflush(int, int);
    "tcgetattr",    // int tcgetattr(int, struct termios *);
    "tcgetsid",     // pid_t tcgetsid(int);
    "tcsendbreak",  // int tcsendbreak(int, int);
    "tcsetattr",    // int tcsetattr(int, int, const struct termios *);
    NULL
};

