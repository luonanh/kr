//
//  main.c
//  Chapter1-22
//
//  Created by Anh Luong on 7/5/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>

#define MAX_COLUMN  4
#define MAXLINE 1000    /* maximum input line length */
#define TRUE    1
#define FALSE   0

int fold(char s[]);

int main(int argc, const char * argv[]) {
    int len;
    char line[MAXLINE];
    
    while ((len = fold(line)) > 0)
        printf("%s\n",line);
    return 0;
}

int fold(char s[])
{
    int i, c, len, lastSpaceBeforeMaxCol = -1, firstSpaceAfterMaxCol = -1;
    char r[MAXLINE];
    int spaceFound = FALSE;
    
    // 1st iteration, read in the line
    // find  the last space position before MAX_COLUMN
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i) {
        r[i] = s[i] = c;
        if (c == ' ') {
            spaceFound = TRUE;
            if (i < MAX_COLUMN)
                lastSpaceBeforeMaxCol = i;
            else {
                if (firstSpaceAfterMaxCol == -1)    // initialize firstSpaceAfterMaxCol to proper value if it's not yet
                    firstSpaceAfterMaxCol = i;
            }
        }
    }
    
    if (c == '\n') {
        r[i] = c;
        s[i++] = c;
    }
    s[i] = '\0';
    r[i] = '\0';
    len = i;
    
    if (len <= MAX_COLUMN+1)
        return len;
    
    if (spaceFound == FALSE)    // no space, then print as is
        return len;
    
    if (lastSpaceBeforeMaxCol == -1) {  // no space before MAX_COLUMN
        s[firstSpaceAfterMaxCol] = '\n';
    } else {
        s[lastSpaceBeforeMaxCol] = '\n';
    }
        
    
    return i;   // return the length of new array
}