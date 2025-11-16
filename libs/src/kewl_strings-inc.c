/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_strings-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include <strings.h> /* strcasecmp */

// Returns the number of UTF-8 characters (code points) in a null-terminated UTF-8 encoded string.
// Returns -1 if an invalid UTF-8 sequence is encountered or if the provided string is NULL.
ssize_t get_utf8_string_length(const char* str) {
    if (str == NULL) return -1;
    ssize_t length = 0;
    const unsigned char* p = (const unsigned char*)str;
    while (*p) {
        ssize_t char_len = get_utf8_char_length(*p);
        if (char_len == -1) // Invalid UTF-8 start byte
            return -1;
        // Verify continuation bytes start with '10xxxxxx'
        for (ssize_t i = 1; i < char_len; i++)
        #ifdef __c23
            if ((p[i] & 0b11000000) != 0b10000000) // Invalid continuation byte
        #else
            if ((p[i] & 0xC0) != 0x80)
        #endif
                return -1;
        p += char_len;
        length++;
    }
    return length;
}

bool is_ascii_string(const char* str) {
    if (str == NULL || str[0] == CHARS_NULL) return false;
    for (int i = 0; str[i] != CHARS_NULL; i++)
        if (!is_ascii_char(str[i]))
            return false;
    return true;
}

bool is_hex_string(const char* str) {
    if (str == NULL || str[0] == CHARS_NULL) return false;
    for (int i = 0; str[i] != CHARS_NULL; i++)
        if (!is_hex_char(str[i]))
            return false;
    return true;
}

bool is_alphanumeric_string(const char* str) {
    if (str == NULL || str[0] == CHARS_NULL) return false;
    for (int i = 0; str[i] != CHARS_NULL; i++)
        if (!isalnum((unsigned char)str[i]))
            return false;
    return true;
}

bool is_numeric_string(const char* str) {
    if (str == NULL || str[0] == CHARS_NULL) return false; // Empty string or NULL pointer
    int i = 0;
    if (str[i] == CHARS_PLUS || str[i] == CHARS_MINUS) i++; // Optional sign
    // Check each character
    int dot_count = 0;
    bool digit_found = false;
    for (; str[i]; i++) {
        if (isdigit((unsigned char)str[i])) {
            digit_found = true;
        } else if (str[i] == CHARS_PERIOD) {
            if (dot_count++ > 0) return false; // Multiple decimals
        } else
            return false; // Invalid character
    }
    return digit_found; // Must have at least one digit
}

bool contains_char(const char* str, char chr) {
    if (assigned(str))
        while (*str != CHARS_NULL) {
            if (*str == chr)
                return true;
            str++;
        }
    return false;
}

ssize_t count_char(const char* str, char chr) {
    if (str == NULL) return -1;
    ssize_t result = 0;
    while (*str != CHARS_NULL) {
        if (*str == chr)
            result++;
        str++;
    }
    return result;
}

ssize_t left_count_char(const char* str, char chr) {
    if (str == NULL) return -1;
    ssize_t result = 0;
    while (*str != CHARS_NULL)
        if (*str == chr) {
            result++;
            str++;
        } else break;
    return result;
}

ssize_t right_count_char(const char* str, char chr) {
    if (str == NULL) return -1;
    ssize_t result = 0;
    ssize_t len = strlen(str);
    if (len > 0) {
        const char* ptr = str + len - 1;
        while (ptr >= str && *ptr == chr) {
            result++;
            ptr--;
        }
    }
    return result;
}

char* prepend_char(const char* str, char chr) {
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    char* result = ce_malloc(len + 2);
    if (result == NULL) return NULL;
    result[0] = chr;
    strcpy(result + 1, str);
    result[len + 1] = CHARS_NULL;
    return result;
}

char* append_char(const char* str, char chr) {
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    char* result = ce_malloc(len + 2);
    if (result == NULL) return NULL;
    strcpy(result, str);
    result[len] = chr;
    result[len + 1] = CHARS_NULL;
    return result;
}

char* remove_char(const char* str, char chr) {
    if (str == NULL) return NULL;
    size_t count = 0;
    for (const char* p = str; *p != CHARS_NULL; p++)
        if (*p != chr)
            count++;
    char* result = ce_malloc(count + 1);
    if (result == NULL) return NULL;
    char* dest = result;
    for (const char* p = str; *p != CHARS_NULL; p++)
        if (*p != chr)
            *dest++ = *p;
    *dest = CHARS_NULL;
    return result;
}

char* strreverse(char* str) {
    if (assigned(str)) {
        size_t len = strlen(str), i, j;
        if (len > 1)
            for (i = 0, j = len - 1; i < j; ++i, --j) {
                char tmp = str[i];
                str[i] = str[j];
                str[j] = tmp;
            }
    }
    return str;
}

char* to_upper_case(const char* str) {
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    char* result = ce_malloc(len + 1);
    if (result == NULL) return NULL;
    for (size_t i = 0; i < len; i++)
        result[i] = toupper((unsigned char)str[i]);
    result[len] = CHARS_NULL;
    return result;
}

char* to_lower_case(const char* str) {
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    char* result = ce_malloc(len + 1);
    if (result == NULL) return NULL;
    for (size_t i = 0; i < len; i++)
        result[i] = tolower((unsigned char)str[i]);
    result[len] = CHARS_NULL;
    return result;
}

