#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
char keyMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'J'},
    {'K', 'U', 'N', 'O', 'P'},
    {'Q', 'Z', 'V', 'W', 'X'},
    {'Y', 'E', 'L', 'A', 'R'},
    {'G', 'D', 'S', 'T', 'B'}
};
void findPosition(char ch, int *row, int *col) {
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
void prepareMessage(char *message, char *processedMessage) {
    int len = strlen(message);
    int k = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            char ch = toupper(message[i]);
            processedMessage[k++] = ch;
        }
    }
	for (int i = 0; i < k; i += 2) {
        if (processedMessage[i] == processedMessage[i + 1]) {
            for (int j = k; j > i + 1; j--) {
                processedMessage[j] = processedMessage[j - 1];
            }
            processedMessage[i + 1] = 'X';
            k++;
        }
    }
    if (k % 2 != 0) {
        processedMessage[k++] = 'X'; 
    }
    processedMessage[k] = '\0';
}
void encryptDigraph(char digraph[2], char *result) {
    int row1, col1, row2, col2;
	findPosition(digraph[0], &row1, &col1);
    findPosition(digraph[1], &row2, &col2);
	if (row1 == row2) {
        result[0] = keyMatrix[row1][(col1 + 1) % SIZE];
        result[1] = keyMatrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        result[0] = keyMatrix[(row1 + 1) % SIZE][col1];
        result[1] = keyMatrix[(row2 + 1) % SIZE][col2];
    } else {
        result[0] = keyMatrix[row1][col2];
        result[1] = keyMatrix[row2][col1];
    }
}
void encryptPlayfair(char *message, char *encryptedMessage) {
    char processedMessage[500];
    prepareMessage(message, processedMessage);

    int len = strlen(processedMessage);
    for (int i = 0; i < len; i += 2) {
        encryptDigraph(&processedMessage[i], &encryptedMessage[i]);
    }
    encryptedMessage[len] = '\0';
}

int main() {
    char message[500], encryptedMessage[500];
	printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0'; 
	encryptPlayfair(message, encryptedMessage);
	printf("Encrypted Message: %s\n", encryptedMessage);

    return 0;
}

