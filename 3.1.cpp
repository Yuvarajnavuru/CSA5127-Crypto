#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepareKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]) {
    int i, j, k;
    char alphabet[26] = {'A','B','C','D','E','F','G','H','I','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int len = strlen(key);

    for (i = 0, k = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; ) {
            if (k < len) {
                keyMatrix[i][j++] = toupper(key[k]);
                for (int x = 0; x < 26; x++) {
                    if (key[k] == alphabet[x]) {
                        alphabet[x] = 0;
                    }
                }
            } else {
                int flag = 0;
                while (alphabet[flag] == 0) {
                    flag++;
                }
                keyMatrix[i][j++] = alphabet[flag];
                for (int x = 0; x < 26; x++) {
                    if (alphabet[flag] == alphabet[x]) {
                        alphabet[x] = 0;
                    }
                }
            }
            k++;
        }
    }
}

void findPosition(char keyMatrix[SIZE][SIZE], char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I';

    for (*row = 0; *row < SIZE; (*row)++) {
        for (*col = 0; *col < SIZE; (*col)++) {
            if (keyMatrix[*row][*col] == ch)
                return;
        }
    }
}

void encrypt(char keyMatrix[SIZE][SIZE], char digraph[2], char encryptedDigraph[2]) {
    int row1, row2, col1, col2;

    findPosition(keyMatrix, digraph[0], &row1, &col1);
    findPosition(keyMatrix, digraph[1], &row2, &col2);

    if (row1 == row2) {
        encryptedDigraph[0] = keyMatrix[row1][(col1 + 1) % SIZE];
        encryptedDigraph[1] = keyMatrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        encryptedDigraph[0] = keyMatrix[(row1 + 1) % SIZE][col1];
        encryptedDigraph[1] = keyMatrix[(row2 + 1) % SIZE][col2];
    } else {
        encryptedDigraph[0] = keyMatrix[row1][col2];
        encryptedDigraph[1] = keyMatrix[row2][col1];
    }
}

int main() {
    char key[100], plaintext[1000], keyMatrix[SIZE][SIZE], encryptedDigraph[2];
    int i, j;

    printf("Enter the key: ");
    scanf("%s", key);

    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    prepareKeyMatrix(key, keyMatrix);

    printf("Key matrix:\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%c ", keyMatrix[i][j]);
        }
        printf("\n");
    }

    printf("Encrypted text: ");
    for (i = 0; i < strlen(plaintext); i += 2) {
        encrypt(keyMatrix, plaintext + i, encryptedDigraph);
        printf("%c%c", encryptedDigraph[0], encryptedDigraph[1]);
    }

    return 0;
}
