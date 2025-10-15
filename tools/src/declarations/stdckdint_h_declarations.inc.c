const char* stdckdint_h_name = "stdckdint.h";

const char* stdckdint_h_globals[] = {
    // stdckdint.h (a C23 header) provides checked integer arithmetic functions/macros,
    // but it does NOT define any global variables.
    NULL
};

// Types declared in stdckdint.h
const char* stdckdint_h_types[] = {
    NULL
};

// Macros declared in stdckdint.h
const char* stdckdint_h_macros[] = {
    // No macros defined by the standard in stdckdint.h
    NULL
};

// Functions declared in stdckdint.h
const char* stdckdint_h_functions[] = {
    // Checked addition functions: perform addition with overflow detection
    "ckd_add_int8",    // int ckd_add_int8(int8_t a, int8_t b, int8_t *result);
    "ckd_add_int16",   // int ckd_add_int16(int16_t a, int16_t b, int16_t *result);
    "ckd_add_int32",   // int ckd_add_int32(int32_t a, int32_t b, int32_t *result);
    "ckd_add_int64",   // int ckd_add_int64(int64_t a, int64_t b, int64_t *result);

    "ckd_add_uint8",   // int ckd_add_uint8(uint8_t a, uint8_t b, uint8_t *result);
    "ckd_add_uint16",  // int ckd_add_uint16(uint16_t a, uint16_t b, uint16_t *result);
    "ckd_add_uint32",  // int ckd_add_uint32(uint32_t a, uint32_t b, uint32_t *result);
    "ckd_add_uint64",  // int ckd_add_uint64(uint64_t a, uint64_t b, uint64_t *result);

    // Checked subtraction functions
    "ckd_sub_int8",    // int ckd_sub_int8(int8_t a, int8_t b, int8_t *result);
    "ckd_sub_int16",   // int ckd_sub_int16(int16_t a, int16_t b, int16_t *result);
    "ckd_sub_int32",   // int ckd_sub_int32(int32_t a, int32_t b, int32_t *result);
    "ckd_sub_int64",   // int ckd_sub_int64(int64_t a, int64_t b, int64_t *result);

    "ckd_sub_uint8",   // int ckd_sub_uint8(uint8_t a, uint8_t b, uint8_t *result);
    "ckd_sub_uint16",  // int ckd_sub_uint16(uint16_t a, uint16_t b, uint16_t *result);
    "ckd_sub_uint32",  // int ckd_sub_uint32(uint32_t a, uint32_t b, uint32_t *result);
    "ckd_sub_uint64",  // int ckd_sub_uint64(uint64_t a, uint64_t b, uint64_t *result);

    // Checked multiplication functions
    "ckd_mul_int8",    // int ckd_mul_int8(int8_t a, int8_t b, int8_t *result);
    "ckd_mul_int16",   // int ckd_mul_int16(int16_t a, int16_t b, int16_t *result);
    "ckd_mul_int32",   // int ckd_mul_int32(int32_t a, int32_t b, int32_t *result);
    "ckd_mul_int64",   // int ckd_mul_int64(int64_t a, int64_t b, int64_t *result);

    "ckd_mul_uint8",   // int ckd_mul_uint8(uint8_t a, uint8_t b, uint8_t *result);
    "ckd_mul_uint16",  // int ckd_mul_uint16(uint16_t a, uint16_t b, uint16_t *result);
    "ckd_mul_uint32",  // int ckd_mul_uint32(uint32_t a, uint32_t b, uint32_t *result);
    "ckd_mul_uint64",  // int ckd_mul_uint64(uint64_t a, uint64_t b, uint64_t *result);

    NULL
};

