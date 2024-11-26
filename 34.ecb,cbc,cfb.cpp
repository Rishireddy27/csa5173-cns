#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8

void pad_plaintext(uint8_t *plaintext, int *length) {
    int pad_len = BLOCK_SIZE - (*length % BLOCK_SIZE);
    plaintext[*length] = 0x80;
    for (int i = 1; i < pad_len; i++) {
        plaintext[*length + i] = 0x00;
    }
    *length += pad_len;
}

void xor_blocks(uint8_t *a, uint8_t *b, uint8_t *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] ^ b[i];
    }
}

void simple_encrypt(uint8_t *input, uint8_t *output, uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i % BLOCK_SIZE];
    }
}

void ecb_mode(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        simple_encrypt(&plaintext[i], &ciphertext[i], key);
    }
}

void cbc_mode(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t *iv, int length) {
    uint8_t temp[BLOCK_SIZE];
    memcpy(temp, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        uint8_t block[BLOCK_SIZE];
        xor_blocks(&plaintext[i], temp, block, BLOCK_SIZE);
        simple_encrypt(block, &ciphertext[i], key);
        memcpy(temp, &ciphertext[i], BLOCK_SIZE);
    }
}

void cfb_mode(uint8_t *plaintext, uint8_t *ciphertext, uint8_t *key, uint8_t *iv, int length) {
    uint8_t temp[BLOCK_SIZE];
    memcpy(temp, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        uint8_t block[BLOCK_SIZE];
        simple_encrypt(temp, block, key);
        xor_blocks(&plaintext[i], block, &ciphertext[i], BLOCK_SIZE);
        memcpy(temp, &ciphertext[i], BLOCK_SIZE);
    }
}

int main() {
    uint8_t plaintext[64] = "This is a test message for encryption modes.";
    uint8_t key[BLOCK_SIZE] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8};
    uint8_t iv[BLOCK_SIZE] = {0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x1, 0x2};
    uint8_t ciphertext[64] = {0};
    uint8_t decrypted[64] = {0};
    int length = strlen((char *)plaintext);

    pad_plaintext(plaintext, &length);

    printf("ECB Mode:\n");
    ecb_mode(plaintext, ciphertext, key, length);
    for (int i = 0; i < length; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    printf("CBC Mode:\n");
    cbc_mode(plaintext, ciphertext, key, iv, length);
    for (int i = 0; i < length; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    printf("CFB Mode:\n");
    cfb_mode(plaintext, ciphertext, key, iv, length);
    for (int i = 0; i < length; i++) printf("%02X ", ciphertext[i]);
    printf("\n");

    return 0;
}

