/**
 * cinco --- c include outfinding tool
 * (c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "tools_declarations.h"
#include "tools_utilities.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("cinco --- c include outfinding tool\n"
            "(c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)\n"
            "\nUsage: %s <c-definition-name>\n", argv[0]);
        return EXIT_FAILURE;
    }
    load_declarations();
    printf("Loaded %zu declarations.\n", declarations_array.size);
    const char* text = argv[1];
    printf("Text to search: %s\n", text);
    struct file_declarations_dt* item = find_in_declarations_array(text);
    printf("Found at file: %s\n", item ? item->name : "-");
    unload_declarations();
    return EXIT_SUCCESS;
}

