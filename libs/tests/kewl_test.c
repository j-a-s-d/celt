/**
 * Kewl C Library
 */

#include "gem_testing.h"
#include <float.h> // FLT_EPSILON and DBL_EPSILON
#include "kewl.h"

#ifdef KEWL_HELP
CE_MESSAGE("\n\n*** compile with: -Wfatal-errors -I../include -o ../bin/kewl_test ../src/kewl.c kewl_test.c\n \
  and one of the following flag combinations at minimum (for ex. no DATETIME's nap):\n \
    -std=c99\n \
  for more but not all (for ex. DATETIME's nap):\n \
    -std=gnu99\n \
    -std=c99 -D_POSIX_C_SOURCE=199309L\n \
  or one of the following to get all the features:\n \
    -std=gnu11\n \
    -std=c11 -D_POSIX_C_SOURCE=199309L\n\n");
#endif

static inline void test_fs_utilities() {
    const char* filename = "example.txt";
    const char* content = "Hello, World!\n";
    Tests.run("write_file", write_file(filename, content));

    char* data = read_file(filename);
    Tests.run("read_file", assigned(data));
    Tests.print("File content: %s\n", data);
    if (data) free(data);

    Tests.run("file_exists", file_exists(filename));

    long size = get_file_size(filename);
    Tests.run("get_file_size", size > -1);
    Tests.print("File size: %ld bytes\n", size);

    Tests.run("append_file", append_file(filename, "This is appended content.\n"));

    data = read_file(filename);
    if (data) {
        Tests.print("Updated file content: %s\n", data);
        free(data);
    }

    const char* other_filename = "example2.txt";
    Tests.run("rename_file YES", rename_file(filename, other_filename));
    Tests.run("rename_file NO inexistent", !rename_file(filename, other_filename));
    Tests.run("rename_file NO null1", !rename_file(NULL, other_filename));
    Tests.run("rename_file NO null2", !rename_file(filename, NULL));
    Tests.run("delete_file NO null", !delete_file(NULL));
    Tests.run("delete_file NO inexistent", !delete_file(filename));
    Tests.run("delete_file YES", delete_file(other_filename));

    const char* hex_fn = "hex.bin";
    const char* hex_ar[] = {"48", "65", "6C", "6C", "6F"}; // "Hello"
    ssize_t hex_sz = ARRAY_SIZE(hex_ar);
    Tests.run("write_hex_data_to_file", write_hex_data_as_binary_to_file(hex_fn, hex_ar, hex_sz));
    Tests.run("file_exists", file_exists(hex_fn));
    Tests.run("get_file_size", get_file_size(hex_fn) == hex_sz);
    size_t hex_ln;
    __auto char** hex_dt = read_file_as_hex_data(hex_fn, &hex_ln);
    Tests.run("read_file_as_hex_data", hex_ln == 5);
    for (size_t j = 0; j < hex_ln; j++) free(hex_dt[j]);
    __auto char* hex_st = read_file_as_hex_string(hex_fn, " ");
    Tests.run("read_file_as_hex_string", streq(hex_st, "48 65 6C 6C 6F"));
    Tests.run("delete_file", delete_file(hex_fn));
    
    mode_t mode = 0755;
    Tests.run("create_moded_directories", create_moded_directories("z", mode));
    Tests.run("directory_exists", directory_exists("z"));
    Tests.run("delete_directory", delete_directory("z"));

    Tests.run("create_directory", create_directory("y"));
    Tests.run("directory_exists", directory_exists("y"));
    Tests.run("delete_directory", delete_directory("y"));
    
    Tests.run("create_nested_directories", create_nested_directories("x/w"));
    Tests.run("directory_exists", directory_exists("x"));
    Tests.run("delete_directory", !delete_directory("x"));
    Tests.run("delete_directory", delete_directory("x/w"));
    Tests.run("delete_directory", delete_directory("x"));

    const char* path = "a/b/c/d";
    Tests.run("create_moded_nested_directories", create_moded_nested_directories(path, mode));
    Tests.run("directory_exists", directory_exists("a"));
    Tests.run("delete_directory", !delete_directory("a"));
    Tests.run("delete_nested_directories", delete_nested_directories("a"));
    Tests.run("delete_directory", !delete_directory("a"));
    AUTO_STRING(ld, list_directory(".", ","));
    Tests.run("list_directory", assigned(ld));
    Tests.print("%s\n", ld);
}

static inline void test_mth_utilities() {
    Tests.run("float_sqrt YES", float_sqrt(9.0f) == 3.0f);
    Tests.run("float_sqrt NO", float_isNaN(float_sqrt(-9.0f)));
    Tests.run("double_sqrt YES", double_sqrt(9.0) == 3.0);
    Tests.run("double_sqrt NO", double_isNaN(double_sqrt(-9.0f)));
    Tests.run("long_double_sqrt YES", (double)long_double_sqrt(9.0L) == 3.0);
    Tests.run("long_double_sqrt NO", long_double_isNaN(long_double_sqrt(-9.0L)));

    float adcValue = 512.0f; // Example ADC reading
    float voltage = float_interpolate(adcValue, 0.0f, 1023.0f, 0.0f, 5.0f);
    printf("ADC value: %.2f maps to Voltage: %.3f V\n", adcValue, voltage);
    Tests.run("float_interpolate", float_isNaN(float_interpolate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f)));
    Tests.run("float_interpolate_custom", float_isNaN(float_interpolate_custom(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, FLT_EPSILON)));
    
    double tempF = 98.6;
    double tempC = double_interpolate(tempF, 32.0, 212.0, 0.0, 100.0); // Map [32, 212] F to [0, 100] C
    printf("Temperature: %.2f F = %.2f C\n", tempF, tempC);
    Tests.run("double_interpolate", double_isNaN(double_interpolate(0.0, 0.0, 0.0, 0.0, 0.0)));
    Tests.run("double_interpolate", double_isNaN(double_interpolate_custom(0.0, 0.0, 0.0, 0.0, 0.0, DBL_EPSILON)));
    
    double aa = 15.0;
    double bb = double_interpolate(aa, 0.0, 23.93/* = (360-1)/15, same as 23 hours 56 minutes = (365-6)/15 */, 0.0, 6000.0 /* (7-1)*1000 = (7-(7-6))*1000 */);
    // FUN FACT: interpolate(Jesus-death-time-hour, 0..circle-1/solar-term, 0..week-days-1/God-day-in-years) = interpolate(15, 0..(360-1)/15, 0..(7-1)*1000) = interpolate(15, 0, 23.93, 0, 6000) = 3760.97 (3760 = year 0 + 365*0.97 = 354.05 (day 354 = Dec 20) + 24*0.05 = 1.2 (hour 1, minutes 12)) = Dec 20th, 0 @ 01:12 (in other words, it's a pointer to the night time of the winter solstice of the first year, suggesting the exit point of Jesus -Lord of History- refers to his entry point)
    Tests.print("Result: %.2f\n", bb);

    double decimal_degrees = dms_to_decimal_degrees(0, 45, 06.123, false);
    Tests.run("dms_to_decimal_degrees +", double_equal(decimal_degrees, 0.751701, 0.000001));
    Tests.print("Decimal: %f\n", decimal_degrees);
    int degrees, minutes;
    double seconds;
    bool negative;
    decimal_degrees_to_dms(decimal_degrees, &degrees, &minutes, &seconds, &negative);
    Tests.run("decimal_degrees_to_dms +", negative == false && degrees == 0 && minutes == 45 && (int)seconds == 6);
    Tests.print("Values: degrees %d, minutes %d, seconds %.4f, negative %s\n", degrees, minutes, seconds, strbool(negative));
    decimal_degrees = dms_to_decimal_degrees(0, 45, 06.123, true);
    Tests.run("dms_to_decimal_degrees -", double_equal(decimal_degrees, -0.751701, 0.000001));
    decimal_degrees_to_dms(decimal_degrees, &degrees, &minutes, &seconds, &negative);
    Tests.run("decimal_degrees_to_dms -", negative == true && degrees == 0 && minutes == 45 && (int)seconds == 6);
    Tests.print("Values: degrees %d, minutes %d, seconds %.4f, negative %s\n", degrees, minutes, seconds, strbool(negative));
    
    Tests.run("normalize_circular_angle 0", double_equal(normalize_circular_angle(0.0), 0.0, 0.000001));
    Tests.run("normalize_circular_angle -0", double_equal(normalize_circular_angle(-0.0), 0.0, 0.000001));
    Tests.run("normalize_circular_angle 40", double_equal(normalize_circular_angle(40.0), 40.0, 0.000001));
    Tests.run("normalize_circular_angle -40", double_equal(normalize_circular_angle(-40.0), 320.0, 0.000001));
    Tests.run("normalize_circular_angle 360", double_equal(normalize_circular_angle(360.0), 0.0, 0.000001));
    Tests.run("normalize_circular_angle -360", double_equal(normalize_circular_angle(-360.0), 0.0, 0.000001));
    Tests.run("normalize_circular_angle 400", double_equal(normalize_circular_angle(400.0), 40.0, 0.000001));
    Tests.run("normalize_circular_angle -400", double_equal(normalize_circular_angle(-400.0), 320.0, 0.000001));
    Tests.run("get_circular_opposite_point 0", double_equal(get_circular_opposite_point(0.0), 180.0, 0.000001));
    Tests.run("get_circular_opposite_point -0", double_equal(get_circular_opposite_point(-0.0), 180.0, 0.000001));
    Tests.run("get_circular_opposite_point 40", double_equal(get_circular_opposite_point(40.0), 220.0, 0.000001));
    Tests.run("get_circular_opposite_point -40", double_equal(get_circular_opposite_point(-40.0), 140.0, 0.000001));
    Tests.run("get_circular_opposite_point 360", double_equal(get_circular_opposite_point(360.0), 180.0, 0.000001));
    Tests.run("get_circular_opposite_point -360", double_equal(get_circular_opposite_point(-360.0), 180.0, 0.000001));
    Tests.run("get_circular_opposite_point 400", double_equal(get_circular_opposite_point(400.0), 220.0, 0.000001));
    Tests.run("get_circular_opposite_point -400", double_equal(get_circular_opposite_point(-400.0), 140.0, 0.000001));
    Tests.run("is_circular_point_between YES 0 in 350..10", is_circular_point_between(0.0, 350.0, 10.0));
    Tests.run("is_circular_point_between YES 360 in 350..10", is_circular_point_between(0.0, 350.0, 10.0));
    Tests.run("is_circular_point_between NO 0 in 10..350", !is_circular_point_between(0.0, 10.0, 350.0));
    Tests.run("is_circular_point_between NO 360 in 10..350", !is_circular_point_between(360.0, 10.0, 350.0));
    Tests.run("is_circular_point_between YES 40 in 30..50", is_circular_point_between(40.0, 30.0, 50.0));
    Tests.run("is_circular_point_between NO -40 in 30..50", !is_circular_point_between(-40.0, 30.0, 50.0));
    Tests.run("get_circular_distance 0..10", double_equal(get_circular_distance(0.0, 10.0), 10.0, 0.000001));
    Tests.run("get_circular_distance 350..10", double_equal(get_circular_distance(350.0, 10.0), 20.0, 0.000001));
    Tests.run("get_circular_offset_percentage_between 0 in 0..10", double_equal(get_circular_offset_percentage_between(0.0, 0.0, 10.0), 0.0, 0.000001));
    Tests.run("get_circular_offset_percentage_between 1 in 0..10", double_equal(get_circular_offset_percentage_between(1.0, 0.0, 10.0), 10.0, 0.000001));
    Tests.run("get_circular_offset_percentage_between 0 in 350..10", double_equal(get_circular_offset_percentage_between(0.0, 350.0, 10.0), 50.0, 0.000001));
    
    uint8_t data[] = {0, 42, 42, 200, 255, 0};
    __auto uint8_t* hist = get_histogram(data, sizeof(data) / sizeof(data[0]));
    Tests.run("get_histogram", hist != NULL &&
        hist[0] == 2 && hist[42] == 2 && hist[200] == 1 && hist[255] == 1 &&
        hist[1] == 0 && hist[31] == 0 && hist[81] == 0 && hist[123] == 0);
}

