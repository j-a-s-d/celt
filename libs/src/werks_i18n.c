/**
 * werks_i18n: messages localization
 */

#include "werks_i18n.h"

typedef struct WERKS_I18N_MESSAGE_ALIGNMENT {
    char* code;
    char* text;
} werks_i18n_message_dt;

typedef struct WERKS_I18N_ALIGNMENT {
    char code[3]; // 2 letters + null terminator
    char* name;
    kewl_ptrholder_dt* messages;
    uint16_t id;
} werks_i18n_language_dt;

typedef struct WERKS_I18N_ALIGNMENT {
    werks_i18n_language_dt** languages;
    werks_i18n_language_dt* current;
    ssize_t size;
    ssize_t capacity;
    float capacity_grow_factor;
    float capacity_grow_padding;
} werks_i18n_dt;

unit_internal({
    werks_i18n_dt i18n;
}) = {{NULL, 0, 0, 0, WERKS_I18N_GROW_FACTOR, WERKS_I18N_GROW_PADDING}};

#define EACH_LANGUAGE(lng, blk) \
    LOOP_VAR_TIMES(idx, internal_.i18n.size) {\
        werks_i18n_language_dt* lng = internal_.i18n.languages[idx]; \
        blk \
    }

bool werks_i18n_init(void) {
    if (internal_.i18n.languages == NULL) {
        internal_.i18n.languages = ce_malloc(WERKS_I18N_INITIAL_CAPACITY * sizeof(werks_i18n_language_dt*));
        if (internal_.i18n.languages == NULL) return false;
        internal_.i18n.size = 0;
        internal_.i18n.capacity = WERKS_I18N_INITIAL_CAPACITY;
        internal_.i18n.capacity_grow_factor = WERKS_I18N_GROW_FACTOR;
        internal_.i18n.capacity_grow_padding = WERKS_I18N_GROW_PADDING;
    }
    return true;
}

ssize_t werks_i18n_get_size(void) {
    return internal_.i18n.languages == NULL ? 0 : internal_.i18n.size;
}

ssize_t werks_i18n_get_capacity(void) {
    return internal_.i18n.languages == NULL ? 0 : internal_.i18n.capacity;
}

float werks_i18n_get_capacity_grow_factor(void) {
    return internal_.i18n.capacity_grow_factor;
}

float werks_i18n_get_capacity_grow_padding(void) {
    return internal_.i18n.capacity_grow_padding;
}

void werks_i18n_set_capacity_grow_factor(float factor) {
    internal_.i18n.capacity_grow_factor = factor;
}

void werks_i18n_set_capacity_grow_padding(float padding) {
    internal_.i18n.capacity_grow_padding = padding;
}

static inline bool set_capacity(ssize_t new_capacity) {
    werks_i18n_language_dt** new_languages = TYPE_REALLOC(internal_.i18n.languages, werks_i18n_language_dt*, new_capacity);
    if (!new_languages) return false;
    internal_.i18n.languages = new_languages;
    internal_.i18n.capacity = new_capacity;
    return true;
}

bool werks_i18n_grow_capacity(float factor, float padding) {
    if (internal_.i18n.languages == NULL) return false;
    ssize_t new_capacity = (internal_.i18n.capacity * factor) + padding;
    if (internal_.i18n.capacity > new_capacity) new_capacity = internal_.i18n.capacity + 1; // ensure growth
    return set_capacity(new_capacity);
}

static bool append_language(werks_i18n_language_dt* const language) {
    if (internal_.i18n.languages == NULL || language == NULL) return false;
    if (internal_.i18n.size == internal_.i18n.capacity)
        if (!werks_i18n_grow_capacity(internal_.i18n.capacity_grow_factor, internal_.i18n.capacity_grow_padding)) return false;
    internal_.i18n.languages[internal_.i18n.size++] = language;
    return true;
}

static werks_i18n_language_dt* fetch_language(uint16_t id) {
    EACH_LANGUAGE(lng, {
        if (lng->id == id)
            return lng;
    });
    return NULL;
}

bool werks_i18n_accept_language(const char* language, const char* name) {
    if (language == NULL || name == NULL || strlen(language) != 2) return false;
    uint16_t id = pack_little_endian_16((uint8_t[2]){language[0], language[1]});
    if (assigned(fetch_language(id))) return false;
    VAR_MALLOC(lng, werks_i18n_language_dt);
    strcpy(lng->code, language);
    lng->name = strdup(name);
    lng->id = id;
    lng->messages = kewl_ptrholder_create(WERKS_I18N_MESSAGES_INITIAL_CAPACITY);
    kewl_ptrholder_set_capacity_grow_factor(lng->messages, WERKS_I18N_MESSAGES_GROW_FACTOR);
    kewl_ptrholder_set_capacity_grow_padding(lng->messages, WERKS_I18N_MESSAGES_GROW_PADDING);
    bool result = append_language(lng);
    if (internal_.i18n.current == NULL)
        internal_.i18n.current = lng;
    return result;
}

const char* werks_i18n_get_current_language(void) {
    return assigned(internal_.i18n.current) ? internal_.i18n.current->code : NULL;
}

const char* werks_i18n_get_current_language_name(void) {
    return assigned(internal_.i18n.current) ? internal_.i18n.current->name : NULL;
}

bool werks_i18n_set_current_language(const char* language) {
    if (assigned(language) && strlen(language) == 2)
        EACH_LANGUAGE(lng, {
            if (strcmp(lng->code, language) == 0) {
                internal_.i18n.current = lng;
                return true;
            }
        });
    return false;
}

