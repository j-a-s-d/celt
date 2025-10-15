/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_sampleprofiler-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

struct KEWL_SAMPLEPROFILER_ALIGNMENT kewl_sampleprofiler_dt {
    // current values
    size_t current_round;
    double current_sum;
    double current_average;
    double current_ss; // sum of squares of differences from the current mean
    // min/max data
    double max_input;
    double min_input;
    size_t max_input_round;
    size_t min_input_round;
    double max_average;
    double min_average;
    size_t max_average_round;
    size_t min_average_round;
    // events
    kewl_sampleprofiler_on_before_new_input_handler_fn on_before_new_input_handler;
    kewl_sampleprofiler_on_minimum_input_handler_fn on_minimum_input_handler;
    kewl_sampleprofiler_on_maximum_input_handler_fn on_maximum_input_handler;
    kewl_sampleprofiler_on_minimum_mean_handler_fn on_minimum_mean_handler;
    kewl_sampleprofiler_on_maximum_mean_handler_fn on_maximum_mean_handler;
};

kewl_sampleprofiler_dt* kewl_sampleprofiler_create(void) {
    RET_MALLOC(kewl_sampleprofiler_dt, {
        result->current_round = 0;
        result->current_sum = 0.0;
        result->max_input = -DBL_MAX;
        result->min_input = DBL_MAX;
        result->max_input_round = 0;
        result->min_input_round = 0;
        result->current_average = 0.0;
        result->current_ss = 0.0;
        result->max_average = -DBL_MAX;
        result->min_average = DBL_MAX;
        result->max_average_round = 0;
        result->min_average_round = 0;
        result->on_before_new_input_handler = NULL;
        result->on_minimum_input_handler = NULL;
        result->on_maximum_input_handler = NULL;
        result->on_minimum_mean_handler = NULL;
        result->on_maximum_mean_handler = NULL;
    });
}

void kewl_sampleprofiler_destroy(kewl_sampleprofiler_dt* const data) {
    ce_free(data);
}

void kewl_sampleprofiler_update(kewl_sampleprofiler_dt* const data, double new_number) {
    if (data == NULL) return;
    if (assigned(data->on_before_new_input_handler))
        if (!data->on_before_new_input_handler(data, new_number))
            return;
    data->current_sum += new_number;
    data->current_round++;
    if (new_number < data->min_input) {
        data->min_input = new_number;
        data->min_input_round = data->current_round;
        if (assigned(data->on_minimum_input_handler))
            data->on_minimum_input_handler(data, data->current_round, new_number);
    }
    if (new_number > data->max_input) {
        data->max_input = new_number;
        data->max_input_round = data->current_round;
        if (assigned(data->on_maximum_input_handler))
            data->on_maximum_input_handler(data, data->current_round, new_number);
    }
    // welford update, instead of "average = sum / rounds"
    double delta = new_number - data->current_average;
    data->current_average += delta / data->current_round;
    double delta2 = new_number - data->current_average;
    data->current_ss += delta * delta2;
    if (data->current_average < data->min_average) {
        data->min_average = data->current_average;
        data->min_average_round = data->current_round;
        if (assigned(data->on_minimum_mean_handler))
            data->on_minimum_mean_handler(data, data->current_round, new_number);
    }
    if (data->current_average > data->max_average) {
        data->max_average = data->current_average;
        data->max_average_round = data->current_round;
        if (assigned(data->on_maximum_mean_handler))
            data->on_maximum_mean_handler(data, data->current_round, new_number);
    }
}

size_t kewl_sampleprofiler_get_total_rounds(kewl_sampleprofiler_dt* const data) {
    return data == NULL ? 0 : data->current_round;
}

double kewl_sampleprofiler_get_total_sum(kewl_sampleprofiler_dt* const data) {
    return data == NULL ? 0.0 : data->current_sum;
}

double kewl_sampleprofiler_get_minimum_input(kewl_sampleprofiler_dt* const data) {
    return (data == NULL || data->current_round < 1) ? 0.0 : data->min_input;
}

size_t kewl_sampleprofiler_get_minimum_input_round(kewl_sampleprofiler_dt* const data) {
    return data == NULL ? 0 : data->min_input_round;
}

double kewl_sampleprofiler_get_maximum_input(kewl_sampleprofiler_dt* const data) {
    return (data == NULL || data->current_round < 1) ? 0.0 : data->max_input;
}

