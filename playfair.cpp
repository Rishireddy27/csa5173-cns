#include <stdio.h>
#include <ctype.h>
#include <string.h>

void createPlayfairMatrix(char key[], char matrix[5][5]) {
    int used[26] = {0}; 
    int i, j, k = 0;
    int keyLength = strlen(key);
    for (i = 0; i < keyLength; i++) {
        key[i] = toupper(key[i]);
    }
    for (i = 0; i < keyLength; i++) {
        if (key[i] == 'J') {
            key[i] = 'I';  
        }
        if (key[i] != 'J' && !used[key[i] - 'A']) {
            matrix[k / 5][k % 5] = key[i];
            used[key[i] - 'A'] = 1;
            k++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (!used[i] && (i + 'A') != 'J') {
            matrix[k / 5][k % 5] = i + 'A';
            k++;
        }
    }
}

void preprocessPlaintext(char plaintext[], char processedText[]) {
    int i, j = 0;
    int length = strlen(plaintext);
	for (i = 0; i < length; i++) {
        if (isalpha(plaintext[i])) {
            processedText[j++] = toupper(plaintext[i]);
        }
    }
	if (j % 2 != 0) {
        processedText[j++] = 'X';
    }
    processedText[j] = '\0';  
}

void encryptPlayfair(char plaintext[], char ciphertext[], char matrix[5][5]) {
    int i, row1, col1, row2, col2;
    for (i = 0; plaintext[i] != '\0'; i += 2) {
        char char1 = plaintext[i];
        char char2 = plaintext[i + 1];
		for (row1 = 0; row1 < 5; row1++) {
            for (col1 = 0; col1 < 5; col1++) {
                if (matrix[row1][col1] == char1) {
                    break;
                }
            }
            if (col1 < 5) break;
        }

        for (row2 = 0; row2 < 5; row2++) {
            for (col2 = 0; col2 < 5; col2++) {
                if (matrix[row2][col2] == char2) {
                    break;
                }
            }
            if (col2 < 5) break;
        }
		if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % 5];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % 5];
        }
        else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % 5][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % 5][col2];
        }
        else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[i] = '\0';  
}
int main() {
    char key[100], plaintext[100], ciphertext[100], processedText[100];
    char matrix[5][5];
    int choice;
	printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  
	printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  
	createPlayfairMatrix(key, matrix);
	preprocessPlaintext(plaintext, processedText);
	encryptPlayfair(processedText, ciphertext, matrix);
	printf("Encrypted text: %s\n", ciphertext);
	return 0;
}

