/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_debug-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

// DEBUG -- General-purpose Utilities

// Function to print alignment information
void print_alignment_information(const void* ptr, size_t alignment);

// Function to print a byte array as hex
void print_bytes_as_hex(const void* ptr, size_t size, size_t columns, const char* separator);

// DEBUG -- Binary-print Utilities

// Function to print an unsigned 8-bit integer in binary
static inline void print_binary8(uint8_t x) {
    for (int i = 7; i >= 0; i--)
        printf("%c", (x & (1 << i)) ? '1' : '0');
}

// Function to print unsigned 16-bit integer in binary
static inline void print_binary16(uint16_t x) {
    for (int i = 15; i >= 0; i--)
        printf("%c", (x & (1 << i)) ? '1' : '0');
}

// Function to print unsigned 32-bit integer in binary
static inline void print_binary32(uint32_t x) {
    for (int i = 31; i >= 0; i--)
        printf("%c", (x & (1 << i)) ? '1' : '0');
}

// Function to print unsigned 64-bit integer in binary
static inline void print_binary64(uint64_t x) {
    for (int i = 63; i >= 0; i--)
        printf("%c", (x & (1 << i)) ? '1' : '0');
}

// DEBUG -- Generic-print Utilities

#define _PRINT_FORMATTED_FN(fn) \
    fmt = ensure_const_string(fmt); \
    va_list args; \
    va_start(args, fmt); \
    ssize_t size = get_string_format_size(fmt, args); \
    if (size < 0) { \
        va_end(args); \
        return false; /* encoding error */ \
    } \
    char* text = perform_string_format(size, fmt, args); \
    va_end(args); \
    fn(text); \
    free(text); \
    return true;

#ifndef KEWL_PRINT_TEXT_PREFIX
    #define KEWL_PRINT_TEXT_PREFIX STRINGS_NOTHING
#endif
#ifndef KEWL_PRINT_TEXT_SUFFIX
    #define KEWL_PRINT_TEXT_SUFFIX STRINGS_NOTHING
#endif

// Function to safely print a generic text to the console (without line feed)
static inline void print_text(const char* text) {
    printf(KEWL_PRINT_TEXT_PREFIX "%s" KEWL_PRINT_TEXT_SUFFIX, ensure_const_string(text));
}

// Function to safely print a formatted text to the console (without line feed) returning true on success
__unused static bool print_formatted_text(const char* fmt, ...) {
    _PRINT_FORMATTED_FN(print_text)
}

#ifndef KEWL_PRINT_LINE_PREFIX
    #define KEWL_PRINT_LINE_PREFIX STRINGS_NOTHING
#endif
#ifndef KEWL_PRINT_LINE_SUFFIX
    #define KEWL_PRINT_LINE_SUFFIX STRINGS_LF
#endif

// Function to safely print a generic message to the console
static inline void print_line(const char* text) {
    printf(KEWL_PRINT_LINE_PREFIX "%s" KEWL_PRINT_LINE_SUFFIX, ensure_const_string(text));
}

// Function to safely print a formatted message to the console returning true on success
__unused static bool print_formatted_line(const char* fmt, ...) {
    _PRINT_FORMATTED_FN(print_line)
}

#ifndef KEWL_PRINT_ERROR_PREFIX
    #define KEWL_PRINT_ERROR_PREFIX "ERROR: "
#endif
#ifndef KEWL_PRINT_ERROR_SUFFIX
    #define KEWL_PRINT_ERROR_SUFFIX STRINGS_LF
#endif

// Function to safely print a generic error message to the console
static inline void print_error(const char* text) {
    printf(KEWL_PRINT_ERROR_PREFIX "%s" KEWL_PRINT_ERROR_SUFFIX, ensure_const_string(text));
}

// Function to safely print a formatted error message to the console returning true on success
__unused static bool print_formatted_error(const char* fmt, ...) {
    _PRINT_FORMATTED_FN(print_error)
}

#ifndef KEWL_PRINT_INFO_PREFIX
    #define KEWL_PRINT_INFO_PREFIX "INFO: "
#endif
#ifndef KEWL_PRINT_INFO_SUFFIX
    #define KEWL_PRINT_INFO_SUFFIX STRINGS_LF
#endif

// Function to print a generic info message to the console safely
static inline void print_info(const char* text) {
    printf(KEWL_PRINT_INFO_PREFIX "%s" KEWL_PRINT_INFO_SUFFIX, ensure_const_string(text));
}

// Function to safely print a formatted info message to the console returning true on success
__unused static bool print_formatted_info(const char* fmt, ...) {
    _PRINT_FORMATTED_FN(print_info)
}

#ifndef KEWL_PRINT_HINT_PREFIX
    #define KEWL_PRINT_HINT_PREFIX "HINT: "
#endif
#ifndef KEWL_PRINT_HINT_SUFFIX
    #define KEWL_PRINT_HINT_SUFFIX STRINGS_LF
#endif

// Function to print a generic hint message to the console safely
static inline void print_hint(const char* text) {
    printf(KEWL_PRINT_HINT_PREFIX "%s" KEWL_PRINT_HINT_SUFFIX, ensure_const_string(text));
}

// Function to safely print a formatted hint message to the console returning true on success
__unused static bool print_formatted_hint(const char* fmt, ...) {
    _PRINT_FORMATTED_FN(print_hint)
}

#undef _PRINT_FORMATTED_FN

// DEBUG -- Dev-mode Utilities

// Global DEV move flag
extern bool DEVELOPMENT;

// Function to formatted print if in DEV mode
static inline void debug_print(const char* fmt, ...) {
    if (DEVELOPMENT) {
        va_list args;
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
    }
}

// Function to only print text if in DEV mode
static inline void debug_text(const char* text) {
    if (DEVELOPMENT)
        printf("%s\n", text);
}

// Function to only print a byte array as hex if in DEV mode
static inline void debug_hex(const void* ptr, size_t size, size_t columns, const char* separator) {
    if (DEVELOPMENT)
        print_bytes_as_hex(ptr, size, columns, separator);
}