bool str_to_bool(const char* str) {
    if (str == NULL) return false;
    while (*str && isspace((unsigned char)*str)) str++; // skip leading spaces
    if (strcasecmp(str, "true") == 0 || strcmp(str, "1") == 0) {
        return true;
    } else if (strcasecmp(str, "false") == 0 || strcmp(str, "0") == 0) {
        return false;
    }
    return false;
}

signed char str_to_signed_char_def(const char* str, signed char default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    long val = strtol(str, &endptr, 10);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0) // Conversion error occurred (overflow, underflow, invalid input)
        || (val < SCHAR_MIN || val > SCHAR_MAX)) // Value out of range for signed char
            return default_value;
    return (signed char)val;
}

unsigned char str_to_unsigned_char_def(const char* str, unsigned char default_value) {
    if (str == NULL || *str == CHARS_MINUS) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    unsigned long val = strtoul(str, &endptr, 10);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0) // Conversion error occurred (overflow, underflow, invalid input)
        || (val > UCHAR_MAX)) // Max value out of range for unsigned char
            return default_value;
    return (unsigned char)val;
}

short str_to_short_def(const char* str, short default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    long val = strtol(str, &endptr, 10);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno == ERANGE) // Out of range for long
        || (val < SHRT_MIN || val > SHRT_MAX)) // Out of range for short
            return default_value;
    return (short)val;
}

unsigned short str_to_unsigned_short_def(const char* str, unsigned short default_value) {
    if (str == NULL || *str == CHARS_MINUS) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    unsigned long val = strtoul(str, &endptr, 10);
    // Check for various possible errors
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno == ERANGE) // Out of range for unsigned long
        || (val > USHRT_MAX))  // Out of range for unsigned short
        return default_value;
    return (unsigned short)val;
}

int str_to_int_def(const char* str, int default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // To distinguish success/failure after call
    long val = strtol(str, &endptr, 10);
    // Check for various possible errors
    if ((str == endptr) // No digits found
        || ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (val > INT_MAX || val < INT_MIN)) // Out of range
        || (*endptr != CHARS_NULL)) // Extra characters after number
        return default_value;
    return (int)val;
}

unsigned int str_to_unsigned_int_def(const char* str, unsigned int default_value) {
    if (str == NULL || *str == CHARS_MINUS) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    unsigned long val = strtoul(str, &endptr, 10);
    // Check for various possible errors
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno == ERANGE) // Out of range for unsigned long
        || (val > UINT_MAX)) // Out of range for unsigned int
        return default_value;
    return (unsigned int)val;
}

long str_to_long_def(const char* str, long default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // To distinguish success/failure after call
    long val = strtol(str, &endptr, 10);
    // Check for various possible errors
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno == ERANGE)) // Out of range for long
        return default_value;
    return val;
}

unsigned long str_to_unsigned_long_def(const char* str, unsigned long default_value) {
    if (str == NULL || *str == CHARS_MINUS) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    unsigned long val = strtoul(str, &endptr, 10);
    // Check for various possible errors
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno == ERANGE)) // Out of range for unsigned long
        return default_value;
    return val;
}

long long str_to_long_long_def(const char* str, long long default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    long long val = strtoll(str, &endptr, 10);
    // Check for various possible errors
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno == ERANGE)) // Out of range for long long
        return default_value;
    return val;
}

unsigned long long str_to_unsigned_long_long_def(const char* str, unsigned long long default_value) {
    if (str == NULL || *str == CHARS_MINUS) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    unsigned long long val = strtoull(str, &endptr, 10);
    // Check for various possible errors
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno == ERANGE)) // Out of range for unsigned long long
        return default_value;
    return val;
}

int8_t str_to_int8_def(const char* str, int8_t default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    long val = strtol(str, &endptr, 10);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0) // Conversion error occurred (overflow, underflow, invalid input)
        || (val < INT8_MIN || val > INT8_MAX)) // Value out of range for int8_t
            return default_value;
    return (int8_t)val;
}

uint8_t str_to_uint8_def(const char* str, uint8_t default_value) {
    if (str == NULL || *str == CHARS_MINUS) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    unsigned long val = strtoul(str, &endptr, 10);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0) // Conversion error occurred (overflow, underflow, invalid input)
        || (val > UINT8_MAX)) // Max value out of range for uint8_t
            return default_value;
    return (uint8_t)val;
}

int16_t str_to_int16_def(const char* str, int16_t default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    long val = strtol(str, &endptr, 10);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0) // Conversion error occurred (overflow, underflow, invalid input)
        || (val < INT16_MIN || val > INT16_MAX)) // Value out of range for int16_t
            return default_value;
    return (int16_t)val;
}

uint16_t str_to_uint16_def(const char* str, uint16_t default_value) {
    if (str == NULL || *str == CHARS_MINUS) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    unsigned long val = strtoul(str, &endptr, 10);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0) // Conversion error occurred (overflow, underflow, invalid input)
        || (val > UINT16_MAX)) // Max value out of range for uint16_t
            return default_value;
    return (uint16_t)val;
}

int32_t str_to_int32_def(const char* str, int32_t default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    long val = strtol(str, &endptr, 10);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0) // Conversion error occurred (overflow, underflow, invalid input)
        || (val < INT32_MIN || val > INT32_MAX)) // Value out of range for int32_t
            return default_value;
    return (int32_t)val;
}

