#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8 // Size of each block in bytes

// Function to perform ECB encryption
void ecbEncrypt(uint8_t *plaintext, uint8_t *key, int numBlocks) {
    printf("ECB Mode Encryption:\n");
    for (int i = 0; i < numBlocks; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i * BLOCK_SIZE + j] ^= key[j]; // XOR with the key
        }
        printf("Ciphertext Block %d: ", i + 1);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%02x ", plaintext[i * BLOCK_SIZE + j]);
        }
        printf("\n");
    }
}

// Function to perform CBC encryption
void cbcEncrypt(uint8_t *plaintext, uint8_t *key, uint8_t *iv, int numBlocks) {
    printf("\nCBC Mode Encryption:\n");
    uint8_t prevBlock[BLOCK_SIZE];
    memcpy(prevBlock, iv, BLOCK_SIZE); // Initialize previous block with IV
    for (int i = 0; i < numBlocks; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i * BLOCK_SIZE + j] ^= prevBlock[j]; // XOR with the previous block
        }
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i * BLOCK_SIZE + j] ^= key[j]; // XOR with the key
        }
        memcpy(prevBlock, &plaintext[i * BLOCK_SIZE], BLOCK_SIZE); // Update previous block
        printf("Ciphertext Block %d: ", i + 1);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%02x ", plaintext[i * BLOCK_SIZE + j]);
        }
        printf("\n");
    }
}

int main() {
    uint8_t plaintext[] = {0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f}; // "Hello Wo"
    uint8_t key[] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xab, 0xcd, 0xef};
    uint8_t iv[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Initialization Vector
    int numBlocks = sizeof(plaintext) / BLOCK_SIZE;

    // Display plaintext
    printf("Plaintext: ");
    for (int i = 0; i < BLOCK_SIZE * numBlocks; i++) {
        printf("%02x ", plaintext[i]);
    }
    printf("\n");

    // Encrypt in ECB mode
    ecbEncrypt(plaintext, key, numBlocks);

    // Encrypt in CBC mode
    cbcEncrypt(plaintext, key, iv, numBlocks);

    return 0;
}
