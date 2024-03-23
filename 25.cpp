#include <stdio.h>

// Function to calculate the greatest common divisor (GCD) using Euclidean algorithm
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find the modular multiplicative inverse using extended Euclidean algorithm
int modInverse(int a, int m) {
    int m0 = m;
    int y = 0, x = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        // q is quotient
        int q = a / m;
        int t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m, a = t;
        t = y;

        // Update x and y
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0)
        x += m0;

    return x;
}

int main() {
    int e = 31;
    int n = 3599;

    // Step 1: Factorization of n
    int p, q;
    // Code to find at least one factor of n

    // Step 2: Compute phi(n)
    int phi_n = (p - 1) * (q - 1);

    // Step 3: Compute the private key d
    int d = modInverse(e, phi_n);

    printf("Private Key (d): %d\n", d);

    return 0;
}
