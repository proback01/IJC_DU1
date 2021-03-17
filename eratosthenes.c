// eratosthenes.c
// Řešení IJC-DU1, příklad a), 17.3.2021
// Autor: Viktor Kubec, FIT
// Přeloženo: gcc 9.3.0
#define UPPER_BOUND 200*1000*1000
#define PRINTABLE_PRIMES 10

#include <math.h>
#include "error.h"

void eratosthenes(bitset_t* bit_arr)
{
    bitset_index_t root = sqrt(UPPER_BOUND);
    for(bitset_index_t i=2;i<=root;i++)
    {
        if(!bitset_getbit(bit_arr,i))
        {
            for(bitset_index_t j = i*i; j<bitset_size(bit_arr);j+=i)
            {
                bitset_setbit(bit_arr, j, 1);
            }
        }
    }
}
