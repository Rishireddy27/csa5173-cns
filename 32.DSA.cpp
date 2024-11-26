#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

uint64_t mod_exp(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

uint64_t mod_inverse(uint64_t a, uint64_t q) {
    uint64_t q0 = q, t, y = 0, x = 1;
    while (a > 1) {
        uint64_t quotient = a / q;
        t = q;
        q = a % q;
        a = t;
        t = y;
        y = x - quotient * y;
        x = t;
    }
    if (x < 0)
        x += q0;
    return x;
}

void generate_dsa_signature(uint64_t p, uint64_t q, uint64_t g, uint64_t x, uint64_t h, uint64_t k, uint64_t *r, uint64_t *s) {
    *r = mod_exp(g, k, p) % q;
    uint64_t k_inv = mod_inverse(k, q);
    *s = (k_inv * (h + x * (*r))) % q;
}

int main() {
    uint64_t p = 23, q = 11, g = 2;
    uint64_t x = 5;
    uint64_t y = mod_exp(g, x, p);
    uint64_t message_hash = 9;
    uint64_t k1, k2, r1, s1, r2, s2;

    srand(time(NULL));
    k1 = rand() % (q - 1) + 1;
    k2 = rand() % (q - 1) + 1;

    generate_dsa_signature(p, q, g, x, message_hash, k1, &r1, &s1);
    generate_dsa_signature(p, q, g, x, message_hash, k2, &r2, &s2);

    printf("Message Hash: %llu\n", message_hash);
    printf("Signature 1: r = %llu, s = %llu (k = %llu)\n", r1, s1, k1);
    printf("Signature 2: r = %llu, s = %llu (k = %llu)\n", r2, s2, k2);

    return 0;
}

