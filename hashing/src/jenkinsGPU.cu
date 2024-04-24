#include <iostream>

__device__ unsigned int jenkins_hash_step(unsigned int previousHash, char c) {
    unsigned int hash = previousHash;
    hash += c;
    hash += (hash << 10);
    hash ^= (hash >> 6);
    return hash;
}

__global__ void computeJenkinsHashKernel(const char *input, int len, unsigned int *hash) {
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index < len) {
        unsigned int localHash = jenkins_hash_step(0, input[index]);  // Initialize local hash for each character
        atomicAdd(hash, localHash);
    }
}

extern void computeJenkinsHash(const char *input, int len, unsigned int &result) {
    char *d_input;
    unsigned int *d_hash;
    unsigned int zero = 0;

    cudaMalloc((void **)&d_input, len);
    cudaMalloc((void **)&d_hash, sizeof(unsigned int));

    cudaMemcpy(d_input, input, len, cudaMemcpyHostToDevice);
    cudaMemcpy(d_hash, &zero, sizeof(unsigned int), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocks = (len + blockSize - 1) / blockSize;
    computeJenkinsHashKernel<<<numBlocks, blockSize>>>(d_input, len, d_hash);

    cudaMemcpy(&result, d_hash, sizeof(unsigned int), cudaMemcpyDeviceToHost);

    // Apply final Jenkins mix steps without modulo normalization
    result += (result << 3);
    result ^= (result >> 11);
    result += (result << 15);

    cudaFree(d_input);
    cudaFree(d_hash);
}
