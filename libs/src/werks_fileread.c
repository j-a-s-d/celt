/**
 * werks_fileread: file reading with callbacks
 */

#include "werks_fileread.h"

// BY CHUNKS

bool read_binary_file_by_chunk(const char* filename, size_t chunksize, chunk_read_handler_fn cb) {
    FILE_OPERATION("r", false, {
        char* buffer;
        size_t amount = 0;
        bool go = true;
        while (assigned(buffer = read_chunk_from_stream(file, chunksize, &amount))) {
            go = cb(buffer, amount);
            ce_free(buffer);
            if (!go) break;
        }
        fclose(file);
        return true;
    });
}

bool read_binary_file_by_chunk_with_reference(const char* filename, size_t chunksize, chunk_read_handler_with_reference_fn cb, void* reference) {
    FILE_OPERATION("r", false, {
        char* buffer;
        size_t amount = 0;
        bool go = true;
        while (assigned(buffer = read_chunk_from_stream(file, chunksize, &amount))) {
            go = cb(buffer, amount, reference);
            ce_free(buffer);
            if (!go) break;
        }
        fclose(file);
        return true;
    });
}

// BY LINES

bool read_text_file_by_line(const char* filename, line_read_handler_fn cb) {
    FILE_OPERATION("r", false, {
        char* line;
        bool go = true;
        while (assigned(line = read_line_from_stream(file))) {
            go = cb(line);
            ce_free(line);
            if (!go) break;
        }
        fclose(file);
        return true;
    });
}

bool read_text_file_by_line_with_reference(const char* filename, line_read_handler_with_reference_fn cb, void* reference) {
    FILE_OPERATION("r", false, {
        char* line;
        bool go = true;
        while (assigned(line = read_line_from_stream(file))) {
            go = cb(line, reference);
            ce_free(line);
            if (!go) break;
        }
        fclose(file);
        return true;
    });
}

// BY BYTES

bool read_binary_file_by_byte(const char* filename, byte_read_handler_fn cb) {
    FILE_OPERATION("r", false, {
        int b;
        if ((b = getc(file)) == EOF) {
            fclose(file);
            return false;
        }
        do {
            if (!cb((unsigned char)b)) break;
        } while ((b = getc(file)) != EOF);
        fclose(file);
        return true;
    });
}

bool read_binary_file_by_byte_with_reference(const char* filename, byte_read_handler_with_reference_fn cb, void* reference) {
    FILE_OPERATION("r", false, {
        int b;
        if ((b = getc(file)) == EOF) {
            fclose(file);
            return false;
        }
        do {
            if (!cb((unsigned char)b, reference)) break;
        } while ((b = getc(file)) != EOF);
        fclose(file);
        return true;
    });
}

