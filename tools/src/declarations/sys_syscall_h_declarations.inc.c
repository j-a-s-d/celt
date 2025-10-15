const char* sys_syscall_h_name = "sys/syscall.h";

const char* sys_syscall_h_globals[] = {
    // <sys/syscall.h> declares symbolic constants for system call numbers (SYS_*),
    // and declares the syscall() function for making arbitrary system calls,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/syscall.h
const char* sys_syscall_h_types[] = {
    // Typically none; this header mainly defines symbolic constants for system call numbers
    NULL
};

// Macros declared in sys/syscall.h
const char* sys_syscall_h_macros[] = {
    // System call number constants, e.g.:
    "SYS_read",         // System call number for read
    "SYS_write",        // System call number for write
    "SYS_open",         // System call number for open
    "SYS_close",        // System call number for close
    "SYS_stat",         // System call number for stat
    "SYS_fstat",        // System call number for fstat
    "SYS_lstat",        // System call number for lstat
    "SYS_poll",         // System call number for poll
    "SYS_lseek",        // System call number for lseek
    "SYS_mmap",         // System call number for mmap
    "SYS_mprotect",     // System call number for mprotect
    "SYS_munmap",       // System call number for munmap
    "SYS_brk",          // System call number for brk
    "SYS_rt_sigaction", // System call number for rt_sigaction
    "SYS_rt_sigprocmask",// System call number for rt_sigprocmask
    "SYS_ioctl",        // System call number for ioctl
    "SYS_pread64",      // System call number for pread64
    "SYS_pwrite64",     // System call number for pwrite64
    "SYS_readv",        // System call number for readv
    "SYS_writev",       // System call number for writev
    "SYS_access",       // System call number for access
    "SYS_pipe",         // System call number for pipe
    "SYS_select",       // System call number for select
    "SYS_sched_yield",  // System call number for sched_yield
    "SYS_mremap",       // System call number for mremap
    "SYS_msync",        // System call number for msync
    "SYS_mincore",      // System call number for mincore
    "SYS_madvise",      // System call number for madvise
    "SYS_shmget",       // System call number for shmget
    "SYS_shmat",        // System call number for shmat
    "SYS_shmctl",       // System call number for shmctl
    "SYS_dup",          // System call number for dup
    "SYS_dup2",         // System call number for dup2
    // ... and many more, platform and version dependent
    NULL
};

// Functions declared in sys/syscall.h
const char* sys_syscall_h_functions[] = {
    "syscall",          // long syscall(long number, ...);
    "__syscall",        // quad_t __syscall(quad_t number, ...); (for 64-bit arguments)
    NULL
};

