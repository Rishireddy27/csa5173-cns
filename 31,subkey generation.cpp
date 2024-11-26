#include <stdio.h>
#include <stdint.h>
#include <string.h>

void left_shift(uint8_t *input, uint8_t *output, int size) {
    int carry = 0;
    for (int i = size - 1; i >= 0; i--) {
        int next_carry = input[i] >> 7;
        output[i] = (input[i] << 1) | carry;
        carry = next_carry;
    }
}

void xor_with_constant(uint8_t *key, uint8_t constant, int size) {
    key[size - 1] ^= constant;
}

void generate_subkeys(uint8_t *L, uint8_t *K1, uint8_t *K2, int block_size) {
    uint8_t R_b = (block_size == 64) ? 0x1B : 0x87;
    uint8_t temp[16] = {0};
    int size = block_size / 8;

    left_shift(L, K1, size);
    if (L[0] & 0x80) xor_with_constant(K1, R_b, size);

    left_shift(K1, K2, size);
    if (K1[0] & 0x80) xor_with_constant(K2, R_b, size);
}

int main() {
    uint8_t L[16] = {0}; 
    uint8_t K1[16] = {0}, K2[16] = {0};
    int block_size = 128;

    memset(L, 0xA1, block_size / 8);

    generate_subkeys(L, K1, K2, block_size);

    printf("K1: ");
    for (int i = 0; i < block_size / 8; i++) printf("%02X ", K1[i]);
    printf("\nK2: ");
    for (int i = 0; i < block_size / 8; i++) printf("%02X ", K2[i]);
    printf("\n");

    return 0;
}

