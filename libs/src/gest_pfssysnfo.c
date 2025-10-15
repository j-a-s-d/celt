/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: GeST PFSSYSNFO
 * File: gest_pfssysnfo.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "gest_pfssysnfo.h"

#include <stdio.h>
#include <dirent.h>

// FILES

int count_open_files(pid_t pid) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/fd", pid);
    DIR* dir = opendir(path);
    if (dir == NULL) return -1; // error opening directory
    int count = 0;
    struct dirent* entry;
    while (assigned(entry = readdir(dir)))
        if (entry->d_name[0] != '.') // skip "." and ".." entries
            count++;
    closedir(dir);
    return count;
}

// MEMORY

pfs_memory_info_dt get_memory_info(void) {
    pfs_memory_info_dt memory_info = {0, 0, 0, 0.0f, 0.0f, false};
    // see https://man7.org/linux/man-pages/man5/proc_meminfo.5.html
    FILE* file = fopen("/proc/meminfo", "r");
    if (!(memory_info.error = file == NULL)) {
        char line[256];
        while (fgets(line, sizeof(line), file))
            if (strncmp(line, "MemTotal:", 9) == 0) {
                sscanf(line + 9, "%lu", &memory_info.total_memory);
            } else if (strncmp(line, "MemFree:", 8) == 0) {
                sscanf(line + 8, "%lu", &memory_info.free_memory);
            } else if (strncmp(line, "MemAvailable:", 13) == 0) {
                sscanf(line + 13, "%lu", &memory_info.available_memory);
            }
        fclose(file);
        memory_info.free_percentage = ((float)memory_info.free_memory / memory_info.total_memory) * 100;
        memory_info.available_percentage = ((float)memory_info.available_memory / memory_info.total_memory) * 100;
    }
    return memory_info;
}

// CPU

// Structure to hold CPU time statistics
typedef struct {
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
    unsigned long iowait;
    unsigned long irq;
    unsigned long softirq;
    unsigned long steal;
} cpu_stats_dt;

// Function to read CPU statistics from /proc/stat
static inline cpu_stats_dt read_cpu_stats(void) {
    cpu_stats_dt stats = {0};
    FILE* fp = fopen("/proc/stat", "r");
    if (assigned(fp)) {
        char buffer[1024];
        if (assigned(fgets(buffer, sizeof(buffer), fp)))
            sscanf(buffer, "cpu %lu %lu %lu %lu %lu %lu %lu %lu", &stats.user, &stats.nice, &stats.system, &stats.idle, &stats.iowait, &stats.irq, &stats.softirq, &stats.steal);
        fclose(fp);
    }
    return stats;
}

// Function to calculate CPU usage
static inline float calculate_cpu_usage(const cpu_stats_dt prev_stats, const cpu_stats_dt curr_stats) {
    long prev_total = prev_stats.user + prev_stats.nice + prev_stats.system + prev_stats.idle + prev_stats.iowait + prev_stats.irq + prev_stats.softirq + prev_stats.steal;
    long curr_total = curr_stats.user + curr_stats.nice + curr_stats.system + curr_stats.idle + curr_stats.iowait + curr_stats.irq + curr_stats.softirq + curr_stats.steal;
    long diff_total = curr_total - prev_total;
    long diff_idle = curr_stats.idle - prev_stats.idle;
    return diff_total == 0 ? 0 : ((100.0 * (diff_total - diff_idle)) / diff_total);
}

float get_cpu_usage(void) {
    cpu_stats_dt prev_stats = read_cpu_stats();
    sleep(1);
    cpu_stats_dt curr_stats = read_cpu_stats();
    return calculate_cpu_usage(prev_stats, curr_stats);
}

