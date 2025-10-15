/**
 * werks_strhashgroup: string hash group
 */

#include "werks_strhashgroup.h"

struct WERKS_STRHASHGROUP_ALIGNMENT werks_strhashgroup_dt {
    kewl_component_dt* component_instance;
    // collection
    union {
        kewl_strhashbag_dt* bag;
        kewl_strhashset_dt* set;
    } string_collection;
    // events
    werks_strhashgroup_on_before_insertion_handler_fn on_before_insertion;
    werks_strhashgroup_on_before_deletion_handler_fn on_before_deletion;
    // flags
    bool accepts_duplicates;
};

werks_strhashgroup_dt* werks_strhashgroup_create(bool accept_duplicates) {
    RET_MALLOC(werks_strhashgroup_dt, {
        if ((result->accepts_duplicates = accept_duplicates)) {
            result->string_collection.bag = kewl_strhashbag_make();
        } else
            result->string_collection.set = kewl_strhashset_make();
        result->on_before_insertion = NULL;
        result->on_before_deletion = NULL;
        result->component_instance = kewl_component_create(result, WERKS_STRHASHGROUP_TYPE_NAME);
    });
}

const kewl_component_dt* werks_strhashgroup_get_component(werks_strhashgroup_dt* const group) {
    return group == NULL ? NULL : group->component_instance;
}

bool werks_strhashgroup_has(werks_strhashgroup_dt* const group, const char* token) {
    if (assigned(group)) {
        if (group->accepts_duplicates) {
            return kewl_strhashbag_has(group->string_collection.bag, token);
        } else
            return kewl_strhashset_has(group->string_collection.set, token);
    }
    return false;
}

werks_strhashgroup_on_before_insertion_handler_fn werks_strhashgroup_get_on_before_insertion(werks_strhashgroup_dt* const group) {
    return assigned(group) ? group->on_before_insertion : NULL;
}

void werks_strhashgroup_set_on_before_insertion(werks_strhashgroup_dt* const group, werks_strhashgroup_on_before_insertion_handler_fn handler) {
    if (assigned(group)) group->on_before_insertion = handler;
}

werks_strhashgroup_on_before_deletion_handler_fn werks_strhashgroup_get_on_before_deletion(werks_strhashgroup_dt* const group) {
    return assigned(group) ? group->on_before_deletion : NULL;
}

void werks_strhashgroup_set_on_before_deletion(werks_strhashgroup_dt* const group, werks_strhashgroup_on_before_deletion_handler_fn handler) {
    if (assigned(group)) group->on_before_deletion = handler;
}

bool werks_strhashgroup_add(werks_strhashgroup_dt* const group, const char* token) {
    if (assigned(group)) {
        if (assigned(group->on_before_insertion))
            if (!group->on_before_insertion(group, token))
                return false;
        if (group->accepts_duplicates) {
            return kewl_strhashbag_add(group->string_collection.bag, token);
        } else
            return kewl_strhashset_add(group->string_collection.set, token);
    }
    return false;
}

bool werks_strhashgroup_remove_once(werks_strhashgroup_dt* const group, const char* token) {
    if (assigned(group)) {
        if (assigned(group->on_before_deletion))
            if (!group->on_before_deletion(group, token))
                return false;
        if (group->accepts_duplicates) {
            return kewl_strhashbag_remove_once(group->string_collection.bag, token);
        } else
            return kewl_strhashset_remove(group->string_collection.set, token);
    }
    return false;
}

bool werks_strhashgroup_remove_every(werks_strhashgroup_dt* const group, const char* token) {
    if (assigned(group)) {
        if (assigned(group->on_before_deletion))
            if (!group->on_before_deletion(group, token))
                return false;
        if (group->accepts_duplicates) {
            return kewl_strhashbag_remove_every(group->string_collection.bag, token);
        } else
            return kewl_strhashset_remove(group->string_collection.set, token);
    }
    return false;
}

ssize_t werks_strhashgroup_count_total(werks_strhashgroup_dt* const group) {
    if (assigned(group)) {
        if (group->accepts_duplicates) {
            return kewl_strhashbag_count_total(group->string_collection.bag);
        } else
            return kewl_strhashset_count(group->string_collection.set);
    }
    return -1;
}

ssize_t werks_strhashgroup_count_every(werks_strhashgroup_dt* const group, const char* token) {
    if (assigned(group)) {
        if (group->accepts_duplicates) {
            return kewl_strhashbag_count_every(group->string_collection.bag, token);
        } else
            return kewl_strhashset_has(group->string_collection.set, token) ? 1 : 0;
    }
    return -1;
}

static void werks_strhashgroup_insertion_callback(const char* str, const void* ref) {
    UNUSED(werks_strhashgroup_add((werks_strhashgroup_dt*)ref, str));
}

bool werks_strhashgroup_read_from_string(werks_strhashgroup_dt* const group, const char* data, const char* separator) {
    return assigned(group) && has_content(data) && has_content(separator) &&
        parse_separated_values_with_reference(data, separator, werks_strhashgroup_insertion_callback, group);
}

char* werks_strhashgroup_write_to_string(werks_strhashgroup_dt* const group, char separator) {
    if (assigned(group)) {
        if (group->accepts_duplicates) {
            return kewl_strhashbag_stringify(group->string_collection.bag, separator);
        } else
            return kewl_strhashset_stringify(group->string_collection.set, separator);
    }
    return NULL;
}

void werks_strhashgroup_clear(werks_strhashgroup_dt* const group) {
    if (assigned(group)) {
        if (group->accepts_duplicates) {
            kewl_strhashbag_clear(group->string_collection.bag);
        } else
            kewl_strhashset_clear(group->string_collection.set);
    }
}

void werks_strhashgroup_destroy(werks_strhashgroup_dt* const group) {
    if (assigned(group)) {
        if (group->accepts_duplicates) {
            if (assigned(group->string_collection.bag)) {
                kewl_strhashbag_destroy(group->string_collection.bag);
                group->string_collection.bag = NULL;
            }
        } else
            if (assigned(group->string_collection.set)) {
                kewl_strhashset_destroy(group->string_collection.set);
                group->string_collection.set = NULL;
            }
        kewl_component_destroy(group->component_instance);
        group->component_instance = NULL;
        ce_free(group);
    }
}

