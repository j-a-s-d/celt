#include "gem_testing.h"
#include "werks_ansi.h"

#ifdef WERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/werks_ansi_test ../src/kewl.c ../src/werks_ansi.c werks_ansi_test.c");
#endif

int main(void) {
    Tests.begin("WeRKS ANSI");
    char* bs = ansi_blue("hello");
    char* bbs = ansi_bold(bs);
    Tests.run("ANSI ROUTINES", streq(bbs, ANSI_CODE_BOLD ANSI_CODE_BLUE "hello" ANSI_CODE_RESET ANSI_CODE_RESET));
    Tests.print("%s\n", bbs);
    free(bs);
    Tests.run("has_ansi_codes YES", has_ansi_codes(bbs));
    Tests.run("has_ansi_codes NO", !has_ansi_codes(TEST_STRING));
    char* sbbs = strip_ansi_codes(bbs);
    Tests.run("strip_ansi_codes", !has_ansi_codes(sbbs));
    Tests.print("%s\n", sbbs);
    free(bbs);
    free(sbbs);
    Tests.run("ANSI CONSTANTS", ANSI_CODE_UNDERLINED != NULL && strlen(ANSI_CODE_BOLD) > 0);
    Tests.print("[%sGREEN%s]\n", ANSI_CODE_GREEN, ANSI_CODE_RESET);
    printf(ANSI_CODE_BOLD ANSI_CODE_RED "DANGER: " ANSI_CODE_YELLOW ANSI_CODE_UNDERLINED "This is a test");
    puts(ANSI_CODE_RESET);
    return Tests.end();
}

