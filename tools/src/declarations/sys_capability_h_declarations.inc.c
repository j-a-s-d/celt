const char* sys_capability_h_name = "sys/capability.h";

const char* sys_capability_h_globals[] = {
    // <sys/capability.h> declares types, constants, and functions for Linux capabilities,
    // but it does NOT declare or define global variables with external linkage.
    NULL
};

// Types declared in sys/capability.h
const char* sys_capability_h_types[] = {
    "cap_t",             // Opaque handle for a capability set
    "cap_value_t",       // Integer type representing a single capability value
    "cap_flag_t",        // Enumeration for capability flag types (e.g., effective, permitted, inheritable)
    "cap_flag_value_t",  // Enumeration for flag values (set or clear)
    "cap_user_header_t", // Pointer to user-space capability header structure (kernel interface)
    "cap_user_data_t",   // Pointer to user-space capability data structure (kernel interface)
    NULL
};

// Macros declared in sys/capability.h
const char* sys_capability_h_macros[] = {
    // Capability flag types
    "CAP_EFFECTIVE",     // Effective capability set
    "CAP_PERMITTED",     // Permitted capability set
    "CAP_INHERITABLE",   // Inheritable capability set

    // Flag values
    "CAP_SET",           // Flag is set
    "CAP_CLEAR",         // Flag is clear

    // Common capability values (examples, actual list is in linux/capability.h)
    "CAP_CHOWN",
    "CAP_DAC_OVERRIDE",
    "CAP_DAC_READ_SEARCH",
    "CAP_FOWNER",
    "CAP_FSETID",
    "CAP_KILL",
    "CAP_SETGID",
    "CAP_SETUID",
    "CAP_SETPCAP",
    "CAP_LINUX_IMMUTABLE",
    "CAP_NET_BIND_SERVICE",
    "CAP_NET_BROADCAST",
    "CAP_NET_ADMIN",
    "CAP_NET_RAW",
    "CAP_IPC_LOCK",
    "CAP_IPC_OWNER",
    "CAP_SYS_MODULE",
    "CAP_SYS_RAWIO",
    "CAP_SYS_CHROOT",
    "CAP_SYS_PTRACE",
    "CAP_SYS_PACCT",
    "CAP_SYS_ADMIN",
    "CAP_SYS_BOOT",
    "CAP_SYS_NICE",
    "CAP_SYS_RESOURCE",
    "CAP_SYS_TIME",
    "CAP_SYS_TTY_CONFIG",
    "CAP_MKNOD",
    "CAP_LEASE",
    "CAP_AUDIT_WRITE",
    "CAP_AUDIT_CONTROL",
    "CAP_SETFCAP",
    "CAP_MAC_OVERRIDE",
    "CAP_MAC_ADMIN",
    "CAP_SYSLOG",
    "CAP_WAKE_ALARM",
    "CAP_BLOCK_SUSPEND",
    "CAP_AUDIT_READ",
    NULL
};

// Functions declared in sys/capability.h
const char* sys_capability_h_functions[] = {
    "cap_get_file",         // cap_t cap_get_file(const char *path_p);
    "cap_set_file",         // int cap_set_file(const char *path_p, cap_t cap_p);
    "cap_get_proc",         // cap_t cap_get_proc(void);
    "cap_set_proc",         // int cap_set_proc(cap_t cap_p);
    "cap_init",             // cap_t cap_init(void);
    "cap_clear",            // int cap_clear(cap_t cap_p);
    "cap_free",             // int cap_free(void *cap);
    "cap_dup",              // cap_t cap_dup(cap_t cap_p);
    "cap_from_text",        // cap_t cap_from_text(const char *text_p);
    "cap_to_text",          // char *cap_to_text(cap_t cap_p, ssize_t *len_p);
    "cap_get_flag",         // int cap_get_flag(cap_t cap_p, cap_value_t cap, cap_flag_t flag, cap_flag_value_t *value_p);
    "cap_set_flag",         // int cap_set_flag(cap_t cap_p, cap_flag_t flag, int ncap, const cap_value_t *caps, cap_flag_value_t value);
    "cap_compare",          // int cap_compare(cap_t cap1, cap_t cap2);
    "cap_copy_ext",         // int cap_copy_ext(cap_t dest, cap_t src);
    "cap_is_subset",        // int cap_is_subset(cap_t subset, cap_t superset);
    "cap_to_name",          // const char *cap_to_name(cap_value_t cap);
    "cap_from_name",        // int cap_from_name(const char *name, cap_value_t *cap);
    NULL
};

