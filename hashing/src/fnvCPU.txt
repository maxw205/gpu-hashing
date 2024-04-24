#include <cstring>  // For strlen
#include "hahing.h"

unsigned int fnv1_hash(const char* str) {
    const unsigned int FNV_prime = 0x01000193; // 16777619
    const unsigned int FNV_offset_basis = 0x811C9DC5; // 2166136261

    unsigned int hash = FNV_offset_basis;
    int len = strlen(str); // Compute the length of the string

    for (int i = 0; i < len; i++) {
        hash *= FNV_prime;
        hash ^= (unsigned int)str[i]; // XOR with the byte of the data
    }

    return hash;
}
