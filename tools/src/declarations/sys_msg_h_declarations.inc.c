const char* sys_msg_h_name = "sys/msg.h";

const char* sys_msg_h_globals[] = {
    // <sys/msg.h> declares types, constants, structures, and functions for System V message queues,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/msg.h
const char* sys_msg_h_types[] = {
    "msgqnum_t",       // Unsigned integer type for number of messages in the queue
    "msglen_t",        // Unsigned integer type for maximum number of bytes allowed in a message
    "struct msqid_ds", // Message queue data structure
    NULL
};

// Macros declared in sys/msg.h
const char* sys_msg_h_macros[] = {
    "MSG_NOERROR",     // Flag: no error if message is too big, truncate instead
    NULL
};

// Functions declared in sys/msg.h
const char* sys_msg_h_functions[] = {
    "msgctl",          // int msgctl(int msqid, int cmd, struct msqid_ds *buf);
    "msgget",          // int msgget(key_t key, int msgflg);
    "msgrcv",          // ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
    "msgsnd",          // int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
    NULL
};

