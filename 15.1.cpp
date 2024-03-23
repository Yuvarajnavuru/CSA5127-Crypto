#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// English letter frequency table
const float english_frequencies[ALPHABET_SIZE] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094,
    0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929,
    0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150,
    0.01974, 0.00074
};

// Function to decrypt the text using a key
void decrypt(const char *text, char *decrypted, int key) {
    int i;
    for (i = 0; text[i] != '\0'; ++i) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            decrypted[i] = ((text[i] - base - key) % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            decrypted[i] = text[i];
        }
    }
    decrypted[i] = '\0';
}

// Function to calculate the score of a plaintext based on letter frequency
float score_text(const char *text) {
    int letter_counts[ALPHABET_SIZE] = {0};
    int total_letters = 0;
    int i;

    // Count the frequency of each letter
    for (i = 0; text[i] != '\0'; ++i) {
        if (isalpha(text[i])) {
            char c = tolower(text[i]);
            letter_counts[c - 'a']++;
            total_letters++;
        }
    }

    // Calculate the score based on letter frequency
    float score = 0.0;
    for (i = 0; i < ALPHABET_SIZE; ++i) {
        score += (float)letter_counts[i] / total_letters * english_frequencies[i];
    }

    return score;
}

int main() {
    char encrypted_text[1000];
    printf("Enter the encrypted text: ");
    fgets(encrypted_text, sizeof(encrypted_text), stdin);

    int top_n;
    printf("Specify the number of top possible plaintexts to output: ");
    scanf("%d", &top_n);

    float best_scores[top_n];
    char best_texts[top_n][1000];
    int i, key;

    // Initialize best scores with negative values
    for (i = 0; i < top_n; ++i) {
        best_scores[i] = -9999999.0;
    }

    // Perform the letter frequency attack for all possible keys
    for (key = 1; key < ALPHABET_SIZE; ++key) {
        char decrypted_text[1000];
        decrypt(encrypted_text, decrypted_text, key);
        float score = score_text(decrypted_text);

        // Update top N scores and texts
        for (i = 0; i < top_n; ++i) {
            if (score > best_scores[i]) {
                memmove(best_scores + i + 1, best_scores + i, (top_n - i - 1) * sizeof(float));
                memmove(best_texts[i + 1], best_texts[i], (top_n - i - 1) * sizeof(char) * 1000);
                best_scores[i] = score;
                strcpy(best_texts[i], decrypted_text);
                break;
            }
        }
    }

    // Output the top N possible plaintexts
    printf("\nTop %d possible plaintexts:\n", top_n);
    for (i = 0; i < top_n; ++i) {
        printf("Plaintext %d (score %.2f): %s", i + 1, best_scores[i], best_texts[i]);
    }

    return 0;
}

