/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_sampleprofiler.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

/*
    This is a simple sample profiler which take values incrementally
    and updates a series of statistical data about them (average, max, min, etc).
    Welford's algorithm is used instead of the simpler "average = sum / rounds".
    It also offers events and a routine to calculate standard deviation with a
    custom sqrt function (for ex. the kewl's double_sqrt, just in case you don't
    want to include math.h and the libm just for this).
*/

#ifndef KEWL_SAMPLEPROFILER_ALIGNMENT
    #define KEWL_SAMPLEPROFILER_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

typedef struct kewl_sampleprofiler_dt kewl_sampleprofiler_dt;

kewl_sampleprofiler_dt* kewl_sampleprofiler_create(void);
void kewl_sampleprofiler_destroy(kewl_sampleprofiler_dt* data);

void kewl_sampleprofiler_update(kewl_sampleprofiler_dt* data, double new_number);
size_t kewl_sampleprofiler_get_total_rounds(kewl_sampleprofiler_dt* data);
double kewl_sampleprofiler_get_total_sum(kewl_sampleprofiler_dt* data);
double kewl_sampleprofiler_get_minimum_input(kewl_sampleprofiler_dt* data);
size_t kewl_sampleprofiler_get_minimum_input_round(kewl_sampleprofiler_dt* data);
double kewl_sampleprofiler_get_maximum_input(kewl_sampleprofiler_dt* data);
size_t kewl_sampleprofiler_get_maximum_input_round(kewl_sampleprofiler_dt* data);
double kewl_sampleprofiler_get_mean(kewl_sampleprofiler_dt* data);
double kewl_sampleprofiler_get_minimum_mean(kewl_sampleprofiler_dt* data);
size_t kewl_sampleprofiler_get_minimum_mean_round(kewl_sampleprofiler_dt* data);
double kewl_sampleprofiler_get_maximum_mean(kewl_sampleprofiler_dt* data);
size_t kewl_sampleprofiler_get_maximum_mean_round(kewl_sampleprofiler_dt* data);
double kewl_sampleprofiler_get_sum_of_squares(kewl_sampleprofiler_dt* data);
double kewl_sampleprofiler_calculate_variance(kewl_sampleprofiler_dt* data);
double kewl_sampleprofiler_calculate_standard_deviation(kewl_sampleprofiler_dt* data, trt_double_fn sqrt_function);

typedef bool (*kewl_sampleprofiler_on_before_new_input_handler_fn)(kewl_sampleprofiler_dt* data, double new_value);
void kewl_sampleprofiler_set_on_before_new_input_handler(kewl_sampleprofiler_dt* data, kewl_sampleprofiler_on_before_new_input_handler_fn handler);
kewl_sampleprofiler_on_before_new_input_handler_fn kewl_sampleprofiler_get_on_before_new_input_handler(kewl_sampleprofiler_dt* data);

typedef void (*kewl_sampleprofiler_on_minimum_input_handler_fn)(kewl_sampleprofiler_dt* data, size_t current_round, double new_minimum);
void kewl_sampleprofiler_set_on_minimum_input_handler(kewl_sampleprofiler_dt* data, kewl_sampleprofiler_on_minimum_input_handler_fn handler);
kewl_sampleprofiler_on_minimum_input_handler_fn kewl_sampleprofiler_get_on_minimum_input_handler(kewl_sampleprofiler_dt* data);

typedef void (*kewl_sampleprofiler_on_maximum_input_handler_fn)(kewl_sampleprofiler_dt* data, size_t current_round, double new_maximum);
void kewl_sampleprofiler_set_on_maximum_input_handler(kewl_sampleprofiler_dt* data, kewl_sampleprofiler_on_maximum_input_handler_fn handler);
kewl_sampleprofiler_on_maximum_input_handler_fn kewl_sampleprofiler_get_on_maximum_input_handler(kewl_sampleprofiler_dt* data);

typedef void (*kewl_sampleprofiler_on_minimum_mean_handler_fn)(kewl_sampleprofiler_dt* data, size_t current_round, double new_minimum);
void kewl_sampleprofiler_set_on_minimum_mean_handler(kewl_sampleprofiler_dt* data, kewl_sampleprofiler_on_minimum_mean_handler_fn handler);
kewl_sampleprofiler_on_minimum_mean_handler_fn kewl_sampleprofiler_get_on_minimum_mean_handler(kewl_sampleprofiler_dt* data);

typedef void (*kewl_sampleprofiler_on_maximum_mean_handler_fn)(kewl_sampleprofiler_dt* data, size_t current_round, double new_maximum);
void kewl_sampleprofiler_set_on_maximum_mean_handler(kewl_sampleprofiler_dt* data, kewl_sampleprofiler_on_maximum_mean_handler_fn handler);
kewl_sampleprofiler_on_maximum_mean_handler_fn kewl_sampleprofiler_get_on_maximum_mean_handler(kewl_sampleprofiler_dt* data);

