/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_debug-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

bool DEVELOPMENT = false;

void print_alignment_information(const void* ptr, size_t alignment) {
    uintptr_t addr = (uintptr_t)ptr;
    printf("Address: %p\n", ptr);
    printf("As decimal integer: %" PRIuPTR "\n", addr);
    printf("Modulo %zu: %" PRIuPTR "\n", alignment, addr % alignment);
    printf("Bitmask (0x%zx): %s\n", alignment - 1, (addr & (alignment - 1)) ? "Unaligned" : "Aligned");
}

void print_bytes_as_hex(const void* ptr, size_t size, size_t columns, const char* separator) {
    if (size == 0) return;
    const unsigned char* byte_ptr = (const unsigned char*)ptr;
    for (size_t i = 0; i < size; i++) {
        printf("%02X", byte_ptr[i]);
        // print separator if not the last byte in the row or the last byte overall
        if ((i + 1) % columns != 0 && i + 1 < size) {
            printf("%s", separator);
        } else // at end of column or end of data just print a newline
            printf("\n");
    }
}

