#include "hashing.h"


int main() {
    std::string input = "Hello, World!";
    
    unsigned int hash = simpleHash(input);
    std::cout << "Hash of \"" << input << "\": " << hash << std::endl;

    return 0;
}