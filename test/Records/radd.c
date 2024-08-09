#include <sys/stat.h>
#include <getopt.h>
#include <ctype.h>

#include "Records.h"

#define FILENAME "records.bin"

/* ================================================================ */

int main(int argc, char** argv) {

    extern char *optarg;
    extern int optind, opterr, optopt;

    int opt;
    const char* optstr = ":";

    Record* r = NULL;
    CdD_Dict* dict = NULL;

    struct stat b;

    char* id = NULL;
    char* name = NULL;
    int access_level = X;

    /* ================ */

    if ((argc < 3) || (argc > 4)) {
        printf("usage: %s --id \"XX1-11-x\" --name \"John Doe\" [--acs \"access level\"]\n\n", argv[0]);
        printf("The follwoing access levels are posssible:\n -M (Master Researcher)\n -M1 (Senior Scientist)\n -M2 (Research Associate)\n -B (Biological Technician)\n -B1 (Data Analyst)\n -B3 (Laboratory Assistant)\n -C (Collaborating Researcher)\n -X (Visitor)\n");

        /* ======== */
        return EXIT_FAILURE;
    }

    while (1) {

        int index = 0;

        static struct option options[] = {
            {"id", required_argument, NULL, 0},
            {"name", required_argument, NULL, 1},
            {"acs", optional_argument, NULL, 2},
            {"help", optional_argument, NULL, 3},
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
                name = optarg;

                break ;

            /* ======== */

            case 2:
                access_level = (isdigit(optarg[0]) && (optarg[0] >= 48 && optarg[0] <= 55)) ? optarg[0] - '0' : -1;

                break ;

            /* ======== */

            case 3:
                printf("usage: %s --id \"XX1-11-x\" --name \"John Doe\" [--acs \"access level\"]\n\n", argv[0]);
                printf("The follwoing access levels are posssible:\n -M (Master Researcher)\n -M1 (Senior Scientist)\n -M2 (Research Associate)\n -B (Biological Technician)\n -B1 (Data Analyst)\n -B3 (Laboratory Assistant)\n -C (Collaborating Researcher)\n -X (Visitor)\n");

                /* ======== */
                return EXIT_FAILURE;
        }
    }

    if (access_level == -1) {
        printf("Unknown or unsupported access level provided.\nUnfortunately, the system does not grant the default permission,\nwhich appears to be 'visitor' due to certain events that occurred in the past.\nIf you are sure you are following the correct procedures and still receive this message,\nplease refer to your supervisor.\n");

        /* ======== */

        return EXIT_FAILURE;
    }

    if (stat(FILENAME, &b) == 0) {

        if ((dict = Dict_load(FILENAME, (void (*)(void*)) Record_print, (void (*)(void*)) Record_destroy, (int (*)(void*, FILE*))   Record_save, (int (*)(void**, FILE*)) Record_load)) == NULL) {

            printf("Unable to load a dictionary: %s\n", strerror(errno));

            /* ======== */
            return EXIT_FAILURE;
        }
    }
    else {
        if ((dict = Dict_new(7, (void (*)(void*)) Record_print, (void (*)(void*)) Record_destroy, (int (*)(void*, FILE*))   Record_save, (int (*)(void**, FILE*)) Record_load)) == NULL) {

            printf("Unable to create a dictionary: %s\n", strerror(errno));

            /* ======== */
            return EXIT_FAILURE;
        }
    }

    if ((r = Record_new(id, name, access_level)) == NULL) {
        fprintf(stderr, "Error has occured: unable to create a new error - %s\n", strerror(errno));

        /* ======== */
        return EXIT_FAILURE; 
    }

    Dict_insert(id, r, dict);

    Dict_save(dict, FILENAME);

    Dict_destroy(dict);

    /* ======== */

    return EXIT_SUCCESS;
}

/* ================================================================ */