uint32_t str_to_uint32_def(const char* str, uint32_t default_value) {
    if (str == NULL || *str == CHARS_MINUS) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    unsigned long val = strtoul(str, &endptr, 10);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0) // Conversion error occurred (overflow, underflow, invalid input)
        || (val > UINT32_MAX)) // Max value out of range for uint32_t
            return default_value;
    return (uint32_t)val;
}

int64_t str_to_int64_def(const char* str, int64_t default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    long long val = strtoll(str, &endptr, 10);
    // Check for various possible errors
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0) // Conversion error occurred (overflow, underflow, invalid input)
        || (val < INT64_MIN || val > INT64_MAX)) // Value out of range for int64_t
        return default_value;
    return (int64_t)val;
}

uint64_t str_to_uint64_def(const char* str, uint64_t default_value) {
    if (str == NULL || *str == CHARS_MINUS) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    unsigned long long val = strtoull(str, &endptr, 10);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0) // Conversion error occurred (overflow, underflow, invalid input)
        || (val > UINT64_MAX)) // Max value out of range for uint64_t
            return default_value;
    return (uint64_t)val;
}

float str_to_float_def(const char* str, float default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    float val = strtof(str, &endptr);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0)) // Conversion error occurred (overflow, underflow, invalid input)
        return default_value;
    return val;
}

double str_to_double_def(const char* str, double default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    double val = strtod(str, &endptr);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0)) // Conversion error occurred (overflow, underflow, invalid input)
        return default_value;
    return val;
}

long double str_to_long_double_def(const char* str, long double default_value) {
    if (str == NULL) return default_value;
    char* endptr;
    errno = 0; // Clear errno to detect overflow
    long double val = strtold(str, &endptr);
    if ((str == endptr) // No digits found
        || (*endptr != CHARS_NULL) // Extra characters after number
        || (errno != 0)) // Conversion error occurred (overflow, underflow, invalid input)
        return default_value;
    return val;
}

char* char_to_str(char value) {
    char* buffer = ce_malloc(2);
    if (buffer) {
        buffer[0] = value;
        buffer[1] = CHARS_NULL;
    }
    return buffer;
}

char* signed_char_to_str(signed char value) {
    // allocate enough space for sign, 3 digits, and null terminator
    char* buffer = ce_malloc(5);
    if (buffer == NULL) return NULL;
    sprintf(buffer, "%d", (int)value);
    return buffer;
}

char* unsigned_char_to_str(unsigned char value) {
    // allocate enough space for 3 digits and null terminator
    char* buffer = ce_malloc(4);
    if (buffer == NULL) return NULL;
    sprintf(buffer, "%u", (unsigned int)value);
    return buffer;
}

#define VALUE_TO_STR(format) \
    char buffer[32]; \
    sprintf(buffer, format, value); \
    char* result = ce_malloc(strlen(buffer) + 1); \
    if (result == NULL) return NULL; \
    strcpy(result, buffer); \
    return result;

char* short_to_str(short value) {
    VALUE_TO_STR("%hd");
}

char* unsigned_short_to_str(unsigned short value) {
    VALUE_TO_STR("%hu");
}

char* int_to_str(int value) {
    VALUE_TO_STR("%d");
}

char* unsigned_int_to_str(unsigned int value) {
    VALUE_TO_STR("%u");
}

char* long_to_str(long value) {
    VALUE_TO_STR("%ld");
}

char* unsigned_long_to_str(unsigned long value) {
    VALUE_TO_STR("%lu");
}

char* long_long_to_str(long long value) {
    VALUE_TO_STR("%lld");
}

char* unsigned_long_long_to_str(unsigned long long value) {
    VALUE_TO_STR("%llu");
}

char* float_to_str(float value) {
    VALUE_TO_STR("%.03f");
}

char* double_to_str(double value) {
    VALUE_TO_STR("%.08f");
}

char* long_double_to_str(long double value) {
    char buffer[100];
    sprintf(buffer, "%.*Lf", LDBL_DIG, value);
    char* result = ce_malloc(strlen(buffer) + 1);
    if (result == NULL) return NULL;
    strcpy(result, buffer);
    return result;
}

char* int8_to_str(int8_t value) {
    VALUE_TO_STR(STRINGS_PERCENT PRIi8);
}

char* uint8_to_str(uint8_t value) {
    VALUE_TO_STR(STRINGS_PERCENT PRIu8);
}

char* int16_to_str(int16_t value) {
    VALUE_TO_STR(STRINGS_PERCENT PRIi16);
}

char* uint16_to_str(uint16_t value) {
    VALUE_TO_STR(STRINGS_PERCENT PRIu16);
}

char* int32_to_str(int32_t value) {
    VALUE_TO_STR(STRINGS_PERCENT PRIi32);
}

char* uint32_to_str(uint32_t value) {
    VALUE_TO_STR(STRINGS_PERCENT PRIu32);
}

char* int64_to_str(int64_t value) {
    VALUE_TO_STR(STRINGS_PERCENT PRIi64);
}

char* uint64_to_str(uint64_t value) {
    VALUE_TO_STR(STRINGS_PERCENT PRIu64);
}

char* ptr_to_str(void* value) {
    VALUE_TO_STR("%p");
}

