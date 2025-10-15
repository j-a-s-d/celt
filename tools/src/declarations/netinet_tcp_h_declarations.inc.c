const char* netinet_tcp_h_name = "netinet/tcp.h";

const char* netinet_tcp_h_globals[] = {
    // <netinet/tcp.h> defines the TCP header structure and related constants,
    // but it does NOT declare or define any global variables with external linkage.
    NULL
};

// Types declared in netinet/tcp.h
const char* netinet_tcp_h_types[] = {
    "tcp_seq",          // TCP sequence number type (usually uint32_t)
    "struct tcphdr",    // TCP header structure with members:
                        // u_int16_t th_sport;  // source port
                        // u_int16_t th_dport;  // destination port
                        // tcp_seq th_seq;      // sequence number
                        // tcp_seq th_ack;      // acknowledgement number
                        // u_int8_t th_off;     // data offset (header length)
                        // u_int8_t th_flags;   // control flags (TH_SYN, TH_ACK, etc.)
                        // u_int16_t th_win;    // window size
                        // u_int16_t th_sum;    // checksum
                        // u_int16_t th_urp;    // urgent pointer
    "struct tcp_info",  // (often defined in Linux) TCP connection info structure
    NULL
};

// Macros declared in netinet/tcp.h
const char* netinet_tcp_h_macros[] = {
    "TCP_NODELAY",       // Disable Nagle's algorithm (no delay)
    "TCP_MAXSEG",        // Set maximum segment size
    "TCP_CORK",          // Control sending of partial frames (Linux-specific)
    "TCP_KEEPIDLE",      // Start keepalives after this period (Linux-specific)
    "TCP_KEEPINTVL",     // Interval between keepalives (Linux-specific)
    "TCP_KEEPCNT",       // Number of keepalives before death (Linux-specific)
    "TCP_SYNCNT",        // Number of SYN retransmits (Linux-specific)
    "TH_FIN",            // TCP FIN flag (0x01)
    "TH_SYN",            // TCP SYN flag (0x02)
    "TH_RST",            // TCP RST flag (0x04)
    "TH_PUSH",           // TCP PUSH flag (0x08)
    "TH_ACK",            // TCP ACK flag (0x10)
    "TH_URG",            // TCP URG flag (0x20)
    "TCP_MD5SIG_MAXKEYLEN", // Maximum key length for TCP MD5 signature (usually 80)
    NULL
};

// Functions declared in netinet/tcp.h
const char* netinet_tcp_h_functions[] = {
    // Typically no functions declared directly in <netinet/tcp.h>
    // TCP socket options are set via setsockopt() and getsockopt()
    NULL
};

