#include "../countries.h"

/* ================================================================ */

Country* Country_new(const char* name, const char* capital, const char* president, const char* currency, double area, size_t population, int year) {
    
    Country* c = NULL;
    
    /* ================ */
    
    if ((c = calloc(1, sizeof(struct country))) == NULL) {
        return NULL;
    }
    
    strncpy(c->name, name, NAMELEN);
    c->capital = strdup(capital);
    c->president = strdup(president);
    c->currency = strdup(currency);
    
    c->area = area;
    c->Population.amount = population;
    c->Population.year = year;
    
    /* ======== */
    
    return c;
}

/* ================================================================ */

void Country_destroy(Country** country) {
    
    if ((country == NULL) || (*country == NULL)) {
        return ;
    }
    
    free((*country)->name);
    free((*country)->capital);
    free((*country)->president);
    free((*country)->currency);
    
    free(*country);
}

/* ================================================================ */

void Country_print(const Country* country) {
    
    if (country == NULL) {
        return ;
    }
    
    printf("Name: %s\n", country->name);
    printf("Capital: %s\n", country->capital);
    printf("Area: %.2f\n", country->area);
    printf("President (current): %s\n", country->president);
    printf("Currency: %s\n", country->currency);
    printf("Population: %zu (%d)\n", country->Population.amount, country->Population.year);
}

/* ================================================================ */

void Country_save(Country* c, FILE* file) {
    
    size_t bytes = 0;
    
    /* ================ */
    
    if (c == NULL) {
        return ;
    }
    
    /* Writing a country's name */
    bytes = strlen(c->name);
    fwrite(&bytes, sizeof(bytes), 1, file);
    fwrite(c->name, sizeof(char), bytes, file);
    
    /* Writing a country's capital */
    bytes = strlen(c->capital);
    fwrite(&bytes, sizeof(bytes), 1, file);
    fwrite(c->capital, sizeof(char), bytes, file);
    
    printf("The country capital name must contain %zd characters\n", bytes);
    
    /* Writing a country's area */
    fwrite(&c->area, sizeof(double), 1, file);
    
    /* Writing a country's president */
    bytes = strlen(c->president);
    fwrite(&bytes, sizeof(bytes), 1, file);
    fwrite(c->president, sizeof(char), bytes, file);
    
    /* Writing a country's currency */
    bytes = strlen(c->currency);
    fwrite(&bytes, sizeof(bytes), 1, file);
    fwrite(c->currency, sizeof(char), bytes, file);
    
    /* Writing country's population */
    fwrite(&c->Population.amount, sizeof(size_t), 1, file);
    fwrite(&c->Population.year, sizeof(int), 1, file);
}

/* ================================================================ */

void Country_load(Country* c, FILE* file) {
    
    size_t bytes_to_read = 0;
    
    /* ================ */
    
    if (c == NULL) {
        return ;
    }
    
    /* Reading a country's name */
    fread(&bytes_to_read, sizeof(size_t), 1, file);
    if ((c->name = malloc(bytes_to_read)) == NULL) {
        return ;
    }
    fread(c->name, sizeof(char), bytes_to_read, file);
    
    /* Reading a country's capital */
    fread(&bytes_to_read, sizeof(size_t), 1, file);
    if ((c->capital = malloc(bytes_to_read)) == NULL) {
        return ;
    }
    fread(c->capital, sizeof(char), bytes_to_read, file);
    
    /* Reading a country's area */
    fread(&c->area, sizeof(double), 1, file);
    
    /* Reading a country's president */
    fread(&bytes_to_read, sizeof(size_t), 1, file);
    if ((c->president = malloc(bytes_to_read)) == NULL) {
        return ;
    }
    fread(c->president, sizeof(char), bytes_to_read, file);
    
    /* Reading a country's currency */
    fread(&bytes_to_read, sizeof(size_t), 1, file);
    if ((c->currency = malloc(bytes_to_read)) == NULL) {
        return ;
    }
    fread(c->currency, sizeof(char), bytes_to_read, file);
    
    /* Reading country's population */
    fread(&c->Population.amount, sizeof(size_t), 1, file);
    fread(&c->Population.year, sizeof(int), 1, file);
}

/* ================================================================ */
