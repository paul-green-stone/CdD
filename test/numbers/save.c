#include "../../dictionary.h"

#define FILENAME "dictionary.bin"

/* ================================================================ */

/* Not implemented in this scenario */
void how_to_print_INT(void* data);

int how_to_write_INT(void* data, FILE* file);

/* Not implemented in this scenario */
int how_to_read_INT(void* data, FILE* file);

/* ================================================================ */

int main(int argc, char** argv) {
    
    CdD_Dict* d = Dict_new(5, NULL, NULL, how_to_write_INT, NULL);
    
    int n10 = 10;
    int n77 = 77;
    int n1 = 1;
    int nn22 = -22;
    
    /* ================ */
    
    if (d == NULL) {
        fprintf(stderr, "Unable to create a dictionary - %s\n", strerror(errno));
        
        /* ======== */
        return EXIT_FAILURE;
    }
    
    Dict_insert("ten", &n10, d);
    Dict_insert("seventy seven", &n77, d);
    Dict_insert("one", &n1, d);
    Dict_insert("negative twenty two", &nn22, d);
    
    Dict_save(d, FILENAME);
    
    Dict_destroy(d);
    
    /* ======== */
    
    return EXIT_SUCCESS;
}

/* ================================================================ */

int how_to_write_INT(void* data, FILE* file) {
    fwrite(data, sizeof(int), 1, file);

    return 0;
}
