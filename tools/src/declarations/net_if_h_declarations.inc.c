const char* net_if_h_name = "net/if.h";

const char* net_if_h_globals[] = {
    // The <net/if.h> header defines constants, structures, and ioctl flags related to network interfaces,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in net/if.h
const char* net_if_h_types[] = {
    "struct if_nameindex",  // Structure representing network interface index and name
    NULL
};

// Macros declared in net/if.h
const char* net_if_h_macros[] = {
    "IF_NAMESIZE",          // Size of buffer for interface name including null terminator (typically 16)

    // Common interface flags (may be defined under __USE_MISC or similar feature test macros)
    "IFF_UP",               // Interface is up
    "IFF_BROADCAST",        // Broadcast address valid
    "IFF_DEBUG",            // Turn on debugging
    "IFF_LOOPBACK",         // Is a loopback interface
    "IFF_POINTOPOINT",      // Interface is point-to-point link
    "IFF_NOTRAILERS",       // Avoid use of trailers
    "IFF_RUNNING",          // Resources allocated
    "IFF_NOARP",            // No ARP protocol
    "IFF_PROMISC",          // Promiscuous mode
    "IFF_ALLMULTI",         // Receive all multicast packets
    "IFF_MULTICAST",        // Supports multicast
    NULL
};

// Functions declared in net/if.h
const char* net_if_h_functions[] = {
    "if_nameindex",         // struct if_nameindex *if_nameindex(void);
    "if_freenameindex",     // void if_freenameindex(struct if_nameindex *);
    "if_nametoindex",       // unsigned int if_nametoindex(const char *);
    "if_indextoname",       // char *if_indextoname(unsigned int, char *);
    NULL
};

