#include <stdio.h>
#include <ctype.h>
int main() {
    char text[100];
    int k, choice;
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the shift value (1-25): ");
    scanf("%d", &k);
    printf("Choose an option:\n1. Encrypt\n2. Decrypt\n");
    scanf("%d", &choice);
    if (choice == 2) {
        k = -k;
    } else if (choice != 1) {
        printf("Invalid choice.\n");
        return 1;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + k + 26) % 26 + base; 
        }
    }
    if (choice == 1) {
        printf("Encrypted text: %s\n", text);
    } else {
        printf("Decrypted text: %s\n", text);
    }

    return 0;
}

