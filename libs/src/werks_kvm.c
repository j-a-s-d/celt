/**
 * werks_kvm: general-purpose key-value map
 */

#include "werks_kvm.h"

struct WERKS_KVM_ALIGNMENT werks_kvm_dt {
    kewl_component_dt* component_instance;
    werks_kvm_dt* parent;
    bool packable;
    // options
    char* eol_replacement;
    werks_kvm_untyped_treatment_dt untyped_treatment;
    // arrays
    uint8_t* checksums;
    char** keys;
    werks_kvm_type_dt* types;
    void** values;
    // dimensions
    ssize_t size;
    ssize_t capacity;
    float capacity_grow_factor;
    float capacity_grow_padding;
    // events
    werks_kvm_on_before_read_from_file_handler_fn on_before_read_from_file;
    werks_kvm_on_before_write_to_file_handler_fn on_before_write_to_file;
    werks_kvm_on_before_read_from_string_handler_fn on_before_read_from_string;
    werks_kvm_on_before_write_to_string_handler_fn on_before_write_to_string;
    werks_kvm_on_before_store_item_handler_fn on_before_store_item;
    werks_kvm_on_before_overwrite_item_handler_fn on_before_overwrite_item;
    werks_kvm_on_before_rename_item_handler_fn on_before_rename_item;
    werks_kvm_on_before_delete_item_handler_fn on_before_delete_item;
    werks_kvm_on_before_transfer_item_handler_fn on_before_transfer_item;
    werks_kvm_on_before_copy_item_handler_fn on_before_copy_item;
    // permissions
    bool allow_set;
    bool allow_rename;
    bool allow_retype;
    bool allow_delete;
    bool allow_transfer;
    bool allow_copy;
    bool allow_pack;
    bool allow_loop;
    bool allow_persistence;
    bool allow_events;
};

typedef struct WERKS_KVM_ALIGNMENT {
    void* bp;
    ssize_t sz;
} werks_kvm_buffer_dt;

static inline bool setup_map_arrays(werks_kvm_dt* const map, ssize_t capacity) {
    map->checksums = TYPE_MALLOC(uint8_t, capacity); 
    map->types = TYPE_MALLOC(werks_kvm_type_dt, capacity);
    map->keys = TYPE_MALLOC(char*, capacity);
    map->values = TYPE_MALLOC(void*, capacity);
    return assigned(map->checksums) && assigned(map->types) && assigned(map->keys) && assigned(map->values);
}

static inline void reset_map_dimensions(werks_kvm_dt* const map, ssize_t capacity) {
    map->size = 0;
    map->capacity = capacity;
    map->capacity_grow_factor = WERKS_KVM_GROW_FACTOR;
    map->capacity_grow_padding = WERKS_KVM_GROW_PADDING;
}

static inline void free_value(werks_kvm_type_dt type, void* const ptr) {
    if (type == WERKS_KVM_TYPE_KVM) {
        werks_kvm_destroy((werks_kvm_dt*)ptr);
    } else {
        if (type == WERKS_KVM_TYPE_BUFFER)
            ce_free(((werks_kvm_buffer_dt*)ptr)->bp);
        ce_free(ptr);
    }
}

static inline void erase_map_item(werks_kvm_dt* const map, int index) {
    map->checksums[index] = BYTES_00;
    map->keys[index] = NULL;
    map->values[index] = NULL;
    map->types[index] = WERKS_KVM_TYPE_NOTHING;
    map->packable = true;
}

static inline bool destroy_map_item(werks_kvm_dt* const map, int index) {
    if (map->allow_events && assigned(map->on_before_delete_item))
        if (!map->on_before_delete_item(map, map->keys[index]))
            return false;
    ce_free(map->keys[index]);
    free_value(map->types[index], map->values[index]);
    erase_map_item(map, index);
    return true;
}

static inline void set_map_flags(werks_kvm_dt* const map, bool flag_set, bool flag_rename, bool flag_retype, bool flag_delete, bool flag_transfer, bool flag_copy, bool flag_pack, bool flag_loop, bool flag_persistence, bool flag_events) {
    map->allow_set = flag_set;
    map->allow_rename = flag_rename;
    map->allow_retype = flag_retype;
    map->allow_delete = flag_delete;
    map->allow_transfer = flag_transfer;
    map->allow_copy = flag_copy;
    map->allow_pack = flag_pack;
    map->allow_loop = flag_loop;
    map->allow_persistence = flag_persistence;
    map->allow_events = flag_events;
}

static inline void set_map_events(werks_kvm_dt* const map,
    werks_kvm_on_before_read_from_file_handler_fn on_before_read_from_file_handler,
    werks_kvm_on_before_write_to_file_handler_fn on_before_write_to_file_handler,
    werks_kvm_on_before_read_from_string_handler_fn on_before_read_from_string_handler,
    werks_kvm_on_before_write_to_string_handler_fn on_before_write_to_string_handler,
    werks_kvm_on_before_store_item_handler_fn on_before_store_item_handler,
    werks_kvm_on_before_overwrite_item_handler_fn on_before_overwrite_item_handler,
    werks_kvm_on_before_rename_item_handler_fn on_before_rename_item_handler,
    werks_kvm_on_before_delete_item_handler_fn on_before_delete_item_handler,
    werks_kvm_on_before_transfer_item_handler_fn on_before_transfer_item_handler,
    werks_kvm_on_before_copy_item_handler_fn on_before_copy_item_handler) {
        map->on_before_read_from_file = on_before_read_from_file_handler;
        map->on_before_write_to_file = on_before_write_to_file_handler;
        map->on_before_read_from_string = on_before_read_from_string_handler;
        map->on_before_write_to_string = on_before_write_to_string_handler;
        map->on_before_store_item = on_before_store_item_handler;
        map->on_before_overwrite_item = on_before_overwrite_item_handler;
        map->on_before_rename_item = on_before_rename_item_handler;
        map->on_before_delete_item = on_before_delete_item_handler;
        map->on_before_transfer_item = on_before_transfer_item_handler;
        map->on_before_copy_item = on_before_copy_item_handler;
}

static inline void set_map_item(werks_kvm_dt* const map, int index, werks_kvm_type_dt type, char* key, void* value) {
    map->checksums[index] = crc8_string(key);
    map->types[index] = type;
    map->keys[index] = key;
    map->values[index] = value;
}

static inline void free_items_arrays(uint8_t* checksums, werks_kvm_type_dt* types, char** keys, void** values) {
    ce_free(checksums);
    ce_free(types);
    ce_free(keys);
    ce_free(values);
}

// kvm constructor
werks_kvm_dt* werks_kvm_create(ssize_t initial_capacity) {
    RET_MALLOC(werks_kvm_dt, {
        if (!setup_map_arrays(result, initial_capacity)) {
            werks_kvm_destroy(result);
            return NULL;
        }
        reset_map_dimensions(result, initial_capacity);
        set_map_flags(result, true, true, true, true, true, true, true, true, true, true);
        set_map_events(result, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        result->eol_replacement = strdup(WERKS_KVM_MULTILINE_STRINGS_EOL);
        result->untyped_treatment = WERKS_KVM_UNTYPED_TREATMENT_DEFAULT;
        result->parent = NULL;
        result->packable = false; // initial capacity is not zappable on purpose
        result->component_instance = kewl_component_create(result, WERKS_KVM_TYPE_NAME);
    });
}

// kvm destructor
void werks_kvm_destroy(werks_kvm_dt* const map) {
    if (map == NULL) return;
    map->allow_events = false;
    set_map_events(map, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    for (ssize_t i = 0; i < map->size; i++)
        UNUSED(destroy_map_item(map, i));
    free_items_arrays(map->checksums, map->types, map->keys, map->values);
    map->checksums = NULL;
    map->types = NULL;
    map->keys = NULL;
    map->values = NULL;
    reset_map_dimensions(map, 0);
    ce_free(map->eol_replacement);
    map->parent = NULL;
    kewl_component_destroy(map->component_instance);
    map->component_instance = NULL;
    ce_free(map);
}

const kewl_component_dt* werks_kvm_get_component(werks_kvm_dt* const map) {
    return map == NULL ? NULL : map->component_instance;
}

// kvm flags

void werks_kvm_enable_set(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_set = true;
}

void werks_kvm_disable_set(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_set = false;
}

bool werks_kvm_is_set_allowed(werks_kvm_dt* const map) {
    return assigned(map) ? map->allow_set : false;
}

void werks_kvm_enable_retype(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_retype = true;
}

void werks_kvm_disable_retype(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_retype = false;
}

bool werks_kvm_is_retype_allowed(werks_kvm_dt* const map) {
    return assigned(map) ? map->allow_retype : false;
}

void werks_kvm_enable_rename(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_rename = true;
}

void werks_kvm_disable_rename(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_rename = false;
}

bool werks_kvm_is_rename_allowed(werks_kvm_dt* const map) {
    return assigned(map) ? map->allow_rename : false;
}

void werks_kvm_enable_delete(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_delete = true;
}

void werks_kvm_disable_delete(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_delete = false;
}

bool werks_kvm_is_delete_allowed(werks_kvm_dt* const map) {
    return assigned(map) ? map->allow_delete : false;
}

void werks_kvm_enable_transfer(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_transfer = true;
}

void werks_kvm_disable_transfer(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_transfer = false;
}

bool werks_kvm_is_transfer_allowed(werks_kvm_dt* const map) {
    return assigned(map) ? map->allow_transfer : false;
}

void werks_kvm_enable_copy(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_copy = true;
}

void werks_kvm_disable_copy(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_copy = false;
}

bool werks_kvm_is_copy_allowed(werks_kvm_dt* const map) {
    return assigned(map) ? map->allow_copy : false;
}

void werks_kvm_enable_pack(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_pack = true;
}

void werks_kvm_disable_pack(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_pack = false;
}

bool werks_kvm_is_pack_allowed(werks_kvm_dt* const map) {
    return assigned(map) ? map->allow_pack : false;
}

void werks_kvm_enable_loop(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_loop = true;
}

void werks_kvm_disable_loop(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_loop = false;
}

bool werks_kvm_is_loop_allowed(werks_kvm_dt* const map) {
    return assigned(map) ? map->allow_loop : false;
}

void werks_kvm_enable_persistence(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_persistence = true;
}

void werks_kvm_disable_persistence(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_persistence = false;
}

bool werks_kvm_is_persistence_allowed(werks_kvm_dt* const map) {
    return assigned(map) ? map->allow_persistence : false;
}

void werks_kvm_enable_events(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_events = true;
}

void werks_kvm_disable_events(werks_kvm_dt* const map) {
    if (assigned(map)) map->allow_events = false;
}

bool werks_kvm_are_events_allowed(werks_kvm_dt* const map) {
    return assigned(map) ? map->allow_events : false;
}

static bool is_map_item(werks_kvm_dt* const map, ssize_t index, const char* name, uint8_t checksum) {
    const char* key = map->keys[index];
    return assigned(key) && (map->checksums[index] == checksum) && strcmp(key, name) == 0;
}

// Function to store a key-value pair into the map.
// If not already in the map, it reuses the first unusued slot (if any),
// otherwise assigns a new one, and if it reaches its limit tries to double its capacity.
// Returns true on success, false otherwise.
static bool store_item(werks_kvm_dt* const map, werks_kvm_type_dt type, const char* key, void* value) {
    if (map->allow_events && assigned(map->on_before_store_item))
        if (!map->on_before_store_item(map, key, type, value))
            return false;
    bool unused_found = false;
    ssize_t first_unused;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] == WERKS_KVM_TYPE_NOTHING && !unused_found) {
            unused_found = true;
            first_unused = i;
        } else if (assigned(map->keys[i]) && strcmp(map->keys[i], key) == 0) {
            if (!map->allow_retype && map->types[i] != type) return false;
            if (map->values[i] != value) {
                if (map->allow_events && assigned(map->on_before_overwrite_item))
                    if (!map->on_before_overwrite_item(map, key, type, value))
                        return false;
                free_value(map->types[i], map->values[i]);
                map->values[i] = value;
            }
            map->types[i] = type;
            return true;
        }
    char* key_copy = strdup(key);
    if (key_copy == NULL) return false;
    if (unused_found) {
        set_map_item(map, first_unused, type, key_copy, value);
        return true;
    }
    if (map->size == map->capacity) {
        ssize_t new_capacity = (map->capacity * map->capacity_grow_factor) + map->capacity_grow_padding;
        if (map->capacity > new_capacity) new_capacity = map->capacity + 1; // ensure growth
        uint8_t* new_checksums = TYPE_REALLOC(map->checksums, uint8_t, new_capacity);
        werks_kvm_type_dt* new_types = TYPE_REALLOC(map->types, werks_kvm_type_dt, new_capacity);
        char** new_keys = TYPE_REALLOC(map->keys, char*, new_capacity);
        void** new_values = TYPE_REALLOC(map->values, void*, new_capacity);
        if (new_checksums == NULL || new_types == NULL || new_keys == NULL || new_values == NULL) {
            free_items_arrays(new_checksums, new_types, new_keys, new_values);
            return false;
        }
        map->checksums = new_checksums;
        map->types = new_types;
        map->keys = new_keys;
        map->values = new_values;
        map->capacity = new_capacity;
    }
    set_map_item(map, map->size, type, key_copy, value);
    map->size++;
    return true;
}