char* bool_to_str(bool value) {
    char* buffer = NULL;
    if (value) {
        buffer = ce_malloc(5);
        if (assigned(buffer))
            strcpy(buffer, "true");
    } else {
        buffer = ce_malloc(6);
        if (assigned(buffer))
            strcpy(buffer, "false");
    }
    return buffer;
}

#undef VALUE_TO_STR

char* bytes_to_hex(const uint8_t* bytes, ssize_t size) {
    if (bytes == NULL || size == 0) return NULL;
    // Each byte -> 2 hex chars, plus 1 for null terminator
    char* result = ce_malloc(size * 2 + 1);
    if (result == NULL) return NULL;
    char* ptr = result;
    LOOP_VAR_TIMES(i, size) {
        sprintf(ptr, "%02X", bytes[i]); // Write two uppercase hex digits per byte
        ptr += 2;
    }
    *ptr = CHARS_NULL;
    return result;
}

bool hex_to_bytes(const char* hex_str, uint8_t** out_bytes, ssize_t* out_len) {
    if (hex_str == NULL || out_bytes == NULL || out_len == NULL) return false;
    ssize_t hex_len = 0;
    while (hex_str[hex_len] != CHARS_NULL) {
        if (!isxdigit((unsigned char)hex_str[hex_len]))
            return false; // invalid char
        hex_len++;
    }
    if (hex_len == 0 || (hex_len % 2) != 0) return false; // length must be even
    ssize_t byte_len = hex_len / 2;
    VAR_MALLOC_SIZE(bytes, uint8_t, byte_len);
    if (bytes == NULL) return false;
    LOOP_VAR_TIMES(i, byte_len) {
        int hi = hex_char_to_int(hex_str[2 * i]);
        int lo = hex_char_to_int(hex_str[2 * i + 1]);
        if (hi == -1 || lo == -1) {
            ce_free(bytes);
            return false;
        }
        bytes[i] = (uint8_t)((hi << 4) | lo);
    }
    *out_bytes = bytes;
    *out_len = byte_len;
    return true;
}

int decode_utf8_escape(const char* str, char* out) {
    if (str == NULL || out == NULL) return 0;
    int u = 0;
    for (int i = 0; i < 4; i++) {
        int val = hex_char_to_int(str[i]);
        if (val < 0) return 0;
        u = (u << 4) | val;
    }
    if (u <= 0x7F) { // encode u as UTF-8
        out[0] = (char)u;
        return 1;
    } else if (u <= 0x7FF) {
        out[0] = (char)(0xC0 | ((u >> 6) & 0x1F));
        out[1] = (char)(0x80 | (u & 0x3F));
        return 2;
    } else {
        out[0] = (char)(0xE0 | ((u >> 12) & 0x0F));
        out[1] = (char)(0x80 | ((u >> 6) & 0x3F));
        out[2] = (char)(0x80 | (u & 0x3F));
        return 3;
    }
}

char** string_array_create(ssize_t size, const char* default_value) {
    if (size <= 0 || default_value == NULL) return NULL;
    RET_MALLOC_SIZE(char*, size * sizeof(char*), {
        for (ssize_t i = 0; i < size; i++) {
            result[i] = strdup(default_value);
            if (result[i] == NULL) { // free any allocated memory on failure
                for (ssize_t j = 0; j < i; j++) free(result[j]);
                free(result);
                return NULL;
            }
        }
    });
}

char** string_array_with_sentinel_create(ssize_t size, const char* default_value) {
    if (size <= 0 || default_value == NULL) return NULL;
    RET_MALLOC_SIZE(char*, (size + 1) * sizeof(char*), {
        for (ssize_t i = 0; i < size; i++) {
            result[i] = strdup(default_value);
            if (result[i] == NULL) { // free any allocated memory on failure
                for (ssize_t j = 0; j < i; j++) free(result[j]);
                free(result);
                return NULL;
            }
        }
        result[size] = NULL;
    });
}

char** string_array_replace_segment(const char* array[], ssize_t arr_len, ssize_t from, ssize_t to, const char* source[], ssize_t src_len, ssize_t* out_len) {
    if (array == NULL || arr_len < 1 || source == NULL || src_len < 1 || from < 0 || to >= arr_len || from > to) return NULL;
    ssize_t new_len = arr_len - (to - from + 1) + src_len;
    RET_MALLOC_SIZE(char*, new_len * sizeof(char*), {
        for (ssize_t i = 0; i < from; i++) // copy elements before 'from'
            result[i] = strdup(array[i]);
        for (ssize_t i = 0; i < src_len; i++) // copy all elements from source
            result[from + i] = strdup(source[i]);
        for (ssize_t i = to + 1; i < arr_len; i++) // copy elements after 'to'
            result[src_len + i - (to + 1) + from] = strdup(array[i]);
        *out_len = new_len;
    });
}

ssize_t string_array_find_first_null(ssize_t size, const char* array[]) {
    if (size > 0 && assigned(array))
        for (ssize_t i = 0; i < size; i++)
            if (array[i] == NULL)
                return i;
    return -1;
}

ssize_t string_array_find_first(ssize_t size, const char* array[], const char* target) {
    if (size > 0 && assigned(array) && assigned(target))
        for (ssize_t i = 0; i < size; i++)
            if (assigned(array[i]) && strcmp(array[i], target) == 0)
                return i;
    return -1;
}

ssize_t string_array_find_last(ssize_t size, const char* array[], const char* target) {
    if (size > 0 && assigned(array) && assigned(target))
        for (ssize_t i = size - 1; i > 0; i--)
            if (assigned(array[i]) && strcmp(array[i], target) == 0)
                return i;
    return -1;
}

