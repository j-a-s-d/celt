/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: WeRKS RANDOMNESS
 * File: werks_randomness.h
 * Brief: chance stuff
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "kewl.h"

#define WERKS_RANDOMNESS

// RANDOMNESS -- chance

// Function to get a random booleam value (like a coin toss)
bool coin_toss(void);

// Function to get a random unsigned 8-bit integer value (like a dice roll)
uint8_t dice_roll(const uint8_t faces);

// Function to get a random float number between 0.0f (inclusive) and 1.0f (exclusive)
float get_random_float_decimals(void);

// Function to get a random double number between 0.0 (inclusive) and 1.0 (exclusive)
double get_random_double_decimals(void);

// Function to get a random short in a specified range of values
short get_short_in_range(const short from, const short to);

// Function to get a random integer in a specified range of values
int get_int_in_range(const int from, const int to);

// Function to get a random long in a specified range of values
long get_long_in_range(const long from, const long to);

// Function to get a random float in a specified range of values
float get_float_in_range(const float min, const float max);

// Function to get a random double in a specified range of values
double get_double_in_range(const double min, const double max);

// Function to fill of random bytes the referred existing array of the specified size
void get_random_bytes_into_buffer(uint8_t* buffer, size_t size);

// Function to generate an array of random bytes of the specified size
uint8_t* get_random_bytes(const size_t amount);

#if defined(__posix08)
// Function to fill of cryptographically secure random bytes the referred existing array of the specified size
bool get_secure_random_bytes_into_buffer(uint8_t* buffer, const size_t amount);
#endif

// RANDOMNESS -- uuid

// In a UUID version 4 the 13th hex digit is always 4 (version) and the 17th is one of 8, 9, A, or B (variant bits)
#define UUIDv4_MASK "xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx"

// Function to generate a version 4 Universally Unique Identifier
char* generate_random_uuid(void);

#ifdef __cplusplus
}
#endif


