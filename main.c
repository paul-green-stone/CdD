#include "./dictionary.h"

#include <time.h>

void print_int(void* data) {
    printf("%d", *((int*) data));
}

void _write(void* data, FILE* file) {
    fwrite(data, sizeof(int), 1, file);
}

void _read(void* data, FILE* file) {
    fread(data, sizeof(int), 1, file);
}

int main(int argc, char** argv) {

    srand(time(NULL));

    char* filename = "numbers.txt";
    
    Dict_t dictionary = Dict_new(7, print_int, free, _write, NULL);
    Dict_t d;
    
    char* keys[] = {"one", "two", "three"};

    for (size_t i = 0; i < 3; i++) {
        int* value;

        if ((value = malloc(sizeof(int))) != NULL) {
            *value = rand() % 100;

            Dict_insert(keys[i], value, dictionary);
        }
    }

    Dict_print(dictionary);

    Dict_saveb(dictionary, filename);

    d = Dict_loadb(filename, print_int, free, _write, _read);

    printf("The size of the new dict is %zd and its capacity is %zd\n", Dict_size(d), Dict_capacity(d));

    Dict_print(d);

    Dict_destroy(dictionary);
    Dict_destroy(d);
}
