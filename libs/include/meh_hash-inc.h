/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: MeH
 * File: meh_hash-inc.h
 * Brief: part of MeH
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef MEH
#warning This is intended to be part of the MeH C Library.
#endif

/* MeH.HASH -- Hashing Routines */

// error detection

#ifndef KEWL_CRC8_INITIAL_VALUE
    #define KEWL_CRC8_INITIAL_VALUE 0x00
    // NOTE: you may use 0xFF
#endif

#ifndef KEWL_CRC8_POLYNOMIAL_VALUE
    #define KEWL_CRC8_POLYNOMIAL_VALUE 0x31 // polynomial x^8 + x^5 + x^4 + 1 (for a MAXIM like setup)
    // NOTE: there are other options using this algorithm like CRC-8-CCITT (0x07)
#endif

#define crc8(dat, len) crc8_lsbshrxor(dat, len)

/**
 * Calculates a 8-bit Cyclic Redundancy Check for the given data and length.
 * NOTE: this algorithm is like the one used in sensors, it shifts left and, if the MSB is set, it xors.
 */
static inline uint8_t crc8_msbshlxor(const uint8_t* data, int length) {
    uint8_t crc = KEWL_CRC8_INITIAL_VALUE;
    for (int i = 0; i < length; i++) {
        crc ^= data[i]; // xor byte into crc
        for (int bit = 0; bit < 8; bit++)
            if (crc & 0x80) // if MSB is set
                crc = (crc << 1) ^ KEWL_CRC8_POLYNOMIAL_VALUE; // shift left and xor
            else
                crc <<= 1; // only shift left
    }
    return crc;
}

/**
 *
 * Calculates a 8-bit Cyclic Redundancy Check for the given data and length.
 * NOTE: this algorithm is like the one used for bit-reflected (reversed bit order) data, like -mostly- legacy communications protocols (for example some specific proprietary serial communication setups), testing 0x01 for LSB to use with shift right instead.
 */
static inline uint8_t crc8_lsbshrxor(const uint8_t* data, int length) {
    uint8_t crc = KEWL_CRC8_INITIAL_VALUE;
    for (int i = 0; i < length; i++) {
        crc ^= data[i]; // xor byte into crc
        for (int bit = 0; bit < 8; bit++)
            if (crc & 0x01) // if LSB is set
                crc = (crc >> 1) ^ KEWL_CRC8_POLYNOMIAL_VALUE; // shift right and xor
            else
                crc >>= 1; // only shift right
    }
    return crc;
}

static inline uint8_t crc8_string(const char* str) {
    return crc8((uint8_t*)str, strlen(str));
}

// data distribution

/**
 * Calculates the djb2 hash for the specified string.
 */
static inline uint32_t djb2(const char* str) {
    uint32_t hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

/**
 * Calculates the djb2 hash for the specified string producing a valid hash table index according to the provided size.
 */
static inline uint32_t djb2_hash(const char* str, uint32_t htsz) {
    return djb2(str) % htsz; // modulo reduces the numeric hash to the table's bucket count
}

