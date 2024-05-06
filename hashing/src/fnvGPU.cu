#include <iostream>

__device__ unsigned int fnv1_hash(unsigned int previousHash, char c) {
    const unsigned int FNV_prime = 0x01000193; 
    unsigned int hash = previousHash;
    hash *= FNV_prime;
    hash ^= (unsigned int)c;
    return hash;
}

__global__ void computeFNV1HashKernel(const char *input, int len, unsigned int *hash) {
    const unsigned int FNV_offset_basis = 0x811C9DC5; 
    int index = threadIdx.x + blockIdx.x * blockDim.x;
    if (index < len) {
        unsigned int localHash = fnv1_hash(FNV_offset_basis, input[index]);
        atomicAdd(hash, localHash);
    }
}

extern void computeFNV1Hash(const char *input, int len, unsigned int &result) {
    char *d_input;
    unsigned int *d_hash;
    unsigned int zero = 0;

    cudaMalloc((void **)&d_input, len);
    cudaMalloc((void **)&d_hash, sizeof(unsigned int));

    cudaMemcpy(d_input, input, len, cudaMemcpyHostToDevice);
    cudaMemcpy(d_hash, &zero, sizeof(unsigned int), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocks = (len + blockSize - 1) / blockSize;
    computeFNV1HashKernel<<<numBlocks, blockSize>>>(d_input, len, d_hash);

    cudaMemcpy(&result, d_hash, sizeof(unsigned int), cudaMemcpyDeviceToHost);

    result %= 1023;

    cudaFree(d_input);
    cudaFree(d_hash);
}
