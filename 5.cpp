#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to check if 'a' is relatively prime to 'b'
int isRelativelyPrime(int a, int b) {
    return gcd(a, b) == 1;
}

// Function to encrypt a character using the affine Caesar cipher
char encrypt(char ch, int a, int b) {
    if (isalpha(ch)) {
        if (isupper(ch)) {
            return ((a * (ch - 'A') + b) % 26) + 'A';
        } else {
            return ((a * (ch - 'a') + b) % 26) + 'a';
        }
    } else {
        return ch; // If the character is not a letter, return it unchanged
    }
}

int main() {
    char plaintext[1000], ciphertext[1000];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Removing newline character

    printf("Enter the value of 'a' (must be relatively prime to 26): ");
    scanf("%d", &a);

    // Check if 'a' is relatively prime to 26
    if (!isRelativelyPrime(a, 26)) {
        printf("Error: 'a' must be relatively prime to 26.\n");
        return 1; // Exit with error code 1
    }

    printf("Enter the value of 'b': ");
    scanf("%d", &b);

    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        ciphertext[i] = encrypt(plaintext[i], a, b);
    }
    ciphertext[len] = '\0'; // Null-terminate the ciphertext

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
