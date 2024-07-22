#include "./dictionary.h"

void print_int(void* data) {
    printf("%d", *((int*) data));
}

int main(int argc, char** argv) {
    
    Dict_t dictionary = Dict_new(7, print_int, NULL);
    
    int v1 = 100;
    int v2 = 200;
    int v3 = 300;
    int v4 = 400;
    int v5 = 500;
    int v6 = 6000;
    int v7 = -19;

    Dict_add(dictionary, "Homer", &v1);
    Dict_add(dictionary, "Marge", &v2);
    Dict_add(dictionary, "Lisa", &v3);
    Dict_add(dictionary, "Bart", &v4);
    Dict_add(dictionary, "Moe", &v5);
    Dict_add(dictionary, "Nelson", &v6);
    Dict_add(dictionary, "Me?", &v7);
    Dict_add(dictionary, "WHo's that boy?", &v7);
    
    printf("size = %zd\n", Dict_size(dictionary));
    printf("load factor = %.2f\n", Dict_loadF(dictionary));
    
    Dict_print(dictionary);
    
    int* n =  Dict_get(dictionary, "Moe");
    
    if (n) printf("\nMoe's favorite number is %d\n", *n);
    
    printf("After deleting the Moe's favorite number:\n");
    
    Dict_remove(dictionary, "Moe");
    Dict_print(dictionary);
    
    printf("\nNew size is %zd\n", Dict_size(dictionary));

    Dict_destroy(dictionary);
}
