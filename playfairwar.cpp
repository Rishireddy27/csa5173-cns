#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
void generateKeyMatrix(char *key, char keyMatrix[SIZE][SIZE]) {
    int used[26] = {0};
    int x = 0, y = 0;
	for (int i = 0; key[i] != '\0'; i++) {
        if (toupper(key[i]) == 'J') {
            key[i] = 'I';
        }
    }
	for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (!used[ch - 'A']) {
            keyMatrix[x][y] = ch;
            used[ch - 'A'] = 1;
            y++;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }
	for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; 
        if (!used[ch - 'A']) {
            keyMatrix[x][y] = ch;
            used[ch - 'A'] = 1;
            y++;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }
}
void findPosition(char keyMatrix[SIZE][SIZE], char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void decryptDigraph(char digraph[2], char keyMatrix[SIZE][SIZE], char *result) {
    int row1, col1, row2, col2;

    findPosition(keyMatrix, digraph[0], &row1, &col1);
    findPosition(keyMatrix, digraph[1], &row2, &col2);

    if (row1 == row2) {
        result[0] = keyMatrix[row1][(col1 + SIZE - 1) % SIZE];
        result[1] = keyMatrix[row2][(col2 + SIZE - 1) % SIZE];
    } else if (col1 == col2) {
        result[0] = keyMatrix[(row1 + SIZE - 1) % SIZE][col1];
        result[1] = keyMatrix[(row2 + SIZE - 1) % SIZE][col2];
    } else {
        result[0] = keyMatrix[row1][col2];
        result[1] = keyMatrix[row2][col1];
    }
}
void decryptPlayfair(char *ciphertext, char *key, char *plaintext) {
    char keyMatrix[SIZE][SIZE];
    generateKeyMatrix(key, keyMatrix);

    char digraph[2];
    int k = 0;

    for (int i = 0; i < strlen(ciphertext); i += 2) {
        if (isalpha(ciphertext[i]) && isalpha(ciphertext[i + 1])) {
            digraph[0] = toupper(ciphertext[i]);
            digraph[1] = toupper(ciphertext[i + 1]);
            decryptDigraph(digraph, keyMatrix, &plaintext[k]);
            k += 2;
        }
    }
    plaintext[k] = '\0';
}

int main() {
    char key[100], ciphertext[500], plaintext[500];
	strcpy(key, "PTBOAT");
    strcpy(ciphertext, "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONECUZWRGDSONSXBOUYWRHEBAAHYUSEDQ");

    decryptPlayfair(ciphertext, key, plaintext);

    printf("Decrypted message: %s\n", plaintext);

    return 0;
}

