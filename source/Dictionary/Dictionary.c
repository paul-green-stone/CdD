#include "../../dictionary.h"

#define IS_EMPTY(dict, cell) ((strlen((dict)->mappings[(cell)]->key) == 0) && ((dict)->mappings[(cell)]->value == NULL))

#define MAX_TAG_LEN 64

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
    int (*save_data)(void* data, FILE* file);
    int (*load_data)(void** data, FILE* file);
    
    struct mapping** mappings;
};

typedef struct dictionary* Dict_t;

/* ================================================================ */

Dict_t Dict_new(size_t size, void (*print)(void* data), void (*destroy)(void* data), int (*save_data)(void* data, FILE* file), int (*load_data)(void** data, FILE* file)) {
    
    Dict_t dict = NULL;
    
    /* ================ */
    
    if ((dict = calloc(1, sizeof(struct dictionary))) == NULL) {
        return NULL;
    }
    
    if ((dict->mappings = calloc(size, sizeof(struct mapping*))) == NULL) {
        free(dict);
        
        /* ======== */
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        dict->mappings[i] = calloc(1, sizeof(struct mapping));
        
        if (dict->mappings[i] == NULL) {
            
            for (size_t j = 0; j < i; j++) {
                free(dict->mappings[j]);
            }
            
            free(dict->mappings);
            free(dict);
            
            /* ======== */
            
            return NULL;
        }
    }
    
    dict->logical_size = size;
    
    dict->print = print;
    dict->destroy = destroy;
    dict->save_data = save_data;
    dict->load_data = load_data;
    
    /* ======== */
    
    return dict;
}

/* ================================================================ */

void Dict_print(const Dict_t dict) {
    
    if (dict == NULL) {
        return ;
    }
    
    for (size_t i = 0; i < dict->logical_size; i++) {
        printf("%zu. ", i);
        
        if (!IS_EMPTY(dict, i)) {
            // dict->mappings[i]->value != NULL
            printf("%s -> ", dict->mappings[i]->key);
            dict->print(dict->mappings[i]->value);
        }
        
        printf("\n");
    }
}

/* ================================================================ */

ssize_t Dict_insert(const char* key, void* value, Dict_t dict) {
    
    size_t index = 0;
    
    /* ================ */
    
    if (dict == NULL) {
        return -1;
    }
    
    if (dict->actual_size == dict->logical_size) {
        return -1;
    }
    
    for (size_t i = 0; i < dict->logical_size; i++) {
        index = (hash_pjw(key, dict->logical_size) + i * probe_hash(key, dict->logical_size)) % dict->logical_size;
        
        if (IS_EMPTY(dict, index)) {
            
            strncpy(dict->mappings[index]->key, key, MAX_TAG_LEN - 1);
            dict->mappings[index]->value = value;
            
            dict->actual_size++;
            
            /* ======== */
            break ;
        }
        else if (strcmp(dict->mappings[index]->key, key) == 0) {
            return -1;
        }
    }
    
    /* ======== */
    
    return index;
}

/* ================================================================ */

ssize_t Dict_size(const Dict_t dict) {
    
    if (dict == NULL) {
        return -1;
    }
    
    /* ======== */
    
    return dict->actual_size;
}

/* ================================================================ */

ssize_t Dict_capacity(const Dict_t dict) {

    if (dict == NULL) {
        return -1;
    }
    
    /* ======== */
    
    return dict->logical_size;
}

/* ================================================================ */

void Dict_destroy(Dict_t dict) {
    
    if (dict == NULL) {
        return ;
    }

    for (size_t i = 0; i < dict->logical_size; i++) {

        if (dict->destroy) {
            dict->destroy(dict->mappings[i]->value);
        }

        free(dict->mappings[i]);
    }

    free(dict->mappings);
    free(dict);
}

/* ================================================================ */

float Dict_loadF(const Dict_t dict) {
    
    if (dict == NULL || dict->logical_size == 0) {
        return -1.f;
    }
    
    /* ======== */
    
    return ((float) dict->actual_size / dict->logical_size);
}

/* ================================================================ */

void* Dict_lookup(const char* key, Dict_t dict) {
    
    size_t index = 0;
    
    /* ================ */
    
    if (dict == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < dict->logical_size; i++) {
        index = (hash_pjw(key, dict->logical_size) + i * probe_hash(key, dict->logical_size)) % dict->logical_size;
        
        if (IS_EMPTY(dict, index)) {
            return NULL;
        }
        else if (!IS_EMPTY(dict, index) && strcmp(key, dict->mappings[index]->key) == 0) {
            return dict->mappings[index]->value;
        }
    }
    
    /* ======== */
    
    return NULL;
}

