/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: PeRKS SIGNALS
 * File: perks_signals.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */
 
#include "perks_signals.h"

#ifndef PERKS_SIGNALS_OLD_HANDLERS_ARRAY_INITIAL_CAPACITY
    #define PERKS_SIGNALS_OLD_HANDLERS_ARRAY_INITIAL_CAPACITY 16
#endif

#ifndef PERKS_SIGNALS_OLD_MASKS_ARRAY_INITIAL_CAPACITY
    #define PERKS_SIGNALS_OLD_MASKS_ARRAY_INITIAL_CAPACITY 16
#endif

struct old_mask_t {
    int signal;
    sigset_t* set;
};
struct old_handler_t {
    int signal;
    bool is_info;
    struct sigaction* action;
};
unit_internal({
    kewl_ptrholder_dt* old_masks;
    kewl_ptrholder_dt* old_handlers;
    on_signal_sent_t on_signal_sent;
    volatile sig_atomic_t count;
}) = {NULL, NULL, NULL, 0};

void signals_cleanup(void) {
    kewl_ptrholder_destroy(internal_.old_masks);
    kewl_ptrholder_destroy(internal_.old_handlers);
}

void set_on_signal_sent_handler(on_signal_sent_t handler) {
    internal_.on_signal_sent = handler;
}

on_signal_sent_t get_on_signal_sent_handler(void) {
    return internal_.on_signal_sent;
}

int get_signals_count(void) {
    return internal_.count;
}

void set_signals_count(int amount) {
    internal_.count = amount;
}

int increment_and_get_signals_count(void) {
    return ++internal_.count;
}

bool safe_signal_write(const char* message) {
    char buffer[512];
    size_t index = 0;
    while (message[index] != CHARS_NULL && index < sizeof(buffer) - 1) {
        buffer[index] = message[index];
        index++;
    }
    buffer[index] = CHARS_NULL;
    return write(STDOUT_FILENO, buffer, index) != -1;
}

bool safe_signal_write_hex_ptr(void* ptr) {
    uintptr_t val = (uintptr_t)ptr;
    int ptr_sz = (int)(sizeof(uintptr_t) * 2);
    int pfx_sz = 2; // 0 for no prefix
    char buf[pfx_sz + ptr_sz + 1];
    int idx;
    if (pfx_sz == 2) {
        buf[0] = CHARS_NUMBER_ZERO;
        buf[1] = CHARS_LOWERCASE_X;
    }
    // convert each nibble to hex, starting from the highest nibble
    for (idx = 0; idx < ptr_sz; idx++) {
        int shift = ((ptr_sz - 1 - idx) * NIBBLE_BITS);
        buf[pfx_sz + idx] = HEX_DIGITS[(val >> shift) & 0xF];
    }
    buf[pfx_sz + ptr_sz] = CHARS_NULL;
    return safe_signal_write(buf);
}

static inline void setup_sigaction_struct(struct sigaction* sa, int flags) {
    memset(sa, 0, sizeof(struct sigaction)); // zero out the sigaction struct to clear garbage
    sigemptyset(&(sa->sa_mask)); // block no additional signals during handler
    sa->sa_flags = flags; // set flags
}

static bool apply_signal_action(int signal, sighandler_t handler, int flags, struct old_handler_t* old_handler) {
    struct sigaction sa;
    setup_sigaction_struct(&sa, flags);
    sa.sa_handler = handler; // set the handler function
    // install the handler for the supplied signal number
    return sigaction(signal, &sa, old_handler == NULL ? NULL : old_handler->action) != -1;
}

static bool apply_signal_info_action(int signal, sighandler_siginfo_t handler, struct old_handler_t* old_handler) {
    struct sigaction sa;
    setup_sigaction_struct(&sa, SA_SIGINFO);
    sa.sa_sigaction = handler; // set the info handler function
    // install the info handler for the supplied signal number
    return sigaction(signal, &sa, old_handler == NULL ? NULL : old_handler->action) != -1;
}

#define each_old_handler(var, block) \
    size_t sz = kewl_ptrholder_get_size(internal_.old_handlers); \
    for (size_t i = 0; i < sz; i++) { \
        struct old_handler_t* var = (struct old_handler_t*)kewl_ptrholder_get(internal_.old_handlers, i); \
        if (assigned(var)) block; }

#define dispose_old_handler(var) \
    UNUSED(kewl_ptrholder_delete_once(internal_.old_handlers, (kewl_ptrholder_ptr_dt)var)); \
    ce_free(var->action); \
    ce_free(var);

static void save_old_handler(struct old_handler_t* old_handler) {
    if (internal_.old_handlers == NULL)
        internal_.old_handlers = kewl_ptrholder_create(PERKS_SIGNALS_OLD_HANDLERS_ARRAY_INITIAL_CAPACITY);
    each_old_handler(o, {
        if (o->signal == old_handler->signal) {
            dispose_old_handler(o);
            break;
        }
    });
    UNUSED(kewl_ptrholder_add(internal_.old_handlers, (kewl_ptrholder_ptr_dt)old_handler));
}

