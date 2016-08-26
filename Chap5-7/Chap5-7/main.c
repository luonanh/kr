//
//  main.c
//  Chap5-7
//
//  Created by Anh Luong on 7/13/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>

#define MAXLINES    5000    // max #lines to be sorted
#define MAXLEN      1000    // max length of any input line

char *lineptr[MAXLINES];    // pointers to text lines

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void myqsort(char *lineptr[], int left, int right);

int mygetline(char *, int);
char *alloc(int);

void mystrcpy(char *s, char *t);
int mystrcmp(char *s, char *t);

/* sort input lines */
int main(int argc, const char * argv[]) {
    int nlines;             // number of input lines read
    
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        myqsort(lineptr, 0, nlines-1);
        writelines(lineptr, nlines);
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
    return 0;
}


int mygetline(char *s, int lim)
{
    int i, c = 0;
    
    for (i = 0; i < lim && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    
    if (c == '\n')
        s[i++] = c;
    
    s[i] = '\0';
    return i;
}

/* strcpy:  copy t to s; pointer version */
void mystrcpy(char *s, char *t)
{
    for (; (*s++ = *t++); )
        ;
}

int mystrcmp(char *s, char *t)
{
    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

#define ALLOCSIZE     10000       // size of available space

static char allocbuf[ALLOCSIZE];       // storage for alloc
static char *allocp = allocbuf;   // next free position

char *alloc(int n)                // return pointer to n characters
{
    if (allocbuf + ALLOCSIZE - allocp >= n) { // it fits
        allocp += n;
        return allocp - n;            // old allocp
    } else {                        // not enough room
        return NULL;
    }
}

void afree(char *p)               // free storage pointed to by p
{
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

/* readlines:   read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    
    nlines = 0;
    while ((len = mygetline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len-1] = '\0'; // delete newline
            mystrcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
    /* 1st way
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
     */
    while (--nlines >= 0)
        printf("%s\n", *lineptr++);
}

void swap(char *lineptr[], int i, int j)
{
    char *temp = lineptr[i];
    lineptr[i] = lineptr[j];
    lineptr[j] = temp;
}
/* myqsort: sort v[left]...v[right] into increasing order */
void myqsort(char *v[], int left, int right)
{
    int i, last;  // last the leftmost index of v[] such that v[last] >= partition elem
    
    if (left >= right)                    // do nothing if array contains fewer than 2 elements
        return;
    
    swap(v, left, (left + right) / 2);    // move partition elem to v[0]
    last = left;
    for (i = left + 1; i <= right; i++) { // partition
        if (mystrcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    }
    swap(v, left, last);                  // restore partition elem
    myqsort(v, left, last - 1);
    myqsort(v, last + 1, right);
}