char* string_array_join_range(ssize_t size, const char* array[], ssize_t from, ssize_t to, const char* separator) {
    if (size <= 0 || array == NULL || from > to || from < 0 || to >= size) return NULL;
    const char* sep = assigned(separator) ? separator : STRINGS_NOTHING;
    ssize_t sep_length = strlen(sep);
    ssize_t total_length = 0;
    for (int i = from; i < to + 1; i++) {
        total_length += strlen(array[i]);
        if (i < to) total_length += sep_length;
    }
    RET_MALLOC_SIZE(char, total_length + 1, {
        result[0] = CHARS_NULL;
        for (ssize_t i = from; i < to + 1; i++) {
            strcat(result, array[i]);
            if (i < to) strcat(result, sep);
        }
    });
}

ssize_t string_array_count_occurrences(ssize_t size, const char* array[], const char* target) {
    ssize_t result = 0;
    if (size > 0 && assigned(array) && assigned(target))
        for (ssize_t i = size - 1; i > 0; i--)
            if (assigned(array[i]) && strcmp(array[i], target) == 0)
                result++;
    return result;
}

static int string_sort_compare(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    return strcmp(str1, str2);
}

void string_array_sort(ssize_t size, char* array[]) {
    if (size <= 0 || array == NULL) return;
    qsort(array, size, sizeof(char*), string_sort_compare);
}

static int string_reversed_sort_compare(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    return strcmp(str2, str1);
}

void string_array_reversed_sort(ssize_t size, char* array[]) {
    if (size <= 0 || array == NULL) return;
    qsort(array, size, sizeof(char*), string_reversed_sort_compare);
}

void string_array_shuffle(ssize_t size, char* array[], fn_int_fn rand_func) {
    if (size <= 0 || array == NULL) return;
    for (ssize_t i = size - 1; i > 0; i--) {
        ssize_t j = rand_func() % (i + 1); // random index j such that 0 <= j <= i
        char* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

// Function to validate an array of hex byte strings
bool string_array_hex_validate(ssize_t size, const char* array[]) {
    if (size <= 0 || array == NULL) return false;
    for (ssize_t i = 0; i < size; i++) {
        const char* byte_str = array[i];
        // Check if the string is exactly 2 characters long
        if (byte_str[0] == CHARS_NULL || byte_str[1] == CHARS_NULL || byte_str[2] != CHARS_NULL)
            return false; // Invalid length
        // Check each character is a valid hex digit
        if (!is_hex_char(byte_str[0]) || !is_hex_char(byte_str[1]))
            return false; // Invalid hex character
    }
    return true; // All valid
}

#define INTERNAL_CAT_FN(length, blk) \
    size_t len_str = str == NULL ? 0 : strlen(str); \
    size_t len_src = length; \
    size_t new_len = len_str + len_src; \
    char* result = realloc(str, new_len + 1); \
    if (assigned(result)) { \
        blk; \
        result[new_len] = CHARS_NULL; \
    } \
    return result;

char* strprepend(char* str, const char* src) {
    if (src == NULL) return str;
    INTERNAL_CAT_FN(strlen(src), {
        // move the original content rightwards to make space for src prefix
        memmove(result + len_src, result, len_str);
        // copy src at the beginning
        memcpy(result, src, len_src);
    });
}

char* strappend(char* str, const char* src) {
    if (src == NULL) return str;
    INTERNAL_CAT_FN(strlen(src), {
        // append src at the end of the original string
        memcpy(result + len_str, src, len_src);
    });
}

char* strappend_twice(char* str, const char* src1, const char* src2) {
    if (src1 == NULL || src2 == NULL) return str;
    size_t len_src1 = strlen(src1);
    size_t len_src2 = strlen(src2);
    INTERNAL_CAT_FN(len_src1 + len_src2, {
        // append src1 at the end of the original string
        memcpy(result + len_str, src1, len_src1);
        // append src2 at the end of the previous concatenation
        memcpy(result + len_str + len_src1, src2, len_src2);
    });
}

char* strappend_thrice(char* str, const char* src1, const char* src2, const char* src3) {
    if (src1 == NULL || src2 == NULL) return str;
    size_t len_src1 = strlen(src1);
    size_t len_src2 = strlen(src2);
    size_t len_src3 = strlen(src3);
    INTERNAL_CAT_FN(len_src1 + len_src2 + len_src3, {
        // append src1 at the end of the original string
        memcpy(result + len_str, src1, len_src1);
        // append src2 at the end of the previous concatenation
        memcpy(result + len_str + len_src1, src2, len_src2);
        // append src2 at the end of the previous concatenation
        memcpy(result + len_str + len_src1 + len_src2, src3, len_src3);
    });
}

char* strenclose(char* str, const char* prefix, const char* suffix) {
    if (prefix == NULL || suffix == NULL) return str;
    size_t len_prefix = strlen(prefix);
    size_t len_suffix = strlen(suffix);
    INTERNAL_CAT_FN(len_prefix + len_suffix, {
        // move the original content rightwards to make space for src prefix
        memmove(result + len_prefix, result, len_str);
        // copy prefix at the beginning
        memcpy(result, prefix, len_prefix);
        // append suffix at the end of the previous concatenation
        memcpy(result + len_str + len_prefix, suffix, len_suffix);
    });
}

#undef INTERNAL_CAT_FN

char* concat_strings(const char* str1, const char* str2) {
    char* result = NULL;
    if (!(str1 == NULL && str2 == NULL)) {
        size_t n = (str1 == NULL ? 0 : strlen(str1)) + (str2 == NULL ? 0 : strlen(str2));
        if ((assigned(str1) || assigned(str2)) && assigned(result = ce_malloc(n + 1))) {
            *result = CHARS_NULL;
            if (assigned(str1)) strcpy(result, str1);
            if (assigned(str2)) strcat(result, str2);
        }
    }
    return result;
}

bool starts_with(const char* str, const char* pfx) {
    if (str == NULL || pfx == NULL) return false;
    size_t prefix_size = strlen(pfx);
    return strncmp(pfx, str, prefix_size) == 0;
}

bool ends_with(const char* str, const char* sfx) {
    if (str == NULL || sfx == NULL) return false;
    size_t string_len = strlen(str);
    size_t suffix_len = strlen(sfx);
    if (suffix_len > string_len) return false;
    return strcmp(str + string_len - suffix_len, sfx) == 0;
}

ssize_t find_first_index_of(const char* str, const char* target) {
    if (str == NULL || *str == CHARS_NULL || target == NULL || *target == CHARS_NULL) return -1;
    char* p = (char*)strstr(str, target);
    return p == NULL ? -1 : p - str;
}

ssize_t find_last_index_of(const char* str, const char* target) {
    if (str == NULL || *str == CHARS_NULL || target == NULL || *target == CHARS_NULL) return -1;
    char* last = NULL;
    char* p = (char*)str;
    while ((p = strstr(p, target)) != NULL)
        last = p++; // save current match and move pointer forward
    return last == NULL ? -1 : last - str;
}

char* trim_right(const char* str) {
    if (str == NULL) return NULL;
    size_t len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1]))
        len--;
    char* trimmed = ce_malloc(len + 1);
    if (trimmed == NULL) return NULL;
    strncpy(trimmed, str, len);
    trimmed[len] = CHARS_NULL;
    return trimmed;
}

