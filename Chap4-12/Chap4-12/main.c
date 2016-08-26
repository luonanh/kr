//
//  main.c
//  Chap4-12
//
//  Created by Anh Luong on 7/12/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <string.h>

void printd(int n);
void myqsort(int v[], int left, int right);
int itoa(int n , char s[]);
void reverse(char s[]);

int main(int argc, const char * argv[])
{
    /*
     int n = -12345;
     
     printd(n);
     printf("\n");
     */
    int v[] = {10, -9, -8, 7, 6, 5, 4, 3, 2, 1};
    int n = sizeof(v)/sizeof(int);
    int i;
    //myqsort(v, 0, sizeof(v)/sizeof(int) - 1);
    myqsort(v, 0, n-1);
    
    for (i = 0; i < n; i++) {
        printd(v[i]);
        printf(" ");
    }
    printf("\n");
    
    i = -12345;
    char s[100];
    s[itoa(i, s)] = '\0';;
    printf("\n%lu\n", strlen(s));
    printf("%s\n", s);
    reverse(s);
    printf("%s\n", s);
    
    return 0;
}

/* printd:  print n in decimal */
void printd(int n)
{
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    
    if (n / 10) {
        printd(n / 10);
    }
    putchar(n % 10 + '0');
}

/* myqsort: sort v[left]...v[right] into increasing order */
void myqsort(int v[], int left, int right)
{
    int i, last;  // last the leftmost index of v[] such that v[last] >= partition elem
    void swap(int v[], int i, int j);
    
    if (left >= right)                    // do nothing if array contains fewer than 2 elements
        return;
    
    swap(v, left, (left + right) / 2);    // move partition elem to v[0]
    last = left;
    for (i = left + 1; i <= right; i++) { // partition
        if (v[i] < v[left])
            swap(v, ++last, i);
    }
    swap(v, left, last);                  // restore partition elem
    myqsort(v, left, last - 1);
    myqsort(v, last + 1, right);
}

/* swap:  interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
    int c;
    
    c = v[i];
    v[i] = v[j];
    v[j] = c;
}

/* from 3-6
void reverse(char s[])
{
    int i, j;
    char c;
    
    for (i = 0, j = (int)strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[])
{
    int i, sign;
    
    if ((sign = n) < 0)
        n = -n;
    
    i = 0;
    do {
        s[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    
    if (sign < 0)
        s[i++] = '-';
    
    s[i] = '\0';
    reverse(s);
}
*/

int itoa(int n , char s[])
{
    int i = 1;
    if (n < 0) {
        s[0] = '-';
        n = -n;
    }
    
    if (n / 10) {
        i = itoa(n / 10, s);
    }
    //printf("0x%lu %d\n", s, i);
    s[i++] = n % 10 + '0';
    return i;
}

void reverseR(char s[], int left, int right)
{
    int c;
    
    if (left >= right)
        return;
    printf("left %d %c | right %d %c\n", left, s[left], right, s[right]);
    c = s[left];
    s[left] = s[right];
    s[right] = c;
    reverseR(s, ++left, --right);
}

void reverse(char s[])
{
    reverseR(s, 0, (int)strlen(s) - 1);
}