static inline void test_sampleprofiler() {
    kewl_sampleprofiler_dt* data = kewl_sampleprofiler_create();
    Tests.run("kewl_sampleprofiler_create", assigned(data));
    Tests.run("kewl_sampleprofiler_get_total_rounds 0", kewl_sampleprofiler_get_total_rounds(data) == 0);
    Tests.run("kewl_sampleprofiler_get_total_sum 0.0", kewl_sampleprofiler_get_total_sum(data) == 0.0);
    Tests.run("kewl_sampleprofiler_get_mean 0.0", kewl_sampleprofiler_get_mean(data) == 0.0);
    Tests.run("kewl_sampleprofiler_get_maximum_input 0.0", kewl_sampleprofiler_get_maximum_input(data) == 0.0);
    Tests.run("kewl_sampleprofiler_get_minimum_input 0.0", kewl_sampleprofiler_get_minimum_input(data) == 0.0);
    Tests.run("kewl_sampleprofiler_get_maximum_input_round 0", kewl_sampleprofiler_get_maximum_input_round(data) == 0);
    Tests.run("kewl_sampleprofiler_get_minimum_input_round 0", kewl_sampleprofiler_get_minimum_input_round(data) == 0);
    Tests.run("kewl_sampleprofiler_get_maximum_mean 0.0", kewl_sampleprofiler_get_maximum_mean(data) == 0.0);
    Tests.run("kewl_sampleprofiler_get_minimum_mean 0.0", kewl_sampleprofiler_get_minimum_mean(data) == 0.0);
    Tests.run("kewl_sampleprofiler_get_maximum_mean_round 0", kewl_sampleprofiler_get_maximum_mean_round(data) == 0);
    Tests.run("kewl_sampleprofiler_get_minimum_mean_round 0", kewl_sampleprofiler_get_minimum_mean_round(data) == 0);
    Tests.run("kewl_sampleprofiler_get_sum_of_squares 0.0", kewl_sampleprofiler_get_sum_of_squares(data) == 0.0);
    Tests.run("kewl_sampleprofiler_calculate_variance 0.0", kewl_sampleprofiler_calculate_variance(data) == 0.0);
    Tests.run("kewl_sampleprofiler_calculate_standard_deviation 0.0", kewl_sampleprofiler_calculate_standard_deviation(data, double_sqrt) == 0.0);
    kewl_sampleprofiler_update(data, 5.0);
    Tests.run("kewl_sampleprofiler_get_total_rounds 1", kewl_sampleprofiler_get_total_rounds(data) == 1);
    Tests.run("kewl_sampleprofiler_get_total_sum 5.0", kewl_sampleprofiler_get_total_sum(data) == 5.0);
    Tests.run("kewl_sampleprofiler_get_mean 5.0", kewl_sampleprofiler_get_mean(data) == 5.0);
    Tests.run("kewl_sampleprofiler_get_maximum_input 5.0", kewl_sampleprofiler_get_maximum_input(data) == 5.0);
    Tests.run("kewl_sampleprofiler_get_minimum_input 5.0", kewl_sampleprofiler_get_minimum_input(data) == 5.0);
    Tests.run("kewl_sampleprofiler_get_maximum_input_round 1", kewl_sampleprofiler_get_maximum_input_round(data) == 1);
    Tests.run("kewl_sampleprofiler_get_minimum_input_round 1", kewl_sampleprofiler_get_minimum_input_round(data) == 1);
    Tests.run("kewl_sampleprofiler_get_maximum_mean 5.0", kewl_sampleprofiler_get_maximum_mean(data) == 5.0);
    Tests.run("kewl_sampleprofiler_get_minimum_mean 5.0", kewl_sampleprofiler_get_minimum_mean(data) == 5.0);
    Tests.run("kewl_sampleprofiler_get_maximum_mean_round 1", kewl_sampleprofiler_get_maximum_mean_round(data) == 1);
    Tests.run("kewl_sampleprofiler_get_minimum_mean_round 1", kewl_sampleprofiler_get_minimum_mean_round(data) == 1);
    Tests.run("kewl_sampleprofiler_get_sum_of_squares 0.0", kewl_sampleprofiler_get_sum_of_squares(data) == 0.0);
    Tests.run("kewl_sampleprofiler_calculate_variance 0.0", kewl_sampleprofiler_calculate_variance(data) == 0.0);
    Tests.run("kewl_sampleprofiler_calculate_standard_deviation 0.0", kewl_sampleprofiler_calculate_standard_deviation(data, double_sqrt) == 0.0);
    kewl_sampleprofiler_update(data, 7.0);
    Tests.run("kewl_sampleprofiler_get_total_rounds 2", kewl_sampleprofiler_get_total_rounds(data) == 2);
    Tests.run("kewl_sampleprofiler_get_total_sum 12.0", kewl_sampleprofiler_get_total_sum(data) == 12.0);
    Tests.run("kewl_sampleprofiler_get_mean 6.0", kewl_sampleprofiler_get_mean(data) == 6.0);
    Tests.run("kewl_sampleprofiler_get_maximum_input 7.0", kewl_sampleprofiler_get_maximum_input(data) == 7.0);
    Tests.run("kewl_sampleprofiler_get_minimum_input 5.0", kewl_sampleprofiler_get_minimum_input(data) == 5.0);
    Tests.run("kewl_sampleprofiler_get_maximum_input_round 2", kewl_sampleprofiler_get_maximum_input_round(data) == 2);
    Tests.run("kewl_sampleprofiler_get_minimum_input_round 1", kewl_sampleprofiler_get_minimum_input_round(data) == 1);
    Tests.run("kewl_sampleprofiler_get_maximum_mean 6.0", kewl_sampleprofiler_get_maximum_mean(data) == 6.0);
    Tests.run("kewl_sampleprofiler_get_minimum_mean 5.0", kewl_sampleprofiler_get_minimum_mean(data) == 5.0);
    Tests.run("kewl_sampleprofiler_get_maximum_mean_round 2", kewl_sampleprofiler_get_maximum_mean_round(data) == 2);
    Tests.run("kewl_sampleprofiler_get_minimum_mean_round 1", kewl_sampleprofiler_get_minimum_mean_round(data) == 1);
    Tests.run("kewl_sampleprofiler_get_sum_of_squares 2.0", kewl_sampleprofiler_get_sum_of_squares(data) == 2.0);
    Tests.run("kewl_sampleprofiler_calculate_variance 2.0", kewl_sampleprofiler_calculate_variance(data) == 2.0);
    kewl_sampleprofiler_update(data, 3.0);
    Tests.run("kewl_sampleprofiler_get_total_rounds 3", kewl_sampleprofiler_get_total_rounds(data) == 3);
    Tests.run("kewl_sampleprofiler_get_total_sum 15.0", kewl_sampleprofiler_get_total_sum(data) == 15.0);
    Tests.run("kewl_sampleprofiler_get_mean 5.0", kewl_sampleprofiler_get_mean(data) == 5.0);
    Tests.run("kewl_sampleprofiler_get_maximum_input 7.0", kewl_sampleprofiler_get_maximum_input(data) == 7.0);
    Tests.run("kewl_sampleprofiler_get_minimum_input 3.0", kewl_sampleprofiler_get_minimum_input(data) == 3.0);
    Tests.run("kewl_sampleprofiler_get_maximum_input_round 2", kewl_sampleprofiler_get_maximum_input_round(data) == 2);
    Tests.run("kewl_sampleprofiler_get_minimum_input_round 3", kewl_sampleprofiler_get_minimum_input_round(data) == 3);
    Tests.run("kewl_sampleprofiler_get_maximum_mean 6.0", kewl_sampleprofiler_get_maximum_mean(data) == 6.0);
    Tests.run("kewl_sampleprofiler_get_minimum_mean 5.0", kewl_sampleprofiler_get_minimum_mean(data) == 5.0);
    Tests.run("kewl_sampleprofiler_get_maximum_mean_round 2", kewl_sampleprofiler_get_maximum_mean_round(data) == 2);
    Tests.run("kewl_sampleprofiler_get_minimum_mean_round 1", kewl_sampleprofiler_get_minimum_mean_round(data) == 1);
    Tests.run("kewl_sampleprofiler_get_sum_of_squares 8.0", kewl_sampleprofiler_get_sum_of_squares(data) == 8.0);
    Tests.run("kewl_sampleprofiler_calculate_variance 4.0", kewl_sampleprofiler_calculate_variance(data) == 4.0);
    kewl_sampleprofiler_update(data, 2.0);
    Tests.run("kewl_sampleprofiler_get_total_rounds 4", kewl_sampleprofiler_get_total_rounds(data) == 4);
    Tests.run("kewl_sampleprofiler_get_total_sum 17.0", kewl_sampleprofiler_get_total_sum(data) == 17.0);
    Tests.run("kewl_sampleprofiler_get_mean 4.25", kewl_sampleprofiler_get_mean(data) == 4.25);
    Tests.run("kewl_sampleprofiler_get_maximum_input 7.0", kewl_sampleprofiler_get_maximum_input(data) == 7.0);
    Tests.run("kewl_sampleprofiler_get_minimum_input 2.0", kewl_sampleprofiler_get_minimum_input(data) == 2.0);
    Tests.run("kewl_sampleprofiler_get_maximum_input_round 2", kewl_sampleprofiler_get_maximum_input_round(data) == 2);
    Tests.run("kewl_sampleprofiler_get_minimum_input_round 4", kewl_sampleprofiler_get_minimum_input_round(data) == 4);
    Tests.run("kewl_sampleprofiler_get_maximum_mean 6.0", kewl_sampleprofiler_get_maximum_mean(data) == 6.0);
    Tests.run("kewl_sampleprofiler_get_minimum_mean 4.25", kewl_sampleprofiler_get_minimum_mean(data) == 4.25);
    Tests.run("kewl_sampleprofiler_get_maximum_mean_round 2", kewl_sampleprofiler_get_maximum_mean_round(data) == 2);
    Tests.run("kewl_sampleprofiler_get_minimum_mean_round 4", kewl_sampleprofiler_get_minimum_mean_round(data) == 4);
    Tests.run("kewl_sampleprofiler_get_sum_of_squares 14.75", kewl_sampleprofiler_get_sum_of_squares(data) == 14.75);
    Tests.run("kewl_sampleprofiler_calculate_variance 4.91667", double_equal(kewl_sampleprofiler_calculate_variance(data), 4.91667, 0.00001));
    
    Tests.run("kewl_sampleprofiler_calculate_standard_deviation 2.217356", double_equal(kewl_sampleprofiler_calculate_standard_deviation(data, double_sqrt), 2.217356, 0.00001));
    kewl_sampleprofiler_destroy(data);
}