static void* direct_fetch_map_item_value(werks_kvm_dt* const map, const char* key, werks_kvm_type_dt type) {
    uint8_t checksum = crc8_string(key);
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] == type)
            if (is_map_item(map, i, key, checksum))
                return map->values[i];
    return NULL;
}

// Recursive "xpath-like" traversal resolving the key to the item
static void* xpath_fetch_map_item_value(werks_kvm_dt* const map, const char* key, werks_kvm_type_dt type) {
    char key_copy[WERKS_KVM_KEY_MAX_LEN];
    strncpy(key_copy, key, sizeof(key_copy));
    key_copy[sizeof(key_copy) - 1] = CHARS_NULL;
    char* token = strtok(key_copy, WERKS_KVM_KEY_XPATH_SEPARATOR);
    werks_kvm_dt* current = map;
    while (assigned(token)) {
        if (werks_kvm_get_item_type(current, token) == WERKS_KVM_TYPE_KVM) {
            current = direct_fetch_map_item_value(current, token, WERKS_KVM_TYPE_KVM);
            if (current == NULL)
                break;
            token = strtok(NULL, WERKS_KVM_KEY_XPATH_SEPARATOR);
            continue;
        }
        return direct_fetch_map_item_value(current, token, type);
    }
    return type == WERKS_KVM_TYPE_KVM ? current : NULL;
}

static inline void* get_map_item_value(werks_kvm_dt* const map, const char* key, werks_kvm_type_dt type) {
    return assigned(map) ? (
        contains_string(key, WERKS_KVM_KEY_XPATH_SEPARATOR) ?
        xpath_fetch_map_item_value(map, key, type) :
        direct_fetch_map_item_value(map, key, type)
    ) : NULL;
}

// Check if the provided key exists
bool werks_kvm_has_item(werks_kvm_dt* const map, const char* key) {
    if (assigned(map) && has_content(key)) {
        uint8_t checksum = crc8_string(key);
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (is_map_item(map, i, key, checksum))
                    return true;
    }
    return false;
}

// Check if the provided key exists and has the specified type
bool werks_kvm_has_typed_item(werks_kvm_dt* const map, const char* key, werks_kvm_type_dt type) {
    if (assigned(map) && has_content(key) && type != WERKS_KVM_TYPE_NOTHING) {
        uint8_t checksum = crc8_string(key);
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] == type)
                if (is_map_item(map, i, key, checksum))
                    return true;
    }
    return false;
}

// Check if at least one element of the provided type exists
bool werks_kvm_has_items_typed(werks_kvm_dt* const map, werks_kvm_type_dt type) {
    if (assigned(map) && type != WERKS_KVM_TYPE_NOTHING)
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] == type)
                return true;
    return false;
}

// Check if at least one element with a different type from the provided one exists
bool werks_kvm_has_items_not_typed(werks_kvm_dt* const map, werks_kvm_type_dt type) {
    if (assigned(map))
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (map->types[i] != type)
                    return true;
    return false;
}

// Check if at least one element with the provided prefix exists
bool werks_kvm_has_items_prefixed(werks_kvm_dt* const map, const char* prefix) {
    if (assigned(map))
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (starts_with(map->keys[i], prefix))
                    return true;
    return false;
}

// Check if at least one element with a different prefix from the provided one exists
bool werks_kvm_has_items_not_prefixed(werks_kvm_dt* const map, const char* prefix) {
    if (assigned(map))
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (!starts_with(map->keys[i], prefix))
                    return true;
    return false;
}

// Check if at least one element with the provided suffix exists
bool werks_kvm_has_items_suffixed(werks_kvm_dt* const map, const char* suffix) {
    if (assigned(map))
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (ends_with(map->keys[i], suffix))
                    return true;
    return false;
}

// Check if at least one element with a different suffix from the provided one exists
bool werks_kvm_has_items_not_suffixed(werks_kvm_dt* const map, const char* suffix) {
    if (assigned(map))
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (!starts_with(map->keys[i], suffix))
                    return true;
    return false;
}

// Retrieve the specified type from the map
werks_kvm_type_dt werks_kvm_get_item_type(werks_kvm_dt* const map, const char* key) {
    if (assigned(map) && has_content(key)) {
        uint8_t checksum = crc8_string(key);
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (is_map_item(map, i, key, checksum))
                    return map->types[i];
    }
    return WERKS_KVM_TYPE_NOTHING; // Key not found
}

// Marks the specified map entry as deleted
bool werks_kvm_delete_item(werks_kvm_dt* const map, const char* key) {
    if (assigned(map) && map->allow_delete && has_content(key)) {
        uint8_t checksum = crc8_string(key);
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (is_map_item(map, i, key, checksum))
                    return destroy_map_item(map, i);
    }
    return false;
}

// Marks the map entries matching the specified type as deleted (returns true if at least one item is deleted)
bool werks_kvm_delete_typed_items(werks_kvm_dt* const map, werks_kvm_type_dt type) {
    if (map == NULL || !map->allow_delete || type == WERKS_KVM_TYPE_NOTHING) return false;
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] == type)
            result |= destroy_map_item(map, i);
    return result;
}

// Marks the map entries not matching the specified type as deleted (returns true if at least one item is deleted)
bool werks_kvm_delete_not_typed_items(werks_kvm_dt* const map, werks_kvm_type_dt type) {
    if (map == NULL || !map->allow_delete || type == WERKS_KVM_TYPE_NOTHING) return false;
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (map->types[i] != type)
                result |= destroy_map_item(map, i);
    return result;
}

// Marks the map entries matching the specified prefix as deleted (returns true if at least one item is deleted)
bool werks_kvm_delete_prefixed_items(werks_kvm_dt* const map, const char* prefix) {
    if (map == NULL || !map->allow_delete) return false;
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (starts_with(map->keys[i], prefix))
                result |= destroy_map_item(map, i);
    return result;
}

// Marks the map entries not matching the specified prefix as deleted (returns true if at least one item is deleted)
bool werks_kvm_delete_not_prefixed_items(werks_kvm_dt* const map, const char* prefix) {
    if (map == NULL || !map->allow_delete) return false;
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!starts_with(map->keys[i], prefix))
                result |= destroy_map_item(map, i);
    return result;
}

// Marks the map entries matching the specified suffix as deleted (returns true if at least one item is deleted)
bool werks_kvm_delete_suffixed_items(werks_kvm_dt* const map, const char* suffix) {
    if (map == NULL || !map->allow_delete) return false;
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (ends_with(map->keys[i], suffix))
                result |= destroy_map_item(map, i);
    return result;
}

// Marks the map entries not matching the specified suffix as deleted (returns true if at least one item is deleted)
bool werks_kvm_delete_not_suffixed_items(werks_kvm_dt* const map, const char* suffix) {
    if (map == NULL || !map->allow_delete) return false;
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!ends_with(map->keys[i], suffix))
                result |= destroy_map_item(map, i);
    return result;
}

// Retrieves the map capacity (all the available for items)
ssize_t werks_kvm_get_capacity(werks_kvm_dt* const map) {
    return map == NULL ? 0 : map->capacity;
}

// Retrieves the map size (all slots, active and inactive)
ssize_t werks_kvm_get_size(werks_kvm_dt* const map) {
    return map == NULL ? 0 : map->size;
}

float werks_kvm_get_capacity_grow_factor(werks_kvm_dt* const map) {
    return map == NULL ? 0.0f : map->capacity_grow_factor;
}

float werks_kvm_get_capacity_grow_padding(werks_kvm_dt* const map) {
    return map == NULL ? 0.0f : map->capacity_grow_padding;
}

void werks_kvm_set_capacity_grow_factor(werks_kvm_dt* const map, float factor) {
    if (assigned(map)) map->capacity_grow_factor = factor;
}

void werks_kvm_set_capacity_grow_padding(werks_kvm_dt* const map, float padding) {
    if (assigned(map)) map->capacity_grow_padding = padding;
}

ssize_t werks_kvm_count_typed_items(werks_kvm_dt* const map, werks_kvm_type_dt type) {
    ssize_t result = 0;
    if (assigned(map) && type != WERKS_KVM_TYPE_NOTHING)
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] == type)
                result++;
    return result;
}

ssize_t werks_kvm_count_not_typed_items(werks_kvm_dt* const map, werks_kvm_type_dt type) {
    ssize_t result = 0;
    if (assigned(map))
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (map->types[i] != type)
                    result++;
    return result;
}

ssize_t werks_kvm_count_prefixed_items(werks_kvm_dt* const map, const char* prefix) {
    ssize_t result = 0;
    if (assigned(map))
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (starts_with(map->keys[i], prefix))
                    result++;
    return result;
}

ssize_t werks_kvm_count_not_prefixed_items(werks_kvm_dt* const map, const char* prefix) {
    ssize_t result = 0;
    if (assigned(map))
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (!starts_with(map->keys[i], prefix))
                    result++;
    return result;
}

ssize_t werks_kvm_count_suffixed_items(werks_kvm_dt* const map, const char* suffix) {
    ssize_t result = 0;
    if (assigned(map))
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (ends_with(map->keys[i], suffix))
                    result++;
    return result;
}

ssize_t werks_kvm_count_not_suffixed_items(werks_kvm_dt* const map, const char* suffix) {
    ssize_t result = 0;
    if (assigned(map))
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (!ends_with(map->keys[i], suffix))
                    result++;
    return result;
}

// Retrieves the items count (only the active ones)
ssize_t werks_kvm_get_items_count(werks_kvm_dt* const map) {
    ssize_t result = 0;
    if (assigned(map))
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                result++;
    return result;
}

bool werks_kvm_is_top(werks_kvm_dt* const map) {
    return assigned(map) && map->parent == NULL;
}

werks_kvm_dt* werks_kvm_get_parent(werks_kvm_dt* const map) {
    return assigned(map) ? map->parent : NULL;
}

bool werks_kvm_filiate_to(werks_kvm_dt* const map, werks_kvm_dt* const new_parent, const char* as_key) {
    if (assigned(map) && assigned(new_parent) && has_content(as_key)) {
        werks_kvm_dt* old_parent = assigned(map->parent) ? map->parent : NULL;
        ssize_t old_index = -1;
        if (assigned(old_parent)) {
            for (ssize_t i = 0; i < old_parent->size; i++)
                if (old_parent->values[i] == (void*)map) {
                    old_index = i;
                    break;
                }
            if (old_index == -1)
                return false;
        }
        if (!store_item(new_parent, WERKS_KVM_TYPE_KVM, as_key, map))
            return false;
        map->parent = new_parent;
        if (assigned(old_parent)) {
            ce_free(old_parent->keys[old_index]);
            erase_map_item(old_parent, old_index);
        }
        return true;
    }
    return false;
}

bool werks_kvm_is_packable(werks_kvm_dt* const map) {
    return assigned(map) && map->allow_pack && map->packable;
}

