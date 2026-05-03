#include <stdio.h>

// Simplified ECC scalar multiplication (simulation)
long long ecc_multiply(long long private_key, long long base_point, long long prime) {
    long long result = 0;
    long long temp_base = base_point;

    while (private_key > 0) {
        if (private_key % 2 == 1) {
            result = (result + temp_base) % prime;
        }
        temp_base = (temp_base + temp_base) % prime;
        private_key /= 2;
    }

    return result;
}

int main() {
    // Public parameters
    long long G = 15;   // Base Point
    long long P = 211;  // Prime Field

    printf("--- ECC Key Exchange (Simulation) ---\n");
    printf("Public Parameters: G = %lld, P = %lld\n", G, P);

    // Private keys
    long long a = 121;  // Alice
    long long b = 203;  // Bob

    // Public keys
    long long Qa = ecc_multiply(a, G, P);
    long long Qb = ecc_multiply(b, G, P);

    printf("\nAlice's Public Key (Qa): %lld\n", Qa);
    printf("Bob's Public Key (Qb): %lld\n", Qb);

    // Shared secret
    long long Sa = ecc_multiply(a, Qb, P);
    long long Sb = ecc_multiply(b, Qa, P);

    printf("\nShared Secret (Alice): %lld\n", Sa);
    printf("Shared Secret (Bob):   %lld\n", Sb);

    if (Sa == Sb) {
        printf("\nSuccess! Shared secrets match.\n");
    } else {
        printf("\nError! Keys do not match.\n");
    }

    return 0;
}