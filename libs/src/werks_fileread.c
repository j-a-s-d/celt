/**
 * werks_fileread: file reading with callbacks
 */

#include "werks_fileread.h"

// BY CHUNKS

bool read_binary_file_by_chunk(const char* filename, size_t chunksize, chunk_read_handler_fn cb) {
    FILE_OPERATION("r", false, {
        char* buffer;
        size_t amount = 0;
        while (assigned(buffer = read_chunk_from_stream(file, chunksize, &amount))) {
            cb(buffer, amount);
            ce_free(buffer);
        }
        fclose(file);
        return true;
    });
}

// BY LINES

bool read_text_file_by_line(const char* filename, line_read_handler_fn cb) {
    FILE_OPERATION("r", false, {
        char* line;
        while (assigned(line = read_line_from_stream(file))) {
            cb(line);
            ce_free(line);
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
            cb((unsigned char)b);
        } while ((b = getc(file)) != EOF);
        fclose(file);
        return true;
    });
}

