/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_polyfills-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

ssize_t getline(char** lineptr, size_t* n, FILE* stream) {
    if (lineptr == NULL || n == NULL || stream == NULL) return -1;
    size_t pos = 0;
    int c;
    if (*lineptr == NULL || *n == 0) { // Ensure buffer
        *n = 128;
        char* new_buf = realloc(*lineptr, *n);
        if (new_buf == NULL) return -1;
        *lineptr = new_buf;
    }
    while ((c = fgetc(stream)) != EOF) {
        if (pos + 1 >= *n) {
            size_t new_size = *n * 2;
            char* new_ptr = (char*)realloc(*lineptr, new_size);
            if (new_ptr == NULL) {
                (*lineptr)[pos] = CHARS_NULL; // Keep buffer valid up to pos
                return -1;
            }
            *lineptr = new_ptr;
            *n = new_size;
        }
        (*lineptr)[pos++] = (char)c;
        if (c == CHARS_LF) break;
    }
    if (pos == 0) return -1; // No data read
    (*lineptr)[pos] = CHARS_NULL;
    return pos;
}

