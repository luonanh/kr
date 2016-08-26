//
//  main.c
//  Chap4-1
//
//  Created by Anh Luong on 7/11/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define MAXLINE   1000

int mygetline(char line[], int max);
int strindex(char source[], char searchfor[]);
int strindexRight(char source[], char searchfor[]);

char pattern[] = "ould";

int main()
{
    char line[MAXLINE];
    int found = 0, i;
    
    while (mygetline(line, MAXLINE) > 0) {
        if ((i = strindexRight(line, pattern)) >= 0) {
            printf("Found pattern at position %d %s\n", i, line);
            found++;
        }
    }
    
    return found;
}

/* getline: get line into s, return length */
int mygetline(char s[], int lim)
{
    int i, c = 0;
    
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    
    if (c == '\n')
        s[i++] = c;
    
    s[i] = '\0';
    return i;
}

/* strindex:  return index of t in s, -1 if none */
int strindex(char s[], char t[])
{
    /* Anh's solution
     int i, j, k;
     
     for (i = 0; i < strlen(s)-1; i++) {
     for (j = 0, k = i; j < strlen(t)-1; j++, k++) {
     if (s[k] != t[j])
     break;
     }
     if (j == strlen(t)-1)
     return i;
     }
     
     return -1;
     */
    
    int i, j, k;
    
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        printf("i = %d, j = %d, k = %d\n", i, j, k);
        if (k > 0 && t[k] == '\0') {
            printf("strindex() find at %d\n", i);
            return i;
        }
    }
    
    printf("strindex NOT found\n");
    return -1;
}

/* strindexRight:   returns the position of the rightmost occurrence of t in s, or -1 if there is none. */
int strindexRight(char s[], char t[])
{
    int i, j, k;
    
    for (i = (int)strlen(s) - 1; i >= (int)strlen(t) - 1; i--) {
        for (j = i, k = (int)strlen(t) - 1; k >= 0 && s[j] == t[k]; j--, k--)
            ;
        
        printf("i = %d, j = %d, k = %d\n", i, j, k);
        if (k < 0)
            return j+1;
    }
    return -1;
}

