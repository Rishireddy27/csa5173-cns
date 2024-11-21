#include <stdio.h>
#include <string.h>
#include <ctype.h>
char shift_char(char ch, int shift, int is_encrypt) {
    if (is_encrypt) {
        return ((ch - 'a' + shift) % 26 + 26) % 26 + 'a';
    } else {
        return ((ch - 'a' - shift) % 26 + 26) % 26 + 'a';
    }
}
void vigenere_cipher(const char *text, const int *key_stream, int key_len, char *result, int is_encrypt) {
    int text_len = strlen(text);
    int key_index = 0;

    for (int i = 0; i < text_len; i++) {
        if (isalpha(text[i])) {
            result[i] = shift_char(tolower(text[i]), key_stream[key_index], is_encrypt);
            key_index = (key_index + 1) % key_len;
        } else {
            result[i] = text[i]; 
        }
    }
    result[text_len] = '\0';
}

int main() {
    const char plaintext[] = "send more money";
    int key_stream[] = {9, 0, 17, 23, 15, 21, 14, 11, 11, 2, 8, 9}; 
    int key_len = sizeof(key_stream) / sizeof(key_stream[0]);
    char ciphertext[100];
	vigenere_cipher(plaintext, key_stream, key_len, ciphertext, 1);
    printf("Ciphertext: %s\n", ciphertext);
	const char target_plaintext[] = "cash not needed";
    char new_key[100];

    for (int i = 0; i < strlen(target_plaintext); i++) {
        if (isalpha(target_plaintext[i])) {
            new_key[i] = ((tolower(ciphertext[i]) - 'a') - (tolower(target_plaintext[i]) - 'a') + 26) % 26 + 'a';
        } else {
            new_key[i] = ' ';
        }
    }
    new_key[strlen(target_plaintext)] = '\0';

    printf("New key to decrypt ciphertext to \"%s\": %s\n", target_plaintext, new_key);

    return 0;
}

