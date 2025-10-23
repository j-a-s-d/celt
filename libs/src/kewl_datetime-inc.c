/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_datetime-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

char* get_formatted_date_time(const char* fmt) {
    time_t now = time(NULL);
    if (now == (time_t)-1) return NULL; // time() error
    struct tm local;
#ifdef __posix01
    if (localtime_r(&now, &local) == NULL) return NULL; // POSIX thread-safe
#else
    struct tm* tmp = localtime(&now); // Non-thread-safe fallback
    if (tmp == NULL) return NULL;
    local = *tmp;
#endif
    char h[64]; // Large enough for most date/time strings
    if (strftime(h, sizeof(h), fmt, &local) == 0) return NULL;
    char* buffer = ce_malloc(strlen(h) + 1);
    if (buffer) strcpy(buffer, h);
    return buffer;
}

char* get_time_converter_stamp(const time_converter_fn tc) {
    if (tc == NULL) return NULL;
    struct timeval tv;
    struct tm* tm_info;
    gettimeofday(&tv, NULL);
    tm_info = tc(&tv.tv_sec);
    if (tm_info == NULL) return NULL;
    char* timestamp = ce_malloc(32);
    if (timestamp == NULL) return NULL;
    size_t len = strftime(timestamp, 32, "%Y-%m-%dT%H:%M:%S", tm_info);
    if (len == 0) {
        ce_free(timestamp);
        return NULL;
    }
    int millis = tv.tv_usec / 1000;
    snprintf(timestamp + len, 32 - len, ".%03dZ", millis);
    return timestamp;
}

char* time_to_iso8601(time_t raw_time) {
    struct tm local_tm;
#ifdef __posix01
    if (localtime_r(&raw_time, &local_tm) == NULL) return NULL; // POSIX thread-safe
#else
    struct tm* tmp = localtime(&raw_time); // Non-thread-safe fallback
    if (tmp == NULL) return NULL;
    local_tm = *tmp;
#endif
    char* buffer = ce_malloc(40);
    if (buffer == NULL) return NULL;
    // Format: YYYY-MM-DDTHH:MM:SS±hhmm (ISO 8601)
    strftime(buffer, 40, "%Y-%m-%dT%H:%M:%S%z", &local_tm);
    return buffer;
}

elapsed_time_t get_elapsed_time(time_t start, time_t end) {
    elapsed_time_t elapsed = DEFAULT_ELAPSED_TIME;
    double diff = difftime(end, start);
    if (diff < 0) return elapsed;
    int total_seconds = (int)diff;
    elapsed.weeks = total_seconds / (7 * 24 * 3600);
    total_seconds %= (7 * 24 * 3600);
    elapsed.days = total_seconds / (24 * 3600);
    total_seconds %= (24 * 3600);
    elapsed.hours = total_seconds / 3600;
    total_seconds %= 3600;
    elapsed.minutes = total_seconds / 60;
    elapsed.seconds = total_seconds % 60;
    return elapsed;
}

static inline int round_(double num) {
    return (int)(num < 0 ? num - 0.5 : num + 0.5);
}

void decimal_hours_to_hms(double decimal_hours, int result[3]) {
    int total_seconds = round_(decimal_hours * 3600);
    result[0] = total_seconds / 3600;
    result[1] = (total_seconds % 3600) / 60;
    result[2] = total_seconds % 60;
}

