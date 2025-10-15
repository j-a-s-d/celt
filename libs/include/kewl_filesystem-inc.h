/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_filesystem-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

#include <sys/stat.h>

// FILESYSTEM -- Files

#define FILE_OPERATION(oper, failure, block) \
    FILE* file = fopen(filename, oper); \
    if (file) block; \
    return failure;

// Function to check if a file exists
static inline bool file_exists(const char* filename) {
    FILE_OPERATION("r", false, {
        fclose(file);
        return true;
    });
}

// Function to get the size of a file
static inline long get_file_size(const char* filename) {
    FILE_OPERATION("r", -1, {
        fseek(file, 0, SEEK_END);
        const long length = ftell(file);
        fclose(file);
        return length;
    });
}

// Function to append content to a file
static inline bool append_file(const char* filename, const char* content) {
    FILE_OPERATION("a", false, {
        fwrite(content, 1, strlen(content), file);
        fflush(file);
        fclose(file);
        return true;
    });
}

// Function to write content to a file
static inline bool write_file(const char* filename, const char* content) {
    FILE_OPERATION("w", false, {
        fwrite(content, 1, strlen(content), file);
        fflush(file);
        fclose(file);
        return true;
    });
}

// Function to read the entire content of a file
static inline char* read_file(const char* filename) {
    FILE_OPERATION("r", NULL, {
        fseek(file, 0, SEEK_END);
        ssize_t length = ftell(file);
        rewind(file);
        char* content = ce_malloc(length + 1);
        if (content) {
            ssize_t read = fread(content, 1, length, file);
            if (read < length && !feof(file) && ferror(file))
                return NULL;
            content[read] = CHARS_NULL;
        }
        fclose(file);
        return content;
    });
}

// Function to rename a file
bool rename_file(const char* source_filename, const char* target_filename);

// Function to delete a file
static inline bool delete_file(const char* filename) {
    return assigned(filename) && remove(filename) == 0;
}

// Function to write a hex data (array of strings) to file as binary
bool write_hex_data_as_binary_to_file(const char* filename, const char* array[], size_t size);

// Function to read a file as hex data (array of stirngs)
char** read_file_as_hex_data(const char* filename, size_t* out_count);

// Function to read a file as hex string
char* read_file_as_hex_string(const char* filename, const char* separator);

// FILESYSTEM -- Directories

#include <dirent.h>

// Function to create a directory with specific permissions
static inline bool create_moded_directories(const char* path, mode_t mode) {
    return mkdir(path, mode) == 0;
}

// Function to create a directory with full permissions
static inline bool create_directory(const char* path) {
    return create_moded_directories(path, S_IRWXU | S_IRWXG | S_IRWXO); // octal 0777
}

// Function to create nested directories (max path size is 256) with specific permissions
bool create_moded_nested_directories(const char* path, mode_t mode);

// Function to create nested directories (max path size is 256) with full permissions
static inline bool create_nested_directories(const char* path) {
    return create_moded_nested_directories(path, S_IRWXU | S_IRWXG | S_IRWXO); // octal 0777
}

// Function to check if a directory exists
static inline bool directory_exists(const char* path) {
    struct stat info;
    return (stat(path, &info) == 0) && (S_ISDIR(info.st_mode) != 0);
}

// Function to delete a directory (must be empty)
static inline bool delete_directory(const char* path) {
    return remove(path) == 0;
}

// Function to delete nested directories (max path size is 512)
bool delete_nested_directories(const char* path);

// Function to list the entries (files and directories) of a directory with a custom separator
char* list_directory(const char* path, const char* separator);

