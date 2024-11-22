#include <stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int modInverse(int e, int phi) {
    int t = 0, new_t = 1;
    int r = phi, new_r = e;
	while (new_r != 0) {
        int quotient = r / new_r;
        int temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;

        int temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }
	if (r > 1) return -1; 
    if (t < 0) t += phi;  

    return t;
}
int main() {
    int n = 3599, e = 31, p, q;
	for (p = 2; p < n; p++) {
        if (n % p == 0) {
            q = n / p;
            if (p * q == n) break;
        }
    }
	printf("Factors of n: p = %d, q = %d\n", p, q);
	int phi = (p - 1) * (q - 1);
    printf("phi(n) = %d\n", phi);
	int d = modInverse(e, phi);
    if (d == -1) {
        printf("Error: e and phi(n) are not coprime\n");
        return 1;
    }

    printf("The private key d = %d\n", d);

    return 0;
}
