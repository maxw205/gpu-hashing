// addition.h
#ifndef ADDITION_H
#define ADDITION_H

#include <iostream>
//#include <openssl/sha.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>

unsigned int simpleHash(const char* input);
unsigned int fnv1_hash(const char* str);

#endif
