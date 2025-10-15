const char* netinet_ip6_h_name = "netinet/ip6.h";

const char* netinet_ip6_h_globals[] = {
    // <netinet/ip6.h> defines IPv6 header structures and related constants,
    // but it does NOT declare or define any modifiable global variables with external linkage.
    NULL
};

// Types declared in netinet/ip6.h
const char* netinet_ip6_h_types[] = {
    "struct ip6_hdr",    // IPv6 header structure with members:
                         // union {
                         //   struct ip6_hdrctl {
                         //     uint32_t ip6_un1_flow;  // 4 bits version, 8 bits traffic class, 20 bits flow label
                         //     uint16_t ip6_un1_plen;  // Payload length
                         //     uint8_t  ip6_un1_nxt;   // Next header
                         //     uint8_t  ip6_un1_hlim;  // Hop limit
                         //   } ip6_un1;
                         //   uint8_t ip6_un2_vfc;     // 4 bits version, top 4 bits traffic class
                         // } ip6_ctlun;
                         // struct in6_addr ip6_src;  // Source IPv6 address
                         // struct in6_addr ip6_dst;  // Destination IPv6 address
    NULL
};

// Macros declared in netinet/ip6.h
const char* netinet_ip6_h_macros[] = {
    "ip6_vfc",           // Macro for version and traffic class field
    "ip6_flow",          // Macro for flow label and traffic class
    "ip6_plen",          // Macro for payload length
    "ip6_nxt",           // Macro for next header
    "ip6_hlim",          // Macro for hop limit
    NULL
};

// Functions declared in netinet/ip6.h
const char* netinet_ip6_h_functions[] = {
    // Typically no functions declared directly in <netinet/ip6.h>
    NULL
};

