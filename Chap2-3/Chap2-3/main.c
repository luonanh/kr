//
//  main.c
//  Chap2-3
//
//  Created by Anh Luong on 7/6/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>

int myatoi(char s[]);
int htoi(char s[]);

int main(int argc, const char * argv[]) {
    char s[] = "12345";
    char s1[] = "0x1a";
    printf("%d\n", myatoi(s));
    printf("%d\n", htoi(s1));
    return 0;
}

/* strlen: return length of s */
int mystrlen(char s[])
{
    int i;
    
    while (s[i] != '\0')
        ++i;
    return i;
}

/* atoi:    convert s to integer */
int myatoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' &&  s[i] <= '9'; ++i) {
        n = n * 10 + (s[i] - '0');
    }
    return n;
}

/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 'a' - 'A';
    else
        return c;
}

int htoi(char s[])
{
    int i, n = 0;
    char c;
    
    if (tolower(s[1]) == 'x' && s[0] == '0')
        i = 2;
    else
        i = 0;
    for (; isalnum(s[i]); ++i) {
        if (isdigit(s[i]))
            n = n * 16 + s[i] - '0';
        c = tolower(s[i]);
        if (c >= 'a' && c <= 'f')
            n = n * 16 + s[i] - 'a' + 10;
    }
    return n;
}