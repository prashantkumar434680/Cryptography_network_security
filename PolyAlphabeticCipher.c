#include <stdio.h>
#include <string.h>
#include <ctype.h>

void polyAlphaEnc(char text[], char key[]) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    char ciphertext[textLen + 1];

        for (int i = 0, j = 0; i < textLen; i++) {
        char currentByte = text[i];

        if (isalpha(currentByte)) {
            // Determine base (upper or lower)
            char base = isupper(currentByte) ? 'A' : 'a';
            
            // Get key shift (0-25) from the current key character
            int k = toupper(key[j % keyLen]) - 'A';

            // Vigenere Formula: Ci = (Pi + Ki) mod 26
            // This is equivalent to looking up Row Pi and Column Ki in the 2D matrix
            text[i] = (currentByte - base + k) % 26 + base;

            j++; // Move to next key character only for alphabets
        }
    }
}

int main(){
    char message[100];
    char key[50];

    printf("Enter Plaintext: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;

    printf("Enter Keyword: ");
    scanf("%s", key);

    polyAlphaEnc(message, key);

    printf("Encrypted Message: %s\n", message);
    return 0;
}