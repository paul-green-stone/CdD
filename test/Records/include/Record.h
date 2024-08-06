#ifndef RECORD_H
#define RECORD_H

#include "../Records.h"

/* ================================================================ */

typedef struct record {

    char* id;
    char* name;
    unsigned int access_level;
} Record;

/* ================================ */

enum ACCESS_LEVELS {
    M,
    M1,
    M2,
    B,
    B1,
    B2,
    C,
    X
};

/* ================================================================ */
/* ========================== Interface =========================== */
/* ================================================================ */

extern Record* Record_new(const char* ID, const char* name, unsigned int level);

/* ================================================================ */

extern void Record_destroy(Record* record);

/* ================================================================ */

extern int Record_save(Record* record, FILE* file);

/* ================================================================ */

extern int Record_load(Record** record, FILE* file);

/* ================================================================ */

extern void Record_print(const Record* record);

/* ================================================================ */

#endif /* RECORD_H */
