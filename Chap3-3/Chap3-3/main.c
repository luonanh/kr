//
//  main.c
//  Chap3-3
//
//  Created by Anh Luong on 7/10/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int myatoi(char s[]);
void itoa(int n, char s[]);
void reverse(char s[]);

int main(int argc, const char * argv[]) {
    char s[] = "12345";
    char t[1000] = "1000";
    int n = myatoi(s);
    
    printf("atoi %d\n", n);
    itoa(n, t);
    printf("itoa %s\n", t);
    return 0;
}

/* atoi:    convert s to integer; version 2 */
int myatoi(char s[])
{
    int i, n, sign;
    
    for (i = 0; isspace(s[i]); ++i) // skip white space
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') // skip sign
        i++;
    for (n = 0; isdigit(s[i]); ++i)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

void itoa(int n, char s[])
{
    int sign, i = 0;
    
    if ((sign = n) < 0)
        n = -n;
    
    i = 0;
    do {
        printf("%c - ",n % 10 + '0');
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    
    if (sign < 0)
        s[i++] = '-';
    
    s[i] = '\0';
    
    reverse(s);
}

/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;
    
    for (i = 0, j = (int)strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}