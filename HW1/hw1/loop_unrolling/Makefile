CC=gcc
CFLAGS=-O2 -std=c99

all: loop unroll

%: %.c
	$(CC) $(CFLAGS) -o $@ $< 

clean:
	rm -f loop unroll *~
