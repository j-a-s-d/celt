const char* sys_auxv_h_name = "sys/auxv.h";

const char* sys_auxv_h_globals[] = {
    // <sys/auxv.h> does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/auxv.h
const char* sys_auxv_h_types[] = {
    "auxv_t",       // Structure representing an auxiliary vector entry:
                    // int a_type;        // Entry type (e.g., AT_PHDR, AT_BASE)
                    // union {
                    //     long a_val;    // Integer value
                    //     void *a_ptr;   // Pointer value
                    //     void (*a_fcn)(); // Function pointer
                    // } a_un;
    "auxv32_t",     // 32-bit variant of auxv_t for 32-bit systems
    NULL
};

// Macros declared in sys/auxv.h
const char* sys_auxv_h_macros[] = {
    "AT_NULL",          // End of vector
    "AT_IGNORE",        // Entry should be ignored
    "AT_EXECFD",        // File descriptor of program
    "AT_PHDR",          // Program headers
    "AT_PHENT",         // Size of program header entry
    "AT_PHNUM",         // Number of program headers
    "AT_PAGESZ",        // System page size
    "AT_BASE",          // Base address of interpreter
    "AT_FLAGS",         // Flags
    "AT_ENTRY",         // Entry point of program
    "AT_RANDOM",        // Address of 16 random bytes
    "AT_SECURE",        // Secure execution flag
    "AT_UID",           // Real user ID
    "AT_EUID",          // Effective user ID
    "AT_GID",           // Real group ID
    "AT_EGID",          // Effective group ID
    "AT_PLATFORM",      // String identifying platform
    "AT_HWCAP",         // Hardware capabilities
    "AT_CLKTCK",        // Frequency of times()
    // ... plus architecture- or OS-specific entries like AT_SUN_EXECNAME, AT_SUN_MMU, etc.
    NULL
};

// Functions declared in sys/auxv.h
const char* sys_auxv_h_functions[] = {
    "getauxval",    // unsigned long int getauxval(unsigned long int type);
    NULL
};

