/**
 * C eXTRA LiBRARiES & TOOLS
 * (c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#include <sys/types.h>
#include <stdio.h>
#include <string.h>

struct file_declarations_dt {
    const char* name;
    const char** globals;
    size_t globals_len;
    const char** types;
    size_t types_len;
    const char** macros;
    size_t macros_len;
    const char** functions;
    size_t functions_len;
};

struct file_declarations_array_dt {
    struct file_declarations_dt* items;
    size_t size;
    size_t capacity;
};

extern struct file_declarations_array_dt declarations_array;

void load_declarations();
void unload_declarations();

struct file_declarations_dt* find_in_declarations_array(const char* target);

struct file_declarations_dt* get_file_declarations(const char* filename);

