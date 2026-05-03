#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decrypt(char text[], int key) {
    for(int i = 0; text[i] != '\0'; i++) {
        if(isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base - key + 26) % 26 + base;
        }
    }
}

int main() {
    char text[100];
    int key;

    printf("Enter Ciphertext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key: ");
    scanf("%d", &key);

    decrypt(text, key);

    printf("Decrypted Text: %s", text);
    return 0;
}