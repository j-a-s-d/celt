const char* dirent_h_name = "dirent.h";

const char* dirent_h_globals[] = {
    // The <dirent.h> header defines types and functions for directory stream operations,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in dirent.h
const char* dirent_h_types[] = {
    "DIR",          // type representing a directory stream
    "struct dirent",// structure describing a directory entry
    NULL
};

// Macros declared in dirent.h
const char* dirent_h_macros[] = {
    // None mandated by POSIX in <dirent.h>
    NULL
};

// Functions declared in dirent.h
const char* dirent_h_functions[] = {
    "opendir",      // DIR *opendir(const char *name);
    "readdir",      // struct dirent *readdir(DIR *dirp);
    "readdir_r",    // int readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result);
    "closedir",     // int closedir(DIR *dirp);
    "rewinddir",    // void rewinddir(DIR *dirp);
    "seekdir",      // void seekdir(DIR *dirp, long loc);
    "telldir",      // long telldir(DIR *dirp);
    NULL
};

