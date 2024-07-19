#include "include/hash/hash.h"

void print_int(void* data) {
    printf("%d", *((int*) data));
}

int main(int argc, char** argv) {
    
    OAtable_t table = OAtable_new(7, hash_pjw, probe_hash, print_int);
    
    int v1 = 100;
    int v2 = 200;
    int v3 = 300;
    int v4 = 400;
    int v5 = 500;
    int v6 = 6000;
    int v7 = -19;

    OAtable_add(table, "Homer", &v1);
    OAtable_add(table, "Marge", &v2);
    OAtable_add(table, "Lisa", &v3);
    OAtable_add(table, "Bart", &v4);
    OAtable_add(table, "Moe", &v5);
    OAtable_add(table, "Nelson", &v6);
    OAtable_add(table, "Me?", &v7);
    OAtable_add(table, "WHo's that boy?", &v7);
    
    printf("size = %zd\n", OAtable_size(table));
    
    OAtable_print(table);

    OAtable_destroy(table);
}
