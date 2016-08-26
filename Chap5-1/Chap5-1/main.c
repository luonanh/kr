//
//  main.c
//  Chap5-1
//
//  Created by Anh Luong on 7/13/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP   100   // max size of operand or operator
#define NUMBER  '0'   // signal that a number was found

int getint(int *pn);
int getfloat(float *pn);

/* reverse Polish calculator */
int main()
{
    //int n;
    float f;
    
    /*
     if (getint(&n) > 0)
     printf("%d\n", n);
     */
    if (getfloat(&f) > 0)
        printf("%g\n", f);
    return 0;
}

#define MAXVAL    100   // max depth of val stack
int sp = 0;             // next free stack position
double val[MAXVAL];     // value stack

/* push:  push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop:   pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getch(void);
void myungetch(int);

#define BUFSIZE   100

char buf[BUFSIZE];    // buffer for myungetch
int bufp = 0;         // next free position in buf

int getch(void)       // get a (possibly pushed-back) character
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

/* getint:  get next integer from input into *pn. Version 1 provided in K&R
 int getint(int *pn)
 {
 int c, sign;
 
 while (isspace(c = getch()))  // skip white space
 ;
 
 if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
 myungetch(c);                 // it is not a number
 return 0;
 }
 
 sign = (c == '-') ? -1 : 1;
 if (c == '+' || c == '-')
 c = getch();
 
 for (*pn = 0; c != EOF; c = getch())
 *pn = 10 * *pn + (c - '0');
 *pn *= sign;
 
 if (c != EOF)
 myungetch(c);
 
 return c;
 }
 */

/* getint:  get next integer from input into *pn. Version 2 provided in K&R */
int getint(int *pn)
{
    int c, sign;
    
    while (isspace(c = getch()))  // skip white space
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        myungetch(c);                 // it is not a number
        return 0;
    }
    
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            myungetch(c);
            return 0;
        }
    }
    
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    
    if (c != EOF)
        myungetch(c);
    
    return c;
}

int getfloat(float *pn)
{
    int c, sign;
    float power;
    
    while (isspace(c = getch()))
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        myungetch(c);
        return 0;
    }
    
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c)) {
            myungetch(c);
            return 0;
        }
    }
    
    // significand part
    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');
    
    if (c == '.') {
        c = getch();
    } else {
        goto Done;
    }
    
    for (power = 1.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        power *= 10.0;
    }
    
    *pn *= sign;
    *pn /= power;
    
Done:
    if (c != EOF)
        myungetch(c);
    
    return c;
}