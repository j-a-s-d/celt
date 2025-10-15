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

typedef void (*chunk_read_handler_fn)(char* buffer, size_t length);

// Function to read a entire file chunk by chunk
bool read_binary_file_by_chunk(const char* filename, size_t chunksize, chunk_read_handler_fn cb);

// BY LINES

// Read line callback definition
typedef void (*line_read_handler_fn)(char* line);

// Function to read a entire file line by line
bool read_text_file_by_line(const char* filename, line_read_handler_fn cb);

// BY BYTES

// Read byte callback definition
typedef void (*byte_read_handler_fn)(unsigned char octet);

// Function to read a entire file byte per byte
bool read_binary_file_by_byte(const char* filename, byte_read_handler_fn cb);

#ifdef __cplusplus
}
#endif