// Compacts the specified map recreating the internal arrays keeping the non-deleted entries
bool werks_kvm_pack(werks_kvm_dt* const map) {
    if (map == NULL || !map->allow_pack || !map->packable) return false;
    ssize_t old_size = map->size;
    uint8_t* old_checksums = map->checksums;
    werks_kvm_type_dt* old_types = map->types;
    char** old_keys = map->keys;
    void** old_values = map->values;
    bool old_events = map->allow_events;
    map->allow_events = false;
    ssize_t zapped_capacity = 0;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            zapped_capacity++;
    if (!setup_map_arrays(map, zapped_capacity)) {
        map->allow_events = old_events;
        ce_free(map->checksums);
        map->checksums = old_checksums;
        ce_free(map->types);
        map->types = old_types;
        ce_free(map->keys);
        map->keys = old_keys;
        ce_free(map->values);
        map->values = old_values;
        return false;
    }
    reset_map_dimensions(map, zapped_capacity);
    for (ssize_t i = 0; i < old_size; i++)
        if (old_types[i] != WERKS_KVM_TYPE_NOTHING) {
            UNUSED(store_item(map, old_types[i], old_keys[i], old_values[i]));
            ce_free(old_keys[i]);
        }
    map->packable = false;
    map->allow_events = old_events;
    free_items_arrays(old_checksums, old_types, old_keys, old_values);
    return true;
}

// Removes all the items from the map
void werks_kvm_clear(werks_kvm_dt* const map) {
    if (map == NULL || !map->allow_delete) return;
    for (ssize_t i = 0; i < map->size; i++)
        destroy_map_item(map, i);
}

// kvm clone constructor (only active items with be copied, result is "already packed")
werks_kvm_dt* werks_kvm_clone(werks_kvm_dt* const map) {
    if (map == NULL) return NULL;
    RET_MALLOC(werks_kvm_dt, {
        if (!setup_map_arrays(result, map->capacity)) {
            werks_kvm_destroy(result);
            return NULL;
        }
        reset_map_dimensions(result, map->capacity);
        set_map_flags(result, map->allow_set, map->allow_rename, map->allow_retype, map->allow_delete, map->allow_transfer, map->allow_copy, map->allow_pack, map->allow_loop, map->allow_persistence, map->allow_events);
        set_map_events(result, map->on_before_read_from_file, map->on_before_write_to_file, map->on_before_read_from_string, map->on_before_write_to_string, map->on_before_store_item, map->on_before_overwrite_item, map->on_before_rename_item, map->on_before_delete_item, map->on_before_transfer_item, map->on_before_copy_item);
        if (!werks_kvm_read_items(result, map)) {
            werks_kvm_destroy(result);
            return NULL;
        }
        result->size = map->size;
        result->eol_replacement = strdup(WERKS_KVM_MULTILINE_STRINGS_EOL);
        result->untyped_treatment = map->untyped_treatment;
        result->parent = map->parent;
        result->packable = false;
        result->component_instance = kewl_component_create(result, WERKS_KVM_TYPE_NAME);
    });
}

static bool rename_map_item(werks_kvm_dt* const map, ssize_t index, char* new_key) {
    if (map->allow_events && assigned(map->on_before_rename_item))
        if (!map->on_before_rename_item(map, map->keys[index], new_key))
            return false;
    ce_free(map->keys[index]);
    map->keys[index] = new_key;
    map->checksums[index] = crc8_string(new_key);
    return true;
}

// renames the key name with the provided new one
bool werks_kvm_rename_item(werks_kvm_dt* const map, const char* key, const char* new_key) {
    if (assigned(map) && map->allow_rename && has_content(key) && has_content(new_key)) {
        uint8_t checksum = crc8_string(key);
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING) {
                if (is_map_item(map, i, key, checksum)) {
                    char* str = strdup(new_key);
                    if (!rename_map_item(map, i, str)) {
                        ce_free(str);
                        return false;
                    }
                    return true;
                }
            }
    }
    return false;
}

bool werks_kvm_prefix_keys(werks_kvm_dt* const map, const char* prefix) {
    if (map == NULL || !map->allow_rename || !has_content(prefix)) return false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING) {
            char* str = concat_strings(prefix, map->keys[i]);
            if (!rename_map_item(map, i, str)) {
                ce_free(str);
                return false;
            }
        }
    return true;
}

bool werks_kvm_suffix_keys(werks_kvm_dt* const map, const char* suffix) {
    if (map == NULL || !map->allow_rename || !has_content(suffix)) return false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING) {
            char* str = concat_strings(map->keys[i], suffix);
            if (!rename_map_item(map, i, str)) {
                ce_free(str);
                return false;
            }
        }
    return true;
}

bool werks_kvm_unprefix_keys(werks_kvm_dt* const map, const char* prefix) {
    if (map == NULL || !map->allow_rename || !has_content(prefix)) return false;
    size_t sz = strlen(prefix);
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (starts_with(map->keys[i], prefix)) {
                char* str = drop_left(map->keys[i], sz);
                if (!rename_map_item(map, i, str)) {
                    ce_free(str);
                    return false;
                }
            }
    return true;
}

bool werks_kvm_unsuffix_keys(werks_kvm_dt* const map, const char* suffix) {
    if (map == NULL || !map->allow_rename || !has_content(suffix)) return false;
    size_t sz = strlen(suffix);
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (ends_with(map->keys[i], suffix)) {
                char* str = drop_right(map->keys[i], sz);
                if (!rename_map_item(map, i, str)) {
                    ce_free(str);
                    return false;
                }
            }
    return true;
}

char* werks_kvm_get_joined_keys(werks_kvm_dt* const map, const char* separator) {
    if (map == NULL || separator == NULL) return NULL;
    char* result = strdup(STRINGS_NOTHING);
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING) {
            result = strappend(result, map->keys[i]);
            if (i < map->size - 1)
                result = strappend(result, separator);
        }
    return result;
}

// transfers the specified origin item from the specified origin map to the specified destination map with the specified destination key (if it already exists returns false)
bool werks_kvm_transfer_item(werks_kvm_dt* const map, const char* key, werks_kvm_dt* const destination_map, const char* destination_key) {
    if (map == NULL || !map->allow_transfer || !has_content(key) ||
        destination_map == NULL || !destination_map->allow_transfer || !has_content(destination_key)) return false;
    if (map->allow_events && assigned(map->on_before_transfer_item))
        if (!map->on_before_transfer_item(map, key, destination_map, destination_key))
            return false;
    for (ssize_t i = 0; i < destination_map->size; i++)
        if (destination_map->types[i] != WERKS_KVM_TYPE_NOTHING) {
            uint8_t checksum = crc8_string(destination_key);
            if (is_map_item(destination_map, i, destination_key, checksum))
                return false;
        }
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING) {
            uint8_t checksum = crc8_string(key);
            if (is_map_item(map, i, key, checksum)) {
                result = store_item(destination_map, map->types[i], destination_key, map->values[i]);
                if (result) {
                    if (map->types[i] == WERKS_KVM_TYPE_KVM)
                        ((werks_kvm_dt*)map->values[i])->parent = destination_map;
                    ce_free(map->keys[i]);
                    erase_map_item(map, i);
                }
                break;
            }
        }
    return result;
}

// returns true if at least one typed item is transferred
bool werks_kvm_transfer_typed_items(werks_kvm_dt* const map, werks_kvm_type_dt type, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_transfer || destination_map == NULL || !destination_map->allow_transfer || type == WERKS_KVM_TYPE_NOTHING) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_transfer_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] == type) {
            if (fire_event)
                if (!map->on_before_transfer_item(map, map->keys[i], destination_map, map->keys[i]))
                    continue;
            if (store_item(destination_map, map->types[i], map->keys[i], map->values[i])) {
                result = true;
                if (map->types[i] == WERKS_KVM_TYPE_KVM)
                    ((werks_kvm_dt*)map->values[i])->parent = destination_map;
                ce_free(map->keys[i]);
                erase_map_item(map, i);
            }
        }
    return result;
}

// returns true if at least one item not matching the provided type is transferred
bool werks_kvm_transfer_not_typed_items(werks_kvm_dt* const map, werks_kvm_type_dt type, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_transfer || destination_map == NULL || !destination_map->allow_transfer || type == WERKS_KVM_TYPE_NOTHING) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_transfer_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (map->types[i] != type) {
                if (fire_event)
                    if (!map->on_before_transfer_item(map, map->keys[i], destination_map, map->keys[i]))
                        continue;
                if (store_item(destination_map, map->types[i], map->keys[i], map->values[i])) {
                    result = true;
                    if (map->types[i] == WERKS_KVM_TYPE_KVM)
                        ((werks_kvm_dt*)map->values[i])->parent = destination_map;
                    ce_free(map->keys[i]);
                    erase_map_item(map, i);
                }
            }
    return result;
}

// returns true if at least one prefixed item is transferred
bool werks_kvm_transfer_prefixed_items(werks_kvm_dt* const map, const char* prefix, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_transfer || destination_map == NULL || !destination_map->allow_transfer || !has_content(prefix)) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_transfer_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (starts_with(map->keys[i], prefix)) {
                if (fire_event)
                    if (!map->on_before_transfer_item(map, map->keys[i], destination_map, map->keys[i]))
                        continue;
                if (store_item(destination_map, map->types[i], map->keys[i], map->values[i])) {
                    result = true;
                    if (map->types[i] == WERKS_KVM_TYPE_KVM)
                        ((werks_kvm_dt*)map->values[i])->parent = destination_map;
                    ce_free(map->keys[i]);
                    erase_map_item(map, i);
                }
            }
    return result;
}

// returns true if at least one item not matching the provided prefix is transferred
bool werks_kvm_transfer_not_prefixed_items(werks_kvm_dt* const map, const char* prefix, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_transfer || destination_map == NULL || !destination_map->allow_transfer || !has_content(prefix)) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_transfer_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!starts_with(map->keys[i], prefix)) {
                if (fire_event)
                    if (!map->on_before_transfer_item(map, map->keys[i], destination_map, map->keys[i]))
                        continue;
                if (store_item(destination_map, map->types[i], map->keys[i], map->values[i])) {
                    result = true;
                    if (map->types[i] == WERKS_KVM_TYPE_KVM)
                        ((werks_kvm_dt*)map->values[i])->parent = destination_map;
                    ce_free(map->keys[i]);
                    erase_map_item(map, i);
                }
            }
    return result;
}

// returns true if at least one suffixed item is transferred
bool werks_kvm_transfer_suffixed_items(werks_kvm_dt* const map, const char* suffix, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_transfer || destination_map == NULL || !destination_map->allow_transfer || !has_content(suffix)) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_transfer_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (ends_with(map->keys[i], suffix)) {
                if (fire_event)
                    if (!map->on_before_transfer_item(map, map->keys[i], destination_map, map->keys[i]))
                        continue;
                if (store_item(destination_map, map->types[i], map->keys[i], map->values[i])) {
                    result = true;
                    if (map->types[i] == WERKS_KVM_TYPE_KVM)
                        ((werks_kvm_dt*)map->values[i])->parent = destination_map;
                    ce_free(map->keys[i]);
                    erase_map_item(map, i);
                }
            }
    return result;
}

// returns true if at least one item not matching the provided suffix is transferred
bool werks_kvm_transfer_not_suffixed_items(werks_kvm_dt* const map, const char* suffix, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_transfer || destination_map == NULL || !destination_map->allow_transfer || !has_content(suffix)) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_transfer_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!ends_with(map->keys[i], suffix)) {
                if (fire_event)
                    if (!map->on_before_transfer_item(map, map->keys[i], destination_map, map->keys[i]))
                        continue;
                if (store_item(destination_map, map->types[i], map->keys[i], map->values[i])) {
                    result = true;
                    if (map->types[i] == WERKS_KVM_TYPE_KVM)
                        ((werks_kvm_dt*)map->values[i])->parent = destination_map;
                    ce_free(map->keys[i]);
                    erase_map_item(map, i);
                }
            }
    return result;
}

// Type-specific mutator functions

#define INSERT_POINTER_INTO_MAP(ptr, typ) \
    if (!store_item(map, typ, key, ptr)) { \
        ce_free(ptr); \
        return false; \
    } \
    return true;

#define PUT_VALUE_INTO_MAP(ptr, typ) \
    if (ptr == NULL) return false; \
    *ptr = value; \
    INSERT_POINTER_INTO_MAP(ptr, typ)

// Char mutator
bool werks_kvm_set_char(werks_kvm_dt* const map, const char* key, char value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, char);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_CHAR);
}

// Signed char mutator
bool werks_kvm_set_signed_char(werks_kvm_dt* const map, const char* key, signed char value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, signed char);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_SIGNED_CHAR);
}

