const char* net_if_arp_h_name = "net/if_arp.h";

const char* net_if_arp_h_globals[] = {
    // <net/if_arp.h> defines structures and constants related to the Address Resolution Protocol (ARP),
    // but it does NOT define any modifiable global variables with external linkage.
    NULL
};

// Types declared in net/if_arp.h
const char* net_if_arp_h_types[] = {
    "struct arphdr",    // ARP packet header structure with members:
                        // uint16_t ar_hrd;    // Format of hardware address
                        // uint16_t ar_pro;    // Format of protocol address
                        // uint8_t  ar_hln;    // Length of hardware address
                        // uint8_t  ar_pln;    // Length of protocol address
                        // uint16_t ar_op;     // ARP operation (opcode)
    "struct arpd_request", // Structure used by ARP daemon requests
    NULL
};

// Macros declared in net/if_arp.h
const char* net_if_arp_h_macros[] = {
    // Hardware address format types (ar_hrd)
    "ARPHRD_NETROM",    // 0: NET/ROM pseudo
    "ARPHRD_ETHER",     // 1: Ethernet 10Mbps
    "ARPHRD_EETHER",    // 2: Experimental Ethernet
    "ARPHRD_AX25",      // 3: AX.25 Level 2
    "ARPHRD_PRONET",    // 4: PROnet token ring
    "ARPHRD_CHAOS",     // 5: Chaosnet
    "ARPHRD_IEEE802",   // 6: IEEE 802.2 Ethernet/TR/TB
    "ARPHRD_ARCNET",    // 7: ARCnet
    "ARPHRD_APPLETLK",  // 8: AppleTalk
    "ARPHRD_DLCI",      // 15: Frame Relay DLCI
    "ARPHRD_ATM",       // 19: ATM
    "ARPHRD_METRICOM",  // 23: Metricom
    "ARPHRD_IEEE1394",  // 24: IEEE 1394 IPv4 - RFC 2734
    "ARPHRD_INFINIBAND",// 32: InfiniBand
    // ARP protocol opcodes (ar_op)
    "ARPOP_REQUEST",    // 1: ARP request
    "ARPOP_REPLY",      // 2: ARP reply
    "ARPOP_RREQUEST",   // 3: RARP request
    "ARPOP_RREPLY",     // 4: RARP reply
    "ARPOP_InREQUEST",  // 8: InARP request
    "ARPOP_InREPLY",    // 9: InARP reply
    "ARPOP_NAK",        // 10: (ATM)ARP NAK
    // ARP entry flags
    "ATF_COM",          // Completed entry
    "ATF_PERM",         // Permanent entry
    "ATF_PUBL",         // Publish entry
    "ATF_USETRAILERS",  // Has requested trailers
    "ATF_NETMASK",      // Want to use a netmask (proxy ARP)
    "ATF_DONTPUB",      // Don't answer this address
    "ATF_MAGIC",        // Automatically added entry
    // ARP daemon request types
    "ARPD_UPDATE",      // 1: Update request
    "ARPD_LOOKUP",      // 2: Lookup request
    "ARPD_FLUSH",       // 3: Flush request
    NULL
};

// Functions declared in net/if_arp.h
const char* net_if_arp_h_functions[] = {
    // Typically, no standard functions declared in <net/if_arp.h>
    // ARP-related functions are usually implemented in kernel or user-space daemons
    NULL
};

