CFLAGS=-Wall -Wextra

encrypt:	encrypt.c
	gcc ${CFLAGS} ${EFLAGS} -o $@ $^

install:
	cp encrypt /usr/local/bin/encrypt

uninstall:
	rm /usr/local/bin/encrypt

clean:
	rm encrypt
