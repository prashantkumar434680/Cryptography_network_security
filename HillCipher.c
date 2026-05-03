#include<stdio.h>
#include<string.h>
#include<ctype.h>

void encryptBlock(int key[2][2], int pt[2], int ct[2]){
    ct[0] = (key[0][0] * pt[0] + key[1][0] * pt[1]) % 26;
    ct[1] = (key[0][1] * pt[0] + key[1][1] * pt[1]) % 26;
}

int main(){
    int key[2][2] = {{3,3}, {2,5}};
    char message[] = "HILL";
    int n = strlen(message);

    printf("Plaintext: %s\n", message);
    printf("CipherTest: ");

    for(int i=0;i<n;i+=2){
        int p[2], c[2];
        p[0] = toupper(message[i]) - 'A';
        p[1] = toupper(message[i+1]) - 'A';

        encryptBlock(key, p, c);

        // Convert Back to characters
        printf("%c%c", c[0] + 'A', c[1] + 'A');
    }
    printf("\n");
    return 0;
}