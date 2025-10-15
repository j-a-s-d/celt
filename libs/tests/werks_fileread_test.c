#include "gem_testing.h"
#include "werks_fileread.h"

#ifdef WERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/werks_fileread_test ../src/kewl.c ../src/werks_fileread.c werks_fileread_test.c");
#endif

size_t chunk_size = 50;
size_t chunks_read = 0;
size_t last_chunk_size = 0;

void chunk_processor(char* chunk, size_t length) {
    if (chunk != NULL) chunks_read++;
    last_chunk_size = length;
}

void line_processor(char* line) {
    if (line != NULL) printf("%s\n", line);
}

void byte_processor(unsigned char octet) {
    printf("%x", (uint8_t)octet);
}

int main(void) {
    Tests.begin("WeRKS FILEREAD");
    Tests.run("read_text_file_by_line", read_text_file_by_line("./tests/werks_fileread_test.c", line_processor));
    Tests.run("read_binary_file_by_byte", read_binary_file_by_byte("./tests/werks_fileread_test.c", byte_processor));
    Tests.run("read_binary_file_by_chunk", read_binary_file_by_chunk("./tests/werks_fileread_test.c", chunk_size, chunk_processor));
    Tests.print("%ld chunks of %ld bytes\n", chunks_read, chunk_size);
    Tests.print("last chunk size: %d\n", last_chunk_size);
    return Tests.end();
}