static inline void test_datetime_utilities() {
    double dh = hms_to_decimal_hours(16, 5, 33);
    Tests.run("hms_to_decimal_hours", double_abs(dh - 16.0925) < 0.0001);
    int hv[3] = {0};
    decimal_hours_to_hms(dh, hv);
    Tests.run("decimal_hours_to_hms", hv[0] == 16 && hv[1] == 5 && hv[2] == 33);
    int ut[3];
    int day_shift = 0;
    local_hms_to_utc(10, 30, 0, 5.5 /* GMT+5:30 */, ut, &day_shift);
    Tests.run("local_hms_to_utc", ut[0] == 5 && ut[1] == 0 && ut[2] == 0 && day_shift == 0);
    local_hms_to_utc(10, 30, 0, -3.5 /* GMT-3:30 */, ut, &day_shift);
    Tests.run("local_hms_to_utc", ut[0] == 14 && ut[1] == 0 && ut[2] == 0 && day_shift == 0);
    local_hms_to_utc(20, 0, 1, -4.0 /* GMT-4:00 */, ut, &day_shift);
    Tests.run("local_hms_to_utc", ut[0] == 0 && ut[1] == 0 && ut[2] == 1 && day_shift == +1);
    local_hms_to_utc(2, 0, 0, 4.0 /* GMT+4:00 */, ut, &day_shift);
    Tests.run("local_hms_to_utc", ut[0] == 22 && ut[1] == 0 && ut[2] == 0 && day_shift == -1);
    double uh = local_hms_to_utc_decimal_hours(13, 05, 33, -3.0, &day_shift);
    Tests.run("local_hms_to_utc_decimal_hours", double_abs(uh - 16.0925) < 0.0001 && day_shift == 0);
    day_shift = 0;
    int xt[3];
    utc_decimal_hours_to_local_hms(uh, -3.0, xt, &day_shift);
    Tests.run("utc_decimal_hours_to_local_hms", xt[0] == 13 && xt[1] == 5 && xt[2] == 33 && day_shift == 0);
    __auto datetime_dt* nt = get_now_datetime();
    Tests.run("get_now_datetime", assigned(nt) && nt->year >= 2025);
    Tests.print("now: %d-%d-%d %d:%d:%d\n", nt->day, nt->month, nt->year, nt->hours, nt->minutes, nt->seconds);
    datetime_dt nt2;
    fill_datetime_with_now(&nt2);
    Tests.run("fill_datetime_with_now", nt2.year >= 2025);
    Tests.run("is_leap_year YES", is_leap_year(2024));
    Tests.run("is_leap_year NO", !is_leap_year(2025));
    Tests.run("get_days_in_month 01", get_days_in_month(2024, 1) == 31);
    Tests.run("get_days_in_month 02 leap year", get_days_in_month(2024, 2) == 29);
    Tests.run("get_days_in_month 02 non-leap year", get_days_in_month(2025, 2) == 28);
    Tests.run("get_days_in_month 03", get_days_in_month(2024, 3) == 31);
    Tests.run("get_days_in_month 04", get_days_in_month(2024, 4) == 30);
    Tests.run("get_days_in_month 05", get_days_in_month(2024, 5) == 31);
    Tests.run("get_days_in_month 06", get_days_in_month(2024, 6) == 30);
    Tests.run("get_days_in_month 07", get_days_in_month(2024, 7) == 31);
    Tests.run("get_days_in_month 08", get_days_in_month(2024, 8) == 31);
    Tests.run("get_days_in_month 09", get_days_in_month(2024, 9) == 30);
    Tests.run("get_days_in_month 10", get_days_in_month(2024, 10) == 31);
    Tests.run("get_days_in_month 11", get_days_in_month(2024, 11) == 30);
    Tests.run("get_days_in_month 12", get_days_in_month(2024, 12) == 31);
    Tests.run("get_days_in_month 0 NO", get_days_in_month(2024, 0) == -1);
    Tests.run("get_days_in_month 13 NO", get_days_in_month(2024, 13) == -1);
    bool dr = modify_datetime(NULL, 1, 1, 1, 1, 1, 1);
    Tests.run("modify_datetime NO", !dr);
    datetime_dt dt = (datetime_dt){ 2024, 1, 31, 23, 59, 30 };
    dr = modify_datetime(&dt, 0, 1, 0, 0, 0, 45);
    Tests.run("modify_datetime leap-year month-roll with day-overflow", dr && dt.year == 2024 && dt.month == 3 && dt.day == 1 && dt.hours == 0 && dt.minutes == 0 && dt.seconds == 15);
    dt = (datetime_dt){ 2024, 2, 28, 23, 59, 30 };
    dr = modify_datetime(&dt, 0, 0, 0, 0, 0, 35);
    Tests.run("modify_datetime leap-year day-roll 1", dr && dt.year == 2024 && dt.month == 2 && dt.day == 29 && dt.hours == 0 && dt.minutes == 0 && dt.seconds == 5);
    dt = (datetime_dt){ 2024, 2, 28, 0, 0, 0 };
    dr = modify_datetime(&dt, 0, 0, 1, 0, 0, 0);
    Tests.run("modify_datetime leap-year day-roll 2", dr && dt.year == 2024 && dt.month == 2 && dt.day == 29 && dt.hours == 0 && dt.minutes == 0 && dt.seconds == 0);
    dr = modify_datetime(&dt, 0, 0, 1, 0, 0, 0);
    Tests.run("modify_datetime leap-year day-roll 3", dr && dt.year == 2024 && dt.month == 3 && dt.day == 1 && dt.hours == 0 && dt.minutes == 0 && dt.seconds == 0);
    dt = (datetime_dt){ 2025, 2, 28, 0, 0, 0 };
    dr = modify_datetime(&dt, 0, 0, 1, 0, 0, 0);
    Tests.run("modify_datetime non-leap-year day-roll", dr && dt.year == 2025 && dt.month == 3 && dt.day == 1 && dt.hours == 0 && dt.minutes == 0 && dt.seconds == 0);
    dt = (datetime_dt){ 2025, 12, 31, 0, 0, 0 };
    dr = modify_datetime(&dt, 0, 0, 1, 0, 0, 0);
    Tests.run("modify_datetime new-year day-roll", dr && dt.year == 2026 && dt.month == 1 && dt.day == 1 && dt.hours == 0 && dt.minutes == 0 && dt.seconds == 0);
    dt = (datetime_dt){ 2025, 12, 31, 23, 59, 59 };
    dr = modify_datetime(&dt, 0, 0, 0, 0, 0, 1);
    Tests.run("modify_datetime new-year second-roll", dr && dt.year == 2026 && dt.month == 1 && dt.day == 1 && dt.hours == 0 && dt.minutes == 0 && dt.seconds == 0);
    dr = modify_datetime(&dt, 0, 0, 0, 0, 0, -1);
    Tests.run("modify_datetime old-year second-roll", dr && dt.year == 2025 && dt.month == 12 && dt.day == 31 && dt.hours == 23 && dt.minutes == 59 && dt.seconds == 59);
    dr = modify_datetime(&dt, 0, 1, 0, 0, 0, 0);
    Tests.run("modify_datetime new-year month-roll 1", dr && dt.year == 2026 && dt.month == 1 && dt.day == 31 && dt.hours == 23 && dt.minutes == 59 && dt.seconds == 59);
    dr = modify_datetime(&dt, 0, 1, 0, 0, 0, 0);
    Tests.run("modify_datetime new-year month-roll 2", dr && dt.year == 2026 && dt.month == 2 && dt.day == 28 && dt.hours == 23 && dt.minutes == 59 && dt.seconds == 59);
    dr = modify_datetime(&dt, 0, -2, 0, 0, 0, 0);
    Tests.run("modify_datetime old-year month-roll 3", dr && dt.year == 2025 && dt.month == 12 && dt.day == 28 && dt.hours == 23 && dt.minutes == 59 && dt.seconds == 59);
    datetime_dt ot = (datetime_dt){2025,12,28,23,59,59};
    Tests.run("equal_datetimes YES", equal_datetimes(&dt, &ot));
    ot = (datetime_dt){2025,12,28,23,59,58};
    Tests.run("equal_datetimes NO 1 sec", !equal_datetimes(&dt, &ot));
    ot = (datetime_dt){2025,12,28,23,58,59};
    Tests.run("equal_datetimes NO 2 min", !equal_datetimes(&dt, &ot));
    ot = (datetime_dt){2025,12,28,22,59,59};
    Tests.run("equal_datetimes NO 3 hrs", !equal_datetimes(&dt, &ot));
    ot = (datetime_dt){2025,12,27,23,59,59};
    Tests.run("equal_datetimes NO 4 day", !equal_datetimes(&dt, &ot));
    ot = (datetime_dt){2025,11,28,23,59,59};
    Tests.run("equal_datetimes NO 5 mth", !equal_datetimes(&dt, &ot));
    ot = (datetime_dt){2024,12,28,23,59,59};
    Tests.run("equal_datetimes NO 6 yrs", !equal_datetimes(&dt, &ot));
    ot = (datetime_dt){2025,12,31,23,59,59};
    Tests.run("is_newer_datetime YES", is_newer_datetime(&dt, &ot));
    ot = (datetime_dt){2024,12,28,23,59,59};
    Tests.run("is_newer_datetime NO 1 older", !is_newer_datetime(&dt, &ot));
    ot = (datetime_dt){2025,12,28,23,59,59};
    Tests.run("is_newer_datetime NO 2 equal", !is_newer_datetime(&dt, &ot));
    Tests.run("is_newer_datetime NO 3 null 1", !is_newer_datetime(NULL, &ot));
    Tests.run("is_newer_datetime NO 4 null 2", !is_newer_datetime(&dt, NULL));
    Tests.run("is_newer_datetime NO 5 null 3", !is_newer_datetime(NULL, NULL));
    long int date_val = ymd_to_long_date(2025, 10, 31);
    Tests.run("ymd_to_long_date", date_val == 20251031L);
    Tests.print("Long date: %ld\n", date_val);
    int year, month, day;
    long_date_to_ymd(date_val, &year, &month, &day);
    Tests.run("long_date_to_ymd", year == 2025 && month == 10 && day == 31);
    Tests.print("YMD: year %d, month %d, day %d\n", year, month, day);
    __auto datetime_dt* zt = get_now_datetime();
    datetime_increment_minute(zt);
    elapsed_time_dt def = DEFAULT_ELAPSED_TIME;
    elapsed_time_dt et = get_datetime_elapsed_time(nt, NULL);
    Tests.run("get_datetime_elapsed_time NO null 1", (et.weeks == def.weeks) && (et.days == def.days) && (et.hours == def.hours) && (et.minutes == def.minutes) && (et.seconds == def.seconds));
    et = get_datetime_elapsed_time(NULL, zt);
    Tests.run("get_datetime_elapsed_time NO null 2", (et.weeks == def.weeks) && (et.days == def.days) && (et.hours == def.hours) && (et.minutes == def.minutes) && (et.seconds == def.seconds));
    et = get_datetime_elapsed_time(NULL, NULL);
    Tests.run("get_datetime_elapsed_time NO null 3", (et.weeks == def.weeks) && (et.days == def.days) && (et.hours == def.hours) && (et.minutes == def.minutes) && (et.seconds == def.seconds));
    elapsed_time_dt de = get_datetime_elapsed_time(nt, zt);
    Tests.run("get_datetime_elapsed_time", (de.weeks == 0) && (de.days == 0) && (de.hours == 0) && (de.minutes == 1) && (de.seconds == 0));
    Tests.print("elapsed: %d weeks %d days %d hours %d minutes %d seconds\n", de.weeks, de.days, de.hours, de.minutes, de.seconds);
    __auto datetime_dt* tt = make_datetime(2025, 12, 31, 23, 59, 59);
    Tests.run("datetime_make", tt->year == 2025 && tt->month == 12 && tt->day == 31 && tt->hours == 23 && tt->minutes == 59 && tt->seconds == 59);
    __auto datetime_dt* noon = datetime_midday(2025, 12, 31);
    Tests.run("datetime_make", noon->year == 2025 && noon->month == 12 && noon->day == 31 && noon->hours == 12 && noon->minutes == 0 && noon->seconds == 0);
    __auto datetime_dt* midnite = datetime_midnight(2025, 12, 31);
    Tests.run("datetime_make", midnite->year == 2025 && midnite->month == 12 && midnite->day == 31 && midnite->hours == 0 && midnite->minutes == 0 && midnite->seconds == 0);
    char tmpc = validate_ddmmyyyy_date_string_format(NULL);
    Tests.run("validate_ddmmyyyy_date_string_format NO null", tmpc == CHARS_NULL);
    tmpc = validate_ddmmyyyy_date_string_format("xx/yy/zz");
    Tests.run("validate_ddmmyyyy_date_string_format NO numeric", tmpc == CHARS_NULL);
    tmpc = validate_ddmmyyyy_date_string_format("11-22");
    Tests.run("validate_ddmmyyyy_date_string_format NO short", tmpc == CHARS_NULL);
    tmpc = validate_ddmmyyyy_date_string_format("11/22/3344/55");
    Tests.run("validate_ddmmyyyy_date_string_format NO large", tmpc == CHARS_NULL);
    tmpc = validate_ddmmyyyy_date_string_format("11-22/3344");
    Tests.run("validate_ddmmyyyy_date_string_format NO diff", tmpc == CHARS_NULL);
    tmpc = validate_ddmmyyyy_date_string_format("11-22-3344");
    Tests.run("validate_ddmmyyyy_date_string_format YES", tmpc == CHARS_MINUS);
    tmpc = validate_yyyymmdd_date_string_format(NULL);
    Tests.run("validate_yyyymmdd_date_string_format NO null", tmpc == CHARS_NULL);
    tmpc = validate_yyyymmdd_date_string_format("xx/yy/zz");
    Tests.run("validate_yyyymmdd_date_string_format NO numeric", tmpc == CHARS_NULL);
    tmpc = validate_yyyymmdd_date_string_format("0011-22");
    Tests.run("validate_yyyymmdd_date_string_format NO short", tmpc == CHARS_NULL);
    tmpc = validate_yyyymmdd_date_string_format("0011/22/33/44");
    Tests.run("validate_yyyymmdd_date_string_format NO large", tmpc == CHARS_NULL);
    tmpc = validate_yyyymmdd_date_string_format("0011-22/33");
    Tests.run("validate_yyyymmdd_date_string_format NO diff", tmpc == CHARS_NULL);
    tmpc = validate_yyyymmdd_date_string_format("0011-22-33");
    Tests.run("validate_yyyymmdd_date_string_format YES", tmpc == CHARS_MINUS);
}

static inline void test_strhashset() {
    kewl_strhashset_dt* hs = kewl_strhashset_make();
    Tests.run("kewl_strhashset_make", assigned(hs));
    Tests.run("kewl_strhashset_has NO NULL", !kewl_strhashset_has(hs, NULL));
    Tests.run("kewl_strhashset_has test NO", !kewl_strhashset_has(hs, "test"));
    Tests.run("kewl_strhashset_remove NO NULL", !kewl_strhashset_remove(hs, NULL));
    Tests.run("kewl_strhashset_remove NO inexistent", !kewl_strhashset_remove(hs, "test"));
    Tests.run("kewl_strhashset_count 0", kewl_strhashset_count(hs) == 0);
    Tests.run("kewl_strhashset_add test YES", kewl_strhashset_add(hs, "test"));
    Tests.run("kewl_strhashset_count 1", kewl_strhashset_count(hs) == 1);
    Tests.run("kewl_strhashset_add test NO", !kewl_strhashset_add(hs, "test"));
    Tests.run("kewl_strhashset_count 1", kewl_strhashset_count(hs) == 1);
    Tests.run("kewl_strhashset_add NULL NO", !kewl_strhashset_add(hs, NULL));
    Tests.run("kewl_strhashset_count 1", kewl_strhashset_count(hs) == 1);
    Tests.run("kewl_strhashset_has test YES", kewl_strhashset_has(hs, "test"));
    Tests.run("kewl_strhashset_add testing YES", kewl_strhashset_add(hs, "testing"));
    Tests.run("kewl_strhashset_count 2", kewl_strhashset_count(hs) == 2);
    char* hss = kewl_strhashset_stringify(hs, ';');
    Tests.run("kewl_strhashset_stringify", streq(hss, "test;testing"));
    free(hss);
    Tests.run("kewl_strhashset_remove YES", kewl_strhashset_remove(hs, "test"));
    Tests.run("kewl_strhashset_count 1", kewl_strhashset_count(hs) == 1);
    Tests.run("kewl_strhashset_remove NO removed", !kewl_strhashset_remove(hs, "test"));
    Tests.run("kewl_strhashset_count 1", kewl_strhashset_count(hs) == 1);
    Tests.run("kewl_strhashset_has test NO", !kewl_strhashset_has(hs, "test"));
    Tests.run("kewl_strhashset_remove YES", kewl_strhashset_remove(hs, "testing"));
    Tests.run("kewl_strhashset_count 0", kewl_strhashset_count(hs) == 0);
    Tests.run("kewl_strhashset_remove NO empty", !kewl_strhashset_remove(hs, ""));
    Tests.run("kewl_strhashset_add and YES", kewl_strhashset_add(hs, "and"));
    Tests.run("kewl_strhashset_add yet YES", kewl_strhashset_add(hs, "yet"));
    Tests.run("kewl_strhashset_add more YES", kewl_strhashset_add(hs, "more"));
    Tests.run("kewl_strhashset_count 3", kewl_strhashset_count(hs) == 3);
    kewl_strhashset_clear(hs);
    Tests.run("kewl_strhashset_clear", kewl_strhashset_count(hs) == 0);
    kewl_strhashset_clear(hs);
    hss = kewl_strhashset_stringify(hs, ';');
    Tests.run("kewl_strhashset_stringify", streq(hss, STRINGS_NOTHING));
    free(hss);
    kewl_strhashset_destroy(hs);
    kewl_strhashset_destroy(NULL);
}

