/**
 * werks_log: buffered logging
 */

#include "werks_log.h"

unit_internal({
    char* log_filename;
    FILE* log_file;
    const char* entry_fields_separator;
    const char* entry_component_separator;
    const char* entry_prefix;
    const char* entry_suffix;
    char* ignored_levels;
    bool in_console;
    werks_log_on_flush_fail_callback_fn on_flush_fail_callback;
    size_t buffer_pos;
    char buffer[WERKS_LOG_BUFFER_SIZE];
}) = {NULL, NULL, STRINGS_PIPE, STRINGS_COLON, STRINGS_NOTHING, STRINGS_NOTHING, NULL, false, NULL, 0, STRINGS_NOTHING};

bool werks_log_is_logging(void) {
    return assigned(internal_.log_file);
}

bool werks_log_in_console(void) {
    return internal_.in_console;
}

bool werks_log_init(const char* filename) {
    if (assigned(internal_.log_file))
        werks_log_close();
    return assigned((internal_.log_file = fopen((
        internal_.log_filename = strdup((
            internal_.in_console = (filename == NULL)
        ) ? CTL_TERM : filename)
    ), "a")));
}

const char* werks_log_get_filename(void) {
    return internal_.log_filename;
}

void werks_log_set_entry_prefix(const char* value) {
    internal_.entry_prefix = ensure_const_string(value);
}

const char* werks_log_get_entry_prefix(void) {
    return internal_.entry_prefix;
}

void werks_log_set_entry_suffix(const char* value) {
    internal_.entry_suffix = ensure_const_string(value);
}

const char* werks_log_get_entry_suffix(void) {
    return internal_.entry_suffix;
}

void werks_log_set_entry_fields_separator(const char* value) {
    internal_.entry_fields_separator = ensure_const_string_def(value, STRINGS_PIPE);
}

const char* werks_log_get_entry_fields_separator(void) {
    return internal_.entry_fields_separator;
}

#ifndef KEWL_DISABLE_COMPONENT

void werks_log_set_entry_component_separator(const char* value) {
    internal_.entry_component_separator = ensure_const_string_def(value, STRINGS_COLON);
}

const char* werks_log_get_entry_component_separator(void) {
    return internal_.entry_component_separator;
}

#endif

void werks_log_add_ignored_level(char chr) {
    char* old = internal_.ignored_levels;
    internal_.ignored_levels = append_char(ensure_const_string(internal_.ignored_levels), chr);
    if (assigned(old)) ce_free(old);
}

void werks_log_remove_ignored_level(char chr) {
    char* old = internal_.ignored_levels;
    if (assigned(old)) {
        internal_.ignored_levels = remove_char(internal_.ignored_levels, chr);
        ce_free(old);
    }
}

bool werks_log_has_level_ignored(char chr) {
    return assigned(internal_.ignored_levels) && contains_char(internal_.ignored_levels, chr);
}

void werks_log_set_on_flush_fail(werks_log_on_flush_fail_callback_fn handler) {
    internal_.on_flush_fail_callback = handler;
}

werks_log_on_flush_fail_callback_fn werks_log_get_on_flush_fail(void) {
    return internal_.on_flush_fail_callback;
}

void werks_log_flush(void) {
    if (assigned(internal_.log_file) && internal_.buffer_pos > 0) {
        size_t written = fwrite(internal_.buffer, 1, internal_.buffer_pos, internal_.log_file);
        if (written < internal_.buffer_pos || fflush(internal_.log_file) != 0) {
            if (assigned(internal_.on_flush_fail_callback))
                // pass the error indicator from the stream
                internal_.on_flush_fail_callback(ferror(internal_.log_file));
            return;
        }
        internal_.buffer_pos = 0;
    }
}

