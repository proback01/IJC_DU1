// ppm.h
// Řešení IJC-DU1, příklad b), 17.3.2021
// Autor: Viktor Kubec, FIT
// Přeloženo: gcc 9.3.0

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

struct ppm * ppm_read(const char * filename);
void ppm_free(struct ppm *p);
