C=gcc
CFLAGS= -Wall -g
DFLAGS= functions.c
PROGS= main

all: $(PROGS)

%: %.c
	        $(CC) $(CFLAGS) $(DFLAGS) $< -o $@

clean:
	        rm -f $(PROGS) *.o ~*
