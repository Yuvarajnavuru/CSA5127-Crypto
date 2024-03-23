#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to perform modular exponentiation (base^exp % mod)
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
    // Public parameters (generator and modulus)
    long long int g = 5;  // Generator
    long long int q = 23; // Prime modulus

    // Alice's secret number
    long long int x = 6; // Alice's secret number

    // Bob's secret number
    long long int y = 15; // Bob's secret number

    // Compute public values
    long long int A = modExp(g, x, q); // Alice's public value
    long long int B = modExp(g, y, q); // Bob's public value

    // Exchange public values (simulated communication)
    printf("Alice sends: %lld\n", A);
    printf("Bob sends: %lld\n", B);
    printf("\n");

    // Compute shared secret key
    long long int K1 = modExp(B, x, q); // Alice computes shared secret key
    long long int K2 = modExp(A, y, q); // Bob computes shared secret key

    // Display shared secret key
    printf("Shared secret key (Alice): %lld\n", K1);
    printf("Shared secret key (Bob): %lld\n", K2);

    return 0;
}
