const char* sys_acl_h_name = "sys/acl.h";

const char* sys_acl_h_globals[] = {
    // The <sys/acl.h> header declares types, constants, and functions for Access Control Lists (ACLs) on POSIX systems.
    // It does NOT declare or define global variables with external linkage.
    NULL
};

// Types declared in sys/acl.h
const char* sys_acl_h_types[] = {
    "acl_t",           // Opaque type representing an Access Control List (ACL)
    "acl_entry_t",     // Opaque type representing an ACL entry
    "acl_permset_t",   // Opaque type representing a set of permissions in an ACL entry
    "acl_tag_t",       // Enumeration type for ACL entry tag types (e.g., ACL_USER, ACL_GROUP)
    "acl_perm_t",      // Enumeration type for ACL permissions (e.g., read, write, execute)
    NULL
};

// Macros declared in sys/acl.h
const char* sys_acl_h_macros[] = {
    "ACL_USER_OBJ",    // Entry tag for file owner permissions
    "ACL_USER",        // Entry tag for named user permissions
    "ACL_GROUP_OBJ",   // Entry tag for file group permissions
    "ACL_GROUP",       // Entry tag for named group permissions
    "ACL_MASK",        // Entry tag for maximum permissions mask
    "ACL_OTHER",       // Entry tag for others' permissions
    "ACL_READ",        // Permission: read
    "ACL_WRITE",       // Permission: write
    "ACL_EXECUTE",     // Permission: execute
    NULL
};

// Functions declared in sys/acl.h
const char* sys_acl_h_functions[] = {
    "acl_init",            // acl_t acl_init(int count);
    "acl_free",            // int acl_free(void *obj_p);
    "acl_dup",             // acl_t acl_dup(const acl_t acl);
    "acl_create_entry",    // int acl_create_entry(acl_t *acl_p, acl_entry_t *entry_p);
    "acl_delete_entry",    // int acl_delete_entry(acl_t acl, acl_entry_t entry_d);
    "acl_get_entry",       // int acl_get_entry(acl_t acl, int entry_id, acl_entry_t *entry_p);
    "acl_get_permset",     // int acl_get_permset(acl_entry_t entry_d, acl_permset_t *permset_p);
    "acl_set_permset",     // int acl_set_permset(acl_entry_t entry_d, acl_permset_t permset);
    "acl_add_perm",        // int acl_add_perm(acl_permset_t permset, acl_perm_t perm);
    "acl_delete_perm",     // int acl_delete_perm(acl_permset_t permset, acl_perm_t perm);
    "acl_clear_perms",     // int acl_clear_perms(acl_permset_t permset);
    "acl_get_tag_type",    // int acl_get_tag_type(acl_entry_t entry_d, acl_tag_t *tag_type_p);
    "acl_set_tag_type",    // int acl_set_tag_type(acl_entry_t entry_d, acl_tag_t tag_type);
    "acl_get_qualifier",   // void *acl_get_qualifier(acl_entry_t entry_d);
    "acl_set_qualifier",   // int acl_set_qualifier(acl_entry_t entry_d, const void *qualifier_p);
    "acl_valid",           // int acl_valid(acl_t acl);
    "acl_from_text",       // acl_t acl_from_text(const char *buf_p);
    "acl_to_text",         // char *acl_to_text(acl_t acl, ssize_t *len_p);
    "acl_get_file",        // acl_t acl_get_file(const char *path_p, acl_type_t type);
    "acl_set_file",        // int acl_set_file(const char *path_p, acl_type_t type, acl_t acl);
    "acl_delete_def_file", // int acl_delete_def_file(const char *path_p);
    "acl_get_fd",          // acl_t acl_get_fd(int fd, acl_type_t type);
    "acl_set_fd",          // int acl_set_fd(int fd, acl_type_t type, acl_t acl);
    NULL
};

