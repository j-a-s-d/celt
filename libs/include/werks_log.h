/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: WeRKS LOG
 * File: werks_log.h
 * Brief: buffered logging
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "kewl.h"

#define WERKS_LOG

#ifndef WERKS_LOG_BUFFER_SIZE
    #define WERKS_LOG_BUFFER_SIZE 4096
#endif

#ifndef WERKS_LOG_MESSAGE_SIZE
    #define WERKS_LOG_MESSAGE_SIZE 512
#endif

bool werks_log_init(const char* filename);
const char* werks_log_get_filename(void);
bool werks_log_is_logging(void);
bool werks_log_in_console(void);
void werks_log_close(void);

const char* werks_log_get_entry_prefix(void);
void werks_log_set_entry_prefix(const char* value);
const char* werks_log_get_entry_suffix(void);
void werks_log_set_entry_suffix(const char* value);
const char* werks_log_get_entry_fields_separator(void);
void werks_log_set_entry_fields_separator(const char* value);
#ifndef KEWL_DISABLE_COMPONENT
void werks_log_set_entry_component_separator(const char* value);
const char* werks_log_get_entry_component_separator(void);
#endif
void werks_log_add_ignored_level(char chr);
void werks_log_remove_ignored_level(char chr);
bool werks_log_has_level_ignored(char chr);

typedef void(*werks_log_on_flush_fail_callback_fn)(int err);
void werks_log_set_on_flush_fail(werks_log_on_flush_fail_callback_fn handler);
werks_log_on_flush_fail_callback_fn werks_log_get_on_flush_fail(void);
void werks_log_flush(void);

void werks_log_message(char level, const char* fmt, va_list args);

#define LOG_LEVEL_DEBUG 'D'
#define LOG_LEVEL_INFO 'I'
#define LOG_LEVEL_WARNING 'W'
#define LOG_LEVEL_ERROR 'E'
#define LOG_LEVEL_FATAL 'F'

#define LOG_LEVEL(level_char, fnc_name) \
    void fnc_name(const char* fmt, ...) { \
        va_list args; \
        va_start(args, fmt); \
        werks_log_message(level_char, fmt, args); \
        va_end(args); \
    }

void werks_log_debug(const char* fmt, ...);
void werks_log_info(const char* fmt, ...);
void werks_log_warning(const char* fmt, ...);
void werks_log_error(const char* fmt, ...);
void werks_log_fatal(const char* fmt, ...);

#ifndef KEWL_DISABLE_COMPONENT

#define LOG_COMPONENT_LEVEL(level_char, fnc_name) \
    void fnc_name(kewl_component_dt* component, const char* fmt, ...) { \
        va_list args; \
        va_start(args, fmt); \
        werks_log_component_message(level_char, component, fmt, args); \
        va_end(args); \
    }

void werks_log_component_debug(kewl_component_dt* component, const char* fmt, ...);
void werks_log_component_info(kewl_component_dt* component, const char* fmt, ...);
void werks_log_component_warning(kewl_component_dt* component, const char* fmt, ...);
void werks_log_component_error(kewl_component_dt* component, const char* fmt, ...);
void werks_log_component_fatal(kewl_component_dt* component, const char* fmt, ...);

#endif

#define LOG_EXTENSION ".log"

static const struct {
    bool (*const init)(const char* filename);
    const char* (*const get_filename)(void);
    bool (*const is_logging)(void);
    bool (*const in_console)(void);
    void (*const debug)(const char*, ...);
    void (*const info)(const char*, ...);
    void (*const warning)(const char*, ...);
    void (*const error)(const char*, ...);
    void (*const fatal)(const char*, ...);
    #ifndef KEWL_DISABLE_COMPONENT
    void (*const component_debug)(kewl_component_dt* component, const char*, ...);
    void (*const component_info)(kewl_component_dt* component, const char*, ...);
    void (*const component_warning)(kewl_component_dt* component, const char*, ...);
    void (*const component_error)(kewl_component_dt* component, const char*, ...);
    void (*const component_fatal)(kewl_component_dt* component, const char*, ...);
    #endif
    void (*const flush)(void);
    void (*const set_on_flush_fail)(werks_log_on_flush_fail_callback_fn handler);
    werks_log_on_flush_fail_callback_fn (*const get_on_flush_fail)(void);
    void (*const set_entry_prefix)(const char* value);
    void (*const set_entry_suffix)(const char* value);
    void (*const set_entry_fields_separator)(const char* value);
    const char* (*const get_entry_prefix)(void);
    const char* (*const get_entry_suffix)(void);
    const char* (*const get_entry_fields_separator)(void);
    void (*const add_ignored_level)(char chr);
    void (*const remove_ignored_level)(char chr);
    bool (*const has_level_ignored)(char chr);
    void (*const close)(void);
} Log = {
    werks_log_init,
    werks_log_get_filename, werks_log_is_logging, werks_log_in_console,
    werks_log_debug, werks_log_info, werks_log_warning, werks_log_error, werks_log_fatal,
    #ifndef KEWL_DISABLE_COMPONENT
    werks_log_component_debug, werks_log_component_info, werks_log_component_warning, werks_log_component_error, werks_log_component_fatal,
    #endif
    werks_log_flush, werks_log_set_on_flush_fail, werks_log_get_on_flush_fail,
    werks_log_set_entry_prefix, werks_log_set_entry_suffix, werks_log_set_entry_fields_separator,
    werks_log_get_entry_prefix, werks_log_get_entry_suffix, werks_log_get_entry_fields_separator,
    werks_log_add_ignored_level, werks_log_remove_ignored_level, werks_log_has_level_ignored,
    werks_log_close
};

#ifdef __cplusplus
}
#endif

