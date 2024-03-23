#include <stdio.h>
#include <stdint.h>

#define IP_SIZE 64
#define SUBKEY_SIZE 48

// Initial permutation table
int IP[IP_SIZE] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Key permutation table
int key_permutation[56] = {
    57, 49, 41, 33, 25, 17, 9, 1,
    58, 50, 42, 34, 26, 18, 10, 2,
    59, 51, 43, 35, 27, 19, 11, 3,
    60, 52, 44, 36, 63, 55, 47, 39,
    31, 23, 15, 7, 62, 54, 46, 38,
    30, 22, 14, 6, 61, 53, 45, 37,
    29, 21, 13, 5, 28, 20, 12, 4
};

// Key shift schedule
int key_shifts[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// Subkey permutation table
int subkey_permutation[SUBKEY_SIZE] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

// Function to perform initial permutation
void initial_permutation(uint64_t *data) {
    uint64_t result = 0;
    for (int i = 0; i < IP_SIZE; i++) {
        result |= ((*data >> (IP_SIZE - IP[i])) & 1) << (IP_SIZE - i - 1);
    }
    *data = result;
}

// Function to generate round keys
void generate_round_keys(uint64_t key) {
    // Apply initial key permutation
    uint64_t permuted_key = 0;
    for (int i = 0; i < 56; i++) {
        permuted_key |= ((key >> (64 - key_permutation[i])) & 1) << (55 - i);
    }

    // Split into left and right halves
    uint32_t left = permuted_key >> 28;
    uint32_t right = permuted_key & 0x0FFFFFFF;

    // Generate round keys
    for (int i = 0; i < 16; i++) {
        // Perform left circular shift
        left = ((left << key_shifts[i]) | (left >> (28 - key_shifts[i]))) & 0x0FFFFFFF;
        right = ((right << key_shifts[i]) | (right >> (28 - key_shifts[i]))) & 0x0FFFFFFF;

        // Merge left and right halves
        uint64_t merged_key = ((uint64_t)left << 28) | right;

        // Apply subkey permutation
        uint64_t round_key = 0;
        for (int j = 0; j < SUBKEY_SIZE; j++) {
            round_key |= ((merged_key >> (56 - subkey_permutation[j])) & 1) << (47 - j);
        }

        // Output the round key
        printf("Round Key %2d: %012lX\n", i + 1, round_key);
    }
}

int main() {
    uint64_t key = 0x133457799BBCDFF1; // Example key
    printf("Original Key: %016lX\n", key);
    initial_permutation(&key);
    printf("Permuted Key: %016lX\n", key);
    generate_round_keys(key);
    return 0;
}

