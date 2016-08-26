//
//  main.c
//  Chap2-4
//
//  Created by Anh Luong on 7/7/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>

#define MAX_ASCII_CHAR  256
#define TRUE            1
#define FALSE           0

void squeeze2(char s1[], char s2[]);
int any(char s1[], char s2[]);

int main(int argc, const char * argv[]) {
    char s1[] = "123456789abcdefgh";
    char s2[] = "bdefgh"; // "13579bdefgh";
    /*
    squeeze2(s1, s2);
    printf("%s\n", s1);
     */
    
    printf("any(s1, s2) is %d\n", any(s1, s2));
    return 0;
}

/* squeeze: delete all c from s */
void squeeze(char s[], int c)
{
    int i, j;   // use 2 indexes i and j, i runs first, if s[i] is different from c, then s[j] = s[i]

    for (i = j = 0; s[i] != '\0'; i++)
        if (s[i] != c)
            s[j++] = s[i];
    
    s[j] = '\0';
}

/* squeeze2:    delete each character in s1 that matches any character in the string s2 */
void squeeze2(char s1[], char s2[])
{
    char c[MAX_ASCII_CHAR];
    int i, j;
    
    for (i = 0; i < MAX_ASCII_CHAR; i++) {
        c[i] = FALSE;
    }
    
    i = 0;
    while (s2[i] != '\0') {
        c[s2[i++]] = TRUE;
    }
    
    /* for debug, print out the characters that are in s2[]
    for (i = 0; i < MAX_ASCII_CHAR; i++) {
        if (c[i] == TRUE)
            printf(" %c |", i);
    }
    printf("\n");
    */
    
    for (i = j = 0; s1[i] != '\0'; ++i) {
        if (c[s1[i]] == FALSE)
            s1[j++] = s1[i];
    }
    
    s1[j] = '\0';
}

/* strcat:  concatenate t to end of s; s must be big enough */
void mystrcat(char s[], char t[])
{
    int i, j;
    
    /*
    for (i = 0; s[i++] != '\0';) {}
    
    for (j = 0; t[j] != '\0'; ) {
        s[i++] = t[j++];
    }
     */
    i = j = 0;
    while (s[i] != '\0')    // find end of s
        i++;
    while ((s[i++] = t[j++]) != '\0')   // copy t
        ;
}
/* any: returns the first location in a string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. Very similar to strpbrk */
int any(char s1[], char s2[])
{
    char c[MAX_ASCII_CHAR];
    int i;
    
    for (i = 0; i < MAX_ASCII_CHAR; i++) {
        c[i] = FALSE;
    }
    
    i = 0;
    while (s2[i] != '\0') {
        c[s2[i++]] = TRUE;
    }
    
    /* for debug, print out the characters that are in s2[]
     for (i = 0; i < MAX_ASCII_CHAR; i++) {
     if (c[i] == TRUE)
     printf(" %c |", i);
     }
     printf("\n");
     */
    
    for (i = 0; s1[i] != '\0'; ++i) {
        if (c[s1[i]] == TRUE)
            return i;
    }
    
    return -1;
}
