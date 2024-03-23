#include <stdio.h>
#include <string.h>

void printString(char Str[], int K) {
    char plaintext[5][100];
    int freq[26] = {0};
    int freqSorted[26];
    int Used[26] = {0};

    for (int i = 0; i < K; i++) {
        if (Str[i] != ' ') {
            freq[Str[i] - 'A']++;
        }
    }

    for (int i = 0; i < 26; i++) {
        freqSorted[i] = freq[i];
    }

    char T[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

    for (int i = 0; i < 5; i++) {
        int ch = -1;
        for (int j = 0; j < 26; j++) {
            if (freqSorted[i] == freq[j] && Used[j] == 0) {
                Used[j] = 1;
                ch = j;
                break;
            }
        }
        if (ch == -1) break;

        int x = T[i] - 'A' - ch;

        for (int k = 0; k < K; k++) {
            if (Str[k] == ' ') {
                plaintext[i][k] = ' ';
                continue;
            }
            int y = Str[k] - 'A' + x;
            if (y < 0) y += 26;
            if (y > 25) y -= 26;
            plaintext[i][k] = 'A' + y;
        }
        plaintext[i][K] = '\0';
    }

    for (int i = 0; i < 5; i++) {
        printf("Plaintext %d: %s\n", i + 1, plaintext[i]);
    }
}

int main() {
    char ciphertext[] = "asdfghjklpiyrwqwertyuiopmnbv";
    int N = strlen(ciphertext);
    printString(ciphertext, N);
    return 0;
}

