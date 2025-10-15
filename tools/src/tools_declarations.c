/**
 * C eXTRA LiBRARiES & TOOLS
 * (c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "../include/tools_declarations.h"
#include "../include/tools_utilities.h"

// define names
#define aio_h "aio.h"
#define alloca_h "alloca.h"
#define argp_h "argp.h"
#define arpa_inet_h "arpa/inet.h"
#define arpa_nameser_h "arpa/nameser.h"
#define assert_h "assert.h"
#define atomic_h "atomic.h"
#define byteswap_h "byteswap.h"
#define complex_h "complex.h"
#define ctype_h "ctype.h"
#define dirent_h "dirent.h"
#define dlfcn_h "dlfcn.h"
#define errno_h "errno.h"
#define fcntl_h "fcntl.h"
#define features_h "features.h"
#define fenv_h "fenv.h"
#define float_h "float.h"
#define ftw_h "ftw.h"
#define getopt_h "getopt.h"
#define glob_h "glob.h"
#define gnu_ctype_h "ctype.h"
#define gnu_libc_lock_h "libc-lock.h"
#define gnu_libc_version_h "gnu/libc-version.h"
#define gnu_lib_names_h "gnu/lib-names.h"
#define gnu_mcount_h "gnu-mcount.h"
#define gnu_prefetch_h "prefetch.h"
#define gnu_pthread_h "pthread.h"
#define gnu_stdio_h "stdio.h"
#define gnu_versions_h "gnu-versions.h"
#define inttypes_h "inttypes.h"
#define iso646_h "iso646.h"
#define limits_h "limits.h"
#define locale_h "locale.h"
#define malloc_h "malloc.h"
#define math_h "math.h"
#define monetary_h "monetary.h"
#define netdb_h "netdb.h"
#define net_ethernet_h "net/ethernet.h"
#define net_if_arp_h "net/if_arp.h"
#define net_if_dl_h "net/if_dl.h"
#define net_if_h "net/if.h"
#define netinet_ether_h "netinet/ether.h"
#define netinet_icmp6_h "netinet/icmp6.h"
#define netinet_if_ether_h "netinet/if_ether.h"
#define netinet_in_h "netinet/in.h"
#define netinet_in_systm_h "netinet/in_systm.h"
#define netinet_ip6_h "netinet/ip6.h"
#define netinet_ip_h "netinet/ip.h"
#define netinet_ip_icmp_h "netinet/ip_icmp.h"
#define netinet_tcp_h "netinet/tcp.h"
#define netinet_udp_h "netinet/udp.h"
#define obstack_h "obstack.h"
#define poll_h "poll.h"
#define pthread_h "pthread.h"
#define pthread_np_h "pthread_np.h"
#define regex_h "regex.h"
#define resolv_h "resolv.h"
#define sched_h "sched.h"
#define search_h "search.h"
#define setjmp_h "setjmp.h"
#define signal_h "signal.h"
#define spawn_h "spawn.h"
#define stdalign_h "stdalign.h"
#define stdarg_h "stdarg.h"
#define stdatomic_h "stdatomic.h"
#define stdbit_h "stdbit.h"
#define stdbool_h "stdbool.h"
#define stdckdint_h "stdckdint.h"
#define stddef_h "stddef.h"
#define stdint_h "stdint.h"
#define stdio_h "stdio.h"
#define stdlib_h "stdlib.h"
#define stdnoreturn_h "stdnoreturn.h"
#define string_h "string.h"
#define strings_h "strings.h"
#define sys_acl_h "sys/acl.h"
#define sys_auxv_h "sys/auxv.h"
#define sys_capability_h "sys/capability.h"
#define sys_cdefs_h "sys/cdefs.h"
#define sys_conf_h "sys/conf.h"
#define sys_epoll_h "sys/epoll.h"
#define sys_eventfd_h "sys/eventfd.h"
#define sys_event_h "sys/event.h"
#define sys_fcntl_h "sys/fcntl.h"
#define sys_filio_h "sys/filio.h"
#define sys_inotify_h "sys/inotify.h"
#define sys_ioccom_h "sys/ioccom.h"
#define sys_ioctl_h "sys/ioctl.h"
#define sys_ipc_h "sys/ipc.h"
#define sys_kqueue_h "sys/kqueue.h"
#define syslog_h "syslog.h"
#define sys_mman_h "sys/mman.h"
#define sys_mount_h "sys/mount.h"
#define sys_msg_h "sys/msg.h"
#define sys_param_h "sys/param.h"
#define sys_queue_h "sys/queue.h"
#define sys_resource_h "sys/resource.h"
#define sys_select_h "sys/select.h"
#define sys_sem_h "sys/sem.h"
#define sys_sendfile_h "sys/sendfile.h"
#define sys_shm_h "sys/shm.h"
#define sys_signalfd_h "sys/signalfd.h"
#define sys_socket_h "sys/socket.h"
#define sys_stat_h "sys/stat.h"
#define sys_statvfs_h "sys/statvfs.h"
#define sys_syscall_h "sys/syscall.h"
#define sys_sysctl_h "sys/sysctl.h"
#define sys_sysinfo_h "sys/sysinfo.h"
#define sys_syslog_h "sys/syslog.h"
#define sys_termio_h "sys/termio.h"
#define sys_timeb_h "sys/timeb.h"
#define sys_time_h "sys/time.h"
#define sys_timerfd_h "sys/timerfd.h"
#define sys_ttycom_h "sys/ttycom.h"
#define sys_types_h "sys/types.h"
#define sys_ucontext_h "sys/ucontext.h"
#define sys_uio_h "sys/uio.h"
#define sys_un_h "sys/un.h"
#define sys_utsname_h "sys/utsname.h"
#define sys_vfs_h "sys/vfs.h"
#define sys_wait_h "sys/wait.h"
#define termios_h "termios.h"
#define tgmath_h "tgmath.h"
#define threads_h "threads.h"
#define time_h "time.h"
#define uchar_h "uchar.h"
#define ucontext_h "ucontext.h"
#define unistd_h "unistd.h"
#define utime_h "utime.h"
#define utmp_h "utmp.h"
#define utmpx_h "utmpx.h"
#define wchar_h "wchar.h"
#define wctype_h "wctype.h"
#define wordexp_h "wordexp.h"

// include files
#include "./declarations/aio_h_declarations.inc.c"
#include "./declarations/alloca_h_declarations.inc.c"
#include "./declarations/argp_h_declarations.inc.c"
#include "./declarations/arpa_inet_h_declarations.inc.c"
#include "./declarations/arpa_nameser_h_declarations.inc.c"
#include "./declarations/assert_h_declarations.inc.c"
#include "./declarations/atomic_h_declarations.inc.c"
#include "./declarations/byteswap_h_declarations.inc.c"
#include "./declarations/complex_h_declarations.inc.c"
#include "./declarations/ctype_h_declarations.inc.c"
#include "./declarations/dirent_h_declarations.inc.c"
#include "./declarations/dlfcn_h_declarations.inc.c"
#include "./declarations/errno_h_declarations.inc.c"
#include "./declarations/fcntl_h_declarations.inc.c"
#include "./declarations/features_h_declarations.inc.c"
#include "./declarations/fenv_h_declarations.inc.c"
#include "./declarations/float_h_declarations.inc.c"
#include "./declarations/ftw_h_declarations.inc.c"
#include "./declarations/getopt_h_declarations.inc.c"
#include "./declarations/glob_h_declarations.inc.c"
#include "./declarations/gnu_ctype_h_declarations.inc.c"
#include "./declarations/gnu_libc_lock_h_declarations.inc.c"
#include "./declarations/gnu_libc_version_h_declarations.inc.c"
#include "./declarations/gnu_lib_names_h_declarations.inc.c"
#include "./declarations/gnu_mcount_h_declarations.inc.c"
#include "./declarations/gnu_prefetch_h_declarations.inc.c"
#include "./declarations/gnu_pthread_h_declarations.inc.c"
#include "./declarations/gnu_stdio_h_declarations.inc.c"
#include "./declarations/gnu_versions_h_declarations.inc.c"
#include "./declarations/inttypes_h_declarations.inc.c"
#include "./declarations/iso646_h_declarations.inc.c"
#include "./declarations/limits_h_declarations.inc.c"
#include "./declarations/locale_h_declarations.inc.c"
#include "./declarations/malloc_h_declarations.inc.c"
#include "./declarations/math_h_declarations.inc.c"
#include "./declarations/monetary_h_declarations.inc.c"
#include "./declarations/netdb_h_declarations.inc.c"
#include "./declarations/net_ethernet_h_declarations.inc.c"
#include "./declarations/net_if_arp_h_declarations.inc.c"
#include "./declarations/net_if_dl_h_declarations.inc.c"
#include "./declarations/net_if_h_declarations.inc.c"
#include "./declarations/netinet_ether_h_declarations.inc.c"
#include "./declarations/netinet_icmp6_h_declarations.inc.c"
#include "./declarations/netinet_if_ether_h_declarations.inc.c"
#include "./declarations/netinet_in_h_declarations.inc.c"
#include "./declarations/netinet_in_systm_h_declarations.inc.c"
#include "./declarations/netinet_ip6_h_declarations.inc.c"
#include "./declarations/netinet_ip_h_declarations.inc.c"
#include "./declarations/netinet_ip_icmp_h_declarations.inc.c"
#include "./declarations/netinet_tcp_h_declarations.inc.c"
#include "./declarations/netinet_udp_h_declarations.inc.c"
#include "./declarations/obstack_h_declarations.inc.c"
#include "./declarations/poll_h_declarations.inc.c"
#include "./declarations/pthread_h_declarations.inc.c"
#include "./declarations/pthread_np_h_declarations.inc.c"
#include "./declarations/regex_h_declarations.inc.c"
#include "./declarations/resolv_h_declarations.inc.c"
#include "./declarations/sched_h_declarations.inc.c"
#include "./declarations/search_h_declarations.inc.c"
#include "./declarations/setjmp_h_declarations.inc.c"
#include "./declarations/signal_h_declarations.inc.c"
#include "./declarations/spawn_h_declarations.inc.c"
#include "./declarations/stdalign_h_declarations.inc.c"
#include "./declarations/stdarg_h_declarations.inc.c"
#include "./declarations/stdatomic_h_declarations.inc.c"
#include "./declarations/stdbit_h_declarations.inc.c"
#include "./declarations/stdbool_h_declarations.inc.c"
#include "./declarations/stdckdint_h_declarations.inc.c"
#include "./declarations/stddef_h_declarations.inc.c"
#include "./declarations/stdint_h_declarations.inc.c"
#include "./declarations/stdio_h_declarations.inc.c"
#include "./declarations/stdlib_h_declarations.inc.c"
#include "./declarations/stdnoreturn_h_declarations.inc.c"
#include "./declarations/string_h_declarations.inc.c"
#include "./declarations/strings_h_declarations.inc.c"
#include "./declarations/sys_acl_h_declarations.inc.c"
#include "./declarations/sys_auxv_h_declarations.inc.c"
#include "./declarations/sys_capability_h_declarations.inc.c"
#include "./declarations/sys_cdefs_h_declarations.inc.c"
#include "./declarations/sys_conf_h_declarations.inc.c"
#include "./declarations/sys_epoll_h_declarations.inc.c"
#include "./declarations/sys_eventfd_h_declarations.inc.c"
#include "./declarations/sys_event_h_declarations.inc.c"
#include "./declarations/sys_fcntl_h_declarations.inc.c"
#include "./declarations/sys_filio_h_declarations.inc.c"
#include "./declarations/sys_inotify_h_declarations.inc.c"
#include "./declarations/sys_ioccom_h_declarations.inc.c"
#include "./declarations/sys_ioctl_h_declarations.inc.c"
#include "./declarations/sys_ipc_h_declarations.inc.c"
#include "./declarations/sys_kqueue_h_declarations.inc.c"
#include "./declarations/syslog_h_declarations.inc.c"
#include "./declarations/sys_mman_h_declarations.inc.c"
#include "./declarations/sys_mount_h_declarations.inc.c"
#include "./declarations/sys_msg_h_declarations.inc.c"
#include "./declarations/sys_param_h_declarations.inc.c"
#include "./declarations/sys_queue_h_declarations.inc.c"
#include "./declarations/sys_resource_h_declarations.inc.c"
#include "./declarations/sys_select_h_declarations.inc.c"
#include "./declarations/sys_sem_h_declarations.inc.c"
#include "./declarations/sys_sendfile_h_declarations.inc.c"
#include "./declarations/sys_shm_h_declarations.inc.c"
#include "./declarations/sys_signalfd_h_declarations.inc.c"
#include "./declarations/sys_socket_h_declarations.inc.c"
#include "./declarations/sys_stat_h_declarations.inc.c"
#include "./declarations/sys_statvfs_h_declarations.inc.c"
#include "./declarations/sys_syscall_h_declarations.inc.c"
#include "./declarations/sys_sysctl_h_declarations.inc.c"
#include "./declarations/sys_sysinfo_h_declarations.inc.c"
#include "./declarations/sys_syslog_h_declarations.inc.c"
#include "./declarations/sys_termio_h_declarations.inc.c"
#include "./declarations/sys_timeb_h_declarations.inc.c"
#include "./declarations/sys_time_h_declarations.inc.c"
#include "./declarations/sys_timerfd_h_declarations.inc.c"
#include "./declarations/sys_ttycom_h_declarations.inc.c"
#include "./declarations/sys_types_h_declarations.inc.c"
#include "./declarations/sys_ucontext_h_declarations.inc.c"
#include "./declarations/sys_uio_h_declarations.inc.c"
#include "./declarations/sys_un_h_declarations.inc.c"
#include "./declarations/sys_utsname_h_declarations.inc.c"
#include "./declarations/sys_vfs_h_declarations.inc.c"
#include "./declarations/sys_wait_h_declarations.inc.c"
#include "./declarations/termios_h_declarations.inc.c"
#include "./declarations/tgmath_h_declarations.inc.c"
#include "./declarations/threads_h_declarations.inc.c"
#include "./declarations/time_h_declarations.inc.c"
#include "./declarations/uchar_h_declarations.inc.c"
#include "./declarations/ucontext_h_declarations.inc.c"
#include "./declarations/unistd_h_declarations.inc.c"
#include "./declarations/utime_h_declarations.inc.c"
#include "./declarations/utmp_h_declarations.inc.c"
#include "./declarations/utmpx_h_declarations.inc.c"
#include "./declarations/wchar_h_declarations.inc.c"
#include "./declarations/wctype_h_declarations.inc.c"
#include "./declarations/wordexp_h_declarations.inc.c"

struct file_declarations_array_dt declarations_array = {NULL, 0, 0};

int add_file_declarations(struct file_declarations_dt new_item) {
    if (declarations_array.size == declarations_array.capacity) {
        size_t new_capacity = declarations_array.capacity == 0 ? 72 : declarations_array.capacity * 2;
        struct file_declarations_dt* new_items = realloc(declarations_array.items, new_capacity * sizeof(struct file_declarations_dt));
        if (!new_items) return -1;
        declarations_array.items = new_items;
        declarations_array.capacity = new_capacity;
    }
    declarations_array.items[declarations_array.size++] = new_item;
    return 0;
}

#define ADD_FILE(X) \
    struct file_declarations_dt CONCAT(mystruct_, __LINE__) = { \
        .name = (X##_name), \
        .globals = (X##_globals), \
        .globals_len = find_first_null_index((X##_globals)),\
        .types = (X##_types), \
        .types_len = find_first_null_index((X##_types)),\
        .macros = (X##_macros), \
        .macros_len = find_first_null_index((X##_macros)),\
        .functions = (X##_functions), \
        .functions_len = find_first_null_index((X##_functions))\
    }; \
    add_file_declarations(CONCAT(mystruct_, __LINE__));

void load_declarations() {
    ADD_FILE(aio_h)
    ADD_FILE(alloca_h)
    ADD_FILE(argp_h)
    ADD_FILE(arpa_inet_h)
    ADD_FILE(arpa_nameser_h)
    ADD_FILE(assert_h)
    ADD_FILE(atomic_h)
    ADD_FILE(byteswap_h)
    ADD_FILE(complex_h)
    ADD_FILE(ctype_h)
    ADD_FILE(dirent_h)
    ADD_FILE(dlfcn_h)
    ADD_FILE(errno_h)
    ADD_FILE(fcntl_h)
    ADD_FILE(features_h)
    ADD_FILE(fenv_h)
    ADD_FILE(float_h)
    ADD_FILE(ftw_h)
    ADD_FILE(getopt_h)
    ADD_FILE(glob_h)
    ADD_FILE(gnu_ctype_h)
    ADD_FILE(gnu_libc_lock_h)
    ADD_FILE(gnu_libc_version_h)
    ADD_FILE(gnu_lib_names_h)
    ADD_FILE(gnu_mcount_h)
    ADD_FILE(gnu_prefetch_h)
    ADD_FILE(gnu_pthread_h)
    ADD_FILE(gnu_stdio_h)
    ADD_FILE(gnu_versions_h)
    ADD_FILE(inttypes_h)
    ADD_FILE(iso646_h)
    ADD_FILE(limits_h)
    ADD_FILE(locale_h)
    ADD_FILE(malloc_h)
    ADD_FILE(math_h)
    ADD_FILE(monetary_h)
    ADD_FILE(netdb_h)
    ADD_FILE(net_ethernet_h)
    ADD_FILE(net_if_arp_h)
    ADD_FILE(net_if_dl_h)
    ADD_FILE(net_if_h)
    ADD_FILE(netinet_ether_h)
    ADD_FILE(netinet_icmp6_h)
    ADD_FILE(netinet_if_ether_h)
    ADD_FILE(netinet_in_h)
    ADD_FILE(netinet_in_systm_h)
    ADD_FILE(netinet_ip6_h)
    ADD_FILE(netinet_ip_h)
    ADD_FILE(netinet_ip_icmp_h)
    ADD_FILE(netinet_tcp_h)
    ADD_FILE(netinet_udp_h)
    ADD_FILE(obstack_h)
    ADD_FILE(poll_h)
    ADD_FILE(pthread_h)
    ADD_FILE(pthread_np_h)
    ADD_FILE(regex_h)
    ADD_FILE(resolv_h)
    ADD_FILE(sched_h)
    ADD_FILE(search_h)
    ADD_FILE(setjmp_h)
    ADD_FILE(signal_h)
    ADD_FILE(spawn_h)
    ADD_FILE(stdalign_h)
    ADD_FILE(stdarg_h)
    ADD_FILE(stdatomic_h)
    ADD_FILE(stdbit_h)
    ADD_FILE(stdbool_h)
    ADD_FILE(stdckdint_h)
    ADD_FILE(stddef_h)
    ADD_FILE(stdint_h)
    ADD_FILE(stdio_h)
    ADD_FILE(stdlib_h)
    ADD_FILE(stdnoreturn_h)
    ADD_FILE(string_h)
    ADD_FILE(strings_h)
    ADD_FILE(sys_acl_h)
    ADD_FILE(sys_auxv_h)
    ADD_FILE(sys_capability_h)
    ADD_FILE(sys_cdefs_h)
    ADD_FILE(sys_conf_h)
    ADD_FILE(sys_epoll_h)
    ADD_FILE(sys_eventfd_h)
    ADD_FILE(sys_event_h)
    ADD_FILE(sys_fcntl_h)
    ADD_FILE(sys_filio_h)
    ADD_FILE(sys_inotify_h)
    ADD_FILE(sys_ioccom_h)
    ADD_FILE(sys_ioctl_h)
    ADD_FILE(sys_ipc_h)
    ADD_FILE(sys_kqueue_h)
    ADD_FILE(syslog_h)
    ADD_FILE(sys_mman_h)
    ADD_FILE(sys_mount_h)
    ADD_FILE(sys_msg_h)
    ADD_FILE(sys_param_h)
    ADD_FILE(sys_queue_h)
    ADD_FILE(sys_resource_h)
    ADD_FILE(sys_select_h)
    ADD_FILE(sys_sem_h)
    ADD_FILE(sys_sendfile_h)
    ADD_FILE(sys_shm_h)
    ADD_FILE(sys_signalfd_h)
    ADD_FILE(sys_socket_h)
    ADD_FILE(sys_stat_h)
    ADD_FILE(sys_statvfs_h)
    ADD_FILE(sys_syscall_h)
    ADD_FILE(sys_sysctl_h)
    ADD_FILE(sys_sysinfo_h)
    ADD_FILE(sys_syslog_h)
    ADD_FILE(sys_termio_h)
    ADD_FILE(sys_timeb_h)
    ADD_FILE(sys_time_h)
    ADD_FILE(sys_timerfd_h)
    ADD_FILE(sys_ttycom_h)
    ADD_FILE(sys_ucontext_h)
    ADD_FILE(sys_uio_h)
    ADD_FILE(sys_un_h)
    ADD_FILE(sys_utsname_h)
    ADD_FILE(sys_vfs_h)
    ADD_FILE(sys_wait_h)
    ADD_FILE(termios_h)
    ADD_FILE(tgmath_h)
    ADD_FILE(threads_h)
    ADD_FILE(time_h)
    ADD_FILE(uchar_h)
    ADD_FILE(ucontext_h)
    ADD_FILE(unistd_h)
    ADD_FILE(utime_h)
    ADD_FILE(utmp_h)
    ADD_FILE(utmpx_h)
    ADD_FILE(wchar_h)
    ADD_FILE(wctype_h)
    ADD_FILE(wordexp_h)
    // leave sys/types.h for last
    ADD_FILE(sys_types_h)
}

struct file_declarations_dt* find_in_declarations_array(const char* target) {
    #define find_target(arr, len) find_string_in_array(target, arr, len) != -1
    if (target) for (size_t i = 0; i < declarations_array.size; i++) {
        struct file_declarations_dt* item = &declarations_array.items[i];
        if (find_target(item->globals, item->globals_len) ||
            find_target(item->types, item->types_len) ||
            find_target(item->macros, item->macros_len) ||
            find_target(item->functions, item->functions_len)) {
            return item;
        }
    }
    return NULL;
    #undef find_target
}

struct file_declarations_dt* get_file_declarations(const char* filename) {
    if (filename) for (size_t i = 0; i < declarations_array.size; i++) {
        struct file_declarations_dt* item = &declarations_array.items[i];
        if (strcmp(item->name, filename) == 0) return item;
    }
    return NULL;
}

void unload_declarations() {
    if (declarations_array.items != NULL) {
        free(declarations_array.items);
        declarations_array.items = NULL;
    }
}

