

#include<stdio.h>
#include<string.h>

void monoAlphaSub(char text[], char key[]){
    for(int i = 0; text[i] != '\0'; i++){

        // For uppercase letters
        if(text[i] >= 'A' && text[i] <= 'Z'){
            text[i] = key[text[i] - 'A'];
        }

        // For lowercase letters
        else if(text[i] >= 'a' && text[i] <= 'z'){
            text[i] = key[text[i] - 'a'] + 32;  // convert to lowercase
        }
    }
}

int main(){
    char text[100];
    char key[26] = "QWERTYUIOPASDFGHJKLZXCVBNM";

    printf("Enter text to Encrypt: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline character
    text[strcspn(text, "\n")] = 0;

    monoAlphaSub(text, key);

    printf("Encrypted text: %s\n", text);

    return 0;
}