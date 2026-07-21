/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: PeRKS ASSETS
 * File: perks_assets.h
 * Brief: assets embedding
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "kewl.h"

#define PERKS_ASSETS

// This macro generates the assembly to embed the specified file and declares the extern variables with the specified prefix to be dumped later with DUMP_ASSET macro
#define EMBED_ASSET(file_path, prefix) \
    __asm__( \
        ".section .rodata\n" /* force the linker into the read-only data section */ \
        ".balign 16\n" /* 16-byte alignment optimizes CPU vector instruction speeds */ \
        ".global " STR(prefix) "_start\n" \
        ".global " STR(prefix) "_end\n" \
        STR(prefix) "_start:\n" \
        ".incbin \"" file_path "\"\n" \
        STR(prefix) "_end:\n" \
        ".byte 0\n" /* append a hidden null-terminator for safety */ \
        ".section .text\n" /* switch back to code section */ \
    ); \
    extern const unsigned char prefix##_start[]; \
    extern const unsigned char prefix##_end[]

// This macro dumps a file with the specified name which was previously embedded with EMBED_ASSET macro using the specified prefix
#define DUMP_ASSET(file_path, prefix) \
    write_binary_file(file_path, (uint8_t**)prefix##_start, (size_t)prefix##_end - (size_t)prefix##_start)

#ifdef __cplusplus
}
#endif