size_t kewl_sampleprofiler_get_maximum_input_round(kewl_sampleprofiler_dt* const data) {
    return data == NULL ? 0 : data->max_input_round;
}

double kewl_sampleprofiler_get_mean(kewl_sampleprofiler_dt* const data) {
    return data == NULL ? 0.0 : data->current_average;
}

double kewl_sampleprofiler_get_minimum_mean(kewl_sampleprofiler_dt* const data) {
    return (data == NULL || data->current_round < 1) ? 0.0 : data->min_average;
}

size_t kewl_sampleprofiler_get_minimum_mean_round(kewl_sampleprofiler_dt* const data) {
    return data == NULL ? 0.0 : data->min_average_round;
}

double kewl_sampleprofiler_get_maximum_mean(kewl_sampleprofiler_dt* const data) {
    return (data == NULL || data->current_round < 1) ? 0.0 : data->max_average;
}

size_t kewl_sampleprofiler_get_maximum_mean_round(kewl_sampleprofiler_dt* const data) {
    return data == NULL ? 0.0 : data->max_average_round;
}

double kewl_sampleprofiler_get_sum_of_squares(kewl_sampleprofiler_dt* const data) {
    if (data == NULL || data->current_round < 2) return 0.0;
    return data->current_ss;
}

double kewl_sampleprofiler_calculate_variance(kewl_sampleprofiler_dt* const data) {
    if (data == NULL || data->current_round < 2) return 0.0;
    return data->current_ss / (data->current_round - 1);
}

double kewl_sampleprofiler_calculate_standard_deviation(kewl_sampleprofiler_dt* const data, trt_double_fn sqrt_function) {
    if (data == NULL || sqrt_function == NULL || data->current_round < 2) return 0.0;
    return sqrt_function(data->current_ss / (data->current_round - 1));
}

void kewl_sampleprofiler_set_on_before_new_input_handler(kewl_sampleprofiler_dt* const data, kewl_sampleprofiler_on_before_new_input_handler_fn handler) {
    if (assigned(data)) data->on_before_new_input_handler = handler;
}

kewl_sampleprofiler_on_before_new_input_handler_fn kewl_sampleprofiler_get_on_before_new_input_handler(kewl_sampleprofiler_dt* const data) {
    return data == NULL ? NULL : data->on_before_new_input_handler;
}

void kewl_sampleprofiler_set_on_minimum_input_handler(kewl_sampleprofiler_dt* const data, kewl_sampleprofiler_on_minimum_input_handler_fn handler) {
    if (assigned(data)) data->on_minimum_input_handler = handler;
}

kewl_sampleprofiler_on_minimum_input_handler_fn kewl_sampleprofiler_get_on_minimum_input_handler(kewl_sampleprofiler_dt* const data) {
    return data == NULL ? NULL : data->on_minimum_input_handler;
}

void kewl_sampleprofiler_set_on_maximum_input_handler(kewl_sampleprofiler_dt* const data, kewl_sampleprofiler_on_maximum_input_handler_fn handler) {
    if (assigned(data)) data->on_maximum_input_handler = handler;
}

kewl_sampleprofiler_on_maximum_input_handler_fn kewl_sampleprofiler_get_on_maximum_input_handler(kewl_sampleprofiler_dt* const data) {
    return data == NULL ? NULL : data->on_maximum_input_handler;
}

void kewl_sampleprofiler_set_on_minimum_mean_handler(kewl_sampleprofiler_dt* const data, kewl_sampleprofiler_on_minimum_mean_handler_fn handler) {
    if (assigned(data)) data->on_minimum_mean_handler = handler;
}

kewl_sampleprofiler_on_minimum_mean_handler_fn kewl_sampleprofiler_get_on_minimum_mean_handler(kewl_sampleprofiler_dt* const data) {
    return data == NULL ? NULL : data->on_minimum_mean_handler;
}

void kewl_sampleprofiler_set_on_maximum_mean_handler(kewl_sampleprofiler_dt* const data, kewl_sampleprofiler_on_maximum_mean_handler_fn handler) {
    if (assigned(data)) data->on_maximum_mean_handler = handler;
}

kewl_sampleprofiler_on_maximum_mean_handler_fn kewl_sampleprofiler_get_on_maximum_mean_handler(kewl_sampleprofiler_dt* data) {
    return data == NULL ? NULL : data->on_maximum_mean_handler;
}

