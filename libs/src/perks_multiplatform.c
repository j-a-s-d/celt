/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: PeRKS MULTIPLATFORM
 * File: perks_multiplatform.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "kewl.h"

#include <float.h> /* LDBL_DIG */
#include <complex.h>

#ifndef __c11
#error "perks_multiplatform requires the C11 or higher to work."
#endif

void echo_ptr(const void* x) {
    printf("%p\n", x);
}

void echo_int(int x) {
    printf("%d\n", x);
}

void echo_float(float x) {
    printf("%f\n", x);
}

void echo_double(double x) {
    printf("%lf\n", x);
}

void echo_char(char x) {
    printf("%c\n", x);
}

void echo_signed_char(signed char x) {
    printf("%hhi\n", x);
}

void echo_unsigned_char(unsigned char x) {
    printf("%hhu\n", x);
}

void echo_short(short x) {
    printf("%hi\n", x);
}

void echo_unsigned_short(unsigned short x) {
    printf("%hu\n", x);
}

void echo_str(const char* x) {
    printf("%s\n", x);
}

void echo_bool(bool x) {
    printf("%s\n", x ? "true" : "false");
}

void echo_long_double(long double x) {
    printf("%.*Lf\n", LDBL_DIG, x);
}

void echo_float_complex(float _Complex x) {
    printf("%.2f %+.2fi\n", crealf(x), cimagf(x));
}

void echo_double_complex(double _Complex x) {
    printf("%.2lf %+.2lfi\n", creal(x), cimag(x));
}

void echo_long_double_complex(long double _Complex x) {
    printf("%.2Lf %+.2Lfi\n", creall(x), cimagl(x));
}

void echo_long_int(long int x) {
    printf("%ld\n", x);
}

void echo_long_long_int(long long int x) {
    printf("%lld\n", x);
}

void echo_unsigned_int(unsigned int x) {
    printf("%u\n", x);
}

void echo_unsigned_long_int(unsigned long int x) {
    printf("%lu\n", x);
}

void echo_unsigned_long_long_int(unsigned long long int x) {
    printf("%llu\n", x);
}