static inline void test_strhashbag() {
    kewl_strhashbag_dt* hs = kewl_strhashbag_make();
    Tests.run("kewl_strhashbag_make", assigned(hs));
    Tests.run("kewl_strhashbag_has NO NULL", !kewl_strhashbag_has(hs, NULL));
    Tests.run("kewl_strhashbag_has test NO", !kewl_strhashbag_has(hs, "test"));
    Tests.run("kewl_strhashbag_remove_once NO NULL", !kewl_strhashbag_remove_once(hs, NULL));
    Tests.run("kewl_strhashbag_remove_once NO inexistent", !kewl_strhashbag_remove_once(hs, "test"));
    Tests.run("kewl_strhashbag_count_total 0", kewl_strhashbag_count_total(hs) == 0);
    Tests.run("kewl_strhashbag_add test YES", kewl_strhashbag_add(hs, "test"));
    Tests.run("kewl_strhashbag_count_total 1", kewl_strhashbag_count_total(hs) == 1);
    Tests.run("kewl_strhashbag_add test YES", kewl_strhashbag_add(hs, "test"));
    Tests.run("kewl_strhashbag_count_total 2", kewl_strhashbag_count_total(hs) == 2);
    Tests.run("kewl_strhashbag_add NULL NO", !kewl_strhashbag_add(hs, NULL));
    Tests.run("kewl_strhashbag_count_total 2", kewl_strhashbag_count_total(hs) == 2);
    Tests.run("kewl_strhashbag_has test YES", kewl_strhashbag_has(hs, "test"));
    Tests.run("kewl_strhashbag_add testing YES", kewl_strhashbag_add(hs, "testing"));
    Tests.run("kewl_strhashbag_count_total 3", kewl_strhashbag_count_total(hs) == 3);
    Tests.run("kewl_strhashbag_count_every test 2", kewl_strhashbag_count_every(hs, "test") == 2);
    char* hss = kewl_strhashbag_stringify(hs, ';');
    Tests.run("kewl_strhashbag_stringify", streq(hss, "test;test;testing"));
    free(hss);
    Tests.run("kewl_strhashbag_remove_once YES", kewl_strhashbag_remove_once(hs, "test"));
    Tests.run("kewl_strhashbag_count_total 2", kewl_strhashbag_count_total(hs) == 2);
    Tests.run("kewl_strhashbag_remove_once NO inexistent", !kewl_strhashbag_remove_once(hs, "baz"));
    Tests.run("kewl_strhashbag_count_total 2", kewl_strhashbag_count_total(hs) == 2);
    Tests.run("kewl_strhashbag_has test YES", kewl_strhashbag_has(hs, "test"));
    Tests.run("kewl_strhashbag_has inexistent NO", !kewl_strhashbag_has(hs, "baz"));
    Tests.run("kewl_strhashbag_remove_once YES", kewl_strhashbag_remove_once(hs, "testing"));
    Tests.run("kewl_strhashbag_count_total 1", kewl_strhashbag_count_total(hs) == 1);
    Tests.run("kewl_strhashbag_remove_once NO empty", !kewl_strhashbag_remove_once(hs, ""));
    Tests.run("kewl_strhashbag_add test YES", kewl_strhashbag_add(hs, "test"));
    Tests.run("kewl_strhashbag_count_total 2", kewl_strhashbag_count_total(hs) == 2);
    Tests.run("kewl_strhashbag_remove_every test", kewl_strhashbag_remove_every(hs, "test"));
    Tests.run("kewl_strhashbag_count_total 0", kewl_strhashbag_count_total(hs) == 0);
    Tests.run("kewl_strhashbag_add and YES", kewl_strhashbag_add(hs, "and"));
    Tests.run("kewl_strhashbag_add yet YES", kewl_strhashbag_add(hs, "yet"));
    Tests.run("kewl_strhashbag_add more YES", kewl_strhashbag_add(hs, "more"));
    Tests.run("kewl_strhashbag_count_total 3", kewl_strhashbag_count_total(hs) == 3);
    kewl_strhashbag_clear(hs);
    Tests.run("kewl_strhashbag_clear", kewl_strhashbag_count_total(hs) == 0);
    kewl_strhashbag_clear(hs);
    hss = kewl_strhashbag_stringify(hs, ';');
    Tests.run("kewl_strhashbag_stringify", streq(hss, STRINGS_NOTHING));
    free(hss);
    kewl_strhashbag_destroy(hs);
    kewl_strhashbag_destroy(NULL);
}

static inline void test_stream_functions() {
    const char* filename = "example.txt";
    bool wrote = write_file(filename, "Hello, World!\nABC\n");
    FILE* f = fopen(filename, "rb");
    size_t chunkSize = 5;
    size_t len;
    char* data = read_chunk_from_stream(f, chunkSize, &len);
    Tests.run("read_chunk_from_stream", wrote && assigned(f) && assigned(data));
    Tests.print("Read: %zu bytes\n", len);
    Tests.print("Data: %s\n", data);
    free(data);
    rewind(f);
    data = read_line_from_stream(f);
    Tests.run("read_line_from_stream", assigned(data));
    Tests.print("Data: %s\n", data);
    free(data);
    fclose(f);
    UNUSED(delete_file(filename));
}

const char* valid_commands[] = {"exit", "test", "help"};
const int num_valid_commands = 3;

bool is_valid_command(const char* cmd) {
    for (int i = 0; i < num_valid_commands; i++)
        if (strcmp(cmd, valid_commands[i]) == 0)
            return true;
    return false;
}

bool cmdline_executed = false;

bool test_prompt_handler(size_t line_number) {
    Tests.run("cmdline prompt", cmdline_executed = true);
    Tests.print("line number: %d\n", line_number);
    return true;
}

bool test_cmd_handler(cmdline_data_dt* cmd_data) {
    if (is_valid_command(cmd_data->command)) {
        if (strcmp(cmd_data->command, "exit") == 0) {
            Tests.run("cmdline exit number", cmd_data->number == 3);
            Tests.run("cmdline exit params", cmd_data->parameter_count == 0);
            return false;
        }
        Tests.run("cmdline help number", cmd_data->number == 2);
        Tests.run("cmdline help params", cmd_data->parameter_count == 3);
        Tests.print("Command: %s\n", cmd_data->command);
        AUTO_STRING(ra, rejoin_arguments(cmd_data->parameter_count, (const char**)cmd_data->parameters));
        Tests.print("Params (%d): %s\n", cmd_data->parameter_count, ra);
    } else
        Tests.run("cmdline unknown command", cmd_data->number == 1);
    return true;
}

static inline void test_cmdline() {
    const char* sample_commands[] = {
        "",
        "unknown-command",
        "help param1 param2 param3",
        "exit"
    };
    size_t line_count = 4;
    char tmp_filename[] = "temp_input.txt";
    FILE* tmp = fopen(tmp_filename, "w+");
    if (!tmp) {
        Tests.print("ERROR: Failed to create temporary file to test CMDLINE\n");
        return;
    }
    
    for (size_t i = 0; i < line_count; ++i)
        fprintf(tmp, "%s\n", sample_commands[i]);
    rewind(tmp);
    cmdline_start(tmp, test_prompt_handler, test_cmd_handler, true);
    Tests.run("cmdline_start", cmdline_executed);
    fclose(tmp);
    
    Tests.run("cmdline_load_from_file", cmdline_load_from_file(tmp_filename, test_prompt_handler, test_cmd_handler, true));
    remove(tmp_filename);
#ifdef __posix08
    AUTO_STRING(j, string_array_join(line_count, sample_commands, STRINGS_LF));
    Tests.run("cmdline_load_from_string", cmdline_load_from_string(j, test_prompt_handler, test_cmd_handler, true));
#endif
}

char char_treater(char c) {
    return toupper(c);
}

char* string_treater(char* str) {
    return strappend(str, "00");
}

void print_value(const char* value) {
    Tests.run("parse_separated_values value", has_content(value));
    Tests.print("Value: \"%s\"\n", value);
}

void* sample_ptr;

void print_value_with_reference(const char* value, const void* reference) {
    Tests.run("parse_separated_values_with_reference value", has_content(value) && reference == sample_ptr);
    Tests.print("Value: \"%s\"\n", value);
    Tests.print("Reference: \"%p\"\n", reference);
}

void print_parsed_string(const char* str) {
    Tests.print("Parsed String: %s\n", str);
}

void print_parsed_string_with_reference(const char* str, const void* reference) {
    Tests.print("Parsed String: %s\n", str);
    Tests.print("Passed Reference: %p\n", reference);
}

