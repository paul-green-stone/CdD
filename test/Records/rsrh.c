#include <getopt.h>
#include "Records.h"

#define FILENAME "records.bin"

/* ================================================================ */

int main(int argc, char** argv) {

    Dict_t dict = NULL;

    extern char *optarg;
    extern int optind, opterr, optopt;

    int opt;
    const char* optstr = ":";

    char* id = NULL;

    void* data = NULL;

    /* ================ */

    if (argc != 2) {
        printf("usage: %s --id \"id\"\n", argv[0]);

        /* ========*/
        return EXIT_SUCCESS;
    }

    while (1) {

        int index = 0;

        static struct option options[] = {
            {"id", required_argument, NULL, 0},
            {"help", optional_argument, NULL, 1},
        };

        if ((opt = getopt_long(argc, argv, optstr, options, &index)) == -1) {
            break ;
        }

        /* ================================================================ */

        switch (opt) {

            case 0:
                id = optarg;

                break ;

            /* ======== */

            case 1:
                printf("usage: %s --id \"id\"\n", argv[0]);

                /* ======== */
                return EXIT_SUCCESS;
        }
    }

    /* ================ */

    if ((dict = Dict_load(FILENAME, (void (*)(void*)) Record_print, (void (*)(void*)) Record_destroy, (int (*)(void*, FILE*))   Record_save, (int (*)(void**, FILE*)) Record_load)) == NULL) {

        printf("Unable to load a dictionary: %s\n", strerror(errno));

        /* ======== */
        return EXIT_FAILURE;
    }

    if ((data = Dict_lookup(id, dict)) != NULL) {
        Record_print((Record*) data);
        printf("\n");
    }
    else {
        printf("There is no such key\n");
    }

    Dict_destroy(dict);

    /* ======== */

    return EXIT_SUCCESS;
}

/* ================================================================ */
