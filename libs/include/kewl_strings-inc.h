/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_strings-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

#include <ctype.h>
#include <float.h>

// ENSURE

static inline const char* ensure_const_string(const char* str) {
    return str == NULL ? STRINGS_NOTHING : str;
}

static inline const char* ensure_const_string_def(const char* str, const char* def) {
    return str == NULL ? def : str;
}

static inline char* ensure_new_string(const char* str) {
    return strdup(str == NULL ? STRINGS_NOTHING : str);
}

static inline char* ensure_new_string_def(const char* str, const char* def) {
    return strdup(str == NULL ? def : str);
}

// INSPECTION

static inline bool has_content(const char* str) {
    return assigned(str) && *str != CHARS_NULL; // quicker than (strlen(str) > 0) and more verbose than (str && *str)
}

bool is_ascii_string(const char* str);
bool is_ascii_readable_string(const char* str);
bool is_hex_string(const char* str);
bool is_alphanumeric_string(const char* str);
bool is_numeric_string(const char* str);
bool is_uppercase_string(const char* str);
bool is_lowercase_string(const char* str);

static inline bool streq(const char* a, const char* b) {
    return both_assigned(a, b) && strcmp(a, b) == 0;
}

static inline bool contains_string(const char* container, const char* contained) {
    return assigned(container) && assigned(contained) && assigned(strstr(container, contained));
}

bool starts_with(const char* str, const char* pfx);
bool ends_with(const char* str, const char* sfx);

ssize_t find_first_index_of(const char* str, const char* target);
ssize_t find_last_index_of(const char* str, const char* target);

ssize_t get_utf8_string_length(const char* str);

// CHARACTERS

static inline bool is_ascii_char(char chr) {
    return (unsigned char)chr <= 127;
}

static inline bool is_ascii_readable_char(char chr) {
    return (chr >= 32 && chr <= 126);
}

static inline bool is_uppercase_char(char chr) {
    return (chr >= 'A' && chr <= 'Z');
}

static inline bool is_lowercase_char(char chr) {
    return (chr >= 'a' && chr <= 'f');
}

static inline bool is_digit_char(char chr) {
    return (chr >= '0' && chr <= '9');
}

static inline bool is_hex_char(char chr) {
    return (chr >= '0' && chr <= '9') ||
           (chr >= 'a' && chr <= 'f') ||
           (chr >= 'A' && chr <= 'F');
}

bool contains_char(const char* str, char chr);
ssize_t count_char(const char* str, char chr);
ssize_t left_count_char(const char* str, char chr);
ssize_t right_count_char(const char* str, char chr);
char* prepend_char(const char* str, char chr);
char* append_char(const char* str, char chr);
char* remove_char(const char* str, char chr);

static inline char get_last_char(const char* str) {
    return has_content(str) ? str[strlen(str) - 1] : CHARS_NULL;
}

static inline bool treat_chars(char* str, ssize_t limit, trt_char_fn treater) {
    if (str == NULL || treater == NULL || limit < 1) return false;
    for (int i = 0; str[i] != CHARS_NULL; i++) {
        if (i == limit) return false;
        str[i] = treater(str[i]);
    }
    return true;
}

// CONVERSION

#define strchar(value) ((char[2]){value, CHARS_NULL})

static inline char bool_to_int_char(bool value) {
    return value ? CHARS_NUMBER_ONE : CHARS_NUMBER_ZERO;
}

static inline const char* strbool(bool value) {
    return value ? "true" : "false";
}

