#include "gem_testing.h"
#include "gem_memcb.h"
#include <string.h>

#ifdef GEM_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/gem_memcb_test gem_memcb_test.c\n"
    "and under clang you need to include -fblocks and -lBlocksRuntime\n"
);
#endif

void print_and_fill(void* mem) {
    Tests.run("MEMCB", mem != NULL);
    memset(mem, 'X', 7);
    char* str = mem;
    str[7] = '\0';
    Tests.print("Memory allocated at %p, filled with 'X': %s\n", mem, str);
    // NOTE: remember not to free the pointer!
}

typedef struct {
    int x;
    int y;
} point_dt;

int main(void) {
    Tests.begin("GeM MEMCB");
    memcallback(8, memcb_proxy(print_and_fill)); // the proxy macro is provided for gcc/clang compatibility
    memcallback(32, NULL); // if no callback then nothing happens
    MEMCB(64, mem, Tests.print("Memory allocated at %p\n", mem));
    MEMCB_TYPED(16, char*, str, {
        Tests.run("MEMCB_TYPED", str != NULL);
        str = "123\0";
        Tests.print("Memory allocated at %p, with content: %s\n", (void*)str, str);
    });
    MEMCB_STRUCT(point_dt, point, {
        Tests.run("MEMCB_STRUCT", point != NULL);
        point->x = 1;
        point->y = 2;
        Tests.print("Memory allocated at %p, with size of %lu\n", (void*)point, sizeof(point_dt));
    });
    return Tests.end();
}

