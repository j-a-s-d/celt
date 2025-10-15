/**
 * GeST PfsSysNfo: proc pseudo-filesystem system information
 */

#include "gem_testing.h"
#include "gest_pfssysnfo.h"

#ifdef GEST_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/gest_pfssysnfo_test ../src/kewl.c ../src/gest_pfssysnfo.c gest_pfssysnfo_test.c");
#endif

int main(void) {
    Tests.begin("GeST PFSSYSNFO");
    pid_t pid = getpid();
    int open_files = count_open_files(pid);
    Tests.run("count_open_files", open_files > -1);
    Tests.print("Process ID: %d\n", pid);
    Tests.print("Open Files: %d\n", open_files);
    pfs_memory_info_dt memory_info = get_memory_info();
    Tests.run("get_memory_info", memory_info.total_memory > 0);
    Tests.print("Total Memory: %lu kB\n", memory_info.total_memory);
    Tests.print("Free Memory: %lu kB (%.2f %%)\n", memory_info.free_memory, memory_info.free_percentage);
    Tests.print("Available Memory: %lu kB (%.2f %%)\n", memory_info.available_memory, memory_info.available_percentage);
    float cpu_usage = get_cpu_usage();
    Tests.run("get_cpu_usage", cpu_usage > 0.0f);
    Tests.print("CPU Usage: %.2f %%\n", cpu_usage);
    return Tests.end();
}

