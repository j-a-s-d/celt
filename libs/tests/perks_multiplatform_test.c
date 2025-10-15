#define GEM_TESTING_COMPLEX
#include "gem_testing.h"
#include "perks_multiplatform.h"

#ifdef PERKS_HELP
CE_MESSAGE("compile with: -std=c11 -Wall -Wfatal-errors -I../include -I../src -o ../bin/perks_multiplatform_test ../src/kewl.c ../src/perks_multiplatform.c perks_multiplatform_test.c")
#endif

void test_debug(void) {
    int x = 999;
    int y = debug(x);
    if (x != y) printf("debug ERROR");
    DEVELOPMENT = true;
    int z = debug(x);
    if (x != z) printf("debug ERROR");
    DEVELOPMENT = false;
    debug(x);
}

#define EXPECTED_DEBUG_OUTPUT "999\n"

char* s = "test";
const char* cs = "testing";
void* p = &s;
const void* cp = &cs;

void test_echo(void) {
    echo(TEST_CHAR);
    echo(TEST_SIGNED_CHAR);
    echo(TEST_UNSIGNED_CHAR);
    echo(TEST_SHORT);
    echo(TEST_UNSIGNED_SHORT);
    echo(TEST_FLOAT);
    echo(TEST_DOUBLE);
    echo(TEST_LONG_DOUBLE);
    echo(TEST_FLOAT_COMPLEX);
    echo(TEST_DOUBLE_COMPLEX);
    echo(TEST_LONG_DOUBLE_COMPLEX);
    echo(TEST_INT);
    echo(TEST_UNSIGNED_INT);
    echo(TEST_LONG_INT);
    echo(TEST_UNSIGNED_LONG_INT);
    echo(TEST_LONG_LONG_INT);
    echo(TEST_UNSIGNED_LONG_LONG_INT);
    echo(TEST_BOOL);
    echo(s);
    echo(cs);
    echo(p);
    echo(cp);
}

#define EXPECTED_ECHO_OUTPUT "c\n" \
    "-12\n" \
    "250\n" \
    "-123\n" \
    "456\n" \
    "123.449997\n" \
    "123.450000\n" \
    "3.141592653589793239\n" \
    "1.20 +3.40i\n" \
    "5.60 +7.80i\n" \
    "9.00 +1.10i\n" \
    "-123456\n" \
    "123456\n" \
    "-1234567890\n" \
    "1234567890\n" \
    "-1234567890123456789\n" \
    "12345678901234567890\n" \
    "true\n" \
    "test\n" \
    "testing\n"

int main(void) {
    Tests.begin("PeRKS MULTIPLATFORM");
    const char* tmp_filename = "kewl_stdout_capture.tmp";
    redirected_stdout_call(test_echo, tmp_filename);
    char* captured_output = read_file(tmp_filename);
    Tests.run("echo", starts_with(captured_output, EXPECTED_ECHO_OUTPUT));
    Tests.print("captured:\n%s", captured_output);
    free(captured_output);
    Tests.run("typename", streq(typename(s), "char*"));
    Tests.print("%s\n", typename(s));
    Tests.run("typename", streq(typename(cs), "const char*"));
    Tests.print("%s\n", typename(cs));
    Tests.run("typename", streq(typename(p), "void*"));
    Tests.print("%s\n", typename(p));
    Tests.run("typename", streq(typename(cp), "const void*"));
    Tests.print("%s\n", typename(cp));
    Tests.run("typename", streq(typename(TEST_BOOL), "_Bool"));
    Tests.print("%s\n", typename(TEST_BOOL));
    Tests.run("typename", streq(typename(TEST_FLOAT), "float"));
    Tests.print("%s\n", typename(TEST_FLOAT));
    Tests.run("typename", streq(typename(TEST_DOUBLE), "double"));
    Tests.print("%s\n", typename(TEST_DOUBLE));
    Tests.run("typename", streq(typename(TEST_LONG_DOUBLE), "long double"));
    Tests.print("%s\n", typename(TEST_LONG_DOUBLE));
    Tests.run("typename", streq(typename(TEST_SHORT), "short"));
    Tests.print("%s\n", typename(TEST_SHORT));
    Tests.run("typename", streq(typename(TEST_UNSIGNED_SHORT), "unsigned short"));
    Tests.print("%s\n", typename(TEST_UNSIGNED_SHORT));
    Tests.run("typename", streq(typename(TEST_INT), "int"));
    Tests.print("%s\n", typename(TEST_INT));
    Tests.run("typename", streq(typename(TEST_UNSIGNED_INT), "unsigned int"));
    Tests.print("%s\n", typename(TEST_UNSIGNED_INT));
    Tests.run("typename", streq(typename(TEST_LONG_INT), "long int"));
    Tests.print("%s\n", typename(TEST_LONG_INT));
    Tests.run("typename", streq(typename(TEST_UNSIGNED_LONG_INT), "unsigned long int"));
    Tests.print("%s\n", typename(TEST_UNSIGNED_LONG_INT));
    Tests.run("typename", streq(typename(TEST_LONG_LONG_INT), "long long int"));
    Tests.print("%s\n", typename(TEST_LONG_LONG_INT));
    Tests.run("typename", streq(typename(TEST_UNSIGNED_LONG_LONG_INT), "unsigned long long int"));
    Tests.print("%s\n", typename(TEST_UNSIGNED_LONG_LONG_INT));
    Tests.run("typename", streq(typename(TEST_FLOAT_COMPLEX), "float complex"));
    Tests.print("%s\n", typename(TEST_FLOAT_COMPLEX));
    Tests.run("typename", streq(typename(TEST_DOUBLE_COMPLEX), "double complex"));
    Tests.print("%s\n", typename(TEST_DOUBLE_COMPLEX));
    Tests.run("typename", streq(typename(TEST_LONG_DOUBLE_COMPLEX), "long double complex"));
    Tests.print("%s\n", typename(TEST_LONG_DOUBLE_COMPLEX));
    redirected_stdout_call(test_debug, tmp_filename);
    captured_output = read_file(tmp_filename);
    Tests.run("debug", starts_with(captured_output, EXPECTED_DEBUG_OUTPUT));
    Tests.print("captured:\n%s", captured_output);
    free(captured_output);
    remove(tmp_filename);
    unless(false) println();
    return Tests.end();
}