bool str_to_bool(const char* str);
signed char str_to_signed_char_def(const char* str, signed char default_value);
unsigned char str_to_unsigned_char_def(const char* str, unsigned char default_value);
short str_to_short_def(const char* str, short default_value);
unsigned short str_to_unsigned_short_def(const char* str, unsigned short default_value);
int str_to_int_def(const char* str, int default_value);
unsigned int str_to_unsigned_int_def(const char* str, unsigned int default_value);
long str_to_long_def(const char* str, long default_value);
unsigned long str_to_unsigned_long_def(const char* str, unsigned long default_value);
long long str_to_long_long_def(const char* str, long long default_value);
unsigned long long str_to_unsigned_long_long_def(const char* str, unsigned long long default_value);
int8_t str_to_int8_def(const char* str, int8_t default_value);
uint8_t str_to_uint8_def(const char* str, uint8_t default_value);
int16_t str_to_int16_def(const char* str, int16_t default_value);
uint16_t str_to_uint16_def(const char* str, uint16_t default_value);
int32_t str_to_int32_def(const char* str, int32_t default_value);
uint32_t str_to_uint32_def(const char* str, uint32_t default_value);
int64_t str_to_int64_def(const char* str, int64_t default_value);
uint64_t str_to_uint64_def(const char* str, uint64_t default_value);
float str_to_float_def(const char* str, float default_value);
double str_to_double_def(const char* str, double default_value);
long double str_to_long_double_def(const char* str, long double default_value);

char* char_to_str(char value);
char* signed_char_to_str(signed char value);
char* unsigned_char_to_str(unsigned char value);
char* short_to_str(short value);
char* unsigned_short_to_str(unsigned short value);
char* int_to_str(int value);
char* unsigned_int_to_str(unsigned int value);
char* long_to_str(long value);
char* unsigned_long_to_str(unsigned long value);
char* long_long_to_str(long long value);
char* unsigned_long_long_to_str(unsigned long long value);
char* float_to_str(float value); // with 3 decimals
char* double_to_str(double value); // with 8 decimals
char* long_double_to_str(long double value);
char* int8_to_str(int8_t value);
char* uint8_to_str(uint8_t value);
char* int16_to_str(int16_t value);
char* uint16_to_str(uint16_t value);
char* int32_to_str(int32_t value);
char* uint32_to_str(uint32_t value);
char* int64_to_str(int64_t value);
char* uint64_to_str(uint64_t value);
char* bool_to_str(bool value);

char* ptr_to_str(void* value);

char* bytes_to_hex(const uint8_t* bytes, ssize_t size);
bool hex_to_bytes(const char* hex_str, uint8_t** out_bytes, ssize_t* out_len);

// Function to convert a single hex character to its integer value
static inline int hex_char_to_int(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'f') return 10 + (c - 'a');
    if ('A' <= c && c <= 'F') return 10 + (c - 'A');
    return -1;
}

// Convert a hex string (2 characters) to a byte
static inline bool hex_string_to_byte(const char* hex_str, unsigned char* byte) {
    if (hex_str == NULL || byte == NULL) return false;
    int high = hex_char_to_int(hex_str[0]);
    int low = hex_char_to_int(hex_str[1]);
    if (high == -1 || low == -1) return false;
    *byte = (unsigned char)((high << 4) | low);
    return true;
}

// UTF-8

// Returns the number of bytes in a UTF-8 character (-1 if the provided char is not a valid UTF-8 start byte)
static inline int8_t get_utf8_char_length(char c) {
#ifdef __c23
    if ((c & 0b11111000) == 0b11110000) return 4; // 4-byte char
    if ((c & 0b11110000) == 0b11100000) return 3; // 3-byte char
    if ((c & 0b11100000) == 0b11000000) return 2; // 2-byte char
    if ((c & 0b10000000) == 0b00000000) return 1; // 1-byte char (ASCII)
#else
    unsigned char uc = (unsigned char)c;
    if ((uc & 0xF8) == 0xF0) return 4; // 4-byte char (11110xxx)
    if ((uc & 0xF0) == 0xE0) return 3; // 3-byte char (1110xxxx)
    if ((uc & 0xE0) == 0xC0) return 2; // 2-byte char (110xxxxx)
    if ((uc & 0x80) == 0x00) return 1; // 1-byte char ASCII (0xxxxxxx)
#endif
    return -1; // continuation byte or invalid
}

// It decodes \uXXXX unicode escape into UTF-8 bytes and returns the number of UTF-8 bytes written, 0 if invalid
int decode_utf8_escape(const char* str, char* out);

