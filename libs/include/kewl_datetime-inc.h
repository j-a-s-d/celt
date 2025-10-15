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
 * elapsed_time_t structure.
 */
typedef struct {
    int weeks;
    int days;
    int hours;
    int minutes;
    int seconds;
} elapsed_time_t;

#define DEFAULT_ELAPSED_TIME ((elapsed_time_t){0, 0, 0, 0, 0})

/**
 * Returns an elapsed_time_t structure with the elapsed time information between start and end values.
 */
elapsed_time_t get_elapsed_time(time_t start, time_t end);

/**
 * Compares the two provided elapsed_time_t structures.
 */
static inline int elapsed_time_equal(elapsed_time_t a, elapsed_time_t b) {
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
typedef struct tm*(*time_converter_fn)(const time_t *);

/**
 * Get the ISO 8601 timestamp string using the specified time converter.
 */
char* get_time_converter_stamp(const time_converter_fn tc);

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

