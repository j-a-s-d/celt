/**
 * werks_randomness: chance stuff
 */

#include "kewl.h"

#include <unistd.h>

unit_internal({ bool seeded_rng; }) = {false};

static inline unsigned int good_seed(void) {
    // NOTE: the prime numbers multiplications make the code look "kewl", so it is
    // "seconds since epoch * largest prime number less than the old RAND_MAX ^
    // the current process id * largest prime number in byte values ^
    // seconds since epoch xor process id * the luckiest prime number"
    unsigned int t = (unsigned int)time(NULL);
    unsigned int p = (unsigned int)getpid();
    unsigned int x = t ^ p;
    return (t * 32749) ^ (p * 251) ^ (x * 7);
}

static inline void random_calls(ssize_t up_to) {
    // NOTE: a small random amount of rand() calls is consumed to grease the wheels
    LOOP_TIMES((rand() % up_to) + 1) rand();
}

static void randomize(void) {
    if (internal_.seeded_rng) return;
    srand(good_seed());
    random_calls(31);
    internal_.seeded_rng = true;
}

unit_initialization({
    randomize();
})

bool coin_toss(void) {
    return rand() & 1;
}

uint8_t dice_roll(const uint8_t faces) {
    return (rand() % faces) + 1;
}

float get_random_float_decimals(void) {
    return rand() / ((float)RAND_MAX + 1.0f);
}

double get_random_double_decimals(void) {
    return rand() / (RAND_MAX + 1.0);
}

short get_short_in_range(const short from, const short to) {
    return rand() % (to - from + 1) + from;
}

int get_int_in_range(const int from, const int to) {
    return rand() % (to - from + 1) + from;
}

long get_long_in_range(const long from, const long to) {
    return rand() % (to - from + 1) + from;
}

float get_float_in_range(const float min, const float max) {
    return min + (max - min) * (rand() / ((float)RAND_MAX + 1.0f));
}

double get_double_in_range(const double min, const double max) {
    return min + (max - min) * (rand() / (RAND_MAX + 1.0));
}

void get_random_bytes_into_buffer(uint8_t* buffer, size_t size) {
    for (size_t i = 0; i < size; i++)
        buffer[i] = rand() & 0xFF;
}

uint8_t* get_random_bytes(const size_t amount) {
    if (amount == 0) return NULL;
    VAR_MALLOC_SIZE(buffer, uint8_t, amount);
    if (!buffer) return NULL;
    get_random_bytes_into_buffer(buffer, amount);
    return buffer;
}

#if defined(__posix08)

#include <fcntl.h>
#include <errno.h>

int get_secure_random_bytes(uint8_t* buffer, const size_t amount) {
    if (buffer == NULL || amount == 0) return false;
    int fd = open("/dev/urandom", O_RDONLY | O_CLOEXEC);
    if (fd < 0) return false;
    size_t total_read = 0;
    while (total_read < amount) {
        ssize_t r = read(fd, buffer + total_read, amount - total_read);
        if (r < 0) {
            if (errno == EINTR) continue;  // Interrupted, retry
            close(fd);
            return false;
        } else if (r == 0) {
            close(fd);
            return false;
        }
        total_read += r;
    }
    close(fd);
    return true;
}

#endif

char* generate_random_uuid(void) {
    VAR_MALLOC_SIZE(uuid_str, char, 37);
    if (uuid_str == NULL) return NULL;
    uint8_t bytes[16];
    get_random_bytes_into_buffer(bytes, 16);
    // Set version (4) and variant (10xx)
    bytes[6] = (bytes[6] & 0x0F) | 0x40;  // Version 4
    bytes[8] = (bytes[8] & 0x3F) | 0x80;  // Variant
    // Format UUID string
    sprintf(uuid_str,
        "%02x%02x%02x%02x-"
        "%02x%02x-"
        "%02x%02x-"
        "%02x%02x-"
        "%02x%02x%02x%02x%02x%02x",
        bytes[0], bytes[1], bytes[2], bytes[3],
        bytes[4], bytes[5],
        bytes[6], bytes[7],
        bytes[8], bytes[9],
        bytes[10], bytes[11], bytes[12], bytes[13], bytes[14], bytes[15]
    );
    return uuid_str;
}

