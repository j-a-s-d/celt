/**
 * werks_randomness: chance stuff
 */

#include "gem_testing.h"
#include "werks_randomness.h"

#ifdef WERKS_HELP
CE_MESSAGE("compile with: -Wall -Wfatal-errors -I../include -I../src -o ../bin/werks_randomness_test ../src/kewl.c ../src/werks_randomness.c werks_randomness_test.c")
#endif

int main() {
    Tests.begin("WeRKS RANDOMNESS");

    Tests.print("Coin toss: %s\n", coin_toss() ? "HEADS" : "TAILS");
    Tests.print("Coin toss: %s\n", coin_toss() ? "HEADS" : "TAILS");
    Tests.print("Coin toss: %s\n", coin_toss() ? "HEADS" : "TAILS");
    Tests.println();

    int x = dice_roll(6);
    Tests.run("dice_roll", IN_RANGE(x, 1, 6));
    Tests.print("Dice roll: %d\n", x);
    x = dice_roll(6);
    Tests.run("dice_roll", IN_RANGE(x, 1, 6));
    Tests.print("Dice roll: %d\n", x);
    x = dice_roll(6);
    Tests.run("dice_roll", IN_RANGE(x, 1, 6));
    Tests.print("Dice roll: %d\n", x);
    Tests.println();

    Tests.print("Random float decimals: %f\n", get_random_float_decimals());
    Tests.print("Random float decimals: %f\n", get_random_float_decimals());
    Tests.print("Random float decimals: %f\n", get_random_float_decimals());
    Tests.println();
    
    Tests.print("Random double decimals: %lf\n", get_random_double_decimals());
    Tests.print("Random double decimals: %lf\n", get_random_double_decimals());
    Tests.print("Random double decimals: %lf\n", get_random_double_decimals());
    Tests.println();

    short s = get_short_in_range(-10, 15);
    Tests.run("get_short_in_range", IN_RANGE(s, -10, 15));
    Tests.print("Short from -10 to 15: %hd\n", s);
    s = get_short_in_range(-110, 115);
    Tests.run("get_short_in_range", IN_RANGE(s, -110, 115));
    Tests.print("Short from -110 to 115: %hd\n", s);
    s = get_short_in_range(-1110, 1115);
    Tests.run("get_short_in_range", IN_RANGE(s, -1110, 1115));
    Tests.print("Short from -1110 to 1115: %hd\n", s);
    Tests.println();

    int i = get_int_in_range(-10, 15);
    Tests.run("get_int_in_range", IN_RANGE(i, -10, 15));
    Tests.print("Int from -10 to 15: %d\n", i);
    i = get_int_in_range(-110, 115);
    Tests.run("get_int_in_range", IN_RANGE(i, -110, 115));
    Tests.print("Int from -110 to 115: %d\n", i);
    i = get_int_in_range(-1110, 1115);
    Tests.run("get_int_in_range", IN_RANGE(i, -1110, 1115));
    Tests.print("Int from -1110 to 1115: %d\n", i);
    Tests.println();

    long l = get_long_in_range(-10, 15);
    Tests.run("get_long_in_range", IN_RANGE(l, -10, 15));
    Tests.print("Long from -10 to 15: %ld\n", l);
    l = get_long_in_range(-110, 115);
    Tests.run("get_long_in_range", IN_RANGE(l, -110, 115));
    Tests.print("Long from -110 to 115: %ld\n", l);
    l = get_long_in_range(-1110, 1115);
    Tests.run("get_long_in_range", IN_RANGE(l, -1110, 1115));
    Tests.print("Long from -1110 to 1115: %ld\n", l);
    Tests.println();

    float f = get_float_in_range(10.0f, 15.5f);
    Tests.run("get_float_in_range", IN_RANGE(f, 10.0f, 15.5f));
    Tests.print("Number from 10f to 15.5f: %f\n", f);
    f = get_float_in_range(110.0f, 115.5f);
    Tests.run("get_float_in_range", IN_RANGE(f, 110.0f, 115.5f));
    Tests.print("Number from 110f to 115.5f: %f\n", f);
    f = get_float_in_range(1110.0f, 1115.5f);
    Tests.run("get_float_in_range", IN_RANGE(f, 1110.0f, 1115.5f));
    Tests.print("Number from 1110f to 1115.5f: %f\n", f);
    Tests.println();

    double d = get_double_in_range(10.0, 15.5);
    Tests.run("get_double_in_range", IN_RANGE(d, 10.0, 15.5));
    Tests.print("Number from 10 to 15.5: %lf\n", d);
    d = get_double_in_range(110.0, 115.5);
    Tests.run("get_double_in_range", IN_RANGE(d, 110.0, 115.5));
    Tests.print("Number from 110 to 115.5: %lf\n", d);
    d = get_double_in_range(1110.0, 1115.5);
    Tests.run("get_double_in_range", IN_RANGE(d, 1110.0, 1115.5));
    Tests.print("Number from 1110 to 1115.5: %lf\n", d);
    Tests.println();

    size_t n = 10;
    __auto uint8_t* bytes = get_random_bytes(n);
    Tests.run("get_random_bytes", assigned(bytes));
    if (bytes) {
        Tests.print("Random bytes (%zu): ", n);
        for (size_t i = 0; i < n; i++)
            Tests.print("%02X\n", bytes[i]);
    }
    Tests.println();

    AUTO_STRING(g1, generate_random_uuid());
    Tests.run("generate_random_uuid", has_content(g1));
    Tests.print("GUID: %s\n", g1);
    AUTO_STRING(g2, generate_random_uuid());
    Tests.run("generate_random_uuid", has_content(g2));
    Tests.print("GUID: %s\n", g2);
    AUTO_STRING(g3, generate_random_uuid());
    Tests.run("generate_random_uuid", has_content(g3));
    Tests.print("GUID: %s\n", g3);
    return Tests.end();
}

