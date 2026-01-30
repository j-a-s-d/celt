/**
 * werks_ansi: ansi constants and routines
 */

#include "werks_ansi.h"

bool has_ansi_codes(const char* input) {
    if (assigned(input)) {
        size_t len = strlen(input);
        for (size_t i = 0; i < len; i++) {
            if (input[i] == ANSI_ESCAPE[0])
                if (i + 1 < len && input[i + 1] == CHARS_BRACKETS_OPEN)
                    return true;
        }
    }
    return false;
}

char* strip_ansi_codes(const char* input) {
    if (input == NULL) return NULL;
    size_t len = strlen(input);
    VAR_MALLOC_SIZE(output, char, len + 1);
    if (output == NULL) return NULL;
    size_t i = 0, j = 0;
    bool in_escape = false;
    bool in_csi = false; // Control Sequence Introducer
    while (i < len)
        if (!in_escape) {
            if (input[i] == ANSI_ESCAPE[0]) {
                in_escape = true;
                i++;
            } else
                output[j++] = input[i++];
        } else
            if (!in_csi) { // expect '[' after ESC for CSI sequences
                if (input[i] == CHARS_BRACKETS_OPEN) {
                    in_csi = true;
                    i++;
                } else // not a CSI sequence, just skip one char
                    in_escape = false;
            } else { // inside CSI sequence - consume until a letter in the range @-~ (final byte)
                if ((input[i] >= CHARS_AT && input[i] <= CHARS_TILDE)) { // end of CSI sequence
                    in_escape = false;
                    in_csi = false;
                    i++;
                } else // consume argument bytes inside CSI
                    i++;
            }
    output[j] = CHARS_NULL;
    return output;
}

void printf_at(int row, int col, const char* format, ...) {
    va_list args;
    va_start(args, format);
    printf(ANSI_CODE_CURSOR_REPOSITION_FORMAT, row, col);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
}

