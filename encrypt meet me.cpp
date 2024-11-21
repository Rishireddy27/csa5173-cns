#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 26
int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; 
}
int determinant_mod26(int matrix[2][2]) {
    int det = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    return (det % MOD + MOD) % MOD; 
}
void matrix_inverse_mod26(int matrix[2][2], int inv_matrix[2][2]) {
    int det = determinant_mod26(matrix);
    int det_inv = mod_inverse(det, MOD);
    if (det_inv == -1) {
        printf("Matrix is not invertible modulo 26\n");
        exit(1);
    }
	inv_matrix[0][0] = matrix[1][1] * det_inv % MOD;
    inv_matrix[0][1] = -matrix[0][1] * det_inv % MOD;
    inv_matrix[1][0] = -matrix[1][0] * det_inv % MOD;
    inv_matrix[1][1] = matrix[0][0] * det_inv % MOD;
	for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inv_matrix[i][j] = (inv_matrix[i][j] + MOD) % MOD;
        }
    }
}
void hill_encrypt(int key[2][2], char* plaintext, char* ciphertext) {
    int n = strlen(plaintext);
    for (int i = 0; i < n; i += 2) {
        int p1 = plaintext[i] - 'a';
        int p2 = plaintext[i + 1] - 'a';

        
        ciphertext[i] = (key[0][0] * p1 + key[0][1] * p2) % MOD + 'a';
        ciphertext[i + 1] = (key[1][0] * p1 + key[1][1] * p2) % MOD + 'a';
    }
    ciphertext[n] = '\0';
}
void hill_decrypt(int inv_key[2][2], char* ciphertext, char* plaintext) {
    int n = strlen(ciphertext);
    for (int i = 0; i < n; i += 2) {
        int c1 = ciphertext[i] - 'a';
        int c2 = ciphertext[i + 1] - 'a';
		plaintext[i] = (inv_key[0][0] * c1 + inv_key[0][1] * c2) % MOD + 'a';
        plaintext[i + 1] = (inv_key[1][0] * c1 + inv_key[1][1] * c2) % MOD + 'a';
    }
    plaintext[n] = '\0';
}

int main() {
    
    int key[2][2] = { {6, 5}, {7, 7} };
    int inv_key[2][2];
	matrix_inverse_mod26(key, inv_key);
	char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";
    int n = strlen(plaintext);
    if (n % 2 != 0) strcat(plaintext, "x"); 
	char ciphertext[100];
    hill_encrypt(key, plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
	char decryptedtext[100];
    hill_decrypt(inv_key, ciphertext, decryptedtext);
    printf("Decrypted Text: %s\n", decryptedtext);

    return 0;
}

