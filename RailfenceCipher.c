#include <stdio.h>
#include <string.h>

void decryptRailFence(char cipher[], int key) {
    int len = strlen(cipher);
    char rail[key][len];

    // Step 1: Fill matrix with marker
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    // Step 2: Mark zig-zag pattern
    int row = 0, direction_down = 0;

    for (int i = 0; i < len; i++) {
        rail[row][i] = '*';

        if (row == 0 || row == key - 1)
            direction_down = !direction_down;

        row += direction_down ? 1 : -1;
    }

    // Step 3: Fill marked positions with ciphertext
    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] == '*' && index < len) {
                rail[i][j] = cipher[index++];
            }
        }
    }

    // Step 4: Read zig-zag to get plaintext
    printf("Decrypted text: ");
    row = 0;
    direction_down = 0;

    for (int i = 0; i < len; i++) {
        printf("%c", rail[row][i]);

        if (row == 0 || row == key - 1)
            direction_down = !direction_down;

        row += direction_down ? 1 : -1;
    }
    printf("\n");
}

void encryptRailFence(char text[], int key) {
    int len = strlen(text);
    char rail[key][len];

    // Initialize the matrix with a marker
    for (int i = 0; i < key; i++)
        for (int j = 0; j < len; j++)
            rail[i][j] = '\n';

    int row = 0;
    int direction_down = 0; // To track zig-zag direction

    // Fill the rail matrix in a zig-zag manner
    for (int i = 0; i < len; i++) {
        rail[row][i] = text[i];

        // Reverse direction if we hit the top or bottom rail
        if (row == 0 || row == key - 1)
            direction_down = !direction_down;

        row += direction_down ? 1 : -1;
    }

    // Read the matrix row by row to get ciphertext
    printf("Ciphertext: ");
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] != '\n')
                printf("%c", rail[i][j]);
        }
    }
    printf("\n");
}

int main() {
    char message[100];
    int rails;

    printf("Enter the message: ");
    scanf("%[^\n]s", message);

    printf("Enter number of rails: ");
    scanf("%d", &rails);

    encryptRailFence(message, rails);

    printf("Enter ciphertext to decrypt: ");
    scanf(" %[^\n]s", message);

    decryptRailFence(message, rails);

    return 0;
}