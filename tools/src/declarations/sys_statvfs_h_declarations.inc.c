const char* sys_statvfs_h_name = "sys/statvfs.h";

const char* sys_statvfs_h_globals[] = {
    // <sys/statvfs.h> declares the statvfs structure, constants, and function prototypes,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/statvfs.h
const char* sys_statvfs_h_types[] = {
    "struct statvfs",   // File system status structure with members:
                       // unsigned long f_bsize;   // File system block size
                       // unsigned long f_frsize;  // Fundamental file system block size
                       // fsblkcnt_t f_blocks;     // Total number of blocks (in f_frsize units)
                       // fsblkcnt_t f_bfree;      // Total number of free blocks
                       // fsblkcnt_t f_bavail;     // Number of free blocks available to unprivileged user
                       // fsfilcnt_t f_files;      // Total number of file serial numbers (inodes)
                       // fsfilcnt_t f_ffree;      // Total number of free file serial numbers
                       // fsfilcnt_t f_favail;     // Number of file serial numbers available to unprivileged user
                       // unsigned long f_fsid;    // File system ID
                       // unsigned long f_flag;    // Bit mask of mount flags
                       // unsigned long f_namemax; // Maximum filename length
    NULL
};

// Macros declared in sys/statvfs.h
const char* sys_statvfs_h_macros[] = {
    "ST_RDONLY",    // File system mounted read-only
    "ST_NOSUID",    // File system does not support set-user-ID and set-group-ID bits
    "ST_NODEV",     // Do not interpret character or block special devices on the file system
    "ST_NOEXEC",    // Do not allow execution of any binaries on the mounted file system
    "ST_SYNCHRONOUS", // Writes are synced immediately
    "ST_MANDLOCK",  // Allow mandatory locking on the file system
    "ST_WRITE",     // File system is writable
    "ST_APPEND",    // Append-only file system
    "ST_IMMUTABLE", // Immutable file system
    "ST_NOATIME",   // Do not update access times
    "ST_NODIRATIME",// Do not update directory access times
    "ST_RELATIME",  // Update atime relative to mtime/ctime
    // Note: Availability of some flags may vary by system
    NULL
};

// Functions declared in sys/statvfs.h
const char* sys_statvfs_h_functions[] = {
    "statvfs",      // int statvfs(const char *path, struct statvfs *buf);
    "fstatvfs",     // int fstatvfs(int fd, struct statvfs *buf);
    NULL
};

