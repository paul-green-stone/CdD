#include "../../oatable.h"

#define IS_EMPTY(table, cell) ((strlen((table)->cells[(cell)]->tag) == 0) && ((table)->cells[(cell)]->data == NULL))

#define MAX_TAG_LEN 32

/* ================================================================ */

static struct cell {
    void* data;
    char tag[MAX_TAG_LEN];
};

/* ================================ */

static struct oatable {
    
    size_t logical_size;
    size_t actual_size;
    
    size_t (*h1)(const char* key, size_t mod);
    size_t (*h2)(const char* key, size_t mod);
    
    void (*print)(void* data);
    void (*destroy)(void* data);
    
    struct cell** cells;
};

typedef struct oatable* OAtable_t;

/* ================================================================ */

OAtable_t OAtable_new(size_t size, size_t (*h1)(const char* key, size_t mod), size_t (*h2)(const char* key, size_t mod), void (*print)(void* data)) {
    
    OAtable_t table = NULL;
    
    /* ================ */
    
    if ((table = calloc(1, sizeof(struct oatable))) == NULL) {
        return NULL;
    }
    
    if ((table->cells = calloc(size, sizeof(struct cell*))) == NULL) {
        free(table);
        
        /* ======== */
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        table->cells[i] = calloc(1, sizeof(struct cell));
        
        if (table->cells[i] == NULL) {
            
            for (size_t j = 0; j < i; j++) {
                free(table->cells[j]);
            }
            
            free(table->cells);
            free(table);
            
            /* ======== */
            
            return NULL;
        }
    }
    
    table->logical_size = size;
    
    table->h1 = h1;
    table->h2 = h2;
    table->print = print;
    
    /* ======== */
    
    return table;
}

/* ================================================================ */

void OAtable_print(const OAtable_t table) {
    
    if (table == NULL) {
        return ;
    }
    
    for (size_t i = 0; i < table->logical_size; i++) {
        printf("%zu. ", i);
        
        if (table->cells[i]->data != NULL) {
            printf("%s -> ", table->cells[i]->tag);
            table->print(table->cells[i]->data);
        }
        
        printf("\n");
    }
}

/* ================================================================ */

ssize_t OAtable_add(OAtable_t table, const char* key, void* data) {
    
    size_t index = 0;
    
    /* ================ */
    
    if (table == NULL) {
        return -1;
    }
    
    if (table->actual_size == table->logical_size) {
        return -1;
    }
    
    for (size_t i = 0; i < table->logical_size; i++) {
        index = (table->h1(key, table->logical_size) + i * table->h2(key, table->logical_size)) % table->logical_size;
        
        if (IS_EMPTY(table, index)) {
            
            strncpy(table->cells[index]->tag, key, MAX_TAG_LEN - 1);
            table->cells[index]->data = data;
            
            table->actual_size++;
            
            /* ======== */
            break ;
        }
        else if (strcmp(table->cells[index]->tag, key) == 0) {
            return -1;
        }
    }
    
    /* ======== */
    
    return index;
}

/* ================================================================ */

ssize_t OAtable_size(const OAtable_t table) {
    
    if (table == NULL) {
        return -1;
    }
    
    /* ======== */
    
    return table->actual_size;
}

