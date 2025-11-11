/**
 * Meh C Library
 */

#include "gem_testing.h"
#include "meh.h"

#ifdef MEH_HELP
CE_MESSAGE("\n\n*** compile with: -Wfatal-errors -I../src -o ../bin/meh_test meh_test.c\n \
  and at minimum one of the following -std values:\n \
    -std=c99\n \
    -std=gnu99\n");
#endif

#define TREATER(type, name) type name(type value) { return value + 1; }

TREATER(short, short_treater)
TREATER(unsigned short, unsigned_short_treater)
TREATER(int, int_treater)
TREATER(unsigned int, unsigned_int_treater)
TREATER(long, long_treater)
TREATER(unsigned long, unsigned_long_treater)
TREATER(long long, long_long_treater)
TREATER(unsigned long long, unsigned_long_long_treater)
TREATER(char, char_treater)
TREATER(signed char, signed_char_treater)
TREATER(unsigned char, unsigned_char_treater)
TREATER(int8_t, int8_treater)
TREATER(uint8_t, uint8_treater)
TREATER(int16_t, int16_treater)
TREATER(uint16_t, uint16_treater)
TREATER(int32_t, int32_treater)
TREATER(uint32_t, uint32_treater)
TREATER(int64_t, int64_treater)
TREATER(uint64_t, uint64_treater)
TREATER(float, float_treater)
TREATER(double, double_treater)
TREATER(long double, long_double_treater)

