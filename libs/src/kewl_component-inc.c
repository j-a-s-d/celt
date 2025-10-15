/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_component-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

struct KEWL_COMPONENT_ALIGNMENT kewl_component_dt {
    // user-defined
    const kewl_component_dt* owner_component;
    const void* type_instance;
    char* type_name;
    void* tag_pointer;
    // auto-generated
    size_t instance_number;
    char* instance_name;
};

unit_container(component_, {
    size_t instance_counter;
}) = {0};

static inline char* make_instance_name(const char* type_name, size_t instance_number) {
    ssize_t size = measure_string_format("%s%lu", type_name, instance_number) + 1;
    STR_MALLOC(result, size);
    if (assigned(result)) {
        UNUSED(snprintf(result, size, "%s%lu", type_name, instance_number));
    } else
        result = strdup(STRINGS_NOTHING);
    return result;
}

kewl_component_dt* kewl_component_create(void* type_instance, const char* type_name) {
    RET_MALLOC(kewl_component_dt, {
        result->owner_component = NULL;
        result->type_instance = type_instance;
        result->type_name = strdup(assigned(type_name) ? type_name : STRINGS_NOTHING);
        result->instance_number = ++component_.instance_counter;
        result->instance_name = make_instance_name(result->type_name, result->instance_number);
        result->tag_pointer = NULL;
    });
}

void kewl_component_destroy(kewl_component_dt* const component) {
    if (component == NULL) return;
    ce_free(component->instance_name);
    ce_free(component->type_name);
    ce_free(component);
}

const kewl_component_dt* kewl_component_get_owner(kewl_component_dt* const component) {
    return component == NULL ? NULL : component->owner_component;
}

void kewl_component_set_owner(kewl_component_dt* const component, const kewl_component_dt* owner_component) {
    if (assigned(component))
        component->owner_component = owner_component;
}

void* kewl_component_get_tag(kewl_component_dt* const component) {
    return component == NULL ? NULL : component->tag_pointer;
}

void kewl_component_set_tag(kewl_component_dt* component, void* tag_pointer) {
    if (assigned(component))
        component->tag_pointer = tag_pointer;
}

const char* kewl_component_get_type_name(kewl_component_dt* component) {
    return component == NULL ? NULL : component->type_name;
}

const void* kewl_component_get_type_instance(kewl_component_dt* component) {
    return component == NULL ? NULL : component->type_instance;
}

size_t kewl_component_get_instance_number(kewl_component_dt* component) {
    return component == NULL ? 0 : component->instance_number;
}

const char* kewl_component_get_instance_name(kewl_component_dt* component) {
    return component == NULL ? NULL : component->instance_name;
}

