#include <iostream>
#include "hashing.h"

extern void computeHash(const char *input, int len, unsigned int &result);

int main() {
    std::cout << "Hello from CPU." << std::endl;

    const char *input = "Hello, World!";
    unsigned int hashResult = 0;
    computeHash(input, strlen(input), hashResult);

    std::cout << "Hash of '" << input << "' is " << hashResult << std::endl;

    std::string input2 = "Hello, World!";
    
    unsigned int hash = simpleHash(input2);
    std::cout << "Hash of \"" << input2 << "\": " << hash << std::endl;


    return 0;
}
