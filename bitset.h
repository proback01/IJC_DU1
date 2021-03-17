// bitset.h
// Řešení IJC-DU1, příklad a), 17.3.2021
// Autor: Viktor Kubec, FIT
// Přeloženo: gcc 9.3.0
#pragma once
#include "error.h"
#include <limits.h>
#include <assert.h>
typedef unsigned long bitset_t;
typedef unsigned long bitset_index_t;

#define bits2longs(velikost) \
((velikost+(sizeof(bitset_t)*8-1))/(sizeof(bitset_t)*8)+1)

#define arr_idx(velikost) \
((velikost+(sizeof(bitset_t)*8-1))/(sizeof(bitset_t)*8))

#define bitset_create(jmeno_pole,velikost) \
static_assert(velikost>=0,"Len can't be negative.");\
bitset_t bit_arr[bits2longs(velikost)] = {velikost};

#define bitset_alloc(jmeno_pole,velikost) \
assert(velikost <= ULONG_MAX);            \
bitset_t*jmeno_pole = (bitset_t*)calloc(bits2longs(velikost),sizeof(bitset_t)); \
if(jmeno_pole==NULL)                      \
{\
    printf("bitset_alloc: Chyba alokace pameti.\n");\
    exit(0);\
}                                     \
jmeno_pole[0] = velikost;

#ifndef USE_INLINE

#define bitset_free(jmeno_pole) \
free(jmeno_pole);

#define bitset_size(jmeno_pole) \
jmeno_pole[0]

#define bitset_setbit(jmeno_pole,index,vyraz) \
if(index >= bitset_size(jmeno_pole)) \
{ \
    error_exit("bitset_setbit: Index %ld je mimo rozsah 0..%ld\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole)-1); \
}\
vyraz ? ((jmeno_pole[arr_idx(index)]) |= ((1UL<<(index%(sizeof(bitset_t)*8))))) \
:\
((jmeno_pole[arr_idx(index)]) &= (~(1UL<<(index%(sizeof(bitset_t)*8)))))

#define bitset_getbit(jmeno_pole,index) (\
((unsigned long)index >= bitset_size(jmeno_pole))\
   ? (error_exit("bitset_getbit: Index %ld je mimo rozsah 0..%ld\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole)-1), 0)\
:\
    (((jmeno_pole[arr_idx(index)]) & ((1UL<<(index%(sizeof(bitset_t)*8))))) ? 1 : 0)\
)
#else
extern inline void bitset_free(bitset_t jmeno_pole[])
{
    free(jmeno_pole);
}

extern inline bitset_index_t bitset_size(bitset_t jmeno_pole[])
{
    return jmeno_pole[0];
}

extern inline void bitset_setbit(bitset_t jmeno_pole[],bitset_index_t index,int vyraz)
{
    if(index >= bitset_size(jmeno_pole)) \
    {
        error_exit("bitset_setbit: Index %ld je mimo rozsah 0..%ld\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole)-1);
    }
    vyraz ? ((jmeno_pole[arr_idx(index)]) |= ((1UL<<(index%(sizeof(bitset_t)*8)))))
    :
    ((jmeno_pole[arr_idx(index)]) &= (~(1UL<<(index%(sizeof(bitset_t)*8)))));
}

extern inline int bitset_getbit(bitset_t jmeno_pole[],bitset_index_t index)
{
    if(index >= bitset_size(jmeno_pole))
    {
        error_exit("bitset_getbit: Index %ld je mimo rozsah 0..%ld\n", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole)-1);
    }
    return (((jmeno_pole[arr_idx(index)]) & ((1UL<<(index%(sizeof(bitset_t)*8))))) ? 1 : 0) ;
}
#endif
