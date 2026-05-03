#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

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
    printf("Ciphertext: ");
    for(int i = 0; i < strlen(text); i += 2) {
        // If last character is alone, pair with 'X'
        char p1 = text[i];
        char p2 = (text[i+1] == '\0') ? 'X' : text[i+1];
        encrypt(matrix, p1, p2);
    }
    printf("\n");
    return 0;
}