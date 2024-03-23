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

// Function to find the modular multiplicative inverse of a number 'a' modulo 'm'
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

// Function to decrypt a character using the affine cipher
char decrypt(char ch, int a, int b) {
    if (isupper(ch)) {
        return (((modInverse(a, 26) * ((ch - 'A') - b)) + 26) % 26) + 'A';
    } else if (islower(ch)) {
        return (((modInverse(a, 26) * ((ch - 'a') - b)) + 26) % 26) + 'a';
    } else {
        return ch; // If the character is not a letter, return it unchanged
    }
}

int main() {
    char ciphertext[1000];
    int frequency[26] = {0};

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Removing newline character

    // Count the frequency of each letter in the ciphertext
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            frequency[tolower(ciphertext[i]) - 'a']++;
        }
    }

    // Determine the most frequent letter
    int maxFrequency = 0, maxIndex;
    for (int i = 0; i < 26; i++) {
        if (frequency[i] > maxFrequency) {
            maxFrequency = frequency[i];
            maxIndex = i;
        }
    }

    // Assume 'B' is mapped to 'E' (most frequent letter) and 'U' is mapped to 'T' (second most frequent letter)
    // We find the key 'a' by finding the distance between 'B' and 'E' modulo 26, and similarly for 'U' and 'T'
    int keyA = (maxIndex - ('E' - 'a') + 26) % 26; // Modulo 26 to handle negative values
    int keyB = (tolower('B') - 'a' - (keyA * ('E' - 'a'))) % 26;

    // Decrypt the ciphertext using the deduced key
    printf("Deduced Key (a, b): (%d, %d)\n", keyA, keyB);
    printf("Decrypted Text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        printf("%c", decrypt(ciphertext[i], keyA, keyB));
    }
    printf("\n");

    return 0;
}
