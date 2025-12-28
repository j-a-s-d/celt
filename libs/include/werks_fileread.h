/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: WeRKS FILEREAD
 * File: werks_fileread.h
 * Brief: file reading with callbacks
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "kewl.h"

#define WERKS_FILEREAD

// BY CHUNKS

// Read chunk callback definition
typedef bool (*chunk_read_handler_fn)(char* buffer, size_t length);

// Function to read a entire file chunk by chunk
bool read_binary_file_by_chunk(const char* filename, size_t chunksize, chunk_read_handler_fn cb);

// Read chunk callback definition with reference
typedef bool (*chunk_read_handler_with_reference_fn)(char* buffer, size_t length, void* reference);

// Function to read a entire file chunk by chunk with reference
bool read_binary_file_by_chunk_with_reference(const char* filename, size_t chunksize, chunk_read_handler_with_reference_fn cb, void* reference);

// BY LINES

// Read line callback definition
typedef bool (*line_read_handler_fn)(char* line);

// Function to read a entire file line by line
bool read_text_file_by_line(const char* filename, line_read_handler_fn cb);

// Read line callback definition with reference
typedef bool (*line_read_handler_with_reference_fn)(char* line, void* reference);

// Function to read a entire file line by line with reference
bool read_text_file_by_line_with_reference(const char* filename, line_read_handler_with_reference_fn cb, void* reference);

// BY BYTES

// Read byte callback definition
typedef bool (*byte_read_handler_fn)(unsigned char octet);

// Function to read a entire file byte per byte
bool read_binary_file_by_byte(const char* filename, byte_read_handler_fn cb);

// Read byte callback definition with reference
typedef bool (*byte_read_handler_with_reference_fn)(unsigned char octet, void* reference);

// Function to read a entire file byte per byte with reference
bool read_binary_file_by_byte_with_reference(const char* filename, byte_read_handler_with_reference_fn cb, void* reference);

#ifdef __cplusplus
}
#endif

