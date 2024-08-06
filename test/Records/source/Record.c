#include "../Records.h"

static char* access_level_descriptions[] = {
    "M (Master Researcher)\nThe highest level of access, reserved for lead scientists and principal investigators.\nMaster Researchers have full control over all laboratory operations, including\nexperimental design, funding allocation, and personnel management.\nThey are responsible for overseeing all research activities and ensuring\ncompliance with safety protocols.",

    "M1 (Senior Scientist)\nSenior Scientists have extensive experience and can lead major research projects.\nThey can design experiments, analyze data, and publish findings.\nThey also mentor junior staff and have the authority to approve significant changes to research protocols.",
    
    "M2 (Research Associate)\nResearch Associates support Senior Scientists by conducting experiments and managing\nspecific research tasks. They have access to laboratory equipment and\ncan analyze samples but must operate under the guidance of higher-level researchers.",

    "B (Biological Technician)\nBiological Technicians assist in the preparation and analysis of biological samples.\nThey can perform routine laboratory procedures, maintain equipment, and ensure compliance with safety standards.\nTheir access allows them to handle samples but not to make significant experimental decisions.",

    "B1 (Data Analyst)\nData Analysts focus on interpreting research data and generating reports.\nThey have access to computational resources and statistical tools necessary for data analysis,\nbut they do not conduct experiments or handle biological materials directly.",

    "B2 (Laboratory Assistant)\nLaboratory Assistants perform essential support tasks, such as cleaning and organizing the lab,\npreparing reagents, and assisting with sample collection. They have limited access\nto sensitive areas and materials, primarily focused on maintaining laboratory operations.",

    "C (Collaborating Researcher)\nCollaborating Researchers are external scientists or interns who work on specific\nprojects in the lab. They have restricted access to certain areas and data,\nallowing them to contribute to research while ensuring that sensitive information is protected.",

    "X (Visitor)\nVisitors have the lowest level of access, typically granted to guests or stakeholders.\nThey can tour the facility and attend presentations but are not allowed in restricted\nareas or to interact with sensitive materials."
    };

/* ================================================================ */

Record* Record_new(const char* ID, const char* name, unsigned int level) {

    Record* r = NULL;

    /* ================ */

    if ((r = calloc(1, sizeof(struct record))) == NULL) {
        return NULL;
    }

    r->id = strdup(ID);
    r->name = strdup(name);
    r->access_level = level;

    /* ======== */

    return r;
}

/* ================================================================ */

void Record_destroy(Record* r) {

    if (r == NULL) {
        return ;
    }

    free(r->name);
    free(r->id);

    free(r);
}

/* ================================================================ */

void Record_print(const Record* r) {

    if (r == NULL) {
        return ;
    }

    printf("%s (%s)\nAccess Level: %s", r->name, r->id, access_level_descriptions[r->access_level]);
}

/* ================================================================ */

int Record_save(Record* r, FILE* file) {

    size_t string_size = 0;
    size_t bytes_written = 0;

    /* ================== */

    if ((r == NULL) || (file == NULL)) {
        return EXIT_FAILURE;
    }

    string_size = strlen(r->id);

    if ((bytes_written = fwrite(&string_size, sizeof(size_t), 1, file)) != 1) {
        fprintf(stderr, "Written unexpected number of bytes\n");

        /* ======== */
        return EXIT_FAILURE;
    }

    if ((bytes_written = fwrite(r->id, sizeof(char), string_size, file)) != string_size * sizeof(char)) {
        fprintf(stderr, "Written unexpected number of bytes\n");

        /* ======== */
        return EXIT_FAILURE;
    }

    /* ======== */

    string_size = strlen(r->name);

    if ((bytes_written = fwrite(&string_size, sizeof(size_t), 1, file)) != 1) {
        fprintf(stderr, "Written unexpected number of bytes\n");

        /* ======== */
        return EXIT_FAILURE;
    }

    if ((bytes_written = fwrite(r->name, sizeof(char), string_size, file)) != string_size * sizeof(char)) {
        fprintf(stderr, "Written unexpected number of bytes\n");

        /* ======== */
        return EXIT_FAILURE;
    }

    /* ======== */

    if ((bytes_written = fwrite(&r->access_level, sizeof(r->access_level), 1, file)) != 1) {
        fprintf(stderr, "Written unexpected number of bytes\n");

        /* ======== */
        return EXIT_FAILURE;
    }

    /* ======== */

    return EXIT_SUCCESS;
}

/* ================================================================ */

int Record_load(Record** record, FILE* file) {

    char* id = NULL;
    char* name = NULL;
    unsigned int level = 0;

    size_t bytes_to_read = 0;
    size_t bytes_read = 0;

    size_t string_size = 0;

    /* ================================================ */
    /* ================== Reading ID ================== */
    /* ================================================ */

    if ((bytes_read = fread(&string_size, sizeof(size_t), 1, file)) != 1) {
        fprintf(stderr, "Read unexpected number of bytes for size (%s) (%zd - %zd)\n", strerror(errno), bytes_read, string_size);

        /* ======== */
        return EXIT_FAILURE;
    }

    if ((id = malloc(sizeof(char) * string_size + 1)) == NULL) {
        return EXIT_FAILURE;
    }

    if ((bytes_read = fread(id, sizeof(char), string_size, file)) != string_size) {
        fprintf(stderr, "Read unexpected number of bytes\n");

        /* ======== */
        return EXIT_FAILURE;
    }

    id[bytes_read] = '\0';

    /* ================================================ */
    /* =============== Reading the name =============== */
    /* ================================================ */
    
    if (fread(&string_size, sizeof(size_t), 1, file) != 1) {
        fprintf(stderr, "Read unexpected number of bytes\n");

        free(id);

        /* ======== */
        return EXIT_FAILURE;
    }

    if ((name = malloc(sizeof(char) * string_size + 1)) == NULL) {
        free(id);

        /* ======== */
        return EXIT_FAILURE;
    }

    if ((bytes_read = fread(name, sizeof(char), string_size, file)) != string_size) {
        fprintf(stderr, "Read unexpected number of bytes\n");

        free(id);

        /* ======== */
        return EXIT_FAILURE;
    }

    name[bytes_read] = '\0';

    /* ================================================ */
    /* =========== Reading the access level =========== */
    /* ================================================ */

    if ((bytes_read = fread(&level, sizeof(unsigned int), 1, file)) != 1) {
        fprintf(stderr, "Read unexpected number of bytes\n");

        free(id);
        free(name);

        /* ======== */
        return EXIT_FAILURE;
    }

    if ((*record = Record_new(id, name, level)) == NULL) {

        free(id);
        free(name);

        /* ======== */
        return EXIT_FAILURE;
    }

    free(id);
    free(name);

    /* ======== */

    return EXIT_SUCCESS;
}

/* ================================================================ */
