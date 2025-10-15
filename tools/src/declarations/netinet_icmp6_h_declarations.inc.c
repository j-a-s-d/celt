const char* netinet_icmp6_h_name = "netinet/icmp6.h";

const char* netinet_icmp6_h_globals[] = {
    // <netinet/icmp6.h> defines ICMPv6 message structures, constants, and macros,
    // but it does NOT declare or define any modifiable global variables with external linkage.
    NULL
};

// Types declared in netinet/icmp6.h
const char* netinet_icmp6_h_types[] = {
    "struct icmp6_hdr",       // ICMPv6 header structure with members:
                              // uint8_t  icmp6_type;    // message type
                              // uint8_t  icmp6_code;    // message subtype
                              // uint16_t icmp6_cksum;   // checksum
                              // union {
                              //     uint32_t icmp6_un_data32;
                              //     uint16_t icmp6_un_data16;
                              //     uint8_t  icmp6_un_data8;
                              // } icmp6_dataun;         // type-specific data
    "struct nd_opt_prefix_info", // Neighbor Discovery prefix information option (RFC 4861)
    "struct nd_opt_rdnss",        // Recursive DNS Server option (RFC 6106)
    "struct nd_opt_dnssl",        // DNS Search List option (RFC 6106)
    "struct icmp6_namelookup",    // ICMPv6 name lookup message structure
    "struct icmp6_nodeinfo",      // ICMPv6 node information message structure
    NULL
};

// Macros declared in netinet/icmp6.h
const char* netinet_icmp6_h_macros[] = {
    // ICMPv6 message types (examples)
    "ND_ROUTER_SOLICIT",      // Router Solicitation (Type 133)
    "ND_ROUTER_ADVERT",       // Router Advertisement (Type 134)
    "ND_NEIGHBOR_SOLICIT",    // Neighbor Solicitation (Type 135)
    "ND_NEIGHBOR_ADVERT",     // Neighbor Advertisement (Type 136)
    "ND_REDIRECT",            // Redirect Message (Type 137)
    "ICMP6_DST_UNREACH",      // Destination Unreachable (Type 1)
    "ICMP6_PACKET_TOO_BIG",   // Packet Too Big (Type 2)
    "ICMP6_TIME_EXCEEDED",    // Time Exceeded (Type 3)
    "ICMP6_PARAM_PROB",       // Parameter Problem (Type 4)
    NULL
};

// Functions declared in netinet/icmp6.h
const char* netinet_icmp6_h_functions[] = {
    // Typically no functions declared directly in <netinet/icmp6.h>
    // ICMPv6 handling is done via raw sockets and user-space utilities
    NULL
};

