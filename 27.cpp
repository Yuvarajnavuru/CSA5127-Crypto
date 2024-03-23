#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate modular exponentiation (base^exp % mod)
long long int modExp(long long int base, long long int exp, long long int mod) {
    long long int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    // Public key parameters
    long long int e = 65537; // Public exponent
    long long int n = 979797; // Modulus

    // Message to be encrypted (alphabetic characters only)
    char message[] = "HELLO";

    // Encryption
    printf("Encrypted Message: ");
    for (int i = 0; message[i] != '\0'; i++) {
        // Convert each character to an integer between 0 and 25
        int charInt = message[i] - 'A';
        
        // Encrypt the integer using RSA encryption
        long long int encryptedInt = modExp(charInt, e, n);
        
        // Print the encrypted integer
        printf("%lld ", encryptedInt);
    }
    printf("\n");

    return 0;
}
