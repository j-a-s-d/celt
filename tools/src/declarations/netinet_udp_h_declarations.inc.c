const char* netinet_udp_h_name = "netinet/udp.h";

const char* netinet_udp_h_globals[] = {
    // <netinet/udp.h> defines the UDP header structure and related constants,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in netinet/udp.h
const char* netinet_udp_h_types[] = {
    "struct udphdr",    // UDP header structure with members:
                        // u_short uh_sport;  // source port
                        // u_short uh_dport;  // destination port
                        // u_short uh_ulen;   // UDP length
                        // u_short uh_sum;    // UDP checksum
    NULL
};

// Macros declared in netinet/udp.h
const char* netinet_udp_h_macros[] = {
    "UDP_ENCAP",                // User-settable option for UDP encapsulation
    "UDP_ENCAP_ESPINUDP_NON_IKE", // Encapsulation type: ESP in UDP (non-IKE)
    "UDP_ENCAP_ESPINUDP",       // Encapsulation type: ESP in UDP (IKE)
    "UDP_ENCAP_ESPINUDP_PORT",  // Default port for ESP in UDP encapsulation (usually 500)
    "UDP_ENCAP_ESPINUDP_MAXFRAGLEN", // Maximum UDP fragment size for ESP over UDP
    NULL
};

// Functions declared in netinet/udp.h
const char* netinet_udp_h_functions[] = {
    // Typically no functions declared directly in <netinet/udp.h>
    // UDP socket functions are provided by socket API in <sys/socket.h>
    NULL
};