// MUTATION

// Unescape single characters from the provided string. Note that multiple character escapes like Octal (\nnn), Hex (\xnn), etc, are not unscaped.
char* unescape_single_chars(const char* src);

char* strreverse(char* str);
char* to_lower_case(const char* str);
char* to_upper_case(const char* str);

// STRING ARRAY

char** string_array_create(ssize_t size, const char* default_value);
char** string_array_with_sentinel_create(ssize_t size, const char* default_value);
char** string_array_with_sentinel_from_string_split(const char* str, char separator);
char** string_array_replace_segment(const char* array[], ssize_t arr_len, ssize_t from, ssize_t to, const char* source[], ssize_t src_len, ssize_t* out_len);
static inline ssize_t string_array_find_null_sentinel(const char* array[], ssize_t limit) {
    ssize_t i = 0;
    if (assigned(array)) while (assigned(array[i]) && limit > i) i++;
    return i == limit ? -1 : i;
}
ssize_t string_array_find_first_null(ssize_t size, const char* array[]);
ssize_t string_array_find_first(ssize_t size, const char* array[], const char* target);
ssize_t string_array_find_last(ssize_t size, const char* array[], const char* target);
static inline bool string_array_contains(ssize_t size, const char* array[], const char* target) {
    return string_array_find_first(size, array, target) > -1;
}
char* string_array_join_range(ssize_t size, const char* array[], ssize_t from, ssize_t to, const char* separator);
static inline char* string_array_join(ssize_t size, const char* array[], const char* separator) {
    return string_array_join_range(size, array, 0, size - 1, separator);
}
ssize_t string_array_count_occurrences(ssize_t size, const char* array[], const char* target);
void string_array_sort(ssize_t size, char* array[]);
void string_array_reversed_sort(ssize_t size, char* array[]);
void string_array_shuffle(ssize_t size, char* array[], fn_int_fn rand_func);
bool string_array_hex_validate(ssize_t size, const char* array[]);
static inline bool string_array_equal(const char* array1[], const char* array2[], ssize_t size) {
    if (array1 == NULL || array2 == NULL || size < 1) return false;
    for (ssize_t i = 0; i < size; i++)
        if (strcmp(array1[i], array2[i]) != 0)
            return false;
    return true;
}
static inline bool string_array_treat(ssize_t size, char* array[], trt_string_fn treater) {
    if (array == NULL || treater == NULL || size < 1) return false;
    for (ssize_t i = 0; i < size; i++)
        array[i] = treater(array[i]);
    return true;
}
static inline void string_array_destroy(char* array[], ssize_t size) {
    FREE_ARRAY_ITEMS(array, size);
    ce_free(array);
}
static inline void string_array_with_sentinel_destroy(char* array[], ssize_t limit) {
    if (assigned(array)) {
        ssize_t size = string_array_find_null_sentinel((const char**)array, limit);
        if (size > 0)
            FREE_ARRAY_ITEMS(array, size);
        ce_free(array);
    }
}

// CONCATENATION/JOIN

char* strprepend(char* str, const char* src);
char* strappend(char* str, const char* src);
char* strappend_twice(char* str, const char* src1, const char* src2);
char* strappend_thrice(char* str, const char* src1, const char* src2, const char* src3);
char* strenclose(char* str, const char* prefix, const char* suffix);

#define apostrophe(str) strenclose(str, STRINGS_APOSTROPHE, STRINGS_APOSTROPHE)
#define quote(str) strenclose(str, STRINGS_QUOTE, STRINGS_QUOTE)
#define brace(str) strenclose(str, STRINGS_BRACES_OPEN, STRINGS_BRACES_CLOSE)
#define bracketize(str) strenclose(str, STRINGS_BRACKETS_OPEN, STRINGS_BRACKETS_CLOSE)
#define parenthesize(str) strenclose(str, STRINGS_PARENTHESES_OPEN, STRINGS_PARENTHESES_CLOSE)
#define chevronize(str) strenclose(str, STRINGS_MINOR, STRINGS_MAJOR)

