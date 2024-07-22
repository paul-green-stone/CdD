#include "../../dictionary.h"

#define IS_EMPTY(table, cell) ((strlen((table)->mappings[(cell)]->key) == 0) && ((table)->mappings[(cell)]->value == NULL))

#define MAX_TAG_LEN 32

/* ================================================================ */

static struct mapping {
    void* value;
    char key[MAX_TAG_LEN];
};

/* ================================ */

static struct dictionary {
    
    size_t logical_size;
    size_t actual_size;
    
    void (*print)(void* data);
    void (*destroy)(void* data);
    
    struct mapping** mappings;
};

typedef struct dictionary* Dict_t;

/* ================================================================ */

Dict_t Dict_new(size_t size, void (*print)(void* data), void (*destroy)(void* data)) {
    
    Dict_t table = NULL;
    
    /* ================ */
    
    if ((table = calloc(1, sizeof(struct dictionary))) == NULL) {
        return NULL;
    }
    
    if ((table->mappings = calloc(size, sizeof(struct mapping*))) == NULL) {
        free(table);
        
        /* ======== */
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        table->mappings[i] = calloc(1, sizeof(struct mapping));
        
        if (table->mappings[i] == NULL) {
            
            for (size_t j = 0; j < i; j++) {
                free(table->mappings[j]);
            }
            
            free(table->mappings);
            free(table);
            
            /* ======== */
            
            return NULL;
        }
    }
    
    table->logical_size = size;
    
    table->print = print;
    table->destroy = destroy;
    
    /* ======== */
    
    return table;
}

/* ================================================================ */

void Dict_print(const Dict_t table) {
    
    if (table == NULL) {
        return ;
    }
    
    for (size_t i = 0; i < table->logical_size; i++) {
        printf("%zu. ", i);
        
        if (table->mappings[i]->value != NULL) {
            printf("%s -> ", table->mappings[i]->key);
            table->print(table->mappings[i]->value);
        }
        
        printf("\n");
    }
}

/* ================================================================ */

ssize_t Dict_add(Dict_t table, const char* key, void* value) {
    
    size_t index = 0;
    
    /* ================ */
    
    if (table == NULL) {
        return -1;
    }
    
    if (table->actual_size == table->logical_size) {
        return -1;
    }
    
    for (size_t i = 0; i < table->logical_size; i++) {
        index = (hash_pjw(key, table->logical_size) + i * probe_hash(key, table->logical_size)) % table->logical_size;
        
        if (IS_EMPTY(table, index)) {
            
            strncpy(table->mappings[index]->key, key, MAX_TAG_LEN - 1);
            table->mappings[index]->value = value;
            
            table->actual_size++;
            
            /* ======== */
            break ;
        }
        else if (strcmp(table->mappings[index]->key, key) == 0) {
            return -1;
        }
    }
    
    /* ======== */
    
    return index;
}

/* ================================================================ */

ssize_t Dict_size(const Dict_t table) {
    
    if (table == NULL) {
        return -1;
    }
    
    /* ======== */
    
    return table->actual_size;
}

/* ================================================================ */

void Dict_destroy(Dict_t table) {
    
    if (table == NULL) {
        return ;
    }

    for (size_t i = 0; i < table->logical_size; i++) {
        free(table->mappings[i]);
    }

    free(table->mappings);
    free(table);
}

/* ================================================================ */

float Dict_loadF(const Dict_t table) {
    
    if (table == NULL || table->logical_size == 0) {
        return -1.f;
    }
    
    /* ======== */
    
    return ((float) table->actual_size / table->logical_size);
}

/* ================================================================ */

void* Dict_get(Dict_t table, const char* key) {
    
    size_t index = 0;
    
    /* ================ */
    
    if (table == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < table->logical_size; i++) {
        index = (hash_pjw(key, table->logical_size) + i * probe_hash(key, table->logical_size)) % table->logical_size;
        
        if (IS_EMPTY(table, index)) {
            return NULL;
        }
        else if (!IS_EMPTY(table, index) && strcmp(key, table->mappings[index]->key) == 0) {
            return table->mappings[index]->value;
        }
    }
    
    /* ======== */
    
    return NULL;
}

/* ================================================================ */

void* Dict_remove(Dict_t table, const char* key) {
    
    size_t index = 0;
    void* value = NULL;
    
    /* ================ */
    
    if (table == NULL || key == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < table->logical_size; i++) {
        index = (hash_pjw(key, table->logical_size) + i * probe_hash(key, table->logical_size)) % table->logical_size;
        
        if (IS_EMPTY(table, index)) {
            return NULL;
        }
        else if (!IS_EMPTY(table, index) && strcmp(key, table->mappings[index]->key) == 0) {
            
            memset(table->mappings[index]->key, '\0', MAX_TAG_LEN);
            
            value = table->mappings[index]->value;
            table->mappings[index]->value = NULL;
            
            table->actual_size--;
        }
    }
                                  
    /* ======== */
    
    return value;
}

/* ================================================================ */
