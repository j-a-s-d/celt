const char* sys_types_h_name = "sys/types.h";

const char* sys_types_h_globals[] = {
    // <sys/types.h> defines a wide range of fundamental data types used throughout system headers and APIs,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/types.h
const char* sys_types_h_types[] = {
    "blkcnt_t",     // file block counts
    "blksize_t",    // block sizes
    "clock_t",      // system times in clock ticks
    "clockid_t",    // clock ID type (POSIX)
    "dev_t",        // device IDs
    "fsblkcnt_t",   // file system block counts (XSI)
    "fsfilcnt_t",   // file system file counts (XSI)
    "gid_t",        // group IDs
    "id_t",         // general identifier (can hold pid_t, uid_t, gid_t)
    "ino_t",        // file serial numbers (inode numbers)
    "key_t",        // IPC keys (XSI)
    "mode_t",       // file attribute bitmasks
    "nlink_t",      // link counts
    "off_t",        // file sizes and offsets
    "pid_t",        // process IDs and process group IDs
    "pthread_attr_t",// thread attribute object (POSIX threads)
    "size_t",       // size type (usually from <stddef.h>)
    "ssize_t",      // signed size type
    "time_t",       // time values
    "uid_t",        // user IDs
    NULL
};

// Macros declared in sys/types.h
const char* sys_types_h_macros[] = {
    // Typically sys/types.h does not define many macros,
    // but may define feature test macros or constants in some implementations.
    NULL
};

// Functions declared in sys/types.h
const char* sys_types_h_functions[] = {
    // sys/types.h declares no functions itself; functions using these types
    // are declared in other headers like <unistd.h>, <sys/stat.h>, etc.
    NULL
};

