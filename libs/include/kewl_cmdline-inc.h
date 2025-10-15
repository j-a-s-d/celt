/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_cmdline-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

#ifndef KEWL_CMDLINE_ALIGNMENT
    #define KEWL_CMDLINE_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

#ifndef KEWL_CMDLINE_MAX_PARAMS
    #define KEWL_CMDLINE_MAX_PARAMS 64
#endif

#ifndef KEWL_CMDLINE_MAX_LINE_SIZE
    #define KEWL_CMDLINE_MAX_LINE_SIZE 256
#endif

typedef struct KEWL_CMDLINE_ALIGNMENT {
    size_t number;
    char* command;
    char** parameters;
    unsigned short parameter_count;
} cmdline_data_dt;

typedef bool (*cmdline_prompt_display_handler_fn)(size_t line_number);
typedef bool (*cmdline_command_data_handler_fn)(cmdline_data_dt* cmd_data);

// NOTE: this is required for cases where "free_commands" is false (ex. history keeping)
void cmdline_free_command_data(cmdline_data_dt* cmd_data);

// NOTE: this is usually called with stdin as input_stream
void cmdline_start(
    FILE* input_stream,
    cmdline_prompt_display_handler_fn prompt_handler,
    cmdline_command_data_handler_fn command_handler,
    bool free_commands
);

static inline bool cmdline_load_from_file(
    const char* filename,
    cmdline_prompt_display_handler_fn prompt_handler,
    cmdline_command_data_handler_fn command_handler,
    bool free_commands
) {
    FILE* tmp = fopen(filename, "r");
    if (tmp == NULL) return false;
    cmdline_start(tmp, prompt_handler, command_handler, free_commands);
    fclose(tmp);
    return true;
}

#ifdef __posix08
static inline bool cmdline_load_from_string(
    const char* input_string,
    cmdline_prompt_display_handler_fn prompt_handler,
    cmdline_command_data_handler_fn command_handler,
    bool free_commands
) {
    FILE* stream = fmemopen((void*)input_string, strlen(input_string), "r");
    if (stream == NULL) return false;
    cmdline_start(stream, prompt_handler, command_handler, free_commands);
    fclose(stream);
    return true;
}
#endif

