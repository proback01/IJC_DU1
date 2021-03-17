#==========================================================
PRGNAME = primes
PRGNAME-I = primes-i
PRGNAME-STEG = steg-decode

all: $(PRGNAME) $(PRGNAME-I) $(PRGNAME-STEG)

run: all
	./primes
	./primes-i

clean:
	rm -f primes
	rm -f primes-i
	rm -f steg-decode
#==========================================================
CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra
LDFLAGS = -lm -O2
#==========================================================

$(PRGNAME): primes.c eratosthenes.c  bitset.h error.c
	$(CC) $(CFLAGS) primes.c error.c $(LDFLAGS) -o $(PRGNAME)

$(PRGNAME-I): primes.c eratosthenes.c bitset.h error.c
	$(CC) $(CFLAGS) -DUSE_INLINE primes.c error.c $(LDFLAGS) -o $(PRGNAME-I)

$(PRGNAME-STEG): steg-decode.c error.c error.h ppm.c ppm.h eratosthenes.c
	$(CC) $(CFLAGS) steg-decode.c -o $(PRGNAME-STEG)
