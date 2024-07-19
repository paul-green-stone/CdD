#ifndef OPEN_ADDRESSED_TABLE_H
#define OPEN_ADDRESSED_TABLE_H

/* ================================================================ */

typedef struct oatable* OAtable_t;

/* ================================ */

extern OAtable_t OAtable_new(size_t size, size_t (*hash)(const char* key, size_t mod), size_t (*phash)(const char* key, size_t mod), void (*print)(void* data));

/* ================================================================ */

extern ssize_t OAtable_add(OAtable_t table, const char* key, void* data);

/* ================================================================ */

extern ssize_t OAtable_size(const OAtable_t table);

/* ================================================================ */

extern void* OAtable_get(OAtable_t table, const char* key);

/* ================================================================ */

extern void OAtable_print(const OAtable_t table);

/* ================================================================ */

extern void OAtable_destroy(OAtable_t table);

#endif /* OPEN_ADDRESSED_TABLE_H */
