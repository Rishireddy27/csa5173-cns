#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define ALPHABET_SIZE 26
#define MAX_TEXT_SIZE 1000
const char english_freq_order[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
void decrypt(const char *ciphertext, const char *mapping, char *plaintext) {
    for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            int index = toupper(ciphertext[i]) - 'A';
            plaintext[i] = mapping[index];  
            if (islower(ciphertext[i])) plaintext[i] = tolower(plaintext[i]);
        } else {
            plaintext[i] = ciphertext[i];  
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}
void sort_by_frequency(int *freq, char *sorted) {
    int index[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        index[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (freq[index[i]] < freq[index[j]]) {
                int temp = index[i];
                index[i] = index[j];
                index[j] = temp;
            }
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted[i] = 'A' + index[i];
    }
}
int main() {
    char ciphertext[MAX_TEXT_SIZE], sorted[ALPHABET_SIZE], mapping[ALPHABET_SIZE];
    int freq[ALPHABET_SIZE] = {0}, n;
	printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  
	printf("Enter number of top results: ");
    scanf("%d", &n);
	for (int i = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            freq[toupper(ciphertext[i]) - 'A']++;
        }
    }
	sort_by_frequency(freq, sorted);
	for (int i = 0; i < ALPHABET_SIZE; i++) {
        
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            mapping[sorted[j] - 'A'] = english_freq_order[(j + i) % ALPHABET_SIZE];
        }
		char plaintext[MAX_TEXT_SIZE];
        decrypt(ciphertext, mapping, plaintext);
        printf("Decrypted (shift %d): %s\n", i, plaintext);
    }

    return 0;
}

