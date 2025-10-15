/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_strhashset-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

typedef struct KEWL_STRHASHSET_ALIGNMENT kewl_strhashset_node_dt {
    struct kewl_strhashset_node_dt* next;
    char* token;
    uint8_t checksum;
} kewl_strhashset_node_dt;

unit_container(strhashset_, {
    kewl_strhashset_hash_fn hash;
}) = {NULL};

#define DO_HASH(tkn) strhashset_.hash(tkn, KEWL_STRHASHSET_SIZE)
#define VAR_HASH(var, tkn) KEWL_STRHASHSET_TYPE var = DO_HASH(tkn)
#define EACH_NODE(hs, idx, node, blk) \
    LOOP_VAR_TIMES(idx, KEWL_STRHASHSET_SIZE) { \
        kewl_strhashset_node_dt* node = hs[idx]; \
        blk \
    }

kewl_strhashset_dt* kewl_strhashset_create(kewl_strhashset_hash_fn hash_function) {
    if (hash_function == NULL) return NULL;
    strhashset_.hash = hash_function;
    RET_CALLOC(kewl_strhashset_dt, KEWL_STRHASHSET_SIZE, EMPTY_BLOCK);
}

static inline bool strhashset_is(kewl_strhashset_node_dt* node, uint8_t checksum, const char* token) {
    return node->checksum == checksum && strcmp(node->token, token) == 0;
}

static inline kewl_strhashset_node_dt* strhashset_fetch(kewl_strhashset_node_dt* node, const char* token) {
    uint8_t checksum = crc8_string(token);
    while (assigned(node)) {
        if (strhashset_is(node, checksum, token))
            return node;
        node = node->next;
    }
    return NULL;
}

bool kewl_strhashset_has(kewl_strhashset_dt* const hs, const char* token) {
    return assigned(hs) && assigned(token) &&
        assigned(strhashset_fetch(hs[DO_HASH(token)], token));
}

bool kewl_strhashset_remove(kewl_strhashset_dt* const hs, const char* token) {
    if (assigned(hs) && assigned(token)) {
        VAR_HASH(h, token);
        kewl_strhashset_node_dt* node = hs[h];
        kewl_strhashset_node_dt* last = NULL;
        uint8_t checksum = crc8_string(token);
        while (assigned(node)) {
            if (strhashset_is(node, checksum, token)) {
                if (last == NULL) {
                    kewl_strhashset_node_dt* tmp = hs[h]->next;
                    ce_free(hs[h]->token);
                    ce_free(hs[h]);
                    hs[h] = tmp;
                } else {
                    last->next = node->next;
                    ce_free(node->token);
                    ce_free(node);
                }
                return true;
            }
            last = node;
            node = node->next;
        }
    }
    return false;
}

bool kewl_strhashset_add(kewl_strhashset_dt* const hs, const char* token) {
    if (hs == NULL || token == NULL)
        return false;
    VAR_HASH(h, token);
    if (assigned(strhashset_fetch(hs[h], token)))
        return false;
    VAR_MALLOC(new_node, kewl_strhashset_node_dt);
    if (new_node == NULL)
        return false;
    new_node->token = strdup(token);
    new_node->checksum = crc8_string(token);
    if (new_node->token == NULL)
        return false;
    new_node->next = hs[h];
    hs[h] = new_node;
    return true;
}

ssize_t kewl_strhashset_count(kewl_strhashset_dt* const hs) {
    ssize_t result = 0;
    if (assigned(hs)) {
        EACH_NODE(hs, i, node, {
            while (assigned(node)) {
                result++;
                node = node->next;
            }
        });
    }
    return result;
}

char* kewl_strhashset_stringify(kewl_strhashset_dt* const hs, char separator) {
    char* result = NULL;
    if (assigned(hs)) {
        ssize_t count = 0;
        ssize_t len = 0;
        EACH_NODE(hs, i, node, {
            while (assigned(node)) {
                if (assigned(node->token)) {
                    count++;
                    len += strlen(node->token);
                }
                node = node->next;
            }
        });
        if (count > 0 && len > 0) {
            ssize_t last = len + count - 1;
            // NOTE: here keep the + 2 since the separator is 2 bytes long, so the
            // last write needs an extra byte (besides we place a NULL in the end)
            // otherwise valgrind will mark this as an error (an invalid write).
            result = TYPE_MALLOC(char, last + 2);
            if (assigned(result)) {
                const char* sep = strchar(separator);
                result[0] = CHARS_NULL;
                EACH_NODE(hs, i, node, {
                    while (assigned(node)) {
                        if (assigned(node->token))
                            UNUSED(strcat(strcat(result, node->token), sep));
                        node = node->next;
                    }
                });
                result[last] = CHARS_NULL;
            }
        } else
            result = strdup(STRINGS_NOTHING);
    }
    return result;
}

void kewl_strhashset_clear(kewl_strhashset_dt* const hs) {
    if (assigned(hs)) {
        EACH_NODE(hs, i, node, {
            while (assigned(node)) {
                kewl_strhashset_node_dt* tmp = node;
                node = node->next;
                ce_free(tmp->token);
                ce_free(tmp);
            }
            hs[i] = NULL;
        });
    }
}

void kewl_strhashset_destroy(kewl_strhashset_dt* const hs) {
    if (assigned(hs)) {
        kewl_strhashset_clear(hs);
        ce_free(hs);
    }
}

#undef EACH_NODE
#undef VAR_HASH
#undef DO_HASH

