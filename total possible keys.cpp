#include <stdio.h>
#include <math.h>

double factorial(int n) {
    if (n == 0 || n == 1) return 1.0;
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
int main() {
    int num_characters = 25;
    double total_permutations = factorial(num_characters);
    double total_permutations_log2 = log2(total_permutations);
	printf("Total possible Playfair keys (approx): 2^%.2f\n", total_permutations_log2);
	double effective_keys_log2 = 49.4;
    printf("Effective unique Playfair keys (approx): 2^%.2f\n", effective_keys_log2);

    return 0;
}

