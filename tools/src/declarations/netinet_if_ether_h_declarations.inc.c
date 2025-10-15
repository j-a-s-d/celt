const char* netinet_if_ether_h_name = "netinet/if_ether.h";

const char* netinet_if_ether_h_globals[] = {
    // <netinet/if_ether.h> defines Ethernet-related constants, macros, and structures,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in netinet/if_ether.h
const char* netinet_if_ether_h_types[] = {
    "struct ether_header",   // Ethernet frame header structure with members:
                             // uint8_t  ether_dhost[6];  // Destination MAC address
                             // uint8_t  ether_shost[6];  // Source MAC address
                             // uint16_t ether_type;      // Ethernet type field (protocol identifier)
    "struct ether_arp",      // ARP packet structure including:
                             // struct arphdr ea_hdr;    // Fixed-size ARP header
                             // uint8_t arp_sha[6];      // Sender hardware address
                             // uint8_t arp_spa[4];      // Sender protocol address (IPv4)
                             // uint8_t arp_tha[6];      // Target hardware address
                             // uint8_t arp_tpa[4];      // Target protocol address (IPv4)
    NULL
};

// Macros declared in netinet/if_ether.h
const char* netinet_if_ether_h_macros[] = {
    "ETHER_ADDR_LEN",        // Ethernet address length (6 bytes)
    "ETHER_TYPE_LEN",        // Length of Ethernet type field (2 bytes)
    "ETHER_CRC_LEN",         // Length of Ethernet CRC field (4 bytes)
    "ETHER_HDR_LEN",         // Total length of Ethernet header (usually 14 bytes)
    "ETHER_MIN_LEN",         // Minimum Ethernet frame length including CRC (64 bytes)
    "ETHER_MAX_LEN",         // Maximum Ethernet frame length including CRC (1518 bytes)
    "ETHERMTU",              // Maximum transmission unit for Ethernet (usually 1500 bytes)
    "ETHERMIN",              // Minimum payload size for Ethernet frames
    "ETHER_IS_MULTICAST", // Macro to check if an Ethernet address is multicast
    "ETHER_IS_BROADCAST", // Macro to check if an Ethernet address is broadcast
    "ETHER_IS_UNICAST",    // Macro to check if an Ethernet address is unicast
    "ETHER_MAP_IP_MULTICAST", // Macro to map an IP multicast address to Ethernet multicast address
    NULL
};

// Functions declared in netinet/if_ether.h
const char* netinet_if_ether_h_functions[] = {
    "ether_ntoa",            // Convert Ethernet address to ASCII string
    "ether_aton",            // Convert ASCII string to Ethernet address
    "ether_ntohost",         // Convert Ethernet address to hostname
    "ether_hostton",         // Convert hostname to Ethernet address
    "ether_line",            // Parse Ethernet address line
    NULL
};

