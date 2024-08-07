#include "../../dictionary.h"

#define FILENAME "dictionary.bin"

/* ================================================================ */

void how_to_print_INT(void* data);

/* Not implemented in this scenario */
int how_to_write_INT(void* data, FILE* file);

int how_to_read_INT(void** data, FILE* file);

/* ================================================================ */

int main(int argc, char** argv) {
    
    Dict_t d = Dict_load(FILENAME, how_to_print_INT, free, NULL, how_to_read_INT);
    
    /* ================ */
    
    if (d == NULL) {
        fprintf(stderr, "Unable to create a dictionary - %s\n", strerror(errno));
        
        /* ======== */
        return EXIT_FAILURE;
    }
    
    printf("The dictionary has been loaded successfully!\n");
    Dict_print(d);
    
    Dict_destroy(d);
    
    /* ======== */
    
    return EXIT_SUCCESS;
}

/* ================================================================ */

int how_to_read_INT(void** data, FILE* file) {

    *data = malloc(sizeof(int));

    fread(*data, sizeof(int), 1, file);

    return 0;
}

/* ================================================================ */

void how_to_print_INT(void* data) {
    printf("%d", *((int*) data));
}
