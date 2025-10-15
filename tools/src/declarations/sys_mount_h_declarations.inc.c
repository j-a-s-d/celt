const char* sys_mount_h_name = "sys/mount.h";

const char* sys_mount_h_globals[] = {
    // <sys/mount.h> declares constants, macros, and types related to mounting and unmounting filesystems on Linux,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/mount.h
const char* sys_mount_h_types[] = {
    "struct mount_attr",   // Structure describing mount attributes (Linux-specific), with fields like:
                           // __u64 attr_set;       // Attributes to set
                           // __u64 attr_clr;       // Attributes to clear
                           // __u64 propagation;    // Propagation flags
                           // __u64 userns_fd;      // User namespace file descriptor
    NULL
};

// Macros declared in sys/mount.h
const char* sys_mount_h_macros[] = {
    // Mount flags (fs-independent), used in mount(2) syscall
    "MS_RDONLY",           // Mount read-only
    "MS_NOSUID",           // Ignore suid and sgid bits
    "MS_NODEV",            // Disallow access to device special files
    "MS_NOEXEC",           // Disallow program execution
    "MS_SYNCHRONOUS",      // Writes are synced immediately
    "MS_REMOUNT",          // Remount an existing mount
    "MS_MANDLOCK",         // Allow mandatory locks on FS
    "MS_DIRSYNC",          // Directory modifications are synchronous
    "MS_NOATIME",          // Do not update access times
    "MS_NODIRATIME",       // Do not update directory access times
    "MS_BIND",             // Bind mount
    "MS_MOVE",             // Move mount point
    "MS_REC",              // Recursive mount or unmount
    "MS_SILENT",           // Suppress some error messages
    "MS_POSIXACL",         // VFS supports POSIX ACLs
    "MS_UNBINDABLE",       // Change to unbindable
    "MS_PRIVATE",          // Change to private
    "MS_SLAVE",            // Change to slave
    "MS_SHARED",           // Change to shared
    "MS_RELATIME",         // Update atime relative to mtime/ctime
    "MS_KERNMOUNT",        // This is a kern_mount call
    "MS_I_VERSION",        // Update inode I_version field
    "MS_STRICTATIME",      // Always perform atime updates
    "MS_LAZYTIME",         // Update times lazily
    NULL
};

// Functions declared in sys/mount.h
const char* sys_mount_h_functions[] = {
    "mount",               // int mount(const char *source, const char *target,
                           //           const char *filesystemtype, unsigned long mountflags,
                           //           const void *data);
    "umount",              // int umount(const char *target);
    "umount2",             // int umount2(const char *target, int flags);
    NULL
};