char* trim_left(const char* str) {
    if (str == NULL) return NULL;
    size_t start = 0;
    size_t len = strlen(str);
    while (start < len && isspace((unsigned char)str[start]))
        start++;
    size_t new_len = len - start;
    char* trimmed = ce_malloc(new_len + 1);
    if (trimmed == NULL) return NULL;
    strcpy(trimmed, str + start);
    return trimmed;
}

char* trim(const char* str) {
    if (str == NULL) return NULL;
    const char* start = str;
    while (*start && isspace((unsigned char)*start))
        start++;
    if (*start == CHARS_NULL) {
        char* empty = ce_malloc(1);
        if (empty) empty[0] = CHARS_NULL;
        return empty;
    }
    const char* end = str + strlen(str) - 1;
    while (end > start && isspace((unsigned char)*end))
        end--;
    size_t len = end - start + 1;
    char* trimmed = ce_malloc(len + 1);
    if (trimmed == NULL) return NULL;
    memcpy(trimmed, start, len);
    trimmed[len] = CHARS_NULL;
    return trimmed;
}

char* drop_both(const char* str, size_t amount) {
    if (str == NULL || amount == 0) return NULL;
    size_t len = strlen(str);
    // check if string is long enough
    if (len < 2 * amount) return NULL;
    size_t new_len = len - 2 * amount;
    char* result = ce_malloc(new_len + 1);
    if (assigned(result)) {
        memcpy(result, str + amount, new_len);
        result[new_len] = CHARS_NULL;
    }
    return result;
}

char* drop_left(const char* str, size_t amount) {
    if (str == NULL || amount == 0) return NULL;
    size_t len = strlen(str);
    if (len < amount) return NULL;
    size_t new_len = len - amount;
    char* result = ce_malloc(new_len + 1);
    if (assigned(result)) {
        memcpy(result, str + amount, new_len);
        result[new_len] = CHARS_NULL;
    }
    return result;
}

char* drop_right(const char* str, size_t amount) {
    if (str == NULL || amount == 0) return NULL;
    size_t len = strlen(str);
    if (len < amount) return NULL;
    size_t new_len = len - amount;
    char* result = ce_malloc(new_len + 1);
    if (assigned(result)) {
        memcpy(result, str, new_len);
        result[new_len] = CHARS_NULL;
    }
    return result;
}

char* remove_whitespace(const char* str) {
    if (str == NULL) return NULL;
    int count = 0;
    for (int i = 0; str[i] != CHARS_NULL; i++)
        if (!isspace((unsigned char)str[i]))
            count++;
    char* result = (char*)ce_malloc(count + 1);
    if (result == NULL) return NULL;
    int j = 0;
    for (int i = 0; str[i] != CHARS_NULL; i++)
        if (!isspace((unsigned char)str[i]))
            result[j++] = str[i];
    result[j] = CHARS_NULL;
    return result;
}

