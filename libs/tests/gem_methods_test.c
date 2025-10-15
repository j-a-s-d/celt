#include "gem_testing.h"
#include "gem_methods.h"
#include <stdlib.h>
#include <string.h>

#ifdef GEM_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/gem_methods_test gem_methods_test.c");
#endif

typedef struct {
    int x;
    int y;
    method_int_fn add;
    method_void_fn greeting;
    method_void_fn destroy;
} heap_struct_dt;

void use_heap_struct(heap_struct_dt* heap_struct) {
    heap_struct->greeting();
    Tests.print("Heap Struct's add(): %d\n", heap_struct->add(123));
    heap_struct->destroy();
}

typedef struct {
    int a;
    int b;
    method_int_fn add;
    method_void_fn greeting;
} stack_struct_dt;

void use_stack_struct(stack_struct_dt stack_struct) {
    stack_struct.greeting();
    Tests.print("Stack Struct's add(): %d\n", stack_struct.add(42));
}

void test_struct_methods() {
    // NOTE: when using method_of in an inline struct initialization while refering to the struct
    // instance itself clang warns since the initialization is not complete before its captured,
    // in this case you can just ignore the warning, in other cases you should go with a sequantial
    // initialization like in the heap struct example ahead
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wuninitialized"
    // setup stack struct (initializing inline, using method_of macro and passing by value)
    stack_struct_dt stack_struct = {
        1,
        2,
        method_of(stack_struct, int, (int c), { return this.a + this.b + c; }),
        method_of(stack_struct, void, (), { Tests.print("Stack Struct says: Hello Method!\n"); })
    };
    Tests.run("method_of [@stack&inlined-static-init](add)", assigned(stack_struct.add));
    Tests.run("method_of [@stack&inlined-static-init](greeting)", assigned(stack_struct.greeting));
    #pragma clang diagnostic pop
    use_stack_struct(stack_struct);
    // setup heap struct (initializing sequentially, using method macro and passing by ref)
    VAR_MALLOC(heap_struct, heap_struct_dt);
    heap_struct->x = 3;
    heap_struct->y = 4;
    method(heap_struct, add, int, (int z), { return this->x + this->y + z; });
    Tests.run("method [@heap&sequential-dynamic-init](add)", assigned(heap_struct->add));
    method(heap_struct, greeting, void, (), { Tests.print("Heap Struct says: Hello Method!\n"); });
    Tests.run("method [@heap&sequential-dynamic-init](greeting)", assigned(heap_struct->greeting));
    method(heap_struct, destroy, void, (), { free(this); });
    Tests.run("method [@heap&sequential-dynamic-init](destroy)", assigned(heap_struct->destroy));
    use_heap_struct(heap_struct);
}
int main(void) {
    Tests.begin("GeM METHODS");
    test_struct_methods();
    return Tests.end();
}

