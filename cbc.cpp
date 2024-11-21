#include <stdio.h>
#include <string.h>
#include <openssl/des.h>
#include <openssl/evp.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 24

// Function to perform CBC encryption using 3DES
void cbc_encrypt_3des(const unsigned char *plaintext, int plaintext_len,
                      const unsigned char *key, const unsigned char *iv,
                      unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    // Create and initialize the context
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        printf("Error creating context\n");
        return;
    }

    // Initialize the 3DES cipher in CBC mode
    if (1 != EVP_EncryptInit_ex(ctx, EVP_des_ede3_cbc(), NULL, key, iv)) {
        printf("Error initializing cipher\n");
        return;
    }

    // Perform the encryption
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
        printf("Error encrypting\n");
        return;
    }
    ciphertext_len = len;

    // Finalize encryption
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        printf("Error finalizing encryption\n");
        return;
    }
    ciphertext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
}

// Function to print the ciphertext in hexadecimal format
void print_hex(const unsigned char *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char key[KEY_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                                   0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
                                   0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
    unsigned char iv[BLOCK_SIZE] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};  // Initialization Vector
    unsigned char plaintext[] = "This is a test message for CBC mode encryption using 3DES!";
    unsigned char ciphertext[128];  // Array to store the ciphertext

    printf("Plaintext: %s\n", plaintext);
    
    // Perform encryption
    cbc_encrypt_3des(plaintext, strlen((const char *)plaintext), key, iv, ciphertext);

    printf("Ciphertext: ");
    print_hex(ciphertext, strlen((const char *)plaintext) + BLOCK_SIZE);

    return 0;
}