static inline void test_math_utilities() {
    int a = 1, b = 2, c = -1;
    Tests.run("MAX", MAX(a, b) == b);
    Tests.run("MIN", MIN(a, b) == a);
    Tests.run("NEG", c == NEG(a));
    Tests.run("ABS", ABS(c) == a);
    Tests.run("float_abs", float_abs(-1.23f) == 1.23f);
    Tests.run("double_abs", double_abs(-1.23) == 1.23);
    Tests.run("long_double_abs", long_double_abs(-1.23L) == 1.23L);
    Tests.run("float_round 1", float_round(-1.49f) == -1.0f);
    Tests.run("double_round 1", double_round(-1.49) == -1.0);
    Tests.run("long_double_round 1", long_double_round(-1.49L) == -1.0L);
    Tests.run("float_round 2", float_round(1.51f) == 2.0f);
    Tests.run("double_round 2", double_round(1.51) == 2.0);
    Tests.run("long_double_round 2", long_double_round(1.51L) == 2.0L);
    Tests.run("float_equal", float_equal(3.21f / -1.23f, -2.609756f, 0.000001f));
    Tests.run("double_equal", double_equal(3.21 / -1.23, -2.609756, 0.000001));
    Tests.run("long_double_equal", long_double_equal(3.21L / -1.23L, -2.609756L, 0.000001L));
    Tests.run("CLAMP", CLAMP(3, a, b) == b);
    Tests.run("CLAMP", CLAMP(c, a, b) == a);
    Tests.run("SQUARE", SQUARE(3) == 9);
    Tests.run("CUBE", CUBE(3) == 27);
    Tests.run("TRUNC", TRUNC(3.5f) == 3);
    Tests.run("FRAC", FRAC(3.5f) == 0.5f);
    Tests.run("IN_RANGE", IN_RANGE(3, 1, 6));
    Tests.run("IN_RANGE", IN_RANGE(3.14, 1.0, 6.0));
    Tests.run("is_odd YES", is_odd(3));
    Tests.run("is_odd NO", !is_odd(42));
    Tests.run("is_even YES", is_even(10));
    Tests.run("is_even NO", !is_even(11));
    Tests.run("is_divisible_by YES", is_divisible_by(1000, 10));
    Tests.run("is_divisible_by NO", !is_divisible_by(100, 3));
    size_t size = 5;
    short short_arr[] = {1, 2, 3, 4, 5};
    __auto short* short_copy = short_array_copy(short_arr, size);
    Tests.run("short_array_copy", assigned(short_copy));
    Tests.run("short_array_equal", short_array_equal(short_arr, short_copy, size));
    Tests.run("short_array_treat", short_array_treat(short_arr, size, short_treater) && short_array_equal(short_arr, (short[]){2, 3, 4, 5, 6}, size));
    unsigned short unsigned_short_arr[] = {1, 2, 3, 4, 5};
    __auto unsigned short* unsigned_short_copy = unsigned_short_array_copy(unsigned_short_arr, size);
    Tests.run("unsigned_short_array_copy", assigned(unsigned_short_copy));
    Tests.run("unsigned_short_array_equal", unsigned_short_array_equal(unsigned_short_arr, unsigned_short_copy, size));
    Tests.run("unsigned_short_array_treat", unsigned_short_array_treat(unsigned_short_arr, size, unsigned_short_treater) && unsigned_short_array_equal(unsigned_short_arr, (unsigned short[]){2, 3, 4, 5, 6}, size));
    int int_arr[] = {10, 20, 30, 40, 50};
    __auto int* int_copy = int_array_copy(int_arr, size);
    Tests.run("int_array_copy", assigned(int_copy));
    Tests.run("int_array_equal", int_array_equal(int_arr, int_copy, size));
    Tests.run("int_array_treat", int_array_treat(int_arr, size, int_treater) && int_array_equal(int_arr, (int[]){11, 21, 31, 41, 51}, size));
    unsigned int unsigned_int_arr[] = {10, 20, 30, 40, 50};
    __auto unsigned int* unsigned_int_copy = unsigned_int_array_copy(unsigned_int_arr, size);
    Tests.run("unsigned_int_array_copy", assigned(unsigned_int_copy));
    Tests.run("unsigned_int_array_equal", unsigned_int_array_equal(unsigned_int_arr, unsigned_int_copy, size));
    Tests.run("unsigned_int_array_treat", unsigned_int_array_treat(unsigned_int_arr, size, unsigned_int_treater) && unsigned_int_array_equal(unsigned_int_arr, (unsigned int[]){11, 21, 31, 41, 51}, size));
    long long_arr[] = {100, 200, 300, 400, 500};
    __auto long* long_copy = long_array_copy(long_arr, size);
    Tests.run("long_array_copy", assigned(long_copy));
    Tests.run("long_array_equal", long_array_equal(long_arr, long_copy, size));
    Tests.run("long_array_treat", long_array_treat(long_arr, size, long_treater) && long_array_equal(long_arr, (long[]){101, 201, 301, 401, 501}, size));
    unsigned long unsigned_long_arr[] = {100, 200, 300, 400, 500};
    __auto unsigned long* unsigned_long_copy = unsigned_long_array_copy(unsigned_long_arr, size);
    Tests.run("unsigned_long_array_copy", assigned(unsigned_long_copy));
    Tests.run("unsigned_long_array_equal", unsigned_long_array_equal(unsigned_long_arr, unsigned_long_copy, size));
    Tests.run("unsigned_long_array_treat", unsigned_long_array_treat(unsigned_long_arr, size, unsigned_long_treater) && unsigned_long_array_equal(unsigned_long_arr, (unsigned long[]){101, 201, 301, 401, 501}, size));
    long long long_long_arr[] = {1000, 2000, 3000, 4000, 5000};
    __auto long long* long_long_copy = long_long_array_copy(long_long_arr, size);
    Tests.run("long_long_array_copy", assigned(long_long_copy));
    Tests.run("long_long_array_equal", long_long_array_equal(long_long_arr, long_long_copy, size));
    Tests.run("long_long_array_treat", long_long_array_treat(long_long_arr, size, long_long_treater) && long_long_array_equal(long_long_arr, (long long[]){1001, 2001, 3001, 4001, 5001}, size));
    unsigned long long unsigned_long_long_arr[] = {1000, 2000, 3000, 4000, 5000};
    __auto unsigned long long* unsigned_long_long_copy = unsigned_long_long_array_copy(unsigned_long_long_arr, size);
    Tests.run("unsigned_long_long_array_copy", assigned(unsigned_long_long_copy));
    Tests.run("unsigned_long_long_array_equal", unsigned_long_long_array_equal(unsigned_long_long_arr, unsigned_long_long_copy, size));
    Tests.run("unsigned_long_long_array_treat", unsigned_long_long_array_treat(unsigned_long_long_arr, size, unsigned_long_long_treater) && unsigned_long_long_array_equal(unsigned_long_long_arr, (unsigned long long[]){1001, 2001, 3001, 4001, 5001}, size));
    char char_arr[] = {'H', 'e', 'l', 'l', 'o'};
    __auto char* char_copy = char_array_copy(char_arr, size);
    Tests.run("char_array_copy", assigned(char_copy));
    Tests.run("char_array_equal", char_array_equal(char_arr, char_copy, size));
    Tests.run("char_array_treat", char_array_treat(char_arr, size, char_treater) && char_array_equal(char_arr, (char[]){'I', 'f', 'm', 'm', 'p'}, size));
    signed char signed_char_arr[] = {1, 2, 3, 4, 5};
    __auto signed char* signed_char_copy = signed_char_array_copy(signed_char_arr, size);
    Tests.run("signed_char_array_copy", assigned(signed_char_copy));
    Tests.run("signed_char_array_equal", signed_char_array_equal(signed_char_arr, signed_char_copy, size));
    Tests.run("signed_char_array_treat", signed_char_array_treat(signed_char_arr, size, signed_char_treater) && signed_char_array_equal(signed_char_arr, (signed char[]){2, 3, 4, 5, 6}, size));
    unsigned char unsigned_char_arr[] = {1, 2, 3, 4, 5};
    __auto unsigned char* unsigned_char_copy = unsigned_char_array_copy(unsigned_char_arr, size);
    Tests.run("unsigned_char_array_copy", assigned(unsigned_char_copy));
    Tests.run("unsigned_char_array_equal", unsigned_char_array_equal(unsigned_char_arr, unsigned_char_copy, size));
    Tests.run("unsigned_char_array_treat", unsigned_char_array_treat(unsigned_char_arr, size, unsigned_char_treater) && unsigned_char_array_equal(unsigned_char_arr, (unsigned char[]){2, 3, 4, 5, 6}, size));
    int8_t int8_arr[] = {1, 2, 3, 4, 5};
    __auto int8_t* int8_copy = int8_array_copy(int8_arr, size);
    Tests.run("int8_array_copy", assigned(int8_copy));
    Tests.run("int8_array_equal", int8_array_equal(int8_arr, int8_copy, size));
    Tests.run("int8_array_treat", int8_array_treat(int8_arr, size, int8_treater) && int8_array_equal(int8_arr, (int8_t[]){2, 3, 4, 5, 6}, size));
    uint8_t uint8_arr[] = {1, 2, 3, 4, 5};
    __auto uint8_t* uint8_copy = uint8_array_copy(uint8_arr, size);
    Tests.run("uint8_array_copy", assigned(uint8_copy));
    Tests.run("uint8_array_equal", uint8_array_equal(uint8_arr, uint8_copy, size));
    Tests.run("uint8_array_treat", uint8_array_treat(uint8_arr, size, uint8_treater) && uint8_array_equal(uint8_arr, (uint8_t[]){2, 3, 4, 5, 6}, size));
    int16_t int16_arr[] = {10, 20, 30, 40, 50};
    __auto int16_t* int16_copy = int16_array_copy(int16_arr, size);
    Tests.run("int16_array_copy", assigned(int16_copy));
    Tests.run("int16_array_equal", int16_array_equal(int16_arr, int16_copy, size));
    Tests.run("int16_array_treat", int16_array_treat(int16_arr, size, int16_treater) && int16_array_equal(int16_arr, (int16_t[]){11, 21, 31, 41, 51}, size));
    uint16_t uint16_arr[] = {10, 20, 30, 40, 50};
    __auto uint16_t* uint16_copy = uint16_array_copy(uint16_arr, size);
    Tests.run("uint16_array_copy", assigned(uint16_copy));
    Tests.run("uint16_array_equal", uint16_array_equal(uint16_arr, uint16_copy, size));
    Tests.run("uint16_array_treat", uint16_array_treat(uint16_arr, size, uint16_treater) && uint16_array_equal(uint16_arr, (uint16_t[]){11, 21, 31, 41, 51}, size));
    int32_t int32_arr[] = {100, 200, 300, 400, 500};
    __auto int32_t* int32_copy = int32_array_copy(int32_arr, size);
    Tests.run("int32_array_copy", assigned(int32_copy));
    Tests.run("int32_array_equal", int32_array_equal(int32_arr, int32_copy, size));
    Tests.run("int32_array_treat", int32_array_treat(int32_arr, size, int32_treater) && int32_array_equal(int32_arr, (int32_t[]){101, 201, 301, 401, 501}, size));
    uint32_t uint32_arr[] = {100, 200, 300, 400, 500};
    __auto uint32_t* uint32_copy = uint32_array_copy(uint32_arr, size);
    Tests.run("uint32_array_copy", assigned(uint32_copy));
    Tests.run("uint32_array_equal", uint32_array_equal(uint32_arr, uint32_copy, size));
    Tests.run("uint32_array_treat", uint32_array_treat(uint32_arr, size, uint32_treater) && uint32_array_equal(uint32_arr, (uint32_t[]){101, 201, 301, 401, 501}, size));
    int64_t int64_arr[] = {1000, 2000, 3000, 4000, 5000};
    __auto int64_t* int64_copy = int64_array_copy(int64_arr, size);
    Tests.run("int64_array_copy", assigned(int64_copy));
    Tests.run("int64_array_equal", int64_array_equal(int64_arr, int64_copy, size));
    Tests.run("int64_array_treat", int64_array_treat(int64_arr, size, int64_treater) && int64_array_equal(int64_arr, (int64_t[]){1001, 2001, 3001, 4001, 5001}, size));
    uint64_t uint64_arr[] = {1000, 2000, 3000, 4000, 5000};
    __auto uint64_t* uint64_copy = uint64_array_copy(uint64_arr, size);
    Tests.run("uint64_array_copy", assigned(uint64_copy));
    Tests.run("uint64_array_equal", uint64_array_equal(uint64_arr, uint64_copy, size));
    Tests.run("uint64_array_treat", uint64_array_treat(uint64_arr, size, uint64_treater) && uint64_array_equal(uint64_arr, (uint64_t[]){1001, 2001, 3001, 4001, 5001}, size));
    float float_arr[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    __auto float* float_copy = float_array_copy(float_arr, size);
    Tests.run("float_array_copy", assigned(float_copy));
    Tests.run("float_array_equal", float_array_equal(float_arr, float_copy, size));
    Tests.run("float_array_equal_custom", float_array_equal_custom(float_arr, float_copy, size, MEH_FLOAT_EPSILON));
    Tests.run("float_array_treat", float_array_treat(float_arr, size, float_treater) && float_array_equal(float_arr, (float[]){2.0f, 3.0f, 4.0f, 5.0f, 6.0f}, size));
    double double_arr[] = {5.5, 4.4, 3.3, 2.2, 1.1};
    __auto double* double_copy = double_array_copy(double_arr, size);
    Tests.run("double_array_copy", assigned(double_copy));
    Tests.run("double_array_equal", double_array_equal(double_arr, double_copy, size));
    Tests.run("double_array_equal_custom", double_array_equal_custom(double_arr, double_copy, size, MEH_DOUBLE_EPSILON));
    Tests.run("double_array_treat", double_array_treat(double_arr, size, double_treater) && double_array_equal(double_arr, (double[]){6.5, 5.4, 4.3, 3.2, 2.1}, size));
    long double ld_arr[] = {1.1L, 2.2L, 3.3L, 4.4L, 5.5L};
    __auto long double* ld_copy = long_double_array_copy(ld_arr, size);
    Tests.run("long_double_array_copy", assigned(ld_copy));
    Tests.run("long_double_array_equal", long_double_array_equal(ld_arr, ld_copy, size));
    Tests.run("long_double_array_equal_custom", long_double_array_equal_custom(ld_arr, ld_copy, size, MEH_LONG_DOUBLE_EPSILON));
    Tests.run("long_double_array_treat", long_double_array_treat(ld_arr, size, long_double_treater) && long_double_array_equal(ld_arr, (long double[]){2.1L, 3.2L, 4.3L, 5.4L, 6.5L}, size));
}

static inline void test_hash_utilities() {
    uint8_t tb[] = {0x12, 0x34, 0xDA, 0x55, 0x67, 0x89, 0xAB, 0xDC};
    uint8_t ctb = crc8_msbshlxor(tb, 8);
    Tests.run("crc8_msbshlxor", ctb == 0xD4);
    Tests.print("Value: 0x%02X\n", ctb);
    ctb = crc8_lsbshrxor(tb, 8);
    Tests.run("crc8_lsbshrxor", ctb == 0x0C);
    Tests.print("Value2: 0x%02X\n", ctb);
    
    char txt[] = "testing";
    uint32_t dval = djb2(txt);
    Tests.run("djb2", dval == 0xD91E9783);
    Tests.print("Values: 0x%08X == 0x%08X\n", dval, 0xD91E9783);
}

typedef struct {
    int X;
    int Y;
} Point;

bool safe_called = false;

static void fn_to_safe_call(bool result) {
    safe_called = result;
}

static inline void test_memory_utilities() {
    int a = 1, b = 2;
    xchg(a, b);
    Tests.run("xchg", a == 2 && b == 1);
    xorxchg(a, b);
    Tests.run("xorxchg", a == 1 && b == 2);
    char* m = "1234";
    char* n = "5678";
    memxchg(&m, &n, 4);
    Tests.run("memxchg", strcmp(m, "5678") == 0 && strcmp(n, "1234") == 0);
    Tests.print("m = %s | n = %s\n", m, n);
    
    uint8_t val8 = 0b10010110;  // 150 decimal, 0x96
    uint8_t rotated_left8 = rol8(val8, 3); // 0xB4, 0b10110100
    Tests.run("rol8", rotated_left8 == 0xB4);
    uint8_t rotated_right8 = ror8(val8, 3); // 0xD2, 0b11010010
    Tests.run("ror8", rotated_right8 == 0xD2);
    Tests.print("Original: 0x%02X | ROL 3: 0x%02X | ROR 3: 0x%02X\n", val8, rotated_left8, rotated_right8);
    
    uint16_t val16 = 0x1234; // 0b0001001000110100
    uint16_t rotated_left16 = rol16(val16, 3);
    Tests.run("rol16", rotated_left16 == 0x91A0);
    uint16_t rotated_right16 = ror16(val16, 3);
    Tests.run("ror16", rotated_right16 == 0x8246);
    Tests.print("Original: 0x%04X | ROL 3: 0x%04X | ROR 3: 0x%04X\n", val16, rotated_left16, rotated_right16);
    
    uint32_t val32 = 0x12345678;
    uint32_t rotated_left32 = rol32(val32, 3);
    Tests.run("rol32", rotated_left32 == 0x91A2B3C0);
    uint32_t rotated_right32 = ror32(val32, 3);
    Tests.run("ror32", rotated_right32 == 0x02468ACF);
    Tests.print("Original: 0x%08X | ROL 3: 0x%08X | ROR 3: 0x%08X\n", val32, rotated_left32, rotated_right32);
    
    uint64_t val64 = 0x123456789ABCDEF0ULL;
    uint64_t rotated_left64 = rol64(val64, 3);
    Tests.run("rol64", rotated_left64 == 0x91A2B3C4D5E6F780);
    uint64_t rotated_right64 = ror64(val64, 3);
    Tests.run("ror64", rotated_right64 == 0x02468ACF13579BDE);
    Tests.print("Original: 0x%016llX | ROL 3: 0x%016llX | ROR 3: 0x%016llX\n", val64, rotated_left64, rotated_right64);

    uint8_t bytes16[2] = {0x0A, 0x0B};
    uint16_t val16_le = pack_little_endian_16(bytes16);
    uint16_t val16_be = pack_big_endian_16(bytes16);
    Tests.run("pack_little_endian_16", val16_le == 0x0B0A);
    Tests.print("16-bit Little-endian packed: 0x%04X\n", val16_le);
    Tests.run("pack_big_endian_16", val16_be == 0x0A0B);
    Tests.print("16-bit Big-endian packed:    0x%04X\n", val16_be); 

    uint8_t bytes32[4] = {0x01, 0x02, 0x03, 0x04};
    uint32_t val32_le = pack_little_endian_32(bytes32);
    uint32_t val32_be = pack_big_endian_32(bytes32);
    Tests.run("pack_little_endian_32", val32_le == 0x04030201);
    Tests.print("32-bit Little-endian packed: 0x%08X\n", val32_le);
    Tests.run("pack_big_endian_32", val32_be == 0x01020304);
    Tests.print("32-bit Big-endian packed:    0x%08X\n", val32_be);

    uint8_t bytes64[8] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
    uint64_t val64_le = pack_little_endian_64(bytes64);
    uint64_t val64_be = pack_big_endian_64(bytes64);
    Tests.run("pack_little_endian_64", val64_le == 0x8070605040302010);
    Tests.print("64-bit Little-endian packed: 0x%016llX\n", val64_le);
    Tests.run("pack_big_endian_64", val64_be == 0x1020304050607080);
    Tests.print("64-bit Big-endian packed:    0x%016llX\n", val64_be);

    char buffer[256] ALIGN_16;
    float* misaligned = (float*)(buffer + 1); // Guaranteed misaligned
    Tests.run("is_byte_aligned (aligned to 16 with 16)", is_byte_aligned(buffer, 16)); // Aligned
    Tests.run("is_byte_aligned (aligned to 16 with 27481)", !is_byte_aligned(buffer, 27481)); // Unaligned
    Tests.run("is_byte_aligned (aligned to 16 with 0)", !is_byte_aligned(buffer, 0)); // Unaligned
    Tests.run("is_byte_aligned (misalined with 16)", !is_byte_aligned(misaligned, 16)); // Unaligned
    Tests.run("is_byte_aligned (misalined with 27481)", !is_byte_aligned(misaligned, 64)); // Unaligned
    Tests.run("is_byte_aligned (misalined with 0)", !is_byte_aligned(misaligned, 0)); // Unaligned

    Tests.run("ensure m n", ensure(m, n) == m);
    Tests.run("ensure m NULL", ensure(m, NULL) == m);
    Tests.run("ensure NULL n", ensure(NULL, n) == n);
    Tests.run("ensure NULL NULL", ensure(NULL, NULL) == NULL);

    Tests.run("null_coalesce m n", null_coalesce(m, n) == m);
    Tests.run("null_coalesce m NULL", null_coalesce(m, NULL) == m);
    Tests.run("null_coalesce NULL n", null_coalesce(NULL, n) == n);
    Tests.run("null_coalesce NULL NULL", null_coalesce(NULL, NULL) == NULL);

    Tests.run("ptreq m m", ptreq(m, m));
    Tests.run("ptreq m n", !ptreq(m, n));
    Tests.run("ptreq m NULL", !ptreq(m, NULL));
    Tests.run("ptreq NULL n", !ptreq(NULL, n));
    Tests.run("ptreq NULL NULL", ptreq(NULL, NULL));
    
    __auto char* str3 = malloc(4);
    strcpy(str3, "foo");
    Tests.run("_auto", (str3 != NULL) && str3[0] == 'f' && str3[1] == 'o' && str3[2] == 'o' && str3[3] == '\0');
    __auto VAR_MALLOC(x, int);
    *x = 123;
    Tests.run("_auto VAR_MALLOC", (x != NULL) && *x == 123);
    __unused __auto void* z = NULL;
    __unused __auto __auto void* zz = NULL;
    
    char* q = malloc(4);
    strcpy(q, "bar");
    AUTO_STRING(sg, q);
    Tests.run("AUTO_STRING", assigned(sg));
    Tests.print("%s\n", sg);
    const AUTO_STRDUP(ss, "hello world");
    Tests.run("AUTO_STRDUP", assigned(ss));
    Tests.print("%s\n", ss);
    AUTO_STRHEAP(hs, "my string in the heap");
    Tests.run("AUTO_STRHEAP", assigned(hs));
    Tests.print("%s\n", hs);
    AUTO_BYTES(bb, 3);
    Tests.run("AUTO_BYTES", assigned(bb));
    bb[0] = BYTES_A1;
    bb[1] = BYTES_B2;
    bb[2] = BYTES_C3;
    Tests.print("[0]=%02X, [1]=%02X, [2]=%02X\n", bb[0], bb[1], bb[2]);
    AUTO_TYPE(pt, Point);
    Tests.run("AUTO_TYPE", assigned(pt));
    pt->X = 123;
    pt->Y = 456;
    Tests.print("X=%d, Y=%d [%p]\n", pt->X, pt->Y, pt);
    Tests.run("safe_fetch YES", (safe_fetch(pt, X, 999) == 123) && (safe_fetch(pt, Y, 999) == 456));
    Point* pt2 = NULL;
    Tests.run("safe_fetch NO", safe_fetch(pt2, X, 999) == 999);
    safe_call(fn_to_safe_call, true);
    Tests.run("safe_call", safe_called);
    Tests.run("FETCH_INT_MEMBER", (FETCH_INT_MEMBER(pt, X) == 123) && (FETCH_INT_MEMBER(pt2, X) == 0));
    const char* src = "sensitive data";
    size_t len = strlen(src);
    STR_MALLOC(str, len);
    safe_free(str, len, 0x77);
    str = TYPE_MALLOC(char, len + 1);
    zero_free(str, len);
}

static inline void test_loops() {
    printf("Example using LOOP_FOREVER (requires break to stop):\n");
    LOOP_FOREVER() {
        printf("This will be repeated forever!\n<break>");
        break;
    }
    printf("\n");

    printf("Example using LOOP_TIMES to print 5 times Hello, world!:\n");
    LOOP_TIMES(5) {
        // The loop variable name is unique and internal, not accessible here
        printf("Hello, world!\n");
    }
    printf("\n");

    printf("Example using LOOP_UPTO to print numbers from 0 to 5:\n");
    LOOP_UPTO(i, 5) {
        printf("%ld ", i);
    }
    printf("\n");
    printf("\n");

    printf("Example using LOOP_UPFROMTO to print numbers from 5 to 10:\n");
    LOOP_UPFROMTO(i, 5, 10) {
        printf("%ld ", i);
    }
    printf("\n");
    printf("\n");

    printf("Example using LOOP_DOWNFROM to print numbers from 5 to 0:\n");
    LOOP_DOWNFROM(i, 5) {
        printf("%ld ", i);
    }
    printf("\n");
    printf("\n");

    printf("Example using LOOP_DOWNFROMTO to print numbers from 10 to 5:\n");
    LOOP_DOWNFROMTO(i, 10, 5) {
        printf("%ld ", i);
    }
    printf("\n");
    printf("\n");

    printf("Example using ARRAY_ITER to iterate through an array:\n");
    const int numbers[] = {10, 20, 30, 40, 50};
    ARRAY_ITER(i, numbers) {
        printf("numbers[%ld] = %d\n", i, numbers[i]);
    }
    printf("\n");

    printf("Example using ARRAY_EACH to iterate through an array:\n");
    const char* words[] = {"hello", "world", "!"};
    int xx = 0;
    ARRAY_EACH(pitem, words) {
        printf("words[%d] = %s @ %p\n", xx++, *pitem, (void*)pitem);
    }
    printf("\n");
    
    BLOCK_ONCE({
        printf("A\n");
        printf("B\n");
        printf("C\n");
    });
    BLOCK_TWICE({
        printf("AA\n");
        printf("BB\n");
        printf("CC\n");
    });
    BLOCK_THRICE({
        printf("AAA\n");
        printf("BBB\n");
        printf("CCC\n");
    });
    printf("\n");
}

unit_initialization({
    puts("First Initializer (special initializer: first in the execution order)!");
})
unit_initializer({
    puts("Static Initializer 1 (normal initializers execute in the sequential order they appear in code)!");
})
unit_initializer({
    puts("Static Initializer 2!");
})
unit_initialize({
    puts("Last Initializer (special initializer: last in the execution order)!");
})
int main(void) {
    Tests.begin("MeH");
    printf("--- LOOPS\n");
    test_loops();
    printf("--- HASH\n");
    test_hash_utilities();
    printf("--- MATH\n");
    test_math_utilities();
    printf("--- MEMORY\n");
    test_memory_utilities();
    return 0;
}
unit_finalize({
    puts("First Finalizer (special finalizer: first in the execution order)!");
})
unit_finalizer({
    puts("Static Finalizer 1 (normal finalizers execute in the reversed sequential order they appear in code)!");
})
unit_finalizer({
    puts("Static Finalizer 2!");
})
unit_finalization({
    puts("Last Finalizer (special finalizer: last in the execution order)!");
    exit(Tests.end());
})

