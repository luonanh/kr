//
//  main.c
//  Chap4-2
//
//  Created by Anh Luong on 7/11/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>

#define MAXLINE     100

int mygetline(char line[], int max);
double myatof(char s[]);

int main(int argc, const char * argv[]) {
    double sum;
    char line[MAXLINE];
    
    sum = 0;
    
    while (mygetline(line, MAXLINE) > 0)
        printf("\t%g\n", sum += myatof(line));
    return 0;
}

/* getline: get line into s, return length */
int mygetline(char s[], int lim)
{
    int i, c;
    
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    
    if (c == '\n')
        s[i++] = c;
    
    s[i] = '\0';
    return i;
}

/* atof:    convert string s to double */
double myatof(char s[])
{
    double val, power;
    int i, sign;
    
    for (i = 0; isspace(s[i]); i++) // skip white space
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    return sign * val / power;
}