#include <stdio.h>


int key = 0b0111111101;
int key1, key2;


int LH(int bits) {
    return bits >> 4;
}


int RH(int bits) {
    return bits & 0xF;
}


int shift(int bits) {
    int leftmost = LH(bits);
    int rightmost = RH(bits);
    int r0 = (leftmost & 0x7) << 1;
    int r1 = (rightmost & 0x7) << 1;
    return (r0 | (leftmost >> 3)) << 4 | (r1 | (rightmost >> 3));
}


void generate_keys() {
    int shifted = shift(key);
    key1 = (shifted & 0xF0) | (shifted & 0xF);
    shifted = shift(shifted);
    key2 = (shifted & 0xF0) | (shifted & 0xF);
}


int main() {
    generate_keys();
    printf("Key1: %d\n", key1);
    printf("Key2: %d\n", key2);
    return 0;
}

