#include "hashing.h"

extern void computeHash(const char *input, int len, unsigned int &result);


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // Open the file using the filename passed from command line
    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << argv[1] << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the whole file into a string stream
    std::string input = buffer.str(); // Convert to string
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
