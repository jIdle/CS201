CC=gcc
CFLAGS= -Wall -g
DFLAGS=
PROGS= setBits showBits
all: $(PROGS)

%: %.c
		$(CC) $(CFLAGS) $(DFLAGS) $< -o $@ -lm

clean:
		rm -f $PROGS) *.o ~*
