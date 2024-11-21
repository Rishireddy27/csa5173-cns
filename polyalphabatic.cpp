#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main() {
    char plaintext[100], ciphertext[100], key[100];
    int i, j = 0, keyLength, textLength;
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  
    keyLength = strlen(key);
    textLength = strlen(plaintext);
    for (i = 0; i < keyLength; i++) {
        key[i] = toupper(key[i]);
    }
    for (i = 0; i < textLength; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';  
            int keyIndex = toupper(key[j % keyLength]) - 'A';  
			ciphertext[i] = (plaintext[i] - base + keyIndex) % 26 + base;
			j++;
        } else {
            
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[i] = '\0';  
	printf("Encrypted text: %s\n", ciphertext);
	return 0;
}

