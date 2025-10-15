/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_streams-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

char* read_chunk_from_stream(FILE* stream, size_t size, size_t* length) {
    if (stream == NULL || size == 0) return NULL;
    char* buffer = ce_malloc(size + 1);
    if (assigned(buffer)) {
        if ((*length = fread(buffer, 1, size, stream)) == 0) {
            ce_free(buffer);
            return NULL;
        }
        buffer[size] = CHARS_NULL;
    }
    return buffer;
}

char* read_line_from_stream(FILE* stream) {
    if (stream == NULL) return NULL;
    char* string = ce_malloc(sizeof(char));
    if (assigned(string)) {
        size_t len = 0;
        if (getline(&string, &len, stream) == -1) {
            ce_free(string);
            return NULL;
        }
        string[strcspn(string, STRINGS_LF)] = CHARS_NULL;
    }
    return string;
}

#ifdef __posix_compliant

#include <unistd.h>
#include <fcntl.h>

// Function to redirect stdout to a file for calling the provided function. The provided function follows "void (*)(void)" same as the one used by atexit() -c89- and at_quick_exit() -c11-
bool redirected_stdout_call(prc_fn subroutine, const char* filename) {
    if (subroutine == NULL || !has_content(filename)) return false;
    fflush(stdout);
    int original_stdout_fd = dup(fileno(stdout));
    if (original_stdout_fd == -1) return false;
    int file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (file_fd == -1) {
        close(original_stdout_fd); // close the duplicated descriptor
        return false;
    }
    if (dup2(file_fd, fileno(stdout)) == -1) {
        close(file_fd); // close the file descriptor
        close(original_stdout_fd); // close the duplicated descriptor
        return false;
    }
    subroutine();
    fflush(stdout);
    close(file_fd);
    if (dup2(original_stdout_fd, fileno(stdout)) == -1) return false;
    close(original_stdout_fd);
    return true;
}

#else

// Function to redirect stdout to a file before calling the provided function and returning stdout to the controlling terminal. The provided function follows "void (*)(void)" same as the one used by atexit() -c89- and at_quick_exit() -c11-
bool redirected_stdout_call(prc_fn subroutine, const char* filename) {
    if (subroutine == NULL || !has_content(filename)) return false;
    fflush(stdout);
    FILE* fp = freopen(filename, "w+", stdout);
    if (fp) {
        subroutine();
        fflush(stdout);
        FILE* ct = freopen(CTL_TERM, "w", stdout);
        UNUSED(ct);
    } else return false;
    return true;
}

#endif

