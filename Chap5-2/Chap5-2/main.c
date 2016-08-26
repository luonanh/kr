//
//  main.c
//  Chap5-2
//
//  Created by Anh Luong on 7/13/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>

void mystrcpy(char *s, char *t);
int mystrcmp(char *s, char *t);

int main(void)
{
    
    char amessage[] = "nOw is the time";
    char *pmessage = "now is the time";
    /*
     printf("%lx\n", (unsigned long)amessage);
     printf("%s\n", amessage);
     amessage[1] = 'e';
     printf("%s\n", amessage);
     printf("%lx\n", (unsigned long)pmessage);
     printf("%lx\n", (unsigned long)&pmessage);
     printf("%s\n", pmessage);
     pmessage = amessage;
     *(pmessage+1) = 'E';
     */
    printf("strcmp %d\n", mystrcmp(pmessage, amessage));
    
    return 0;
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

/* strcpy:  copy t to s; array subscript version
 void strcpy(char *s, char *t)
 {
 int i;
 for (i = 0; (s[i] = t[i]) != '\0'; i++)
 ;
 }
 */

/* strcpy:  copy t to s; pointer version */
void mystrcpy(char *s, char *t)
{
    for (; (*s++ = *t++); )
        ;
}

int mystrcmp(char *s, char *t)
{
    /*
     int result;
     while (!(result = (*s - *t)) && (*s++ != '\0'))
     ;
     return result;
     */
    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}