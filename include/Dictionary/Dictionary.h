#ifndef CDD_INTERFACE_H
#define CDD_INTERFACE_H

/* ================================================================ */

typedef struct dictionary CdD_Dict;

/* ================================ */

extern CdD_Dict* Dict_new(size_t size, void (*print)(void* value), void (*destroy)(void* value), int (*save_data)(void* data, FILE* file), int (*load_data)(void** data, FILE* file));

/* ================================================================ */

extern ssize_t Dict_insert(const char* key, void* value, CdD_Dict* dict);

/* ================================================================ */

extern ssize_t Dict_size(const CdD_Dict* dict);

/* ================================================================ */

extern ssize_t Dict_capacity(const CdD_Dict* dict);

/* ================================================================ */

extern void* Dict_lookup(const char* key, CdD_Dict* dict);

/* ================================================================ */

extern void Dict_print(const CdD_Dict* dict);

/* ================================================================ */

extern void Dict_destroy(CdD_Dict* dict);

/* ================================================================ */

extern float Dict_loadF(const CdD_Dict* dict);

/* ================================================================ */

extern void* Dict_remove(const char* key, CdD_Dict* dict);

/* ================================================================ */

extern int Dict_save(const CdD_Dict* dict, const char* filename);

/* ================================================================ */

extern CdD_Dict* Dict_load(const char* filename, void (*print)(void* value), void (*destroy)(void* value), int (*save_data)(void* data, FILE* file), int (*load_data)(void** data, FILE* file));

/* ================================================================ */

#endif /* CDD_INTERFACE_H */
