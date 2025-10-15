/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_cmdline-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#include "kewl_cmdline-inc.h"

unit_container(cmdline_, {
    size_t line_number;
    size_t command_number;
}) = {0, 0};

static cmdline_data_dt* cmdline_parse_input(const char* line) {
    char temp[KEWL_CMDLINE_MAX_LINE_SIZE];
    strcpy(temp, line);
    char* command = strtok(temp, STRINGS_SPACE);
    if (command == NULL) return NULL;
    VAR_MALLOC(cmd_data, cmdline_data_dt);
    if (assigned(cmd_data)) {
        cmd_data->command = strdup(command);
        cmd_data->parameters = TYPE_MALLOC(char*, KEWL_CMDLINE_MAX_PARAMS);
        cmd_data->parameter_count = 0;
        if (cmd_data->parameters == NULL) {
            ce_free(cmd_data->command);
            ce_free(cmd_data);
            cmd_data = NULL;
        } else {
            char* token = strtok(NULL, STRINGS_SPACE);
            while (assigned(token) && cmd_data->parameter_count < KEWL_CMDLINE_MAX_PARAMS - 1) {
                cmd_data->parameters[cmd_data->parameter_count] = strdup(token);
                cmd_data->parameter_count++;
                token = strtok(NULL, STRINGS_SPACE);
            }
            cmd_data->number = ++cmdline_.command_number;
        }
    }
    return cmd_data;
}

void cmdline_free_command_data(cmdline_data_dt* cmd_data) {
    if (cmd_data == NULL) return;
    ce_free(cmd_data->command);
    for (int i = 0; i < cmd_data->parameter_count; i++)
        ce_free(cmd_data->parameters[i]);
    ce_free(cmd_data->parameters);
    ce_free(cmd_data);
}

void cmdline_start(
    FILE* input_stream,
    cmdline_prompt_display_handler_fn prompt_handler,
    cmdline_command_data_handler_fn command_handler,
    bool free_commands
) {
    if (prompt_handler == NULL || command_handler == NULL) return;
    cmdline_.command_number = 0;
    cmdline_.line_number = 0;
    char line[KEWL_CMDLINE_MAX_LINE_SIZE];
    while (prompt_handler(++cmdline_.line_number) && fgets(line, sizeof(line), input_stream)) {
        line[strcspn(line, STRINGS_LF)] = CHARS_NULL;
        cmdline_data_dt* cmd_data = cmdline_parse_input(line);
        if (assigned(cmd_data)) {
            bool r = command_handler(cmd_data);
            if (free_commands) cmdline_free_command_data(cmd_data);
            if (!r) break;
        }
    }
}

