#include "Records.h"

/* ================================================================ */

int main(int argc, char** argv) {

    Record* r = NULL;

    /* ================ */

    if ((r = Record_new("IU2-77-a", "John Doe", M)) == NULL) {
        printf("Error has occured: %s\n", strerror(errno));
    }

    Record_print(r);

    Record_destroy(r);

    /* ======== */

    return EXIT_SUCCESS;
}

/* ================================================================ */
