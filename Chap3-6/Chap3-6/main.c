//
//  main.c
//  Chap3-6
//
//  Created by Anh Luong on 7/11/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE    1000

void reverse(char s[]);
void itoa(int n, char s[]);
void itob(int n, char s[], unsigned base);
char convertBase(char c, int base);
void itoa3(int n, char s[], int width);

int main(void)
{
    char s[] = "-12345";
    char t[MAX_LINE];
    int n;
    
    n = atoi(s);
    printf("atoi %d\n", n);
    itoa(n, t);
    printf("itoa %s\n", t);
    
    itob(n, t, 2);
    printf("itob 2 %s\n", t);
    itob(n, t, 10);
    printf("itob 10 %s\n", t);
    itob(n, t, 16);
    printf("itob 16 %s\n", t);
    
    itoa3(n, t, 16);
    printf("itoa3 16 %s\n", t);
    return 0;
}

void reverse(char s[])
{
    int i, j;
    char c;
    
    for (i = 0, j = (int)strlen(s)-1; i < j; ++i, --j) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int sign, i;
    
    if ((sign = n) < 0)
        n = -n;
    
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    
    if (sign < 0)
        s[i++] = '-';
    
    s[i] = '\0';
    reverse(s);
}

void itob(int n, char s[], unsigned base)
{
    int sign, i;
    
    if ((sign = n) < 0)
        n = -n;
    
    i = 0;
    do {
        s[i++] = convertBase(n % base, base);
    } while ((n /= base) > 0);
    
    if (sign < 0)
        s[i++] = '-';
    
    s[i] = '\0';
    reverse(s);
}

char convertBase(char c, int base)
{
    switch (base) {
        case 16:
            if (isalpha(c))
                return c - 10 + 'A';
        default:
            return c + '0';
    }
}

void itoa3(int n, char s[], int width)
{
    
    int sign, i;
    
    if ((sign = n) < 0)
        n = -n;
    
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    
    if (sign < 0)
        s[i++] = '-';
    
    while ((width - i) > 0) {
        s[i++] = '|';
    }
    
    s[i] = '\0';
    reverse(s);
}

