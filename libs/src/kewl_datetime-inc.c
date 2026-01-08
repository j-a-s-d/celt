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

char* time_t_to_iso8601(time_t raw_time) {
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

void decimal_hours_to_hms(double decimal_hours, int result[3]) {
    int total_seconds = double_round(decimal_hours * 3600);
    result[0] = total_seconds / 3600;
    result[1] = (total_seconds % 3600) / 60;
    result[2] = total_seconds % 60;
}

static inline void _normalize_hms(int* hours, int* minutes, int* seconds, int* day_shift) {
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
        *day_shift = +1;
    } else if (*hours < 0) {
        *hours = (*hours % 24 + 24) % 24;
        *day_shift = -1;
    } else
        *day_shift = 0;
}

void local_hms_to_utc(int local_hours, int local_minutes, int local_seconds, double gmt_offset, int result[3], int* day_shift) {
    int offset_seconds = (int)(gmt_offset * 3600);
    int local_total_seconds = local_hours * 3600 + local_minutes * 60 + local_seconds;
    int utc_total_seconds = local_total_seconds - offset_seconds;
    result[0] = utc_total_seconds / 3600;
    result[1] = (utc_total_seconds % 3600) / 60;
    result[2] = utc_total_seconds % 60;
    _normalize_hms(&result[0], &result[1], &result[2], day_shift);
}

double local_hms_to_utc_decimal_hours(int local_hours, int local_minutes, int local_seconds, double gmt_offset, int* day_shift) {
    int ut[3];
    int offset_seconds = (int)(gmt_offset * 3600);
    int local_total_seconds = local_hours * 3600 + local_minutes * 60 + local_seconds;
    int utc_total_seconds = local_total_seconds - offset_seconds;
    ut[0] = utc_total_seconds / 3600;
    ut[1] = (utc_total_seconds % 3600) / 60;
    ut[2] = utc_total_seconds % 60;
    _normalize_hms(&ut[0], &ut[1], &ut[2], day_shift);
    return ut[0] + ut[1] / 60.0 + ut[2] / 3600.0; // hms_to_decimal_hours
}

