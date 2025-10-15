const char* sys_mman_h_name = "sys/mman.h";

const char* sys_mman_h_globals[] = {
    // <sys/mman.h> declares symbolic constants, types, and functions for memory management,
    // including memory mapping, locking, synchronization, and shared memory.
    // It does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/mman.h
const char* sys_mman_h_types[] = {
    "struct posix_typed_mem_info", // structure describing typed memory info
    NULL
};

// Macros declared in sys/mman.h
const char* sys_mman_h_macros[] = {
    // Protection flags for mmap()
    "PROT_EXEC",       // Pages may be executed
    "PROT_NONE",       // Pages may not be accessed
    "PROT_READ",       // Pages may be read
    "PROT_WRITE",      // Pages may be written

    // Flags for mmap()
    "MAP_FIXED",       // Interpret addr exactly
    "MAP_PRIVATE",     // Changes are private
    "MAP_SHARED",      // Share changes

    // Flags for msync()
    "MS_ASYNC",        // Perform asynchronous writes
    "MS_INVALIDATE",   // Invalidate mappings
    "MS_SYNC",         // Perform synchronous writes

    // Flags for mlockall()
    "MCL_CURRENT",     // Lock currently mapped pages
    "MCL_FUTURE",      // Lock pages that become mapped

    // Flags for posix_typed_mem_open()
    "POSIX_TYPED_MEM_ALLOCATE",         // Allocate on mmap()
    "POSIX_TYPED_MEM_ALLOCATE_CONTIG",  // Allocate contiguously on mmap()
    "POSIX_TYPED_MEM_MAP_ALLOCATABLE",  // Map on mmap() without affecting allocatability

    // Advice flags for posix_madvise()
    "POSIX_MADV_DONTNEED",   // Expect not to access range soon
    "POSIX_MADV_NORMAL",     // No special advice (default)
    "POSIX_MADV_RANDOM",     // Expect random access
    "POSIX_MADV_SEQUENTIAL", // Expect sequential access
    "POSIX_MADV_WILLNEED",   // Expect to access soon

    // Special constant indicating mmap failure
    "MAP_FAILED",

    NULL
};

// Functions declared in sys/mman.h
const char* sys_mman_h_functions[] = {
    "mlock",                // int mlock(const void *addr, size_t len);
    "mlockall",             // int mlockall(int flags);
    "mmap",                 // void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
    "mprotect",             // int mprotect(void *addr, size_t len, int prot);
    "msync",                // int msync(void *addr, size_t len, int flags);
    "munlock",              // int munlock(const void *addr, size_t len);
    "munlockall",           // int munlockall(void);
    "munmap",               // int munmap(void *addr, size_t len);
    "posix_madvise",        // int posix_madvise(void *addr, size_t len, int advice);
    "posix_mem_offset",     // int posix_mem_offset(const void *restrict addr, size_t len, off_t *restrict off, size_t *restrict devsz, int *restrict flags);
    "posix_typed_mem_get_info", // int posix_typed_mem_get_info(int fd, struct posix_typed_mem_info *info);
    "posix_typed_mem_open", // int posix_typed_mem_open(const char *name, int oflag, int tflag);
    "shm_open",             // int shm_open(const char *name, int oflag, mode_t mode);
    "shm_unlink",           // int shm_unlink(const char *name);

    NULL
};