string_key_value_dt* string_key_value_parse(const char* input, const char* separator) {
    if (input == NULL || *input == CHARS_NULL) return NULL;
    if (separator == NULL || *separator == CHARS_NULL) {
        // if separator is empty or NULL, treat as no separator found (key = input copy, value = NULL)
        string_key_value_dt* result = ce_malloc(sizeof(string_key_value_dt));
        if (result == NULL) return NULL;
        result->key = strdup(input);
        result->value = NULL;
        return result;
    }
    const char* sep_pos = strstr(input, separator);
    string_key_value_dt* result = ce_malloc(sizeof(string_key_value_dt));
    if (result == NULL) return NULL;
    if (sep_pos == NULL) {
        // separator not found: key = whole input, value = NULL
        result->key = strdup(input);
        result->value = NULL;
    } else {
        // separator found: split into key and value
        size_t key_len = sep_pos - input;
        result->key = ce_malloc(key_len + 1);
        if (result->key == NULL) {
            ce_free(result);
            return NULL;
        }
        strncpy(result->key, input, key_len);
        result->key[key_len] = CHARS_NULL;
        const char* value_start = sep_pos + strlen(separator);
        result->value = strdup(value_start);
        if (result->value == NULL) {
            ce_free(result->key);
            ce_free(result);
            return NULL;
        }
    }
    return result;
}

#define PROCESS_TOKEN(p, segnent_start, cb_blk) \
    size_t len = p - segment_start; \
    char* token = (char*)ce_malloc(len + 1); \
    if (token == NULL) return false; \
    memcpy(token, segment_start, len); \
    token[len] = CHARS_NULL; \
    cb_blk; \
    ce_free(token)

bool parse_separated_values(const char* text, const char* separator, parsed_string_callback callback) {
    if (text == NULL || separator == NULL || callback == NULL) return false;
    size_t sep_len = strlen(separator);
    const char* segment_start = text;
    const char* p = text;
    while (*p) {
        // Check if the substring at p matches the separator
        if (strncmp(p, separator, sep_len) == 0) {
            PROCESS_TOKEN(p, segment_start, {
                callback(token);
            });
            p += sep_len;
            segment_start = p;
            continue;
        }
        p++;
    }
    // Handle last token after the final separator (or if no separator found)
    if (p != segment_start) {
        PROCESS_TOKEN(p, segment_start, {
            callback(token);
        });
    }
    return true;
}

bool parse_separated_values_with_reference(const char* text, const char* separator, parsed_string_callback_with_reference callback, const void* reference) {
    if (text == NULL || separator == NULL || callback == NULL) return false;
    size_t sep_len = strlen(separator);
    const char* segment_start = text;
    const char* p = text;
    while (*p) {
        // Check if the substring at p matches the separator
        if (strncmp(p, separator, sep_len) == 0) {
            PROCESS_TOKEN(p, segment_start, {
                callback(token, reference);
            });
            p += sep_len;
            segment_start = p;
            continue;
        }
        p++;
    }
    // Handle last token after the final separator (or if no separator found)
    if (p != segment_start) {
        PROCESS_TOKEN(p, segment_start, {
            callback(token, reference);
        });
    }
    return true;
}

#undef PROCESS_TOKEN

char* replace_first_occurrence(const char* str, const char* target, const char* replacement) {
    if (str == NULL || target == NULL || replacement == NULL) return NULL;
    const char* pos = strstr(str, target);
    if (pos == NULL) // on target not found, return a copy of the original string
        return strdup(str);
    size_t len_before = pos - str;
    size_t len_target = strlen(target);
    size_t len_replacement = strlen(replacement);
    size_t len_after = strlen(pos + len_target);
    char* result = (char*)ce_malloc(len_before + len_replacement + len_after + 1);
    if (result == NULL) return NULL;
    memcpy(result, str, len_before);
    memcpy(result + len_before, replacement, len_replacement);
    memcpy(result + len_before + len_replacement, pos + len_target, len_after);
    result[len_before + len_replacement + len_after] = CHARS_NULL;
    return result;
}

char* replace_last_occurrence(const char* str, const char* target, const char* replacement) {
    if (str == NULL || target == NULL || replacement == NULL) return NULL;
    size_t len_str = strlen(str);
    size_t len_target = strlen(target);
    size_t len_replacement = strlen(replacement);
    const char* last = NULL;
    for (const char* pos = str; (pos = strstr(pos, target)) != NULL; pos += len_target)
        last = pos;
    if (last == NULL) // on target not found, return a copy of the original string
        return strdup(str);
    size_t len_new = len_str + len_replacement - len_target;
    char* result = ce_malloc(len_new + 1);
    if (result == NULL) return NULL;
    char* dest = result;
    const char* src = str;
    size_t len_before = last - src;
    memcpy(dest, src, len_before);
    dest += len_before;
    memcpy(dest, replacement, len_replacement);
    dest += len_replacement;
    src = last + len_target;
    strcpy(dest, src);
    return result;
}

char* replace_all_occurrences(const char* str, const char* target, const char* replacement) {
    if (str == NULL || target == NULL || replacement == NULL) return NULL;
    size_t len_str = strlen(str);
    size_t len_target = strlen(target);
    size_t len_replacement = strlen(replacement);
    size_t count = 0;
    for (const char* pos = str; (pos = strstr(pos, target)) != NULL; pos += len_target)
        count++;
    if (count == 0) // on target not found, return a copy of the original string
        return strdup(str);
    size_t len_new = len_str + count * (len_replacement - len_target);
    char* result = ce_malloc(len_new + 1);
    if (result == NULL) return NULL;
    char* dest = result;
    const char* src = str;
    const char* match;
    while ((match = strstr(src, target)) != NULL) {
        size_t len_before = match - src;
        memcpy(dest, src, len_before);
        dest += len_before;
        memcpy(dest, replacement, len_replacement);
        dest += len_replacement;
        src = match + len_target;
    }
    strcpy(dest, src);
    return result;
}

