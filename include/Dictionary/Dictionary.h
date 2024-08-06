#ifndef DICTIONARY_INTERFACE_H
#define DICTIONARY_INTERFACE_H

/* ================================================================ */

typedef struct dictionary* Dict_t;

/* ================================ */

extern Dict_t Dict_new(size_t size, void (*print)(void* value), void (*destroy)(void* value), int (*save_data)(void* data, FILE* file), int (*load_data)(void** data, FILE* file));

/* ================================================================ */

extern ssize_t Dict_insert(const char* key, void* value, Dict_t dict);

/* ================================================================ */

extern ssize_t Dict_size(const Dict_t dict);

/* ================================================================ */

extern ssize_t Dict_capacity(const Dict_t dict);

/* ================================================================ */

extern void* Dict_lookup(const char* key, Dict_t dict);

/* ================================================================ */

extern void Dict_print(const Dict_t dict);

/* ================================================================ */

extern void Dict_destroy(Dict_t dict);

/* ================================================================ */

extern float Dict_loadF(const Dict_t dict);

/* ================================================================ */

extern void* Dict_remove(const char* key, Dict_t dict);

/* ================================================================ */

extern int Dict_save(const Dict_t dict, const char* filename);

/* ================================================================ */

extern Dict_t Dict_load(const char* filename, void (*print)(void* value), void (*destroy)(void* value), int (*save_data)(void* data, FILE* file), int (*load_data)(void** data, FILE* file));

/* ================================================================ */

#endif /* DICTIONARY_INTERFACE_H */
