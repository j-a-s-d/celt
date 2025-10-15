/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_component-inc.h
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

#pragma once

#ifndef KEWL
#warning This is intended to be part of the KeWL C Library.
#endif

/*
    This is a simple container for some common basic metadata.
    Also custom metadata can be placed via a custom tag pointer.
*/

#ifndef KEWL_COMPONENT_ALIGNMENT
    #define KEWL_COMPONENT_ALIGNMENT MEH_DEFAULT_ALIGNMENT
#endif

typedef struct kewl_component_dt kewl_component_dt;

kewl_component_dt* kewl_component_create(void* type_instance, const char* type_name);
void kewl_component_destroy(kewl_component_dt* component);

const kewl_component_dt* kewl_component_get_owner(kewl_component_dt* component);
void kewl_component_set_owner(kewl_component_dt* component, const kewl_component_dt* owner_component);

void* kewl_component_get_tag(kewl_component_dt* component);
void kewl_component_set_tag(kewl_component_dt* component, void* tag_pointer);

const char* kewl_component_get_type_name(kewl_component_dt* component);
const void* kewl_component_get_type_instance(kewl_component_dt* component);

size_t kewl_component_get_instance_number(kewl_component_dt* component);
const char* kewl_component_get_instance_name(kewl_component_dt* component);

