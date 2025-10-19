/**
 * C Extra Library
 */

#include "gem_testing.h"
#include <string.h>

#ifdef CE_HELP
CE_MESSAGE("\n\n*** compile with: -Wall -Wextra -Wfatal-errors -pedantic -I../include -o ../bin/ce_test ce_test.c\n"
    "  even with -std=c89 (ANSI C)");
#endif

static void test_defines() {
    printf("--- DEFINES\n");
    printf("--- * CPU Architecture\n");
    #ifdef __x86
    printf("x86\n");
    #endif
    #ifdef __arm
    printf("ARM\n");
    #endif
    #ifdef __32bits
    printf("32 bits\n");
    #endif
    #ifdef __64bits
    printf("64 bits\n");
    #endif
    printf("--- * OS Platform\n");
    #ifdef __unix_like
    printf("UNIX LIKE\n");
    #endif
    #ifdef __windows_like
    printf("WINDOWS LIKE\n");
    #endif
    printf("--- * C Version\n");
    #ifdef __c
    printf("C\n");
    #endif
    #ifdef __c89
    printf("C89\n");
    #endif
    #ifdef __c94
    printf("C94\n");
    #endif
    #ifdef __c99
    printf("C99\n");
    #endif
    #ifdef __c11
    printf("C11\n");
    #endif
    #ifdef __c17
    printf("C17\n");
    #endif
    #ifdef __c23
    printf("C23\n");
    #endif
    printf("--- * POSIX Version\n");
    #ifdef __posix90
    printf("POSIX 90\n");
    #endif
    #ifdef __posix93
    printf("POSIX 93\n");
    #endif
    #ifdef __posix95
    printf("POSIX 95\n");
    #endif
    #ifdef __posix01
    printf("POSIX 01\n");
    #endif
    #ifdef __posix08
    printf("POSIX 08\n");
    #endif
    #ifndef __posix_compliant
    printf("NOT POSIX COMPLIANT\n");
    #endif
    NOOP_LOOP;
    NOOP_STATEMENT;
    EMPTY_BLOCK;
}

static void test_polyfills() {
    size_t size = 4096;
    #define ALIGNMENT 64
    void* ptr = aligned_alloca(ALIGNMENT, size);
    printf("--- POLYFILLS\n");
    if (Tests.run("--- * aligned_alloca", ptr != NULL))
        printf("Allocated %lu bytes of memory at address %p with an alignment of %u via aligned_alloca\n", size, ptr, ALIGNMENT);
    if (Tests.run("--- * bool", __bool_true_false_are_defined && true))
        printf("bool is defined\n");
}

static void test_pointers() {
    void* p = NULL;
    void* r = &p;
    printf("--- POINTERS\n");
    Tests.run("--- * assigned", !assigned(NULL) && !assigned(p) && assigned(r));
    Tests.run("--- * both_assigned", both_assigned(r, &test_pointers));
}

static void test_memory() {
    STR_MALLOC(str, 4);
    STR_ALLOCA(str2, 4);
    strcpy(str, "hey");
    strcpy(str2, "bar");
    printf("--- MEMORY\n");
    Tests.run("--- * STR_MALLOC", (str != NULL) && str[0] == 'h' && str[1] == 'e' && str[2] == 'y');
    Tests.run("--- * STR_ALLOCA", (str2 != NULL) && str2[0] == 'b' && str2[1] == 'a' && str2[2] == 'r');
    free(str);
}

int main(void) {
    Tests.begin("Ce");
    test_defines(); /* platforms and versions */
    test_polyfills();
    test_pointers();
    test_memory();
    return Tests.end();
}

