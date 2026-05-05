#include <stdio.h>
#include <string.h>

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

// XOR encryption/decryption
void xorCipher(char text[], long long key) {
    for(int i = 0; text[i] != '\0'; i++) {
        text[i] = text[i] ^ key;
    }
}

int main() {
    long long G = 15;
    long long P = 211;

    printf("--- ECC Key Exchange (Simulation) ---\n");
    printf("Public Parameters: G = %lld, P = %lld\n", G, P);

    long long a = 121; // Alice private
    long long b = 203; // Bob private

    // Public keys
    long long Qa = ecc_multiply(a, G, P);
    long long Qb = ecc_multiply(b, G, P);

    printf("\nAlice's Public Key (Qa): %lld\n", Qa);
    printf("Bob's Public Key (Qb): %lld\n", Qb);

    // Shared secret
    long long Sa = ecc_multiply(a, Qb, P);
    long long Sb = ecc_multiply(b, Qa, P);

    printf("\nShared Secret: %lld\n", Sa);

    if (Sa != Sb) {
        printf("Error! Keys do not match.\n");
        return 0;
    }

    // Message input
    char message[100];
    printf("\nEnter message: ");
    scanf(" %[^\n]", message);

    // Encrypt
    xorCipher(message, Sa);
    printf("Encrypted Message: %s\n", message);

    // Decrypt
    xorCipher(message, Sa);
    printf("Decrypted Message: %s\n", message);

    return 0;
}