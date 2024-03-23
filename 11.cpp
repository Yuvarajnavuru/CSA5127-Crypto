#include <stdio.h>

// Function to calculate the factorial of a number
long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int totalLetters = 25; // Total number of letters in the key matrix
    long long possibleKeys;

    // Calculate the number of possible keys (permutations)
    possibleKeys = factorial(totalLetters);

    printf("Number of possible keys (without considering duplicates): %lld\n", possibleKeys);

    // Taking into account duplicate keys
    possibleKeys /= 2; // Assuming 'I' and 'J' are interchangeable

    printf("Number of effectively unique keys (considering duplicates): %lld\n", possibleKeys);

    return 0;
}
