const char* sys_shm_h_name = "sys/shm.h";

const char* sys_shm_h_globals[] = {
    // <sys/shm.h> does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/shm.h
const char* sys_shm_h_types[] = {
    "shmatt_t",         // Unsigned integer type for number of current attaches (at least as large as unsigned short)
    "struct shmid_ds",  // Shared memory segment data structure with members:
                        // struct ipc_perm shm_perm;   // operation permission structure
                        // size_t shm_segsz;          // size of segment in bytes
                        // pid_t shm_lpid;            // PID of last shared memory operation
                        // pid_t shm_cpid;            // PID of creator
                        // shmatt_t shm_nattch;      // number of current attaches
                        // time_t shm_atime;          // time of last shmat()
                        // time_t shm_dtime;          // time of last shmdt()
                        // time_t shm_ctime;          // time of last change by shmctl()
    NULL
};

// Macros declared in sys/shm.h
const char* sys_shm_h_macros[] = {
    "SHM_RDONLY",       // Attach read-only (else read-write)
    "SHM_RND",          // Round attach address to SHMLBA
    "SHMLBA",           // Segment low boundary address multiple
    NULL
};

// Functions declared in sys/shm.h
const char* sys_shm_h_functions[] = {
    "shmat",            // void *shmat(int shmid, const void *shmaddr, int shmflg);
    "shmctl",           // int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    "shmdt",            // int shmdt(const void *shmaddr);
    "shmget",           // int shmget(key_t key, size_t size, int shmflg);
    NULL
};

