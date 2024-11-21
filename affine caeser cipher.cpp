#include <stdio.h>
#include <ctype.h>
#include <string.h>

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
void affineEncrypt(char *plaintext, int a, int b) {
    int i = 0;
    while (plaintext[i] != '\0') {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            int p = plaintext[i] - base;  
            int c = (a * p + b) % 26;  
            plaintext[i] = c + base;    
        }
        i++;
    }
}
void affineDecrypt(char *ciphertext, int a, int b) {
    int i = 0;
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("No modular inverse found for 'a'. Decryption is not possible.\n");
        return;
    }
    while (ciphertext[i] != '\0') {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int c = ciphertext[i] - base;  
            int p = (a_inv * (c - b + 26)) % 26;  
            ciphertext[i] = p + base;  
        }
        i++;
    }
}

int main() {
    char text[100];
    int a, b;
	printf("Enter the value of a (should be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);
	if (modInverse(a, 26) == -1) {
        printf("Invalid 'a'. It must be coprime with 26.\n");
        return 1;
    }
	getchar();  
    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';  
	affineEncrypt(text, a, b);
    printf("Encrypted text: %s\n", text);
	affineDecrypt(text, a, b);
    printf("Decrypted text: %s\n", text);
	return 0;
}

