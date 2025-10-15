/**
 * C eXTRA LiBRARiES & TOOLS
 * (c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "../include/tools_tokenization.h"
#include "../include/tools_utilities.h"

#define MIN_TOKEN_LEN 4
#define MAX_TOKEN_LEN 256

static hash_table_node_dt* tokens_hash_table[HASH_TABLE_SIZE];

void process_file(const char *filename, void (*callback)(const char *)) {
    #define meets_criteria() (idx >= MIN_TOKEN_LEN && buffer[0] != '#' && !is_c_keyword(buffer) && !hash_table_knows(tokens_hash_table, buffer) && !is_numeric_string(buffer))
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    int c, next_c;
    char buffer[MAX_TOKEN_LEN];
    size_t idx = 0;
    int last_was_dot = 0;
    int in_string = 0;
    int in_block_comment = 0;
    int in_line_comment = 0;
    int prev_char = 0; // for escape detection in strings
    while ((c = fgetc(fp)) != EOF) {
        if (in_string) {
            // Inside string literal, look for unescaped closing quote
            if (c == '"' && prev_char != '\\')
                in_string = 0;
            prev_char = c;
            continue;
        }
        if (in_block_comment) {
            // Inside block comment, look for end */
            if (c == '*' && (next_c = fgetc(fp)) == '/') {
                in_block_comment = 0;
                c = 0; // reset current char to avoid processing '/'
            } else if (c == '*') {
                // put back the char if not '/'
                if (next_c != EOF) ungetc(next_c, fp);
            }
            continue;
        }
        if (in_line_comment) {
            // Inside line comment, skip until newline
            if (c == '\n')
                in_line_comment = 0;
            continue;
        }
        // Not inside string or comment - check for comment/string start
        if (c == '"') {
            // Enter string literal, flush current token first
            while (idx > 0 && buffer[idx - 1] == '.')
                idx--;
            if (idx > 0) {
                buffer[idx] = '\0';
                if (meets_criteria())
                    callback(buffer);
                idx = 0;
            }
            in_string = 1;
            prev_char = 0;
            continue;
        }
        if (c == '/') {
            // Possible start of comment
            next_c = fgetc(fp);
            if (next_c == '/') {
                // Line comment start
                in_line_comment = 1;
                // Flush token before comment
                while (idx > 0 && buffer[idx - 1] == '.')
                    idx--;
                if (idx > 0) {
                    buffer[idx] = '\0';
                    if (meets_criteria())
                        callback(buffer);
                    idx = 0;
                }
                continue;
            } else if (next_c == '*') {
                // Block comment start
                in_block_comment = 1;
                // Flush token before comment
                while (idx > 0 && buffer[idx - 1] == '.')
                    idx--;
                if (idx > 0) {
                    buffer[idx] = '\0';
                    if (meets_criteria())
                        callback(buffer);
                    idx = 0;
                }
                continue;
            } else {
                // Not a comment, put back next_c and continue tokenizing '/'
                if (next_c != EOF) ungetc(next_c, fp);
                // '/' is not a valid token character here, so flush token
                while (idx > 0 && buffer[idx - 1] == '.')
                    idx--;
                if (idx > 0) {
                    buffer[idx] = '\0';
                    if (meets_criteria())
                        callback(buffer);
                    idx = 0;
                }
                last_was_dot = 0;
                continue;
            }
        }
        // Tokenization with dot and '#' support
        if (isalnum(c) || c == '_' || c == '.' || (c == '#' && idx == 0)) {
            if (idx == 0 && (c == '.' || (c == '#' && idx != 0))) {
                // Token cannot start with dot
                // '#' allowed only if idx == 0 (already checked)
                last_was_dot = 0;
                continue;
            }
            if (c == '.') {
                if (last_was_dot) {
                    // Two dots in a row: flush token and skip dot
                    while (idx > 0 && buffer[idx - 1] == '.')
                        idx--;
                    if (idx > 0) {
                        buffer[idx] = '\0';
                        if (meets_criteria())
                            callback(buffer);
                        idx = 0;
                    }
                    last_was_dot = 0;
                    continue;
                } else {
                    last_was_dot = 1;
                }
            } else {
                last_was_dot = 0;
            }

            if (idx < sizeof(buffer) - 1)
                buffer[idx++] = (char)c;
        } else {
            // Flush token if any
            while (idx > 0 && buffer[idx - 1] == '.')
                idx--;
            if (idx > 0) {
                buffer[idx] = '\0';
                if (meets_criteria())
                    callback(buffer);
                idx = 0;
            }
            last_was_dot = 0;
        }
        prev_char = c;
    }
    // Handle last token
    while (idx > 0 && buffer[idx - 1] == '.')
        idx--;
    if (idx > 0) {
        buffer[idx] = '\0';
        if (meets_criteria())
            callback(buffer);
    }
    fclose(fp);
    hash_table_clean(tokens_hash_table);
    #undef meets_criteria
}

