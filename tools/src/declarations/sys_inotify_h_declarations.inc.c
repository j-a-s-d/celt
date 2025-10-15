const char* sys_inotify_h_name = "sys/inotify.h";

const char* sys_inotify_h_globals[] = {
    // <sys/inotify.h> declares constants, types, and function prototypes for the inotify API,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/inotify.h
const char* sys_inotify_h_types[] = {
    "struct inotify_event",  // Structure describing an inotify event with members:
                             // int wd;           // Watch descriptor
                             // uint32_t mask;    // Mask of events
                             // uint32_t cookie;  // Unique cookie associating related events
                             // uint32_t len;     // Length of name field
                             // char name[];      // Optional null-terminated name
    NULL
};

// Macros declared in sys/inotify.h
const char* sys_inotify_h_macros[] = {
    // Initialization flags
    "IN_NONBLOCK",           // Open in non-blocking mode
    "IN_CLOEXEC",            // Set close-on-exec flag

    // Event masks (can be ORed)
    "IN_ACCESS",             // File was accessed
    "IN_MODIFY",             // File was modified
    "IN_ATTRIB",             // Metadata changed
    "IN_CLOSE_WRITE",        // Writable file closed
    "IN_CLOSE_NOWRITE",      // Unwritable file closed
    "IN_OPEN",               // File was opened
    "IN_MOVED_FROM",         // File moved out of watched directory
    "IN_MOVED_TO",           // File moved into watched directory
    "IN_CREATE",             // File/directory created
    "IN_DELETE",             // File/directory deleted
    "IN_DELETE_SELF",        // Watched file/directory was itself deleted
    "IN_MOVE_SELF",          // Watched file/directory was itself moved

    // Special flags
    "IN_UNMOUNT",            // Backing filesystem was unmounted
    "IN_Q_OVERFLOW",         // Event queue overflowed
    "IN_IGNORED",            // Watch was removed explicitly or file was deleted

    // Helper masks
    "IN_CLOSE",              // Close (write or nowrite)
    "IN_MOVE",               // Move (from or to)

    // Watch mask modifiers
    "IN_ONLYDIR",            // Only watch the path if it is a directory
    "IN_DONT_FOLLOW",        // Do not follow a symbolic link
    "IN_EXCL_UNLINK",        // Exclude events on unlinked objects
    "IN_MASK_ADD",           // Add to the mask of an existing watch
    "IN_ISDIR",              // Event occurred against a directory
    "IN_ONESHOT",            // Only send event once

    NULL
};

// Functions declared in sys/inotify.h
const char* sys_inotify_h_functions[] = {
    "inotify_init",          // int inotify_init(void);
    "inotify_init1",         // int inotify_init1(int flags);
    "inotify_add_watch",     // int inotify_add_watch(int fd, const char *pathname, uint32_t mask);
    "inotify_rm_watch",      // int inotify_rm_watch(int fd, int wd);
    NULL
};

