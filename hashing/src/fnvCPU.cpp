#include <cstring>  
#include "hashing.h"

unsigned int fnv1_hash(const char* str) {
    const unsigned int FNV_prime = 0x01000193; 
    const unsigned int FNV_offset_basis = 0x811C9DC5; 

    unsigned int hash = FNV_offset_basis;
    int len = strlen(str); 

    for (int i = 0; i < len; i++) {
        hash *= FNV_prime;
        hash ^= (unsigned int)str[i]; // XOR
    }

    return hash;
}
