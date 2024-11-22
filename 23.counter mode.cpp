#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 8
void sdesEncrypt(uint8_t plaintext, uint8_t key, uint8_t *ciphertext) {
    *ciphertext = plaintext ^ key; 
}
void encryptCTR(uint8_t *plaintext, uint8_t key, uint8_t counter, uint8_t *ciphertext, int num_blocks) {
    for (int i = 0; i < num_blocks; i++) {
        uint8_t encrypted_counter;
        sdesEncrypt(counter, key, &encrypted_counter); 
        ciphertext[i] = plaintext[i] ^ encrypted_counter; 
        counter++; 
    }
}
void decryptCTR(uint8_t *ciphertext, uint8_t key, uint8_t counter, uint8_t *plaintext, int num_blocks) {
    for (int i = 0; i < num_blocks; i++) {
        uint8_t encrypted_counter;
        sdesEncrypt(counter, key, &encrypted_counter); 
        plaintext[i] = ciphertext[i] ^ encrypted_counter; 
        counter++; 
    }
}
int main() {
	uint8_t plaintext[] = {0x01, 0x02, 0x04}; 
    uint8_t key = 0xFD;                      
    uint8_t counter = 0x00;                 
    uint8_t ciphertext[sizeof(plaintext)];
    uint8_t decrypted[sizeof(plaintext)];
    int num_blocks = sizeof(plaintext);
	printf("Plaintext: ");
    for (int i = 0; i < num_blocks; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");
	encryptCTR(plaintext, key, counter, ciphertext, num_blocks);
	printf("Ciphertext: ");
    for (int i = 0; i < num_blocks; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
	decryptCTR(ciphertext, key, counter, decrypted, num_blocks);
	printf("Decrypted: ");
    for (int i = 0; i < num_blocks; i++) {
        printf("%02X ", decrypted[i]);
    }
    printf("\n");

    return 0;
}

