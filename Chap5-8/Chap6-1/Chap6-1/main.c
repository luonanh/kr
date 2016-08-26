//
//  main.c
//  Chap6-1
//
//  Created by Anh Luong on 7/15/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>

typedef struct _key {
    char *word;
    int count;
} key;

key keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

#define NKEYS (sizeof keytab / sizeof(keytab[0]))

int getch(void);
void myungetch(int);

#define BUFSIZE   100

char buf[BUFSIZE];    // buffer for myungetch
int bufp = 0;         // next free position in buf

int getch(void) // get a (possibly pushed-back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void myungetch(int c)   // push a character back on input
{
    if (bufp >= BUFSIZE)
        printf("myungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

#include <ctype.h>
#include <string.h>

#define MAXWORD 100

int getword(char *, int);
//int binsearch(char *, key *, int);
key *binsearch(char *word, key *keytab, int n);

/* count C keywords and print out */
int main(int argc, const char * argv[])
{
    key *p;
    char word[MAXWORD];
    
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((p = binsearch(word, keytab, NKEYS)) != NULL)
                p->count++;
    
    for (p = keytab; p < (keytab + NKEYS); p++)
        if (p->count > 0)
            printf("%4d %s\n", p->count, p->word);
    return 0;
}

/*
int binsearch(char *word, key tab[], int n)
{
    int cond;
    int low, mid, high;
    
    low = 0;
    high = NKEYS - 1;
    
    while (low <= high) {
        mid = (high + low) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    
    return -1;
}
 */
key *binsearch(char *word, key *keytab, int n)
{
    int cond;
    key *low, *mid, *high;
    
    low = &keytab[0];
    high = &keytab[n];
    
    while (low < high) {
        mid = low + (high - low) / 2;
        if ((cond = strcmp(word, mid->word)) < 0)
            high = mid;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    
    return NULL;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c;
    char *w = word;
    
    while (isspace(c = getch()))
        ;
    
    if (c != EOF)
        *w++ = c;
    
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            myungetch(*w);
            break;
        }
    }
    *w = '\0';
    return w[0];
}
