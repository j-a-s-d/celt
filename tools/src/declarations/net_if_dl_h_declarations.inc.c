const char* net_if_dl_h_name = "net/if_dl.h";

const char* net_if_dl_h_globals[] = {
    // The <net/if_dl.h> header is a BSD-specific header that defines data link layer structures,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in net/if_dl.h
const char* net_if_dl_h_types[] = {
    "struct sockaddr_dl",   // Link-level sockaddr structure with members:
                            // u_char sdl_len;         // total length of sockaddr
                            // u_char sdl_family;      // address family (AF_LINK)
                            // u_short sdl_index;      // interface index
                            // u_char sdl_type;        // interface type (e.g. IFT_ETHER)
                            // u_char sdl_nlen;        // interface name length
                            // u_char sdl_alen;        // link-level address length
                            // u_char sdl_slen;        // link-layer selector length
                            // char sdl_data[];        // interface name and link-layer address
    NULL
};

// Macros declared in net/if_dl.h
const char* net_if_dl_h_macros[] = {
    "AF_LINK",             // Address family for link-layer addresses
    "LLADDR",         // Macro to get pointer to link-layer address from sockaddr_dl pointer
    NULL
};

// Functions declared in net/if_dl.h
const char* net_if_dl_h_functions[] = {
    // Typically no functions declared in <net/if_dl.h>
    // It mainly defines structures and macros for link-layer socket addressing
    NULL
};

