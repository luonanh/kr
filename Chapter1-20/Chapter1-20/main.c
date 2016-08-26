//
//  main.c
//  Chapter1-20
//
//  Created by Anh Luong on 7/5/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>

#define TAB_SIZE    8
#define MAXLINE     1000    /* maximum input line length */
#define IN          0
#define OUT         1

int detab(char s[], int lim);
int entab(char s[], int lim);

int main(int argc, const char * argv[]) {
    char s[MAXLINE];
    int len;
    
    while ((len = entab(s, MAXLINE)) > 0)
        printf("%s", s);
    
    return 0;
}

int detab(char s[], int lim)
{
    uint16_t i, j = 0;
    int c = 0;
    
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n';) {
        if (c == '\t') {    // replace tab with the proper number of blanks
            for (j = 0; j < TAB_SIZE; ++j)
                s[i++] = '|';
        } else {
            s[i++] = c;
        }
    }
    
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    
    s[i] = '\0';
    return i;
}

int entab(char s[], int lim)
{
    uint16_t i, j = 0, len;
    int c = 0;
    int state = OUT, ns;
    char r[MAXLINE];
    
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        s[i] = c;
    }
    
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    
    s[i] = '\0';
    len = i;
    printf("%s of length %d\n", s, len);
    
    for (i = 0, j = 0, ns = 0; i <= len; ++i, ++j) {    // i is index to s[], j is index to r[]
        c = s[i];
        r[j] = c;
        if (c != ' ') {         // if current character is not space
            state = OUT;
            ns = 0;
        } else {                // else --> current character is space
            if (state != IN) {  // if previous character is NOT space
                state = IN;
                ns = 1;         // initialize number of space ns
            } else {            // if previous character is space
                ns++;
                if (ns == TAB_SIZE) {
                    j -= TAB_SIZE;
                    r[++j] = '|';
                    ns = 0;
                }
            }
        }
    }
    printf("%s of reduced length %d\n", r, j);
    
    for (i = 0; i <= j ; ++i) {
        s[i] = r[i];
    }
    return j;
}
