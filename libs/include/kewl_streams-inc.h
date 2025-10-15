/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_streams-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

char* read_chunk_from_stream(FILE* stream, size_t size, size_t* length);
char* read_line_from_stream(FILE* stream);

bool redirected_stdout_call(prc_fn subroutine, const char* filename);

