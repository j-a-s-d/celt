/**
 * C eXTRA LiBRARiES & TOOLS
 * (c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "../include/tools_utilities.h"

// ceems -- HASH

unsigned long djb2(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}

unsigned long djb2_hash(const char* str, unsigned long htsz) {
    return djb2(str) % htsz; // modulo reduces the numeric hash to the table's bucket count
}

// ceems -- HASH TABLE

int hash_table_knows(hash_table_node_dt** hash_table, const char* token) {
    unsigned long h = djb2_hash(token, HASH_TABLE_SIZE);
    hash_table_node_dt* node = hash_table[h];
    while (node) {
        if (strcmp(node->token, token) == 0)
            return 1;
        node = node->next;
    }
    hash_table_node_dt* new_node = malloc(sizeof(hash_table_node_dt));
    if (!new_node) exit(EXIT_FAILURE);
    new_node->token = strdup(token);
    if (!new_node->token) exit(EXIT_FAILURE);
    new_node->next = hash_table[h];
    hash_table[h] = new_node;
    return 0;
}

void hash_table_clean(hash_table_node_dt** hash_table) {
    for (size_t i = 0; i < HASH_TABLE_SIZE; i++) {
        hash_table_node_dt* node = hash_table[i];
        while (node) {
            hash_table_node_dt* tmp = node;
            node = node->next;
            free(tmp->token);
            free(tmp);
        }
        hash_table[i] = NULL;
    }
}

// ceems - STRINGS

int find_string_in_array(const char* target, const char* array[], int array_size) {
    if (target != NULL)
        for (int i = 0; i < array_size; i++)
            if (array[i] != NULL && strcmp(target, array[i]) == 0)
                return i;
    return -1;
}

int is_numeric_string(const char *str) {
    size_t i = 0;
    int has_digit = 0;
    int has_dot = 0;
    if (str[0] == '.')
        i = 1;
    for (; str[i] != '\0'; i++) {
        char c = str[i];
        if (isdigit((unsigned char)c)) {
            has_digit = 1;
        } else if (c == '.') {
            if (has_dot) return 0; // more than one dot invalid for simple float
            has_dot = 1;
        } else if (c == 'e' || c == 'E' || c == 'f' || c == 'F' || c == '+' || c == '-') {
            // Allow exponent and float suffix letters and signs
            // Signs only allowed if preceded by e/E, but for simplicity, allow anywhere
            continue;
        } else if ((c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) {
            // Allow hex digits a-f, A-F
            continue;
        } else
            return 0; // invalid char for numeric literal
    }
    return has_digit;
}

int find_first_null_index(const char** arr) {
    if (!arr) return -1;
    size_t i = 0;
    while (arr[i] != NULL) i++;
    return (int)i;
}

// ceems -- C LANGUAGE

// List of standard C keywords (C11 + common reserved words + C23 keywords)
const char* c_keywords[] = {
    // C11 and earlier keywords
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while", "_Alignas", "_Alignof",
    "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn",
    "_Static_assert", "_Thread_local",
    // C23 new keywords
    "consteval", "constinit", "synchronized",
    "atomic_cancel", "atomic_commit", "atomic_noexcept",
};

const size_t num_keywords = sizeof(c_keywords) / sizeof(c_keywords[0]);

int is_c_keyword(const char* word) {
    for (size_t i = 0; i < num_keywords; i++)
        if (strcmp(word, c_keywords[i]) == 0)
            return 1;
    return 0;
}

