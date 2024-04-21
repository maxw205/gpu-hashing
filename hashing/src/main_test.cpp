#include "hashing.h"

extern void computeHash(const char *input, int len, unsigned int &result);


int main() {
    // File loading
    std::ifstream file("random_text.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();  // Read the whole file into a string stream
    std::string input = buffer.str();  // Convert to string
    file.close();

    // Ensure input is not empty
    if (input.empty()) {
        std::cerr << "File is empty or reading failed." << std::endl;
        return 1;
    }

    unsigned int hashGPUResult = 0;
    unsigned int hashCPUResult = 0;

    // Timing GPU hash computation
    auto startGPU = std::chrono::high_resolution_clock::now();
    computeHash(input.c_str(), input.length(), hashGPUResult);
    auto endGPU = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> gpuTime = endGPU - startGPU;

    std::cout << "Hash of the file (GPU): " << hashGPUResult << std::endl;
    std::cout << "Time taken by GPU: " << gpuTime.count() << " ms" << std::endl;

    // Timing CPU hash computation
    auto startCPU = std::chrono::high_resolution_clock::now();
    hashCPUResult = simpleHash(input.c_str());
    auto endCPU = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> cpuTime = endCPU - startCPU;

    std::cout << "Hash of the file (CPU): " << hashCPUResult << std::endl;
    std::cout << "Time taken by CPU: " << cpuTime.count() << " ms" << std::endl;

    return 0;
}