const char* sys_sem_h_name = "sys/sem.h";

const char* sys_sem_h_globals[] = {
    // <sys/sem.h> does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/sem.h
const char* sys_sem_h_types[] = {
    "struct semid_ds",   // Semaphore set data structure with members:
                         // struct ipc_perm sem_perm;    // operation permission structure
                         // unsigned short sem_nsems;   // number of semaphores in set
                         // time_t sem_otime;            // last semop() time
                         // time_t sem_ctime;            // last change time by semctl()
    "struct sembuf",     // Semaphore operation structure with members:
                         // unsigned short sem_num;      // semaphore number
                         // short sem_op;                // semaphore operation
                         // short sem_flg;               // operation flags
    "unsigned short",    // used for semaphore values and counts
    NULL
};

// Macros declared in sys/sem.h
const char* sys_sem_h_macros[] = {
    "SEM_UNDO",          // Flag to adjust semaphore on process exit

    // Commands for semctl()
    "GETNCNT",           // Get number of processes waiting for semval to increase
    "GETPID",            // Get PID of last operation
    "GETVAL",            // Get semaphore value
    "GETALL",            // Get all semaphore values in set
    "GETZCNT",           // Get number of processes waiting for semval to become zero
    "SETVAL",            // Set semaphore value
    "SETALL",            // Set all semaphore values in set

    NULL
};

// Functions declared in sys/sem.h
const char* sys_sem_h_functions[] = {
    "semctl",            // int semctl(int semid, int semnum, int cmd, ...);
    "semget",            // int semget(key_t key, int nsems, int semflg);
    "semop",             // int semop(int semid, struct sembuf *sops, size_t nsops);
    NULL
};

