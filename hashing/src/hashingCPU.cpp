#include "hashing.h"

unsigned int simpleHash(const char* input) {
    unsigned int hash = 0;
    for (const char* p = input; *p != '\0'; ++p) {
        hash = (hash + *p) * 31;  // Multiply by 31 for each character
    }
    return hash % 1023;  // Return modulo 1023
}