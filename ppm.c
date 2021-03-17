// ppm.c
// Řešení IJC-DU1, příklad b), 17.3.2021
// Autor: Viktor Kubec, FIT
// Přeloženo: gcc 9.3.0
#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include "error.h"

void ppm_free(struct ppm *p)
{
    free(p);
}

struct ppm * ppm_read(const char * filename)
{
    FILE*myImgFile;
    int read,size,maxVal;
    unsigned width,height;
    char ch;

    myImgFile = fopen(filename,"rb");
    if(!myImgFile)
    {
        warning_msg("Soubor %s se nepodarilo otevrit.\n",filename);
        return  NULL;
    }

    if (fscanf(myImgFile,"P%c\n",&ch) != 1 || ch != '6')
    {
        warning_msg("Soubor %s neni ve formatu P6.\n",filename);
        return NULL;
    }

    ch = getc(myImgFile);
    while (ch == '#')
    {
        do {
            ch = getc(myImgFile);
        } while (ch != '\n');
        ch = getc(myImgFile);
    }

    ungetc(ch, myImgFile);

    fscanf(myImgFile,"%u%u%d\n",&width,&height,&maxVal);

    if(maxVal != 255)
    {
        warning_msg("Obrazek neni true-color.\n");
        return NULL;
    }

    size = width*height*3;
    struct ppm* myPicture = malloc(sizeof(struct ppm)+size*sizeof(char));
    if(!myPicture)
    {
        warning_msg("Pamet se nepodarilo alokovat.\n");
        return NULL;
    }
    myPicture->xsize = width;
    myPicture->ysize = height;

    read = fread(myPicture->data,1,size,myImgFile);
    if (read != size)
    {
        warning_msg("Nemohu cist data ze souboru.\n");
        ppm_free(myPicture);
        return NULL;
    }
    fclose(myImgFile);
    return myPicture;
}
