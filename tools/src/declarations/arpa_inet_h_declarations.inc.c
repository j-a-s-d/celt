const char* arpa_inet_h_name = "arpa/inet.h";

const char* arpa_inet_h_globals[] = {
    // <arpa/inet.h> declares no global variables with external linkage,
    // only types, macros, and functions for internet address manipulation.
    NULL
};

// Types declared in arpa/inet.h
const char* arpa_inet_h_types[] = {
    NULL
};

// Macros declared in arpa/inet.h
const char* arpa_inet_h_macros[] = {
    NULL
};

// Functions declared in arpa/inet.h
const char* arpa_inet_h_functions[] = {
    // Byte order conversion functions (may be macros or functions)
    "htonl",          // uint32_t htonl(uint32_t hostlong);
    "htons",          // uint16_t htons(uint16_t hostshort);
    "ntohl",          // uint32_t ntohl(uint32_t netlong);
    "ntohs",          // uint16_t ntohs(uint16_t netshort);

    // IPv4 address conversion and manipulation
    "inet_addr",      // in_addr_t inet_addr(const char *cp);
    "inet_lnaof",     // in_addr_t inet_lnaof(struct in_addr in);
    "inet_makeaddr",  // struct in_addr inet_makeaddr(in_addr_t net, in_addr_t lna);
    "inet_netof",     // in_addr_t inet_netof(struct in_addr in);
    "inet_network",   // in_addr_t inet_network(const char *cp);
    "inet_ntoa",      // char *inet_ntoa(struct in_addr in);

    // Protocol-independent address conversion
    "inet_ntop",      // const char *inet_ntop(int af, const void *restrict src, char *restrict dst, socklen_t size);
    "inet_pton",      // int inet_pton(int af, const char *restrict src, void *restrict dst);

    NULL
};

