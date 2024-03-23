#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *plaintext, char *key, char *ciphertext) {
    int i, j;
    int keyLength = strlen(key);
    int plaintextLength = strlen(plaintext);

    for (i = 0, j = 0; i < plaintextLength; i++, j++) {
        if (j == keyLength)
            j = 0;

        // Determine if the character is uppercase or lowercase
        char shift;
        if (isupper(plaintext[i]))
            shift = 'A';
        else if (islower(plaintext[i]))
            shift = 'a';
        else {
            // If not a letter, simply append to ciphertext
            ciphertext[i] = plaintext[i];
            j--;
            continue;
        }

        // Apply the Caesar cipher with the corresponding key letter
        ciphertext[i] = ((plaintext[i] - shift + key[j] - 'A') % 26) + shift;
    }

    // Add null terminator to the ciphertext
    ciphertext[i] = '\0';
}

int main() {
    char plaintext[1000];
    char key[100];
    char ciphertext[1000];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);

    // Remove newline characters from inputs
    plaintext[strcspn(plaintext, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    encrypt(plaintext, key, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
