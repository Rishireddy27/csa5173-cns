#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
long gcd(long a, long b) {
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
long mod_inverse(long e, long phi) {
    long t = 0, new_t = 1, r = phi, new_r = e, quotient, temp;
    while (new_r != 0) {
        quotient = r / new_r;
        temp = new_t;
        new_t = t - quotient * new_t;
        t = temp;
        temp = new_r;
        new_r = r - quotient * new_r;
        r = temp;
    }
    if (r > 1) return -1;
    if (t < 0) t += phi;
    return t;
}
long mod_exp(long base, long exp, long mod) {
    long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
void generate_keys(long *n, long *e, long *d) {
    long p = 61, q = 53;
    *n = p * q;
    long phi = (p - 1) * (q - 1);
	*e = 17;
    while (gcd(*e, phi) != 1) (*e)++;
	*d = mod_inverse(*e, phi);
}
void encrypt_message(const char *message, long e, long n, long *ciphertext) {
    for (size_t i = 0; i < strlen(message); i++) {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            long m = message[i] - 'A';
            ciphertext[i] = mod_exp(m, e, n);
        } else {
            ciphertext[i] = -1; 
        }
    }
}
void decrypt_message(const long *ciphertext, size_t len, long d, long n, char *message) {
    for (size_t i = 0; i < len; i++) {
        if (ciphertext[i] != -1) {
            long m = mod_exp(ciphertext[i], d, n);
            message[i] = m + 'A';
        } else {
            message[i] = ' ';
        }
    }
    message[len] = '\0';
}
int main() {
    long n, e, d;
    generate_keys(&n, &e, &d);
	char message[] = "HELLO";
    long ciphertext[sizeof(message)];
    char decrypted_message[sizeof(message)];
	encrypt_message(message, e, n, ciphertext);
    decrypt_message(ciphertext, strlen(message), d, n, decrypted_message);
	printf("Original message: %s\n", message);
    printf("Encrypted message: ");
    for (size_t i = 0; i < strlen(message); i++) {
        printf("%ld ", ciphertext[i]);
    }
    printf("\nDecrypted message: %s\n", decrypted_message);

    return 0;
}

