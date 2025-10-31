/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_datetime-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

#include <time.h> /* timespec and clock_gettime */

#ifdef __posix93

/**
 * Sleeps for the specified number of milliseconds.
 */
static inline void nap(int milliseconds) {
    struct timespec req;
    req.tv_sec = milliseconds / 1000; // whole seconds
    req.tv_nsec = (milliseconds % 1000) * 1000000L; // remainder in nanoseconds
    nanosleep(&req, NULL);
}

/**
 * Measures in milliseconds the time taken to execute by the specified code block.
 */
#define MEASURE_MS(var, ...) do { \
    struct timespec __start, __end; \
    clock_gettime(CLOCK_MONOTONIC, &__start); \
    __VA_ARGS__; \
    clock_gettime(CLOCK_MONOTONIC, &__end); \
    long __sec_diff = __end.tv_sec - __start.tv_sec; \
    long __nsec_diff = __end.tv_nsec - __start.tv_nsec; \
    double __elapsed_ms = __sec_diff * 1000.0 + __nsec_diff / 1e6; \
    var = __elapsed_ms; \
} while (0)

#endif

/**
 * elapsed_time_dt structure.
 */
typedef struct {
    int weeks;
    int days;
    int hours;
    int minutes;
    int seconds;
} elapsed_time_dt;

#define DEFAULT_ELAPSED_TIME ((elapsed_time_dt){0, 0, 0, 0, 0})

/**
 * Returns an elapsed_time_dt structure with the elapsed time information between start and end values.
 */
elapsed_time_dt get_elapsed_time(time_t start, time_t end);

/**
 * Compares the two provided elapsed_time_dt structures.
 */
static inline int elapsed_time_equal(elapsed_time_dt a, elapsed_time_dt b) {
    return (a.weeks == b.weeks) &&
           (a.days == b.days) &&
           (a.hours == b.hours) &&
           (a.minutes == b.minutes) &&
           (a.seconds == b.seconds);
}

// FORMATTING

#define DATETIME_FORMAT_DDMMYYYY "%d-%m-%Y"
#define DATETIME_FORMAT_DDMMYYYY_HHMMSS "%d-%m-%Y %H:%M:%S"

/**
 * Gets current datetime as formatted string.
 * It accepts a strftime-compatible format string and returns a
 * pointer to allocated string, or NULL on failure.
 * The caller must free() the returned pointer.
 */
char* get_formatted_date_time(const char* fmt);

/**
 * Converts the given time_t (local time, with offset) to it's ISO 8601 string representation.
 */
char* time_to_iso8601(time_t raw_time);

// TIMESTAMP

#include <sys/time.h>

/**
 * ISO 8601 string mask (escaped to avoid the trigraph warning).
 */
#define ISO_8601_MASK "???\?-?\?-??T??:??:??.???Z"

/**
 * Time converter function (gmtime, localtime, etc) type definition.
 */
typedef struct tm*(*time_converter_fn)(const time_t*);

/**
 * Get the ISO 8601 timestamp string using the specified time converter.
 */
char* get_time_converter_stamp(time_converter_fn tc);

/**
 * Get the ISO 8601 timestamp string using gmtime.
 */
static inline char* get_timestamp_utc(void) {
    return get_time_converter_stamp(gmtime);
}

/**
 * Get the ISO 8601 timestamp string using localtime.
 */
static inline char* get_timestamp(void) {
    return get_time_converter_stamp(localtime);
}

// CONVERSION

/**
 * Converts hours, minutes and seconds from integers to a decimal hours double value.
 */
static inline double hms_to_decimal_hours(int hh, int mm, int ss) {
    return hh + mm / 60.0 + ss / 3600.0;
}

/**
 * Converts a decimal hours double value to an hours, minutes and seconds integers array.
 */
void decimal_hours_to_hms(double decimal_hours, int result[3]);

/**
 * Function to convert local time to UTC.
 */
void local_hms_to_utc(int local_hours, int local_minutes, int local_seconds, double gmt_offset, int result[3]);

/**
 * Function to convert local time to UTC decimal hours.
 */
double local_hms_to_utc_decimal_hours(int local_hours, int local_minutes, int local_seconds, double gmt_offset);

/**
 * datetime_dt structure.
 */
typedef struct {
    int year;
    int month;
    int day;
    int hours;
    int minutes;
    int seconds;
} datetime_dt;

/**
 * Function to fill a datetime instance with the data of a tm struct.
 */
bool fill_datetime_from_tm(datetime_dt* datetime, const struct tm* time_tm);

/**
 * Function to get a new datetime instance holding the currante local date time data.
 */
datetime_dt* get_now_datetime(void);

/**
 * Function to determine if an year is leap or not.
 */
static inline bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * Function to determine the amount of days in a month.
 */
int get_days_in_month(int year, int month);

/**
 * Function to modify the provided datetime_dt instance by the provided values (positive to increment and negative to decrement).
 */
void modify_datetime(datetime_dt* dt, int years, int months, int days, int hours, int minutes, int seconds);

/**
 * Function to determine if two datetime_dt instances have the same values.
 */
static inline bool equal_datetimes(datetime_dt* dt1, datetime_dt* dt2) {
    return (dt1->year == dt2->year) &&
           (dt1->month == dt2->month) &&
           (dt1->day == dt2->day) &&
           (dt1->hours == dt2->hours) &&
           (dt1->minutes == dt2->minutes) &&
           (dt1->seconds == dt2->seconds);
}

/**
 * Function to determine if the second datetime_dt instance has a lower value than the first one.
 */
bool is_newer_datetime(datetime_dt* dt1, datetime_dt* dt2);

/**
 * Function to convert 3 ints to a long date value YYYYMMDD.
 */
static inline long ymd_to_long_date(int year, int month, int day) {
    return (long)year * 10000L + (long)month * 100L + (long)day;
}

/**
 * Function to convert long date value YYYYMMDD to 3 ints.
 */
static inline void long_date_to_ymd(long date, int* year, int* month, int* day) {
    *year = date / 10000L;
    *month = (date % 10000L) / 100L;
    *day = date % 100L;
}