// Unsigned char mutator
bool werks_kvm_set_unsigned_char(werks_kvm_dt* const map, const char* key, unsigned char value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, unsigned char);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_UNSIGNED_CHAR);
}

// Signed short mutator
bool werks_kvm_set_short(werks_kvm_dt* const map, const char* key, short value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, short);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_SHORT);
}

// Unsigned short mutator
bool werks_kvm_set_unsigned_short(werks_kvm_dt* const map, const char* key, unsigned short value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, unsigned short);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_UNSIGNED_SHORT);
}

// Signed int mutator
bool werks_kvm_set_int(werks_kvm_dt* const map, const char* key, int value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, int);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_INT);
}

// Unsigned int mutator
bool werks_kvm_set_unsigned_int(werks_kvm_dt* const map, const char* key, unsigned int value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, unsigned int);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_UNSIGNED_INT);
}

// Signed long mutator
bool werks_kvm_set_long(werks_kvm_dt* const map, const char* key, long value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, long);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_LONG);
}

// Unsigned long mutator
bool werks_kvm_set_unsigned_long(werks_kvm_dt* const map, const char* key, unsigned long value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, unsigned long);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_UNSIGNED_LONG);
}

// Signed long long (C99) mutator
bool werks_kvm_set_long_long(werks_kvm_dt* const map, const char* key, long long value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, long long);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_LONG_LONG);
}

// Unsigned long long (C99) mutator
bool werks_kvm_set_unsigned_long_long(werks_kvm_dt* const map, const char* key, unsigned long long value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, unsigned long long);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_UNSIGNED_LONG_LONG);
}

// Float mutator
bool werks_kvm_set_float(werks_kvm_dt* const map, const char* key, float value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, float);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_FLOAT);
}

// Double mutator
bool werks_kvm_set_double(werks_kvm_dt* const map, const char* key, double value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, double);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_DOUBLE);
}

// Long Double mutator
bool werks_kvm_set_long_double(werks_kvm_dt* const map, const char* key, long double value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, long double);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_LONG_DOUBLE);
}

// Bool (C99) mutator
bool werks_kvm_set_bool(werks_kvm_dt* const map, const char* key, bool value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, bool);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_BOOL);
}

// String mutator
bool werks_kvm_set_string(werks_kvm_dt* const map, const char* key, const char* value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    char* ptr = strdup(value);
    if (ptr == NULL) return false;
    INSERT_POINTER_INTO_MAP(ptr, WERKS_KVM_TYPE_STRING);
}

// Buffer mutator
bool werks_kvm_set_buffer(werks_kvm_dt* const map, const char* key, const void* data, ssize_t size) {
    if (map == NULL || !map->allow_set || data == NULL || size == 0) return false;
    VAR_MALLOC(copy, werks_kvm_buffer_dt);
    if (copy == NULL) return false;
    copy->bp = ce_malloc(size);
    if (copy->bp == NULL) return false;
    memcpy(copy->bp, (void*)data, size);
    copy->sz = size;
    INSERT_POINTER_INTO_MAP(copy, WERKS_KVM_TYPE_BUFFER);
}

// Signed int8 mutator
bool werks_kvm_set_int8(werks_kvm_dt* const map, const char* key, int8_t value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, int8_t);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_INT8);
}

// Unsigned int8 mutator
bool werks_kvm_set_uint8(werks_kvm_dt* const map, const char* key, uint8_t value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, uint8_t);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_UINT8);
}

// Signed int16 mutator
bool werks_kvm_set_int16(werks_kvm_dt* const map, const char* key, int16_t value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, int16_t);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_INT16);
}

// Unsigned int16 mutator
bool werks_kvm_set_uint16(werks_kvm_dt* const map, const char* key, uint16_t value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, uint16_t);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_UINT16);
}

// Signed int32 mutator
bool werks_kvm_set_int32(werks_kvm_dt* const map, const char* key, int32_t value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, int32_t);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_INT32);
}

// Unsigned int32 mutator
bool werks_kvm_set_uint32(werks_kvm_dt* const map, const char* key, uint32_t value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, uint32_t);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_UINT32);
}

// Signed int64 mutator
bool werks_kvm_set_int64(werks_kvm_dt* const map, const char* key, int64_t value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, int64_t);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_INT64);
}

// Unsigned int64 mutator
bool werks_kvm_set_uint64(werks_kvm_dt* const map, const char* key, uint64_t value) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    VAR_MALLOC(ptr, uint64_t);
    PUT_VALUE_INTO_MAP(ptr, WERKS_KVM_TYPE_UINT64);
}

// KVM pointer initializer (not a mutator, this forces ownership of the child map)
bool werks_kvm_set_kvm(werks_kvm_dt* const map, const char* key) {
    if (map == NULL || !map->allow_set || !has_content(key)) return false;
    werks_kvm_dt* ptr = werks_kvm_create(WERKS_KVM_INITIAL_CAPACITY);
    if (ptr == NULL) return false;
    ptr->parent = map;
    INSERT_POINTER_INTO_MAP(ptr, WERKS_KVM_TYPE_KVM);
}

#undef COPY_BUFFER_INTO_MAP
#undef PUT_VALUE_INTO_MAP
#undef INSERT_POINTER_INTO_MAP

// Type-specific accessor functions

// Char accessor
char* werks_kvm_get_char(werks_kvm_dt* const map, const char* key) {
    return (char*)get_map_item_value(map, key, WERKS_KVM_TYPE_CHAR);
}

// Signed char accessor
signed char* werks_kvm_get_signed_char(werks_kvm_dt* const map, const char* key) {
    return (signed char*)get_map_item_value(map, key, WERKS_KVM_TYPE_SIGNED_CHAR);
}

// Unigned char accessor
unsigned char* werks_kvm_get_unsigned_char(werks_kvm_dt* const map, const char* key) {
    return (unsigned char*)get_map_item_value(map, key, WERKS_KVM_TYPE_UNSIGNED_CHAR);
}

// Signed short accessor
short* werks_kvm_get_short(werks_kvm_dt* const map, const char* key) {
    return (short*)get_map_item_value(map, key, WERKS_KVM_TYPE_SHORT);
}

// Unsigned short accessor
unsigned short* werks_kvm_get_unsigned_short(werks_kvm_dt* const map, const char* key) {
    return (unsigned short*)get_map_item_value(map, key, WERKS_KVM_TYPE_UNSIGNED_SHORT);
}

// Signed int accessor
int* werks_kvm_get_int(werks_kvm_dt* const map, const char* key) {
    return (int*)get_map_item_value(map, key, WERKS_KVM_TYPE_INT);
}

// Unsigned int accessor
unsigned int* werks_kvm_get_unsigned_int(werks_kvm_dt* const map, const char* key) {
    return (unsigned int*)get_map_item_value(map, key, WERKS_KVM_TYPE_UNSIGNED_INT);
}

// Signed long accessor
long* werks_kvm_get_long(werks_kvm_dt* const map, const char* key) {
    return (long*)get_map_item_value(map, key, WERKS_KVM_TYPE_LONG);
}

// Unsigned long accessor
unsigned long* werks_kvm_get_unsigned_long(werks_kvm_dt* const map, const char* key) {
    return (unsigned long*)get_map_item_value(map, key, WERKS_KVM_TYPE_UNSIGNED_LONG);
}

// Signed long long (C99) accessor
long long* werks_kvm_get_long_long(werks_kvm_dt* const map, const char* key) {
    return (long long*)get_map_item_value(map, key, WERKS_KVM_TYPE_LONG_LONG);
}

// Unsigned long long (C99) accessor
unsigned long long* werks_kvm_get_unsigned_long_long(werks_kvm_dt* const map, const char* key) {
    return (unsigned long long*)get_map_item_value(map, key, WERKS_KVM_TYPE_UNSIGNED_LONG_LONG);
}

// Float accessor
float* werks_kvm_get_float(werks_kvm_dt* const map, const char* key) {
    return (float*)get_map_item_value(map, key, WERKS_KVM_TYPE_FLOAT);
}

// Double accessor
double* werks_kvm_get_double(werks_kvm_dt* const map, const char* key) {
    return (double*)get_map_item_value(map, key, WERKS_KVM_TYPE_DOUBLE);
}

// Long Double accessor
long double* werks_kvm_get_long_double(werks_kvm_dt* const map, const char* key) {
    return (long double*)get_map_item_value(map, key, WERKS_KVM_TYPE_LONG_DOUBLE);
}

// Bool (C99) accessor
bool* werks_kvm_get_bool(werks_kvm_dt* const map, const char* key) {
    return (bool*)get_map_item_value(map, key, WERKS_KVM_TYPE_BOOL);
}

// String accessor
char* werks_kvm_get_string(werks_kvm_dt* const map, const char* key) {
    return (char*)get_map_item_value(map, key, WERKS_KVM_TYPE_STRING);
}

// Buffer pointer accessor
void* werks_kvm_get_buffer_pointer(werks_kvm_dt* const map, const char* key) {
    return ((werks_kvm_buffer_dt*)get_map_item_value(map, key, WERKS_KVM_TYPE_BUFFER))->bp;
}

// Buffer size accessor
ssize_t werks_kvm_get_buffer_size(werks_kvm_dt* const map, const char* key) {
    return ((werks_kvm_buffer_dt*)get_map_item_value(map, key, WERKS_KVM_TYPE_BUFFER))->sz;
}

// Signed int8 accessor
int8_t* werks_kvm_get_int8(werks_kvm_dt* const map, const char* key) {
    return (int8_t*)get_map_item_value(map, key, WERKS_KVM_TYPE_INT8);
}

// Unsigned int8 accessor
uint8_t* werks_kvm_get_uint8(werks_kvm_dt* const map, const char* key) {
    return (uint8_t*)get_map_item_value(map, key, WERKS_KVM_TYPE_UINT8);
}

// Signed int16 accessor
int16_t* werks_kvm_get_int16(werks_kvm_dt* const map, const char* key) {
    return (int16_t*)get_map_item_value(map, key, WERKS_KVM_TYPE_INT16);
}

// Unsigned int16 accessor
uint16_t* werks_kvm_get_uint16(werks_kvm_dt* const map, const char* key) {
    return (uint16_t*)get_map_item_value(map, key, WERKS_KVM_TYPE_UINT16);
}

// Signed int32 accessor
int32_t* werks_kvm_get_int32(werks_kvm_dt* const map, const char* key) {
    return (int32_t*)get_map_item_value(map, key, WERKS_KVM_TYPE_INT32);
}

// Unsigned int32 accessor
uint32_t* werks_kvm_get_uint32(werks_kvm_dt* const map, const char* key) {
    return (uint32_t*)get_map_item_value(map, key, WERKS_KVM_TYPE_UINT32);
}

// Signed int64 accessor
int64_t* werks_kvm_get_int64(werks_kvm_dt* const map, const char* key) {
    return (int64_t*)get_map_item_value(map, key, WERKS_KVM_TYPE_INT64);
}

// Unsigned int64 accessor
uint64_t* werks_kvm_get_uint64(werks_kvm_dt* const map, const char* key) {
    return (uint64_t*)get_map_item_value(map, key, WERKS_KVM_TYPE_UINT64);
}

// KVM pointer accessor
werks_kvm_dt* werks_kvm_get_kvm(werks_kvm_dt* const map, const char* key) {
    return (werks_kvm_dt*)get_map_item_value(map, key, WERKS_KVM_TYPE_KVM);
}

// Comparison functions

static inline bool map_keys_are_also_there(werks_kvm_dt* const map1, werks_kvm_dt* const map2) {
    for (ssize_t i = 0; i < map1->size; i++)
        if (map1->types[i] != WERKS_KVM_TYPE_NOTHING) {
            bool has_it = false;
            for (ssize_t h = 0; h < map2->size; h++)
                if (map2->types[h] != WERKS_KVM_TYPE_NOTHING)
                    if (map1->checksums[i] == map2->checksums[h])
                        if ((has_it = strcmp(map1->keys[i], map2->keys[h]) == 0))
                            break;
            if (!has_it)
                return false;
        }
    return true;
}

// Checks if the two maps have the same named keys
bool werks_kvm_same_keys(werks_kvm_dt* const map, werks_kvm_dt* const map2) {
    if (map == NULL || map2 == NULL) return false;
    return werks_kvm_get_items_count(map) == werks_kvm_get_items_count(map2)
        && map_keys_are_also_there(map, map2)
        && map_keys_are_also_there(map2, map);
}

