/**
 * ceems --- c code well-known includes good-enough inference tool
 * (c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "tools_declarations.h"
#include "tools_tokenization.h"
#include "tools_utilities.h"

static hash_table_node_dt* includes_hash_table[HASH_TABLE_SIZE];

void process_token(const char* token) {
    struct file_declarations_dt* item = find_in_declarations_array(token);
    if (item && !hash_table_knows(includes_hash_table, item->name))
        printf("#include <%s>\n", item->name);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("ceems --- c code well-known includes good-enough inference tool\n"
            "(c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)\n"
            "\nUsage: %s <c-source-file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    load_declarations();
    process_file(argv[1], process_token);
    hash_table_clean(includes_hash_table);
    unload_declarations();
    return EXIT_SUCCESS;
}

