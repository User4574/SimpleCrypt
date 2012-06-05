CFLAGS=-Wall -Wextra

all:
	make encrypt
	make decrypt

encrypt:	encrypt.c
	gcc -o $@ $^ ${CFLAGS}
decrypt:	decrypt.c
	gcc -o $@ $^ ${CFLAGS}
