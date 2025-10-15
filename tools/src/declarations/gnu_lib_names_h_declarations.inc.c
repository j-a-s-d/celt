const char* gnu_lib_names_h_name = "gnu/lib-names.h";

const char* gnu_lib_names_h_globals[] = {
    // <gnu/lib-names.h> defines macros for the shared library filenames of GNU libc components,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in gnu/lib-names.h
const char* gnu_lib_names_h_types[] = {
    // None; this header only defines macros for shared library filenames
    NULL
};

// Macros declared in gnu/lib-names.h
const char* gnu_lib_names_h_macros[] = {
    "LD_LINUX_SO",           // e.g. "ld-linux.so.2" or "ld-linux-x86-64.so.2"
    "LD_SO",                 // Linker/loader shared object name (alias of LD_LINUX_SO)
    "LIBANL_SO",             // "libanl.so.1"
    "LIBBROKENLOCALE_SO",    // "libBrokenLocale.so.1"
    "LIBCIDN_SO",            // "libcidn.so.1"
    "LIBCRYPT_SO",           // "libcrypt.so.1"
    "LIBC_SO",               // "libc.so.6"
    "LIBDL_SO",              // "libdl.so.2"
    "LIBM_SO",               // "libm.so.6"
    "LIBNSL_SO",             // "libnsl.so.1"
    "LIBNSS_COMPAT_SO",      // "libnss_compat.so.2"
    "LIBNSS_DNS_SO",         // "libnss_dns.so.2"
    "LIBNSS_FILES_SO",       // "libnss_files.so.2"
    "LIBNSS_HESIOD_SO",      // "libnss_hesiod.so.2"
    "LIBNSS_LDAP_SO",        // "libnss_ldap.so.2"
    "LIBNSS_NISPLUS_SO",     // "libnss_nisplus.so.2"
    "LIBNSS_NIS_SO",         // "libnss_nis.so.2"
    "LIBPTHREAD_SO",         // "libpthread.so.0"
    "LIBRESOLV_SO",          // "libresolv.so.2"
    "LIBRT_SO",              // "librt.so.1"
    "LIBTHREAD_DB_SO",       // "libthread_db.so.1"
    "LIBUTIL_SO",            // "libutil.so.1"
    NULL
};

// Functions declared in gnu/lib-names.h
const char* gnu_lib_names_h_functions[] = {
    // None; this header only defines macros for sonames of GNU libc shared libraries
    NULL
};

