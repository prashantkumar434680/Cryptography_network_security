#include <stdio.h>
#include <string.h>

// Modular exponentiation
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// XOR Encryption/Decryption
void xorCipher(char text[], long long key) {
    for(int i = 0; text[i] != '\0'; i++) {
        text[i] = text[i] ^ key;
    }
}

int main() {
    long long P, G;
    long long a, b;
    long long x, y;
    long long ka, kb;

    char message[100];

    printf("--- Diffie-Hellman Key Exchange ---\n");

    // Public values
    printf("Enter prime number (P): ");
    scanf("%lld", &P);

    printf("Enter primitive root (G): ");
    scanf("%lld", &G);

    // Private keys
    printf("Enter Alice private key (a): ");
    scanf("%lld", &a);

    printf("Enter Bob private key (b): ");
    scanf("%lld", &b);

    // Public keys
    x = power(G, a, P);
    y = power(G, b, P);

    printf("\nAlice Public Key: %lld\n", x);
    printf("Bob Public Key: %lld\n", y);

    // Shared key
    ka = power(y, a, P);
    kb = power(x, b, P);

    printf("\nShared Key: %lld\n", ka);

    // Input message
    printf("\nEnter message: ");
    scanf(" %[^\n]", message);

    // Encryption
    xorCipher(message, ka);
    printf("Encrypted Message: %s\n", message);

    // Decryption
    xorCipher(message, ka);
    printf("Decrypted Message: %s\n", message);

    return 0;
}