static inline bool map_typed_keys_are_also_there(werks_kvm_dt* const map1, werks_kvm_dt* const map2) {
    for (ssize_t i = 0; i < map1->size; i++)
        if (map1->types[i] != WERKS_KVM_TYPE_NOTHING) {
            bool has_it = false;
            for (ssize_t h = 0; h < map2->size; h++)
                if (map2->types[h] != WERKS_KVM_TYPE_NOTHING)
                    if (map1->checksums[i] == map2->checksums[h])
                        if (strcmp(map1->keys[i], map2->keys[h]) == 0)
                            if ((has_it = map1->types[i] == map2->types[h]))
                                break;
            if (!has_it)
                return false;
        }
    return true;
}

// Checks if the two maps have the same named keys and with the same types
bool werks_kvm_same_typed_keys(werks_kvm_dt* const map, werks_kvm_dt* const map2) {
    if (map == NULL || map2 == NULL) return false;
    return werks_kvm_get_items_count(map) == werks_kvm_get_items_count(map2)
        && map_typed_keys_are_also_there(map, map2)
        && map_typed_keys_are_also_there(map2, map);
}

// Checks if the first map contains the keys of the second one
bool werks_kvm_contains_all_keys_of(werks_kvm_dt* const map, werks_kvm_dt* const map2) {
    return assigned(map) && assigned(map2)
        && map_keys_are_also_there(map2, map);
}

// Checks if the first map contains the keys and types of the second one
bool werks_kvm_contains_all_typed_keys_of(werks_kvm_dt* const map, werks_kvm_dt* const map2) {
    return assigned(map) && assigned(map2)
        && map_typed_keys_are_also_there(map2, map);
}

// Iteration functions

// Loop all the items
void werks_kvm_loop_items(werks_kvm_dt* const map, werks_kvm_callback_fn cb) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            cb(map->types[i], map->keys[i], map->values[i]);
}

// Loop with reference all the items
void werks_kvm_loop_items_with_reference(werks_kvm_dt* const map, werks_kvm_callback_with_reference_fn cb, void* ref) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            cb(map->types[i], map->keys[i], map->values[i], ref);
}

// Loop all the items of the provided type
void werks_kvm_loop_typed_items(werks_kvm_dt* const map, werks_kvm_type_dt t, werks_kvm_callback_fn cb) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (map->types[i] == t)
                cb(map->types[i], map->keys[i], map->values[i]);
}

// Loop with reference all the items of the provided type
void werks_kvm_loop_typed_items_with_reference(werks_kvm_dt* const map, werks_kvm_type_dt t, werks_kvm_callback_with_reference_fn cb, void* ref) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (map->types[i] == t)
                cb(map->types[i], map->keys[i], map->values[i], ref);
}

// Loop all the items thare are not of the provided type
void werks_kvm_loop_not_typed_items(werks_kvm_dt* const map, werks_kvm_type_dt t, werks_kvm_callback_fn cb) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (map->types[i] != t)
                cb(map->types[i], map->keys[i], map->values[i]);
}

// Loop with reference all the items thare are not of the provided type
void werks_kvm_loop_not_typed_items_with_reference(werks_kvm_dt* const map, werks_kvm_type_dt t, werks_kvm_callback_with_reference_fn cb, void* ref) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (map->types[i] != t)
                cb(map->types[i], map->keys[i], map->values[i], ref);
}

// Loop all the items whose keys start with the provided prefix
void werks_kvm_loop_prefixed_items(werks_kvm_dt* const map, const char* prefix, werks_kvm_callback_fn cb) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (starts_with(map->keys[i], prefix))
                cb(map->types[i], map->keys[i], map->values[i]);
}

// Loop all the items whose keys do not start with the provided prefix
void werks_kvm_loop_not_prefixed_items(werks_kvm_dt* const map, const char* prefix, werks_kvm_callback_fn cb) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!starts_with(map->keys[i], prefix))
                cb(map->types[i], map->keys[i], map->values[i]);
}

// Loop with reference all the items whose keys start with the provided prefix
void werks_kvm_loop_prefixed_items_with_reference(werks_kvm_dt* const map, const char* prefix, werks_kvm_callback_with_reference_fn cb, void* ref) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (starts_with(map->keys[i], prefix))
                cb(map->types[i], map->keys[i], map->values[i], ref);
}

// Loop with reference all the items whose do not keys start with the provided prefix
void werks_kvm_loop_not_prefixed_items_with_reference(werks_kvm_dt* const map, const char* prefix, werks_kvm_callback_with_reference_fn cb, void* ref) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!starts_with(map->keys[i], prefix))
                cb(map->types[i], map->keys[i], map->values[i], ref);
}

// Loop all the items whose keys start with the provided suffix
void werks_kvm_loop_suffixed_items(werks_kvm_dt* const map, const char* suffix, werks_kvm_callback_fn cb) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (ends_with(map->keys[i], suffix))
                cb(map->types[i], map->keys[i], map->values[i]);
}

// Loop all the items whose keys do not start with the provided suffix
void werks_kvm_loop_not_suffixed_items(werks_kvm_dt* const map, const char* suffix, werks_kvm_callback_fn cb) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!ends_with(map->keys[i], suffix))
                cb(map->types[i], map->keys[i], map->values[i]);
}

// Loop with reference all the items whose keys start with the provided suffix
void werks_kvm_loop_suffixed_items_with_reference(werks_kvm_dt* const map, const char* suffix, werks_kvm_callback_with_reference_fn cb, void* ref) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (ends_with(map->keys[i], suffix))
                cb(map->types[i], map->keys[i], map->values[i], ref);
}

// Loop with reference all the items whose keys do not start with the provided suffix
void werks_kvm_loop_not_suffixed_items_with_reference(werks_kvm_dt* const map, const char* suffix, werks_kvm_callback_with_reference_fn cb, void* ref) {
    if (map == NULL || !map->allow_loop || cb == NULL) return;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!ends_with(map->keys[i], suffix))
                cb(map->types[i], map->keys[i], map->values[i], ref);
}

// Persistence functions

static inline bool copy_map_item(werks_kvm_dt* const destination_map, const char* destination_key, werks_kvm_dt* const source_map, ssize_t source_index) {
#define SET_GOT(type) \
    if (werks_kvm_set##type(destination_map, destination_key, *werks_kvm_get##type(source_map, source_key))) \
        return true; \
    return false;
    const char* source_key = source_map->keys[source_index];
    switch (source_map->types[source_index]) {
        case WERKS_KVM_TYPE_BUFFER:
            if (werks_kvm_set_buffer(destination_map, destination_key,
                    ((werks_kvm_buffer_dt*)source_map->values[source_index])->bp,
                    ((werks_kvm_buffer_dt*)source_map->values[source_index])->sz
               ))
                return true;
            return false;
        case WERKS_KVM_TYPE_CHAR:
            SET_GOT(_char);
        case WERKS_KVM_TYPE_SIGNED_CHAR:
            SET_GOT(_signed_char);
        case WERKS_KVM_TYPE_UNSIGNED_CHAR:
            SET_GOT(_unsigned_char);
        case WERKS_KVM_TYPE_STRING:
            if (werks_kvm_set_string(destination_map, destination_key,
                    werks_kvm_get_string(source_map, source_key)
               ))
                return true;
            return false;
        case WERKS_KVM_TYPE_SHORT:
            SET_GOT(_short);
        case WERKS_KVM_TYPE_UNSIGNED_SHORT:
            SET_GOT(_unsigned_short);
        case WERKS_KVM_TYPE_INT:
            SET_GOT(_int);
        case WERKS_KVM_TYPE_UNSIGNED_INT:
            SET_GOT(_unsigned_int);
        case WERKS_KVM_TYPE_LONG:
            SET_GOT(_long);
        case WERKS_KVM_TYPE_UNSIGNED_LONG:
            SET_GOT(_unsigned_long);
        case WERKS_KVM_TYPE_LONG_LONG:
            SET_GOT(_long_long);
        case WERKS_KVM_TYPE_UNSIGNED_LONG_LONG:
            SET_GOT(_unsigned_long_long);
        case WERKS_KVM_TYPE_FLOAT:
            SET_GOT(_float);
        case WERKS_KVM_TYPE_DOUBLE:
            SET_GOT(_double);
        case WERKS_KVM_TYPE_LONG_DOUBLE:
            SET_GOT(_long_double);
        case WERKS_KVM_TYPE_BOOL:
            SET_GOT(_bool);
        case WERKS_KVM_TYPE_INT8:
            SET_GOT(_int8);
        case WERKS_KVM_TYPE_UINT8:
            SET_GOT(_uint8);
        case WERKS_KVM_TYPE_INT16:
            SET_GOT(_int16);
        case WERKS_KVM_TYPE_UINT16:
            SET_GOT(_uint16);
        case WERKS_KVM_TYPE_INT32:
            SET_GOT(_int32);
        case WERKS_KVM_TYPE_UINT32:
            SET_GOT(_uint32);
        case WERKS_KVM_TYPE_INT64:
            SET_GOT(_int64);
        case WERKS_KVM_TYPE_UINT64:
            SET_GOT(_uint64);
        case WERKS_KVM_TYPE_KVM:
            if (werks_kvm_set_kvm(destination_map, destination_key)) // NOTE: it already sets the parent
                if (werks_kvm_read_items(
                    werks_kvm_get_kvm(destination_map, destination_key),
                    werks_kvm_get_kvm(source_map, source_key)
                ))
                    return true;
            return false;
        default: return true;
    }
#undef SET_GOT
}

bool werks_kvm_read_items(werks_kvm_dt* const map, werks_kvm_dt* const source_map) {
    if (assigned(map) && assigned(source_map))
        for (ssize_t i = 0; i < source_map->size; i++)
            if (!copy_map_item(map, source_map->keys[i], source_map, i))
                return false;
    return true;
}

// copies the specified item from map to map with the specified key (if it already exists returns false)
bool werks_kvm_copy_item(werks_kvm_dt* const map, const char* key, werks_kvm_dt* const destination_map, const char* destination_key) {
    if (map == NULL || !map->allow_copy || !has_content(key) ||
        destination_map == NULL || !destination_map->allow_copy || !has_content(destination_key)) return false;
    if (map->allow_events && assigned(map->on_before_copy_item))
        if (!map->on_before_copy_item(map, key, destination_map, destination_key))
            return false;
    for (ssize_t i = 0; i < destination_map->size; i++)
        if (destination_map->types[i] != WERKS_KVM_TYPE_NOTHING) {
            uint8_t checksum = crc8_string(destination_key);
            if (is_map_item(destination_map, i, destination_key, checksum))
                return false;
        }
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING) {
            uint8_t checksum = crc8_string(key);
            if (is_map_item(map, i, key, checksum))
                return copy_map_item(destination_map, destination_key, map, i);
        }
    return false;
}

// returns true if at least one typed item is copied
bool werks_kvm_copy_typed_items(werks_kvm_dt* const map, werks_kvm_type_dt type, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_copy || destination_map == NULL || !destination_map->allow_copy || type == WERKS_KVM_TYPE_NOTHING) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_copy_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] == type) {
            if (fire_event)
                if (!map->on_before_copy_item(map, map->keys[i], destination_map, map->keys[i]))
                    continue;
            result |= copy_map_item(destination_map, map->keys[i], map, i);
        }
    return result;
}

// returns true if at least one item not of the provided type is copied
bool werks_kvm_copy_not_typed_items(werks_kvm_dt* const map, werks_kvm_type_dt type, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_copy || destination_map == NULL || !destination_map->allow_copy || type == WERKS_KVM_TYPE_NOTHING) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_copy_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (map->types[i] != type) {
                if (fire_event)
                    if (!map->on_before_copy_item(map, map->keys[i], destination_map, map->keys[i]))
                        continue;
                result |= copy_map_item(destination_map, map->keys[i], map, i);
            }
    return result;
}

// returns true if at least one item with the specified prefix is copied
bool werks_kvm_copy_prefixed_items(werks_kvm_dt* const map, const char* prefix, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_copy || destination_map == NULL || !destination_map->allow_copy || !has_content(prefix)) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_copy_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (starts_with(map->keys[i], prefix)) {
                if (fire_event)
                    if (!map->on_before_copy_item(map, map->keys[i], destination_map, map->keys[i]))
                        continue;
                result |= copy_map_item(destination_map, map->keys[i], map, i);
            }
    return result;
}

