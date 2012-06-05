CFLAGS=-Wall -Wextra -O3

all:
	make encrypt
	make decrypt

encrypt:	encrypt.c
	gcc ${CFLAGS} -o $@ $^
decrypt:	decrypt.c
	gcc ${CFLAGS} -o $@ $^

install:
	cp encrypt /usr/local/bin/encrypt
	cp decrypt /usr/local/bin/decrypt

uninstall:
	rm /usr/local/bin/sc-encrypt
	rm /usr/local/bin/sc-decrypt

clean:
	rm encrypt
	rm decrypt
