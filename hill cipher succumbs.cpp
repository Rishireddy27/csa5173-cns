#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void recover_key(int plaintext[2][2], int ciphertext[2][2], int key[2][2]) {
    int inv_plaintext[2][2];
    matrix_inverse_mod26(plaintext, inv_plaintext);
	for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            key[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                key[i][j] += ciphertext[i][k] * inv_plaintext[k][j];
            }
            key[i][j] = key[i][j] % MOD;
        }
    }
}

int main() {
	int plaintext[2][2] = { {7, 4}, {11, 14} }; 
    int ciphertext[2][2] = { {11, 14}, {19, 7} }; 
	int key[2][2];
	recover_key(plaintext, ciphertext, key);
	printf("Recovered Key Matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    return 0;
}