/* ================================================================ */

void* Dict_remove(const char* key, Dict_t dict) {
    
    size_t index = 0;
    void* value = NULL;
    
    /* ================ */
    
    if (dict == NULL || key == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < dict->logical_size; i++) {
        index = (hash_pjw(key, dict->logical_size) + i * probe_hash(key, dict->logical_size)) % dict->logical_size;

        if (IS_EMPTY(dict, index)) {
            break ;
        }
        else if (!IS_EMPTY(dict, index) && strcmp(key, dict->mappings[index]->key) == 0) {
            
            memset(dict->mappings[index]->key, '\0', MAX_TAG_LEN);
            
            value = dict->mappings[index]->value;
            dict->mappings[index]->value = NULL;
            
            dict->actual_size--;
        }
    }

    /* ======== */

    return value;
}

/* ================================================================ */

int Dict_save(const Dict_t dict, const char* filename) {

    FILE* file;

    size_t bytes_written = 0;

    /* ================ */

    if (dict == NULL) {
        return -1;
    }

    if ((file = fopen(filename, "wb")) == NULL) {
        fprintf(stderr, "Failed to open file for writing: %s\n", strerror(errno));

        /* ======== */
        return -1;
    }

    if (fwrite(&dict->logical_size, sizeof(dict->logical_size), 1, file) != 1) {
        fprintf(stderr, "Error has occured: written unexpected number of bytes for the dictionary size\n");

        /* ======== */
        return -1;
    }

    for (size_t i = 0; i < dict->logical_size; i++) {
        if (!IS_EMPTY(dict, i)) {

            size_t key_len = strlen(dict->mappings[i]->key);

            if ((bytes_written = fwrite(&key_len, sizeof(size_t), 1, file)) != 1) {
                fprintf(stderr, "Error has occured: written unexpected number of bytes for the dictionary key size\n");
            }

            if ((bytes_written = fwrite(dict->mappings[i]->key, sizeof(char), key_len, file)) != key_len) {
                fprintf(stderr, "Error has occured: written unexpected number of bytes for the dictionary key (key = %s)\n", dict->mappings[i]->key);

                /* ======== */
                return -1;
            }
                       
            if (dict->save_data) {
                dict->save_data(dict->mappings[i]->value, file);
            }
        }
    }

    fclose(file);

    /* ======== */

    return 0;
}

/* ================================================================ */

Dict_t Dict_load(const char* filename, void (*print)(void* value), void (*destroy)(void* value), int (*save_data)(void* data, FILE* file), int (*load_data)(void** data, FILE* file)) {

    Dict_t dict = NULL;
    size_t size;
    size_t bytes_read = 0;

    FILE* file = NULL;

    void* value = NULL;

    /* ================ */

    if ((file = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "Failed to open file for reading: %s\n", strerror(errno));

        /* ======== */
        return NULL;
    }

    if ((bytes_read = fread(&size, sizeof(size), 1, file)) != 1) {
        fprintf(stderr, "Error has occured: unable to read the dictionary size (%zd)\n", bytes_read);

        /* ======== */
        return NULL;
    }

    if ((dict = Dict_new(size, print, destroy, save_data, load_data)) == NULL) {
        fclose(file);

        /* ======== */
        return NULL;
    }

    while (1) {
        char* key = NULL;

        size_t key_len = 0;

        if ((bytes_read = fread(&key_len, sizeof(size_t), 1, file)) != 1) {

            if (feof(file)) {
                break ;
            }

            fprintf(stderr, "Error has occured: unable to read the key size (%zd)\n", bytes_read);

            /* ======== */
            return NULL;
        }

        if ((key = malloc(sizeof(char) * key_len + 1)) == NULL) {
            fprintf(stderr, "Error has occured: %s\n", strerror(errno));

            /* ======== */
            return dict;
        }

        if ((bytes_read = fread(key, sizeof(char), key_len, file)) != key_len) {
            fprintf(stderr, "Error has occured: unable to read the key value\n");

            /* ======== */
            return NULL;
        }

        key[bytes_read] = '\0';

        dict->load_data(&value, file);

        Dict_insert(key, value, dict);
        
        free(key);
    }

    fclose(file);

    /* ======== */

    return dict;
}

/* ================================================================ */
