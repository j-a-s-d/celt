/**
 * cinex --- c include expanding tool
 * (c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INCLUDE_DIRS 99
const char* include_dirs[MAX_INCLUDE_DIRS + 1]; // +1 for NULL terminator

#define ENV_SEPARATOR (":") // use ';' on Windows
void load_include_dirs_from_env() {
    const char* env = getenv("CPATH");
    if (!env) env = getenv("C_INCLUDE_PATH");
    if (!env) env = getenv("CPLUS_INCLUDE_PATH");
    if (!env) env = getenv("INCLUDE"); // usually useful in Windows
    if (!env) { // fallback to default include dirs
        include_dirs[0] = ".";
        include_dirs[1] = "/usr/include";
        include_dirs[2] = "/usr/local/include";
        include_dirs[3] = NULL;
        return;
    }
    static char paths_copy[1024];
    strncpy(paths_copy, env, sizeof(paths_copy));
    paths_copy[sizeof(paths_copy) - 1] = '\0';
    int count = 0;
    char* token = strtok(paths_copy, ENV_SEPARATOR);
    while (token && count < MAX_INCLUDE_DIRS) {
        include_dirs[count++] = token;
        token = strtok(NULL, ENV_SEPARATOR);
    }
    include_dirs[count] = NULL;
}

FILE* open_include_file(const char* filename) {
    for (int i = 0; include_dirs[i] != NULL; i++) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", include_dirs[i], filename);
        FILE* f = fopen(path, "r");
        if (f != NULL) return f; // found and opened
    }
    return NULL; // not found in any include dir
}

#define MAX_LINE 1024
// Recursively process a file, expanding only #include directives
void process_file(const char* filename) {
    FILE* f = open_include_file(filename);
    if (!f) {
        fprintf(stderr, "Error: cannot open file %s\n", filename);
        return;
    }
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), f)) {
        // Trim leading whitespace
        char* p = line;
        while (*p == ' ' || *p == '\t') p++;
        // Check if line starts with #include "
        if (strncmp(p, "#include \"", 10) == 0) {
            // Extract the filename inside quotes
            char* start = p + 10; // position after #include "
            char* end = strchr(start, '"');
            if (end) {
                *end = '\0';
                // Recursively process the included file
                char buffer[256];
                snprintf(buffer, sizeof(buffer), "// [cinex] while processing \"%s\" begins expansion of \"%s\"\n", filename, start);
                fputs(buffer, stdout);
                process_file(start);
                continue; // skip printing this include line
            }
        }
        // For all other lines (including macros), print as is
        fputs(line, stdout);
    }
    fclose(f);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("cinex --- c include expanding tool\n"
            "(c) 2025 by Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)\n"
            "\nUsage: %s <c-header-file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    // NOTE: besides it only expands #includes that are between quotes (") and that
    // are formed with a single space separating #include from the quoted filename,
    // we will look in directories defined in common environment variables beyond
    // the current directory (.).
    // It ignores any preprocessor directive.
    load_include_dirs_from_env();
    process_file(argv[1]);
    return EXIT_SUCCESS;
}

