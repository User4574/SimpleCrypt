CFLAGS=-Wall -Wextra

all: encrypt decrypt

%:	%.c
	gcc ${CFLAGS} -o $@ $^

install: encrypt decrypt
	cp encrypt /usr/local/bin/encrypt
	cp decrypt /usr/local/bin/decrypt

uninstall: /usr/local/bin/encrypt /usr/local/bin/decrypt
	rm /usr/local/bin/encrypt
	rm /usr/local/bin/decrypt

clean: encrypt decrypt
	rm encrypt
	rm decrypt
