#ifndef COUNTRY
#define COUNTRY

#include "../countries.h"

#define NAMELEN 64

/* ================================================================ */

struct population {
    size_t amount;
    int year;
};

/* ================================ */

typedef struct country {
    
    /* A country name. Long enough to hold the longest country's name - The United Kingdom of Great Britain and Northern Ireland */
    char* name;
    
    double area;
    
    char* capital;
    /* The current president/leader */
    char* president;
    char* currency;
    
    struct population Population;
} Country;

/* ================================================================ */
/* ========================== Interface =========================== */
/* ================================================================ */

extern Country* Country_new(const char* name, const char* capital, const char* president, const char* currency, double area, size_t population, int year);

/* ================================================================ */

extern void Country_destroy(Country** country);

/* ================================================================ */

extern void Country_print(const Country* country);

/* ================================================================ */

extern void Country_save(Country* c, FILE* file);

/* ================================================================ */

extern void Country_load(Country* c, FILE* file);

/* ================================================================ */

#endif /* COUNTRY */