static bool restore_old_handler(int signal) {
    if (signal == 0) return false;
    each_old_handler(o, {
        if (o->signal == signal) {
            if (o->is_info) {
                if (!apply_signal_info_action(signal, o->action->sa_sigaction, NULL))
                    return false;
            } else
                if (!apply_signal_action(signal, o->action->sa_handler, o->action->sa_flags, NULL))
                    return false;
            dispose_old_handler(o);
            return true;
        }
    });
    return false;
}

#undef each_old_handler
#undef dispose_old_handler

bool set_signal_handler(int signal, sighandler_t handler, int flags) {
    if (signal == 0) return false;
    struct old_handler_t* old_handler;
    old_handler = ce_malloc(sizeof(struct old_handler_t));
    if (old_handler == NULL) return false;
    old_handler->action = ce_malloc(sizeof(struct sigaction));
    if (old_handler->action == NULL) {
        ce_free(old_handler);
        return false;
    }
    old_handler->signal = signal;
    old_handler->is_info = false;
    if (!apply_signal_action(signal, handler, flags, old_handler)) {
        ce_free(old_handler->action);
        ce_free(old_handler);
        return false;
    }
    save_old_handler(old_handler);
    return true;
}

bool set_signal_info_handler(int signal, sighandler_siginfo_t handler) {
    if (signal == 0) return false;
    struct old_handler_t* old_handler;
    old_handler = ce_malloc(sizeof(struct old_handler_t));
    if (old_handler == NULL) return false;
    old_handler->action = ce_malloc(sizeof(struct sigaction));
    if (old_handler->action == NULL) {
        ce_free(old_handler);
        return false;
    }
    old_handler->signal = signal;
    old_handler->is_info = true;
    if (!apply_signal_info_action(signal, handler, old_handler)) {
        ce_free(old_handler->action);
        ce_free(old_handler);
        return false;
    }
    save_old_handler(old_handler);
    return true;
}

bool revert_signal_handler_to_original(int signal) {
    return restore_old_handler(signal);
}

bool revert_signal_handler_to_default(int signal) {
    return set_signal_handler(signal, SIG_DFL, 0);
}

bool handler_ignore_signal(int signal) {
    return set_signal_handler(signal, SIG_IGN, 0);
}

#define each_old_mask(var, block) \
    size_t sz = kewl_ptrholder_get_size(internal_.old_masks); \
    for (size_t i = 0; i < sz; i++) { \
        struct old_mask_t* var = (struct old_mask_t*)kewl_ptrholder_get(internal_.old_masks, i); \
        if (assigned(var)) block; }

#define dispose_old_mask(var) \
    UNUSED(kewl_ptrholder_delete_once(internal_.old_masks, (kewl_ptrholder_ptr_dt)var)); \
    ce_free(var->set); \
    ce_free(var);

bool mask_block_signal(int signal) {
    if (signal == 0) return false;
    struct old_mask_t* old_mask;
    old_mask = ce_malloc(sizeof(struct old_mask_t));
    if (old_mask == NULL) return false;
    old_mask->set = ce_malloc(sizeof(sigset_t));
    if (old_mask->set == NULL) {
        ce_free(old_mask);
        return false;
    }
    old_mask->signal = signal;
    sigset_t new_set;
    sigemptyset(&new_set);
    sigaddset(&new_set, signal);
    sigprocmask(SIG_BLOCK, &new_set, old_mask->set);
    if (internal_.old_masks == NULL)
        internal_.old_masks = kewl_ptrholder_create(PERKS_SIGNALS_OLD_MASKS_ARRAY_INITIAL_CAPACITY);
    each_old_mask(o, {
        if (o->signal == old_mask->signal) {
            dispose_old_mask(o);
            break;
        }
    });
    UNUSED(kewl_ptrholder_add(internal_.old_masks, (kewl_ptrholder_ptr_dt)old_mask));
    return true;
}

bool revert_signal_mask_to_last(int signal) {
    if (signal == 0) return false;
    each_old_mask(o, {
        if (o->signal == signal) {
            sigset_t* old_set = o->set;
            sigprocmask(SIG_SETMASK, old_set, NULL);
            dispose_old_mask(o);
            return true;
        }
    });
    return false;
}

#undef each_old_mask
#undef dispose_old_mask

static inline bool send_signal_to_pid(int signal, pid_t pid) {
    bool result = kill(pid, signal) != -1;
    if (assigned(internal_.on_signal_sent))
        internal_.on_signal_sent(signal, pid, result);
    return result;
}

bool send_signal(pid_t pid, int signal) {
    return send_signal_to_pid(signal, pid);
}

bool reach_process(pid_t pid) {
    return send_signal_to_pid(0, pid);
}

