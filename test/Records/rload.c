#include "Records.h"

#define FILENAME "records.bin"

/* ================================================================ */

int main(int argc, char** argv) {

    Dict_t dict = NULL;

    /* ================ */

    if ((dict = Dict_load(FILENAME, (void (*)(void*)) Record_print, (void (*)(void*)) Record_destroy, (int (*)(void*, FILE*))   Record_save, (int (*)(void**, FILE*)) Record_load)) == NULL) {

        printf("Unable to load a dictionary: %s\n", strerror(errno));

        /* ======== */
        return EXIT_FAILURE;
    }

    Dict_print(dict);

    Dict_destroy(dict);

    /* ======== */

    return EXIT_SUCCESS;
}

/* ================================================================ */
