const char* netinet_ip_h_name = "netinet/ip.h";

const char* netinet_ip_h_globals[] = {
    // <netinet/ip.h> primarily defines structures and constants for IPv4 headers,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in netinet/ip.h
const char* netinet_ip_h_types[] = {
    "struct ip",          // IPv4 header structure with members like:
                          // uint8_t ip_hl:4;      // header length
                          // uint8_t ip_v:4;       // version
                          // uint8_t ip_tos;       // type of service
                          // uint16_t ip_len;      // total length
                          // uint16_t ip_id;       // identification
                          // uint16_t ip_off;      // fragment offset field
                          // uint8_t ip_ttl;       // time to live
                          // uint8_t ip_p;         // protocol
                          // uint16_t ip_sum;      // checksum
                          // struct in_addr ip_src;// source address
                          // struct in_addr ip_dst;// destination address
    "struct ip_timestamp",// IP timestamp option structure
    NULL
};

// Macros declared in netinet/ip.h
const char* netinet_ip_h_macros[] = {
    "IPVERSION",          // IP version number (usually 4)
    "IP_HDRINCL",         // Option to include IP header
    "IP_OPTIONS",         // IP options
    "IP_MAXPACKET",       // Maximum IP packet size (65535)
    "IP_MF",              // More fragments flag
    "IP_DF",              // Don't fragment flag
    "IP_RF",              // Reserved fragment flag
    "IP_OFFMASK",         // Mask for fragmenting bits
    "IPPROTO_IP",         // Dummy protocol for IP
    "IPPROTO_ICMP",       // ICMP protocol number
    "IPPROTO_TCP",        // TCP protocol number
    "IPPROTO_UDP",        // UDP protocol number
    "IPPROTO_RAW",        // Raw IP packets
    NULL
};

// Functions declared in netinet/ip.h
const char* netinet_ip_h_functions[] = {
    // Typically no functions declared directly in <netinet/ip.h>
    // IP-related functions are usually in other headers or libraries
    NULL
};

