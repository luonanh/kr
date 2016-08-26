//
//  main.c
//  Chap3-2
//
//  Created by Anh Luong on 7/10/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>

#define MAX_LINE    1000    // the max number of characters per line

int countChar(void);
void escape(char s[], char t[]);
void escapeReverse(char s[], char t[]);

int main(int argc, const char * argv[]) {
    // countChar();
    int c, i = 0;
    char input[MAX_LINE], output[MAX_LINE];
    
    while ((c = getchar()) != EOF) {
        input[i++] = c;
    }
    
    escape(input, output);
    printf("Output %s\n", output);
    escapeReverse(output, input);
    printf("Input %s\n", input);
    return 0;
}

int countChar(void)
{
    int c, i, nwhite, nother, ndigit[10];
    
    nwhite = nother = 0;
    for (i = 0; i < 10; ++i)
        ndigit[i] = 0;
    
    while ((c = getchar()) != EOF) {
        switch (c) {
            case '0' : case '1' : case '2' : case '3' : case '4' : \
            case '5' : case '6' : case '7' : case '8' : case '9' :
                ndigit[c - '0']++;
                break;
            case ' ':
            case '\n':
            case '\t':
                nwhite++;
                break;
            default:
                nother++;
                break;
        }
    }
    printf("digits = ");
    for (i = 0; i < 10; i++)
        printf(" %d", ndigit[i]);
    printf(", white space = %d, other = %d\n", nwhite, nother);
    return 0;
}

/* escape:  converts characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. */
void escape(char s[], char t[])
{
    int c, i, j;
    
    i = j = 0;
    while ((c = s[i]) != '\0') {
        switch (c) {
            case '\n':
                t[j++] = '\\';
                t[j++] = 'n';
                i++;
                break;
            case '\t':
                t[j++] = '\\';
                t[j++] = 't';
                i++;
                break;
            default:
                t[j++] = s[i++];
        }
    }
    t[j] = '\0';
}

void escapeReverse(char s[], char t[])
{
    int c, i, j;
    
    i = j = 0;
    while ((c = s[i]) != '\0') {
        switch (c) {
            case 'n':
                if (i > 0 && s[i-1] == '\\')
                    t[--j] = '\n';
                i++;
                j++;
                break;
            case 't':
                if (i > 0 && s[i-1] == '\\')
                    t[--j] = '\t';
                i++;
                j++;
                break;
            default:
                t[j++] = s[i++];
        }
    }
    t[j] = '\0';
}