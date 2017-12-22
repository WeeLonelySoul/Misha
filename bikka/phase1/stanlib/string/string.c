#include "string.h"


void IntToAscii(int n, char str[]){
    int i, sign;
    if ((sign = n) < 0){
        n = -n;
    }
    i = 0;
    do{
        str[i++] = n % 10 + '0';
    }while ((n /= 10) > 0);

    if (sign < 0 ){
        str[i++] = '-';
    }
    str[i] = '\0';
    Reverse(str);
}

void Reverse(char s[]){
    int c, i, j;
    for (i = 0, j = StrLen(s)-1; i<j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int StrLen(char s[]){
    int i = 0;
    while (s[i] != '\0'){
        ++i;
    }
    return i;
}

void Append(char s[], char n){
    int len = StrLen(s);
    s[len] = n;
    s[len+1] = '\0';
}


void backspace(char s[]){
    int len = StrLen(s);
    s[len-1] = '\0';
}

int Strcmp(char s1[], char s2[]){
    int i;
    for (i = 0; s1[i] == s2[i]; i++){
        if (s1[i] == '\0'){
            return 0;
        }
    }
    return s1[i] - s2[i];
}