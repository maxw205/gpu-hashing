#include <iostream>

__global__ void computeHashKernel(const char *input, int len, unsigned int *hash) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index < len) {
        unsigned int localHash = 0;
        char c = input[index];
        localHash = (localHash + c) * 31;
        atomicAdd(hash, localHash);
    }
}

extern void computeHash(const char *input, int len, unsigned int &result) {
    char *d_input;
    unsigned int *d_hash;
    unsigned int zero = 0;

    cudaMalloc((void **)&d_input, len);
    cudaMalloc((void **)&d_hash, sizeof(unsigned int));
    
    cudaMemcpy(d_input, input, len, cudaMemcpyHostToDevice);
    cudaMemcpy(d_hash, &zero, sizeof(unsigned int), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocks = (len + blockSize - 1) / blockSize;
    computeHashKernel<<<numBlocks, blockSize>>>(d_input, len, d_hash);

    cudaMemcpy(&result, d_hash, sizeof(unsigned int), cudaMemcpyDeviceToHost);
    
    result %= 1023;  // Modulo operation as in the CPU version
    std::cout << len;

    cudaFree(d_input);
    cudaFree(d_hash);
}
