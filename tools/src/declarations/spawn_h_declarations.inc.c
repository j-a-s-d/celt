const char* spawn_h_name = "spawn.h";

const char* spawn_h_globals[] = {
    // <spawn.h> does NOT define any global variables with external linkage.
    NULL
};

// Types declared in spawn.h
const char* spawn_h_types[] = {
    "posix_spawn_file_actions_t",   // Type for file actions object used with posix_spawn
    "posix_spawnattr_t",            // Type for spawn attributes object used with posix_spawn
    NULL
};

// Macros declared in spawn.h
const char* spawn_h_macros[] = {
    "POSIX_SPAWN_RESETIDS",         // Flag to reset user and group IDs in spawned process
    "POSIX_SPAWN_SETPGROUP",        // Flag to set process group ID
    "POSIX_SPAWN_SETSIGDEF",        // Flag to set default signal actions
    "POSIX_SPAWN_SETSIGMASK",       // Flag to set signal mask
    "POSIX_SPAWN_USEVFORK",         // Flag to use vfork instead of fork (if supported)
    NULL
};

// Functions declared in spawn.h
const char* spawn_h_functions[] = {
    "posix_spawn",                  // int posix_spawn(pid_t *pid, const char *path, const posix_spawn_file_actions_t *file_actions, const posix_spawnattr_t *attrp, char *const argv[], char *const envp[]);
    "posix_spawnp",                 // int posix_spawnp(pid_t *pid, const char *file, const posix_spawn_file_actions_t *file_actions, const posix_spawnattr_t *attrp, char *const argv[], char *const envp[]);
    "posix_spawn_file_actions_init",   // int posix_spawn_file_actions_init(posix_spawn_file_actions_t *file_actions);
    "posix_spawn_file_actions_destroy",// int posix_spawn_file_actions_destroy(posix_spawn_file_actions_t *file_actions);
    "posix_spawn_file_actions_addclose",// int posix_spawn_file_actions_addclose(posix_spawn_file_actions_t *file_actions, int fd);
    "posix_spawn_file_actions_adddup2", // int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t *file_actions, int fd, int newfd);
    "posix_spawn_file_actions_addopen", // int posix_spawn_file_actions_addopen(posix_spawn_file_actions_t *file_actions, int fd, const char *path, int oflag, mode_t mode);
    "posix_spawnattr_init",             // int posix_spawnattr_init(posix_spawnattr_t *attr);
    "posix_spawnattr_destroy",          // int posix_spawnattr_destroy(posix_spawnattr_t *attr);
    "posix_spawnattr_getflags",         // int posix_spawnattr_getflags(const posix_spawnattr_t *attr, short *flags);
    "posix_spawnattr_setflags",         // int posix_spawnattr_setflags(posix_spawnattr_t *attr, short flags);
    "posix_spawnattr_getpgroup",        // int posix_spawnattr_getpgroup(const posix_spawnattr_t *attr, pid_t *pgroup);
    "posix_spawnattr_setpgroup",        // int posix_spawnattr_setpgroup(posix_spawnattr_t *attr, pid_t pgroup);
    "posix_spawnattr_getsigdefault",    // int posix_spawnattr_getsigdefault(const posix_spawnattr_t *attr, sigset_t *sigdefault);
    "posix_spawnattr_setsigdefault",    // int posix_spawnattr_setsigdefault(posix_spawnattr_t *attr, const sigset_t *sigdefault);
    "posix_spawnattr_getsigmask",       // int posix_spawnattr_getsigmask(const posix_spawnattr_t *attr, sigset_t *sigmask);
    "posix_spawnattr_setsigmask",       // int posix_spawnattr_setsigmask(posix_spawnattr_t *attr, const sigset_t *sigmask);
    NULL
};

