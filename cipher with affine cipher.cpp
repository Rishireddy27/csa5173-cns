#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MOD 26
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; 
}
char decryptChar(char c, int a_inv, int b) {
    if (isalpha(c)) {
        int y = toupper(c) - 'A';
        int x = (a_inv * (y - b + MOD)) % MOD;
        if (x < 0) x += MOD;
        return 'A' + x;
    }
    return c; 
}
void decrypt(char *ciphertext, int a, int b) {
    int a_inv = modInverse(a, MOD);
    if (a_inv == -1) {
        printf("Error: a (%d) does not have a modular inverse under mod %d.\n", a, MOD);
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        ciphertext[i] = decryptChar(ciphertext[i], a_inv, b);
    }
}
int main() {
    int x1 = 1, y1 = 4; 
    int x2 = 20, y2 = 19; 
	int a = (y1 - y2 + MOD) * modInverse(x1 - x2 + MOD, MOD) % MOD;
    if (a < 0) a += MOD;
	int b = (y1 - a * x1) % MOD;
    if (b < 0) b += MOD;
	printf("Keys found: a = %d, b = %d\n", a, b);
	char ciphertext[] = "BUNBUVKJNBUBULVNB";
	decrypt(ciphertext, a, b);
    printf("Decrypted text: %s\n", ciphertext);

    return 0;
}

