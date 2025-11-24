/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_filesystem-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include <errno.h>

// FILES

bool write_hex_data_as_binary_to_file(const char* filename, const char* array[], size_t size) {
    if (filename == NULL || array == NULL) return false;
    FILE* file = fopen(filename, "wb");
    if (file == NULL) return false;
    for (size_t i = 0; i < size; i++) {
        const char* hex_str = array[i];
        if (hex_str == NULL || strlen(hex_str) != 2) {
            fclose(file);
            return false;
        }
        unsigned char byte;
        if (!hex_string_to_byte(hex_str, &byte)) {
            fclose(file);
            return false;
        }
        if (fwrite(&byte, 1, 1, file) != 1) {
            fclose(file);
            return false;
        }
    }
    fclose(file);
    return true;
}

char** read_file_as_hex_data(const char* filename, size_t* out_count) {
    if (filename == NULL || out_count == NULL) return NULL;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) return NULL;
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }
    long filesize = ftell(file);
    if (filesize < 0) {
        fclose(file);
        return NULL;
    }
    rewind(file);
    // allocate array of pointers for hex strings
    char** hex_array = ce_malloc(filesize * sizeof(char*));
    if (hex_array == NULL) {
        fclose(file);
        return NULL;
    }
    for (long i = 0; i < filesize; i++) {
        hex_array[i] = ce_malloc(3); // 2 hex chars + null terminator
        if (hex_array[i] == NULL) {
            // free previously allocated memory on failure
            for (long j = 0; j < i; j++) ce_free(hex_array[j]);
            ce_free(hex_array);
            fclose(file);
            return NULL;
        }
    }
    for (long i = 0; i < filesize; i++) {
        int byte = fgetc(file);
        if (byte == EOF) { // on unexpected EOF, clean up
            for (long j = 0; j < filesize; j++) ce_free(hex_array[j]);
            ce_free(hex_array);
            fclose(file);
            return NULL;
        }
        snprintf((char*)hex_array[i], 3, "%02X", (unsigned char)byte);
    }
    fclose(file);
    *out_count = (size_t)filesize;
    return hex_array;
}

char* read_file_as_hex_string(const char* filename, const char* separator) {
    if (filename == NULL || separator == NULL) return NULL;
    FILE* file = fopen(filename, "rb");
    if (file == NULL) return NULL;
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }
    ssize_t filesize = ftell(file);
    if (filesize < 0) {
        fclose(file);
        return NULL;
    }
    rewind(file);
    if (filesize == 0) {
        fclose(file);
        return strdup(STRINGS_NOTHING);
    }
    unsigned char* buffer = ce_malloc(filesize);
    if (buffer == NULL) {
        fclose(file);
        return NULL;
    }
    ssize_t read_bytes = fread(buffer, 1, filesize, file);
    fclose(file);
    if (read_bytes != (ssize_t)filesize) {
        ce_free(buffer);
        return NULL;
    }
    ssize_t sep_len = strlen(separator);
    // each byte is 2 hex chars plus separator between bytes (except last) + 1 for '\0'
    ssize_t output_len = (2 * filesize) + (sep_len * (filesize - 1)) + 1;
    char* output = ce_malloc(output_len);
    if (output == NULL) {
        ce_free(buffer);
        return NULL;
    }
    char* p = output;
    for (ssize_t i = 0; i < filesize; i++) {
        sprintf(p, "%02X", buffer[i]);
        p += 2;
        if (i != filesize - 1) {
            memcpy(p, separator, sep_len);
            p += sep_len;
        }
    }
    *p = CHARS_NULL;
    ce_free(buffer);
    return output;
}

bool rename_file(const char* source_filename, const char* target_filename) {
    if (source_filename == NULL || target_filename == NULL) return false;
#ifdef __posix_compliant
    return rename(source_filename, target_filename) == 0;
#else
    FILE* src = fopen(source_filename, "rb");
    if (src == NULL) return false;
    FILE* tgt = fopen(target_filename, "wb");
    if (tgt == NULL) {
        fclose(src);
        return false;
    }
    char buffer[4 * KILOBYTE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), src)) > 0)
        if (fwrite(buffer, 1, bytes_read, tgt) != bytes_read) {
            fclose(src);
            fclose(tgt);
            return false;
        }
    fclose(src);
    fclose(tgt);
    return true;
#endif
}

// DIRECTORIES

bool create_moded_nested_directories(const char* path, mode_t mode) {
    char temp[256];
    snprintf(temp, sizeof(temp), "%s", path);
    size_t len = strlen(temp);
    if (temp[len - 1] == CHARS_SLASH) temp[len - 1] = CHARS_NULL;
    char* p = NULL;
    for (p = temp + 1; *p; p++)
        if (*p == CHARS_SLASH) {
            *p = CHARS_NULL;
            if (mkdir(temp, mode) != 0 && errno != EEXIST) return false;
            *p = CHARS_SLASH;
        }
    if (mkdir(temp, mode) != 0 && errno != EEXIST) return false;
    return true;
}

bool delete_nested_directories(const char* path) {
    DIR* dir = opendir(path);
    if (dir == NULL) return false;
    struct dirent* entry;
    bool success = true;
    while (assigned(entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        char d[512];
        snprintf(d, sizeof(d), "%s/%s", path, entry->d_name);
        struct stat statbuf;
        if (stat(d, &statbuf) != 0) {
            success = false;
            break;
        }
        if (S_ISDIR(statbuf.st_mode)) {
            if (!delete_nested_directories(d)) {
                success = false;
                break;
            }
        } else {
            if (remove(path) != 0) {
                success = false;
                break;
            }
        }
    }
    closedir(dir);
    if (success) {
        if (remove(path) != 0)
            success = false;
    }
    return success;
}

char* list_directory(const char* path, const char* separator) {
    DIR* dir;
    struct dirent* entry;
    size_t separator_len = strlen(separator);
    size_t buffer_size = MEH_DEFAULT_BUFFER_SIZE; // Initial buffer size
    char* result = ce_malloc(buffer_size);
    if (result == NULL) return NULL;
    result[0] = CHARS_NULL; // Initialize as an empty string
    dir = opendir(path);
    if (dir == NULL) {
        ce_free(result);
        return NULL;
    }
    while (assigned(entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) // Skip "." and ".."
            continue;
        // Calculate required buffer size
        size_t entry_len = strlen(entry->d_name);
        size_t new_length = strlen(result) + entry_len + separator_len + 1; // +1 for null terminator
        // Resize buffer if necessary
        if (new_length > buffer_size) {
            buffer_size *= 2; // Double the buffer size
            char* temp = realloc(result, buffer_size);
            if (!temp) {
                ce_free(result);
                closedir(dir);
                return NULL;
            }
            result = temp;
        }
        // Append entry and separator to result
        strcat(result, entry->d_name);
        strcat(result, separator);
    }
    closedir(dir);
    // Remove trailing separator, if any
    size_t result_len = strlen(result);
    if (result_len > separator_len)
        result[result_len - separator_len] = CHARS_NULL;
    return result;
}

