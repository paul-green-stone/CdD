#include "../../dictionary.h"

/* ================================================================ */

size_t hash_pjw(const char* key, size_t mod) {
    
    const char* ptr = key;
    size_t value = 0;
    
    /* ================ */
    
    while (*ptr != '\0') {
        size_t temp;
        
        value = (value << 4) + (*ptr);
        
        if ((temp = (value & 0xf0000000))) {
            value = value ^ (temp >> 24);
            value = value ^ temp;
        }
        
        ptr++;
    }
    
    /* ======== */
    
    return value % mod;
}

/* ================================================================ */

size_t probe_hash(size_t hash_index, size_t prime) {
    return prime - (hash_index % prime);
}

/* ================================================================ */
