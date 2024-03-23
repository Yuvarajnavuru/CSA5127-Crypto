#include <stdio.h>
#include <math.h>

int main() {
    int capacity_bits = 1024;
    int capacity_lanes = capacity_bits / 64; // Assuming each lane is 64 bits
    int total_lanes = 25; // Total number of lanes in the state matrix

    // Calculate the number of blocks needed to set all lanes in the capacity portion to nonzero values
    int blocks_needed = ceil((double)capacity_lanes / 64); // Assuming each block contains 64 lanes

    printf("Number of blocks needed: %d\n", blocks_needed);

    return 0;
}
