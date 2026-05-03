#include <stdio.h>

// Modular exponentiation: (base^exp) % mod
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

// GCD function
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    long long p = 61, q = 101;
    long long n, phi, e = 7, d = 0;

    // Step 1 & 2
    n = p * q;

    // Step 3
    phi = (p - 1) * (q - 1);

    // Step 4: Find e
    while (e < phi) {
        if (gcd(e, phi) == 1)
            break;
        e++;
    }

    // Step 5: Find d
    for (long long i = 1; i < phi; i++) {
        if ((e * i) % phi == 1) {
            d = i;
            break;
        }
    }

    printf("--- RSA Algorithm ---\n");
    printf("Public Key (e, n): (%lld, %lld)\n", e, n);
    printf("Private Key (d, n): (%lld, %lld)\n", d, n);

    long long msg;
    printf("\nEnter numeric message (< %lld): ", n);
    scanf("%lld", &msg);

    // Encryption
    long long cipher = power(msg, e, n);
    printf("Encrypted Data: %lld\n", cipher);

    // Decryption
    long long decrypted = power(cipher, d, n);
    printf("Decrypted Message: %lld\n", decrypted);

    return 0;
}