void utc_decimal_hours_to_local_hms(double utc_decimal_hour, double gmt_offset, int result[3], int* day_shift) {
    double local_time = utc_decimal_hour + gmt_offset;
    result[0] = (int)local_time;
    double fractional_hour = local_time - result[0];
    double total_minutes = fractional_hour * 60.0;
    result[1] = (int)total_minutes;
    double fractional_minute = total_minutes - result[1];
    result[2] = (int)double_round(fractional_minute * 60.0);
    _normalize_hms(&result[0], &result[1], &result[2], day_shift);
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

bool fill_datetime_with_now(datetime_dt* dt) {
    time_t now = time(NULL);
    if (now == (time_t)-1) return false; // time() error
    struct tm local;
#ifdef __posix01
    if (localtime_r(&now, &local) == NULL) return false; // POSIX thread-safe
#else
    struct tm* tmp = localtime(&now); // Non-thread-safe fallback
    if (tmp == NULL) return false;
    local = *tmp;
#endif
    return fill_datetime_from_tm(dt, &local);
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

int get_days_in_month(int year, int month) {
    if (month < 1 || month > 12)
        return -1;
    else if (month == 2)
        return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28; // is_leap_year
    else
        return (month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31;
}

bool modify_datetime(datetime_dt* dt, int years, int months, int days, int hours, int minutes, int seconds) {
    if (dt == NULL) return false;
    dt->seconds += seconds;
    while (dt->seconds >= 60) {
        dt->seconds -= 60;
        dt->minutes++;
    }
    while (dt->seconds < 0) {
        dt->seconds += 60;
        dt->minutes--;
    }
    dt->minutes += minutes;
    while (dt->minutes >= 60) {
        dt->minutes -= 60;
        dt->hours++;
    }
    while (dt->minutes < 0) {
        dt->minutes += 60;
        dt->hours--;
    }
    dt->hours += hours;
    while (dt->hours >= 24) {
        dt->hours -= 24;
        dt->day++;
    }
    while (dt->hours < 0) {
        dt->hours += 24;
        dt->day--;
    }
    dt->day += days;
    while (dt->day > get_days_in_month(dt->year, dt->month)) {
        dt->day -= get_days_in_month(dt->year, dt->month);
        dt->month++;
        if (dt->month > 12) {
            dt->month = 1;
            dt->year++;
        }
    }
    while (dt->day < 1) {
        dt->month--;
        if (dt->month < 1) {
            dt->month = 12;
            dt->year--;
        }
        dt->day += get_days_in_month(dt->year, dt->month);
    }
    dt->month += months;
    while (dt->month > 12) {
        dt->month -= 12;
        dt->year++;
    }
    while (dt->month < 1) {
        dt->month += 12;
        dt->year--;
    }
    dt->year += years;
    // NOTE: a direct month roll can overflow days in the month so a clamp is required
    if (dt->day > get_days_in_month(dt->year, dt->month))
        dt->day = get_days_in_month(dt->year, dt->month);
    return true;
}

bool is_newer_datetime(datetime_dt* dt1, datetime_dt* dt2) {
    if (both_assigned(dt1, dt2)) {
        if (dt2->year > dt1->year) return true;
        if (dt2->year < dt1->year) return false;
        if (dt2->month > dt1->month) return true;
        if (dt2->month < dt1->month) return false;
        if (dt2->day > dt1->day) return true;
        if (dt2->day < dt1->day) return false;
        if (dt2->hours > dt1->hours) return true;
        if (dt2->hours < dt1->hours) return false;
        if (dt2->minutes > dt1->minutes) return true;
        if (dt2->minutes < dt1->minutes) return false;
        if (dt2->seconds > dt1->seconds) return true;
    }
    return false;
}

time_t datetime_to_time_t(datetime_dt* dt) {
    struct tm tm_time = {0};
    tm_time.tm_year = dt->year - 1900;
    tm_time.tm_mon = dt->month - 1;
    tm_time.tm_mday = dt->day;
    tm_time.tm_hour = dt->hours;
    tm_time.tm_min = dt->minutes;
    tm_time.tm_sec = dt->seconds;
    return mktime(&tm_time);
}

elapsed_time_dt get_datetime_elapsed_time(datetime_dt* start, datetime_dt* end) {
    if (both_assigned(start, end)) {
        time_t tstart = datetime_to_time_t(start);
        time_t tend = datetime_to_time_t(end);
        return get_elapsed_time(tstart, tend);
    }
    return DEFAULT_ELAPSED_TIME;
}

long get_days_between_time_t(time_t t1, time_t t2) {
    double seconds = difftime(t2, t1);
    return labs((long)double_round(seconds / (24 * 60 * 60)));
}

long get_days_between_ymd(int y1, int m1, int d1, int y2, int m2, int d2) {
    // initialize structs tm (months are 0-11, years are years since 1900)
    struct tm date1 = {0};
    date1.tm_year = y1 - 1900;
    date1.tm_mon = m1 - 1;
    date1.tm_mday = d1;
    struct tm date2 = {0};
    date2.tm_year = y2 - 1900;
    date2.tm_mon = m2 - 1;
    date2.tm_mday = d2;
    // convert to time_t
    time_t t1 = mktime(&date1);
    time_t t2 = mktime(&date2);
    return t1 == -1 || t2 == -1 ? -1 : get_days_between_time_t(t1, t2);
}

long get_days_between_datetime(datetime_dt* start, datetime_dt* end) {
    if (both_assigned(start, end)) {
        time_t tstart = datetime_to_time_t(start);
        time_t tend = datetime_to_time_t(end);
        return get_days_between_time_t(tstart, tend);
    }
    return -1;
}

char validate_ddmmyyyy_date_string_format(const char* text) {
    char result = CHARS_NULL;
    if (assigned(text) && strlen(text) == 10) {
        char tmp = text[2];
        if (tmp == text[5]) {
            if (isdigit(text[0]) && isdigit(text[1]) &&
                isdigit(text[3]) && isdigit(text[4]) &&
                isdigit(text[6]) && isdigit(text[7]) &&
                isdigit(text[8]) && isdigit(text[9]))
                result = tmp;
        }
    }
    return result;
}

char validate_yyyymmdd_date_string_format(const char* text) {
    char result = CHARS_NULL;
    if (assigned(text) && strlen(text) == 10) {
        char tmp = text[4];
        if (tmp == text[7]) {
            if (isdigit(text[0]) && isdigit(text[1]) &&
                isdigit(text[2]) && isdigit(text[3]) &&
                isdigit(text[5]) && isdigit(text[6]) &&
                isdigit(text[8]) && isdigit(text[9]))
                result = tmp;
        }
    }
    return result;
}

