const char* netdb_h_name = "netdb.h";

const char* netdb_h_globals[] = {
    "h_errno",      // Error status for network database operations (may be a macro or extern int)
    NULL
};

// Types declared in netdb.h
const char* netdb_h_types[] = {
    "struct hostent",   // Host entry structure
    "struct netent",    // Network entry structure
    "struct protoent",  // Protocol entry structure
    "struct servent",   // Service entry structure
    NULL
};

// Macros declared in netdb.h
const char* netdb_h_macros[] = {
    "IPPORT_RESERVED",  // Highest reserved Internet port number, usually 1023
    "HOST_NOT_FOUND",   // Authoritative answer host not found
    "NO_DATA",          // Valid name, no data record of requested type
    "NO_RECOVERY",      // Non-recoverable name server error
    "TRY_AGAIN",        // Temporary error on authoritative name server
    NULL
};

// Functions declared in netdb.h
const char* netdb_h_functions[] = {
    "endhostent",       // void endhostent(void);
    "endnetent",        // void endnetent(void);
    "endprotoent",      // void endprotoent(void);
    "endservent",       // void endservent(void);
    "gethostbyaddr",    // struct hostent *gethostbyaddr(const void *addr, size_t len, int type);
    "gethostbyname",    // struct hostent *gethostbyname(const char *name);
    "gethostent",       // struct hostent *gethostent(void);
    "getnetbyaddr",     // struct netent *getnetbyaddr(uint32_t net, int type);
    "getnetbyname",     // struct netent *getnetbyname(const char *name);
    "getnetent",        // struct netent *getnetent(void);
    "getprotobyname",   // struct protoent *getprotobyname(const char *name);
    "getprotobynumber", // struct protoent *getprotobynumber(int proto);
    "getprotoent",      // struct protoent *getprotoent(void);
    "getservbyname",    // struct servent *getservbyname(const char *name, const char *proto);
    "getservbyport",    // struct servent *getservbyport(int port, const char *proto);
    "getservent",       // struct servent *getservent(void);
    "sethostent",       // void sethostent(int stayopen);
    "setnetent",        // void setnetent(int stayopen);
    "setprotoent",      // void setprotoent(int stayopen);
    "setservent",       // void setservent(int stayopen);
    NULL
};

