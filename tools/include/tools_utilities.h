/**
 * C eXTRA LiBRARiES & TOOLS
 * (c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// ceems -- MACROS

#define CONCAT_IMPL(a, b) a##b
#define CONCAT(a, b) CONCAT_IMPL(a, b)

// ceems -- HASH

// djb2 hash function for strings
unsigned long djb2(const char* str);

// djb2 hash function variant that produces a valid hash table index
unsigned long djb2_hash(const char* str, unsigned long htsz);

// ceems -- HASH TABLE

#define HASH_TABLE_SIZE 4096

// Simple hash table for storing unique tokens
typedef struct hash_table_node_dt {
    char* token;
    struct hash_table_node_dt* next;
} hash_table_node_dt;

// Check if token is already stored; if not, insert it and return 0; else return 1
int hash_table_knows(hash_table_node_dt** hash_table, const char* token);

// Cleanup hash table memory
void hash_table_clean(hash_table_node_dt** hash_table);

// ceems - STRINGS

int is_numeric_string(const char *str);
int find_string_in_array(const char* target, const char* array[], int array_size);
int find_first_null_index(const char** arr);

// ceems -- C LANGUAGE

int is_c_keyword(const char* word);

