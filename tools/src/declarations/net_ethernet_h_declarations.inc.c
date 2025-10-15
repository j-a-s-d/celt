const char* net_ethernet_h_name = "net/ethernet.h";

const char* net_ethernet_h_globals[] = {
    // <net/ethernet.h> defines Ethernet-related constants, structures, and functions,
    // but it does NOT declare or define any modifiable global variables with external linkage.
    NULL
};

// Types declared in net/ethernet.h
const char* net_ethernet_h_types[] = {
    "struct ether_addr",    // Ethernet (MAC) address: 6 bytes (ETH_ALEN)
    "struct ether_header",  // Ethernet frame header with members:
                            // u_int8_t ether_dhost[ETH_ALEN]; // Destination MAC address
                            // u_int8_t ether_shost[ETH_ALEN]; // Source MAC address
                            // u_int16_t ether_type;            // Ethernet type field (protocol ID)
    NULL
};

// Macros declared in net/ethernet.h
const char* net_ethernet_h_macros[] = {
    "ETHER_ADDR_LEN",       // Length of Ethernet address (6 bytes)
    "ETHER_TYPE_LEN",       // Length of Ethernet type field (2 bytes)
    "ETHER_CRC_LEN",        // Length of Ethernet CRC field (4 bytes)
    "ETHER_HDR_LEN",        // Total length of Ethernet header (usually 14 bytes)
    "ETHER_MIN_LEN",        // Minimum Ethernet frame length including CRC (usually 64 bytes)
    "ETHER_MAX_LEN",        // Maximum Ethernet frame length including CRC (usually 1518 bytes)
    "ETHER_IS_VALID_LEN", // Macro to check if a length is valid Ethernet frame length
    "ETHERTYPE_TRAIL",      // Trailer packet type (0x1000)
    "ETHERTYPE_NTRAILER",   // Number of trailer packets (16)
    "ETHERMTU",             // Ethernet MTU (maximum transmission unit)
    "ETHERMIN",             // Minimum Ethernet frame size excluding CRC
    NULL
};

// Functions declared in net/ethernet.h
const char* net_ethernet_h_functions[] = {
    "ether_aton",           // Convert Ethernet address string to struct ether_addr *
    "ether_aton_r",         // Reentrant version of ether_aton
    "ether_hostton",        // Convert hostname to Ethernet address
    "ether_line",           // Parse Ethernet address line
    "ether_ntoa",           // Convert struct ether_addr * to string
    "ether_ntoa_r",         // Reentrant version of ether_ntoa
    "ether_ntohost",        // Convert Ethernet address to hostname
    NULL
};

