#include <stdio.h>
#include <string.h>

void frequency_attack(char ciphertext[]) {
    int shift, i;
    char plaintext[100];

    for (shift = 0; shift < 26; shift++) {
        for (i = 0; ciphertext[i] != '\0'; i++) {
            plaintext[i] = ((ciphertext[i] - 'a' - shift + 26) % 26) + 'a';
        }
        plaintext[i] = '\0';
        printf("Shift %d: %s\n", shift, plaintext);
    }
}

int main() {
    char ciphertext[] = "ymnxnxftaj";
    printf("Possible plaintexts:\n");
    frequency_attack(ciphertext);
    return 0;
}