static inline void test_str_functions() {
    Tests.run("streq YES", streq("abc", "abc"));
    Tests.run("streq YES empty both", streq("", ""));
    Tests.run("streq NO null 1", !streq(NULL, "abc"));
    Tests.run("streq NO null 2", !streq("abc", NULL));
    Tests.run("streq NO null both", !streq(NULL, NULL));
    Tests.run("contains_string YES", contains_string("abcd", "c"));
    Tests.run("contains_string YES empty", contains_string("abcd", ""));
    Tests.run("contains_string YES empty both", contains_string("", ""));
    Tests.run("contains_string NO null", !contains_string("abcd", NULL));
    Tests.run("contains_string NO null both", !contains_string(NULL, NULL));
    Tests.run("strchar", strcmp(strchar('A'), "A\0") == 0);
    Tests.run("strbool", streq(strbool(true), "true"));
    char* st = bool_to_str(true);
    Tests.run("bool_to_str", streq(st, "true"));
    bool bt = str_to_bool(st);
    Tests.run("str_to_bool", bt);
    free(st);
    Tests.run("is_ascii_char \\0", is_ascii_char('\0'));
    Tests.run("is_ascii_char \\s", is_ascii_char(' '));
    Tests.run("is_ascii_char A", is_ascii_char('A'));
    Tests.run("is_ascii_char CHARS_LOWERCASE_O", is_ascii_char(CHARS_LOWERCASE_O));
    char cc = '\xC3';
    Tests.run("is_ascii_char \\xC3", !is_ascii_char(cc));
    Tests.run("is_ascii_string NULL", !is_ascii_string(NULL));
    Tests.run("is_ascii_string STRINGS_NOTHING", !is_ascii_string(STRINGS_NOTHING));
    Tests.run("is_ascii_string STRINGS_SPACE", is_ascii_string(STRINGS_SPACE));
    Tests.run("is_ascii_string hello", is_ascii_string("hello"));
    Tests.run("is_ascii_string Café", !is_ascii_string("Café")); // 'é' is not ASCII
    Tests.run("get_utf8_char_length 1", get_utf8_char_length("A"[0]) == 1); // ASCII, 1 byte
    Tests.run("get_utf8_char_length 2", get_utf8_char_length("ñ"[0]) == 2); // U+00F1, 2 bytes (C3 B1)
    Tests.run("get_utf8_char_length 3", get_utf8_char_length("ह"[0]) == 3); // U+0939 (Devanagari HA), 3 bytes (E0 A4 B9)
    Tests.run("get_utf8_char_length 4", get_utf8_char_length("𐍈"[0]) == 4); // U+10348 (Gothic Letter Hwair), 4 bytes (F0 90 8D 88)
    Tests.run("get_utf8_string_length 5", get_utf8_string_length(NULL) == -1);
    Tests.run("get_utf8_string_length 5", get_utf8_string_length("") == 0);
    Tests.run("get_utf8_string_length 5", get_utf8_string_length("Hello") == 5); // ASCII only, 5 chars
    Tests.run("get_utf8_string_length 5", get_utf8_string_length("ñandú") == 5); // includes 2-byte char ñ, total 5 chars
    Tests.run("get_utf8_string_length 6", get_utf8_string_length("हिन्दी") == 6); // Hindi word, multiple 3-byte chars
    Tests.run("get_utf8_string_length 4", get_utf8_string_length("𐍈abc") == 4); // starts with a 4-byte char + 3 ASCII chars, total 4 chars
    //Tests.run("get_utf8_string_length -1", get_utf8_string_length("invalid\xFFbyte") == -1); // invalid UTF-8
    char* sc = "ABC";
    Tests.run("prepend_char NULL", prepend_char(NULL, '_') == NULL);
    __auto char* sc2 = prepend_char(sc, '_');
    Tests.run("prepend_char _", streq(sc2, "_ABC"));
    Tests.run("append_char NULL", append_char(NULL, '_') == NULL);
    __auto char* sc3 = append_char(sc2, '_');
    Tests.run("append_char _", streq(sc3, "_ABC_"));
    char s1[] = "A3B";
    char s2[] = "ccXX";
    Tests.run("ensure_const_string NULL", streq(ensure_const_string(NULL), STRINGS_NOTHING));
    Tests.run("ensure_const_string abc", streq(ensure_const_string("abc"), "abc"));
    Tests.run("ensure_const_string_def NULL |", streq(ensure_const_string_def(NULL, STRINGS_PIPE), STRINGS_PIPE));
    Tests.run("ensure_const_string_def abc |", streq(ensure_const_string_def("abc", STRINGS_PIPE), "abc"));
    char* tt = ensure_new_string(NULL);
    Tests.run("ensure_new_string NULL", streq(tt, STRINGS_NOTHING));
    free(tt);
    tt = ensure_new_string("abc");
    Tests.run("ensure_new_string abc", streq(tt, "abc"));
    free(tt);
    tt = ensure_new_string_def(NULL, STRINGS_PIPE);
    Tests.run("ensure_new_string_def NULL |", streq(tt, STRINGS_PIPE));
    free(tt);
    tt = ensure_new_string_def("abc", STRINGS_PIPE);
    Tests.run("ensure_new_string_def abc |", streq(tt, "abc"));
    free(tt);
    Tests.run("to_lower_case NULL", to_lower_case(NULL) == NULL);
    tt = to_lower_case(STRINGS_NOTHING);
    Tests.run("to_lower_case", streq(tt, STRINGS_NOTHING));
    free(tt);
    tt = to_lower_case("\0");
    Tests.run("to_lower_case", streq(tt, STRINGS_NOTHING));
    free(tt);
    tt = to_lower_case(s1);
    Tests.run("to_lower_case A3B", strcmp(tt, "a3b") == 0);
    free(tt);
    tt = to_lower_case(s2);
    Tests.run("to_lower_case ccXX", strcmp(tt, "ccxx") == 0);
    free(tt);
    Tests.run("to_upper_case NULL", to_upper_case(NULL) == NULL);
    tt = to_upper_case("");
    Tests.run("to_upper_case", streq(tt, ""));
    free(tt);
    tt = to_upper_case("\0");
    Tests.run("to_upper_case", streq(tt, ""));
    free(tt);
    tt = to_upper_case(s1);
    Tests.run("to_upper_case a3b", strcmp(tt, "A3B") == 0);
    free(tt);
    tt = to_upper_case(s2);
    Tests.run("to_upper_case ccxx", strcmp(tt, "CCXX") == 0);
    tt = strreverse(tt);
    Tests.run("strreverse xxcc", strcmp(tt, "XXCC") == 0);
    free(tt);
    Tests.run("strreverse NULL", strreverse(NULL) == NULL);
    Tests.run("treat_chars s2", streq(s2, "ccXX") && treat_chars(s2, strlen(s2), char_treater) && streq(s2, "CCXX"));
    Tests.run("treat_chars s2 NULL", !treat_chars(s2, strlen(s2), NULL));
    Tests.run("treat_chars s2 0 s2", !treat_chars(s2, 0, char_treater));
    Tests.run("treat_chars NULL 1 s2", !treat_chars(NULL, 1, char_treater));
    Tests.run("to_upper_case ccxx", strcmp(s2, "CCXX") == 0);
    Tests.run("is_hex_string NULL", !is_hex_string(NULL));
    Tests.run("is_hex_string STRINGS_NOTHING", !is_hex_string(STRINGS_NOTHING));
    Tests.run("is_hex_string s1", is_hex_string(s1));
    Tests.run("is_hex_string s2", !is_hex_string(s2));
    Tests.run("is_numeric_string NULL", !is_numeric_string(NULL));
    Tests.run("is_numeric_string STRINGS_NOTHING", !is_numeric_string(STRINGS_NOTHING));
    Tests.run("is_numeric_string \\s", !is_numeric_string(" "));
    Tests.run("is_numeric_string \\0", !is_numeric_string("\0"));
    Tests.run("is_numeric_string 3.14", is_numeric_string("3.14"));
    Tests.run("is_numeric_string -12.5", is_numeric_string("-12.5"));
    Tests.run("is_numeric_string 3.1.4", !is_numeric_string("3.1.4"));
    Tests.run("is_numeric_string 1-2", !is_numeric_string("1-2"));
    Tests.run("is_numeric_string abc", !is_numeric_string("abc"));
    Tests.run("is_alphanumeric_string NULL", !is_alphanumeric_string(NULL));
    Tests.run("is_alphanumeric_string STRINGS_NOTHING", !is_alphanumeric_string(STRINGS_NOTHING));
    Tests.run("is_alphanumeric_string \\s", !is_alphanumeric_string(" "));
    Tests.run("is_alphanumeric_string \\0", !is_alphanumeric_string("\0"));
    Tests.run("is_alphanumeric_string a1", is_alphanumeric_string("a1"));
    Tests.run("is_alphanumeric_string 2B", is_alphanumeric_string("2B"));
    Tests.run("is_alphanumeric_string a-1", !is_alphanumeric_string("a-1"));
    Tests.run("is_alphanumeric_string 33 aa", !is_alphanumeric_string("33 aa"));
    Tests.run("has_content a", has_content("a"));
    Tests.run("has_content NULL", !has_content(NULL));
    Tests.run("has_content STRINGS_NOTHING", !has_content(STRINGS_NOTHING));
    Tests.run("has_content STRINGS_SPACE", has_content(STRINGS_SPACE));
    Tests.run("str_to_signed_char_def NULL", (str_to_signed_char_def(NULL, -3) == -3));
    Tests.run("str_to_signed_char_def STRINGS_NOTHING", (str_to_signed_char_def(STRINGS_NOTHING, -3) == -3));
    Tests.run("str_to_signed_char_def -7", (str_to_signed_char_def("-7", -7) == -7));
    Tests.run("str_to_unsigned_char_def NULL", (str_to_unsigned_char_def(NULL, 3) == 3));
    Tests.run("str_to_unsigned_char_def STRINGS_NOTHING", (str_to_unsigned_char_def(STRINGS_NOTHING, 3) == 3));
    Tests.run("str_to_unsigned_char_def 7", (str_to_unsigned_char_def("7", 7) == 7));
    Tests.run("str_to_short_def NULL", (str_to_short_def(NULL, -3) == -3));
    Tests.run("str_to_short_def STRINGS_NOTHING", (str_to_short_def(STRINGS_NOTHING, -3) == -3));
    Tests.run("str_to_short_def -7", (str_to_short_def("-7", -7) == -7));
    Tests.run("str_to_unsigned_short_def NULL", (str_to_unsigned_short_def(NULL, 3) == 3));
    Tests.run("str_to_unsigned_short_def STRINGS_NOTHING", (str_to_unsigned_short_def(STRINGS_NOTHING, 3) == 3));
    Tests.run("str_to_unsigned_short_def 3", (str_to_unsigned_short_def("3", 3) == 3));
    Tests.run("str_to_int_def NULL", (str_to_int_def(NULL, -1234) == -1234));
    Tests.run("str_to_int_def STRINGS_NOTHING", (str_to_int_def(STRINGS_NOTHING, -1234) == -1234));
    Tests.run("str_to_int_def -1234", (str_to_int_def("-1234", -1234) == -1234));
    Tests.run("str_to_unsigned_int_def NULL", (str_to_unsigned_int_def(NULL, 1234) == 1234));
    Tests.run("str_to_unsigned_int_def STRINGS_NOTHING", (str_to_unsigned_int_def(STRINGS_NOTHING, 1234) == 1234));
    Tests.run("str_to_unsigned_int_def 1234", (str_to_unsigned_int_def("1234", 1234) == 1234));
    Tests.run("str_to_long_def NULL", (str_to_long_def(NULL, -1234567890L) == -1234567890));
    Tests.run("str_to_long_def STRINGS_NOTHING", (str_to_long_def(STRINGS_NOTHING, -1234567890L) == -1234567890));
    Tests.run("str_to_long_def -1234567890", (str_to_long_def("-1234567890", -1234567890L) == -1234567890));
    Tests.run("str_to_unsigned_long_def NULL", (str_to_unsigned_long_def(NULL, 1234567890UL) == 1234567890));
    Tests.run("str_to_unsigned_long_def STRINGS_NOTHING", (str_to_unsigned_long_def(STRINGS_NOTHING, 1234567890UL) == 1234567890));
    Tests.run("str_to_unsigned_long_def 1234567890", (str_to_unsigned_long_def("1234567890", 1234567890UL) == 1234567890));
    Tests.run("str_to_long_long_def NULL", (str_to_long_long_def(NULL, -1234567890123456789LL) == -1234567890123456789LL));
    Tests.run("str_to_long_long_def STRINGS_NOTHING", (str_to_long_long_def(STRINGS_NOTHING, -1234567890123456789LL) == -1234567890123456789LL));
    Tests.run("str_to_long_long_def -1234567890123456789", (str_to_long_long_def("-1234567890123456789", -1234567890123456789LL) == -1234567890123456789LL));
    Tests.run("str_to_unsigned_long_long_def NULL", (str_to_unsigned_long_long_def(NULL, 12345678901234567890ULL) == 12345678901234567890ULL));
    Tests.run("str_to_unsigned_long_long_def STRINGS_NOTHING", (str_to_unsigned_long_long_def(STRINGS_NOTHING, 12345678901234567890ULL) == 12345678901234567890ULL));
    Tests.run("str_to_unsigned_long_long_def 12345678901234567890", (str_to_unsigned_long_long_def("12345678901234567890", 12345678901234567890ULL) == 12345678901234567890ULL));
    char* tmp = short_to_str(-3);
    Tests.run("short_to_str", streq(tmp, "-3"));
    Tests.print("%s\n", tmp);
    free(tmp);
    tmp = unsigned_short_to_str(3);
    Tests.run("unsigned_short_to_str", streq(tmp, "3"));
    Tests.print("%s\n", tmp);
    free(tmp);
    tmp = int_to_str(-1234);
    Tests.run("int_to_str", streq(tmp, "-1234"));
    Tests.print("%s\n", tmp);
    free(tmp);
    tmp = unsigned_int_to_str(1234u);
    Tests.run("unsigned_int_to_str", streq(tmp, "1234"));
    Tests.print("%s\n", tmp);
    free(tmp);
    tmp = long_to_str(-1234567890L);
    Tests.run("long_to_str", streq(tmp, "-1234567890"));
    Tests.print("%s\n", tmp);
    free(tmp);
    tmp = unsigned_long_to_str(1234567890UL);
    Tests.run("unsigned_long_to_str", streq(tmp, "1234567890"));
    Tests.print("%s\n", tmp);
    free(tmp);
    tmp = long_long_to_str(-1234567890123456789LL);
    Tests.run("long_long_to_str", streq(tmp, "-1234567890123456789"));
    Tests.print("%s\n", tmp);
    free(tmp);
    tmp = unsigned_long_long_to_str(12345678901234567890ULL);
    Tests.run("unsigned_long_long_to_str", streq(tmp, "12345678901234567890"));
    Tests.print("%s\n", tmp);
    free(tmp);
    tmp = float_to_str(1234.567f);
    Tests.run("float_to_str", streq(tmp, "1234.567"));
    Tests.print("%s\n", tmp);
    free(tmp);
    tmp = double_to_str(3.14159265);
    Tests.run("double_to_str", streq(tmp, "3.14159265"));
    Tests.print("%s\n", tmp);
    free(tmp);
    tmp = long_double_to_str(3.141592653589793238L);
    Tests.run("long_double_to_str", starts_with(tmp, "3.141592653589793")); // NOTE: check is done like this so it will work ok under Valgrind check too, long double normally uses 80-bit precision on x86/x86_64, but Valgrind reduces this to 64-bit double internally
    Tests.print("%s\n", tmp);
    free(tmp);
    tmp = ptr_to_str(&tmp);
    Tests.run("ptr_to_str", strlen(tmp) > 0);
    Tests.print("%s\n", tmp);
    free(tmp);
    unsigned char barr[11] = { BYTES_12, BYTES_34, BYTES_56, BYTES_78, BYTES_9A, BYTES_BC, BYTES_DE, BYTES_F0, BYTES_33, BYTES_22, BYTES_11 };
    tmp = bytes_to_hex(barr, ARRAY_SIZE(barr));
    Tests.run("bytes_to_hex", streq(tmp, "123456789ABCDEF0332211"));
    Tests.print("%s\n", tmp);
    uint8_t* bytes = NULL;
    ssize_t bytes_len = 0;
    Tests.run("hex_to_bytes", hex_to_bytes(tmp, &bytes, &bytes_len) && assigned(bytes) && bytes_len == 11);
    free(tmp);
    free(bytes);
    const char* arr[] = {"foo", "bar", "baz", "qux", "bar", NULL};
    size_t size = ARRAY_SIZE(arr);
    Tests.run("string_array_find_first_null 1 NULL", string_array_find_first_null(1, NULL) == -1);
    Tests.run("string_array_find_first_null 0 arr", string_array_find_first_null(0, arr) == -1);
    Tests.run("string_array_find_first_null size arr", string_array_find_first_null(size, arr) == 5);
    Tests.run("string_array_find_first bar", string_array_find_first(size, arr, "bar") == 1);
    Tests.run("string_array_find_first empty", string_array_find_first(size, arr, "") == -1);
    Tests.run("string_array_find_first NULL", string_array_find_first(size, arr, NULL) == -1);
    Tests.run("string_array_find_last bar", string_array_find_last(size, arr, "bar") == 4);
    Tests.run("string_array_find_last empty", string_array_find_last(size, arr, "") == -1);
    Tests.run("string_array_find_last NULL", string_array_find_last(size, arr, NULL) == -1);
    Tests.run("string_array_contains bar YES", string_array_contains(size, arr, "bar"));
    Tests.run("string_array_contains inexistent NO", !string_array_contains(size, arr, "no"));
    Tests.run("string_array_contains NULL NO", !string_array_contains(size, arr, NULL));
    tmp = string_array_join_range(size, arr, 1, 3, "--");
    Tests.run("string_array_join_range", strcmp(tmp, "bar--baz--qux") == 0);
    free(tmp);
    tmp = string_array_join_range(size, arr, 0, 0, "");
    Tests.run("string_array_join_range", strcmp(tmp, "foo") == 0);
    free(tmp);
    tmp = string_array_join_range(size, arr, 0, 1, "");
    Tests.run("string_array_join_range", strcmp(tmp, "foobar") == 0);
    free(tmp);
    tmp = string_array_join_range(size, arr, 0, 1, NULL);
    Tests.run("string_array_join_range", strcmp(tmp, "foobar") == 0);
    free(tmp);
    tmp = string_array_join_range(0, arr, 0, -1, "|");
    Tests.run("string_array_join_range", tmp == NULL);
    free(tmp);
    tmp = string_array_join_range(size, arr, 0, -1, "|");
    Tests.run("string_array_join_range", tmp == NULL);
    free(tmp);
    tmp = string_array_join_range(size, arr, -1, 0, "|");
    Tests.run("string_array_join_range", tmp == NULL);
    free(tmp);
    tmp = string_array_join_range(size, NULL, 0, 0, "|");
    Tests.run("string_array_join_range", tmp == NULL);
    free(tmp);
    char* arr2[] = {"def", "abc", "jkl", "ghi"};
    string_array_sort(4, arr2);
    Tests.run("strings_array_sort arr2", strcmp(arr2[0], "abc") == 0 &&
        strcmp(arr2[1], "def") == 0 && strcmp(arr2[2], "ghi") == 0 &&
        strcmp(arr2[3], "jkl") == 0);
    srand(42); // good enough
    string_array_shuffle(4, arr2, rand);
    Tests.run("strings_array_shuffle arr2", !(strcmp(arr2[0], "abc") == 0 &&
        strcmp(arr2[1], "def") == 0 && strcmp(arr2[2], "ghi") == 0 &&
        strcmp(arr2[3], "jkl") == 0)); // this can fail if the items are in the same indexes but ok
    string_array_reversed_sort(4, arr2);
    Tests.run("string_array_reversed_sort arr2", strcmp(arr2[3], "abc") == 0 &&
        strcmp(arr2[2], "def") == 0 && strcmp(arr2[1], "ghi") == 0 &&
        strcmp(arr2[0], "jkl") == 0);
    const char* valid_hex[] = {"1A", "2B", "3C", "4D"};
    const char* invalid_hex[] = {"1G", "2B", "3C", "4D"};
    const char* invalid2_hex[] = {"1A", "2B", "3C", "4Dx"};
    const char* invalid3_hex[] = {"1A", "2B", "3C", "4"};
    Tests.run("string_array_hex_validate YES", string_array_hex_validate(ARRAY_SIZE(valid_hex), valid_hex));
    Tests.run("string_array_hex_validate NO1", !string_array_hex_validate(ARRAY_SIZE(invalid_hex), invalid_hex));
    Tests.run("string_array_hex_validate NO2", !string_array_hex_validate(ARRAY_SIZE(invalid2_hex), invalid2_hex));
    Tests.run("string_array_hex_validate NO3", !string_array_hex_validate(ARRAY_SIZE(invalid3_hex), invalid3_hex));
    Tests.run("string_array_create NO 4 nil", string_array_create(4, NULL) == NULL);
    char** a0 = string_array_create(4, STRINGS_NOTHING);
    Tests.run("string_array_create YES 4 empty", assigned(a0) && streq(a0[0], STRINGS_NOTHING) && streq(a0[1], STRINGS_NOTHING) && streq(a0[2], STRINGS_NOTHING) && streq(a0[3], STRINGS_NOTHING));
    string_array_treat(4, a0, string_treater);
    Tests.run("string_array_treat", assigned(a0) && streq(a0[0], "00") && streq(a0[1], "00") && streq(a0[2], "00") && streq(a0[3], "00"));
    char** a1 = string_array_with_sentinel_create(3, STRINGS_NOTHING);
    Tests.run("string_array_create YES 3 empty + sentinel", assigned(a1) && streq(a1[0], STRINGS_NOTHING) && streq(a1[1], STRINGS_NOTHING) && streq(a1[2], STRINGS_NOTHING) && a1[3] == NULL);
    ssize_t out_len = -1;
    char** a2 = string_array_replace_segment((const char**)a0, 4, 1, 2, (const char**)a1, 3, &out_len);
    Tests.run("string_array_replace_segment", assigned(a2) && out_len == 5 && streq(a2[0], "00") && streq(a2[1], STRINGS_NOTHING) && streq(a2[2], STRINGS_NOTHING) && streq(a2[3], STRINGS_NOTHING) && streq(a2[4], "00"));
    string_array_destroy(a2, 5);
    string_array_with_sentinel_destroy(a1, 10);
    string_array_destroy(a0, 4);
    Tests.run("string_array_equal YES", string_array_equal((const char*[]){"1", "22", "333"}, (const char*[]){"1", "22", "333"}, 3));
    Tests.run("string_array_equal NO different", !string_array_equal((const char*[]){"1", "22", "333"}, (const char*[]){"1", "22", "0"}, 3));
    Tests.run("string_array_equal NO null1", !string_array_equal(NULL, (const char*[]){"1", "22", "0"}, 3));
    Tests.run("string_array_equal NO null2", !string_array_equal((const char*[]){"1", "22", "333"}, NULL, 3));
    Tests.run("string_array_equal NO unsized", !string_array_equal((const char*[]){"1", "22", "333"}, (const char*[]){"1", "22", "333"}, 0));
    Tests.run("string_array_with_sentinel_from_string_split NO", string_array_with_sentinel_from_string_split(NULL, ',') == NULL);
    char** zz = string_array_with_sentinel_from_string_split("aaa,bbb,ccc,ddd", ',');
    Tests.run("string_array_with_sentinel_from_string_split YES", assigned(zz) && streq(zz[0], "aaa") && streq(zz[1], "bbb") && streq(zz[2], "ccc") && streq(zz[3], "ddd") && zz[4] == NULL);
    string_array_with_sentinel_destroy(zz, 100);
    
    tmp = concat_strings("Hello", "World");
    Tests.run("concat_strings text text", strcmp(tmp, "HelloWorld") == 0);
    free(tmp);
    tmp = concat_strings("Hello", NULL);
    Tests.run("concat_strings text NULL", strcmp(tmp, "Hello") == 0);
    free(tmp);
    tmp = concat_strings(NULL, "World");
    Tests.run("concat_strings NULL text", strcmp(tmp, "World") == 0);
    free(tmp);
    Tests.run("concat_strings NULL NULL", concat_strings(NULL, NULL) == NULL);
    
    char* str_txt1 = strprepend(NULL, "World");
    Tests.run("strprepend to NULL", streq(str_txt1, "World"));
    Tests.print("%s\n", str_txt1);
    str_txt1 = strprepend(str_txt1, "Hello ");
    Tests.run("strprepend to World", streq(str_txt1, "Hello World"));
    Tests.print("%s\n", str_txt1);
    str_txt1 = strenclose(str_txt1, "++", "++");
    Tests.run("strenclose to Hello World", streq(str_txt1, "++Hello World++"));
    Tests.print("%s\n", str_txt1);
    str_txt1 = apostrophe(str_txt1);
    Tests.run("apostrophe to ++Hello World++", streq(str_txt1, "'++Hello World++'"));
    Tests.print("%s\n", str_txt1);
    str_txt1 = quote(str_txt1);
    Tests.run("quote to '++Hello World++'", streq(str_txt1, "\"'++Hello World++'\""));
    Tests.print("%s\n", str_txt1);
    str_txt1 = brace(str_txt1);
    Tests.run("brace to '{\"++Hello World++'\"}", streq(str_txt1, "{\"'++Hello World++'\"}"));
    Tests.print("%s\n", str_txt1);
    str_txt1 = bracketize(str_txt1);
    Tests.run("bracketize to '[{\"++Hello World++'\"}]", streq(str_txt1, "[{\"'++Hello World++'\"}]"));
    Tests.print("%s\n", str_txt1);
    str_txt1 = parenthesize(str_txt1);
    Tests.run("parenthesize to '([{\"++Hello World++'\"}])", streq(str_txt1, "([{\"'++Hello World++'\"}])"));
    Tests.print("%s\n", str_txt1);
    str_txt1 = chevronize(str_txt1);
    Tests.run("chevronize to '<([{\"++Hello World++'\"}])>", streq(str_txt1, "<([{\"'++Hello World++'\"}])>"));
    Tests.print("%s\n", str_txt1);
    free(str_txt1);
    char* str_txt2 = strappend(NULL, "Hello");
    Tests.run("strappend to NULL", streq(str_txt2, "Hello"));
    Tests.print("%s\n", str_txt2);
    str_txt2 = strappend(str_txt2, " World");
    Tests.run("strappend to Hello", streq(str_txt2, "Hello World"));
    Tests.print("%s\n", str_txt2);
    str_txt2 = strappend_twice(str_txt2, " !!!", " :)");
    Tests.run("strappend_twice to Hello World", streq(str_txt2, "Hello World !!! :)"));
    Tests.print("%s\n", str_txt2);
    str_txt2 = strappend_thrice(str_txt2, "1", "2", "3");
    Tests.run("strappend_thrice to Hello World !!! :)", streq(str_txt2, "Hello World !!! :)123"));
    Tests.print("%s\n", str_txt2);
    free(str_txt2);
    Tests.run("count_char test t 2", count_char("test", 't') == 2);
    Tests.run("count_char test x 0", count_char("test", 'x') == 0);
    Tests.run("count_char NULL x -1", count_char(NULL, 'x') == -1);
    Tests.run("left_count_char NULL x -1", left_count_char(NULL, 'x') == -1);
    Tests.run("left_count_char test x 0", left_count_char("test", 'x') == 0);
    Tests.run("left_count_char test t 1", left_count_char("test", 't') == 1);
    Tests.run("left_count_char aabbcc a 2", left_count_char("aabbcc", 'a') == 2);
    Tests.run("right_count_char aabbcc c 2", right_count_char("aabbcc", 'c') == 2);
    Tests.run("right_count_char test t 1", right_count_char("test", 't') == 1);
    Tests.run("right_count_char test x 0", right_count_char("test", 'x') == 0);
    Tests.run("right_count_char NULL x -1", right_count_char(NULL, 'x') == -1);
    Tests.run("starts_with text prefix", starts_with("abcdef", "abc"));
    Tests.run("starts_with text text", starts_with("abc", "abc"));
    Tests.run("starts_with prefix text", !starts_with("abc", "abcdef"));
    Tests.run("starts_with text wrong", !starts_with("abcdef", "d"));
    Tests.run("starts_with text NULL", !starts_with("abcdef", NULL));
    Tests.run("starts_with NULL text", !starts_with(NULL, "blah"));
    Tests.run("starts_with NULL NULL", !starts_with(NULL, NULL));
    Tests.run("ends_with text suffix", ends_with("abcdef", "def"));
    Tests.run("ends_with text text", ends_with("abc", "abc"));
    Tests.run("ends_with text start", !ends_with("abcdef", "abc"));
    Tests.run("ends_with text wrong", !ends_with("abcdef", "d"));
    Tests.run("ends_with text NULL", !ends_with("abcdef", NULL));
    Tests.run("ends_with NULL text", !ends_with(NULL, "blah"));
    Tests.run("ends_with NULL NULL", !ends_with(NULL, NULL));
    tmp = trim_left("  abc");
    Tests.run("trim_left spaces text", streq(tmp, "abc"));
    free(tmp);
    tmp = trim_left("abc  ");
    Tests.run("trim_left text spaces", streq(tmp, "abc  "));
    free(tmp);
    Tests.run("trim_left NULL", trim_left(NULL) == NULL);
    tmp = trim_right("abc  ");
    Tests.run("trim_right text spaces", streq(tmp, "abc"));
    free(tmp);
    tmp = trim_right("  abc");
    Tests.run("trim_right spaces text", streq(tmp, "  abc"));
    free(tmp);
    Tests.run("trim_right NULL", trim_right(NULL) == NULL);
    tmp = trim("  abc  ");
    Tests.run("trim spaces text spaces", streq(tmp, "abc"));
    free(tmp);
    tmp = trim("abc  ");
    Tests.run("trim text spaces", streq(tmp, "abc"));
    free(tmp);
    tmp = trim("  abc");
    Tests.run("trim spaces text", streq(tmp, "abc"));
    free(tmp);
    Tests.run("trim NULL", trim(NULL) == NULL);
    tmp = drop_left("abc", 1);
    Tests.run("drop_left OK 1", streq(tmp, "bc"));
    free(tmp);
    tmp = drop_left("abc", 3);
    Tests.run("drop_left OK 3", streq(tmp, STRINGS_NOTHING));
    free(tmp);
    Tests.run("drop_left NULL", drop_left(NULL, 0) == NULL);
    Tests.run("drop_left 0", drop_left("abc", 0) == NULL);
    Tests.run("drop_left excessive", drop_left("abc", 4) == NULL);
    tmp = drop_right("abc", 1);
    Tests.run("drop_right OK 1", streq(tmp, "ab"));
    free(tmp);
    tmp = drop_right("abc", 3);
    Tests.run("drop_right OK 3", streq(tmp, STRINGS_NOTHING));
    free(tmp);
    Tests.run("drop_right NULL", drop_right(NULL, 0) == NULL);
    Tests.run("drop_right 0", drop_right("abc", 0) == NULL);
    Tests.run("drop_right excessive", drop_right("abc", 4) == NULL);
    tmp = drop_both("abcde", 2);
    Tests.run("drop_both OK", streq(tmp, "c")); 
    free(tmp);
    tmp = drop_both("abcd", 2);
    Tests.run("drop_both OK 2", streq(tmp, STRINGS_NOTHING));
    free(tmp);
    tmp = drop_both("ab", 1);
    Tests.run("drop_both OK 1", streq(tmp, STRINGS_NOTHING));
    free(tmp);
    Tests.run("drop_both NULL", drop_both(NULL, 0) == NULL);
    Tests.run("drop_both 0", drop_both("abc", 0) == NULL);
    Tests.run("drop_both excessive", drop_both("abc", 2) == NULL);
    AUTO_STRING(eee, remove_whitespace(" this is\ta test "));
    Tests.run("remove_whitespace YES", streq(eee, "thisisatest"));
    Tests.run("remove_whitespace NO", remove_whitespace(NULL) == NULL);
    Tests.run("get_last_char NULL CHARS_NULL", get_last_char(NULL) == CHARS_NULL);
    Tests.run("get_last_char empty CHARS_NULL", get_last_char("") == CHARS_NULL);
    Tests.run("get_last_char a a", get_last_char("a") == 'a');
    Tests.run("get_last_char abc c", get_last_char("abc") == 'c');
    const char* args[] = {"-test", "123"};
    tmp = rejoin_arguments(2, args);
    Tests.run("rejoin_arguments 2 args", streq(tmp, "-test 123"));
    free(tmp);
    Tests.run("rejoin_arguments 2 NULL", rejoin_arguments(2, NULL) == NULL);
    Tests.run("rejoin_arguments 1 args", rejoin_arguments(1, args) == NULL);
    Tests.run("rejoin_arguments 0 args", rejoin_arguments(0, args) == NULL);
    Tests.run("rejoin_arguments -1 args", rejoin_arguments(-1, args) == NULL);
    Tests.run("hex_char_to_int A", hex_char_to_int('A') == 10);
    Tests.run("hex_char_to_int a", hex_char_to_int('A') == 10);
    Tests.run("hex_char_to_int Z", hex_char_to_int('Z') == -1);
    unsigned char b = -1;
    Tests.run("hex_string_to_byte OK", hex_string_to_byte("1B", &b) && b == 27);
    Tests.run("hex_string_to_byte OK extra", hex_string_to_byte("1B3", &b) && b == 27);
    Tests.run("hex_string_to_byte absent", !hex_string_to_byte("1B", NULL));
    Tests.run("hex_string_to_byte incomplete", !hex_string_to_byte("1", &b));
    Tests.run("hex_string_to_byte empty", !hex_string_to_byte("", &b));
    Tests.run("hex_string_to_byte NULL", !hex_string_to_byte(NULL, &b));
    string_key_value_dt* kv = string_key_value_parse("username=admin", "|");
    Tests.run("string_key_value_parse bad-sep", assigned(kv) && streq(kv->key, "username=admin") && !has_content(kv->value));
    string_key_value_destroy(kv);
    kv = string_key_value_parse("username=admin", NULL);
    Tests.run("string_key_value_parse null-sep", assigned(kv) && streq(kv->key, "username=admin") && !has_content(kv->value));
    string_key_value_destroy(kv);
    kv = string_key_value_parse("username=admin", NULL);
    Tests.run("string_key_value_parse empty-sep", assigned(kv) && streq(kv->key, "username=admin") && !has_content(kv->value));
    string_key_value_destroy(kv);
    const char* sep = "=";
    kv = string_key_value_parse("username=admin", sep);
    Tests.run("string_key_value_parse username=admin", assigned(kv) && streq(kv->key, "username") && streq(kv->value, "admin"));
    string_key_value_destroy(kv);
    kv = string_key_value_parse("username=admin=extra", sep);
    Tests.run("string_key_value_parse username=admin=extra", assigned(kv) && streq(kv->key, "username") && streq(kv->value, "admin=extra"));
    string_key_value_destroy(kv);
    kv = string_key_value_parse("username=", sep);
    Tests.run("string_key_value_parse username=", assigned(kv) && streq(kv->key, "username") && streq(kv->value, ""));
    string_key_value_destroy(kv);
    kv = string_key_value_parse("=admin", sep);
    Tests.run("string_key_value_parse =admin", assigned(kv) && streq(kv->key, "") && streq(kv->value, "admin"));
    string_key_value_destroy(kv);
    kv = string_key_value_parse("username", sep);
    Tests.run("string_key_value_parse username=", assigned(kv) && streq(kv->key, "username") && !assigned(kv->value));
    string_key_value_destroy(kv);
    kv = string_key_value_parse("=", sep);
    Tests.run("string_key_value_parse =", assigned(kv) && !has_content(kv->key) && !has_content(kv->value));
    string_key_value_destroy(kv);
    kv = string_key_value_parse("", sep);
    Tests.run("string_key_value_parse empty", !assigned(kv));
    kv = string_key_value_parse(NULL, sep);
    Tests.run("string_key_value_parse null", !assigned(kv));
    Tests.run("parse_separated_values", parse_separated_values("abc,def,ghi", ",", print_value));
    sample_ptr = malloc(1);
    Tests.run("parse_separated_values_with_reference", parse_separated_values_with_reference("abc,def,ghi", ",", print_value_with_reference, sample_ptr));
    free(sample_ptr);
    const char* str = "Hello World!! Hello World!!";
    AUTO_STRING(aaa, replace_first_occurrence(str, "World", "Universe"));
    Tests.run("replace_first_occurrence YES", streq(aaa, "Hello Universe!! Hello World!!"));
    Tests.run("replace_first_occurrence NO null1", replace_first_occurrence(NULL, "World", "Universe") == NULL);
    Tests.run("replace_first_occurrence NO null2", replace_first_occurrence(str, NULL, "Universe") == NULL);
    Tests.run("replace_first_occurrence NO null3", replace_first_occurrence(str, "World", NULL) == NULL);
    AUTO_STRING(bbb, replace_first_occurrence(str, "Mundo", "Universe"));
    Tests.run("replace_first_occurrence NO hits", streq(str, bbb));
    AUTO_STRING(ccc, replace_last_occurrence(str, "World", "Universe"));
    Tests.run("replace_last_occurrence YES", streq(ccc, "Hello World!! Hello Universe!!"));
    Tests.run("replace_last_occurrence NO null1", replace_last_occurrence(NULL, "World", "Universe") == NULL);
    Tests.run("replace_last_occurrence NO null2", replace_last_occurrence(str, NULL, "Universe") == NULL);
    Tests.run("replace_last_occurrence NO null3", replace_last_occurrence(str, "World", NULL) == NULL);
    AUTO_STRING(ddd, replace_last_occurrence(str, "Mundo", "Universe"));
    Tests.run("replace_last_occurrence NO hits", streq(str, ddd));
    AUTO_STRING(zzz, replace_all_occurrences(str, "Hello", "Hey"));
    Tests.run("replace_all_occurrences YES", streq(zzz, "Hey World!! Hey World!!"));
    Tests.run("replace_all_occurrences NO null1", replace_all_occurrences(NULL, "World", "Universe") == NULL);
    Tests.run("replace_all_occurrences NO null2", replace_all_occurrences(str, NULL, "Universe") == NULL);
    Tests.run("replace_all_occurrences NO null3", replace_all_occurrences(str, "World", NULL) == NULL);
    AUTO_STRING(yyy, replace_all_occurrences(str, "Mundo", "Universe"));
    Tests.run("replace_all_occurrences NO hits", streq(str, yyy));
    ssize_t x = find_first_index_of(str, "World");
    Tests.run("find_first_index_of YES", x == 6 && str[x] == 'W');
    Tests.run("find_first_index_of NO bad", find_first_index_of(str, "Mundo") == -1);
    Tests.run("find_first_index_of NO null1", find_first_index_of(NULL, "World") == -1);
    Tests.run("find_first_index_of NO null2", find_first_index_of(str, NULL) == -1);
    x = find_last_index_of(str, "World");
    Tests.run("find_last_index_of YES", x == 20 && str[x] == 'W');
    Tests.run("find_last_index_of NO bad", find_last_index_of(str, "Mundo") == -1);
    Tests.run("find_last_index_of NO null1", find_last_index_of(NULL, "World") == -1);
    Tests.run("find_last_index_of NO null2", find_last_index_of(str, NULL) == -1);
    printf(STRINGS_LF);
    Tests.run("measure_string_format", measure_string_format("%s%d", "HEY", 123) == 6);
    AUTO_STRING(sss, format_string("A%sD", "BC"));
    Tests.run("format_string", streq(sss, "ABCD"));
    Tests.run("parse_json_strings_array NO null null", !parse_json_strings_array(NULL, NULL));
    Tests.run("parse_json_strings_array NO null 1", !parse_json_strings_array(NULL, print_parsed_string));
    Tests.run("parse_json_strings_array NO null 2", !parse_json_strings_array("", NULL));
    Tests.run("parse_json_strings_array NO empty", !parse_json_strings_array("", print_parsed_string));
    Tests.run("parse_json_strings_array NO bad item 1", !parse_json_strings_array("[0]", print_parsed_string));
    Tests.run("parse_json_strings_array NO bad item 2", !parse_json_strings_array("[0,\"\"]", print_parsed_string));
    Tests.run("parse_json_strings_array NO bad item 3", !parse_json_strings_array("[\"\",0]", print_parsed_string));
    Tests.run("parse_json_strings_array YES 1", parse_json_strings_array("[]", print_parsed_string));
    Tests.run("parse_json_strings_array YES 2", parse_json_strings_array("[\"\"]", print_parsed_string));
    Tests.run("parse_json_strings_array YES 3", parse_json_strings_array("[\"hello\"]", print_parsed_string));
    Tests.run("parse_json_strings_array YES 4", parse_json_strings_array("[ \"hello\", \"w\\\"orld\", \"line\\nbreak\", \"unicode \\u263A\" ]", print_parsed_string));
    Tests.run("parse_json_strings_array_with_reference NO null null", !parse_json_strings_array_with_reference(NULL, NULL, sample_ptr));
    Tests.run("parse_json_strings_array_with_reference NO null 1", !parse_json_strings_array_with_reference(NULL, print_parsed_string_with_reference, sample_ptr));
    Tests.run("parse_json_strings_array_with_reference NO null 2", !parse_json_strings_array_with_reference("", NULL, sample_ptr));
    Tests.run("parse_json_strings_array_with_reference NO empty", !parse_json_strings_array_with_reference("", print_parsed_string_with_reference, sample_ptr));
    Tests.run("parse_json_strings_array_with_reference NO bad item 1", !parse_json_strings_array_with_reference("[0]", print_parsed_string_with_reference, sample_ptr));
    Tests.run("parse_json_strings_array_with_reference NO bad item 2", !parse_json_strings_array_with_reference("[0,\"\"]", print_parsed_string_with_reference, sample_ptr));
    Tests.run("parse_json_strings_array_with_reference NO bad item 3", !parse_json_strings_array_with_reference("[\"\",0]", print_parsed_string_with_reference, sample_ptr));
    Tests.run("parse_json_strings_array_with_reference YES 1", parse_json_strings_array_with_reference("[]", print_parsed_string_with_reference, sample_ptr));
    Tests.run("parse_json_strings_array_with_reference YES 2", parse_json_strings_array_with_reference("[\"\"]", print_parsed_string_with_reference, sample_ptr));
    Tests.run("parse_json_strings_array_with_reference YES 3", parse_json_strings_array_with_reference("[\"hello\"]", print_parsed_string_with_reference, sample_ptr));
    Tests.run("parse_json_strings_array_with_reference YES 4", parse_json_strings_array_with_reference("[ \"hello\", \"w\\\"orld\", \"line\\nbreak\", \"unicode \\u263A\" ]", print_parsed_string_with_reference, sample_ptr));
    char source[] = "Hello World!";
    char destination[10] = STRINGS_NOTHING;
    Tests.run("copy_substring NO null 1", !copy_substring(NULL, destination, 6, 5) && streq(destination, STRINGS_NOTHING));
    Tests.run("copy_substring NO null 2", !copy_substring(source, NULL, 6, 5) && streq(destination, STRINGS_NOTHING));
    Tests.run("copy_substring NO index", !copy_substring(source, destination, -1, 5) && streq(destination, STRINGS_NOTHING));
    Tests.run("copy_substring NO length", !copy_substring(source, destination, 6, 0) && streq(destination, STRINGS_NOTHING));
    Tests.run("copy_substring YES", copy_substring(source, destination, 6, 5) && streq(destination, "World"));
    int y, m, d;
    Tests.run("parse_xyz_ints_string", parse_xyz_ints_string("2025-11-15", '-', &y, &m, &d) && y == 2025 && m == 11 && d == 15);
    Tests.print("Parsed: year %d, month %d, day %d\n", y, m, d);
    short hh, mm, ss;
    Tests.run("parse_xyz_shorts_string", parse_xyz_shorts_string("23:59:59", ':', &hh, &mm, &ss) && hh == 23 && mm == 59 && ss == 59);
    Tests.print("Parsed: hours %hd, minutes %hd, seconds %hd\n", hh, mm, ss);
    long d1, d2, d3;
    Tests.run("parse_xyz_longs_string", parse_xyz_longs_string("19780625;19860629;20221218", ';', &d1, &d2, &d3) && d1 == 19780625L && d2 == 19860629L && d3 == 20221218L);
    Tests.print("Parsed: wc1 %ld, wc2 %ld, wc3 %ld\n", d1, d2, d3);
    long l1, l2, l3;
    Tests.run("parse_xyz_longs_string", parse_xyz_longs_string("19780625123;19860629123;20221218123", ';', &l1, &l2, &l3) && l1 == 19780625123LL && l2 == 19860629123LL && l3 == 20221218123LL);
    Tests.print("Parsed: ll1 %ld, ll2 %ld, ll3 %ld\n", d1, d2, d3);
    float t0, t1, t2;
    Tests.run("parse_xyz_floats_string", parse_xyz_floats_string("30.5,0.25,-5.75", ',', &t0, &t1, &t2) && float_equal(t0, 30.5, 0.00001) && float_equal(t1, 0.25, 0.00001) && float_equal(t2, -5.75, 0.00001));
    Tests.print("Parsed: t0 %f, t1 %f, t2 %f\n", t0, t1, t2);
    double lon, lat, alt;
    Tests.run("parse_xyz_doubles_string", parse_xyz_doubles_string("-58.521461,-34.600583,0.0", ',', &lon, &lat, &alt) && double_equal(lon, -58.521461, 0.00001) && double_equal(lat, -34.600583, 0.00001) && double_equal(alt, 0.0, 0.00001));
    Tests.print("Parsed: longitude %f, latitude %f, altitude %f\n", lon, lat, alt);
    long double ld1, ld2, ld3;
    Tests.run("parse_xyz_long_doubles_string", parse_xyz_long_doubles_string("-58.521461,-34.600583,0.0", ',', &ld1, &ld2, &ld3) && long_double_equal(ld1, -58.521461, 0.00001) && long_double_equal(ld2, -34.600583, 0.00001) && long_double_equal(ld3, 0.0, 0.00001));
    Tests.print("Parsed: longitude %Lf, latitude %Lf, altitude %Lf\n", ld1, ld2, ld3);
    char tmpc = validate_numeric_xx_yy_zz_string(NULL);
    Tests.run("validate_numeric_xx_yy_zz_string NO null", tmpc == CHARS_NULL);
    tmpc = validate_numeric_xx_yy_zz_string("xx:yy:zz");
    Tests.run("validate_numeric_xx_yy_zz_string NO numeric", tmpc == CHARS_NULL);
    tmpc = validate_numeric_xx_yy_zz_string("11.22");
    Tests.run("validate_numeric_xx_yy_zz_string NO short", tmpc == CHARS_NULL);
    tmpc = validate_numeric_xx_yy_zz_string("11:22:33:44");
    Tests.run("validate_numeric_xx_yy_zz_string NO large", tmpc == CHARS_NULL);
    tmpc = validate_numeric_xx_yy_zz_string("11.22:33");
    Tests.run("validate_numeric_xx_yy_zz_string NO diff", tmpc == CHARS_NULL);
    tmpc = validate_numeric_xx_yy_zz_string("11:22:33");
    Tests.run("validate_numeric_xx_yy_zz_string YES", tmpc == CHARS_COLON);
}

