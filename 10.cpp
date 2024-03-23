#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to find the row and column of a character in the Playfair matrix
void findPosition(char (*matrix)[5], char ch, int *row, int *col) {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (matrix[i][j] == ch || (matrix[i][j] == 'I' && ch == 'J')) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a plaintext using the Playfair cipher
void encryptPlayfair(char *plaintext, char (*matrix)[5], char *ciphertext) {
    int len = strlen(plaintext);
    int i, row1, col1, row2, col2;
    int index = 0;

    for (i = 0; i < len; i += 2) {
        // Find positions of the two characters in the matrix
        findPosition(matrix, plaintext[i], &row1, &col1);
        findPosition(matrix, plaintext[i + 1], &row2, &col2);

        // If both characters are in the same row
        if (row1 == row2) {
            ciphertext[index++] = matrix[row1][(col1 + 1) % 5];
            ciphertext[index++] = matrix[row2][(col2 + 1) % 5];
        }
        // If both characters are in the same column
        else if (col1 == col2) {
            ciphertext[index++] = matrix[(row1 + 1) % 5][col1];
            ciphertext[index++] = matrix[(row2 + 1) % 5][col2];
        }
        // If they form a rectangle
        else {
            ciphertext[index++] = matrix[row1][col2];
            ciphertext[index++] = matrix[row2][col1];
        }
    }
    ciphertext[index] = '\0';
}

int main() {
    char matrix[5][5] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };
    char plaintext[1000];
    char ciphertext[1000];

    // Get the plaintext from the user
    printf("Enter the plaintext (in uppercase, without spaces): ");
    scanf("%s", plaintext);

    // Encrypt the plaintext using the Playfair cipher
    encryptPlayfair(plaintext, matrix, ciphertext);

    // Print the ciphertext
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    return 0;
}
