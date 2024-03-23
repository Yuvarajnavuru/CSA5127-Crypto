#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate a monoalphabetic cipher sequence using a keyword
void generateCipherSequence(char *keyword, char *cipherSequence) {
    int i, j;
    char key[26] = {0};

    // Convert the keyword to uppercase and remove duplicate letters
    for (i = 0; i < strlen(keyword); i++) {
        if (isalpha(keyword[i])) {
            keyword[i] = toupper(keyword[i]);
            if (key[keyword[i] - 'A'] == 0) {
                key[keyword[i] - 'A'] = 1;
            }
        }
    }

    // Fill in the remaining unused letters in normal order
    j = 0;
    for (i = 0; i < 26; i++) {
        if (key[i] == 0) {
            cipherSequence[j++] = 'A' + i;
        }
    }

    // Append the keyword to the cipher sequence
    strcat(cipherSequence, keyword);
}

// Function to encrypt a plaintext using a monoalphabetic cipher
void encrypt(char *plaintext, char *cipherSequence, char *ciphertext) {
    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            if (isupper(plaintext[i])) {
                ciphertext[i] = toupper(cipherSequence[plaintext[i] - 'A']);
            } else {
                ciphertext[i] = tolower(cipherSequence[plaintext[i] - 'a']);
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the ciphertext
}

int main() {
    char keyword[50];
    char plaintext[1000];
    char cipherSequence[26];
    char ciphertext[1000];

    // Get the keyword from the user
    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // Remove newline character

    // Get the plaintext from the user
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    // Generate the cipher sequence from the keyword
    generateCipherSequence(keyword, cipherSequence);

    // Encrypt the plaintext using the generated cipher sequence
    encrypt(plaintext, cipherSequence, ciphertext);

    // Print the encrypted ciphertext
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
