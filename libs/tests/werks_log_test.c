#include "gem_testing.h"
#include "werks_log.h"

#ifdef WERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/werks_log_test ../src/kewl.c ../src/werks_log.c werks_log_test.c");
#endif

void on_flush_error(const int err) {
    printf("Could not flush the log file (%d error).\n", err);
}

int main(int argc, char* argv[]) {
    Tests.begin("WeRKS LOG");
    if (!werks_log_init(NULL)) { // logs to console
        printf("Could not log to the console.");
        return -1;
    }
    Tests.run("is logging? YES", werks_log_is_logging());
    Tests.run("logging to the console? YES", werks_log_in_console());
    werks_log_info("Logging directly to the console (bypassing any capture attempt)");
    werks_log_close();
    __auto char* filename = concat_strings(argv[argc * 0], LOG_EXTENSION);
    Tests.run("is logging? NO", !werks_log_is_logging());
    if (!werks_log_init(filename)) {
        printf("Could not create the log file.");
        free(filename);
        return -1;
    }
    Tests.run("is logging? YES", werks_log_is_logging());
    werks_log_set_on_flush_fail(on_flush_error);
    werks_log_debug("Application %s...", "starting");
    werks_log_set_entry_prefix("#PREFIX#");
    werks_log_info("Sample info");
    werks_log_set_entry_suffix("#SUFFIX#");
    werks_log_warning("Sample warning");
    werks_log_set_entry_prefix(NULL); // reverts to default
    werks_log_error("Sample error");
    werks_log_set_entry_suffix(NULL); // reverts to default
    werks_log_set_entry_fields_separator("$$");
#ifndef KEWL_DISABLE_COMPONENT
    Log.component_info(NULL, "Nothing happens...");
    kewl_component_dt* tc = kewl_component_create(NULL, "TestComponent");
    Log.component_info(tc, "Here is the component logging some info...");
    kewl_component_destroy(tc);
#endif
    werks_log_fatal("Application %s...", "ending");
    werks_log_close();
    Tests.run("is logging? NO", !werks_log_is_logging());
    Tests.print("entry prefix: %s\n", werks_log_get_entry_prefix());
    Tests.print("entry suffix: %s\n", werks_log_get_entry_suffix());
    Tests.print("entry fields separator: %s\n", werks_log_get_entry_fields_separator());
    __auto char* contents = read_file(filename);
    Tests.run("log contents", has_content(contents));
    Tests.print("filename: %s\n", werks_log_get_filename());
    Tests.print("contents (%p):\n%s\n", contents, contents);
    remove(filename);
    werks_log_set_entry_fields_separator(NULL); // reverts to default
    if (!werks_log_init(NULL)) { // logs to console
        printf("Could not log to the console.");
        return -1;
    }
    Tests.run("is logging? YES", werks_log_is_logging());
    Tests.run("logging to the console again? YES", werks_log_in_console());
    werks_log_add_ignored_level(LOG_LEVEL_INFO);
    Tests.run("ignored level? YES", werks_log_has_level_ignored(LOG_LEVEL_INFO));
    werks_log_info("This is ignored!");
    werks_log_remove_ignored_level(LOG_LEVEL_INFO);
    Tests.run("ignored level? NO", !werks_log_has_level_ignored(LOG_LEVEL_INFO));
    werks_log_info("Logging to the console again");
    werks_log_close();
    Tests.run("is logging? NO", !werks_log_is_logging());
    werks_log_info("Not logged at all");
    return Tests.end();
}

