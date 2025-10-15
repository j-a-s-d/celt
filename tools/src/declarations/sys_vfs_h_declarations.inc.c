const char* sys_vfs_h_name = "sys/vfs.h";

const char* sys_vfs_h_globals[] = {
    // <sys/vfs.h> is a system header that defines data structures, constants, and function prototypes
    // related to the virtual file system (VFS) layer in UNIX-like operating systems.
    // It does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/vfs.h
const char* sys_vfs_h_types[] = {
    "struct statfs",       // File system status structure with members such as:
                           // f_type;        // Filesystem type
                           // f_bsize;       // Optimal transfer block size
                           // f_blocks;      // Total data blocks in filesystem
                           // f_bfree;       // Free blocks
                           // f_bavail;      // Free blocks available to unprivileged user
                           // f_files;       // Total file nodes (inodes)
                           // f_ffree;       // Free file nodes
                           // f_fsid;        // Filesystem ID
                           // f_namelen;     // Maximum filename length
                           // f_frsize;      // Fragment size (some systems)
    "struct statvfs",      // POSIX file system status structure (often declared in <sys/statvfs.h>)
    NULL
};

// Macros declared in sys/vfs.h
const char* sys_vfs_h_macros[] = {
    // Filesystem type magic numbers (platform-dependent)
    "NFS_SUPER_MAGIC",     // NFS filesystem type
    "EXT4_SUPER_MAGIC",    // ext4 filesystem type
    "TMPFS_MAGIC",         // tmpfs filesystem type
    "PROC_SUPER_MAGIC",    // proc filesystem type
    "SYSFS_MAGIC",         // sysfs filesystem type
    "MSDOS_SUPER_MAGIC",   // MSDOS filesystem type
    "FUSE_SUPER_MAGIC",    // FUSE filesystem type
    // ... many others depending on platform and kernel version

    NULL
};

// Functions declared in sys/vfs.h
const char* sys_vfs_h_functions[] = {
    "statfs",              // int statfs(const char *path, struct statfs *buf);
    "fstatfs",             // int fstatfs(int fd, struct statfs *buf);
    "statvfs",             // int statvfs(const char *path, struct statvfs *buf);
    "fstatvfs",            // int fstatvfs(int fd, struct statvfs *buf);
    NULL
};

