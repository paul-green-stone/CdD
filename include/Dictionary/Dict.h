#ifndef OPEN_ADDRESSED_TABLE_H
#define OPEN_ADDRESSED_TABLE_H

/* ================================================================ */

typedef struct dictionary* Dict_t;

/* ================================ */

extern Dict_t Dict_new(size_t size, void (*print)(void* data), void (*destroy)(void* data));

/* ================================================================ */

extern ssize_t Dict_add(Dict_t table, const char* key, void* data);

/* ================================================================ */

extern ssize_t Dict_size(const Dict_t table);

/* ================================================================ */

extern void* Dict_get(Dict_t table, const char* key);

/* ================================================================ */

extern void Dict_print(const Dict_t table);

/* ================================================================ */

extern void Dict_destroy(Dict_t table);

/* ================================================================ */

extern float Dict_loadF(const Dict_t table);

/* ================================================================ */

extern void* Dict_remove(Dict_t table, const char* key);

/* ================================================================ */

#endif /* OPEN_ADDRESSED_TABLE_H */
