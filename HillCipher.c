#include <stdio.h>

// Function to find modular inverse of a number under mod 26
int modInverse(int det) {
    det = det % 26;
    for(int i = 1; i < 26; i++) {
        if((det * i) % 26 == 1)
            return i;
    }
    return -1; // No inverse exists
}

// Function to find inverse of 2x2 matrix
void findInverse(int key[2][2], int invKey[2][2]) {
    int det = (key[0][0]*key[1][1] - key[0][1]*key[1][0]) % 26;

    if(det < 0) det += 26;

    int invDet = modInverse(det);

    if(invDet == -1) {
        printf("Inverse does not exist!\n");
        return;
    }

    // Adjoint matrix
    invKey[0][0] =  key[1][1];
    invKey[0][1] = -key[0][1];
    invKey[1][0] = -key[1][0];
    invKey[1][1] =  key[0][0];

    // Multiply by inverse of determinant and take mod 26
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            invKey[i][j] = (invKey[i][j] * invDet) % 26;

            // Handle negative values
            if(invKey[i][j] < 0)
                invKey[i][j] += 26;
        }
    }
}

int main() {
    int key[2][2] = {{3,3},{2,5}};
    int invKey[2][2];

    findInverse(key, invKey);

    printf("Inverse Matrix:\n");
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d ", invKey[i][j]);
        }
        printf("\n");
    }

    return 0;
}