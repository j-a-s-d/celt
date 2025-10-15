/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: MeH
 * File: meh_loops-inc.h
 * Brief: part of MeH
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef MEH
#warning This is intended to be part of the MeH C Library.
#endif

/* MeH.LOOPS -- Block Unrolling */

#define BLOCK_ONCE(block) do block while(0)
#define BLOCK_TWICE(block) BLOCK_ONCE(block); BLOCK_ONCE(block)
#define BLOCK_THRICE(block) BLOCK_ONCE(block); BLOCK_ONCE(block); BLOCK_ONCE(block)

/* MeH.LOOPS -- Arithmetic-Logic Iteration */

#define LOOP_FOREVER() \
    while (1)

#define LOOP_VAR_TIMES(var, times) \
    for (ssize_t var = 0; var < (times); var++)

#define LOOP_TIMES(times) \
    LOOP_VAR_TIMES(CONCAT(_loop_i_, __COUNTER__), times)

#define LOOP_UPFROMTO(var, start, stop) \
    for (ssize_t var = (start); var <= (stop); var++)

#define LOOP_UPTO(var, stop) \
    LOOP_UPFROMTO(var, 0, stop)

#define LOOP_DOWNFROMTO(var, start, stop) \
    for (ssize_t var = (start); var >= (stop); var--)

#define LOOP_DOWNFROM(var, start) \
    LOOP_DOWNFROMTO(var, start, 0)

/* MeH.LOOPS -- Array Iteration */

#define ARRAY_ITER(var, array) \
    for (ssize_t var = 0; var < (int)ARRAY_SIZE(array); var++)

#define ARRAY_EACH(var, array) \
    for (__typeof__(*(array)) *var = (array); var < (array) + ARRAY_SIZE(array); ++var)

