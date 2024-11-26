#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16

void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block1[i] ^ block2[i];
    }
}

void encrypt_block(uint8_t *key, uint8_t *input, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}

void CBC_MAC(uint8_t *key, uint8_t *message, int num_blocks, uint8_t *mac) {
    uint8_t iv[BLOCK_SIZE] = {0};
    uint8_t temp[BLOCK_SIZE];

    for (int i = 0; i < num_blocks; i++) {
        xor_blocks(iv, &message[i * BLOCK_SIZE], temp);
        encrypt_block(key, temp, iv);
    }
    memcpy(mac, iv, BLOCK_SIZE);
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                               0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};

    uint8_t message[BLOCK_SIZE] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
                                    0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};

    uint8_t mac[BLOCK_SIZE];
    CBC_MAC(key, message, 1, mac);

    uint8_t extended_message[BLOCK_SIZE * 2];
    memcpy(extended_message, message, BLOCK_SIZE);
    uint8_t xor_block[BLOCK_SIZE];
    xor_blocks(message, mac, xor_block);
    memcpy(extended_message + BLOCK_SIZE, xor_block, BLOCK_SIZE);

    uint8_t mac_extended[BLOCK_SIZE];
    CBC_MAC(key, extended_message, 2, mac_extended);

    printf("MAC for single-block message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02X ", mac[i]);
    printf("\n");

    printf("MAC for two-block message X || (X XOR T): ");
    for (int i = 0; i < BLOCK_SIZE; i++) printf("%02X ", mac_extended[i]);
    printf("\n");

    return 0;
}

