/**
 * chime - c header included members explorer tool
 * (c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "tools_declarations.h"
#include "tools_utilities.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("cinco --- c header included members explorer tool\n"
            "(c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)\n"
            "\nUsage: %s <header-file-name>\n", argv[0]);
        return EXIT_FAILURE;
    }
    load_declarations();
    printf("Loaded %zu declarations.\n", declarations_array.size);
    const char* filename = argv[1];
    printf("File: %s\n", filename);
    struct file_declarations_dt* item = get_file_declarations(filename);
    if (item == NULL) {
        printf("File not found.\n");
        return EXIT_FAILURE;
    }
    printf("-- Globals\n");
    if (item->globals_len == 0) {
        printf("    -\n");
    } else for (size_t i = 0; i < item->globals_len; i++)
        printf("    %s\n", item->globals[i]);
    printf("-- Types\n");
    if (item->types_len == 0) {
        printf("    -\n");
    } else for (size_t i = 0; i < item->types_len; i++)
        printf("    %s\n", item->types[i]);
    printf("-- Macros\n");
    if (item->macros_len == 0) {
        printf("    -\n");
    } else for (size_t i = 0; i < item->macros_len; i++)
        printf("    %s\n", item->macros[i]);
    printf("-- Functions\n");
    if (item->functions_len == 0) {
        printf("    -\n");
    } else for (size_t i = 0; i < item->functions_len; i++)
        printf("    %s\n", item->functions[i]);
    unload_declarations();
    return EXIT_SUCCESS;
}

