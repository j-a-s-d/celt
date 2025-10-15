/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: GeM LINUX
 * File: gem_linux.h
 * Brief: linux-specific functions
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "ce.h"

#define GeM_LINUX

#if !defined(__unix_like)
#error "GeM Linux requires a unix-like environment to work."
#endif

/* GeM.LINUX -- Running-privileges stuff */

#include <stdlib.h>
#include <unistd.h>

/**
 * Returns true if running with root privileges (effective UID == 0),
 * otherwise returns false.
 */
static inline bool is_root(void) {
    return geteuid() == 0;
}

/**
 * Returns true if running under sudo, detected by the presence of
 * the SUDO_USER environment variable, otherwise false.
 */
static inline bool under_sudo(void) {
    return assigned(getenv("SUDO_USER"));
}

/* GeM.LINUX -- Port reading */

#ifdef __x86

#include <sys/io.h>
#include <errno.h>

/* Reads a byte from the specified I/O port with permission handling.
   Returns the byte read on success, or -1 on failure (check errno).
   This function requires root privileges or the CAP_SYS_RAWIO capability to succeed.
   Works on Linux x86 systems. */
int read_port_byte(unsigned short port) {
    if (ioperm(port, 1, 1) != 0) // enable access to the port
        return -1;
    unsigned char value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    if (ioperm(port, 1, 0) != 0) // disable access to the port
        NOOP_STATEMENT; // even if disabling fails, we return the read value
    return value;
}

#endif

#ifdef __cplusplus
}
#endif

