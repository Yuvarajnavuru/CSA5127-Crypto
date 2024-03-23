#include <stdio.h>
#include <string.h>

void decrypt(char *ciphertext) {
    char substitution[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?";

    
    char mapping[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-=[]{}|;:,.<>?";

    int i, j;

    for (i = 0; i < strlen(ciphertext); i++) {
        if (ciphertext[i] >= '0' && ciphertext[i] <= '9') {
            
            j = ciphertext[i] - '0' + 52;
            printf("%c", substitution[j]);
        } else {
            
            for (j = 0; j < 72; j++) {
                if (ciphertext[i] == mapping[j]) {
                    printf("%c", substitution[j]);
                    break;
                }
            }
            if (j == 72)
                printf("%c", ciphertext[i]); 
        }
    }
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?";
    
    printf("Decrypted text: ");
    decrypt(ciphertext);
    printf("\n");

    return 0;
}

