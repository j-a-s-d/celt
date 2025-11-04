#include "gem_testing.h"
#include "werks_program.h"

#ifdef WERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/werks_program_dtest ../src/kewl.c ../src/werks_program.c werks_program_dtest.c");
#endif

bool prg_before_main(werks_program_dt* prg, int args_count, const char* args_values[]) {
    Tests.print("---\nRunning program: %s\nEvent: on_before_main\nInput Args [%p]: %d\n", werks_program_get_created_timestamp(prg), (void*)args_values, args_count);
    return true;
}

int prg_main(werks_program_dt* prg) {
    nap(1000);
    elapsed_time_dt et = werks_program_get_elapsed_time(prg);
    Tests.print("Elapsed time (W D HH:MM:SS): %d weeks, %d days, %02d:%02d:%02d\n",
           et.weeks, et.days, et.hours, et.minutes, et.seconds);
    nap(1000);
    if (!werks_program_has_finished(prg))
        Tests.print("---\nRunning program: %s\nEvent: on_run_main\n", werks_program_get_created_timestamp(prg));
    return 0;
}

void prg_after_main(werks_program_dt* prg, int exit_value) {
    Tests.print("---\nRunning program: %s\nEvent: on_after_main\nExit value: %d\n", werks_program_get_created_timestamp(prg), exit_value);
}

int main(int argc, const char* argv[]) {
    Tests.begin("WeRKS PROGRAM");
    werks_program_dt* prg = werks_program_create();
    Tests.run("werks_program_create", assigned(prg));
    Tests.run("werks_program_get_component NULL", werks_program_get_component(NULL) == NULL);
    Tests.run("werks_program_get_component", assigned(werks_program_get_component(prg)));
    Tests.run("werks_program_get_input_argc NULL", werks_program_get_input_argc(NULL) == -1);
    Tests.run("werks_program_get_input_argv NULL", werks_program_get_input_argv(NULL) == NULL);
    Tests.run("werks_program_get_input_argc NO", werks_program_get_input_argc(prg) == -1);
    Tests.run("werks_program_get_input_argv NO", werks_program_get_input_argv(prg) == NULL);
    werks_program_set_input_args(prg, argc, argv);
    Tests.run("werks_program_get_input_argc YES", werks_program_get_input_argc(prg) > -1);
    Tests.run("werks_program_get_input_argv YES", assigned(werks_program_get_input_argv(prg)));
    Tests.run("werks_program_get_context NULL", werks_program_get_context(NULL) == NULL);
    Tests.run("werks_program_get_context NO", werks_program_get_context(prg) == NULL);
    werks_program_set_context(prg, prg);
    Tests.run("werks_program_get_context YES", assigned(werks_program_get_context(prg)));
    Tests.run("werks_program_get_created_timestamp NULL", werks_program_get_created_timestamp(NULL) == NULL);
    const char* s = werks_program_get_created_timestamp(prg);
    Tests.run("werks_program_get_created_timestamp", has_content(s));
    Tests.print("Created program: %s\n", s);
    Tests.run("werks_program_get_on_before_main NULL", werks_program_get_on_before_main(NULL) == NULL);
    Tests.run("werks_program_get_on_before_main NO", werks_program_get_on_before_main(prg) == NULL);
    werks_program_set_on_before_main(prg, prg_before_main);
    Tests.run("werks_program_set_on_before_main YES", werks_program_get_on_before_main(prg) == prg_before_main);
    Tests.run("werks_program_get_on_after_main NULL", werks_program_get_on_after_main(NULL) == NULL);
    Tests.run("werks_program_get_on_after_main NO", werks_program_get_on_after_main(prg) == NULL);
    werks_program_set_on_after_main(prg, prg_after_main);
    Tests.run("werks_program_set_on_after_main YES", werks_program_get_on_after_main(prg) == prg_after_main);
    const char* args_values[] = {"this", "is", "a", "test"};
    werks_program_set_input_args(prg, 4, args_values);
    Tests.print("Executed without main: %s\n", strbool(werks_program_run(prg)));
    Tests.run("werks_program_get_main NULL", werks_program_get_main(prg) == NULL);
    Tests.run("werks_program_get_main", werks_program_get_main(prg) == NULL);
    werks_program_set_main(prg, prg_main);
    Tests.run("werks_program_set_main", werks_program_get_main(prg) == prg_main);
    Tests.run("werks_program_run NULL", !werks_program_run(NULL));
    Tests.run("werks_program_run", werks_program_run(prg));
    elapsed_time_dt et = werks_program_get_elapsed_time(NULL);
    Tests.run("werks_program_get_elapsed_time NULL", elapsed_time_equal(et, DEFAULT_ELAPSED_TIME));
    et = werks_program_get_elapsed_time(prg);
    Tests.run("werks_program_get_elapsed_time", !elapsed_time_equal(et, DEFAULT_ELAPSED_TIME));
    Tests.print("Elapsed time (W D HH:MM:SS): %d weeks, %d days, %02d:%02d:%02d\n",
           et.weeks, et.days, et.hours, et.minutes, et.seconds);
    Tests.run("werks_program_get_exit_value NULL", werks_program_get_exit_value(NULL) == -1);
    Tests.run("werks_program_get_exit_value", werks_program_get_exit_value(prg) == 0);
    Tests.run("werks_program_destroy NULL", werks_program_destroy(NULL) == -1);
    Tests.run("werks_program_destroy", werks_program_destroy(prg) == 0);
    return Tests.end();
}

