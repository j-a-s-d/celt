const char* netinet_ether_h_name = "netinet/ether.h";

const char* netinet_ether_h_globals[] = {
    // <netinet/ether.h> defines Ethernet-related constants, structures, and functions,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in netinet/ether.h
const char* netinet_ether_h_types[] = {
    "struct ether_addr",   // Ethernet (MAC) address structure:
                          // uint8_t ether_addr_octet[6];  // 6-byte hardware address
    NULL
};

// Macros declared in netinet/ether.h
const char* netinet_ether_h_macros[] = {
    NULL  // Typically no macros directly defined here; constants are usually in <net/ethernet.h> or <netinet/if_ether.h>
};

// Functions declared in netinet/ether.h
const char* netinet_ether_h_functions[] = {
    "ether_aton",          // Convert ASCII Ethernet address string to struct ether_addr *
    "ether_aton_r",        // Reentrant version of ether_aton
    "ether_ntoa",          // Convert struct ether_addr * to ASCII string
    "ether_ntoa_r",        // Reentrant version of ether_ntoa
    "ether_hostton",       // Map hostname to Ethernet address
    "ether_ntohost",       // Map Ethernet address to hostname
    "ether_line",          // Parse a line from /etc/ethers format
    NULL
};

