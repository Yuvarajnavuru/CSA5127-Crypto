#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000


void encrypt(char *message, int *key, int key_length) {
    int i;
    for (i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            char base = islower(message[i]) ? 'a' : 'A';
            message[i] = ((message[i] - base) + key[i % key_length]) % 26 + base;
        }
    }
}

int main() {
    char plaintext[MAX_TEXT_LENGTH];
    int key[MAX_TEXT_LENGTH];
    int key_length, i;

    printf("Enter the plaintext: ");
    fgets(plaintext, MAX_TEXT_LENGTH, stdin);

    printf("Enter the key (space-separated numbers between 0 and 26): ");
    for (i = 0; scanf("%d", &key[i]) == 1; i++) {
        if (key[i] < 0 || key[i] > 26) {
            printf("Invalid key! Key elements must be between 0 and 26.\n");
            return 1;
        }
    }
    key_length = i;

    encrypt(plaintext, key, key_length);

    printf("Encrypted message: %s\n", plaintext);

    return 0;
}

