#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char plaintext[100], ciphertext[100];
    char key[26], completedKey[26], reverseKey[26];
    int choice;
    printf("Enter the substitution key (up to 26 letters): ");
    scanf("%s", key);
    int keyLength = strlen(key);
    int used[26] = {0}; 
    for (int i = 0; i < keyLength; i++) {
        key[i] = toupper(key[i]); 
        used[key[i] - 'A'] = 1;   
        completedKey[i] = key[i];
    }
    int idx = keyLength;
    for (int i = 0; i < 26; i++) {
        if (!used[i]) { 
            completedKey[idx++] = 'A' + i;
        }
    }
    completedKey[26] = '\0'; 
    for (int i = 0; i < 26; i++) {
        reverseKey[completedKey[i] - 'A'] = 'A' + i;
    }
    getchar();
    printf("Enter the text: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    printf("Choose an option:\n1. Encrypt\n2. Decrypt\n");
    scanf("%d", &choice);
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int index = plaintext[i] - base;
            if (choice == 1) {
                ciphertext[i] = isupper(plaintext[i]) ? completedKey[index] : tolower(completedKey[index]);
            } else if (choice == 2) {
                ciphertext[i] = isupper(plaintext[i]) ? reverseKey[index] : tolower(reverseKey[index]);
            }
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
    if (choice == 1) {
        printf("Encrypted text: %s\n", ciphertext);
    } else if (choice == 2) {
        printf("Decrypted text: %s\n", ciphertext);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}

