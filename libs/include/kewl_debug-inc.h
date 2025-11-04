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

