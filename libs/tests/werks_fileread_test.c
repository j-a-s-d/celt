#include "gem_testing.h"
#include "werks_fileread.h"

#ifdef WERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/werks_fileread_test ../src/kewl.c ../src/werks_fileread.c werks_fileread_test.c");
#endif

size_t chunk_size = 50;
size_t chunks_read = 0;
size_t last_chunk_size = 0;
bool chunks_read_flag = false;
bool lines_read_flag = false;
bool bytes_read_flag = false;

bool chunk_processor(char* chunk, size_t length) {
    if (chunk != NULL) chunks_read++;
    last_chunk_size = length;
    return true;
}

bool chunk_processor_with_reference(char* chunk, size_t length, void* ref) {
    if (chunk != NULL) chunks_read++;
    last_chunk_size = length;
    if (ref != NULL) *(bool*)ref = true;
    return true;
}

bool line_processor(char* line) {
    if (line != NULL) printf("%s\n", line);
    return true;
}

bool line_processor_with_reference(char* line, void* ref) {
    if (line != NULL) printf("%s %p\n", line, ref);
    if (ref != NULL) *(bool*)ref = true;
    return true;
}

bool byte_processor(unsigned char octet) {
    printf("%x", (uint8_t)octet);
    return true;
}

bool byte_processor_with_reference(unsigned char octet, void* ref) {
    printf("%x %p\n", (uint8_t)octet, ref);
    if (ref != NULL) *(bool*)ref = true;
    return true;
}

int main(void) {
    Tests.begin("WeRKS FILEREAD");
    Tests.run("read_text_file_by_line", read_text_file_by_line("./tests/werks_fileread_test.c", line_processor));
    Tests.run("read_text_file_by_line_with_reference", read_text_file_by_line_with_reference("./tests/werks_fileread_test.c", line_processor_with_reference, (void*)&lines_read_flag) && lines_read_flag);
    Tests.run("read_binary_file_by_byte", read_binary_file_by_byte("./tests/werks_fileread_test.c", byte_processor));
    Tests.run("read_binary_file_by_byte_with_reference", read_binary_file_by_byte_with_reference("./tests/werks_fileread_test.c", byte_processor_with_reference, (void*)&bytes_read_flag) && bytes_read_flag);
    Tests.run("read_binary_file_by_chunk", read_binary_file_by_chunk("./tests/werks_fileread_test.c", chunk_size, chunk_processor));
    Tests.print("%ld chunks of %ld bytes\n", chunks_read, chunk_size);
    Tests.print("last chunk size: %d\n", last_chunk_size);
    Tests.run("read_binary_file_by_chunk_with_reference", read_binary_file_by_chunk_with_reference("./tests/werks_fileread_test.c", chunk_size, chunk_processor_with_reference, (void*)&chunks_read_flag) && chunks_read_flag);
    return Tests.end();
}

