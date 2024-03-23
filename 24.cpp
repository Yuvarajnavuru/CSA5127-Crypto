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

    // Step 1: Find p and q using trial and error
    int p, q;
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }

    // Step 2: Calculate Euler's totient function
    int phi_n = (p - 1) * (q - 1);

    // Step 3: Find the modular multiplicative inverse of e modulo phi(n)
    int d = modInverse(e, phi_n);

    printf("Private Key (d): %d\n", d);

    return 0;
}
