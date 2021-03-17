// primes.c
// Řešení IJC-DU1, příklad a), 17.3.2021
// Autor: Viktor Kubec, FIT
// Přeloženo: gcc 9.3.0
#include <math.h>
#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bitset.h"
#include "eratosthenes.c"
#include "error.h"

int main()
{
    clock_t start;
    start = clock();
    bitset_alloc(myArr2,UPPER_BOUND);
    int cnt = 0;
    bitset_index_t idx;
    int lastTen[PRINTABLE_PRIMES];
    eratosthenes(myArr2);
    idx = UPPER_BOUND-1;
    for(;;)
    {
        if(!bitset_getbit(myArr2,idx))
        {
            lastTen[cnt] = idx;
            cnt++;
        }
        idx--;
        if(cnt >= PRINTABLE_PRIMES)
            break;
    }
    while(cnt)
    {
        cnt--;
        printf("%d\n",lastTen[cnt]);
    }
    bitset_free(myArr2);
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}