// returns true if at least one item not having the provided prefix is copied
bool werks_kvm_copy_not_prefixed_items(werks_kvm_dt* const map, const char* prefix, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_copy || destination_map == NULL || !destination_map->allow_copy || !has_content(prefix)) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_copy_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!starts_with(map->keys[i], prefix)) {
                if (fire_event)
                    if (!map->on_before_copy_item(map, map->keys[i], destination_map, map->keys[i]))
                        continue;
                result |= copy_map_item(destination_map, map->keys[i], map, i);
            }
    return result;
}

// returns true if at least one item with the specified suffix is copied
bool werks_kvm_copy_suffixed_items(werks_kvm_dt* const map, const char* suffix, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_copy || destination_map == NULL || !destination_map->allow_copy || !has_content(suffix)) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_copy_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (ends_with(map->keys[i], suffix)) {
                if (fire_event)
                    if (!map->on_before_copy_item(map, map->keys[i], destination_map, map->keys[i]))
                        continue;
                result |= copy_map_item(destination_map, map->keys[i], map, i);
            }
    return result;
}

// returns true if at least one item not having the provided suffix is copied
bool werks_kvm_copy_not_suffixed_items(werks_kvm_dt* const map, const char* suffix, werks_kvm_dt* const destination_map) {
    if (map == NULL || !map->allow_copy || destination_map == NULL || !destination_map->allow_copy || !has_content(suffix)) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_copy_item);
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!ends_with(map->keys[i], suffix)) {
                if (fire_event)
                    if (!map->on_before_copy_item(map, map->keys[i], destination_map, map->keys[i]))
                        continue;
                result |= copy_map_item(destination_map, map->keys[i], map, i);
            }
    return result;
}

// copies the items not present in the current map from the provided source map
bool werks_kvm_include_items(werks_kvm_dt* const map, werks_kvm_dt* const source_map) {
    if (map == NULL || !map->allow_copy || source_map == NULL || !source_map->allow_copy) return false;
    bool fire_event = map->allow_events && assigned(map->on_before_copy_item);
    bool result = false;
    for (ssize_t i = 0; i < source_map->size; i++)
        if (source_map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!werks_kvm_has_item(map, source_map->keys[i])) {
                if (fire_event)
                    if (!map->on_before_copy_item(source_map, source_map->keys[i], map, source_map->keys[i]))
                        continue;
                result |= copy_map_item(map, source_map->keys[i], source_map, i);
            }
    return result;
}

// removes from the current map those items whose keys are in the provided source map
bool werks_kvm_exclude_items_of(werks_kvm_dt* const map, werks_kvm_dt* const source_map) {
    if (map == NULL || !map->allow_delete || ptreq(map, source_map)) return false;
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (werks_kvm_has_item(source_map, map->keys[i]))
                result |= destroy_map_item(map, i);
    return result;
}

// removes from the current map those items whose keys and types are in the provided source map
bool werks_kvm_exclude_typed_items_of(werks_kvm_dt* const map, werks_kvm_dt* const source_map) {
    if (map == NULL || !map->allow_delete || ptreq(map, source_map)) return false;
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (werks_kvm_has_typed_item(source_map, map->keys[i], map->types[i]))
                result |= destroy_map_item(map, i);
    return result;
}

// removes from the current map every key in the first map except those in the second map
bool werks_kvm_keep_items_of(werks_kvm_dt* const map, werks_kvm_dt* const source_map) {
    if (map == NULL || !map->allow_delete || ptreq(map, source_map)) return false;
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!werks_kvm_has_item(source_map, map->keys[i]))
                result |= destroy_map_item(map, i);
    return result;
}

// removes from the current map every key in the first map except those in the second map matching types
bool werks_kvm_keep_typed_items_of(werks_kvm_dt* const map, werks_kvm_dt* const source_map) {
    if (map == NULL || !map->allow_delete || ptreq(map, source_map)) return false;
    bool result = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
            if (!werks_kvm_has_typed_item(source_map, map->keys[i], map->types[i]))
                result |= destroy_map_item(map, i);
    return result;
}

const char** werks_kvm_keys_to_array_with_size(werks_kvm_dt* const map, ssize_t* const size) {
    ssize_t count = werks_kvm_get_items_count(map);
    if (map == NULL || count == 0) return NULL;
    VAR_MALLOC_SIZE(result, const char*, count * sizeof(char*));
    if (assigned(result)) {
        ssize_t idx = 0;
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                result[idx++] = map->keys[i];
        if (assigned(size)) *size = count;
    }
    return result;
}

char** werks_kvm_get_keys_as_sorted_array_with_size(werks_kvm_dt* const map, ssize_t* const size) {
    ssize_t count = werks_kvm_get_items_count(map);
    if (map == NULL || count == 0) return NULL;
    VAR_MALLOC_SIZE(result, char*, count * sizeof(char*));
    if (assigned(result)) {
        ssize_t idx = 0;
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                result[idx++] = strdup(map->keys[i]);
        if (assigned(size)) *size = count;
        if (count > 0)
            string_array_sort(count, result);
    }
    return result;
}

const char** werks_kvm_keys_to_array_with_sentinel(werks_kvm_dt* const map) {
    ssize_t count = werks_kvm_get_items_count(map);
    if (map == NULL || count == 0) return NULL;
    VAR_MALLOC_SIZE(result, const char*, (count + 1) * sizeof(char*));
    if (assigned(result)) {
        ssize_t idx = 0;
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                result[idx++] = map->keys[i];
        result[count] = NULL;
    }
    return result;
}

char** werks_kvm_get_keys_as_sorted_array_with_sentinel(werks_kvm_dt* const map) {
    ssize_t count = werks_kvm_get_items_count(map);
    if (map == NULL || count == 0) return NULL;
    VAR_MALLOC_SIZE(result, char*, (count + 1) * sizeof(char*));
    if (assigned(result)) {
        ssize_t idx = 0;
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                result[idx++] = strdup(map->keys[i]);
        result[count] = NULL;
        if (count > 0)
            string_array_sort(count, result);
    }
    return result;
}

const char* werks_kvm_get_eol_replacement(werks_kvm_dt* const map) {
    return map == NULL ? NULL : map->eol_replacement;
}

void werks_kvm_set_eol_replacement(werks_kvm_dt* const map, const char* eol) {
    if (assigned(map) && assigned(eol)) {
        ce_free(map->eol_replacement);
        map->eol_replacement = strdup(eol);
    }
}

werks_kvm_untyped_treatment_dt werks_kvm_get_untyped_treatment(werks_kvm_dt* const map) {
    return map == NULL ? WERKS_KVM_UNTYPED_TREATMENT_DEFAULT : map->untyped_treatment;
}

void werks_kvm_set_untyped_treatment(werks_kvm_dt* map, werks_kvm_untyped_treatment_dt behaviour) {
    if (assigned(map)) map->untyped_treatment = behaviour;
}

static inline char* stringify_item_value(werks_kvm_dt* const map, int index) {
    switch (map->types[index]) {
        case WERKS_KVM_TYPE_BUFFER: return bytes_to_hex(((werks_kvm_buffer_dt*)map->values[index])->bp, ((werks_kvm_buffer_dt*)map->values[index])->sz);
        case WERKS_KVM_TYPE_CHAR: return unsigned_char_to_str(*(unsigned char*)map->values[index]); // encode as unsigned char -- you can not do a strdup(map->values[index])
        case WERKS_KVM_TYPE_SIGNED_CHAR: return signed_char_to_str(*(signed char*)map->values[index]);
        case WERKS_KVM_TYPE_UNSIGNED_CHAR: return unsigned_char_to_str(*(unsigned char*)map->values[index]);
        case WERKS_KVM_TYPE_STRING: return assigned(map->eol_replacement) ? replace_all_occurrences(map->values[index], strchar(CHARS_LF), map->eol_replacement) : strdup(map->values[index]);
        case WERKS_KVM_TYPE_SHORT: return short_to_str(*(short*)map->values[index]);
        case WERKS_KVM_TYPE_UNSIGNED_SHORT: return unsigned_short_to_str(*(unsigned short*)map->values[index]);
        case WERKS_KVM_TYPE_INT: return int_to_str(*(int*)map->values[index]);
        case WERKS_KVM_TYPE_UNSIGNED_INT: return unsigned_int_to_str(*(unsigned int*)map->values[index]);
        case WERKS_KVM_TYPE_LONG: return long_to_str(*(long*)map->values[index]);
        case WERKS_KVM_TYPE_UNSIGNED_LONG: return unsigned_long_to_str(*(unsigned long*)map->values[index]);
        case WERKS_KVM_TYPE_LONG_LONG: return long_long_to_str(*(long long*)map->values[index]);
        case WERKS_KVM_TYPE_UNSIGNED_LONG_LONG: return unsigned_long_long_to_str(*(unsigned long long*)map->values[index]);
        case WERKS_KVM_TYPE_FLOAT: return float_to_str(*(float*)map->values[index]);
        case WERKS_KVM_TYPE_DOUBLE: return double_to_str(*(double*)map->values[index]);
        case WERKS_KVM_TYPE_LONG_DOUBLE: return long_double_to_str(*(long double*)map->values[index]);
        case WERKS_KVM_TYPE_BOOL: return bool_to_str(*(bool*)map->values[index]);
        case WERKS_KVM_TYPE_INT8: return int8_to_str(*(int8_t*)map->values[index]);
        case WERKS_KVM_TYPE_UINT8: return uint8_to_str(*(uint8_t*)map->values[index]);
        case WERKS_KVM_TYPE_INT16: return int16_to_str(*(int16_t*)map->values[index]);
        case WERKS_KVM_TYPE_UINT16: return uint16_to_str(*(uint16_t*)map->values[index]);
        case WERKS_KVM_TYPE_INT32: return int32_to_str(*(int32_t*)map->values[index]);
        case WERKS_KVM_TYPE_UINT32: return uint32_to_str(*(uint32_t*)map->values[index]);
        case WERKS_KVM_TYPE_INT64: return int64_to_str(*(int64_t*)map->values[index]);
        case WERKS_KVM_TYPE_UINT64: return uint64_to_str(*(uint64_t*)map->values[index]);
        default: return strdup(STRINGS_NOTHING);
    }
}

// Renders as string the item value specified by the provided key
// NOTE: all types are rendered like in the persistence routines except for the char type which is rendered directly as string (instead of unsigned char) and the kvm type which is not rendered (an empty string is returned)
char* werks_kvm_render_value_as_string(werks_kvm_dt* const map, const char* key) {
    if (assigned(map) && assigned(key)) {
        uint8_t checksum = crc8_string(key);
        for (ssize_t i = 0; i < map->size; i++)
            if (map->types[i] != WERKS_KVM_TYPE_NOTHING)
                if (is_map_item(map, i, key, checksum))
                    return map->types[i] == WERKS_KVM_TYPE_CHAR ?
                        char_to_str(*(char*)map->values[i]) :
                        stringify_item_value(map, i);
    }
    return NULL;
}

static inline char* serialize_map_item(werks_kvm_dt* const map, int index) {
    if (map->keys[index] == NULL || map->types[index] == WERKS_KVM_TYPE_NOTHING) return NULL;
    char* val = stringify_item_value(map, index);
    char* tmp = strappend(strappend(concat_strings(
            map->keys[index], WERKS_KVM_KEYVALUE_SEPARATOR STRINGS_PARENTHESES_OPEN
        ), werks_kvm_get_type_name(map->types[index])), STRINGS_PARENTHESES_CLOSE);
    char* res = concat_strings(tmp, val);
    ce_free(tmp);
    ce_free(val);
    return res;
}

char* werks_kvm_save_to_string(werks_kvm_dt* const map) {
    if (map == NULL || !map->allow_persistence) return NULL;
    if (map->allow_events && assigned(map->on_before_write_to_string))
        if (!map->on_before_write_to_string(map))
            return NULL;
    char* result = strdup(STRINGS_NOTHING);
    char* si = NULL;
    for (ssize_t i = 0; i < map->size; i++)
        if (assigned(si = serialize_map_item(map, i))) {
            if (map->types[i] == WERKS_KVM_TYPE_KVM) {
                char* mv = werks_kvm_save_to_string(map->values[i]); // recurse
                if (assigned(mv)) {
                    si = strappend(strappend(strappend(
                        si, STRINGS_BRACKETS_OPEN WERKS_KVM_ITEMS_SEPARATOR), mv), STRINGS_BRACKETS_CLOSE);
                    ce_free(mv);
                }
            }
            result = strappend(strappend(result, si), WERKS_KVM_ITEMS_SEPARATOR);
            ce_free(si);
        }
    return result;
}

