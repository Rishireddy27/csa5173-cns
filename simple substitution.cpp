#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 1024
void calculate_frequency(const char *ciphertext, int freq[256]) {
    for (int i = 0; i < 256; i++) freq[i] = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        freq[(unsigned char)ciphertext[i]]++;
    }
}
void display_frequency(int freq[256]) {
    printf("Character Frequency Analysis:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0 && isprint(i)) {
            printf("'%c' (%d): %d\n", i, i, freq[i]);
        }
    }
}
void substitute_characters(const char *ciphertext, const char *substitutions, char *decoded) {
    int map[256];
    for (int i = 0; i < 256; i++) map[i] = i; 
	for (int i = 0; substitutions[i] != '\0'; i += 2) {
        map[(unsigned char)substitutions[i]] = substitutions[i + 1];
    }
	for (int i = 0; ciphertext[i] != '\0'; i++) {
        decoded[i] = (char)map[(unsigned char)ciphertext[i]];
    }
    decoded[strlen(ciphertext)] = '\0';
}
int main() {
    const char ciphertext[] = "53‡‡†305))6*:4826)41.)41);806*;48+860))85;;]8*::$8+83 (88)5*4:46(;88*96?;8)(;485);5+2:(;4956*2(5*4)88\n"
                               "4069285);)6+8)4‡‡:1($9:48081;8:811;48485;4)485+528806*81 ($9;48;(88;4(†234;48)4;161;:188;12;";
    char decoded[MAX_LENGTH];
    int freq[256];
    char substitutions[256]; 
	printf("Ciphertext:\n%s\n\n", ciphertext);
	calculate_frequency(ciphertext, freq);
    display_frequency(freq);
	printf("\nEnter substitutions as pairs (e.g., '5e3t8h'), or 'q' to quit: ");
    while (1) {
        scanf("%s", substitutions);
        if (substitutions[0] == 'q') break;
        substitute_characters(ciphertext, substitutions, decoded);
        printf("Decoded text:\n%s\n", decoded);
    }

    printf("Exiting...\n");
    return 0;
}

