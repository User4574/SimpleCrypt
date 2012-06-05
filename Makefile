CFLAGS=-Wall -Wextra -O3

encrypt:	encrypt.c
	gcc ${CFLAGS} ${EFLAGS} -o $@ $^

install:
	cp encrypt /usr/local/bin/encrypt

uninstall:
	rm /usr/local/bin/sc-encrypt

clean:
	rm encrypt
