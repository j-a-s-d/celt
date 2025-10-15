const char* ftw_h_name = "ftw.h";

const char* ftw_h_globals[] = {
    // <ftw.h> declares functions for file tree traversal,
    // but it does NOT define any global variables with external linkage.
    NULL
};

// Types declared in ftw.h
const char* ftw_h_types[] = {
    "struct FTW",   // Structure passed to the callback function in nftw(), with members:
                    // int base;   // Offset of the filename in the pathname
                    // int level;  // Depth of the current file relative to the root of the tree
    NULL
};

// Macros declared in ftw.h
const char* ftw_h_macros[] = {
    // Values for the typeflag argument passed to the callback function in ftw() and nftw()
    "FTW_F",     // File
    "FTW_D",     // Directory
    "FTW_DNR",   // Directory without read permission
    "FTW_DP",    // Directory with subdirectories visited (post-order)
    "FTW_NS",    // Unknown type; stat() failed
    "FTW_SL",    // Symbolic link
    "FTW_SLN",   // Symbolic link that names a nonexistent file

    // Flags for the fourth argument of nftw()
    "FTW_PHYS",  // Physical walk; do not follow symbolic links
    "FTW_MOUNT", // Do not cross mount points
    "FTW_DEPTH", // Visit all subdirectories before the directory itself (post-order)
    "FTW_CHDIR", // Change to each directory before reading it

    NULL
};

// Functions declared in ftw.h
const char* ftw_h_functions[] = {
    "ftw",       // int ftw(const char *pathname, int (*fn)(const char *, const struct stat *, int), int nopenfd);
    "nftw",      // int nftw(const char *pathname, int (*fn)(const char *, const struct stat *, int, const struct FTW *), int nopenfd, int flags);
    NULL
};

