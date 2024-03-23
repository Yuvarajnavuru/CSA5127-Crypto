#include <stdio.h>

// Function to calculate the determinant of a 2x2 matrix
int determinant(int matrix[2][2]) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// Function to calculate the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Function to calculate the inverse of a 2x2 matrix modulo 26
void inverse(int matrix[2][2], int inv[2][2]) {
    int det = determinant(matrix);
    int detInverse = modInverse(det, 26);

    // Calculate the adjugate matrix
    inv[0][0] = matrix[1][1];
    inv[1][1] = matrix[0][0];
    inv[0][1] = -matrix[0][1];
    inv[1][0] = -matrix[1][0];

    // Apply modulo 26 and ensure positive values
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inv[i][j] = (inv[i][j] * detInverse) % 26;
            if (inv[i][j] < 0) {
                inv[i][j] += 26;
            }
        }
    }
}

// Function to multiply two 2x2 matrices modulo 26
void multiply(int A[2][2], int B[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
            result[i][j] %= 26;
        }
    }
}

int main() {
    // Known plaintext-ciphertext pairs
    int plaintext1[2] = {0, 3}; // "ad"
    int ciphertext1[2] = {15, 13}; // "po"
    int plaintext2[2] = {1, 4}; // "be"
    int ciphertext2[2] = {8, 9}; // "ij"

    // Calculate the key matrix
    int plaintextMatrix[2][2] = {{plaintext1[0], plaintext2[0]}, {plaintext1[1], plaintext2[1]}};
    int ciphertextMatrix[2][2] = {{ciphertext1[0], ciphertext2[0]}, {ciphertext1[1], ciphertext2[1]}};
    int inverseMatrix[2][2];

    inverse(plaintextMatrix, inverseMatrix);

    // Calculate the key matrix
    int keyMatrix[2][2];
    multiply(inverseMatrix, ciphertextMatrix, keyMatrix);

    // Print the key matrix
    printf("Recovered Key Matrix:\n");
    printf("%d %d\n", keyMatrix[0][0], keyMatrix[0][1]);
    printf("%d %d\n", keyMatrix[1][0], keyMatrix[1][1]);

    return 0;
}
