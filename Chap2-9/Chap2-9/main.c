//
//  main.c
//  Chap2-9
//
//  Created by Anh Luong on 7/7/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>

int bitcount(unsigned x);
int bitcount2(unsigned x);

int main(int argc, const char * argv[]) {
    printf("%d\n", bitcount(0xaa55));
    printf("%d\n", bitcount2(0xaa55));
    printf("%d\n", bitcount2(0x1122));
    printf("%d\n", bitcount2(0x3311));
    return 0;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
    int b;
    
    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}

int bitcount2(unsigned x)
{
    int b;
    
    for (b = ((x != 0) ? 1 : 0); (x &= (x-1)) != 0; b++);
    return b;
}

/* lower:   convert c to lower case; ASCII only */
int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}