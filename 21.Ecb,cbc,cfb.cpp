#include <stdio.h>
#include <string.h>
void xorBlock(unsigned char *block, unsigned char *key, int block_size) {
    for (int i = 0; i < block_size; i++) {
        block[i] ^= key[i % strlen((char *)key)];
    }
}
void encryptECB(unsigned char *plaintext, unsigned char *key, int block_size) {
    int len = strlen((char *)plaintext);
    unsigned char block[block_size];
	printf("ECB Encryption:\n");
    for (int i = 0; i < len; i += block_size) {
        memcpy(block, plaintext + i, block_size);
        xorBlock(block, key, block_size);
        printf("%.*s", block_size, block);
    }
    printf("\n");
}
void decryptECB(unsigned char *ciphertext, unsigned char *key, int block_size) {
    int len = strlen((char *)ciphertext);
    unsigned char block[block_size];
	printf("ECB Decryption:\n");
    for (int i = 0; i < len; i += block_size) {
        memcpy(block, ciphertext + i, block_size);
        xorBlock(block, key, block_size);
        printf("%.*s", block_size, block);
    }
    printf("\n");
}
void encryptCBC(unsigned char *plaintext, unsigned char *key, unsigned char *iv, int block_size) {
    int len = strlen((char *)plaintext);
    unsigned char block[block_size];
    unsigned char previous[block_size];
	memcpy(previous, iv, block_size);
    printf("CBC Encryption:\n");
    for (int i = 0; i < len; i += block_size) {
        memcpy(block, plaintext + i, block_size);
        for (int j = 0; j < block_size; j++) {
            block[j] ^= previous[j];
        }
        xorBlock(block, key, block_size);
        memcpy(previous, block, block_size);
        printf("%.*s", block_size, block);
    }
    printf("\n");
}
void decryptCBC(unsigned char *ciphertext, unsigned char *key, unsigned char *iv, int block_size) {
    int len = strlen((char *)ciphertext);
    unsigned char block[block_size];
    unsigned char previous[block_size], temp[block_size];
	memcpy(previous, iv, block_size);
    printf("CBC Decryption:\n");
    for (int i = 0; i < len; i += block_size) {
        memcpy(temp, ciphertext + i, block_size);
        memcpy(block, ciphertext + i, block_size);
        xorBlock(block, key, block_size);
        for (int j = 0; j < block_size; j++) {
            block[j] ^= previous[j];
        }
        memcpy(previous, temp, block_size);
        printf("%.*s", block_size, block);
    }
    printf("\n");
}
void encryptCFB(unsigned char *plaintext, unsigned char *key, unsigned char *iv, int block_size) {
    int len = strlen((char *)plaintext);
    unsigned char block[block_size];
    unsigned char feedback[block_size];
	memcpy(feedback, iv, block_size);
    printf("CFB Encryption:\n");
    for (int i = 0; i < len; i += block_size) {
        memcpy(block, plaintext + i, block_size);
        xorBlock(feedback, key, block_size);
        for (int j = 0; j < block_size; j++) {
            feedback[j] = block[j] ^= feedback[j];
        }
        printf("%.*s", block_size, block);
    }
    printf("\n");
}
void decryptCFB(unsigned char *ciphertext, unsigned char *key, unsigned char *iv, int block_size) {
    int len = strlen((char *)ciphertext);
    unsigned char block[block_size];
    unsigned char feedback[block_size], temp[block_size];
	memcpy(feedback, iv, block_size);
    printf("CFB Decryption:\n");
    for (int i = 0; i < len; i += block_size) {
        memcpy(temp, ciphertext + i, block_size);
        xorBlock(feedback, key, block_size);
        for (int j = 0; j < block_size; j++) {
            block[j] = temp[j] ^ feedback[j];
            feedback[j] = temp[j];
        }
        printf("%.*s", block_size, block);
    }
    printf("\n");
}

int main() {
    unsigned char key[] = "SECRETKEY"; 
    unsigned char iv[] = "INITVECTOR"; 
    unsigned char plaintext[] = "HELLOWORLDHELLO"; 
    unsigned char ciphertext[64];
    int block_size = 8; 
	printf("Plaintext: %s\n\n", plaintext);
	encryptECB(plaintext, key, block_size);
    memcpy(ciphertext, plaintext, strlen((char *)plaintext)); 
    decryptECB(ciphertext, key, block_size);
	encryptCBC(plaintext, key, iv, block_size);
    memcpy(ciphertext, plaintext, strlen((char *)plaintext));
    decryptCBC(ciphertext, key, iv, block_size);
	encryptCFB(plaintext, key, iv, block_size);
    memcpy(ciphertext, plaintext, strlen((char *)plaintext));
    decryptCFB(ciphertext, key, iv, block_size);

    return 0;
}

