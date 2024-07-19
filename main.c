#include "include/hash/hash.h"

void print_int(void* data) {
    printf("%d", *((int*) data));
}

int main(int argc, char** argv) {
    
    OAtable_t table = OAtable_new(7, hash_pjw, probe_hash, print_int);
    
    int value = 991;
    int value2 = 90;
    char* key = "Awesome Value";
    
    OAtable_add(table, key, &value);
    key = "hey";
    OAtable_add(table, key, &value2);
    
    printf("size = %zd\n", OAtable_size(table));
    
    OAtable_print(table);
}
