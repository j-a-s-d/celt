#include "gem_testing.h"
#include "werks_dynvoke.h"

#ifdef WERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/werks_dynvoke_test ../src/kewl.c ../src/werks_dynvoke.c werks_dynvoke_test.c\n" \
    "and to add support for the calling of unregistered functions in unix-like systems just add\n" \
    "-rdynamic, and in some systems also -ldl is required, and yet in other setups also -D_GNU_SOURCE\n" \
    "invoke it as: ../bin/werks_dynvoke_test dbg_call param1 param2 param3")
#endif

int dbg_call(int argc, char* argv[]) {
    printf("argc: %d\n", argc);
    for (int i = 0; i < argc; i++)
        printf("argv[%d] = %s\n", i, argv[i]);
    return 0;
}
int show_argv0(__unused int argc, char* argv[]) {
    printf("%s\n", argv[0]);
    return 0; // avoid the unused-parameter warning
}
int show_argc(int argc, __unused char* argv[]) {
    printf("%d\n", argc);
    return 0;
}
int unregistered_show_argc(int argc, __unused char* argv[]) {
    printf("%d\n", argc);
    return 0;
}

void tests() {
    typedef struct { int A; } A_struct;
    A_struct custom_data = { 123 };
    Tests.run("has_function NULL", !dynvoke_has_function(NULL));
    Tests.run("has_function dbg_call", dynvoke_has_function(dbg_call));
    Tests.run("get_function_data show_argv0", dynvoke_get_function_data(show_argv0) == NULL);
    Tests.run("set_function_data show_argv0 &custom_data", dynvoke_set_function_data(show_argv0, &custom_data));
    Tests.run("get_function_data show_argv0 is &custom_data", dynvoke_get_function_data(show_argv0) == &custom_data);
    Tests.run("set_function_data show_argc &custom_data", dynvoke_set_function_data(show_argc, &custom_data));
    Tests.run("set_function_data show_argc NULL", dynvoke_set_function_data(show_argc, NULL));
    Tests.run("set_named_function_data show_argc &custom_data", dynvoke_set_named_function_data("show_argc", &custom_data));
    Tests.run("set_named_function_data foo &custom_data)", !dynvoke_set_named_function_data("foo", &custom_data));
    Tests.run("get_named_function_data show_argc is &custom_data", dynvoke_get_named_function_data("show_argc") == &custom_data);
    A_struct* data = (A_struct*)dynvoke_get_named_function_data("show_argc");
    Tests.run("get_named_function_data show_argc", data->A == 123);
    data->A = 456;
    Tests.run("get_named_function_data show_argc", (((A_struct*)dynvoke_get_named_function_data("show_argc"))->A == 456));
    Tests.run("has_named_function NULL", !dynvoke_has_named_function(NULL));
    Tests.run("has_named_function empty", !dynvoke_has_named_function(STRINGS_NOTHING));
    Tests.run("has_named_function foo", !dynvoke_has_named_function("foo"));
    Tests.run("has_named_function show_argc", dynvoke_has_named_function("show_argc"));
    Tests.run("has_named_function dbg_call", dynvoke_has_named_function("dbg_call"));
    Tests.run("execute_function NULL", dynvoke_execute_function(NULL).exit_value != 0);
    Tests.run("execute_function empty", dynvoke_execute_function(STRINGS_NOTHING).exit_value != 0);
    Tests.run("execute_function dbg_call", dynvoke_execute_function("dbg_call paramA paramB").exit_value == 0);
    dynvoke_unregister_functions();
    DYNVOKE_REGISTER(dbg_call);
    Tests.run("has_named_function show_argc", !dynvoke_has_named_function("show_argc"));
    Tests.run("has_named_function dbg_call", dynvoke_has_named_function("dbg_call"));
    Tests.run("has_function dbg_call", dynvoke_has_function(dbg_call));
    Tests.run("execute_function", dynvoke_execute_function("dbg_call paramA paramB paramC").exit_value == 0);
    Tests.run("execute_unregistered_function", dynvoke_execute_unregistered_function("unregistered_show_argc paramA paramB paramC").exit_value == 0);
    Tests.run("execute_unregistered_function", dynvoke_execute_unregistered_function("unregistered").exit_value == -1);
}

void print_result(dynvoke_function_result_dt r) {
    printf("Exit value: %d\n", r.exit_value);
    if (r.error_message != NULL) printf("Error: %s\n", r.error_message);
}

int main(int argc, const char* argv[]) {
    Tests.begin("WeRKS DYNVOKE");
    DYNVOKE_REGISTER(dbg_call);
    DYNVOKE_REGISTER(show_argv0);
    DYNVOKE_REGISTER(show_argc);
    AUTO_STRING(cl_args, string_array_join_range(argc, argv, 1, argc - 1, " "));
    if (!cl_args || !*cl_args) {
        printf("No function call provided.\nRunning tests...\n");
        tests();
    } else if (!dynvoke_has_named_function(argv[1])) {
        printf("Function not found.\n");
        #ifdef WERKS_DYNVOKE_ALLOW_UNREGISTERED
        printf("Trying to invoke unregistered %s()...\n", argv[1]);
        print_result(dynvoke_execute_unregistered_function(cl_args));
        #endif
    } else {
        printf("Invoking registered %s()...\n", argv[1]);
        print_result(dynvoke_execute_function(cl_args));
    }
    dynvoke_unregister_functions();
    return Tests.end();
}

