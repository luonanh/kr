//
//  main.c
//  Chap1
//
//  Created by Anh Luong on 7/2/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define LOWER   0       // symbolic name or symbolic constant
#define UPPER   300     // symbolic name or symbolic constant
#define STEP    20      // symbolic name or symbolic constant
#define IN      1       // inside a word
#define OUT     0       // outside a word
#define MAX_WORD_LENGTH 100
#define MAXLINE 1000    /* maximum input line length */
#define CUTOFF_LENGTH   80  // for 1-17

int power(int base, int n);
int mygetline(char s[], int lim);
void copy(char to[], char from[]);
int getLineRmTrailing(char s[], int lim);
int reverse(char s[]);

int main(int argc, const char * argv[]) {
    /* start before 1-...
    char c = 0x32;
    
    printf("The character is %c\n", c);
    c = 'a';
    printf("The hex value of %c is 0x%3x\n", c, c);
    
    float fahr, celsius;
    float lower, upper, step;
    
    lower = 0;
    upper = 300;
    step = 20;
    
    fahr = lower;
    printf("Fahrenheit to Celsius\n");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    
    celsius = lower;
    printf("Celsius to Fahrenheit\n");
    while (celsius <= upper) {
        fahr = (9.0/5.0)*celsius + 32;
        printf("%3.0f %6.1f\n", celsius, fahr); // %3.0f -> right-justified, at least 3 characters wide, no decimal points. %6.1f -> ..., at least 6 characters wide, with 1 digit after the decimal point.
        celsius += step;
    }
    
    int ch;     // char type is not big enough to hold EOF, hence must use type int here
    printf("EOF value is: 0x%x\n", ch = EOF);
    end 1-... */
     
    /* This loop keeps reading the character from keyboard and print it to screen
    while ((ch = getchar()) != EOF) {
        printf("\nYou entered: ");
        putchar(ch);
    }
     */
    
    /* start 1.8
    long nc;
    double nl;  // try double with printf
    long nb, nt;
    
    printf("Value of newline character is: %d\n", '\n');
    for (nc = 0, nl = 0.0, nb = 0, nt = 0; (ch = getchar()) != EOF; ++nc) {
        if (ch == '\n')
            ++nl;
        else if (ch == ' ')
            ++nb;
        else if (ch == '\t')
            ++nt;
    }
    printf("The total char: %ld; total of blanks: %ld; total of tabs: %ld\n", nc, nb, nt);
    printf("The total of lines is: %.0f\n", nl);
    end 1.8 */

    /* start 1.9
    int preChar = -1;   // previous character
    while ((ch = getchar()) != EOF) {
        if (preChar == -1) {   // previous character was not inialized yet
            preChar = ch;
            putchar(ch);
            continue;
        }
        
        if (ch == ' ') {        // if current character is space
            if (preChar == ' ') // if previous character is space, then skip
                continue;
        }
        putchar(ch);
        preChar = ch;           // update previous character
    }
    end 1.9 */
    
    /* start 1-10 
     * haven't tested this yet
     
    int preChar = -1;   // previous character
    while ((ch = getchar()) != EOF) {
        if (preChar == -1) {   // previous character was not inialized yet
            preChar = ch;
            putchar(ch);
            continue;
        }
        
        if (ch == ' ') {        // if current character is space
            if (preChar == ' ') // if previous character is space, then skip
                continue;
        }

        preChar = ch;           // update previous character
        
        if (ch == '\t') {
            putchar('\\');
            putchar('t');
        } else if (ch == '\b') {
            putchar('\\');
            putchar('b');
        } else if (ch == '\\') {
            putchar('\\');
            putchar('\\');
        }
        putchar(ch);
    }
    end 1-10 */
    
    /* start 1-12 
     * definition of a word: any sequence of characters that does not contain a blank, tab, or newline

    int nl, nw, nc, state;
    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state != OUT) { // if previous character is not whitespace, newline, nor tab, then print a new line. Otherwise, don't print a new line
                state = OUT;
                putchar('\n');
            }
            continue;
        } else if (state == OUT) {
            state = IN;
            ++nw;
        }
        putchar(c);
    }
    printf("%d %d %d\n", nl, nw, nc);
     end 1-12 */

    /* start 1-13
    int c, i, j;
    int nl, nw, nc, state, wLength;
    int nwLength[MAX_WORD_LENGTH];  // keep frequencies of word length
    state = OUT;
    nl = nw = nc = 0;
    wLength = 0;
    
    for (i = 0; i < MAX_WORD_LENGTH; ++i)
        nwLength[i] = 0;
    
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t') {
            if (state != OUT) {
                state = OUT;
                putchar('\n');
                ++nwLength[wLength];
            }
            continue;
        } else if (state == OUT) {
            state = IN;
            ++nw;
            wLength = 0;
        }
        
        putchar(c);
        
        // if come here, then we must be inside a word (state == IN)
        ++wLength;
    }
    printf("%d %d %d\n", nl, nw, nc);
    
    printf("Histogram\n");
    for (i = 1; i < MAX_WORD_LENGTH; ++i) {
        if (nwLength[i] == 0)
            continue;
        
        printf("%3d characters: ", i);
        for (j = 1; j <= nwLength[i]; ++j)
            printf("- ");
        printf("\n");
    }
    1-13 end */

    /* start 1-14

    int c, i, nwhite, nother, j;
    int ndigit[10];
    
    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;
    
    while ((c = getchar()) != EOF)
        if (c >= '0' && c <= '9')
            ++ndigit[c-'0'];
        else if (c == ' ' || c == '\n' || c == '\t')
            ++nwhite;
        else
            ++nother;
    
    printf("digits =");
    for (i = 0; i < 10; ++i)
        printf(" %d", ndigit[i]);
    printf(", white space = %d, other = %d\n", nwhite, nother);
    printf("Histogram\n");
    for (i = 0; i < 10; ++i) {
        printf("%2d : ", i);
        for (j = 1; j <= ndigit[i]; ++j)
            printf("- ");
        printf("\n");
    }
    end 1-14 */
    
    /* print the longest input line
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];
    
    max = 0;
    while ((len = mygetline(line, MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    if (max > 0)    /* there was a line
        printf("%s", longest);
    */
    
    /* 1-16 ??? */
    /* 1-17 starts
    int len;
    char line[MAXLINE];

    while ((len = mygetline(line, MAXLINE)) > 0) {
        if (len > CUTOFF_LENGTH)
            printf("%s", line);
    }
     1-17 end */
    
    /* 1-18 start
    int len;
    char line[MAXLINE];
    
    while ((len = getLineRmTrailing(line, MAXLINE)) != 0) {
        if (len > 0)
            printf("%s\n", line);
        if (len == 0)
            break;
    }
    1-18 end */
    
    /* 1-19 start 1-18 end */
    int len;
    char line[MAXLINE];
    
    while ((len = reverse(line)) > 0)
        printf("%s\n", line);

    return 0;
}

