const char* sys_sysinfo_h_name = "sys/sysinfo.h";

const char* sys_sysinfo_h_globals[] = {
    // <sys/sysinfo.h> declares the struct sysinfo and the sysinfo() system call interface,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/sysinfo.h
const char* sys_sysinfo_h_types[] = {
    "struct sysinfo",   // Structure holding system statistics like uptime, memory, load averages, etc.
    NULL
};

// Macros declared in sys/sysinfo.h
const char* sys_sysinfo_h_macros[] = {
    "SI_LOAD_SHIFT",    // Shift value used to scale load averages (usually 16)
    NULL
};

// Functions declared in sys/sysinfo.h
const char* sys_sysinfo_h_functions[] = {
    "sysinfo",          // int sysinfo(struct sysinfo *info);
    "get_nprocs_conf",  // int get_nprocs_conf(void); returns number of configured processors
    "get_nprocs",       // int get_nprocs(void); returns number of available processors
    "get_phys_pages",   // long get_phys_pages(void); total physical pages of memory
    "get_avphys_pages", // long get_avphys_pages(void); available physical pages
    NULL
};

