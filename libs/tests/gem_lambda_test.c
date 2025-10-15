#include "gem_testing.h"
#include "gem_lambda.h"
#include <stdlib.h>
#include <string.h>

#ifdef GEM_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/gem_lambda_test gem_lambda_test.c");
#endif

void test_lambda_functions() {
    lambda_void_fn λ = lambda_void((), {
        lambda_pointer_fn Lpointer = lambda_pointer((), { return (void *)&test_lambda_functions; });
        Tests.run("lambda_pointer", Lpointer() == (void*)&test_lambda_functions);
        lambda_intptr_fn Lintptr = lambda_intptr((), { return (intptr_t)&test_lambda_functions; });
        Tests.run("lambda_intptr", Lintptr() == (intptr_t)&test_lambda_functions);
        lambda_uintptr_fn Luintptr = lambda_uintptr((), { return (uintptr_t)&test_lambda_functions; });
        Tests.run("lambda_uintptr", Luintptr() == (uintptr_t)&test_lambda_functions);
        lambda_string_fn Lstring = lambda_string((const char* s), { return strcmp(s,"hey")==0?"Hello":"World"; });
        Tests.run("lambda_string", strcmp(Lstring("hey"), "Hello") == 0);
        Tests.run("lambda_char", lambda_char((), { return (char)'\n'; })() == '\n');
        Tests.run("lambda_unsigned_char", lambda_unsigned_char((), { return (unsigned char)3; })() == 3);
        Tests.run("lambda_int", lambda_int((int x, int y), { return x + y; })(1, 2) == 3);
        Tests.run("lambda_unsigned_int", lambda_unsigned_int((), { return (unsigned int)3; })() == 3);
        Tests.run("lambda_long", lambda_long((long x, long y), { return x + y; })(1, 2) == 3);
        Tests.run("lambda_unsigned_long", lambda_unsigned_long((), { return (unsigned long)3; })() == 3);
        lambda_long_long_fn Llonglong = lambda_long_long((long long x, long long y), { return x + y; });
        Tests.run("lambda_long_long", Llonglong(1, 2) == 3);
        Tests.run("lambda_unsigned_long_long", lambda_unsigned_long_long((), { return (unsigned long long)3; })() == 3);
        Tests.run("lambda_int8", lambda_int8((int8_t x, int8_t y), { return (int8_t)(x + y); })(1, 2) == 3);
        Tests.run("lambda_uint8", lambda_uint8((), { return (uint8_t)3; })() == 3);
        Tests.run("lambda_int16", lambda_int16((int16_t x, int16_t y), { return (int16_t)(x + y); })(1, 2) == 3);
        Tests.run("lambda_uint16", lambda_uint16((), { return (uint16_t)3; })() == 3);
        Tests.run("lambda_int32", lambda_int32((int32_t x, int32_t y), { return (int32_t)(x + y); })(1, 2) == 3);
        Tests.run("lambda_uint32", lambda_uint32((), { return (uint32_t)3; })() == 3);
        Tests.run("lambda_int64", lambda_int64((int64_t x, int64_t y), { return (int64_t)(x + y); })(1, 2) == 3);
        Tests.run("lambda_uint64", lambda_uint64((), { return (uint64_t)3; })() == 3);
        Tests.run("lambda_float", lambda_float((float x, float y), { return x + y; })(0.0f, 0.0f) == 0.0f);
        Tests.run("lambda_double", lambda_double((double x, double y), { return x + y; })(0.0, 0.0) == 0.0);
        Tests.run("lambda_long_double", lambda_long_double((), { return (long double)0.0; })() == 0.0);
        Tests.run("lambda_bool", lambda_bool((), { return (bool)true; })() == true);
        Tests.run("lambda_ pointer", lambda_(void*, (), NULL)() == NULL);
        Tests.run("lambda_ int", lambda_(int, (int x, int y), x + y)(12, 34) == 46);
    });
    Tests.run("lambda_void", λ != NULL);
    if (λ) λ();
}

