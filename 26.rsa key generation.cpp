#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
long encrypt(long message, long e, long n) {
    return mod_exp(message, e, n);
}
long decrypt(long ciphertext, long d, long n) {
    return mod_exp(ciphertext, d, n);
}
int main() {
    long n, e, d;
    generate_keys(&n, &e, &d);
	long message = 42; 
    long ciphertext = encrypt(message, e, n);
    long decrypted_message = decrypt(ciphertext, d, n);
	printf("Original message: %ld\n", message);
    printf("Encrypted message: %ld\n", ciphertext);
    printf("Decrypted message: %ld\n", decrypted_message);
	return 0;
}

