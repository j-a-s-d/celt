/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: MeH
 * File: meh_ensure-inc.h
 * Brief: part of MeH
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef MEH
#warning This is intended to be part of the MeH C Library.
#endif

/* MeH.ENSURE -- Value-Pointers Utilities */

static inline bool ensure_bool_value_def(bool* val, bool def) {
    return assigned(val) ? *val : def;
}

static inline bool ensure_bool_value(bool* val) {
    return assigned(val) ? *val : false;
}

static inline char ensure_char_value_def(char* val, char def) {
    return assigned(val) ? *val : def;
}

static inline char ensure_char_value(char* val) {
    return assigned(val) ? *val : '\0';
}

static inline short ensure_short_value(short* val) {
    return assigned(val) ? *val : 0;
}

static inline int ensure_int_value_def(int* val, int def) {
    return assigned(val) ? *val : def;
}

static inline int ensure_int_value(int* val) {
    return assigned(val) ? *val : 0;
}

static inline long ensure_long_value_def(long* val, long def) {
    return assigned(val) ? *val : def;
}

static inline long ensure_long_value(long* val) {
    return assigned(val) ? *val : 0L;
}

static inline long long ensure_long_long_value_def(long long* val, long long def) {
    return assigned(val) ? *val : def;
}

static inline long long ensure_long_long_value(long long* val) {
    return assigned(val) ? *val : 0LL;
}

static inline signed char ensure_signed_char_value_def(signed char* val, signed char def) {
    return assigned(val) ? *val : def;
}

static inline signed char ensure_signed_char_value(signed char* val) {
    return assigned(val) ? *val : '\0';
}

static inline unsigned char ensure_unsigned_char_value_def(unsigned char* val, unsigned char def) {
    return assigned(val) ? *val : def;
}

static inline unsigned char ensure_unsigned_char_value(unsigned char* val) {
    return assigned(val) ? *val : '\0';
}

static inline short ensure_short_value_def(short* val, short def) {
    return assigned(val) ? *val : def;
}

static inline unsigned short ensure_unsigned_short_value_def(unsigned short* val, unsigned short def) {
    return assigned(val) ? *val : def;
}

static inline unsigned short ensure_unsigned_short_value(unsigned short* val) {
    return assigned(val) ? *val : 0u;
}

static inline unsigned int ensure_unsigned_int_value_def(unsigned int* val, unsigned int def) {
    return assigned(val) ? *val : def;
}

static inline unsigned int ensure_unsigned_int_value(unsigned int* val) {
    return assigned(val) ? *val : 0u;
}

static inline unsigned long ensure_unsigned_long_value_def(unsigned long* val, unsigned long def) {
    return assigned(val) ? *val : def;
}

static inline unsigned long ensure_unsigned_long_value(unsigned long* val) {
    return assigned(val) ? *val : 0UL;
}

static inline unsigned long long ensure_unsigned_long_long_value_def(unsigned long long* val, unsigned long long def) {
    return assigned(val) ? *val : def;
}

static inline unsigned long long ensure_unsigned_long_long_value(unsigned long long* val) {
    return assigned(val) ? *val : 0ULL;
}

static inline float ensure_float_value_def(float* val, float def) {
    return assigned(val) ? *val : def;
}

static inline float ensure_float_value(float* val) {
    return assigned(val) ? *val : 0.0f;
}

static inline double ensure_double_value_def(double* val, double def) {
    return assigned(val) ? *val : def;
}

static inline double ensure_double_value(double* val) {
    return assigned(val) ? *val : 0.0;
}

static inline long double ensure_long_double_value_def(long double* val, long double def) {
    return assigned(val) ? *val : def;
}

static inline long double ensure_long_double_value(long double* val) {
    return assigned(val) ? *val : 0.0L;
}

static inline int8_t ensure_int8_value_def(int8_t* val, int8_t def) {
    return assigned(val) ? *val : def;
}

static inline int8_t ensure_int8_value(int8_t* val) {
    return assigned(val) ? *val : 0;
}

static inline uint8_t ensure_uint8_value_def(uint8_t* val, uint8_t def) {
    return assigned(val) ? *val : def;
}

static inline uint8_t ensure_uint8_value(uint8_t* val) {
    return assigned(val) ? *val : 0;
}

static inline int16_t ensure_int16_value_def(int16_t* val, int16_t def) {
    return assigned(val) ? *val : def;
}

static inline int16_t ensure_int16_value(int16_t* val) {
    return assigned(val) ? *val : 0;
}

static inline uint16_t ensure_uint16_value_def(uint16_t* val, uint16_t def) {
    return assigned(val) ? *val : def;
}

static inline uint16_t ensure_uint16_value(uint16_t* val) {
    return assigned(val) ? *val : 0;
}

static inline int32_t ensure_int32_value_def(int32_t* val, int32_t def) {
    return assigned(val) ? *val : def;
}

static inline int32_t ensure_int32_value(int32_t* val) {
    return assigned(val) ? *val : 0;
}

static inline uint32_t ensure_uint32_value_def(uint32_t* val, uint32_t def) {
    return assigned(val) ? *val : def;
}

static inline uint32_t ensure_uint32_value(uint32_t* val) {
    return assigned(val) ? *val : 0;
}

static inline int64_t ensure_int64_value_def(int64_t* val, int64_t def) {
    return assigned(val) ? *val : def;
}

static inline int64_t ensure_int64_value(int64_t* val) {
    return assigned(val) ? *val : 0;
}

static inline uint64_t ensure_uint64_value_def(uint64_t* val, uint64_t def) {
    return assigned(val) ? *val : def;
}

static inline uint64_t ensure_uint64_value(uint64_t* val) {
    return assigned(val) ? *val : 0;
}

