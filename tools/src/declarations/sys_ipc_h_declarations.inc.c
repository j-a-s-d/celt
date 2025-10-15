const char* sys_ipc_h_name = "sys/ipc.h";

const char* sys_ipc_h_globals[] = {
    // <sys/ipc.h> declares types, constants, and the function ftok() for XSI interprocess communication (IPC),
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/ipc.h
const char* sys_ipc_h_types[] = {
    "struct ipc_perm",  // IPC permission structure with members:
                       // uid_t uid;    // Owner's user ID
                       // gid_t gid;    // Owner's group ID
                       // uid_t cuid;   // Creator's user ID
                       // gid_t cgid;   // Creator's group ID
                       // mode_t mode;  // Read/write permission bits
                       // key_t key;    // Key supplied to create the IPC object
                       // unsigned short seq; // Sequence number
    NULL
};

// Macros declared in sys/ipc.h
const char* sys_ipc_h_macros[] = {
    // Flags for IPC creation and operation
    "IPC_CREAT",       // Create entry if key does not exist
    "IPC_EXCL",        // Fail if key exists (used with IPC_CREAT)
    "IPC_NOWAIT",      // Return error on wait (do not block)

    // Special key values
    "IPC_PRIVATE",     // Private key (usually 0)

    // Control commands for IPC objects
    "IPC_RMID",        // Remove identifier
    "IPC_SET",         // Set options
    "IPC_STAT",        // Get options/status

    NULL
};

// Functions declared in sys/ipc.h
const char* sys_ipc_h_functions[] = {
    "ftok",            // key_t ftok(const char *pathname, int proj_id);
    NULL
};

