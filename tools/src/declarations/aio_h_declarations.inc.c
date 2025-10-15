const char* aio_h_name = "aio.h";

const char* aio_h_globals[] = {
    // The <aio.h> header declares the aiocb structure, constants, and asynchronous I/O functions,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in aio.h
const char* aio_h_types[] = {
    "struct aiocb",     // Asynchronous I/O control block structure with members:
                       // int aio_fildes;           // File descriptor
                       // off_t aio_offset;         // File offset
                       // volatile void *aio_buf;   // Location of buffer
                       // size_t aio_nbytes;        // Length of transfer
                       // int aio_reqprio;          // Request priority offset
                       // struct sigevent aio_sigevent; // Signal for notification
                       // int aio_lio_opcode;       // Operation to be performed (for lio_listio)
    NULL
};

// Macros declared in aio.h
const char* aio_h_macros[] = {
    "AIO_ALLDONE",      // Return value indicating all requested operations are complete
    "AIO_CANCELED",     // Return value indicating all requested operations were canceled
    "AIO_NOTCANCELED",  // Return value indicating some operations could not be canceled
    "LIO_NOP",          // lio_listio() operation: no transfer requested
    "LIO_WAIT",         // lio_listio() synchronization: wait for completion
    "LIO_NOWAIT",       // lio_listio() synchronization: do not wait
    "LIO_READ",         // lio_listio() operation: read request
    "LIO_WRITE",        // lio_listio() operation: write request
    NULL
};

// Functions declared in aio.h
const char* aio_h_functions[] = {
    "aio_read",         // int aio_read(struct aiocb *);
    "aio_write",        // int aio_write(struct aiocb *);
    "aio_cancel",       // int aio_cancel(int fd, struct aiocb *);
    "aio_error",        // int aio_error(const struct aiocb *);
    "aio_return",       // ssize_t aio_return(struct aiocb *);
    "aio_suspend",      // int aio_suspend(const struct aiocb *const[], int, const struct timespec *);
    "aio_fsync",        // int aio_fsync(int op, struct aiocb *);
    "lio_listio",       // int lio_listio(int mode, struct aiocb *const[], int, struct sigevent *);
    NULL
};