void werks_log_message(char level, const char* fmt, va_list args) {
    if (fmt == NULL || args == NULL || internal_.log_file == NULL || werks_log_has_level_ignored(level)) return;
    char message[WERKS_LOG_MESSAGE_SIZE];
    int msg_len = vsnprintf(message, sizeof(message), fmt, args);
    if (msg_len < 0) return;
    char* timestamp = ISO_8601_MASK;
    char* tmp = get_timestamp();
    if (assigned(tmp)) timestamp = tmp;
    int entry_size = strlen(internal_.entry_prefix) + strlen(timestamp) + (
            strlen(internal_.entry_fields_separator) * 2
        ) + 1 + strlen(internal_.entry_suffix) + 1 + msg_len;
    if (internal_.buffer_pos + entry_size >= WERKS_LOG_BUFFER_SIZE) werks_log_flush();
    snprintf(
        internal_.buffer + internal_.buffer_pos,
        WERKS_LOG_BUFFER_SIZE - internal_.buffer_pos,
        "%s%s%s%c%s%s%s\n", // PFX TST SEP LVL SEP MSG SFX LF
        internal_.entry_prefix,
        timestamp,
        internal_.entry_fields_separator, level, internal_.entry_fields_separator, message,
        internal_.entry_suffix
    ); // build entry directly into buffer
    internal_.buffer_pos += entry_size;
    ce_free(tmp);
}

LOG_LEVEL(LOG_LEVEL_DEBUG, werks_log_debug)
LOG_LEVEL(LOG_LEVEL_INFO, werks_log_info)
LOG_LEVEL(LOG_LEVEL_WARNING, werks_log_warning)
LOG_LEVEL(LOG_LEVEL_ERROR, werks_log_error)
LOG_LEVEL(LOG_LEVEL_FATAL, werks_log_fatal)

#ifndef KEWL_DISABLE_COMPONENT

void werks_log_component_message(char level, kewl_component_dt* const component, const char* fmt, va_list args) {
    if (component == NULL || fmt == NULL || args == NULL || internal_.log_file == NULL || werks_log_has_level_ignored(level)) return;
    char message[WERKS_LOG_MESSAGE_SIZE];
    int msg_len = vsnprintf(message, sizeof(message), fmt, args);
    if (msg_len < 0) return;
    char* timestamp = ISO_8601_MASK;
    char* tmp = get_timestamp();
    if (assigned(tmp)) timestamp = tmp;
    const char* comp_inst = kewl_component_get_instance_name(component);
    int entry_size = strlen(internal_.entry_prefix) + strlen(timestamp) + (
            strlen(internal_.entry_fields_separator) * 2
        ) + 1 + strlen(internal_.entry_suffix) + 1 + msg_len + (
            strlen(comp_inst) + strlen(internal_.entry_component_separator
        ) + 1);
    if (internal_.buffer_pos + entry_size >= WERKS_LOG_BUFFER_SIZE) werks_log_flush();
    snprintf(
        internal_.buffer + internal_.buffer_pos,
        WERKS_LOG_BUFFER_SIZE - internal_.buffer_pos,
        "%s%s%s%c%s%s%s%s%s\n", // PFX TST SEP LVL SEP C_I C_S MSG SFX LF
        internal_.entry_prefix,
        timestamp,
        internal_.entry_fields_separator, level,
        internal_.entry_fields_separator, comp_inst, internal_.entry_component_separator, message,
        internal_.entry_suffix
    ); // build entry directly into buffer
    internal_.buffer_pos += entry_size;
    ce_free(tmp);
}

LOG_COMPONENT_LEVEL(LOG_LEVEL_DEBUG, werks_log_component_debug)
LOG_COMPONENT_LEVEL(LOG_LEVEL_INFO, werks_log_component_info)
LOG_COMPONENT_LEVEL(LOG_LEVEL_WARNING, werks_log_component_warning)
LOG_COMPONENT_LEVEL(LOG_LEVEL_ERROR, werks_log_component_error)
LOG_COMPONENT_LEVEL(LOG_LEVEL_FATAL, werks_log_component_fatal)

#endif

void werks_log_close(void) {
    if (assigned(internal_.log_file)) {
        werks_log_flush();
        fclose(internal_.log_file);
        internal_.log_file = NULL;
        ce_free(internal_.log_filename);
        internal_.log_filename = NULL;
        ce_free(internal_.ignored_levels);
        internal_.ignored_levels = NULL;
    }
}

unit_finalization({
    werks_log_close();
})