bool werks_kvm_save_to_file(werks_kvm_dt* const map, const char* filename) {
    if (map == NULL || !map->allow_persistence) return false;
    if (map->allow_events && assigned(map->on_before_write_to_file))
        if (!map->on_before_write_to_file(map, filename))
            return false;
    bool result = false;
    char* content = werks_kvm_save_to_string(map);
    if (assigned(content)) {
        result = write_file(filename, content);
        ce_free(content);
    }
    return result;
}

bool werks_kvm_append_to_file(werks_kvm_dt* const map, const char* filename) {
    if (map == NULL || !map->allow_persistence) return false;
    if (map->allow_events && assigned(map->on_before_write_to_file))
        if (!map->on_before_write_to_file(map, filename))
            return false;
    bool result = false;
    char* content = werks_kvm_save_to_string(map);
    if (assigned(content)) {
        result = append_file(filename, content);
        ce_free(content);
    }
    return result;
}

#define WERKS_KVM_TYPE_NAME_BUFFER "buffer"
#define WERKS_KVM_TYPE_NAME_CHAR "char"
#define WERKS_KVM_TYPE_NAME_SIGNED_CHAR "signed char"
#define WERKS_KVM_TYPE_NAME_UNSIGNED_CHAR "unsigned char"
#define WERKS_KVM_TYPE_NAME_STRING "string"
#define WERKS_KVM_TYPE_NAME_SHORT "short"
#define WERKS_KVM_TYPE_NAME_UNSIGNED_SHORT "unsigned short"
#define WERKS_KVM_TYPE_NAME_INT "int"
#define WERKS_KVM_TYPE_NAME_UNSIGNED_INT "unsigned int"
#define WERKS_KVM_TYPE_NAME_LONG "long"
#define WERKS_KVM_TYPE_NAME_UNSIGNED_LONG "unsigned long"
#define WERKS_KVM_TYPE_NAME_LONG_LONG "long long"
#define WERKS_KVM_TYPE_NAME_UNSIGNED_LONG_LONG "unsigned long long"
#define WERKS_KVM_TYPE_NAME_FLOAT "float"
#define WERKS_KVM_TYPE_NAME_DOUBLE "double"
#define WERKS_KVM_TYPE_NAME_LONG_DOUBLE "long double"
#define WERKS_KVM_TYPE_NAME_BOOL "bool"
#define WERKS_KVM_TYPE_NAME_INT8 "int8_t"
#define WERKS_KVM_TYPE_NAME_UINT8 "uint8_t"
#define WERKS_KVM_TYPE_NAME_INT16 "int16_t"
#define WERKS_KVM_TYPE_NAME_UINT16 "uint16_t"
#define WERKS_KVM_TYPE_NAME_INT32 "int32_t"
#define WERKS_KVM_TYPE_NAME_UINT32 "uint32_t"
#define WERKS_KVM_TYPE_NAME_INT64 "int64_t"
#define WERKS_KVM_TYPE_NAME_UINT64 "uint64_t"
#define WERKS_KVM_TYPE_NAME_KVM "kvm"

