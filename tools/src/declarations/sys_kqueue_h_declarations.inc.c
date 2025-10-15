const char* sys_kqueue_h_name = "sys/kqueue.h";

const char* sys_kqueue_h_globals[] = {
    // <sys/kqueue.h> is a BSD-specific header providing declarations for the kqueue event notification system.
    // It declares types, constants, and function prototypes related to kqueue and kevent,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/kqueue.h (usually <sys/event.h>)
const char* sys_kqueue_h_types[] = {
    "struct kevent",   // Kernel event structure with members:
                       // uintptr_t ident;      // Identifier for the event (e.g., file descriptor)
                       // int16_t   filter;    // Filter for event type (e.g., EVFILT_READ)
                       // uint16_t  flags;     // Action flags (e.g., EV_ADD, EV_DELETE)
                       // uint32_t  fflags;    // Filter-specific flags
                       // intptr_t  data;      // Filter-specific data
                       // void     *udata;     // User data pointer
    NULL
};

// Macros declared in sys/kqueue.h (usually <sys/event.h>)
const char* sys_kqueue_h_macros[] = {
    // Filters
    "EVFILT_READ",      // Filter for read availability
    "EVFILT_WRITE",     // Filter for write availability
    "EVFILT_TIMER",     // Timer filter
    "EVFILT_SIGNAL",    // Signal filter
    "EVFILT_PROC",      // Process events filter
    "EVFILT_VNODE",     // Vnode (file) events filter
    "EVFILT_USER",      // User-triggered events

    // Flags
    "EV_ADD",           // Add event to kqueue
    "EV_DELETE",        // Remove event from kqueue
    "EV_ENABLE",        // Enable event
    "EV_DISABLE",       // Disable event
    "EV_ONESHOT",       // Automatically remove event after one trigger
    "EV_CLEAR",         // Clear event state after notification

    // Other useful macros
    "EV_EOF",           // EOF detected
    "EV_ERROR",         // Error condition

    // Helper macro to initialize a kevent structure
    "EV_SET",

    NULL
};

// Functions declared in sys/kqueue.h (usually <sys/event.h>)
const char* sys_kqueue_h_functions[] = {
    "kqueue",           // int kqueue(void);
    "kevent",           // int kevent(int kq, const struct kevent *changelist, int nchanges,
                        //             struct kevent *eventlist, int nevents,
                        //             const struct timespec *timeout);
    NULL
};