static bool append_message(kewl_ptrholder_dt* messages, const char* key, const char* value) {
    if (messages == NULL || !has_content(key) || value == NULL) return false;
    VAR_MALLOC(msg, werks_i18n_message_dt);
    msg->code = strdup(key);
    msg->text = strdup(value);
    return kewl_ptrholder_add(messages, (kewl_ptrholder_ptr_dt)msg);
}

static bool remove_message(kewl_ptrholder_dt* messages, werks_i18n_message_dt* msg) {
    if (messages == NULL || msg == NULL) return false;
    ce_free(msg->code);
    ce_free(msg->text);
    ce_free(msg);
    return kewl_ptrholder_delete_once(messages, (kewl_ptrholder_ptr_dt)msg);
}

bool werks_i18n_add_message(const char* code, const char* text) {
    if (!has_content(code) || !has_content(text) || internal_.i18n.current == NULL) return false;
    return append_message(internal_.i18n.current->messages, code, text);
}

bool werks_i18n_delete_message(const char* code) {
    if (!has_content(code) || internal_.i18n.current == NULL) return false;
    bool result = false;
    PTRHOLDER_REVERSE_EACH_CASTED(internal_.i18n.current->messages, werks_i18n_message_dt, msg, {
        if (strcmp(msg->code, code) == 0)
            result |= remove_message(internal_.i18n.current->messages, msg);
    });
    return result;
}

bool werks_i18n_register_message(const char* message) { // format [lc:msg_code=msg_value] ES:hello_world=Hola Mundo!
    if (message == NULL) return false;
    string_key_value_dt* lang_kv = string_key_value_parse(message, STRINGS_COLON);
    // (lang_kv->key = "ES", lang_kv->value = "hello_world=Hola Mundo")
    uint16_t id = pack_little_endian_16((uint8_t[2]){lang_kv->key[0], lang_kv->key[1]});
    werks_i18n_language_dt* lang = fetch_language(id);
    if (lang == NULL) {
        string_key_value_destroy(lang_kv);
        return false;
    }
    string_key_value_dt* code_kv = string_key_value_parse(lang_kv->value, STRINGS_EQUAL);
    // (code_kv->key = "hello_world", code_kv->value = "Hola Mundo")
    bool result = append_message(lang->messages, code_kv->key, code_kv->value);
    string_key_value_destroy(code_kv);
    string_key_value_destroy(lang_kv);
    return result;
}

const char* werks_i18n_fetch_raw_text(const char* code) {
    if (has_content(code)) {
        PTRHOLDER_EACH_CASTED(internal_.i18n.current->messages, werks_i18n_message_dt, msg, {
            if (strcmp(msg->code, code) == 0)
                return msg->text;
        });
    }
    return WERKS_I18N_MESSAGE_DEFAULT_VALUE;
}

char* werks_i18n_get_text(const char* code, ...) {
    if (!has_content(code)) return WERKS_I18N_MESSAGE_DEFAULT_VALUE;
    const char* fmt = werks_i18n_fetch_raw_text(code);
    va_list args;
    va_start(args, code);
    ssize_t size = get_string_format_size(fmt, args);
    if (size < 0) {
        va_end(args);
        return WERKS_I18N_MESSAGE_DEFAULT_VALUE; // encoding error
    }
    char* result = perform_string_format(size, fmt, args);
    va_end(args);
    return result;
}

const char* werks_i18n_fetch_raw_language_text(const char* language, const char* code) {
    if (assigned(code) && assigned(language) && strlen(language) == 2)
        EACH_LANGUAGE(lng, {
            if (strcmp(lng->code, language) == 0) {
                PTRHOLDER_EACH_CASTED(lng->messages, werks_i18n_message_dt, msg, {
                    if (strcmp(msg->code, code) == 0)
                        return msg->text;
                });
            }
        });
    return WERKS_I18N_MESSAGE_DEFAULT_VALUE;
}

char* werks_i18n_get_language_text(const char* language, const char* code, ...) {
    if (code == NULL || language == NULL || strlen(language) != 2) return WERKS_I18N_MESSAGE_DEFAULT_VALUE;
    const char* fmt = werks_i18n_fetch_raw_language_text(language, code);
    va_list args;
    va_start(args, code);
    ssize_t size = get_string_format_size(fmt, args);
    if (size < 0) {
        va_end(args);
        return WERKS_I18N_MESSAGE_DEFAULT_VALUE; // encoding error
    }
    char* result = perform_string_format(size, fmt, args);
    va_end(args);
    return result;
}

bool werks_i18n_load_from_file(const char* filename) {
    if (filename == NULL) return false;
    FILE* file = fopen(filename, "r");
    if (file == NULL) return false;
    char* line;
    while (assigned((line = read_line_from_stream(file)))) {
        UNUSED(werks_i18n_register_message(line));
        ce_free(line);
    }
    fclose(file);
    return true;
}

void werks_i18n_deinit(void) {
    if (assigned(internal_.i18n.languages))
        EACH_LANGUAGE(lng, {
            PTRHOLDER_REVERSE_EACH_CASTED(lng->messages, werks_i18n_message_dt, msg, {
                remove_message(lng->messages, msg);
            });
            kewl_ptrholder_destroy(lng->messages);
            ce_free(lng->name);
            ce_free(lng);
        });
    ce_free(internal_.i18n.languages);
    internal_.i18n.languages = NULL;
}

#undef EACH_LANGUAGE

