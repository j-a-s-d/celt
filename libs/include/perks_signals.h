/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: PeRKS SIGNALS
 * File: perks_signals.h
 * Brief: signals management
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "kewl.h"

#define PERKS_SIGNALS

#if !defined(__unix_like)
#error "PeRKS SIGNALS requires the a Unix-like system to work."
#endif

#include <unistd.h>
#include <signal.h>

#if !defined(_GNU_SOURCE)
typedef void (*sighandler_t)(int signal);
#endif
typedef void (*sighandler_siginfo_t)(int signal, siginfo_t* info, void* ucontext);

// PeRKS.SIGNALS -- General

// Function to safely write a string to the console from a signal handler.
bool safe_signal_write(const char* message);
// Function to safely write a pointer as hex to the console from a signal handler.
bool safe_signal_write_hex_ptr(void* ptr);

// Sets the custom counter of signals.
void set_signals_count(int amount);
// Gets the custom counter of signals.
int get_signals_count(void);
// Increments and get the custom counter of signals.
int increment_and_get_signals_count(void);

void signals_cleanup(void);

// PeRKS.SIGNALS -- Receiving

// Sets the signal handler for the specified signal.
bool set_signal_handler(int signal, sighandler_t handler, int flags);
// Sets the signal handler with info (SA_SIGINFO flag automatically included) for the specified signal.
bool set_signal_info_handler(int signal, sighandler_siginfo_t handler);
// Reverts the signal handler for the specified signal to the original handler it had before calling set_signal_handler (if any).
bool revert_signal_handler_to_original(int signal);
// Reverts the signal handler for the specified signal to the default action.
bool revert_signal_handler_to_default(int signal);
// Sets the program to ignore the specified signal (if possible).
bool handler_ignore_signal(int signal);
// Block the specified signal (it will be queued until it gets unblocked).
bool mask_block_signal(int signal);
// Reverts the signal mask to the last replaced by block_signal.
bool revert_signal_mask_to_last(int signal);

// PeRKS.SIGNALS -- Sending

typedef void (*on_signal_sent_t)(int signal_sent, pid_t to_pid, bool result_got);
// Sets the on_signal_sent event handler.
void set_on_signal_sent_handler(on_signal_sent_t handler);
// Gets the on_signal_sent event handler.
on_signal_sent_t get_on_signal_sent_handler(void);

// Sends the specified signal to the specified process.
bool send_signal(pid_t pid, int signal);
// Checks if the specified process exists and can receive signals.
bool reach_process(pid_t pid);

// PeRKS.SIGNALS -- SIGTRY, signal macros to allow try-like logic

// NOTE: be sure to use NO_OPTIMIZE attribute in your functions for this to work with all -O levels

#include <setjmp.h>

// NOTE: use it at top-level just once
#define sig_try_setup() \
    static sigjmp_buf sig_jump_buffer; \
    static bool sig_jump_initialized = false

// NOTE: use it inside the signal handler
#define sig_try_jump() \
    if (sig_jump_initialized) \
        siglongjmp(sig_jump_buffer, 1);

// NOTE: use it in your code
#define sig_try_except_finally(try_blk, except_blk, finally_blk) \
    if (sigsetjmp(sig_jump_buffer, 1) == 0) {\
        sig_jump_initialized = true; \
        try_blk \
    } else { \
        except_blk \
    } \
    finally_blk

// NOTE: use it in your code
#define sig_try_finally(try_blk, finally_blk) \
    sig_try_except_finally(try_blk, {}, finally_blk)

// NOTE: use it in your code
#define sig_try(try_blk) \
    sig_try_except_finally(try_blk, {}, {})

