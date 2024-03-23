#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to decrypt a Playfair cipher message
void decryptPlayfair(char *ciphertext, char (*matrix)[5], char *plaintext) {
    int i, j, k = 0;
    char c1, c2;
    int row1, col1, row2, col2;

    for (i = 0; i < strlen(ciphertext); i += 2) {
        c1 = ciphertext[i];
        c2 = ciphertext[i + 1];

        // Find positions of characters in the matrix
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                if (matrix[j][k] == c1) {
                    row1 = j;
                    col1 = k;
                }
                if (matrix[j][k] == c2) {
                    row2 = j;
                    col2 = k;
                }
            }
        }

        // Decrypt based on the positions
        if (row1 == row2) {
            plaintext[i] = matrix[row1][(col1 - 1 + 5) % 5];
            plaintext[i + 1] = matrix[row2][(col2 - 1 + 5) % 5];
        } else if (col1 == col2) {
            plaintext[i] = matrix[(row1 - 1 + 5) % 5][col1];
            plaintext[i + 1] = matrix[(row2 - 1 + 5) % 5][col2];
        } else {
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[1000];
    char matrix[5][5] = {
        {'P', 'L', 'A', 'Y', 'F'},
        {'I', 'R', 'E', 'X', 'M'},
        {'B', 'C', 'D', 'G', 'H'},
        {'K', 'N', 'O', 'Q', 'S'},
        {'T', 'U', 'V', 'W', 'Z'}
    };
    char plaintext[1000];

    // Get the ciphertext from the user
    printf("Enter the ciphertext (without spaces): ");
    scanf("%s", ciphertext);

    // Decrypt the ciphertext using the Playfair cipher decryption function
    decryptPlayfair(ciphertext, matrix, plaintext);

    // Print the decrypted plaintext
    printf("Decrypted Plaintext: %s\n", plaintext);

    return 0;
}
