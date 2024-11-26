#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

void generate_key(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 26;
    }
}

void encrypt(const char *plaintext, char *ciphertext, int *key, int length) {
    for (int i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + key[i]) % 26 + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[length] = '\0';
}

void decrypt(const char *ciphertext, char *plaintext, int *key, int length) {
    for (int i = 0; i < length; i++) {
        if (isalpha(ciphertext[i])) {`
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - key[i] + 26) % 26 + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

int main() {
    char plaintext[256], ciphertext[256], decrypted[256];
    int key[256];
    int length;

    srand(time(NULL));

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    length = strlen(plaintext);
    if (plaintext[length - 1] == '\n') plaintext[--length] = '\0';

    generate_key(key, length);

    encrypt(plaintext, ciphertext, key, length);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, decrypted, key, length);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}