ssize_t measure_string_format(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ssize_t length = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    return length;
}

ssize_t get_string_format_size(const char* fmt, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    ssize_t result = vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);
    return result;
}

char* perform_string_format(ssize_t size, const char* fmt, va_list args) {
    char* buffer = ce_malloc(size + 1);
    if (assigned(buffer))
        vsnprintf(buffer, size + 1, fmt, args);
    return buffer;
}

char* format_string(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    ssize_t size = get_string_format_size(fmt, args);
    if (size < 0) {
        va_end(args);
        return NULL; // encoding error
    }
    char* result = perform_string_format(size, fmt, args);
    va_end(args);
    return result;
}

// Parses a JSON string starting at *p (expects starting quote), returns parsed string via out_str and advances *p
static bool parse_json_string(const char** p, char** out_str) {
    const char* ptr = *p;
    ptr++; // skip opening quote
    // first pass: calculate output length
    size_t length = 0;
    const char* scan = ptr;
    while (*scan && *scan != '"') {
        if (*scan == '\\') {
            scan++;
            if (!*scan) return false;
            if (*scan == 'u') { // unicode escape, 4 hex digits
                for (int i = 1; i <= 4; i++)
                    if (!scan[i] || !isxdigit(scan[i]))
                        return false;
                length += 3; // max UTF-8 length for one unicode char
                scan += 5;
            } else { // other escape sequences count as 1 char output
                length++;
                scan++;
            }
        } else {
            length++;
            scan++;
        }
    }
    if (*scan != '"') return false; // closing quote missing
    // allocate output buffer (length + 1 for null)
    char* buf = malloc(length + 1);
    if (buf == NULL) return false;
    // second pass: decode string
    char* out = buf;
    while (ptr && *ptr != '"') {
        if (*ptr == '\\') {
            ptr++;
            switch (*ptr) {
                case '"':  *out++ = '"';  break;
                case '\\': *out++ = '\\'; break;
                case '/':  *out++ = '/';  break;
                case 'b':  *out++ = '\b'; break;
                case 'f':  *out++ = '\f'; break;
                case 'n':  *out++ = '\n'; break;
                case 'r':  *out++ = '\r'; break;
                case 't':  *out++ = '\t'; break;
                case 'u': {
                    char utf8[3];
                    int bytes = decode_utf8_escape(ptr + 1, utf8);
                    if (bytes == 0) {
                        free(buf);
                        return false;
                    }
                    for (int i = 0; i < bytes; i++)
                        *out++ = utf8[i];
                    ptr += 4; // skip uXXXX digits
                    break;
                }
                default:
                    free(buf);
                    return false; // invalid escape
            }
            ptr++;
        } else
            *out++ = *ptr++;
    }
    *out = CHARS_NULL;
    if (*ptr != '"') {
        free(buf);
        return false;
    }
    *p = ptr + 1; // advance pointer past closing quote
    *out_str = buf;
    return true;
}

bool parse_json_strings_array(const char* json, parsed_string_callback callback) {
    if (json == NULL || callback == NULL) return false;
    const char* p = json;
    while (isspace(*p)) p++;
    if (*p != '[') return false;
    p++;
    LOOP_FOREVER() {
        while (isspace(*p)) p++;
        if (*p == ']') break;
        if (*p != '"') return false; // not a string, invalid or end
        char* str = NULL;
        if (!parse_json_string(&p, &str)) return false; // parse error
        callback(str);
        free(str);
        while (isspace(*p)) p++;
        if (*p == ',') {
            p++;
            continue;
        } else if (*p == ']') {
            break;
        } else
            return false;
    }
    return true;
}

bool parse_json_strings_array_with_reference(const char* json, parsed_string_callback_with_reference callback, const void* reference) {
    if (json == NULL || callback == NULL) return false;
    const char* p = json;
    while (isspace(*p)) p++;
    if (*p != '[') return false;
    p++;
    LOOP_FOREVER() {
        while (isspace(*p)) p++;
        if (*p == ']') break;
        if (*p != '"') return false; // not a string, invalid or end
        char* str = NULL;
        if (!parse_json_string(&p, &str)) return false; // parse error
        callback(str, reference);
        free(str);
        while (isspace(*p)) p++;
        if (*p == ',') {
            p++;
            continue;
        } else if (*p == ']') {
            break;
        } else
            return false;
    }
    return true;
}

bool parse_xyz_ints_string(const char* text, const char separator, int* x, int* y, int* z) {
    if (x == NULL || y == NULL || z == NULL || text == NULL) return false;
    char tmp_buffer[20];
    strncpy(tmp_buffer, text, sizeof(tmp_buffer) - 1);
    tmp_buffer[sizeof(tmp_buffer) - 1] = CHARS_NULL;
    char* token;
    char sep_str[2] = {separator, CHARS_NULL};
    token = strtok(tmp_buffer, sep_str);
    if (token != NULL) *x = atoi(token);
    token = strtok(NULL, sep_str);
    if (token != NULL) *y = atoi(token);
    token = strtok(NULL, sep_str);
    if (token != NULL) *z = atoi(token);
    return true;
}

