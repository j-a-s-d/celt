const char* sys_queue_h_name = "sys/queue.h";

const char* sys_queue_h_globals[] = {
    // <sys/queue.h> is a system header that defines a set of macros to implement
    // various types of data structures but it does NOT declare or define any global
    // variables with external linkage.
    NULL
};

// Types declared in sys/queue.h
const char* sys_queue_h_types[] = {
    // No traditional typedefs; this header defines macros that create data structures
    // such as singly-linked lists, doubly-linked lists, tail queues, and circular queues.
    NULL
};

// Macros declared in sys/queue.h
const char* sys_queue_h_macros[] = {
    // Singly-linked lists
    "SLIST_HEAD",       // Define head of a singly-linked list
    "SLIST_ENTRY",      // Define an entry in a singly-linked list
    "SLIST_INIT",       // Initialize a singly-linked list head
    "SLIST_INSERT_HEAD",// Insert element at head of singly-linked list
    "SLIST_INSERT_AFTER",// Insert element after a given element in singly-linked list
    "SLIST_REMOVE_HEAD",// Remove element from head of singly-linked list
    "SLIST_REMOVE",     // Remove an element from singly-linked list
    "SLIST_FOREACH",    // Iterate over singly-linked list

    // Doubly-linked lists
    "LIST_HEAD",        // Define head of a doubly-linked list
    "LIST_ENTRY",       // Define an entry in a doubly-linked list
    "LIST_INIT",        // Initialize a doubly-linked list head
    "LIST_INSERT_HEAD", // Insert element at head of doubly-linked list
    "LIST_INSERT_AFTER",// Insert element after a given element in doubly-linked list
    "LIST_INSERT_BEFORE",// Insert element before a given element in doubly-linked list
    "LIST_REMOVE",      // Remove an element from doubly-linked list
    "LIST_FOREACH",     // Iterate over doubly-linked list

    // Singly-linked tail queues
    "STAILQ_HEAD",      // Define head of a singly-linked tail queue
    "STAILQ_ENTRY",     // Define an entry in a singly-linked tail queue
    "STAILQ_INIT",      // Initialize a singly-linked tail queue head
    "STAILQ_INSERT_HEAD",// Insert element at head of singly-linked tail queue
    "STAILQ_INSERT_TAIL",// Insert element at tail of singly-linked tail queue
    "STAILQ_INSERT_AFTER",// Insert element after a given element in singly-linked tail queue
    "STAILQ_REMOVE_HEAD",// Remove element from head of singly-linked tail queue
    "STAILQ_REMOVE_AFTER",// Remove element after a given element in singly-linked tail queue
    "STAILQ_FOREACH",   // Iterate over singly-linked tail queue

    // Doubly-linked tail queues
    "TAILQ_HEAD",       // Define head of a doubly-linked tail queue
    "TAILQ_ENTRY",      // Define an entry in a doubly-linked tail queue
    "TAILQ_INIT",       // Initialize a doubly-linked tail queue head
    "TAILQ_INSERT_HEAD",// Insert element at head of doubly-linked tail queue
    "TAILQ_INSERT_TAIL",// Insert element at tail of doubly-linked tail queue
    "TAILQ_INSERT_AFTER",// Insert element after a given element in doubly-linked tail queue
    "TAILQ_INSERT_BEFORE",// Insert element before a given element in doubly-linked tail queue
    "TAILQ_REMOVE",     // Remove an element from doubly-linked tail queue
    "TAILQ_FOREACH",    // Iterate over doubly-linked tail queue

    // Circular queues
    "CIRCLEQ_HEAD",     // Define head of a circular queue
    "CIRCLEQ_ENTRY",    // Define an entry in a circular queue
    "CIRCLEQ_INIT",     // Initialize a circular queue head
    "CIRCLEQ_INSERT_HEAD",// Insert element at head of circular queue
    "CIRCLEQ_INSERT_TAIL",// Insert element at tail of circular queue
    "CIRCLEQ_INSERT_AFTER",// Insert element after a given element in circular queue
    "CIRCLEQ_INSERT_BEFORE",// Insert element before a given element in circular queue
    "CIRCLEQ_REMOVE",   // Remove an element from circular queue
    "CIRCLEQ_FOREACH",  // Iterate over circular queue

    NULL
};

// Functions declared in sys/queue.h
const char* sys_queue_h_functions[] = {
    // None; sys/queue.h defines only macros for data structure manipulation
    NULL
};