void test_dbg_utilities() {
    Tests.run("DEVELOPMENT", DEVELOPMENT == false);
    debug_text("DEV mode is OFF by default");
    DEVELOPMENT = true;
    debug_text("DEV mode is now ON");
    char arr[11] = { BYTES_12, BYTES_34, BYTES_56, BYTES_78, BYTES_9A, BYTES_BC, BYTES_DE, BYTES_F0, BYTES_33, BYTES_22, BYTES_11 };
    debug_hex(arr, 11, 4, " ");
    DEVELOPMENT = false;
    debug_hex(arr, 11, 4, " ");
    debug_text("DEV mode is OFF again");
    printf("\n");
    
    uint8_t val = 0b10010110;  // 150 decimal, 0x96
    uint8_t rotated_left = rol8(val, 3); // 0xB4, 0b10110100
    uint8_t rotated_right = ror8(val, 3); // 0xD2, 0b11010010
    printf("Original: 0x%02X\n", val);
    printf("Original (binary): ");
    print_binary8(val);
    printf("\n");
    printf("ROL 3:    0x%02X\n", rotated_left);
    printf("ROL 3 (binary): ");
    print_binary8(rotated_left);
    printf("\n");
    printf("ROR 3:    0x%02X\n", rotated_right);
    printf("ROR 3 (binary): ");
    print_binary8(rotated_right);
    printf("\n");
    printf("\n");
}

