const char* sys_event_h_name = "sys/event.h";

const char* sys_event_h_globals[] = {
    // <sys/event.h> is a header specific to BSD-derived systems (e.g., FreeBSD, macOS),
    // providing the interface for the kqueue event notification system.
    // It declares types, constants, and functions related to kqueue,
    // but does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/event.h
const char* sys_event_h_types[] = {
    "struct kevent",    // Kernel event structure used with kqueue, containing members like:
                        // uintptr_t ident;       // Identifier for the event (e.g., file descriptor)
                        // short filter;         // Filter for event type (e.g., EVFILT_READ)
                        // unsigned short flags; // Action flags (e.g., EV_ADD, EV_DELETE)
                        // unsigned int fflags;  // Filter-specific flags
                        // intptr_t data;        // Filter-specific data
                        // void *udata;          // User data pointer
    NULL
};

// Macros declared in sys/event.h
const char* sys_event_h_macros[] = {
    // Filters
    "EVFILT_READ",      // Monitor for read readiness
    "EVFILT_WRITE",     // Monitor for write readiness
    "EVFILT_TIMER",     // Timer event
    "EVFILT_SIGNAL",    // Signal event
    "EVFILT_VNODE",     // File system node event
    "EVFILT_PROC",      // Process event
    "EVFILT_USER",      // User-triggered event
    "EVFILT_FS",        // Filesystem event (FreeBSD-specific)

    // Flags
    "EV_ADD",           // Add event to kqueue
    "EV_DELETE",        // Delete event from kqueue
    "EV_ENABLE",        // Enable event
    "EV_DISABLE",       // Disable event
    "EV_ONESHOT",       // Event is one-shot
    "EV_CLEAR",         // Clear event state after notification
    "EV_RECEIPT",       // Request receipt of event status
    NULL
};

// Functions declared in sys/event.h
const char* sys_event_h_functions[] = {
    "kqueue",           // int kqueue(void);
    "kevent",           // int kevent(int kq, const struct kevent *changelist, int nchanges,
                        //             struct kevent *eventlist, int nevents,
                        //             const struct timespec *timeout);
    NULL
};

