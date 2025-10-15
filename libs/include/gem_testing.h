/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: GeM TESTING
 * File: gem_testing.h
 * Brief: simple tooling for testing CeLT stuff
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define GeM_TESTING

/* GeM.TESTING */

#include <stdio.h>
#include <stdarg.h>
#include "ce.h"

#define TEST_BOOL ((bool) true)
#define TEST_CHAR ((char) 'c')
#define TEST_SIGNED_CHAR ((signed char) -12)
#define TEST_UNSIGNED_CHAR ((unsigned char) 250)
#define TEST_SHORT ((short) -123)
#define TEST_UNSIGNED_SHORT ((unsigned short) 456)
#define TEST_INT (-123456)
#define TEST_UNSIGNED_INT (123456u)
#define TEST_LONG_INT (-1234567890L)
#define TEST_UNSIGNED_LONG_INT (1234567890UL)
#define TEST_LONG_LONG_INT (-1234567890123456789LL)
#define TEST_UNSIGNED_LONG_LONG_INT (12345678901234567890ULL)
#define TEST_FLOAT (123.45f)
#define TEST_DOUBLE (123.45)
#define TEST_LONG_DOUBLE (3.141592653589793238462643383279502884L)
#define TEST_STRING "Hello, world!"

#ifdef GEM_TESTING_COMPLEX

#include <complex.h>

#define TEST_FLOAT_COMPLEX ((float _Complex) 1.2f + 3.4f * I)
#define TEST_DOUBLE_COMPLEX ((double _Complex) 5.6 + 7.8 * I)
#define TEST_LONG_DOUBLE_COMPLEX ((long double _Complex) 9.0L + 1.1L * I)

#endif

/* std int aliases constants for convenience */
#define TEST_INT8 ((int8_t) -100)
#define TEST_UINT8 ((uint8_t) 200)
#define TEST_INT16 ((int16_t) -30000)
#define TEST_UINT16 ((uint16_t) 60000)
#define TEST_INT32 ((int32_t) -2000000000)
#define TEST_UINT32 ((uint32_t) 4000000000U)
#define TEST_INT64 ((int64_t) -9000000000000000000LL)
#define TEST_UINT64 ((uint64_t) 18000000000000000000ULL)

static int _total = 0;
static int _errors = 0;
static const char* _text = NULL;

static void test_begin(const char* text) {
    printf("@test_begin: %s\n", text);
    _text = text;
    _total = 0;
    _errors = 0;
}

static bool test_run(const char* text, const bool check) {
    bool result;
    _total++;
    if (!(result = check)) _errors++;
    printf(".%s: %s\n", text, result ? "OK" : "ERROR!");
    return result;
}

static void test_print(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    printf("| ");
    vprintf(fmt, args);
    va_end(args);
}

static void test_println(void) {
    printf("|\n");
}

static int test_end(void) {
    printf("@test_end: %s (%d OK", _text, _total);
    if (_errors > 0) {
        printf(" & %d ERROR)\n", _errors);
    } else
        printf(")\n");
    return _errors;
}

static const struct {
    /* const in members is kept for clarity */
    void (*const begin)(const char*);
    bool (*const run)(const char*, const bool);
    void (*const print)(const char*, ...);
    void (*const println)(void);
    int (*const end)(void);
} Tests = { test_begin, test_run, test_print, test_println, test_end };

#ifdef __cplusplus
}
#endif

