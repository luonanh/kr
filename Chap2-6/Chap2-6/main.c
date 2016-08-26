//
//  main.c
//  Chap2-6
//
//  Created by Anh Luong on 7/7/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);

int main(int argc, const char * argv[]) {
    printf("~0 = %x\n", ~0);
    printf("-1 = %x\n", -1);
    printf("setbits %x\n", setbits(0xa5a5, 11, 8, 0xaabb));
    printf("invert %x\n", invert(0xa5a5, 11, 12));
    printf("rightrot %x\n", rightrot(0xaa55aa55, 3));
    return 0;
}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p+1-n)) & ~(~0 << n);
}

/* setbits: returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    y &= ~(~0 << n);    // rightmost n bits of y
    printf("%x\n",y);
    x &= ~((~0 << (p+1-n)) ^ (~0 << (p+1)));   // x clear n bits to the right, starting from p
    printf("%x\n",x);
    y = y << (p+1-n);   // shift left the rightmost n bits of y the proper number of bits
    printf("%x\n",y);
    return x | y;
}

/* invert:  returns x with the n bits that begin at position p inverted, leaving the others unchanged */
unsigned invert(unsigned x, int p, int n)
{
    unsigned mask = (~0 << (p+1-n)) ^ (~0 << (p+1));
    return x^mask;
}

/* rightrot:    returns the value of the integer x rotated to the right by n positions */
unsigned rightrot(unsigned x, int n)
{
    unsigned nRight = (x & ~(~0 << n)) << (8*sizeof(unsigned) - n);
    x >>= n;
    return x | nRight;
}