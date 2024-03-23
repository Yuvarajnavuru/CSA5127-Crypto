#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to perform a letter frequency attack on an additive cipher
void frequencyAttack(char *ciphertext, int key, int topN) {
    int len = strlen(ciphertext);
    int i, j;
    char possiblePlaintext[len + 1];
    int frequencies[26] = {0};
    int maxFrequencyIndex;
    int decryptedChar;

    // Count the frequencies of letters in the ciphertext
    for (i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            frequencies[tolower(ciphertext[i]) - 'a']++;
        }
    }

    // Perform frequency analysis to find the most likely plaintexts
    for (i = 0; i < topN; i++) {
        maxFrequencyIndex = 0;

        // Find the most frequent letter in the ciphertext
        for (j = 1; j < 26; j++) {
            if (frequencies[j] > frequencies[maxFrequencyIndex]) {
                maxFrequencyIndex = j;
            }
        }

        // Calculate the decrypted character using the most frequent letter
        decryptedChar = (maxFrequencyIndex - ('e' - 'a') - key + 26) % 26 + 'a';

        // Decrypt the ciphertext using the key
        for (j = 0; j < len; j++) {
            if (isalpha(ciphertext[j])) {
                possiblePlaintext[j] = (tolower(ciphertext[j]) - 'a' - key + 26) % 26 + 'a';
                if (isupper(ciphertext[j])) {
                    possiblePlaintext[j] = toupper(possiblePlaintext[j]);
                }
            } else {
                possiblePlaintext[j] = ciphertext[j];
            }
        }
        possiblePlaintext[len] = '\0';

        // Print the decrypted plaintext along with its likelihood
        printf("Likelihood: %d | Possible Plaintext: %s\n", frequencies[maxFrequencyIndex], possiblePlaintext);

        // Set the frequency of the most frequent letter to 0 to find the next most frequent
        frequencies[maxFrequencyIndex] = 0;
    }
}

int main() {
    char ciphertext[] = "Lxo zw fvb xa hnabdn lc Lxo zbacrbg."; // Example ciphertext
    int key;
    int topN;

    // Get the additive key from the user
    printf("Enter the additive key (an integer between 0 and 25): ");
    scanf("%d", &key);

    // Get the number of top possible plaintexts from the user
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    // Perform frequency attack and print the top possible plaintexts
    frequencyAttack(ciphertext, key, topN);

    return 0;
}
