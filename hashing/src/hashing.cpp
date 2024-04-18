#include "hashing.h"

unsigned int simpleHash(const std::string& input) {
    unsigned int hash = 0;
    for (char c : input) {
        hash = (hash + c) * 31;  // Multiply by 31 for each character
    }
    return hash % 1023;  // Return modulo 1023
}