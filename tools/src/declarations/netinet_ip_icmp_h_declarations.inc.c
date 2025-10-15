const char* netinet_ip_icmp_h_name = "netinet/ip_icmp.h";

const char* netinet_ip_icmp_h_globals[] = {
    // <netinet/ip_icmp.h> defines structures and constants for ICMP protocol messages,
    // but it does NOT declare or define any modifiable global variables with external linkage.
    NULL
};

// Types declared in netinet/ip_icmp.h
const char* netinet_ip_icmp_h_types[] = {
    "struct icmphdr",    // ICMP header structure with members:
                         // u_int8_t type;       // message type
                         // u_int8_t code;       // type sub-code
                         // u_int16_t checksum;  // checksum of ICMP message
                         // union {
                         //     struct {
                         //         u_int16_t id;
                         //         u_int16_t sequence;
                         //     } echo;            // echo datagram
                         //     u_int32_t gateway; // gateway address
                         //     struct {
                         //         u_int16_t __unused;
                         //         u_int16_t mtu;
                         //     } frag;            // path MTU discovery
                         // } un;
    NULL
};

// Macros declared in netinet/ip_icmp.h
const char* netinet_ip_icmp_h_macros[] = {
    "ICMP_ECHOREPLY",        // 0: Echo Reply
    "ICMP_DEST_UNREACH",     // 3: Destination Unreachable
    "ICMP_SOURCE_QUENCH",    // 4: Source Quench (Deprecated)
    "ICMP_REDIRECT",         // 5: Redirect (change route)
    "ICMP_ECHO",             // 8: Echo Request
    "ICMP_TIME_EXCEEDED",    // 11: Time Exceeded
    "ICMP_PARAMETERPROB",    // 12: Parameter Problem
    "ICMP_TIMESTAMP",        // 13: Timestamp Request
    "ICMP_TIMESTAMPREPLY",   // 14: Timestamp Reply
    "ICMP_INFO_REQUEST",     // 15: Information Request (Deprecated)
    "ICMP_INFO_REPLY",       // 16: Information Reply (Deprecated)
    "ICMP_ADDRESS",          // 17: Address Mask Request
    "ICMP_ADDRESSREPLY",     // 18: Address Mask Reply
    NULL
};

// Functions declared in netinet/ip_icmp.h
const char* netinet_ip_icmp_h_functions[] = {
    // Typically no functions declared directly in <netinet/ip_icmp.h>
    // ICMP packet handling functions are implemented in user programs or libraries
    NULL
};

