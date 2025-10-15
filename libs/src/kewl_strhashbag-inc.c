/**
 * C eXTRA LiBRARiES & TOOLS
 * Library: KeWL
 * File: kewl_strhashbag-inc.c
 * Copyright (c) 2025 Javier Santo Domingo (j-a-s-d@coderesearchlabs.com)
 */

typedef struct KEWL_STRHASHBAG_ALIGNMENT kewl_strhashbag_node_dt {
    struct kewl_strhashbag_node_dt* next;
    char* token;
    uint8_t checksum;
} kewl_strhashbag_node_dt;

unit_container(strhashbag_, {
    kewl_strhashbag_hash_fn hash;
}) = {NULL};

#define DO_HASH(tkn) strhashbag_.hash(tkn, KEWL_STRHASHBAG_SIZE)
#define VAR_HASH(var, tkn) KEWL_STRHASHBAG_TYPE var = DO_HASH(tkn)
#define EACH_NODE(hb, idx, node, blk) \
    LOOP_VAR_TIMES(idx, KEWL_STRHASHBAG_SIZE) { \
        kewl_strhashbag_node_dt* node = hb[idx]; \
        blk \
    }

kewl_strhashbag_dt* kewl_strhashbag_create(kewl_strhashbag_hash_fn hash_function) {
    if (hash_function == NULL) return NULL;
    strhashbag_.hash = hash_function;
    RET_CALLOC(kewl_strhashbag_dt, KEWL_STRHASHBAG_SIZE, EMPTY_BLOCK);
}

static inline bool strhashbag_is(kewl_strhashbag_node_dt* node, uint8_t checksum, const char* token) {
    return node->checksum == checksum && strcmp(node->token, token) == 0;
}

static inline kewl_strhashbag_node_dt* strhashbag_fetch(kewl_strhashbag_node_dt* node, const char* token) {
    uint8_t checksum = crc8_string(token);
    while (assigned(node)) {
        if (strhashbag_is(node, checksum, token))
            return node;
        node = node->next;
    }
    return NULL;
}

bool kewl_strhashbag_has(kewl_strhashbag_dt* const hb, const char* token) {
    return assigned(hb) && assigned(token) &&
        assigned(strhashbag_fetch(hb[DO_HASH(token)], token));
}

bool kewl_strhashbag_remove_once(kewl_strhashbag_dt* const hb, const char* token) {
    if (assigned(hb) && assigned(token)) {
        VAR_HASH(h, token);
        kewl_strhashbag_node_dt* node = hb[h];
        kewl_strhashbag_node_dt* last = NULL;
        uint8_t checksum = crc8_string(token);
        while (assigned(node)) {
            if (strhashbag_is(node, checksum, token)) {
                if (last == NULL) {
                    kewl_strhashbag_node_dt* tmp = hb[h]->next;
                    ce_free(hb[h]->token);
                    ce_free(hb[h]);
                    hb[h] = tmp;
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

bool kewl_strhashbag_remove_every(kewl_strhashbag_dt* const hb, const char* token) {
    bool result = false;
    if (assigned(hb) && assigned(token)) {
        VAR_HASH(h, token);
        kewl_strhashbag_node_dt* node = hb[h];
        kewl_strhashbag_node_dt* last = NULL;
        uint8_t checksum = crc8_string(token);
        while (assigned(node)) {
            if (strhashbag_is(node, checksum, token)) {
                if (last == NULL) {
                    kewl_strhashbag_node_dt* tmp = hb[h]->next;
                    ce_free(hb[h]->token);
                    ce_free(hb[h]);
                    hb[h] = tmp;
                    node = tmp;
                } else {
                    last->next = node->next;
                    ce_free(node->token);
                    ce_free(node);
                    node = last->next;
                }
                result = true;
            } else {
                last = node;
                node = node->next;
            }
        }
    }
    return result;
}

bool kewl_strhashbag_add(kewl_strhashbag_dt* const hb, const char* token) {
    if (hb == NULL || token == NULL)
        return false;
    VAR_HASH(h, token);
    VAR_MALLOC(new_node, kewl_strhashbag_node_dt);
    if (new_node == NULL)
        return false;
    new_node->token = strdup(token);
    new_node->checksum = crc8_string(token);
    if (new_node->token == NULL)
        return false;
    new_node->next = hb[h];
    hb[h] = new_node;
    return true;
}

ssize_t kewl_strhashbag_count_total(kewl_strhashbag_dt* const hb) {
    ssize_t result = 0;
    if (assigned(hb)) {
        EACH_NODE(hb, i, node, {
            while (assigned(node)) {
                result++;
                node = node->next;
            }
        });
    }
    return result;
}

ssize_t kewl_strhashbag_count_every(kewl_strhashbag_dt* const hb, const char* token) {
    ssize_t result = 0;
    if (assigned(hb)) {
        uint8_t checksum = crc8_string(token);
        EACH_NODE(hb, i, node, {
            while (assigned(node)) {
                if (strhashbag_is(node, checksum, token))
                    result++;
                node = node->next;
            }
        });
    }
    return result;
}

char* kewl_strhashbag_stringify(kewl_strhashbag_dt* const hb, char separator) {
    char* result = NULL;
    if (assigned(hb)) {
        ssize_t count = 0;
        ssize_t len = 0;
        EACH_NODE(hb, i, node, {
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
                EACH_NODE(hb, i, node, {
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

void kewl_strhashbag_clear(kewl_strhashbag_dt* const hb) {
    if (assigned(hb)) {
        EACH_NODE(hb, i, node, {
            while (assigned(node)) {
                kewl_strhashbag_node_dt* tmp = node;
                node = node->next;
                ce_free(tmp->token);
                ce_free(tmp);
            }
            hb[i] = NULL;
        });
    }
}

void kewl_strhashbag_destroy(kewl_strhashbag_dt* const hb) {
    if (assigned(hb)) {
        kewl_strhashbag_clear(hb);
        ce_free(hb);
    }
}

#undef EACH_NODE
#undef VAR_HASH
#undef DO_HASH

