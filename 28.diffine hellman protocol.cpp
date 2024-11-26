#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long mod_exp(long base, long exp, long mod) {
    long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}
int main() {
    long a = 5;
    long q = 23;

    long xA = 6;
    long xB = 15;

    long A = mod_exp(a, xA, q);
    long B = mod_exp(a, xB, q);

    long keyA = mod_exp(B, xA, q);
    long keyB = mod_exp(A, xB, q);

    printf("%ld %ld\n", a, q);
    printf("%ld %ld\n", xA, xB);
    printf("%ld %ld\n", A, B);
    printf("%ld %ld\n", keyA, keyB);

    return 0;
}

