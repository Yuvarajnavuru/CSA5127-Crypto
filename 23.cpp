#include <stdio.h>

// S-DES functions and tables
void generate_key_stream(int counter, char key_stream[]);
void sdes_encrypt(char plaintext[], char key[], char ciphertext[]);
void sdes_decrypt(char ciphertext[], char key[], char decrypted[]);

// Helper function to convert binary strings to integers
int binary_to_decimal(char binary[]);

int main() {
    char plaintext[] = "000000010000001000000100"; // 0000 0001 0000 0010 0000 0100
    char key[] = "0111111101"; // Binary key: 01111 11101
    char ciphertext[25];
    char decrypted[25];

    // Encryption
    sdes_encrypt(plaintext, key, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);

    // Decryption
    sdes_decrypt(ciphertext, key, decrypted);
    printf("Decrypted plaintext: %s\n", decrypted);

    return 0;
}

void generate_key_stream(int counter, char key_stream[]) {
    // Generate key stream using counter mode
    int i;
    for (i = 0; i < 24; i++) {
        key_stream[i] = ((counter >> i) & 1) + '0';
    }
    key_stream[24] = '\0'; // Null-terminate the string
}

void sdes_encrypt(char plaintext[], char key[], char ciphertext[]) {
    int i;
    char key_stream[25];
    int counter = 0;

    // Loop through each block of plaintext
    for (i = 0; i < 24; i += 8) {
        generate_key_stream(counter, key_stream);

        // XOR plaintext with key stream
        for (int j = 0; j < 8; j++) {
            ciphertext[i + j] = ((plaintext[i + j] - '0') ^ (key_stream[j] - '0')) + '0';
        }

        // Increment counter
        counter++;
    }
    ciphertext[24] = '\0'; // Null-terminate the string
}

void sdes_decrypt(char ciphertext[], char key[], char decrypted[]) {
    // Decryption in S-DES is the same as encryption
    sdes_encrypt(ciphertext, key, decrypted);
}

int binary_to_decimal(char binary[]) {
    int decimal = 0;
    int i;
    for (i = 0; binary[i] != '\0'; i++) {
        decimal = decimal * 2 + (binary[i] - '0');
    }
    return decimal;
}