static const struct {
    // services
    bool (*const safe_write)(const char* message);
    bool (*const safe_write_hex_ptr)(void* ptr);
    void (*const set_count)(int amount);
    int (*const get_count)(void);
    int (*const increment_and_get_count)(void);
    void (*const cleanup)(void);
    // handlers
    bool (*const set_handler)(int signal, sighandler_t handler, int flags);
    bool (*const set_info_handler)(int signal, sighandler_siginfo_t handler);
    bool (*const revert_handler_to_original)(int signal);
    bool (*const revert_handler_to_default)(int signal);
    bool (*const ignore)(int signal);
    // masks
    bool (*const block)(int signal);
    bool (*const revert_mask_to_last)(int signal);
    // sending
    void (*const set_on_signal_sent)(on_signal_sent_t handler);
    on_signal_sent_t (*const get_on_signal_sent)(void);
    bool (*const send)(pid_t pid, int signal);
    bool (*const reach)(pid_t pid);
} Signals = {
    safe_signal_write,
    safe_signal_write_hex_ptr,
    set_signals_count,
    get_signals_count,
    increment_and_get_signals_count,
    signals_cleanup,
    set_signal_handler,
    set_signal_info_handler,
    revert_signal_handler_to_original,
    revert_signal_handler_to_default,
    handler_ignore_signal,
    mask_block_signal,
    revert_signal_mask_to_last,
    set_on_signal_sent_handler,
    get_on_signal_sent_handler,
    send_signal,
    reach_process
};

// Well-Known Signals Quick Reference Appendix
// SIGSEGV: Invalid memory reference (segmentation fault) -- ANSI
// SIGTERM: Termination request (default signal sent by kill) -- ANSI
// SIGINT: Interrupt from keyboard (Ctrl+C) -- ANSI
// SIGILL: Illegal instruction -- ANSI
// SIGABRT: Abort signal from abort() call due to critical errors like failed assertions or heap corruption -- ANSI
// SIGFPE: Floating-point exception (e.g., division by zero) -- ANSI
// SIGQUIT: Quit from keyboard (Ctrl+\) -- POSIX
// SIGTRAP: Trace/breakpoint trap (used by debuggers) -- POSIX
// SIGHUP: Hangup detected on controlling terminal or death of controlling process -- POSIX
// SIGKILL: Kill signal (cannot be caught or ignored) -- POSIX
// SIGUSR1: User-defined signal 1 -- POSIX
// SIGUSR2: User-defined signal 2 -- POSIX
// SIGPIPE: Broken pipe: write to pipe with no readers -- POSIX
// SIGALRM: Alarm clock (timer expired) -- POSIX
// SIGCHLD: Child process stopped or terminated -- POSIX
// SIGCONT: Continue executing if stopped -- POSIX
// SIGSTOP: Stop process (cannot be caught or ignored) -- POSIX
// SIGTSTP: Terminal stop signal (Ctrl+seh) -- POSIX
// SIGTTIN: Background process attempting read from tty -- POSIX
// SIGTTOU: Background process attempting write to tty -- POSIX
// SIGSYS: Bad argument to system call -- POSIX
// SIGUNUSED: -- POSIX (same as SIGUNUSED)
// SIGINFO: -- POSIX (same as SIGPWR)
// SIGSTKFLT: Stack fault on coprocessor -- Linux-specific
// SIGIOT: IOT Trap -- BSD
// SIGBUS: Bus error (bad memory access) -- BSD
// SIGURG: Urgent condition on socket -- BSD
// SIGXCPU: CPU time limit exceeded -- BSD
// SIGXFSZ: File size limit exceeded -- BSD
// SIGVTALRM: Virtual timer expired -- BSD
// SIGPROF: Profiling timer expired -- BSD
// SIGIO: I/O now possible -- BSD
// SIGEMT: Emulator trap (hardware-specific, rarely used) -- BSD
// SIGWINCH: Window size change -- BSD/Sun
// SIGPWR: Power failure or restart -- System V (same as SIGINFO)
// SIGPOLL: Pollable event -- System V (same as SIGIO)
// SIGCLD: Child status changed -- System V (synonymous with SIGCHLD)
// SIGWAITING: All LWPs blocked -- Solaris-specific
// SIGLWP: Special signal used by thread library -- Solaris-specific
// SIGFREEZE: Checkpoint freeze -- Solaris-specific
// SIGTHAW: Checkpoint thaw -- Solaris-specific
// SIGCANCEL: Thread cancellation signal -- Solaris-specific
// SIGLOST: Resource lost (file lock lost) -- Solaris-specific

#ifdef __cplusplus
}
#endif

