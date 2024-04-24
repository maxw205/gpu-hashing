#include "hashing.h"
unsigned int jenkins_one_at_a_time_hash(const char* key) {
    int length = strlen(key);  // Calculate the length of the string
    unsigned int hash = 0;
    for (int i = 0; i < length; ++i) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}
