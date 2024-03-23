#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8 // Block size in bytes (64 bits)

// ECB Mode encryption
void ecbEncrypt(char *plaintext, char *key, int numBlocks) {
    printf("ECB Mode Encryption:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Encrypting Block %d\n", i + 1);
        // Perform encryption for each block (dummy operation)
        printf("Plaintext Block %d: %s\n", i + 1, plaintext + i * BLOCK_SIZE);
        printf("Key Used: %s\n", key);
        // Perform encryption operation here
        printf("Encrypted Block %d: EncryptedData\n", i + 1);
        printf("\n");
    }
}

// CBC Mode encryption
void cbcEncrypt(char *plaintext, char *key, int numBlocks) {
    printf("CBC Mode Encryption:\n");
    char previousCipherBlock[BLOCK_SIZE] = {0}; // Initialization vector (IV)
    for (int i = 0; i < numBlocks; i++) {
        printf("Encrypting Block %d\n", i + 1);
        // XOR plaintext with previous ciphertext block (or IV for the first block)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i * BLOCK_SIZE + j] ^= previousCipherBlock[j];
        }
        // Perform encryption for each block (dummy operation)
        printf("Plaintext Block %d: %s\n", i + 1, plaintext + i * BLOCK_SIZE);
        printf("Key Used: %s\n", key);
        // Perform encryption operation here
        printf("Encrypted Block %d: EncryptedData\n", i + 1);
        // Update previousCipherBlock with current ciphertext block
        memcpy(previousCipherBlock, plaintext + i * BLOCK_SIZE, BLOCK_SIZE);
        printf("\n");
    }
}

// CFB Mode encryption
void cfbEncrypt(char *plaintext, char *key, int numBlocks) {
    printf("CFB Mode Encryption:\n");
    char previousCipherBlock[BLOCK_SIZE] = {0}; // Initialization vector (IV)
    for (int i = 0; i < numBlocks; i++) {
        printf("Encrypting Block %d\n", i + 1);
        // Perform encryption for each block (dummy operation)
        printf("Plaintext Block %d: %s\n", i + 1, plaintext + i * BLOCK_SIZE);
        printf("Previous Cipher Block: %s\n", previousCipherBlock);
        printf("Key Used: %s\n", key);
        // XOR plaintext with the previous ciphertext block (or IV for the first block)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i * BLOCK_SIZE + j] ^= previousCipherBlock[j];
        }
        // Perform encryption operation here
        printf("Encrypted Block %d: EncryptedData\n", i + 1);
        // Update previousCipherBlock with current ciphertext block
        memcpy(previousCipherBlock, plaintext + i * BLOCK_SIZE, BLOCK_SIZE);
        printf("\n");
    }
}

int main() {
    char plaintext[] = "This is a test message for encryption purposes!";
    char key[] = "SecretKey";
    int numBlocks = strlen(plaintext) / BLOCK_SIZE;

    // Add padding if necessary
    int padding = BLOCK_SIZE - (strlen(plaintext) % BLOCK_SIZE);
    if (padding != BLOCK_SIZE) {
        memset(plaintext + strlen(plaintext), '0', padding);
        plaintext[strlen(plaintext) + padding] = '\0';
        numBlocks++;
    }

    // Perform encryption in different modes
    ecbEncrypt(plaintext, key, numBlocks);
    cbcEncrypt(plaintext, key, numBlocks);
    cfbEncrypt(plaintext, key, numBlocks);

    return 0;
}
