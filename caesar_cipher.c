#include<stdio.h>
#include<string.h>

void caesar(char text[], int key){
    for(int i = 0; text[i] != '\0'; ++i){
        char ch = text[i];

        // Encrypt lowercase letters
        if(ch >= 'a' && ch <= 'z')
        text[i] = (ch - 'a' + key) % 26 + 'a';

        // Encrypt Uppercase letters
        else if(ch >= 'A' && ch <= 'Z')
        text[i] = (ch - 'A' + key) % 26 + 'A';
    }

    // non-alphabetic character (space, punctuation ) remain unchanged
}

int main(){
    char message[100];
    int key;

    printf("Enter the message: ");
    fgets(message, sizeof(message), stdin);

    // remove new line character if present
    message[strcspn(message, "\n")] = 0;

    printf("Enter the shift key (e.g. 3): ");
    scanf("%d", &key);

    caesar(message, key);

    printf("Encrypted Message: %s\n", message);

    return 0;
}