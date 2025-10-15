const char* arpa_nameser_h_name = "arpa/nameser.h";

const char* arpa_nameser_h_globals[] = {
    // <arpa/nameser.h> declares some global constant data and functions related to DNS message parsing,
    // including an external constant array and various helper functions,
    // but it does NOT define any modifiable global variables with external linkage.
    "_ns_flagdata",  // extern const struct _ns_flagdata[] attribute_hidden;
    NULL
};

// Types declared in arpa/nameser.h
const char* arpa_nameser_h_types[] = {
    "ns_type",          // DNS resource record type constants (e.g., T_A, T_NS)
    "ns_class",         // DNS class constants (e.g., C_IN)
    "ns_opcode",        // DNS opcode values (e.g., QUERY, IQUERY)
    "ns_rcode",         // DNS response codes (e.g., NOERROR, NXDOMAIN)
    "struct ns_msg",    // opaque DNS message handle (used with parser functions)
    "struct ns_rr",     // DNS resource record structure used in parsing
    NULL
};

// Macros declared in arpa/nameser.h
const char* arpa_nameser_h_macros[] = {
    // DNS protocol constants
    "NS_MAXDNAME",      // maximum domain name length (usually 255)
    "NS_MAXLABEL",      // maximum length of a DNS label (63)
    "NS_HFIXEDSZ",      // size of DNS header (12 bytes)
    "NS_QFIXEDSZ",      // size of DNS question fixed part (4 bytes)
    "NS_RRFIXEDSZ",     // size of DNS resource record fixed part (10 bytes)
    "NS_INT32SZ",       // size of a 32-bit integer (4 bytes)
    "NS_INT16SZ",       // size of a 16-bit integer (2 bytes)
    "NS_INT8SZ",        // size of an 8-bit integer (1 byte)

    // DNS resource record types (T_*)
    "T_A",              // IPv4 address record
    "T_NS",             // authoritative name server
    "T_CNAME",          // canonical name for an alias
    "T_SOA",            // start of authority zone
    "T_PTR",            // domain name pointer
    "T_MX",             // mail exchange
    "T_TXT",            // text strings
    "T_AAAA",           // IPv6 address record
    "T_SRV",            // service locator
    "T_ANY",            // wildcard match any type

    // DNS classes (C_*)
    "C_IN",             // Internet
    "C_CH",             // Chaos
    "C_HS",             // Hesiod

    // DNS opcodes (QUERY, IQUERY, STATUS, etc.)
    "QUERY",
    "IQUERY",
    "STATUS",

    // DNS response codes (NOERROR, FORMERR, SERVFAIL, NXDOMAIN, etc.)
    "NOERROR",
    "FORMERR",
    "SERVFAIL",
    "NXDOMAIN",
    "NOTIMP",
    "REFUSED",

    NULL
};

// Functions declared in arpa/nameser.h
const char* arpa_nameser_h_functions[] = {
    // Functions to parse and manipulate DNS messages (typically declared in <resolv.h> but related)
    "ns_initparse",        // int ns_initparse(const unsigned char *msg, int msglen, ns_msg *handle);
    "ns_parserr",          // int ns_parserr(const ns_msg *handle, ns_sect section, int rrnum, ns_rr *rr);
    "ns_sprintrr",         // int ns_sprintrr(const ns_msg *handle, const ns_rr *rr, char *buf, size_t buflen);
    "ns_name_unpack",      // int ns_name_unpack(const unsigned char *msg, const unsigned char *eom, const unsigned char *src, char *dst, size_t dstsiz);
    "ns_name_pack",        // int ns_name_pack(const char *src, unsigned char *dst, int dstsiz, unsigned char **dnptrs, unsigned char **lastdnptr);
    "ns_name_pton",        // int ns_name_pton(const char *src, unsigned char *dst, int dstsiz);
    "ns_name_ntop",        // int ns_name_ntop(const unsigned char *src, char *dst, size_t size);
    NULL
};