char* concat_strings(const char* str1, const char* str2);

static inline char* rejoin_arguments(int argc, const char* argv[]) {
    return argc <= 1 || argv == NULL ? NULL : string_array_join_range(argc, argv, 0, argc - 1, " ");
}

// PARSE/SPLIT

typedef void (*parsed_string_callback)(const char* value);

typedef void (*parsed_string_callback_with_reference)(const char* value, const void* reference);

bool parse_separated_values(const char* text, const char* separator, parsed_string_callback callback);

bool parse_separated_values_with_reference(const char* text, const char* separator, parsed_string_callback_with_reference callback, const void* reference);

// Parse JSON array of strings with escapes and calls the callback with each string
bool parse_json_strings_array(const char* json, parsed_string_callback callback);

// Parse JSON array of strings with escapes and calls the callback with each string and the provided reference
bool parse_json_strings_array_with_reference(const char* json, parsed_string_callback_with_reference callback, const void* reference);

// SANITIZATION

char* trim_right(const char* str);
char* trim_left(const char* str);
char* trim(const char* str);
char* drop_left(const char* str, size_t amount);
char* drop_right(const char* str, size_t amount);
char* drop_both(const char* str, size_t amount);
char* remove_whitespace(const char* str);

// KEY-VALUE

typedef struct {
    char* key;
    char* value;
} string_key_value_dt;

string_key_value_dt* string_key_value_parse(const char* input, const char* separator);

static inline void string_key_value_destroy(string_key_value_dt* kv) {
    if (kv == NULL) return;
    ce_free(kv->key);
    ce_free(kv->value);
    ce_free(kv);
}

// REPLACEMENT

// Returns a new string with the first occurrence of 'target' replaced by 'replacement' in 'str'.
char* replace_first_occurrence(const char* str, const char* target, const char* replacement);

// Returns a new string with the last occurrence of 'target' replaced by 'replacement' in 'str'.
char* replace_last_occurrence(const char* str, const char* target, const char* replacement);

// Returns a new string with all occurrences of 'target' replaced by 'replacement' in 'str'.
char* replace_all_occurrences(const char* str, const char* target, const char* replacement);

// Returns a new string with the portion starting at 'pos' with a size of 'len' replaced with the 'rep' content.
char* replace_substring(const char* str, ssize_t pos, ssize_t len, const char* rep);

// FORMATTING

ssize_t measure_string_format(const char* fmt, ...);
ssize_t get_string_format_size(const char* fmt, va_list args);
char* perform_string_format(ssize_t size, const char* fmt, va_list args);
char* format_string(const char* fmt, ...);

// RETRIEVAL

static inline bool copy_substring(const char* src, char* dst, int pos, int len) {
    if (both_assigned(src, dst) && pos >= 0 && len > 0) {
        for (int i = 0; i < len; i++)
            dst[i] = src[pos + i];
        dst[len] = CHARS_NULL;
        return true;
    }
    return false;
}

bool parse_xyz_shorts_string(const char* text, char separator, short* x, short* y, short* z);
bool parse_xyz_ints_string(const char* text, char separator, int* x, int* y, int* z);
bool parse_xyz_longs_string(const char* text, char separator, long* x, long* y, long* z);
bool parse_xyz_long_longs_string(const char* text, char separator, long long* x, long long* y, long long* z);
bool parse_xyz_floats_string(const char* text, char separator, float* x, float* y, float* z);
bool parse_xyz_doubles_string(const char* text, char separator, double* x, double* y, double* z);
bool parse_xyz_long_doubles_string(const char* text, char separator, long double* x, long double* y, long double* z);

// Returns the separator char after validating a xx yy format of numeric pairs (of 2 integer digits each), otherwise returns '\0'. Useful for hh:mm, dd/mm, etc.
char validate_numeric_xxcyy_string(const char* text);

// Returns the separator char after validating a xx yy zz format of numeric pairs, otherwise returns '\0'. Useful for hh:mm:ss, dd/mm/yy, etc.
char validate_numeric_xxcyyczz_string(const char* text);

