#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt a message using the Hill cipher
void encryptHill(char *message, int key[2][2], char *ciphertext) {
    int len = strlen(message);
    int i, j, k;
    int matrix[2][1], result[2][1];

    for (i = 0; i < len; i += 2) {
        // Construct the matrix from the plaintext characters
        matrix[0][0] = message[i] - 'a';
        matrix[1][0] = message[i + 1] - 'a';

        // Perform matrix multiplication
        for (j = 0; j < 2; j++) {
            result[j][0] = 0;
            for (k = 0; k < 2; k++) {
                result[j][0] += key[j][k] * matrix[k][0];
            }
            result[j][0] %= 26; // Apply modulo 26
        }

        // Convert the result back to characters and store in ciphertext
        ciphertext[i] = result[0][0] + 'a';
        ciphertext[i + 1] = result[1][0] + 'a';
    }
    ciphertext[len] = '\0'; // Null-terminate the ciphertext
}

// Function to find the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Function to decrypt a message using the Hill cipher
void decryptHill(char *ciphertext, int key[2][2], char *plaintext) {
    int len = strlen(ciphertext);
    int i, j, k;
    int matrix[2][1], result[2][1];
    int inverseKey[2][2];

    // Calculate the modular inverse of the key
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    int detInverse = modInverse(det, 26);

    // Calculate the inverse key matrix
    inverseKey[0][0] = (key[1][1] * detInverse) % 26;
    inverseKey[0][1] = (-key[0][1] * detInverse) % 26;
    inverseKey[1][0] = (-key[1][0] * detInverse) % 26;
    inverseKey[1][1] = (key[0][0] * detInverse) % 26;

    // Ensure all elements are positive
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (inverseKey[i][j] < 0) {
                inverseKey[i][j] += 26;
            }
        }
    }

    for (i = 0; i < len; i += 2) {
        // Construct the matrix from the ciphertext characters
        matrix[0][0] = ciphertext[i] - 'a';
        matrix[1][0] = ciphertext[i + 1] - 'a';

        // Perform matrix multiplication with the inverse key
        for (j = 0; j < 2; j++) {
            result[j][0] = 0;
            for (k = 0; k < 2; k++) {
                result[j][0] += inverseKey[j][k] * matrix[k][0];
            }
            result[j][0] %= 26; // Apply modulo 26
        }

        // Convert the result back to characters and store in plaintext
        plaintext[i] = result[0][0] + 'a';
        plaintext[i + 1] = result[1][0] + 'a';
    }
    plaintext[len] = '\0'; // Null-terminate the plaintext
}

int main() {
    char message[] = "Simatsschoolofengineering";
    int key[2][2] = {{9, 4}, {5, 7}};
    char ciphertext[1000];
    char decryptedText[1000];

    // Encrypt the message using the Hill cipher
    encryptHill(message, key, ciphertext);

    // Print the encrypted ciphertext
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext using the Hill cipher
    decryptHill(ciphertext, key, decryptedText);

    // Print the decrypted plaintext
    printf("Decrypted Plaintext: %s\n", decryptedText);

    return 0;
}
