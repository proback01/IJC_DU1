// steg-decode.c
// Řešení IJC-DU1, příklad b), 17.3.2021
// Autor: Viktor Kubec
// Přeloženo: gcc 9.3.0
#include "bitset.h"
#include "eratosthenes.c"
#include "ppm.c"
#include "error.c"
#include <math.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        error_exit("Spatne argumenty programu.\n");
    }
    else
    {
        struct ppm*myImg = ppm_read(argv[1]);
        if(!myImg)
            error_exit("Soubor neni validni.\n");
        unsigned int size = 3*myImg->ysize*myImg->xsize;
        bitset_alloc(erat_image,size);
        eratosthenes(erat_image);
        int zeroCounter = 0;
        unsigned char message[size];
        unsigned long single_input_bit = 0;
        unsigned long iter_j = 0;
        unsigned int iter_i = 0;
        for(iter_i=23;iter_i<size;iter_i++)
        {
            if(!bitset_getbit(erat_image,iter_i))
            {
                single_input_bit = (myImg->data[iter_i] & 1);
                if(!single_input_bit)
                    zeroCounter++;
                else
                    zeroCounter = 0;
                message[iter_j / 8] |= (single_input_bit << (iter_j % 8));
                if(zeroCounter == 8)
                    break;
                iter_j++;
            }
        }
        if(iter_i == size && zeroCounter != 8)
        {
            ppm_free(myImg);
            bitset_free(erat_image);
            error_exit("Zprava neni korektne ukoncena.\n");
        }
        printf("%s\n",message);
        bitset_free(erat_image);
        ppm_free(myImg);
    }
    return 0;
}
