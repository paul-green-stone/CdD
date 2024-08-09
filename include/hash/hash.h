#ifndef HASH_H
#define HASH_H

#include "../../dictionary.h"

/* ================================================================ */

extern size_t hash_pjw(const char* key, size_t mod);

/* ================================================================ */

extern size_t probe_hash(size_t hash_index, size_t mod);

/* ================================================================ */

#endif /* HASH_H */
