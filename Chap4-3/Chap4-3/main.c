//
//  main.c
//  Chap4-3
//
//  Created by Anh Luong on 7/12/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP   100   // max size of operand or operator
#define NUMBER  '0'   // signal that a number was found

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(int argc, const char * argv[])
{
    int type;
    double op2;
    char s[MAXOP];
    
    while ((type = getop(s)) != EOF) {
        switch(type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '%':
                op2 = pop();
                push((int)pop() % (int)op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("unknown command %s\n", s);
                break;
        }
    }
    
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

int mygetch(void);
void myungetch(int);

/* getop: get next character or numeric operand. */
int getop(char s[])
{
    int i, c;
    
    while ((s[0] = c = mygetch()) == ' ' || c == '\t') // skip space and tab
        ;
    
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;       // not a number
    i = 0;
    if (isdigit(c))   // collect integer part
        while (isdigit(s[++i] = c = mygetch()))
            ;
    if (c == '.')     // collect fraction part
        while (isdigit(s[++i] = c = mygetch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        myungetch(c);
    return NUMBER;
}


#define BUFSIZE   100

char buf[BUFSIZE];    // buffer for ungetch
int bufp = 0;         // next free position in buf

int mygetch(void)       // get a (possibly pushed-back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void myungetch(int c)   // push a character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
