#include<stdio.h>
#include<string.h>
#include<ctype.h>

// Encryption
void monoAlphaEncrypt(char text[], char key[]){
    for(int i = 0; text[i] != '\0'; i++){

        if(isupper(text[i])){
            text[i] = key[text[i] - 'A'];
        }
        else if(islower(text[i])){
            text[i] = tolower(key[text[i] - 'a']);
        }
    }
}

// Decryption
void monoAlphaDecrypt(char text[], char key[]){
    for(int i = 0; text[i] != '\0'; i++){

        if(isupper(text[i])){
            for(int j = 0; j < 26; j++){
                if(text[i] == key[j]){
                    text[i] = 'A' + j;
                    break;
                }
            }
        }

        else if(islower(text[i])){
            for(int j = 0; j < 26; j++){
                if(toupper(text[i]) == key[j]){
                    text[i] = 'a' + j;
                    break;
                }
            }
        }
    }
}

int main(){
    char text[100];
    char key[26] = "QWERTYUIOPASDFGHJKLZXCVBNM";

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;

    // Encrypt
    monoAlphaEncrypt(text, key);
    printf("Encrypted text: %s\n", text);

    // Decrypt
    monoAlphaDecrypt(text, key);
    printf("Decrypted text: %s\n", text);

    return 0;
}