const char* sys_socket_h_name = "sys/socket.h";

const char* sys_socket_h_globals[] = {
    // <sys/socket.h> declares socket-related structures, constants, and function prototypes,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in sys/socket.h
const char* sys_socket_h_types[] = {
    "socklen_t",          // length of a socket address
    "sa_family_t",        // address family type
    "struct sockaddr",    // generic socket address structure
    "struct sockaddr_storage", // large enough structure to hold any socket address
    "struct sockaddr_in", // IPv4 socket address structure
    "struct sockaddr_in6",// IPv6 socket address structure
    "struct sockaddr_un", // UNIX domain socket address structure
    "struct sockaddr_alg", // Linux crypto socket address (platform-specific)
    "struct linger",      // structure for SO_LINGER socket option
    "struct msghdr",      // message header for recvmsg/sendmsg
    "struct cmsghdr",     // control message header for ancillary data
    "struct osockaddr",   // compatibility generic sockaddr (rare, BSD)
    NULL
};

// Macros declared in sys/socket.h
const char* sys_socket_h_macros[] = {
    // Socket types
    "SOCK_STREAM",        // stream socket (TCP)
    "SOCK_DGRAM",         // datagram socket (UDP)
    "SOCK_RAW",           // raw socket
    "SOCK_SEQPACKET",     // sequenced packet socket

    // Address families
    "AF_INET",            // IPv4 Internet protocols
    "AF_INET6",           // IPv6 Internet protocols
    "AF_UNIX",            // UNIX domain sockets
    "AF_UNSPEC",          // unspecified

    // Socket option level
    "SOL_SOCKET",         // socket-level options

    // Socket options (option_name for getsockopt/setsockopt)
    "SO_ACCEPTCONN",      // socket is accepting connections
    "SO_BROADCAST",       // permit sending of broadcast messages
    "SO_DEBUG",           // enable debugging info recording
    "SO_DONTROUTE",       // bypass routing
    "SO_ERROR",           // get and clear error status
    "SO_KEEPALIVE",       // keep connections alive
    "SO_LINGER",          // linger on close if data present
    "SO_OOBINLINE",       // receive out-of-band data in line
    "SO_RCVBUF",          // receive buffer size
    "SO_RCVLOWAT",        // receive low-water mark
    "SO_RCVTIMEO",        // receive timeout
    "SO_REUSEADDR",       // allow reuse of local addresses
    "SO_SNDBUF",          // send buffer size
    "SO_SNDLOWAT",        // send low-water mark
    "SO_SNDTIMEO",        // send timeout
    "SO_TYPE",            // get socket type

    // Shutdown how argument for shutdown()
    "SHUT_RD",            // disallow further receptions
    "SHUT_WR",            // disallow further transmissions
    "SHUT_RDWR",          // disallow both receptions and transmissions

    // Ancillary data macros
    "CMSG_DATA",          // pointer to data portion of ancillary message
    "CMSG_FIRSTHDR",      // pointer to first ancillary message
    "CMSG_NXTHDR",        // pointer to next ancillary message
    "CMSG_LEN",           // ancillary data length including header
    "CMSG_SPACE",         // ancillary data length including padding

    NULL
};

// Functions declared in sys/socket.h
const char* sys_socket_h_functions[] = {
    "accept",        // int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    "bind",          // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    "connect",       // int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    "getpeername",   // int getpeername(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    "getsockname",   // int getsockname(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    "getsockopt",    // int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
    "listen",        // int listen(int sockfd, int backlog);
    "recv",          // ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    "recvfrom",      // ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
    "recvmsg",       // ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
    "send",          // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
    "sendmsg",       // ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
    "sendto",        // ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
    "setsockopt",    // int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
    "shutdown",      // int shutdown(int sockfd, int how);
    "sockatmark",    // int sockatmark(int sockfd);
    "socket",        // int socket(int domain, int type, int protocol);
    "socketpair",    // int socketpair(int domain, int type, int protocol, int sv[2]);
    NULL
};

