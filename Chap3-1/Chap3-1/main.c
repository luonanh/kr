//
//  main.c
//  Chap3-1
//
//  Created by Anh Luong on 7/10/16.
//  Copyright © 2016 Anh Luong. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <sys/times.h>

#define MAX_ITEM    10000

int binsearch(int x, int v[], int n);
int binsearch2(int x, int v[], int n);
int main(int argc, const char * argv[]) {
    int i;
    int v[MAX_ITEM];
    
    for (i = 0; i < MAX_ITEM; ++i) {
        v[i] = i;
    }
    
    clock_t start, end;
    /*
    clock_t s, e;
    tms t;
     */
    
    start = clock();
    i = binsearch(25, v, MAX_ITEM);
    printf("v[%d] = %d\n", i, v[i]);
    end = clock();
    printf("Time elapsed: %lu\n", (end-start));
    printf("CLOCKS_PER_SEC = %d\n", CLOCKS_PER_SEC);
    return 0;
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high)/2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    // found match~/dow
            return mid;
    }
    
    return -1;  // no match
}

int binsearch2(int x, int v[], int n)
{
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    mid = (low + high)/2;
    while (low < high && low != mid && mid != high) {
        //mid = (low + high)/2;
        if (x < v[mid]) {
            high = mid - 1;
        }
        else    // if (x >= v[mid])
            low = mid;
        mid = (low + high)/2;
        printf("%d %d %d\n", low, mid, high);
    }
    
    if (x == v[low])
        return low;
    else if (x == v[mid])
        return mid;
    else if (x == v[high])
        return high;
    else
        return -1;  // no match
}