static inline bool deserialize_item_into_map(werks_kvm_dt** const map, const char* item) {
#define ON_WERKS_KVM_TYPE_VAL_DO(typ, blk) \
    if (starts_with(kv->value, typ)) { \
        const char* ser = kv->value + strlen(typ); \
        if (has_content(ser)) blk \
    }
    if (!has_content(item)) return true;
    if (strcmp(item, STRINGS_BRACKETS_CLOSE) == 0) {
        if ((*map)->parent == NULL) return false;
        *map = (*map)->parent;
        return true;
    }
    bool result = false;
    string_key_value_dt* kv = string_key_value_parse(item, WERKS_KVM_KEYVALUE_SEPARATOR);
    ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_KVM STRINGS_PARENTHESES_CLOSE, {
        const char* inherited_eol = werks_kvm_get_eol_replacement(*map);
        werks_kvm_untyped_treatment_dt inherited_behaviour = werks_kvm_get_untyped_treatment(*map);
        result = werks_kvm_set_kvm(*map, kv->key);
        *map = werks_kvm_get_kvm(*map, kv->key);
        werks_kvm_set_untyped_treatment(*map, inherited_behaviour);
        werks_kvm_set_eol_replacement(*map, inherited_eol);
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_BUFFER STRINGS_PARENTHESES_CLOSE, {
        uint8_t* bytes = NULL;
        ssize_t bytes_len = 0;
        if (hex_to_bytes(ser, &bytes, &bytes_len)) {
            result = werks_kvm_set_buffer(*map, kv->key, bytes, bytes_len);
            ce_free(bytes);
        }
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_CHAR STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_char(*map, kv->key, (char)str_to_unsigned_char_def(ser, 0)); // decode -- you can not do a ser[0]
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_SIGNED_CHAR STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_signed_char(*map, kv->key, str_to_signed_char_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_UNSIGNED_CHAR STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_unsigned_char(*map, kv->key, str_to_unsigned_char_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_STRING STRINGS_PARENTHESES_CLOSE, {
        if (assigned((*map)->eol_replacement)) {
            char* tmp = replace_all_occurrences(ser, (*map)->eol_replacement, strchar(CHARS_LF));
            result = werks_kvm_set_string(*map, kv->key, tmp);
            ce_free(tmp);
        } else
            result = werks_kvm_set_string(*map, kv->key, ser);
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_SHORT STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_short(*map, kv->key, str_to_short_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_UNSIGNED_SHORT STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_unsigned_short(*map, kv->key, str_to_unsigned_short_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_INT STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_int(*map, kv->key, str_to_int_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_UNSIGNED_INT STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_unsigned_int(*map, kv->key, str_to_unsigned_int_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_LONG STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_long(*map, kv->key, str_to_long_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_UNSIGNED_LONG STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_unsigned_long(*map, kv->key, str_to_unsigned_long_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_LONG_LONG STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_long_long(*map, kv->key, str_to_long_long_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_UNSIGNED_LONG_LONG STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_unsigned_long_long(*map, kv->key, str_to_unsigned_long_long_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_BOOL STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_bool(*map, kv->key, str_to_bool(ser));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_INT8 STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_int8(*map, kv->key, str_to_int8_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_UINT8 STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_uint8(*map, kv->key, str_to_uint8_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_INT16 STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_int16(*map, kv->key, str_to_int16_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_UINT16 STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_uint16(*map, kv->key, str_to_uint16_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_INT32 STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_int32(*map, kv->key, str_to_int32_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_UINT32 STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_uint32(*map, kv->key, str_to_uint32_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_INT64 STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_int64(*map, kv->key, str_to_int64_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_UINT64 STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_uint64(*map, kv->key, str_to_uint64_def(ser, 0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_FLOAT STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_float(*map, kv->key, str_to_float_def(ser, 0.0f));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_DOUBLE STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_double(*map, kv->key, str_to_double_def(ser, 0.0));
    }) else ON_WERKS_KVM_TYPE_VAL_DO(STRINGS_PARENTHESES_OPEN WERKS_KVM_TYPE_NAME_LONG_DOUBLE STRINGS_PARENTHESES_CLOSE, {
        result = werks_kvm_set_long_double(*map, kv->key, str_to_long_double_def(ser, 0.0));
    }) else if ((*map)->untyped_treatment == WERKS_KVM_UNTYPED_IS_STRING) {
        result = werks_kvm_set_string(*map, kv->key, kv->value);
    } else {
        result = (*map)->untyped_treatment == WERKS_KVM_UNTYPED_IS_IGNORED;
    }
    string_key_value_destroy(kv);
    return result;
#undef ON_WERKS_KVM_TYPE_VAL_DO
}

bool werks_kvm_read_from_string(werks_kvm_dt* const map, const char* props) {
#define DESERIALIZE_BLOCK {\
        ssize_t len = p - segment_start; \
        char* token = TYPE_MALLOC(char, len + 1); \
        if (!token) return false; \
        memcpy(token, segment_start, len); \
        token[len] = CHARS_NULL; \
        bool r = deserialize_item_into_map(&curr, token); \
        ce_free(token); \
        if (!r) return false; \
    }
    if (map == NULL || !map->allow_persistence || !has_content(props)) return false;
    if (map->allow_events && assigned(map->on_before_read_from_string))
        if (!map->on_before_read_from_string(map, props))
            return false;
    ssize_t sep_len = strlen(WERKS_KVM_ITEMS_SEPARATOR);
    const char* segment_start = props;
    const char* p = props;
    werks_kvm_dt* curr = map;
    while (*p) {
        if (strncmp(p, WERKS_KVM_ITEMS_SEPARATOR, sep_len) == 0) {
            DESERIALIZE_BLOCK;
            p += sep_len;
            segment_start = p;
            continue;
        }
        p++;
    }
    // handle last token after the final separator (or if no separator found)
    if (p != segment_start)
        DESERIALIZE_BLOCK;
    return true;
#undef DESERIALIZE_BLOCK
}

werks_kvm_dt* werks_kvm_load_from_string(const char* props) {
    werks_kvm_dt* result = werks_kvm_create(WERKS_KVM_INITIAL_CAPACITY);
    if (!werks_kvm_read_from_string(result, props)) {
        werks_kvm_destroy(result);
        return NULL;
    }
    return result;
}

bool werks_kvm_read_from_file(werks_kvm_dt* const map, const char* filename) {
    if (map == NULL || !map->allow_persistence || !has_content(filename)) return false;
    if (map->allow_events && assigned(map->on_before_read_from_file))
        if (!map->on_before_read_from_file(map, filename))
            return false;
    werks_kvm_dt* curr = map;
    FILE_OPERATION("r", false, {
        char* line;
        while (assigned(line = read_line_from_stream(file))) {
            bool r = deserialize_item_into_map(&curr, line);
            ce_free(line);
            if (!r) {
                fclose(file);
                return false;
            }
        }
        fclose(file);
        return true;
    });
}

werks_kvm_dt* werks_kvm_load_from_file(const char* filename) {
    werks_kvm_dt* result = werks_kvm_create(WERKS_KVM_INITIAL_CAPACITY);
    if (!werks_kvm_read_from_file(result, filename)) {
        werks_kvm_destroy(result);
        return NULL;
    }
    return result;
}

werks_kvm_on_before_read_from_file_handler_fn werks_kvm_get_on_before_read_from_file(werks_kvm_dt* const map) {
    return assigned(map) ? map->on_before_read_from_file : NULL;
}

void werks_kvm_set_on_before_read_from_file(werks_kvm_dt* const map, werks_kvm_on_before_read_from_file_handler_fn handler) {
    if (assigned(map)) map->on_before_read_from_file = handler;
}

werks_kvm_on_before_write_to_file_handler_fn werks_kvm_get_on_before_write_to_file(werks_kvm_dt* const map) {
    return assigned(map) ? map->on_before_write_to_file : NULL;
}

void werks_kvm_set_on_before_write_to_file(werks_kvm_dt* const map, werks_kvm_on_before_write_to_file_handler_fn handler) {
    if (assigned(map)) map->on_before_write_to_file = handler;
}

werks_kvm_on_before_read_from_string_handler_fn werks_kvm_get_on_before_read_from_string(werks_kvm_dt* const map) {
    return assigned(map) ? map->on_before_read_from_string : NULL;
}

void werks_kvm_set_on_before_read_from_string(werks_kvm_dt* const map, werks_kvm_on_before_read_from_string_handler_fn handler) {
    if (assigned(map)) map->on_before_read_from_string = handler;
}

werks_kvm_on_before_write_to_string_handler_fn werks_kvm_get_on_before_write_to_string(werks_kvm_dt* const map) {
    return assigned(map) ? map->on_before_write_to_string : NULL;
}

void werks_kvm_set_on_before_write_to_string(werks_kvm_dt* const map, werks_kvm_on_before_write_to_string_handler_fn handler) {
    if (assigned(map)) map->on_before_write_to_string = handler;
}

werks_kvm_on_before_store_item_handler_fn werks_kvm_get_on_before_store_item(werks_kvm_dt* const map) {
    return assigned(map) ? map->on_before_store_item : NULL;
}

void werks_kvm_set_on_before_store_item(werks_kvm_dt* const map, werks_kvm_on_before_store_item_handler_fn handler) {
    if (assigned(map)) map->on_before_store_item = handler;
}

werks_kvm_on_before_overwrite_item_handler_fn werks_kvm_get_on_before_overwrite_item(werks_kvm_dt* const map) {
    return assigned(map) ? map->on_before_overwrite_item : NULL;
}

void werks_kvm_set_on_before_overwrite_item(werks_kvm_dt* const map, werks_kvm_on_before_overwrite_item_handler_fn handler) {
    if (assigned(map)) map->on_before_overwrite_item = handler;
}

werks_kvm_on_before_rename_item_handler_fn werks_kvm_get_on_before_rename_item(werks_kvm_dt* const map) {
    return assigned(map) ? map->on_before_rename_item : NULL;
}

void werks_kvm_set_on_before_rename_item(werks_kvm_dt* const map, werks_kvm_on_before_rename_item_handler_fn handler) {
    if (assigned(map)) map->on_before_rename_item = handler;
}

werks_kvm_on_before_delete_item_handler_fn werks_kvm_get_on_before_delete_item(werks_kvm_dt* const map) {
    return assigned(map) ? map->on_before_delete_item : NULL;
}

void werks_kvm_set_on_before_delete_item(werks_kvm_dt* const map, werks_kvm_on_before_delete_item_handler_fn handler) {
    if (assigned(map)) map->on_before_delete_item = handler;
}

werks_kvm_on_before_transfer_item_handler_fn werks_kvm_get_on_before_transfer_item(werks_kvm_dt* const map) {
    return assigned(map) ? map->on_before_transfer_item : NULL;
}

void werks_kvm_set_on_before_transfer_item(werks_kvm_dt* const map, werks_kvm_on_before_transfer_item_handler_fn handler) {
    if (assigned(map)) map->on_before_transfer_item = handler;
}

werks_kvm_on_before_copy_item_handler_fn werks_kvm_get_on_before_copy_item(werks_kvm_dt* const map) {
    return assigned(map) ? map->on_before_copy_item : NULL;
}

void werks_kvm_set_on_before_copy_item(werks_kvm_dt* const map, werks_kvm_on_before_copy_item_handler_fn handler) {
    if (assigned(map)) map->on_before_copy_item = handler;
}

static inline char* serialize_map_item_as_partial_json(werks_kvm_dt* const map, int index) {
    if (map->keys[index] == NULL || map->types[index] == WERKS_KVM_TYPE_NOTHING) return NULL;
    char* val = stringify_item_value(map, index);
    char* tmp = strappend(strappend(concat_strings(
            map->keys[index], STRINGS_QUOTE STRINGS_COLON STRINGS_QUOTE STRINGS_PARENTHESES_OPEN
        ), werks_kvm_get_type_name(map->types[index])), STRINGS_PARENTHESES_CLOSE);
    char* res = quote(concat_strings(tmp, val));
    ce_free(tmp);
    ce_free(val);
    return res;
}

char* werks_kvm_export_to_json_object_string(werks_kvm_dt* const map) {
    if (map == NULL || !map->allow_persistence) return NULL;
    if (map->allow_events && assigned(map->on_before_write_to_string))
        if (!map->on_before_write_to_string(map))
            return NULL;
    char* result = strdup(STRINGS_BRACES_OPEN);
    char* si = NULL;
    bool something = false;
    for (ssize_t i = 0; i < map->size; i++)
        if (assigned(si = serialize_map_item_as_partial_json(map, i))) {
            something = true;
            if (map->types[i] == WERKS_KVM_TYPE_KVM) {
                char* mv = werks_kvm_export_to_json_object_string(map->values[i]); // recurse
                if (assigned(mv)) {
                    result = strappend(strappend(strappend(strappend(strappend(result,
                        STRINGS_QUOTE), map->keys[i]), STRINGS_QUOTE STRINGS_COLON), mv), STRINGS_COMMA);
                    ce_free(mv);
                }
            } else
                result = strappend(strappend(result, si), STRINGS_COMMA);
            ce_free(si);
        }
    if (something)
        result[strlen(result) - 1] = CHARS_BRACES_CLOSE;
    else
        result = strappend(result, STRINGS_BRACES_CLOSE);
    return result;
}

char* werks_kvm_get_type_name(const werks_kvm_type_dt t) {
    switch (t) {
        case WERKS_KVM_TYPE_BUFFER: return WERKS_KVM_TYPE_NAME_BUFFER;
        case WERKS_KVM_TYPE_CHAR: return WERKS_KVM_TYPE_NAME_CHAR;
        case WERKS_KVM_TYPE_SIGNED_CHAR: return WERKS_KVM_TYPE_NAME_SIGNED_CHAR;
        case WERKS_KVM_TYPE_UNSIGNED_CHAR: return WERKS_KVM_TYPE_NAME_UNSIGNED_CHAR;
        case WERKS_KVM_TYPE_STRING: return WERKS_KVM_TYPE_NAME_STRING;
        case WERKS_KVM_TYPE_SHORT: return WERKS_KVM_TYPE_NAME_SHORT;
        case WERKS_KVM_TYPE_UNSIGNED_SHORT: return WERKS_KVM_TYPE_NAME_UNSIGNED_SHORT;
        case WERKS_KVM_TYPE_INT: return WERKS_KVM_TYPE_NAME_INT;
        case WERKS_KVM_TYPE_UNSIGNED_INT: return WERKS_KVM_TYPE_NAME_UNSIGNED_INT;
        case WERKS_KVM_TYPE_LONG: return WERKS_KVM_TYPE_NAME_LONG;
        case WERKS_KVM_TYPE_UNSIGNED_LONG: return WERKS_KVM_TYPE_NAME_UNSIGNED_LONG;
        case WERKS_KVM_TYPE_LONG_LONG: return WERKS_KVM_TYPE_NAME_LONG_LONG;
        case WERKS_KVM_TYPE_UNSIGNED_LONG_LONG: return WERKS_KVM_TYPE_NAME_UNSIGNED_LONG_LONG;
        case WERKS_KVM_TYPE_FLOAT: return WERKS_KVM_TYPE_NAME_FLOAT;
        case WERKS_KVM_TYPE_DOUBLE: return WERKS_KVM_TYPE_NAME_DOUBLE;
        case WERKS_KVM_TYPE_LONG_DOUBLE: return WERKS_KVM_TYPE_NAME_LONG_DOUBLE;
        case WERKS_KVM_TYPE_BOOL: return WERKS_KVM_TYPE_NAME_BOOL;
        case WERKS_KVM_TYPE_INT8: return WERKS_KVM_TYPE_NAME_INT8;
        case WERKS_KVM_TYPE_UINT8: return WERKS_KVM_TYPE_NAME_UINT8;
        case WERKS_KVM_TYPE_INT16: return WERKS_KVM_TYPE_NAME_INT16;
        case WERKS_KVM_TYPE_UINT16: return WERKS_KVM_TYPE_NAME_UINT16;
        case WERKS_KVM_TYPE_INT32: return WERKS_KVM_TYPE_NAME_INT32;
        case WERKS_KVM_TYPE_UINT32: return WERKS_KVM_TYPE_NAME_UINT32;
        case WERKS_KVM_TYPE_INT64: return WERKS_KVM_TYPE_NAME_INT64;
        case WERKS_KVM_TYPE_UINT64: return WERKS_KVM_TYPE_NAME_UINT64;
        case WERKS_KVM_TYPE_KVM: return WERKS_KVM_TYPE_NAME_KVM;
        default: return STRINGS_NOTHING;
    }
}

werks_kvm_type_dt werks_kvm_get_type_by_name(const char* n) {
#define RET_WERKS_KVM_TYPE_ON(typ, nam) if (strcmp(n, nam) == 0) { return typ; }
    if (n == NULL) return false;
    while (*n && isspace((unsigned char)*n)) n++; // skip leading spaces
    RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_BUFFER, WERKS_KVM_TYPE_NAME_BUFFER)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_CHAR, WERKS_KVM_TYPE_NAME_CHAR)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_SIGNED_CHAR, WERKS_KVM_TYPE_NAME_SIGNED_CHAR)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_UNSIGNED_CHAR, WERKS_KVM_TYPE_NAME_UNSIGNED_CHAR)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_STRING, WERKS_KVM_TYPE_NAME_STRING)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_SHORT, WERKS_KVM_TYPE_NAME_SHORT)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_UNSIGNED_SHORT, WERKS_KVM_TYPE_NAME_UNSIGNED_SHORT)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_INT, WERKS_KVM_TYPE_NAME_INT)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_UNSIGNED_INT, WERKS_KVM_TYPE_NAME_UNSIGNED_INT)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_LONG, WERKS_KVM_TYPE_NAME_LONG)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_UNSIGNED_LONG, WERKS_KVM_TYPE_NAME_UNSIGNED_LONG)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_LONG_LONG, WERKS_KVM_TYPE_NAME_LONG_LONG)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_UNSIGNED_LONG_LONG, WERKS_KVM_TYPE_NAME_UNSIGNED_LONG_LONG)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_FLOAT, WERKS_KVM_TYPE_NAME_FLOAT)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_DOUBLE, WERKS_KVM_TYPE_NAME_DOUBLE)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_LONG_DOUBLE, WERKS_KVM_TYPE_NAME_LONG_DOUBLE)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_BOOL, WERKS_KVM_TYPE_NAME_BOOL)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_INT8, WERKS_KVM_TYPE_NAME_INT8)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_UINT8, WERKS_KVM_TYPE_NAME_UINT8)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_INT16, WERKS_KVM_TYPE_NAME_INT16)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_UINT16, WERKS_KVM_TYPE_NAME_UINT16)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_INT32, WERKS_KVM_TYPE_NAME_INT32)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_UINT32, WERKS_KVM_TYPE_NAME_UINT32)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_INT64, WERKS_KVM_TYPE_NAME_INT64)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_UINT64, WERKS_KVM_TYPE_NAME_UINT64)
    else RET_WERKS_KVM_TYPE_ON(WERKS_KVM_TYPE_KVM, WERKS_KVM_TYPE_NAME_KVM);
    return WERKS_KVM_TYPE_NOTHING;
#undef RET_WERKS_KVM_TYPE_ON
}

#undef WERKS_KVM_TYPE_NAME_BUFFER
#undef WERKS_KVM_TYPE_NAME_CHAR
#undef WERKS_KVM_TYPE_NAME_SIGNED_CHAR
#undef WERKS_KVM_TYPE_NAME_UNSIGNED_CHAR
#undef WERKS_KVM_TYPE_NAME_STRING
#undef WERKS_KVM_TYPE_NAME_SHORT
#undef WERKS_KVM_TYPE_NAME_UNSIGNED_SHORT
#undef WERKS_KVM_TYPE_NAME_INT
#undef WERKS_KVM_TYPE_NAME_UNSIGNED_INT
#undef WERKS_KVM_TYPE_NAME_LONG
#undef WERKS_KVM_TYPE_NAME_UNSIGNED_LONG
#undef WERKS_KVM_TYPE_NAME_LONG_LONG
#undef WERKS_KVM_TYPE_NAME_UNSIGNED_LONG_LONG
#undef WERKS_KVM_TYPE_NAME_FLOAT
#undef WERKS_KVM_TYPE_NAME_DOUBLE
#undef WERKS_KVM_TYPE_NAME_LONG_DOUBLE
#undef WERKS_KVM_TYPE_NAME_BOOL
#undef WERKS_KVM_TYPE_NAME_INT8
#undef WERKS_KVM_TYPE_NAME_UINT8
#undef WERKS_KVM_TYPE_NAME_INT16
#undef WERKS_KVM_TYPE_NAME_UINT16
#undef WERKS_KVM_TYPE_NAME_INT32
#undef WERKS_KVM_TYPE_NAME_UINT32
#undef WERKS_KVM_TYPE_NAME_INT64
#undef WERKS_KVM_TYPE_NAME_UINT64
#undef WERKS_KVM_TYPE_NAME_KVM

