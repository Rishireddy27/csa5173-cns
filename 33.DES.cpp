#include <stdio.h>
#include <stdint.h>

#define ROUNDS 16

uint64_t initial_permutation(uint64_t block);
uint64_t final_permutation(uint64_t block);
uint32_t feistel_function(uint32_t half_block, uint64_t subkey);
void generate_subkeys(uint64_t key, uint64_t subkeys[16]);
uint64_t des_encrypt(uint64_t plaintext, uint64_t key);
uint64_t des_decrypt(uint64_t ciphertext, uint64_t key);

uint64_t initial_permutation(uint64_t block) {
    static const int IP[64] = {
        58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
    };
    uint64_t permuted = 0;
    for (int i = 0; i < 64; i++) {
        permuted |= ((block >> (64 - IP[i])) & 1) << (63 - i);
    }
    return permuted;
}

uint64_t final_permutation(uint64_t block) {
    static const int FP[64] = {
        40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
    };
    uint64_t permuted = 0;
    for (int i = 0; i < 64; i++) {
        permuted |= ((block >> (64 - FP[i])) & 1) << (63 - i);
    }
    return permuted;
}

uint32_t feistel_function(uint32_t half_block, uint64_t subkey) {
    uint32_t result = half_block ^ (subkey & 0xFFFFFFFF);
    return (result << 1) | (result >> 31);
}

void generate_subkeys(uint64_t key, uint64_t subkeys[16]) {
    for (int i = 0; i < ROUNDS; i++) {
        subkeys[i] = (key >> (ROUNDS - i - 1)) & 0xFFFFFFFFFFFF;
    }
}

uint64_t des_encrypt(uint64_t plaintext, uint64_t key) {
    uint64_t subkeys[16];
    generate_subkeys(key, subkeys);
    uint64_t permuted = initial_permutation(plaintext);
    uint32_t L = permuted >> 32;
    uint32_t R = permuted & 0xFFFFFFFF;

    for (int i = 0; i < ROUNDS; i++) {
        uint32_t temp = R;
        R = L ^ feistel_function(R, subkeys[i]);
        L = temp;
    }

    uint64_t pre_output = ((uint64_t)R << 32) | L;
    return final_permutation(pre_output);
}

uint64_t des_decrypt(uint64_t ciphertext, uint64_t key) {
    uint64_t subkeys[16];
    generate_subkeys(key, subkeys);
    uint64_t permuted = initial_permutation(ciphertext);
    uint32_t L = permuted >> 32;
    uint32_t R = permuted & 0xFFFFFFFF;

    for (int i = ROUNDS - 1; i >= 0; i--) {
        uint32_t temp = L;
        L = R ^ feistel_function(L, subkeys[i]);
        R = temp;
    }

    uint64_t pre_output = ((uint64_t)R << 32) | L;
    return final_permutation(pre_output);
}

int main() {
    uint64_t plaintext = 0x0123456789ABCDEF;
    uint64_t key = 0x133457799BBCDFF1;
    uint64_t ciphertext = des_encrypt(plaintext, key);
    uint64_t decrypted = des_decrypt(ciphertext, key);

    printf("Plaintext: %016llX\n", plaintext);
    printf("Ciphertext: %016llX\n", ciphertext);
    printf("Decrypted: %016llX\n", decrypted);

    return 0;
}

