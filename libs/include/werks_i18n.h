/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: WeRKS I18N
 * File: werks_i18n.h
 * Brief: messages localization
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "kewl.h"

#define WERKS_I18N

#ifndef WERKS_I18N_ALIGNMENT
    #define WERKS_I18N_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef WERKS_I18N_MESSAGE_ALIGNMENT
    #define WERKS_I18N_MESSAGE_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef WERKS_I18N_GROW_FACTOR
    #define WERKS_I18N_GROW_FACTOR 2.0f
#endif

#ifndef WERKS_I18N_GROW_PADDING
    #define WERKS_I18N_GROW_PADDING 0.0f
#endif

#ifndef WERKS_I18N_INITIAL_CAPACITY
    #define WERKS_I18N_INITIAL_CAPACITY 4
#endif

#ifndef WERKS_I18N_MESSAGES_GROW_FACTOR
    #define WERKS_I18N_MESSAGES_GROW_FACTOR 2.0f
#endif

#ifndef WERKS_I18N_MESSAGES_GROW_PADDING
    #define WERKS_I18N_MESSAGES_GROW_PADDING 0.0f
#endif

#ifndef WERKS_I18N_MESSAGES_INITIAL_CAPACITY
    #define WERKS_I18N_MESSAGES_INITIAL_CAPACITY 64
#endif

#ifndef WERKS_I18N_MESSAGE_DEFAULT_VALUE
    #define WERKS_I18N_MESSAGE_DEFAULT_VALUE STRINGS_NOTHING
#endif

bool werks_i18n_init(void);
void werks_i18n_deinit(void);
ssize_t werks_i18n_get_size(void);
ssize_t werks_i18n_get_capacity(void);
float werks_i18n_get_capacity_grow_factor(void);
float werks_i18n_get_capacity_grow_padding(void);
void werks_i18n_set_capacity_grow_factor(float factor);
void werks_i18n_set_capacity_grow_padding(float padding);
bool werks_i18n_grow_capacity(float factor, float padding);
bool werks_i18n_accept_language(const char* language, const char* name);
const char* werks_i18n_get_current_language_name(void);
const char* werks_i18n_get_current_language(void);
bool werks_i18n_set_current_language(const char* language);
bool werks_i18n_add_message(const char* code, const char* text);
bool werks_i18n_delete_message(const char* code);
bool werks_i18n_register_message(const char* message);
const char* werks_i18n_fetch_raw_text(const char* code);
char* werks_i18n_get_text(const char* code, ...);
const char* werks_i18n_fetch_raw_language_text(const char* language, const char* code);
char* werks_i18n_get_language_text(const char* language, const char* code, ...);
bool werks_i18n_load_from_file(const char* filename);

static const struct {
    bool (*const init)(void);
    ssize_t (*const get_size)(void);
    ssize_t (*const get_capacity)(void);
    float (*const get_capacity_grow_factor)(void);
    float (*const get_capacity_grow_padding)(void);
    void (*const set_capacity_grow_factor)(float factor);
    void (*const set_capacity_grow_padding)(float padding);
    bool (*const grow_capacity)(float factor, float padding);
    bool (*const accept_language)(const char* language, const char* name);
    const char* (*const get_current_language_name)(void);
    const char* (*const get_current_language)(void);
    bool (*const set_current_language)(const char* language);
    bool (*const add_message)(const char* code, const char* text);
    bool (*const delete_message)(const char* code);
    bool (*const register_message)(const char* message);
    const char* (*const fetch_raw_text)(const char* code);
    char* (*const get_text)(const char* code, ...);
    const char* (*const fetch_raw_language_text)(const char* language, const char* code);
    char* (*const get_language_text)(const char* language, const char* code, ...);
    bool (*const load_from_file)(const char* filename);
    void (*const deinit)(void);
} I18N = {
    werks_i18n_init,
    werks_i18n_get_size,
    werks_i18n_get_capacity,
    werks_i18n_get_capacity_grow_factor,
    werks_i18n_get_capacity_grow_padding,
    werks_i18n_set_capacity_grow_factor,
    werks_i18n_set_capacity_grow_padding,
    werks_i18n_grow_capacity,
    werks_i18n_accept_language,
    werks_i18n_get_current_language_name,
    werks_i18n_get_current_language,
    werks_i18n_set_current_language,
    werks_i18n_add_message,
    werks_i18n_delete_message,
    werks_i18n_register_message,
    werks_i18n_fetch_raw_text,
    werks_i18n_get_text,
    werks_i18n_fetch_raw_language_text,
    werks_i18n_get_language_text,
    werks_i18n_load_from_file,
    werks_i18n_deinit
};

#ifdef __cplusplus
}
#endif

