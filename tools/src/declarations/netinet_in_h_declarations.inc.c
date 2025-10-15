const char* netinet_in_h_name = "netinet/in.h";

const char* netinet_in_h_globals[] = {
    "in6addr_any",       // const struct in6_addr in6addr_any - IPv6 wildcard address
    "in6addr_loopback",  // const struct in6_addr in6addr_loopback - IPv6 loopback address
    NULL
};

// Types declared in netinet/in.h
const char* netinet_in_h_types[] = {
    "in_port_t",          // 16-bit port number type (equivalent to uint16_t)
    "in_addr_t",          // 32-bit IPv4 address type (equivalent to uint32_t)
    "struct in_addr",     // IPv4 address structure with member: in_addr_t s_addr
    "struct sockaddr_in", // IPv4 socket address structure with members:
                          // sa_family_t sin_family (AF_INET),
                          // in_port_t sin_port (port number in network byte order),
                          // struct in_addr sin_addr (IPv4 address in network byte order)
    "struct in6_addr",    // IPv6 address structure with member: uint8_t s6_addr[16]
    "struct sockaddr_in6",// IPv6 socket address structure
    "struct ipv6_mreq",   // IPv6 multicast group request structure
    "struct ip_mreq",     // IPv4 multicast group request structure
    "struct ip_mreq_source", // IPv4 multicast source filter request structure
    "struct group_req",       // generic group request structure
    "struct group_source_req",// group source request structure
    NULL
};

// Macros declared in netinet/in.h
const char* netinet_in_h_macros[] = {
    // Address families
    "AF_INET",            // IPv4 Internet protocols
    "AF_INET6",           // IPv6 Internet protocols
    // IPv4 address macros
    "INADDR_ANY",         // IPv4 wildcard address (0.0.0.0)
    "INADDR_BROADCAST",   // IPv4 broadcast address (255.255.255.255)
    "INADDR_LOOPBACK",    // IPv4 loopback address (127.0.0.1)
    "INADDR_UNSPEC_GROUP",
    "INADDR_ALLHOSTS_GROUP",
    "INADDR_ALLRTRS_GROUP",
    "INADDR_MAX_LOCAL_GROUP",
    "INADDR_NONE",        // Invalid IPv4 address (usually 255.255.255.255)
    // IPv6 address macros
    "IN6ADDR_ANY_INIT",       // IPv6 wildcard address initializer
    "IN6ADDR_LOOPBACK_INIT",  // IPv6 loopback address initializer
    // IPv6 address classification macros
    "IN6_IS_ADDR_UNSPECIFIED",
    "IN6_IS_ADDR_LOOPBACK",
    "IN6_IS_ADDR_MULTICAST",
    "IN6_IS_ADDR_LINKLOCAL",
    "IN6_IS_ADDR_SITELOCAL",
    "IN6_IS_ADDR_V4MAPPED",
    "IN6_IS_ADDR_V4COMPAT",
    "IN6_IS_ADDR_MC_NODELOCAL",
    "IN6_IS_ADDR_MC_LINKLOCAL",
    "IN6_IS_ADDR_MC_SITELOCAL",
    "IN6_IS_ADDR_MC_ORGLOCAL",
    "IN6_IS_ADDR_MC_GLOBAL",
    // Protocol levels for getsockopt()/setsockopt()
    "IPPROTO_IP",          // IPv4 protocol level
    "IPPROTO_IPV6",        // IPv6 protocol level
    "IPPROTO_ICMP",        // ICMP protocol
    "IPPROTO_TCP",         // TCP protocol
    "IPPROTO_UDP",         // UDP protocol
    "IPPROTO_RAW",         // Raw IP packets
    "IPPROTO_IGMP",
    "IPPROTO_GGP",
    "IPPROTO_PUP",
    "IPPROTO_IDP",
    "IPPROTO_ROUTING",
    "IPPROTO_FRAGMENT",
    "IPPROTO_ESP",
    "IPPROTO_AH",
    "IPPROTO_ICMPV6",
    "IPPROTO_NONE",
    "IPPROTO_DSTOPTS",
    "IPPROTO_MH",
    /* IPv4 multicast socket options */
    "IP_ADD_MEMBERSHIP",
    "IP_DROP_MEMBERSHIP",
    "IP_MULTICAST_IF",
    "IP_MULTICAST_TTL",
    "IP_MULTICAST_LOOP",
    /* Other socket options */
    "IP_TOS",
    "IP_TTL",
    "IP_HDRINCL",
    "IP_OPTIONS",
    "IP_RECVOPTS",
    "IP_RECVRETOPTS",
    "IP_RECVDSTADDR",
    "IP_RETOPTS",
    "IP_PKTINFO",
    "IP_MTU_DISCOVER",
    "IP_MTU",
    "IP_FREEBIND",
    "IP_IPSEC_POLICY",
    "IP_XFRM_POLICY",
    "IP_PASSSEC",
    "IP_TRANSPARENT",
    "IP_ORIGDSTADDR",
    "IP_MINTTL",
    "IP_NODEFRAG",
    "IP_CHECKSUM",
    "IP_BIND_ADDRESS_NO_PORT",
    "IP_UNICAST_IF",
    "IP_RECVERR",
    "IP_RECVTTL",
    "IP_RECVTOS",
    "IP_MSFILTER",
    /* Miscellaneous */
    "IP_DEFAULT_MULTICAST_TTL",
    "IP_DEFAULT_MULTICAST_LOOP",
    "IP_MAX_MEMBERSHIPS"
    /* IPv6 multicast socket options */
    "IPV6_JOIN_GROUP",
    "IPV6_LEAVE_GROUP",
    "IPV6_MULTICAST_HOPS",
    "IPV6_MULTICAST_IF",
    "IPV6_MULTICAST_LOOP",
    "IPV6_UNICAST_HOPS",
    "IPV6_V6ONLY",
    /* Multicast socket options */
    "MCAST_JOIN_GROUP",
    "MCAST_LEAVE_GROUP",
    "MCAST_BLOCK_SOURCE",
    "MCAST_UNBLOCK_SOURCE",
    "MCAST_JOIN_SOURCE_GROUP",
    "MCAST_LEAVE_SOURCE_GROUP",
    /* Buffer sizes for IP address strings */
    "INET_ADDRSTRLEN",   // length of buffer for IPv4 address string
    "INET6_ADDRSTRLEN",  // length of buffer for IPv6 address string
    NULL
};

// Functions declared in netinet/in.h
const char* netinet_in_h_functions[] = {
    // IPv6 helper functions (may be system-specific or extensions)
    "inet6_rth_space",
    "inet6_rth_init",
    "inet6_rth_add",
    "inet6_rth_reverse",
    "inet6_rth_segments",
    "inet6_rth_getaddr",
    "inet6_opt_init",
    "inet6_opt_append",
    "inet6_opt_finish",
    "inet6_opt_set_val",
    "inet6_opt_next",
    "inet6_opt_find",
    "inet6_opt_get_val",
    // Multicast source filter functions (may require feature test macros)
    "setipv4sourcefilter",
    "getipv4sourcefilter",
    "setsourcefilter",
    "getsourcefilter",
    NULL
};

