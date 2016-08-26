//
//  main.c
//  Chap4-14
//
//  Created by Anh Luong on 7/12/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>

#define swap(t,x,y) {t c; c = x; x = y; y = c;}

int main(int argc, const char * argv[]) {
    int i = 1, j = 2;
    
    printf("%d %d\n", i, j);
    swap(int, i, j);
    printf("%d %d\n", i, j);
    return 0;
}

