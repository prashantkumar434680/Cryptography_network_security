#include <stdio.h>

// Permutation Tables
int P10[] = {3,5,2,7,4,10,1,9,8,6};
int P8[]  = {6,3,7,4,8,5,10,9};
int IP[]  = {2,6,3,1,4,8,5,7};
int IPinv[] = {4,1,3,5,7,2,8,6};
int EP[]  = {4,1,2,3,2,3,4,1};
int P4[]  = {2,4,3,1};

int S0[4][4] = {
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

int S1[4][4] = {
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};

// Permutation Function
int permute(int input, int table[], int size, int total_bits) {
    int output = 0;
    for(int i = 0; i < size; i++) {
        output <<= 1;
        output |= (input >> (total_bits - table[i])) & 1;
    }
    return output;
}

// Left shift (circular)
int left_shift(int input, int shifts, int bits) {
    return ((input << shifts) | (input >> (bits - shifts))) & ((1 << bits) - 1);
}

// S-Box lookup
int sbox(int input, int table[4][4]) {
    int row = ((input & 0x8) >> 2) | (input & 0x1);
    int col = (input >> 1) & 0x3;
    return table[row][col];
}

// Function fk
int function_fk(int bits, int key) {
    int L = (bits >> 4) & 0xF;
    int R = bits & 0xF;

    int ep = permute(R, EP, 8, 4) ^ key;

    int left = sbox((ep >> 4) & 0xF, S0);
    int right = sbox(ep & 0xF, S1);

    int s_out = (left << 2) | right;
    int p4 = permute(s_out, P4, 4, 4);

    int newL = L ^ p4;

    return (newL << 4) | R;
}

// Main processing (encryption/decryption)
int process(int data, int k1, int k2) {
    int state = permute(data, IP, 8, 8);

    state = function_fk(state, k1);

    // Swap halves
    state = ((state & 0xF) << 4) | ((state >> 4) & 0xF);

    state = function_fk(state, k2);

    return permute(state, IPinv, 8, 8);
}

int main() {
    int key = 0b1010000010;   // 10-bit key
    int data = 0b10010111;   // 8-bit plaintext

    // Key generation
    int p10 = permute(key, P10, 10, 10);

    int L = (p10 >> 5) & 0x1F;
    int R = p10 & 0x1F;

    int l1 = left_shift(L, 1, 5);
    int r1 = left_shift(R, 1, 5);
    int K1 = permute((l1 << 5) | r1, P8, 8, 10);

    int l2 = left_shift(l1, 2, 5);
    int r2 = left_shift(r1, 2, 5);
    int K2 = permute((l2 << 5) | r2, P8, 8, 10);

    // Encryption
    int cipher = process(data, K1, K2);

    // Decryption (reverse keys)
    int plain = process(cipher, K2, K1);

    printf("--- Simplified DES (S-DES) ---\n");
    printf("Plaintext:  %d\n", data);
    printf("Ciphertext: %d\n", cipher);
    printf("Decrypted:  %d\n", plain);

    return 0;
}