#include "countries.h"

/* ================================================================ */

int main(int argc, char** argv) {
    
    const char* filename = "countries.bin";
    
    Dict_t dictionary = NULL;
    
    if ((dictionary = Dict_load(filename, (void (*)(void*)) Country_print, free, NULL, (void (*)(void*, FILE*)) Country_load, sizeof(struct country))) == NULL) {
        printf("Unable to load a dictionary - %s\n", strerror(errno));
        
        /* ======== */
        return EXIT_FAILURE;
    }
        
    Dict_print(dictionary);
        
    Dict_destroy(dictionary);
    
    /* ======== */
    
    return EXIT_SUCCESS;
}
