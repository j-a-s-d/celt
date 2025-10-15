/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: WeRKS ANSI
 * File: werks_ansi.h
 * Brief: ansi constants and routines
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "kewl.h"

#define WERKS_ANSI

#define ANSI_ESCAPE "\x1b" // hex for octal: \033
#define ANSI_CODE_RESET ANSI_ESCAPE "[0m"
#define ANSI_CODE_BOLD ANSI_ESCAPE "[1m"
#define ANSI_CODE_UNDERLINED ANSI_ESCAPE "[4m"
#define ANSI_CODE_REVERSED ANSI_ESCAPE "[7m"
#define ANSI_CODE_BLACK ANSI_ESCAPE "[30m"
#define ANSI_CODE_RED ANSI_ESCAPE "[31m"
#define ANSI_CODE_GREEN ANSI_ESCAPE "[32m"
#define ANSI_CODE_YELLOW ANSI_ESCAPE "[33m"
#define ANSI_CODE_BLUE ANSI_ESCAPE "[34m"
#define ANSI_CODE_MAGENTA ANSI_ESCAPE "[35m"
#define ANSI_CODE_CYAN ANSI_ESCAPE "[36m"
#define ANSI_CODE_WHITE ANSI_ESCAPE "[37m"
#define ANSI_CODE_BRIGHT_BLACK ANSI_ESCAPE "[90m"
#define ANSI_CODE_BRIGHT_RED ANSI_ESCAPE "[91m"
#define ANSI_CODE_BRIGHT_GREEN ANSI_ESCAPE "[92m"
#define ANSI_CODE_BRIGHT_YELLOW ANSI_ESCAPE "[93m"
#define ANSI_CODE_BRIGHT_BLUE ANSI_ESCAPE "[94m"
#define ANSI_CODE_BRIGHT_MAGENTA ANSI_ESCAPE "[95m"
#define ANSI_CODE_BRIGHT_CYAN ANSI_ESCAPE "[96m"
#define ANSI_CODE_BRIGHT_WHITE ANSI_ESCAPE "[97m"
#define ANSI_CODE_BG_BLACK ANSI_ESCAPE "[40m"
#define ANSI_CODE_BG_RED ANSI_ESCAPE "[41m"
#define ANSI_CODE_BG_GREEN ANSI_ESCAPE "[42m"
#define ANSI_CODE_BG_YELLOW ANSI_ESCAPE "[43m"
#define ANSI_CODE_BG_BLUE ANSI_ESCAPE "[44m"
#define ANSI_CODE_BG_MAGENTA ANSI_ESCAPE "[45m"
#define ANSI_CODE_BG_CYAN ANSI_ESCAPE "[46m"
#define ANSI_CODE_BG_WHITE ANSI_ESCAPE "[47m"
#define ANSI_CODE_BG_BRIGHT_BLACK ANSI_ESCAPE "[100m"
#define ANSI_CODE_BG_BRIGHT_RED ANSI_ESCAPE "[101m"
#define ANSI_CODE_BG_BRIGHT_GREEN ANSI_ESCAPE "[102m"
#define ANSI_CODE_BG_BRIGHT_YELLOW ANSI_ESCAPE "[103m"
#define ANSI_CODE_BG_BRIGHT_BLUE ANSI_ESCAPE "[104m"
#define ANSI_CODE_BG_BRIGHT_MAGENTA ANSI_ESCAPE "[105m"
#define ANSI_CODE_BG_BRIGHT_CYAN ANSI_ESCAPE "[106m"
#define ANSI_CODE_BG_BRIGHT_WHITE ANSI_ESCAPE "[107m"

static inline char* ansi_reset_before(const char* str) {
    return strprepend(strdup(str), ANSI_CODE_RESET);
}

static inline char* ansi_reset_after(const char* str) {
    return strappend(strdup(str), ANSI_CODE_RESET);
}

static inline char* ansi_bold(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BOLD), ANSI_CODE_RESET);
}

static inline char* ansi_underlined(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_UNDERLINED), ANSI_CODE_RESET);
}

static inline char* ansi_reversed(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_REVERSED), ANSI_CODE_RESET);
}

static inline char* ansi_black(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BLACK), ANSI_CODE_RESET);
}

static inline char* ansi_red(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_RED), ANSI_CODE_RESET);
}

static inline char* ansi_green(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_GREEN), ANSI_CODE_RESET);
}

static inline char* ansi_yellow(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_YELLOW), ANSI_CODE_RESET);
}

static inline char* ansi_blue(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BLUE), ANSI_CODE_RESET);
}

static inline char* ansi_magenta(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_MAGENTA), ANSI_CODE_RESET);
}

static inline char* ansi_cyan(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_CYAN), ANSI_CODE_RESET);
}

static inline char* ansi_white(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_WHITE), ANSI_CODE_RESET);
}

static inline char* ansi_bright_black(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BRIGHT_BLACK), ANSI_CODE_RESET);
}

static inline char* ansi_bright_red(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BRIGHT_RED), ANSI_CODE_RESET);
}

static inline char* ansi_bright_green(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BRIGHT_GREEN), ANSI_CODE_RESET);
}

static inline char* ansi_bright_yellow(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BRIGHT_YELLOW), ANSI_CODE_RESET);
}

static inline char* ansi_bright_blue(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BRIGHT_BLUE), ANSI_CODE_RESET);
}

static inline char* ansi_bright_magenta(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BRIGHT_MAGENTA), ANSI_CODE_RESET);
}

static inline char* ansi_bright_cyan(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BRIGHT_CYAN), ANSI_CODE_RESET);
}

static inline char* ansi_bright_white(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BRIGHT_WHITE), ANSI_CODE_RESET);
}

static inline char* ansi_bg_black(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_BLACK), ANSI_CODE_RESET);
}

static inline char* ansi_bg_red(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_RED), ANSI_CODE_RESET);
}

static inline char* ansi_bg_green(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_GREEN), ANSI_CODE_RESET);
}

static inline char* ansi_bg_yellow(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_YELLOW), ANSI_CODE_RESET);
}

static inline char* ansi_bg_blue(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_BLUE), ANSI_CODE_RESET);
}

static inline char* ansi_bg_magenta(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_MAGENTA), ANSI_CODE_RESET);
}

static inline char* ansi_bg_cyan(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_CYAN), ANSI_CODE_RESET);
}

static inline char* ansi_bg_white(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_WHITE), ANSI_CODE_RESET);
}

static inline char* ansi_bg_bright_black(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_BRIGHT_BLACK), ANSI_CODE_RESET);
}

static inline char* ansi_bg_bright_red(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_BRIGHT_RED), ANSI_CODE_RESET);
}

static inline char* ansi_bg_bright_green(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_BRIGHT_GREEN), ANSI_CODE_RESET);
}

static inline char* ansi_bg_bright_yellow(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_BRIGHT_YELLOW), ANSI_CODE_RESET);
}

static inline char* ansi_bg_bright_blue(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_BRIGHT_BLUE), ANSI_CODE_RESET);
}

static inline char* ansi_bg_bright_magenta(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_BRIGHT_MAGENTA), ANSI_CODE_RESET);
}

static inline char* ansi_bg_bright_cyan(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_BRIGHT_CYAN), ANSI_CODE_RESET);
}

static inline char* ansi_bg_bright_white(const char* str) {
    return strappend(strprepend(strdup(str), ANSI_CODE_BG_BRIGHT_WHITE), ANSI_CODE_RESET);
}

bool has_ansi_codes(const char* input);
char* strip_ansi_codes(const char* input);

