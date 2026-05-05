#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void decrypt(char matrix[SIZE][SIZE], char c1, char c2) {
    int r1, c1_pos, r2, c2_pos;
    findPos(matrix, c1, &r1, &c1_pos);
    findPos(matrix, c2, &r2, &c2_pos);

    if (r1 == r2) // Same Row → shift left
        printf("%c%c", matrix[r1][(c1_pos - 1 + 5) % 5],
                        matrix[r2][(c2_pos - 1 + 5) % 5]);

    else if (c1_pos == c2_pos) // Same Column → shift up
        printf("%c%c", matrix[(r1 - 1 + 5) % 5][c1_pos],
                        matrix[(r2 - 1 + 5) % 5][c2_pos]);

    else // Rectangle rule (same as encryption)
        printf("%c%c", matrix[r1][c2_pos],
                        matrix[r2][c1_pos]);
}

// Generate the 5x5 key matrix
void generateMatrix(char key[], char matrix[SIZE][SIZE]) {
    int dict[26] = {0};
    int i = 0, j = 0;
    dict['J' - 'A'] = 1; // Treat J as I

    for (int k = 0; k < strlen(key); k++) {
        char c = toupper(key[k]);
        if (c != 'J' && dict[c - 'A'] == 0) {
            matrix[i][j++] = c;
            dict[c - 'A'] = 1;
            if (j == SIZE) { i++; j = 0; }
        }
    }

    for (int k = 0; k < 26; k++) {
        if (dict[k] == 0) {
            matrix[i][j++] = (char)(k + 'A');
            dict[k] = 1;
            if (j == SIZE) { i++; j = 0; }
        }
    }
}

// Find position of a character in the matrix
void findPos(char matrix[SIZE][SIZE], char c, int *r, int *cl) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == toupper(c)) {
                *r = i; *cl = j;
                return;
            }
        }
    }
}

void encrypt(char matrix[SIZE][SIZE], char p1, char p2) {
    int r1, c1, r2, c2;
    findPos(matrix, p1, &r1, &c1);
    findPos(matrix, p2, &r2, &c2);

    if (r1 == r2) // Same Row
        printf("%c%c", matrix[r1][(c1 + 1) % 5], matrix[r2][(c2 + 1) % 5]);
    else if (c1 == c2) // Same Column
        printf("%c%c", matrix[(r1 + 1) % 5][c1], matrix[(r2 + 1) % 5][c2]);
    else // Rectangle Rule
        printf("%c%c", matrix[r1][c2], matrix[r2][c1]);
}
int main() {
    char matrix[SIZE][SIZE];
    char key[] = "MONARCHY";
    char text[] = "INSTRUMENTS"; 

    generateMatrix(key, matrix);

    char encrypted[100];
    int k = 0;

    printf("Ciphertext: ");
    for(int i = 0; i < strlen(text); i += 2) {
        char p1 = text[i];
        char p2 = (text[i+1] == '\0') ? 'X' : text[i+1];

        int r1, c1, r2, c2;
        findPos(matrix, p1, &r1, &c1);
        findPos(matrix, p2, &r2, &c2);

        if (r1 == r2) {
            encrypted[k++] = matrix[r1][(c1 + 1) % 5];
            encrypted[k++] = matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2) {
            encrypted[k++] = matrix[(r1 + 1) % 5][c1];
            encrypted[k++] = matrix[(r2 + 1) % 5][c2];
        }
        else {
            encrypted[k++] = matrix[r1][c2];
            encrypted[k++] = matrix[r2][c1];
        }
    }
    encrypted[k] = '\0';

    printf("%s\n", encrypted);

    //  Decryption
    printf("Decrypted Text: ");
    for(int i = 0; i < strlen(encrypted); i += 2) {
        decrypt(matrix, encrypted[i], encrypted[i+1]);
    }

    printf("\n");
    return 0;
}