void show_ptr_int_item(__unused kewl_ptrholder_dt* arr, kewl_ptrholder_ptr_dt ptr) {
    if (ptr) {
        Tests.print("This element points to number: %d\n", *(int*)ptr);
    } else
        Tests.print("This element points to nothing\n");
}

void show_ptr_int_item_ref(__unused kewl_ptrholder_dt* arr, kewl_ptrholder_ptr_dt ptr, void* ref) {
    if (ptr) {
        Tests.print("This element points to number (ref): %d (%p)\n", *(int*)ptr, ref);
    } else
        Tests.print("This element points to nothing\n");
}

void test_ptrholder() {
    kewl_ptrholder_dt* da = kewl_ptrholder_create(2);
    Tests.run("kewl_ptrholder_create", da != NULL);
    if (da == NULL) return;
    size_t sz = kewl_ptrholder_get_size(da);
    Tests.run("kewl_ptrholder_get_size", sz == 0);
    Tests.print("Element count at array: %zu\n", sz);
    size_t cz = kewl_ptrholder_get_capacity(da);
    Tests.run("kewl_ptrholder_get_capacity", cz > 0);
    Tests.print("Capacity: %zu\n", cz);
    Tests.run("kewl_ptrholder_add NULL", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)NULL));
    int a = 123;
    Tests.run("kewl_ptrholder_has &a NO", !kewl_ptrholder_has(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.run("kewl_ptrholder_add &a", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.print("Element count at array: %zu\n", kewl_ptrholder_get_size(da));
    Tests.run("kewl_ptrholder_has &a YES", kewl_ptrholder_has(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.run("kewl_ptrholder_delete_once &a", kewl_ptrholder_delete_once(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.print("Element count at array: %zu\n", kewl_ptrholder_get_size(da));
    Tests.run("kewl_ptrholder_has &a NO", !kewl_ptrholder_has(da, (kewl_ptrholder_ptr_dt)&a));
    int b = 456, c = 789;
    Tests.run("kewl_ptrholder_add &a", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.run("kewl_ptrholder_add &b", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&b));
    Tests.run("kewl_ptrholder_add &c (triggers auto grow)", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&c));
    Tests.print("Element count at array: %zu\n", kewl_ptrholder_get_size(da));
    Tests.print("Capacity: %zu\n", kewl_ptrholder_get_capacity(da));
    Tests.run("kewl_ptrholder_grow_capacity MANUAL", kewl_ptrholder_grow_capacity(da, 1.5f, 0.5f));
    Tests.print("Capacity: %zu\n", kewl_ptrholder_get_capacity(da));
    Tests.run("kewl_ptrholder_grow_capacity 0.0 0.0", kewl_ptrholder_grow_capacity(da, 0.0f, 0.0f));
    Tests.print("Capacity: %zu\n", kewl_ptrholder_get_capacity(da));
    kewl_ptrholder_loop(da, show_ptr_int_item);
    kewl_ptrholder_loop_with_reference(da, show_ptr_int_item_ref, da);
    char* s = kewl_ptrholder_stringify(da, ';');
    Tests.run("kewl_ptrholder_stringify", s != NULL);
    if (s != NULL) {
        Tests.print("%s\n", s);
        free(s);
    }
    kewl_ptrholder_clear(da);
    Tests.run("kewl_ptrholder_clear", kewl_ptrholder_get_size(da) == 0);
    Tests.print("Element count at array: %zu\n", kewl_ptrholder_get_size(da));
    kewl_ptrholder_set_capacity_grow_factor(da, 1.5f);
    Tests.print("Capacity grow factor: %f\n", kewl_ptrholder_get_capacity_grow_factor(da));
    kewl_ptrholder_set_capacity_grow_padding(da, 0.5f);
    Tests.print("Capacity grow padding: %f\n", kewl_ptrholder_get_capacity_grow_padding(da));
    Tests.print("Capacity: %zu\n", kewl_ptrholder_get_capacity(da));
    Tests.run("kewl_ptrholder_add &a", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.run("kewl_ptrholder_add &a", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.run("kewl_ptrholder_add &a", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.run("kewl_ptrholder_add &a", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.run("kewl_ptrholder_add &b", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&b));
    Tests.run("kewl_ptrholder_add &b", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&b));
    Tests.run("kewl_ptrholder_add &b", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&b));
    Tests.run("kewl_ptrholder_get_capacity 7", kewl_ptrholder_get_capacity(da) == 7);
    Tests.run("kewl_ptrholder_add &c (triggers auto grow)", kewl_ptrholder_add(da, (kewl_ptrholder_ptr_dt)&c));
    Tests.run("kewl_ptrholder_get_capacity 11", kewl_ptrholder_get_capacity(da) == 11);
    Tests.run("kewl_ptrholder_replace_every &a &b", kewl_ptrholder_replace_every(da, (kewl_ptrholder_ptr_dt)&a, (kewl_ptrholder_ptr_dt)&b));
    Tests.run("kewl_ptrholder_has &a NO", !kewl_ptrholder_has(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.run("kewl_ptrholder_replace_once &c &a", kewl_ptrholder_replace_once(da, (kewl_ptrholder_ptr_dt)&c, (kewl_ptrholder_ptr_dt)&a));
    Tests.run("kewl_ptrholder_has &c NO", !kewl_ptrholder_has(da, (kewl_ptrholder_ptr_dt)&c));
    Tests.run("kewl_ptrholder_has &a YES", kewl_ptrholder_has(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.run("kewl_ptrholder_delete_every &b", kewl_ptrholder_delete_every(da, (kewl_ptrholder_ptr_dt)&b));
    Tests.run("kewl_ptrholder_has &b NO", !kewl_ptrholder_has(da, (kewl_ptrholder_ptr_dt)&b));
    Tests.run("kewl_ptrholder_has &a YES", kewl_ptrholder_has(da, (kewl_ptrholder_ptr_dt)&a));
    Tests.run("kewl_ptrholder_get_size 1", kewl_ptrholder_get_size(da) == 1);
    kewl_ptrholder_destroy(da);
}

void task_initializer(kewl_task_dt* task) {
    Tests.print("Initializing task: %s\n", kewl_task_get_id_label(task));
}
int task_routine(kewl_task_dt* task) {
    void* input_data = kewl_task_get_input_data(task);
    Tests.print("Running task: %s\n", kewl_task_get_id_label(task));
    Tests.print("Input Data: %p\n", input_data);
    kewl_task_set_output_data(task, input_data);
    return assigned(input_data) ? 0 : 1;
}
void task_finalizer(kewl_task_dt* task) {
    Tests.print("Finalizing task: %s\n", kewl_task_get_id_label(task));
}
void test_task() {
    kewl_task_dt* task = kewl_task_create("test");
    Tests.run("kewl_task_create", task != NULL);
    kewl_task_set_initializer(task, task_initializer);
    kewl_task_set_routine(task, task_routine);
    kewl_task_set_finalizer(task, task_finalizer);
    bool gs = kewl_task_get_state(task) == KEWL_TASK_UNINITIALIZED;
    Tests.run("kewl_task_get_state UNINITIALIZED", gs);
    if (gs) {
        Tests.print("Prepared task to run: %s\n", kewl_task_get_id_label(task));
        Tests.print("Times executed: %d\n", kewl_task_get_execution_times(task));
    }
    bool ge = kewl_task_execute(task);
    Tests.run("kewl_task_execute ONCE", ge);
    if (!ge) {
        Tests.print("Failed to execute task: %s\n", kewl_task_get_id_label(task));
    } else {
        Tests.print("Successfully executed task: %s\n", kewl_task_get_id_label(task));
        Tests.print("Exit value: %d\n", kewl_task_get_exit_value(task));
        Tests.print("Output data: %p\n", kewl_task_get_output_data(task));
    }
    bool gf = kewl_task_get_state(task) == KEWL_TASK_FINALIZED;
    Tests.run("kewl_task_get_state FINALIZED", gf);
    if (gf) {
        Tests.print("Prepared task to rerun: %s\n", kewl_task_get_id_label(task));
        Tests.print("Times executed: %d\n", kewl_task_get_execution_times(task));
    }
    kewl_task_set_context_data(task, &test_task);
    Tests.run("kewl_task_get/set_context_data", kewl_task_get_context_data(task) == &test_task);
    char hello[5] = "hello";
    Tests.print("Setting some input data to the task...\n");
    kewl_task_set_input_data(task, &hello);
    Tests.run("kewl_task_get/set_input_data", kewl_task_get_input_data(task) == &hello);
    bool gn = kewl_task_execute(task);
    Tests.run("kewl_task_execute TWICE", gn);
    if (!gn) {
        Tests.print("Failed to rerun task: %s\n", kewl_task_get_id_label(task));
    } else {
        Tests.print("Successfully executed task again: %s\n", kewl_task_get_id_label(task));
        Tests.print("Exit value: %d\n", kewl_task_get_exit_value(task));
        Tests.print("Output data: %p\n", kewl_task_get_output_data(task));
    }
    bool gz = kewl_task_get_state(task) == KEWL_TASK_FINALIZED;
    Tests.run("kewl_task_get_state FINALIZED AGAIN", gz);
    if (gz) {
        Tests.print("task: %s\n", kewl_task_get_id_label(task));
        Tests.print("Times executed: %d\n", kewl_task_get_execution_times(task));
    }
    kewl_task_destroy(task);
    Tests.print("sizeof(kewl_task_dt) = %lu\n", sizeof(kewl_task_dt));
}

void test_component() {
    void* ts = NULL;
    kewl_component_dt* tc = kewl_component_create(&ts, "Sample");
    Tests.run("kewl_component_create", assigned(tc));
    Tests.run("kewl_component_get_instance_number", kewl_component_get_instance_number(tc) == 1);
    Tests.run("kewl_component_get_type_instance", kewl_component_get_type_instance(tc) == &ts);
    Tests.run("kewl_component_get_type_name", streq(kewl_component_get_type_name(tc), "Sample"));
    Tests.run("kewl_component_get_instance_name", streq(kewl_component_get_instance_name(tc), "Sample1"));
    kewl_component_dt* tc2 = kewl_component_create(&ts, "Sample");
    Tests.run("kewl_component_get_instance_number", kewl_component_get_instance_number(tc2) == 2);
    Tests.run("kewl_component_get_instance_name", streq(kewl_component_get_instance_name(tc2), "Sample2"));
    Tests.run("kewl_component_get_owner", kewl_component_get_owner(tc2) == NULL);
    kewl_component_set_owner(tc2, tc);
    Tests.run("kewl_component_set_owner", kewl_component_get_owner(tc2) == tc);
    kewl_component_dt* tc3 = kewl_component_create(&ts, "Sample");
    Tests.run("kewl_component_get_instance_number", kewl_component_get_instance_number(tc3) == 3);
    Tests.run("kewl_component_get_owner", kewl_component_get_owner(tc3) == NULL);
    kewl_component_set_owner(tc2, tc3);
    Tests.run("kewl_component_set_owner", kewl_component_get_owner(tc2) != tc);
    Tests.run("kewl_component_get_tag", kewl_component_get_tag(tc3) == NULL);
    kewl_component_set_tag(tc3, tc2);
    Tests.run("kewl_component_set_tag", kewl_component_get_tag(tc3) == tc2);
    kewl_component_destroy(tc);
    kewl_component_destroy(tc2);
    kewl_component_destroy(tc3);
}

int main(void) {
    Tests.begin("KeWL");
    AUTO_STRING(ts, get_timestamp());
    printf("Executing Kewl tests at %s\n\n", ts);
#ifdef __posix93
    float elapsed_ms;
    MEASURE_MS(elapsed_ms,
#endif
    {
        printf("--- STRHASHSET ---\n");
        test_strhashset();
        printf("\n");

        printf("--- STRHASHBAG ---\n");
        test_strhashbag();
        printf("\n");
        
        printf("--- MATH ---\n");
        test_mth_utilities();
        printf("\n");
        
        printf("--- STRING ---\n");
        test_str_functions();
        printf("\n");
        
        printf("--- DEBUG ---\n");
        test_dbg_utilities();
        printf("\n");

        printf("--- FILESYSTEM ---\n");
        test_fs_utilities();
        printf("\n");

        printf("--- DATETIME ---\n");
        test_datetime_utilities();
        printf("\n");
        
        printf("--- STREAM ---\n");
        test_stream_functions();
        printf("\n");

        printf("--- PTRHOLDER ---\n");
        test_ptrholder();
        printf("\n");
        
        printf("--- SAMPLEPROFILER ---\n");
        test_sampleprofiler();
        printf("\n");
        
        printf("--- TASK ---\n");
        test_task();
        printf("\n");
        
        printf("--- CMDLINE ---\n");
        test_cmdline();
        printf("\n");
        
        printf("--- COMPONENT ---\n");
        test_component();
        printf("\n");
        
        if (truthy() && !falsy()) printf("done\n");
        noop();
#ifndef __posix93
    }
#else
        nap(123);
    });
    AUTO_STRING(ds, get_formatted_date_time(DATETIME_FORMAT_DDMMYYYY_HHMMSS));
    printf("\nBlock executed at %s in %.3f ms\n", ds, elapsed_ms);
#endif
    return Tests.end();
}