/* power:   raise base to n-th power; n >= 0 */
int power(int base, int n)
{
    int i, p;
    
    p = 1;
    for (i = 1; i <= n; ++i)
        p = p * base;
    return p;
}

/* getline: read a line into s, return length */
int mygetline(char s[], int lim)
{
    int c = 0, i;
    
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy:    copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i = 0;
    
    while ((to[i] = from[i]) != '\0')
        ++i;
}

int getLineRmTrailing(char s[], int lim)
{
    int c = 0, i;
    
    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    
    if (i == lim-1 || c == EOF)
        goto done;
    
    while ((i-1 >= 0) && ((s[i-1] == ' ') || (s[i-1] == '\t'))) {
        --i;
    }
    
    if (i == 0)
        goto blankline;
    
done:
    s[i] = '\0';
    return i;

blankline:
    s[i] = '\0';
    return -1;
}

int reverse(char s[])
{
    int c = 0, i, j;
    char *r = NULL;
    
    r = malloc(sizeof((char*)s));
    
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
        r[i] = c;
    }
    if (c == '\n') {    // '\n' is also a character that we want to reverse. If we don't want to account for '\n', remove this if statement.
        r[i] = c;
        i++;
    }
    if (i == 0)     // EOF
        return 0;
    
    s[i] = '\0';    // set last character in the string to NULL
    
    // s is the reverse of the input, which is currently stored in r
    for (j = 0; --i >= 0; ++j) {
        s[j] = r[i];
    }
    
    return j+1;
}