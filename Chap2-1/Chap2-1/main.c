//
//  main.c
//  Chap2-1
//
//  Created by Anh Luong on 7/6/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(int argc, const char * argv[]) {
    /*
    char c;
    short int si;
    int i;
    long int li;
     */
    
    printf("size of char %lu\n", sizeof(char));
    printf("%d to %d\n", CHAR_MIN, CHAR_MAX);
    printf("size of short int %lu\n", sizeof(short int));
    printf("%d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("size of int %lu\n", sizeof(int));
    printf("%d to %d\n", INT_MIN, INT_MAX);
    printf("size of long int %lu\n", sizeof(long int));
    printf("%ld to %ld\n", LONG_MIN, LONG_MAX);
    return 0;
}
