#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8 
void xorBlocks(uint8_t *block1, uint8_t *block2, uint8_t *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}
void sdesEncrypt(uint8_t plaintext, uint8_t key, uint8_t *ciphertext) {
    *ciphertext = plaintext ^ key; 
}
void sdesDecrypt(uint8_t ciphertext, uint8_t key, uint8_t *plaintext) {
    *plaintext = ciphertext ^ key; 
}
void encryptCBC(uint8_t *plaintext, uint8_t key, uint8_t iv, uint8_t *ciphertext, int num_blocks) {
    uint8_t previous = iv;

    for (int i = 0; i < num_blocks; i++) {
        uint8_t input = plaintext[i] ^ previous; 
        sdesEncrypt(input, key, &ciphertext[i]);
        previous = ciphertext[i]; 
    }
}
void decryptCBC(uint8_t *ciphertext, uint8_t key, uint8_t iv, uint8_t *plaintext, int num_blocks) {
    uint8_t previous = iv;
	for (int i = 0; i < num_blocks; i++) {
        uint8_t decrypted_block;
        sdesDecrypt(ciphertext[i], key, &decrypted_block);
        plaintext[i] = decrypted_block ^ previous; 
        previous = ciphertext[i]; 
    }
}
int main() {
    uint8_t plaintext[] = {0x01, 0x23}; 
    uint8_t key = 0xFD;                
    uint8_t iv = 0xAA;                 
    uint8_t ciphertext[sizeof(plaintext)];
    uint8_t decrypted[sizeof(plaintext)];
    int num_blocks = sizeof(plaintext);
	printf("Plaintext: ");
    for (int i = 0; i < num_blocks; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");
	encryptCBC(plaintext, key, iv, ciphertext, num_blocks);
	printf("Ciphertext: ");
    for (int i = 0; i < num_blocks; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
	decryptCBC(ciphertext, key, iv, decrypted, num_blocks);
	printf("Decrypted: ");
    for (int i = 0; i < num_blocks; i++) {
        printf("%02X ", decrypted[i]);
    }
    printf("\n");

    return 0;
}

