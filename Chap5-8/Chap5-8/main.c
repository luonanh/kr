//
//  main.c
//  Chap5-8
//
//  Created by Anh Luong on 7/13/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>

char *month_name(int n);

int main(int argc, const char * argv[]) {
    printf("%s\n", month_name(10));
    return 0;
}

/* month_name:  return name of n-th month */
char *month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };
    
    //return (n < 1 || n > 12) ? name[0] : name[n];
     return (n < 1 || n > 12) ? *name : *(name + n);
}