const char* resolv_h_name = "resolv.h";

const char* resolv_h_globals[] = {
    "_res",          // The global resolver state structure (of type struct __res_state)
    "resolv_event_found", // Event variable in some implementations (e.g., Contiki-NG)
    NULL
};

// Types declared in resolv.h
const char* resolv_h_types[] = {
    "res_state",        // Resolver state structure (opaque type, often __res_state)
    "resolv_status_t",  // Enumeration for DNS resolution status (Contiki-NG specific)
    NULL
};

// Macros declared in resolv.h
const char* resolv_h_macros[] = {
    "RES_INIT",         // Resolver initialized flag
    "RES_DEBUG",        // Enable debug output
    "RES_RECURSE",      // Recursion desired
    "RES_DEFNAMES",     // Use default domain name
    "RES_USEVC",        // Use virtual circuit (TCP)
    "RES_IGNTC",        // Ignore truncation errors
    "RES_AAONLY",       // Authoritative answers only (deprecated)
    // Other resolver option flags defined in standard resolv.h implementations
    NULL
};

// Functions declared in resolv.h
const char* resolv_h_functions[] = {
    "res_init",         // int res_init(void);
    "res_query",        // int res_query(const char *dname, int class, int type, unsigned char *answer, int anslen);
    "res_search",       // int res_search(const char *dname, int class, int type, unsigned char *answer, int anslen);
    "res_send",         // int res_send(const unsigned char *msg, int msglen, unsigned char *answer, int anslen);
    "dn_expand",        // int dn_expand(const unsigned char *msg, const unsigned char *eom, const unsigned char *src, char *dst, int dstsiz);
    "dn_skipname",      // int dn_skipname(const unsigned char *comp_dn, const unsigned char *eom);
    "p_query",          // int p_query(const char *dname, int class, int type, unsigned char *answer, int anslen);
    "res_mkquery",      // int res_mkquery(int op, const char *dname, int class, int type, const unsigned char *data, int datalen, const unsigned char *newrr_in, unsigned char *buf, int buflen);
    "res_send_setqhook",// void res_send_setqhook(void (*qhook)(void));
    "res_send_setrhook",// void res_send_setrhook(void (*rhook)(void));
    NULL
};

