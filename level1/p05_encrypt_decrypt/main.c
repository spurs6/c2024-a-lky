#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char encryptchar(char a, int shift) {
    if (isalpha(a)) {
        if (a >= 'a' && a <= 'z') {
            char x = 'a';
            a = (a - x + shift) %26+ x;
            return a;
        }
        else {
            char x= 'A';
            a = (a - x + shift)%26 + x;
        }
    }
    else {
        return a;
    }
}
char decryptchar(char a, int shift) {
    a = encryptchar(a, 26 - (shift % 26));
    return a;
}
void encryptstring(char* string, int shift) {
    for (int i = 0; string[i]!= '\0'; i++) {
        string[i] = encryptchar(string[i], shift);
    }
}
void decryptstring(char* string, int shift) {
    for (int i = 0; string[i] != '\0'; i++) {
        string[i] = decryptchar(string[i], shift);
    }
}
int main() {
    int shift=0;
    scanf("%d", &shift);
    char* p=(char*) malloc(sizeof(char)*100);
    scanf("%s", p);
    encryptstring(p, shift);
    printf("%s\n",p);
    decryptstring(p,shift);
    printf("%s\n",p);
    free(p);
}




