const char* sys_param_h_name = "sys/param.h";

const char* sys_param_h_globals[] = {
    // <sys/param.h> is a system header that defines various system parameters,
    // macros, and constants used across the kernel and user-space programs,
    // especially on BSD-derived systems and many UNIX-like OSes.
    // It does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/param.h
const char* sys_param_h_types[] = {
    // Typically no new types mandated by POSIX in <sys/param.h>
    NULL
};

// Macros declared in sys/param.h
const char* sys_param_h_macros[] = {
    "MAXPATHLEN",       // Maximum path length (system-dependent)
    "MAXSYMLINKS",      // Maximum number of symbolic links to traverse
    "NCARGS",           // Maximum size of arguments to exec functions
    "NOFILE",           // Maximum number of open files per process
    "NBBY",             // Number of bits per byte (usually 8)
    "DEV_BSIZE",        // Device block size (usually 512 bytes)
    "BLKDEV_IOSIZE",    // Block device I/O size
    "MAXBSIZE",         // Maximum block size for filesystem I/O
    "BSIZE",            // Basic block size
    "UMODE_T",          // File mode type (sometimes defined here)
    "HZ",               // Clock ticks per second (system-dependent)
    "PGSHIFT",          // Page shift (log2 of page size)
    "PGSIZE",           // Page size in bytes
    "PGOFSET",          // Page offset mask
    "NBBY",             // Number of bits per byte
    NULL
};

// Functions declared in sys/param.h
const char* sys_param_h_functions[] = {
    // Typically no functions are declared in <sys/param.h>
    NULL
};

