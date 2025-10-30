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
    if (assigned(buffer)) strcpy(buffer, h);
    return buffer;
}

char* get_time_converter_stamp(time_converter_fn tc) {
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

elapsed_time_dt get_elapsed_time(time_t start, time_t end) {
    elapsed_time_dt elapsed = DEFAULT_ELAPSED_TIME;
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

static inline void _normalize_time(int* hours, int* minutes, int* seconds) {
    if (*seconds >= 60) {
        *minutes += *seconds / 60;
        *seconds %= 60;
    } else if (*seconds < 0) {
        int borrow = (abs(*seconds) + 59) / 60;
        *minutes -= borrow;
        *seconds += borrow * 60;
    }
    if (*minutes >= 60) {
        *hours += *minutes / 60;
        *minutes %= 60;
    } else if (*minutes < 0) {
        int borrow = (abs(*minutes) + 59) / 60;
        *hours -= borrow;
        *minutes += borrow * 60;
    }
    if (*hours >= 24) {
        *hours %= 24;
    } else if (*hours < 0)
        *hours = (*hours % 24 + 24) % 24;
}

void local_hms_to_utc(int local_hours, int local_minutes, int local_seconds, double gmt_offset, int result[3]) {
    int offset_seconds = (int)(gmt_offset * 3600);
    int local_total_seconds = local_hours * 3600 + local_minutes * 60 + local_seconds;
    int utc_total_seconds = local_total_seconds - offset_seconds;
    result[0] = utc_total_seconds / 3600;
    result[1] = (utc_total_seconds % 3600) / 60;
    result[2] = utc_total_seconds % 60;
    _normalize_time(&result[0], &result[1], &result[2]);
}

double local_hms_to_utc_decimal_hours(int local_hours, int local_minutes, int local_seconds, double gmt_offset) {
    int ut[3];
    int offset_seconds = (int)(gmt_offset * 3600);
    int local_total_seconds = local_hours * 3600 + local_minutes * 60 + local_seconds;
    int utc_total_seconds = local_total_seconds - offset_seconds;
    ut[0] = utc_total_seconds / 3600;
    ut[1] = (utc_total_seconds % 3600) / 60;
    ut[2] = utc_total_seconds % 60;
    _normalize_time(&ut[0], &ut[1], &ut[2]);
    return ut[0] + ut[1] / 60.0 + ut[2] / 3600.0; // hms_to_decimal_hours
}

bool fill_datetime_from_tm(datetime_dt* datetime, const struct tm* time_tm) {
    if (datetime == NULL || time_tm == NULL) return false;
    datetime->year = time_tm->tm_year + 1900; // tm_year is years since 1900
    datetime->month = time_tm->tm_mon + 1;    // tm_mon is months since January (0-11)
    datetime->day = time_tm->tm_mday;         // day of the month (1-31)
    datetime->hours = time_tm->tm_hour;       // hours since midnight (0-23)
    datetime->minutes = time_tm->tm_min;      // minutes after the hour (0-59)
    datetime->seconds = time_tm->tm_sec;      // seconds after the minute (0-61)
    return true;
}

datetime_dt* get_now_datetime(void) {
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
    RET_MALLOC(datetime_dt, {
        if (!fill_datetime_from_tm(result, &local)) {
            ce_free(result);
            result = NULL;
        }
    });
}

