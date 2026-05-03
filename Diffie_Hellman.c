#include <stdio.h>

// Function for modular exponentiation: (base^exp) % mod
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

int main() {
    long long P, G;     // Public values
    long long a, b;     // Private keys
    long long x, y;     // Public keys
    long long ka, kb;   // Shared keys

    printf("--- Diffie-Hellman Key Exchange ---\n");

    // 1. Public values
    printf("Enter a prime number (P): ");
    scanf("%lld", &P);

    printf("Enter a primitive root (G): ");
    scanf("%lld", &G);

    // 2. Private keys
    printf("\nEnter Alice's private key (a): ");
    scanf("%lld", &a);

    printf("Enter Bob's private key (b): ");
    scanf("%lld", &b);

    // 3. Public keys
    x = power(G, a, P);  // Alice's public key
    y = power(G, b, P);  // Bob's public key

    printf("\nAlice's Public Key (x): %lld\n", x);
    printf("Bob's Public Key (y): %lld\n", y);

    // 4. Shared secret
    ka = power(y, a, P); // Alice computes
    kb = power(x, b, P); // Bob computes

    printf("\nShared Key (Alice): %lld\n", ka);
    printf("Shared Key (Bob): %lld\n", kb);

    if (ka == kb)
        printf("\nSuccess! Shared keys match.\n");
    else
        printf("\nError! Keys do not match.\n");

    return 0;
}