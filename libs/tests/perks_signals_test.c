#include "gem_testing.h"
#include "perks_signals.h"

#ifdef PERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/perks_signals_test ../src/kewl.c ../src/perks_signals.c perks_signals_test.c")
#endif

void on_signal_sent(int signal_sent, pid_t to_pid, bool result_got) {
    Tests.print("signal sent: %d to process %u (sucess: %s)\n", signal_sent, to_pid, strbool(result_got));
}

void sigint_handler(int signal) {
    UNUSED(signal);
    Signals.increment_and_get_count();
    Signals.safe_write("SIGINT received\n");
}

sig_try_setup();

void segv_handler(int signal, siginfo_t* info, void* ucontext) {
    UNUSED(signal);
    UNUSED(ucontext);
    Signals.increment_and_get_count();
    Signals.safe_write("Caught SIGSEGV at address ");
    Signals.safe_write_hex_ptr(info->si_addr);
    Signals.safe_write("\n");
    sig_try_jump();
}

__unoptimizable void test_try() {
    // NOTE: accessing like this will make valgrind complain
    sig_try({
        int* p = NULL;
        *p = 42;
    });
    Tests.run("count is 4", Signals.get_count() == 4);
    sig_try_finally({
        int* p = NULL;
        *p = 43;
    }, {
        Tests.print("Continue...\n");
    });
    Tests.run("count is 5", Signals.get_count() == 5);
    sig_try_except_finally({
        int* p = NULL;
        *p = 44;
    }, {
        Tests.print("Recovered from a null pointer exception!\n");
    }, {
        Tests.print("Continue again...\n");
    });
    Tests.run("count is 6", Signals.get_count() == 6);
}

int main(void) {
    Tests.begin("PeRKS SIGNALS");
    Tests.run("set_signal_handler", Signals.set_handler(SIGINT, sigint_handler, 0));
    Tests.run("ignore_signal", Signals.ignore(SIGINT));
    Tests.run("revert_signal_handler_to_default", Signals.revert_handler_to_default(SIGINT));
    Tests.run("get_on_signal_sent_handler", Signals.get_on_signal_sent() == NULL);
    Signals.set_on_signal_sent(on_signal_sent);
    Tests.run("set_on_signal_sent_handler", Signals.get_on_signal_sent() == on_signal_sent);
    Tests.run("reach_process", Signals.reach(getpid()));
    Tests.run("count is 0", Signals.get_count() == 0);
    Tests.run("setup SIGINT test", Signals.set_handler(SIGINT, sigint_handler, SA_RESTART)); // Automatically restart interrupted syscalls
    Tests.run("try to interrupt", Signals.send(getpid(), SIGINT));
    Tests.run("count is 1", Signals.get_count() == 1);
    Tests.run("ignore signal test", Signals.ignore(SIGINT));
    Tests.run("try to interrupt again", Signals.send(getpid(), SIGINT));
    Tests.run("count is 1", Signals.get_count() == 1);
    Tests.run("setup SIGINT test again", Signals.set_handler(SIGINT, sigint_handler, SA_RESTART)); // Automatically restart interrupted syscalls
    Tests.run("try to interrupt yet again", Signals.send(getpid(), SIGINT));
    Tests.run("count is 2", Signals.get_count() == 2);
    Tests.run("revert_signal_handler_to_original YES", Signals.revert_handler_to_original(SIGINT));
    Signals.set_on_signal_sent(NULL);
    Tests.run("removed on_signal_sent handler", Signals.get_on_signal_sent() == NULL);
    Tests.run("try to interrupt yet again", Signals.send(getpid(), SIGINT));
    Tests.run("revert_signal_handler_to_original NO", !Signals.revert_handler_to_original(SIGINT));
    Tests.run("block signal", Signals.block(SIGINT));
    Tests.run("and try to interrupt one more time", Signals.send(getpid(), SIGINT));
    Tests.run("revert signal block", Signals.revert_mask_to_last(SIGINT));
    Tests.run("set_signal_info_handler", Signals.set_info_handler(SIGSEGV, segv_handler));
    Tests.run("count is 2", Signals.get_count() == 2);
    Tests.run("send segmentation violation signal", Signals.send(getpid(), SIGSEGV));
    Tests.run("count is 3", Signals.get_count() == 3);
    test_try();
    Tests.run("revert_signal_handler_to_original YES", Signals.revert_handler_to_original(SIGSEGV));
    Tests.run("revert_signal_handler_to_original NO", !Signals.revert_handler_to_original(SIGSEGV));
    Signals.cleanup();
    return Tests.end();
}