#if defined(__GNUC__) && !defined(__clang__)
void test_gcc_lambda_functions() {
    lambda_void_fn λ = lambda$void(() {
        Tests.run("lambda$void", λ != NULL);
        lambda_pointer_fn Lpointer = lambda$pointer(() { return &test_lambda_functions; });
        Tests.run("lambda$pointer", Lpointer() == &test_lambda_functions);
        lambda_intptr_fn Lintptr = lambda$intptr(() { return (intptr_t)&test_lambda_functions; });
        Tests.run("lambda$intptr", Lintptr() == (intptr_t)&test_lambda_functions);
        lambda_uintptr_fn Luintptr = lambda$uintptr(() { return (uintptr_t)&test_lambda_functions; });
        Tests.run("lambda$uintptr", Luintptr() == (uintptr_t)&test_lambda_functions);
        lambda_string_fn Lstring = lambda$string((const char* s) { return strcmp(s,"hey")==0?"Hello":"World"; });
        Tests.run("lambda$string", strcmp(Lstring("hey"), "Hello") == 0);
        Tests.run("lambda$char", lambda$char(() { return '\n'; })() == '\n');
        Tests.run("lambda$unsigned_char", lambda$unsigned_char(() { return 3; })() == 3);
        Tests.run("lambda$int", lambda$int((int x, int y) { return x + y; })(1, 2) == 3);
        Tests.run("lambda$unsigned_int", lambda$unsigned_int(() { return 3; })() == 3);
        Tests.run("lambda$long", lambda$long((long x, long y) { return x + y; })(1, 2) == 3);
        Tests.run("lambda$unsigned_long", lambda$unsigned_long(() { return 3; })() == 3);
        lambda_long_long_fn Llonglong = lambda$long_long((long long x, long long y) { return x + y; });
        Tests.run("lambda$long_long", Llonglong(1, 2) == 3);
        Tests.run("lambda$unsigned_long_long", lambda$unsigned_long_long(() { return 3; })() == 3);
        Tests.run("lambda$int8", lambda$int8((int8_t x, int8_t y) { return x + y; })(1, 2) == 3);
        Tests.run("lambda$uint8", lambda$uint8(() { return 3; })() == 3);
        Tests.run("lambda$int16", lambda$int16((int16_t x, int16_t y) { return x + y; })(1, 2) == 3);
        Tests.run("lambda$uint16", lambda$uint16(() { return 3; })() == 3);
        Tests.run("lambda$int32", lambda$int32((int32_t x, int32_t y) { return x + y; })(1, 2) == 3);
        Tests.run("lambda$uint32", lambda$uint32(() { return 3; })() == 3);
        Tests.run("lambda$int64", lambda$int64((int64_t x, int64_t y) { return x + y; })(1, 2) == 3);
        Tests.run("lambda$uint64", lambda$uint64(() { return 3; })() == 3);
        Tests.run("lambda$float", lambda$float((float x, float y) { return x + y; })(0.0f, 0.0f) == 0.0f);
        Tests.run("lambda$double", lambda$double((double x, double y) { return x + y; })(0.0, 0.0) == 0.0);
        Tests.run("lambda$long_double", lambda$long_double(() { return 0.0; })() == 0.0);
        Tests.run("lambda$bool", lambda$bool(() { return true; })() == true);
        Tests.run("lambda$", lambda$(void*, () { return NULL; })() == NULL);
        Tests.run("lambda$ int", lambda$(int, (int x, int y) { return x + y; })(12, 34) == 46);
    });
    if (λ) λ();
}
#endif

int main(void) {
    Tests.begin("GeM LAMBDA");
    lambda_void((), { puts("Lambda functions test begin!"); })();
    test_lambda_functions();
#if defined(__GNUC__) && !defined(__clang__)
    test_gcc_lambda_functions();
#endif
    lambda_void_fn L = lambda_once(void, (), { puts("Lambda functions test end!"); });
    L(); // puts
    L(); // puts nothing
    return Tests.end();
}

